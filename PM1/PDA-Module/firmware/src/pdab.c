     /*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "pdab.h"
#include "message_exchange.h"

/* task busy flags - used during test to see if we can go to sleep */
#define PDAB_TASK_BUSY          0x0001
#define SCAN_TASK_BUSY          0x0002
#define USB_TASK_BUSY           0x0004
#define ADC_TASK_BUSY           0x0008
#define LSC_TASK_BUSY           0x0010
#define DAC_TASK_BUSY           0x0020
#define DPOT_TASK_BUSY          0x0040
#define PIC_COMMS_TASK_BUSY     0x0080
#define MIN_AWAKE_DELAY         0x0100
#define DEBUG_BUSY              0x0200
#define SCAN_BUSY               0x0400
#define DSPIC_COMMS_TASK_BUSY   0x0800

//#define MAX_COMMAND_LENGTH      128
/* minimum time to stay awake after sleep to allow full message reception */
#define MINIMUM_AWAKE_TIME_MS   2

#define DEBUG_RXID_PING             0x01
#define DEBUG_RXID_LSC_REQ_STATUS   0x80
#define DEBUG_RXID_LSC_START_SCAN   0x81
#define DEBUG_RXID_LSC_START_STOP   0x82
#define DEBUG_RXID_LSC_DEFINE_LIM   0x83

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the PDAB_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

PDAB_DATA pdabData;

DEVICE_STATISTICS_t device_statistics;

_STATUS_BUFFER MAKE_BUFFER_DMA_READY pdabStatus;

extern _SCAN_BUFFER MAKE_BUFFER_DMA_READY _scan_buffer[PDAB_TOTAL_SCAN_BUFFERS];

DEVICE_SETTINGS_t device_settings;

volatile uint16_t pdab_task_timeout_ms = 0;
static uint32_t stay_awake_delay = 0;

// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************

//void (*TMR_CALLBACK)(uint32_t status, uintptr_t context);
void pdab_millisecond_timer_interrupt(uint32_t status, uintptr_t context){
#ifndef ENABLE_DEBUG
    debug_millisecond_timer_interrupt(0, 0);
#endif
    drv_laser_timer();
    pic_transmit_timer();
    dspic_transmit_timer();
    drv_lsc_millisecond_tick();
    if(pdab_task_timeout_ms > 0 ){
        pdab_task_timeout_ms --;
    }
    if(stay_awake_delay > 0)
    {
        stay_awake_delay--;
    }

    static uint ms = 1000;
    if(ms != 0)
    {
        ms--;
    }
    else {
        ms = 1000;
        if(pdabData.eeprom_stats_need_update == true){
            EEPROM_save_statistics();
            pdabData.eeprom_stats_need_update = false;
        }
        //any rarer task
        //dprintf_colour("[RED]CP0: %ul, %ul[WHITE]\r\n", _CP0_GET_COUNT(), _CP0_GET_COMPARE());
    }
    //debug_receive_process();
}

void debug_inpack_process(uint8_t * pack){

    switch(pack[0]){

        case DEBUG_RXID_PING:

            DBG_LEDR_OutputEnable();
            DBG_LEDR_Toggle();

            break;

        case DEBUG_RXID_LSC_REQ_STATUS:

            break;
        case DEBUG_RXID_LSC_START_SCAN:
            drv_lsc_start_scanning();

            break;
        case DEBUG_RXID_LSC_START_STOP:
            drv_lsc_stop_scanning();
            break;
        case DEBUG_RXID_LSC_DEFINE_LIM:
            drv_lsc_define_limits();
            break;

            break;


        default:

            break;
    }

}

// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************

static void PDAB_Send_UART_Status(void);
static inline void Software_Reset(void);
static void PDAB_Send_Settings(void);
static void PDAB_Update_Settings(void);
static void send_USB_DCS_ping(void);

// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************

/*******************************************************************************
  Function:
    void blocking_delay ( uint ms )

  Remarks:
    See prototype in pdab.h.
*******************************************************************************/
void blocking_delay(uint ms)
{
    int i,j;
    for(j=0;j<ms;j++)
    {
        for(i=0;i<50000;i++)
        {Nop();}
    }
}

/*******************************************************************************
  Function:
    void PDAB_Initialize ( void )

  Remarks:
    See prototype in pdab.h.
*******************************************************************************/
void PDAB_Initialize ( void )
{
    // Place the App state machine in its initial state.

    pdabData.state = PDAB_STATE_INIT;
    pdabData.previous_state = PDAB_STATE_IDLE;
    pdabData.error = 0L;
    pdabData.status = &pdabStatus;
    pdabData.status->DAB.Flags.Zero = true;
    pdabData.status->DAB.Flags.Initialised = false;
    pdabData.comm_interface = COMM_UART;
    pdabData.manual_offset = false;
    pdabData.usb_enable = true;
    pdabData.power_off_busy = false;

    PDAB_Error_Status(1,2);//set status 'no error'

    device_settings.LCD_BRIGHTNESS = 101;
    device_settings.LED_BRIGHTNESS = 200;
    device_settings.LED_FADE_RATE = 0;
    device_settings.VOLTAGE_TRESHOLD = 12;
    device_settings.P1_TRESHOLD = 26214;
    device_settings.P2_TRESHOLD = 786;
    device_settings.MIN_SEPARATION = 300;
    device_settings.MAX_SEPARATION = 800;
    device_settings.MIN_FWHM = 35;
    device_settings.MAX_FWHM = 75;
    device_settings.CAMERA_HSTART = 169;
    device_settings.CAMERA_VSTART = 25;


    TMR2_CallbackRegister(&pdab_millisecond_timer_interrupt, 0);
    TMR2_Start();
    TMR2_InterruptEnable();

    pdabData.usb_software = USB_SOFTWARE_PCC; //use pcontrol confocal as default software
}

static inline void Software_Reset(void)
{
    /* Perform system unlock sequence */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    RSWRSTSET = _RSWRST_SWRST_MASK;
    (void) RSWRST;
    while(1);
}

/******************************************************************************
  Function:
    void PDAB_Task(void)

  Remarks:
    See prototype in pdab.h.
 */
bool PDAB_Task(void)
{
    static bool peripherals_initialised = false;
    static bool lda_ready = false;

    /* Error checking */
    if( drv_laser_get_error() )
    {

    }
    else if( drv_lsc_get_error() )
    {

    }
    switch(pdabData.state)
    {
        case PDAB_STATE_INIT:

#ifndef DISABLE_PERIPHERALS
            if(false == peripherals_initialised)
            {
                //remove clear the terminal
                dprintf("\033\143");                                                // Clear terminal
                dprintf("\033[3JResetting terminal and clearing scroll-back\r\n");  // Clear scroll back
                if(SILICON_REVISION_B2 == DEVIDbits.VER || SILICON_REVISION_A3 == DEVIDbits.VER)
                //if(true) // for PDAB with PIC32MZ1024EFH100 MCU
                {
                    dprintf_colour("[BROWN]PDAB Initialising v%.2f Build %03d Silicon ver %d... [WHITE]\r\n", VERSION, BUILD, DEVIDbits.VER);
                }
                else
                {
                    dprintf_colour("[RED]ERROR: WRONG SILICON VERSION[WHITE]\r\n");
                    PDAB_Error_Status(1,4);
                }
                pdabData.error = PDAB_Peripheral_Init();
            }
#endif
            if( pdabData.error == NO_ERRORS )
            {
                peripherals_initialised = true;
            }
            else
            {
                dprintf_colour("[RED]ERROR: initialisation failed: %d[WHITE]\r\n", pdabData.error);
                PDAB_Error_Status(1,5);
            }

            static uint timeout_startup = 10000;

            uint i;
            for(i=0;i<250000 * 1;i++){Nop();}
            timeout_startup--;

            if(lda_ready == 0)
            {
                lda_ready = true;
            }

            if(lda_ready)
            {
                if( drv_dac_get_last_error() != DRV_DAC_ERROR_NONE )
                {
                    drv_dac_clear_error();
                    drv_dac_set_power_mode( DRV_DAC_PDM_NORMAL );
                    drv_dac_set_ldac( DRV_DAC_LDAC_DISABLED );
                    drv_dac_set_reference( DRV_DAC_INTERNAL_REF_ON );
                    drv_dac_set_value( DRV_DAC_1, DRV_DAC1_DEFAULT );
                    drv_dac_set_value( DRV_DAC_2, DRV_DAC2_DEFAULT );
                }
                else
                {
                    if( peripherals_initialised && drv_lsc_is_initialised())
                    {
                        PDAB_Zero_Offset();
                        pdabData.previous_state = pdabData.state;
                        pdabData.state = PDAB_STATE_INIT_ZERO_OFF_WAIT;
                    }
                }

                #ifdef DISABLE_LASER_SWITCHING
                drv_laser_on( false );  // Laser ON
                #endif
                
                
            }

            if( pdabData.error != NO_ERRORS )
            {
                pdabData.previous_state = pdabData.state;
                pdabData.state = PDAB_STATE_ERROR;
                dputs_colour("[RED]ERROR: error during initialisation in PDAB_STATE_INIT[WHITE]\r\n");
                PDAB_Error_Status(1,7);
            }
            
            break;

        case PDAB_STATE_INIT_ZERO_OFF_WAIT:

            if(pdabData.previous_state != pdabData.state){

                pdab_task_timeout_ms = 6000u;

                pdabData.previous_state = pdabData.state;
            }

            if( true == pdabData.status->DAB.Flags.Zero){
                pdabData.state = PDAB_STATE_IDLE;
				pdabData.status->DAB.Flags.Initialised = true;
            }else if(pdab_task_timeout_ms ==0){

                dputs_colour("[RED]ERROR: Timed out waiting for zero offset completion [WHITE]\r\n");
                pdabData.state = PDAB_STATE_ERROR;
            }


            break;

        case PDAB_STATE_ERROR:
            #ifdef DEBUG_LEDS_ENABLED
            LED2_Clear();
            #endif

            if( pdabData.previous_state == PDAB_STATE_INIT)
            {
                dputs_colour("[RED]PDAB Initialisation failure.[WHITE]\r\n");
                PDAB_Error_Status(1,8);
            }
            else if(pdabData.previous_state == PDAB_STATE_INIT_ZERO_OFF_WAIT)
            {
                dputs_colour("[RED]PDAB error PDAB_STATE_INIT_ZERO_OFF_WAIT.[WHITE]\r\n");
                PDAB_Error_Status(1,12);
            }
            else
            {
                dputs_colour("[RED]PDAB error occured.[WHITE]\r\n");
                PDAB_Error_Status(1,9);
            }

            pdabData.previous_state = PDAB_STATE_ERROR;
            pdabData.state = PDAB_STATE_IDLE;

            break;

        case PDAB_STATE_IDLE:

            if( pdabData.status->Command != PDAB_CMD_NONE )
            {
                switch( pdabData.status->Command )
                {
                    case PDAB_CMD_RESET:
                        Software_Reset();
                        break;


                    case PDAB_CMD_GET_STATUS:

                        PDAB_Update_Status();

                        break;
                    case PDAB_CMD_SETTINGS_REQUEST:
                        PDAB_Send_Settings();
                        break;
                    case PDAB_CMD_SETTINGS_UPDATE:
                        PDAB_Update_Settings();
                        break;
                    case PDAB_CMD_START_SCANNING:
                        device_statistics.scans_counter += 1;
                        if(pdabData.scan_from_usb == false){
                            pdabData.eeprom_stats_need_update = true;
                        }
                        //send_USB_DCS_data_burst();
                        
                        update_scan_settings();

                        if(drv_lsc_is_initialised()){
                            if( Start_Scanning( pdabData.comm_interface ) )
                            {
                                pdabData.status->DAB.Flags.Scanning = true;
                                if(pdabData.comm_interface == COMM_USB )
                                {
                                    pdabData.status->DAB.Flags.ILED = true;
                                }
                            }
                        }
                        break;

                    case PDAB_CMD_STOP_SCANNING:
                        Stop_Scanning();
                        
                        send_USB_DCS_ping();

                        //delay 10ms removed (coretimer issue)

                        pdabData.status->DAB.Flags.ILED = false;
                        pdabData.status->DAB.Flags.Scanning = false;
                        break;

                    case PDAB_CMD_ZERO_OFFSET:
#ifndef DISABLE_LDA
                        pdabData.status->DAB.Flags.Zero = false;
#endif
                        break;

                    case PDAB_CMD_ADJUST_OFFSET:
#ifndef DISABLE_LDA
                        pdabData.manual_offset = true;

                        if( pdabData.status->Data[0] == DRV_DAC_1 )
                        {
                            drv_dac_set_value(DRV_DAC_1, pdabData.status->Words[1] );
                        }
                        else if( pdabData.status->Data[0] == DRV_DAC_2 )
                        {
                            drv_dac_set_value(DRV_DAC_2, pdabData.status->Words[1] );
                        }
#endif
                        break;

                    case PDAB_CMD_SET_LASER_POWER:
#ifndef DISABLE_LDA
                        #ifndef DISABLE_LASER_POWER
                        PDAB_Set_Power( pdabData.status->Data[0], pdabData.status->Data[1] );
                        #endif
#endif
                        break;

                    case PDAB_CMD_SET_SCAN_SETTINGS:

                        // UART only command so no handler required

                        break;

                    case PDAB_CMD_READ_NPDA_BUFFER:

                        if (pdabData.comm_interface == COMM_USB)
                        {
                            USB_Return_Data( (const void*)get_npda_buffer_ptr(), sizeof(_NPDA_SCAN_BUFFER), USB_DEVICE_TRANSFER_FLAGS_MORE_DATA_PENDING );
                        }

                        break;

                    case PDAB_CMD_LASER_CHECK:
#ifndef DISABLE_LDA
                        drv_laser_on( true );
#endif
                        break;

                    case PDAB_CMD_SET_GAIN:
                    default:
                        break;
                }
                
                PDAB_Command_Complete();
            }

            break;

        default:
            break;
    }

    if ((pdabData.state !=PDAB_STATE_IDLE) && ( pdabData.status->Command != PDAB_CMD_NONE )) // Process these commands if not in IDLE state
    {
        switch( pdabData.status->Command )
        {
            case PDAB_CMD_RESET:
                Software_Reset();
                break;


            case PDAB_CMD_GET_STATUS:

                PDAB_Update_Status();

                break;
            case PDAB_CMD_SETTINGS_REQUEST:
                PDAB_Send_Settings();
                break;
            case PDAB_CMD_SETTINGS_UPDATE:
                PDAB_Update_Settings();
                break;

            default:

                break;
        }
        pdabData.status->Command = PDAB_CMD_NONE;
        pdabData.status->Length = 0U;

        pdabData.previous_state = pdabData.state;

    }

    return (PDAB_STATE_IDLE != pdabData.state);
}
/******************************************************************************
  Function:
    void PDAB_Tasks(void)

  Remarks:
    See prototype in pdab.h.
 */
void PDAB_Transmit_Status(void){
    if (pdabData.comm_interface == COMM_UART)
    {
        dputs_colour("[BROWN]Sending PDAB status via UART[WHITE]\r\n");
        PDAB_Send_UART_Status();
    }
}

void send_USB(const char * data){
    int state = USB_DEVICE_RESULT_ERROR;
    if(USB_is_device_attached())
    {
        state = USB_Return_Data((const void *) data, sizeof(data), USB_DEVICE_TRANSFER_FLAGS_DATA_COMPLETE);
    }
    if ( USB_DEVICE_RESULT_OK == state )
    {
        //fine
    }
    else if( USB_DEVICE_RESULT_ERROR_TRANSFER_QUEUE_FULL == state )
    {
        //too much data
    }
    else
    {
        USB_Clear_Endpoints();
    }
}

void send_USB_counted(const char * data, uint32_t count){
    int state = USB_DEVICE_RESULT_ERROR;
    if(USB_is_device_attached())
    {
        state = USB_Return_Data((const void *) data, count, USB_DEVICE_TRANSFER_FLAGS_DATA_COMPLETE);
    }
    if ( USB_DEVICE_RESULT_OK == state )
    {
        //fine
    }
    else if( USB_DEVICE_RESULT_ERROR_TRANSFER_QUEUE_FULL == state )
    {
        //too much data
    }
    else
    {
        USB_Clear_Endpoints();
    }
}

static void send_USB_DCS_ping(void){
    if(pdabData.usb_software == USB_SOFTWARE_DCS && pdabData.state != PDAB_STATE_SCANNING )
    {
        send_USB("KAL");
    }
}

static void PDAB_Send_Settings(void)
{
    uint32_t command_length = 0;
    #define MAX_COMMAND_LENGTH 128*2
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];
    uint32_t buffer_length = sizeof(DEVICE_SETTINGS_FOR_PI_t);
    DEVICE_SETTINGS_FOR_PI_t device_settings_for_PI;
    
    memcpy(&device_settings_for_PI.settings, &device_settings, sizeof(device_settings));
    memcpy(&device_settings_for_PI.device_name, &pdabData.device_name, sizeof(pdabData.device_name));
    device_settings_for_PI.scans_counter = device_statistics.scans_counter;
    
    command_buffer[0] = (uint8_t)RESPONSE_SETTINGS;
    command_length++;
    command_buffer[command_length] = ':';
    command_length++;
    memcpy(&command_buffer[command_length], &device_settings_for_PI, buffer_length);
    command_length += buffer_length;
    pic_communications_send_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
}
static void PDAB_Update_Settings(void)
{
    memcpy(&device_settings, pdabData.status->Data, sizeof(DEVICE_SETTINGS_t));


    EEPROM_save_settings();
}
/******************************************************************************
  Function:
    void PDAB_Tasks(void)

  Remarks:
    See prototype in pdab.h.
 */
void PDAB_Tasks(void)
{
    uint16_t busy_tasks;

#ifndef DISABLE_DEBUG_LEDS
    test();
#endif

    /* if we're not busy then we can go to sleep */
    busy_tasks = 0;

    if (PDAB_Task())
    {
        busy_tasks |= PDAB_TASK_BUSY;
    }

    /* maintain system services */
    if (SCAN_IDLE != Scan_Tasks() || PDAB_Zero_Busy())
    {
        busy_tasks |= SCAN_TASK_BUSY;
    }

    /* never go to sleep when connected to USB */
    static uint32_t USB_prevent_sleep_timeout_default = 50;
    static uint32_t USB_prevent_sleep_timeout = 0;
    static uint32_t USB_timeout_default = 100;
    static uint32_t USB_timeout = 0;
    if( USBOTGbits.VBUS > 0 )
    {
        USB_prevent_sleep_timeout = USB_prevent_sleep_timeout_default;
        if( pdabData.usb_enable == false )
        {
            if(USB_timeout > 0){
                USB_timeout--;
            }
            else
            {
                USB_timeout = USB_timeout_default;
                dprintf_colour("[YELLOW]USB reconnecting[WHITE]\r\n");
                USBCSR0bits.SOFTCONN=0;
                uint32_t i;
                for(i=0;i<(250000*20);i++){Nop();}//rough 5ms delay
                USBCSR0bits.SOFTCONN=1;
                dputs_colour("[BLUE]Enable USB[WHITE]\r\n");
                pdabData.usb_enable = true;
            }
        }
        else
        {
            USB_Tasks();
        }
    }
    else if( ( false == USB_is_device_attached() ) && ( USBOTGbits.VBUS > 0 ) )
    {
        if( pdabData.usb_enable == true )
        {
            dputs_colour("[BLUE]Disable USB[WHITE]\r\n");
            pdabData.usb_enable = false;
            USB_prevent_sleep_timeout = USB_prevent_sleep_timeout_default;
        }
    }
    if(USB_prevent_sleep_timeout > 0){
        busy_tasks |= USB_TASK_BUSY;
        USB_prevent_sleep_timeout--;
    }

    if (USB_is_device_attached())
    {
        busy_tasks |= USB_TASK_BUSY;
    }

    PDAB_Check_Zero_State();

    /* maintain device drivers */

    if (drv_ext_adc_tasks())
    {
        busy_tasks |= ADC_TASK_BUSY;
    }

    if (drv_lsc_controller_task())
    {
        busy_tasks |= LSC_TASK_BUSY;
    }

    if (drv_dac_ad5667r_controller_task())
    {
        busy_tasks |= DAC_TASK_BUSY;
    }

    if (drv_dpot_ad5247_controller_task())
    {
        busy_tasks |= DPOT_TASK_BUSY;
    }

    if (pic_comms_task())
    {
        busy_tasks |= PIC_COMMS_TASK_BUSY;
    }
    if (dspic_pic_comms_task())
    {
        busy_tasks |= DSPIC_COMMS_TASK_BUSY;
    }
    if (debug_busy())
    {
        busy_tasks |= DEBUG_BUSY;
    }

    if (Scan_Busy())
    {
        busy_tasks |= SCAN_BUSY;
    }

    if(pdabData.power_off_busy == true){
        busy_tasks = DSPIC_COMMS_TASK_BUSY;
    }

    /* after being woken by the start of a command from the PIB */
    /* we need to allow time for the entire message to be received */
    if(stay_awake_delay > 0)
    {
        busy_tasks |= MIN_AWAKE_DELAY;
    }

#ifndef DISABLE_PWR_MGMT
    /* if nothing is happening then we can go to sleep */
    if (0 == busy_tasks)
    {
        dputs_colour("[CYAN]Going to sleep...[WHITE]\r\n");
        SYS_PORT_PinSet(DRV_EXT_ADC_SHDN);
        SYS_PORT_PinSet(DRV_EXT_ADC_OEN);
        SYS_PORT_PinClear( DRV_EXT_ADC_AMP_EN );

        /* allow a PIB command to wake us up */
        U3MODEbits.WAKE = 1;


        bool int_state = SYS_INT_Disable();
        SYSKEY = 0xAA996655;
        SYSKEY = 0x556699AA;
        // now change the OSCCON register
        OSCCONbits.SLPEN = 1;
        // now lock again
        SYSKEY = 0x0;
        SYS_INT_Restore(int_state);

        /* program will stop here until the start of a message is received from the PIB */
        _wait();

        stay_awake_delay = 5;
    }
#endif

}

/*******************************************************************************
 * Function:        uint16_t PDAB_Peripheral_Init( void )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/
uint16_t PDAB_Peripheral_Init( void )
{
    uint16_t error = NO_ERRORS;

//****************************************************************************//
#ifndef DISABLE_LDA

    drv_laser_init();

    IP_VALID_InputEnable();

    MUX1_OutputEnable();
    MUX1_Set();                     // Gain boost: LOW
//  MUX1_Clear();

    if( drv_ext_adc_set_channel(DRV_EXT_ADC_1) )
    {
        error += ADC_INVALID_CHANNEL;
    }

    // Don't need to set the pots as they initialise to 64 on power up
#endif
//****************************************************************************//

    //initialize and load settings and calibration from EEPROM - blocking
    SPI_eeprom_init();

    return error;
}

/*******************************************************************************
 * Function:        void PDAB_Check_Zero_State( void )
 *
 * Precondition:    None
 *
 * Input:           uint8_t channel: Channel to indicate analogue 1 or analogue 2
 *                  uint8_t gain: Input resistance for amplifier 1
 *
 * Output:          None
 *
 * Returns:         No zero if an error occurred
 *
 * Side Effects:    None
 *
 * Overview:        This function configures the gains for respective input
 *                  channel
 *
 * Notes:           None
 ******************************************************************************/
void PDAB_Check_Zero_State( void )
{
    typedef enum
    {
        ZERO_STATE_SET_GAIN=0,
        ZERO_STATE_ZERO_OFFSET,
        ZERO_STATE_SAVE_OFFSET,
    } ZERO_STATES;
    static uint8_t gain_counter = 0;


    static ZERO_STATES zero_state = ZERO_STATE_SET_GAIN;

    if( false == pdabData.manual_offset )
    {
        if (false == pdabData.status->DAB.Flags.Zero )
        {
            if( !drv_dpot_busy() && !drv_dac_busy() && !drv_ext_adc_busy() && drv_lsc_is_initialised() )
            {
                switch(zero_state)
                {
                    case ZERO_STATE_SET_GAIN:
                    {
                        PDAB_Set_Gain(PDAB_ADC_CHANNEL_1, calculate_digipot_setting(Scan_Idx_To_Gain(gain_counter)));
                        zero_state = ZERO_STATE_ZERO_OFFSET;
                        break;
                    }
                    case ZERO_STATE_ZERO_OFFSET:
                    {
                        if(!drv_dpot_idling())
                        {
                            break;
                        }

                        drv_ext_adc_zero();
                        zero_state = ZERO_STATE_SAVE_OFFSET;
                        break;
                    }
                    case ZERO_STATE_SAVE_OFFSET:
                    {
                        if(drv_ext_adc_zero_busy())
                        {
                            break;
                        }
                        Scan_Set_Dac_Zero_For_Gain(drv_dac_get_value(DRV_DAC_1), gain_counter);
                        if(++gain_counter == AUTO_GAIN_STEPS)
                        {
                            gain_counter = 0;
                            pdabData.status->DAB.Flags.Zero = true;
                            //drv_laser_off();
                        }
                        zero_state = ZERO_STATE_SET_GAIN;
                        break;
                    }
                    default:
                        dputs_colour("[RED]ERROR: unknown state in PDAB_Check_Zero_State[WHITE]\r\n");
                        PDAB_Error_Status(1,11);
                        pdabData.state = PDAB_STATE_ERROR;
                        break;
                }
            }
        }
    }
    else
        pdabData.status->DAB.Flags.Zero = true;
}
/*******************************************************************************
 * Function:        bool PDAB_Zero_Busy( void )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         No zero if an error occurred
 *
 * Side Effects:    None
 *
 * Overview:        This function checks if the zero offset is set
 *
 * Notes:           None
 ******************************************************************************/
bool PDAB_Zero_Busy( void )
{
    return !pdabData.status->DAB.Flags.Zero;
}

/****** *************************************************************************
 * Function:        PDAB_Set_Gain( uint8_t channel, uint8_t gain )
 *
 * Precondition:    None
 *
 * Input:           uint8_t channel: Channel to indicate analogue 1 or analogue 2
 *                  uint8_t gain: Input resistance for amplifier 1
 *
 * Output:          None
 *
 * Returns:         No zero if an error occurred
 *
 * Side Effects:    None
 *
 * Overview:        This function configures the gains for respective input
 *                  channel
 *
 * Notes:           None
 ******************************************************************************/
uint16_t PDAB_Set_Gain( uint8_t channel, uint8_t gain )                         // Needs to be state machine with error checking
{
    dprintf_colour("[CYAN]Gain: %d[WHITE]\r\n", gain);
    uint16_t success = NO_ERRORS;

    if( channel < PDAB_ADC_CHANNELS )
    {
        if( pdabData.status->LDA.DPOT[DRV_DPOT_1].Resistance[channel] != gain )          // Need implement read back to check if it needs to be set
        {
            pdabData.status->LDA.DPOT[DRV_DPOT_1].Resistance[channel] = gain;
            drv_dpot_set_resistance(DRV_DPOT_1, gain );                             // Need implement read back to ensure it was set
#ifndef DISABLE_AUTO_ZERO
            pdabData.status->DAB.Flags.Zero = false;
#endif
        }
    }
    else
    {
        success = SET_GAIN_INVALID_CHANNEL;
    }

    return success;
}

/*******************************************************************************
 * Function:        PDAB_Set_Power( uint8_t power )
 *
 * Precondition:    None
 *
 * Input:           uint8_t power: Laser power
 *
 * Output:          None
 *
 * Returns:         No zero if an error occurred
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the laser output power
 *
 * Notes:           None
 ******************************************************************************/
uint16_t PDAB_Set_Power( uint8_t channel, uint8_t power )                       // Needs to be state machine with error checking
{
    uint16_t success = NO_ERRORS;
#ifndef DISABLE_LASER_POWER
    if( channel < PDAB_LASER_CHANNELS )
    {
        if( pdabData.status->LDA.DPOT[DRV_DPOT_2].Resistance[channel] != power )          // Need implement read back to check if it needs to be set
        {
            drv_dpot_set_resistance(DRV_DPOT_2, power);
            pdabData.status->LDA.DPOT[DRV_DPOT_2].Resistance[channel] = power;   // Need implement read back to ensure it was set and then check LPON to make sure laser is active
#ifndef DISABLE_AUTO_ZERO
            pdabData.status->DAB.Flags.Zero = false;
#endif
        }
    }
    else
    {
        success = SET_POWER_INVALID_CHANNEL;
    }
#endif
    return success;
}

/*******************************************************************************
 * Function:        Update_Status
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/
uint16_t PDAB_Update_Status( void )
{
    pdabData.status->DAB.Flags.USB = USB_is_device_attached();

    pdabData.status->DAB.Flags.LBAT = false;
//    pdabData.status->DAB.Flags.LED1 = SYS_PORT_PinLatchRead(LED1_PIN);
//    pdabData.status->DAB.Flags.LED2 = SYS_PORT_PinLatchRead(LED2_PIN);
    pdabData.status->DAB.Flags.LON = SYS_PORT_PinLatchRead(LON1_PIN);
    pdabData.status->DAB.Flags.LPON = SYS_PORT_PinRead(LPON1_PIN);

    pdabData.status->DAB.Flags.Saturated = false;
    pdabData.status->DAB.Flags.Scanning = false;

    pdabData.status->DAB.Version = (uint16_t)( VERSION * 100L );
    pdabData.status->DAB.Device = device_id;
    pdabData.status->DAB.Error =  pdabData.error;

    pdabData.status->LDA.ADC[0].Offset = drv_ext_adc_get_offset( DRV_EXT_ADC_1 );
    drv_ext_adc_get_value( &pdabData.status->LDA.ADC[0].Voltage );

    pdabData.status->LDA.DAC[DRV_EXT_ADC_1].Voltage[DRV_DAC_1] = drv_dac_get_value(DRV_DAC_1);
    pdabData.status->LDA.DAC[DRV_EXT_ADC_1].Voltage[DRV_DAC_2] = drv_dac_get_value(DRV_DAC_2);
    pdabData.status->LDA.DPOT[DRV_EXT_ADC_1].Resistance[DRV_DPOT_1] = drv_dpot_get_resistance(DRV_DPOT_1);
    pdabData.status->LDA.DPOT[DRV_EXT_ADC_1].Resistance[DRV_DPOT_2] = drv_dpot_get_resistance(DRV_DPOT_2);



    //****************************************************************************//
#ifndef DISABLE_LSC
    if( false == drv_lsc_is_busy() )
    {
        drv_lsc_call_get_status();
        drv_lsc_get_last_status( &pdabData.status->LSC );
        PDAB_Transmit_Status();

    }
    else
    {
        drv_lsc_get_last_status( &pdabData.status->LSC );
        PDAB_Transmit_Status();
    }
#endif
    //****************************************************************************/

    return pdabData.status->DAB.Error;
}
void PDAB_Error_Status(uint16_t id, uint16_t subid)
{
    pdabData.status->status_id = id;
    pdabData.status->status_sub_id = subid;
    PDAB_Send_UART_Status();
}
/*******************************************************************************
 * Function:        Update_Status
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/
void PDAB_Command_Received( PDAB_COMMANDS cmd, uint8_t len, const uint8_t* data, COMM_STATES interface )
{
    if(interface == COMM_USB && cmd == 'A' && len == 'C'&& data[0] == 'K')
    {
        dprintf_colour("[PURPLE]USB ping received.[WHITE]\r\n");
        return;
    }

    if(interface == COMM_USB && cmd == 'O' && len == 'C'&& data[0] == 'C'&& data[1] == 'U'&& data[2] == 'I'&& data[3] == 'T'&& data[4] == 'Y'
            && data[5] == '_'&& data[6] == 'P'&& data[7] == 'M'&& data[8] == '1'&& data[9] == '_'&& data[10] == 'E'&& data[11] == 'T'&& data[12] == 'S')
    {
        dprintf_colour("[GREEN]USB - UNLOCKED - EEPROM TOOL SOFTWARE[WHITE]\r\n");
        pdabData.usb_software = USB_SOFTWARE_ETS;
        return;
    }

    if(interface == COMM_USB && cmd == 'O' && len == 'C'&& data[0] == 'C'&& data[1] == 'U'&& data[2] == 'I'&& data[3] == 'T'&& data[4] == 'Y'
            && data[5] == '_'&& data[6] == 'P'&& data[7] == 'M'&& data[8] == '1'&& data[9] == '_'&& data[10] == 'D'&& data[11] == 'C'&& data[12] == 'S')
    {
        dprintf_colour("[GREEN]USB - UNLOCKED - DATA COLLECTION SOFTWARE[WHITE]\r\n");
        pdabData.usb_software = USB_SOFTWARE_DCS;
    }

    if(interface == COMM_USB && cmd == 'O' && len == 'C'&& data[0] == 'C'&& data[1] == 'U'&& data[2] == 'I'&& data[3] == 'T'&& data[4] == 'Y'
            && data[5] == '_'&& data[6] == 'P'&& data[7] == 'M'&& data[8] == '1'&& data[9] == '_'&& data[10] == 'V'&& data[11] == 'C'&& data[12] == 'T')
    {
        dprintf_colour("[GREEN]USB - UNLOCKED - VCT SOFTWARE[WHITE]\r\n");
        pdabData.usb_software = USB_SOFTWARE_VCT;
        pdabData.scan_from_usb = false;
        return;
    }
    

    if((interface == COMM_USB) && (pdabData.usb_software == USB_SOFTWARE_ETS))
    {
        if(cmd == 'R')//read
        {
            dprintf_colour("[RED]READ EEPROM !!![WHITE]\r\n");
            EEPROM_read_to_USB(data);
        }
        else
        if (cmd == 'W')//write
        {
            dprintf_colour("[RED]WRITE EEPROM !!![WHITE]\r\n");
            EEPROM_save_from_USB(data);
        }
        return;
    }
    if((interface == COMM_USB) && (pdabData.usb_software == USB_SOFTWARE_DCS))
    {
        return;
    }
    if((interface == COMM_USB) && (pdabData.usb_software == USB_SOFTWARE_VCT))
    {
        dprintf_colour("[GREEN]USB - VCT cmd: %d[WHITE]\r\n", cmd);
        static char buffer[16+3];
        buffer[0] = 0x41;
        buffer[1] = 0x42;
        if(cmd == (uint16_t)GET_NAME)
        {
            buffer[2] = cmd;
            memcpy(&buffer[3],pdabData.device_name,16);
            send_USB_counted(buffer, 19);
        }
        if(cmd == (uint16_t)GET_ID)
        {
            //dprintf_colour("[GREEN]USB - VCT: SOFT-RESET[WHITE]\r\n");
            Software_Reset();
        }
        
        if(cmd == (uint16_t)GET_COUNTER)
        {
            itoa(&buffer[3],device_statistics.scans_counter,10);
            send_USB(buffer);
        }
        
        if(cmd == (uint16_t)SCAN_START)
        {
            if(pdabData.scan_from_usb == true)return;
            pdabData.scan_from_usb = true;
            //dprintf_colour("[GREEN]USB - VCT: START SCAN[WHITE]\r\n");
            pdabData.status->Command = PDAB_CMD_START_SCANNING;
        }
        if(cmd == (uint16_t)SCAN_STOP)
        {
            //dprintf_colour("[GREEN]USB - VCT: STOP SCAN[WHITE]\r\n");
            pdabData.status->Command = PDAB_CMD_STOP_SCANNING;
            pdabData.scan_from_usb = false;
        }
        return;
    }

    pdabData.comm_interface = interface;
    pdabData.status->Command = cmd;
    pdabData.status->Length = len;

    if( ( data != NULL ) && ( len > 0 ) )
    {
        memcpy( pdabData.status->Data, (uint8_t*)data, ( len ) );
    }
}

/*******************************************************************************
 * Function:        Update_Status
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/
void PDAB_Command_Complete( void )
{
    pdabData.status->Command = PDAB_CMD_NONE;
    pdabData.status->Length = 0U;

    pdabData.previous_state = pdabData.state;
    pdabData.state = PDAB_STATE_IDLE;
}

/* send status message to the PIB via the UART link */
static void PDAB_Send_UART_Status(void)
{
    uint32_t command_length = 0;
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];

    command_buffer[0] = (uint8_t)RESPONSE_PDAB_STATUS;
    command_length++;
    command_buffer[command_length] = ':';
    command_length++;

    memcpy(&command_buffer[command_length], pdabData.status, sizeof(_STATUS_BUFFER));
    command_length += sizeof(_STATUS_BUFFER);
    pic_communications_send_message((uint8_t *) command_buffer, command_length, false);  // requires ACK

    send_USB_DCS_ping();
}

/*******************************************************************************
 * Function:        PDAB_Zero_Offset
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        This function performs zero offset on demand
 *
 * Notes:           None
 ******************************************************************************/
void PDAB_Zero_Offset(void)
{
    pdabData.status->DAB.Flags.Zero=false;
}
/*******************************************************************************
 End of File
 */
