/* ************************************************************************** */
/** @file main.c
 *
 *  @brief main 
 *
 *  @copyright Occuity Limited (c) 2020
*/
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include <p33CK128MP203.h>

#include "main.h"
#include "debug.h"
#include "motor_drv.h"
#include "encoder_drv.h"
#include "LRS_tuning.h"
#include "message_exchange.h"
//************************************************************************//  
// Global Variables
//************************************************************************//
/** @brief wake up flag */
bool wake_up = false;

/** @brief scanning flag */
bool scanning = false;
/** @brief power supply voltage to motor table consisting dac samples  */
uint16_t VM[DAC_SAMPLES];
/** @brief LSC data object defining set LSC parameters and firmware */
volatile _LSC_DATA lscData;
/** @brief lsc tuning object consisitng data reqiired for tuning process */

volatile _LSC_TUNING_OBJ lsc_tuning;



/**************************************************************************** */
/* Function Name: crc32                                                       */
/*                CRC32 (Ethernet, ZIP, etc) polynomial in reversed bit order */
/* @param[in] uint32_t crc : crc value so far (start from 0)                  */
/* @param[in] const uint8_t *data : data to calculate CRC for                 */
/* @param[in] uint32_t length : length of data                                */
/* @retval CRC                                                                */
/* ************************************************************************** */
uint32_t crc32_nvm(uint32_t crc, const uint8_t *data, uint32_t length)
{
    uint8_t i;
    const uint32_t POLY = 0xedb88320;

    crc = ~crc;
    while (length > 0)
    {
        crc ^= *data;
        data++;

        for (i = 0; i < 8; i++)
        {
            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        }

        length--;
    }

    return (~crc);
}
/* End of function crc32                                                      */

//************************************************************************//  
// Interrupt Service Routines
//************************************************************************//
void EX_INT1_CallBack(void)
{
    if (lscData.StatusFlags.DIR)
    {
        if (!lscData.StatusFlags.REF)
        {
            lscData.RefPosition = GetPosition();
            lscData.StatusFlags.REF = true;
        }
        else if (!lscData.StatusFlags.LS)
        {
            lscData.LsPosition = GetPosition();
            lscData.StatusFlags.LS = true;
        }
    }
}

/* ************************************************************************** */
/** 
 * @brief            Wake up call function
 *
 * @note             Called by ....... WHAT? Set wake up flag
 *
 * @return           None.
 */
/* ************************************************************************** */
void wake_up_call(void)
{
    wake_up = true;
}
/////////* ************************************************************************** */
/////////** 
//////// * @brief            Check for pic32 efh commend
//////// *
//////// * @note             Called by static bool processing_task(void). Identify and
//////// *                   execute the command received from pic32 efh (PDAB)
//////// *
//////// * @return           Returns true if a command was received
//////// */
/////////* ************************************************************************** */
////////static bool check_for_efh_command(void)
////////{
////////    uint8_t command;
////////
/////////** @brief see if we've received a command from the EFH, return if not */
////////    if (UART2_ReceiveBufferIsEmpty())
////////    {
/////////** @brief return false if comment is not received */
////////        return (false);
////////    }
////////
/////////** @brief see what command is received from the EFH*/
////////    UART2_ReadBuffer(&command, 1);
////////
/////////** @brief identify and execute the command */    
////////    switch (command)                                                               
////////    {
////////        case LSC_GET_VERSION:                                                       // re-initialise motion controller
////////            dputs_colour("[PINK]Received command: LSC_GET_VERSION[WHITE]\r\n");
////////            uint32_t version = VERSION;
////////            UART2_WriteBuffer((uint8_t *) &version, 4U);
////////            break; 
////////            
////////        case LSC_DEFINE_LIMITS:                                                     // re-initialise motion controller
////////            dputs_colour("[PINK]Received command: LSC_DEFINE_LIMITS[WHITE]\r\n");
////////            lscData.StatusFlags.DLIM = true;
////////            break;            
////////
/////////** @brief status flag start scanning */
////////        case LSC_START_SCANNING:                                                    
////////            dputs_colour("[PINK]Received command: LSC_START_SCANNING[WHITE]\r\n");
////////            lscData.StatusFlags.START = true;
////////            break;
////////
/////////** @brief status flag stop scanning */            
////////        case LSC_STOP_SCANNING:                                                     
////////            dputs_colour("[PINK]Received command: LSC_STOP_SCANNING[WHITE]\r\n");
////////            lscData.StatusFlags.STOP = true;
////////            break;        	
////////
/////////** @brief send device status to pic32 efh */
////////        case LSC_GET_STATUS:                                                        
////////            dputs_colour("[PINK]Received command: LSC_GET_STATUS[WHITE]\r\n");
////////            send_status();
////////            break;
////////
/////////** @brief soft MCU reset */     
////////        case LSC_RESET:                                                             
////////            dputs_colour("[PINK]Received command: LSC_RESET[WHITE]\r\n");
////////            asm("RESET");
////////            break;
////////
////////        default:                                                                    // Default
////////            dprintf_colour("[PINK]Received unrecognised command: %d[WHITE]\r\n", command);                                                      
////////            break;
////////    }
////////
////////    return (true);
////////}

/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */

#define ENC_MOVE_TIMEOUT_MS     5u


static volatile uint16_t  stop_timeout = 0; 
uint16_t stop_TO_cnt = 0; 

static volatile bool millisecond_tick = false; 


/* ************************************************************************** */
/** 
 * @brief            Hardware initialisation routine 
 *
 * @note             Called by static bool processing_task(void).
 *                   Initialises all PIC hardware peripherals
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Initialisation(void) 		
{	    
    uint32_t crc;
    /** @brief  Configure Peripheral Pin Select - Note most peripherals are configured by MCC */   
    __builtin_write_RPCON(0x0000); // unlock PPS    
    /** @brief define macro setting  RP49/RC1 (DSP_BUSY) tied to QEI1 Comparator Output */
    RPOR8bits.RP49R = 38;       
    /** @brief define macro setting RP49/RC1 (DSP_BUSY) as output */
    TRISCbits.TRISC1 = 0;       
    /** @brief define macro setting Encoder Channel A to RB13 */
    RPINR14bits.QEIA1R = 45;	
    /** @brief define macro setting RP45/RB13 (Encoder Channel A) as input */
    TRISBbits.TRISB13 = 1;		
    /** @brief  define macro setting Encoder Channel B to RB10   */
    RPINR14bits.QEIB1R = 42;    
    /** @brief define macro setting RP42/RB10 (Encoder Channel B) as input */
    TRISBbits.TRISB10 = 1;		
    /** @brief define macro assign QEI Index 1 Input (Encoder Channel Z) to RB5 */
    RPINR15bits.QEINDX1R = 37;	
    /** @brief define macro setting RP37/RB5 (Encoder Channel Z) as input */
    TRISBbits.TRISB5 = 1;		 

    __builtin_write_RPCON(0x0800); // lock PPS    
    
    /** @brief Configure Quadrature Encoder Interface */
    QEI1CON = 0;                // Clear QEICON register
	QEI1CONbits.QEIEN = 0;      // QEI Module Enables
    QEI1CONbits.CCM = 0;        // Interface mode: x4 position counter reset with match
    QEI1CONbits.PIMOD = 0;		// Position counter reset: Disabled
    QEI1CONbits.GATEN  = 0;     // External gate signals disabled 
    QEI1CONbits.INTDIV = 0;     // Velocity counter divider set to 1:1
    
    QEI1IOCbits.SWPAB = 1;
    QEI1IOCbits.QCAPEN = 0;     // Disable index match trigger event
    QEI1IOCbits.OUTFNC = 0b00;  // Disable QEI position match output  
    QEI1IOCbits.FLTREN = 0;     // Digital filtering enabled 
    QEI1IOCbits.QFDIV = 0b001;  // 1:8 Clock
    QEI1STAT = 0;
	
    POS1HLD = 0;                // Position counter high word
	POS1CNTL = 0;               // Position counter low word
	POS1CNTH = 0;               // Position counter low word
    /** @brief  Quadrature encoder interrupt priority */
	IPC12bits.QEI1IP = 5;   
    /** @brief Interrupt flag for QEI Position Counter Compare: cleaned */  
    IFS3bits.QEI1IF = false;    
    /** @brief Interrupt QEI Position Counter Compare: enabled  */  
    IEC3bits.QEI1IE = true;      
    /** @brief Quadrature Encoder Interface Module Enable bit: Module counters are enabled */
    QEI1CONbits.QEIEN = true;   

    /** @brief status flag union cleaned after initialisation */
    lscData.StatusFlags.Short = 0U;
    
    /** @brief set tuning phase to beginning tuning process*/
    lsc_tuning.tuning_phase = TUNING_PHASE_IDLE;
    lsc_tuning.tuning_process_flag = TUNING_NOT_DONE;    
    
    dprintf("\033\143");                                                // Clear terminal
    dprintf("\033[3JResetting terminal and clearing scroll-back\r\n");  // Clear scroll back
    dprintf("LSC Start");
    dprintf_colour("[YELLOW]LSC firmware v%d.%02d Build %03d[WHITE]\r\n", VERSION_MAJOR, VERSION_MINOR, BUILD);
    
#ifdef NVM     
    if (!nvmCtl(NVM_INITIALISE, NULL, NULL))
    {
        if (nvmCtl(NVM_READ, NULL, (uint16_t *) lscData.Buffer))
        {
            // failed to read NVM data
            lscData.StatusFlags.FLASH = false;         
            lscData.StatusFlags.ERR = true;
        }
        else
        {
            // successful read of NVM data, now check the CRC
            crc = crc32_nvm(0, (const uint8_t *) lscData.Buffer, sizeof(_LSC_DATA) - sizeof(uint32_t));
            dprintf_colour("[BROWN]Calculated CRC value is 0x%lx[WHITE]\r\n", crc);
            dprintf_colour("[BROWN]lscData CRC value is 0x%lx[WHITE]\r\n", lscData.crc32);

            if (crc == lscData.crc32 && lscData.StatusFlags.ROFF != true)
            {
                dputs_colour("[BROWN]NVM data CRC passed[WHITE]\r\n");
            }
            else
            {
                dputs_colour("[PINK]NVM data CRC failed or ROFF wrong[WHITE]\r\n");
                // set flag to start tuning process
                lscData.StatusFlags.FLASH = false;
            }
        }
    }
    else
    {
        lscData.StatusFlags.ERR = true;
    }

    if (!lscData.StatusFlags.FLASH)
    {   
#endif        
        lscData.LRADriveFreq = FREQ_START; 
        lscData.LRAResonantFreq = FREQ_START;
        lscData.ScanOffset = 0L;
        lscData.ScanMin = 0L;
        lscData.ScanMax = 0L;
        lscData.ScanRange = SCAN_RANGE;
        lscData.ScanStart = POSITION_OFFSET - (SCAN_RANGE / 2L);
        lscData.ScanStop = POSITION_OFFSET + (SCAN_RANGE / 2L); 
        lscData.LRAWaveForm = DAC_WAVEFORM;
        /** @brief set status flag start tuning process */          
        lscData.StatusFlags.DLIM = true;     
        lscData.LRADriveAMP = DAC_VOLTAGE_START;
        lscData.LRAResonantAMP = DAC_VOLTAGE_START; 
        lscData.FreqStart = FREQ_START;
        lscData.FreqLimit = FREQ_LIMIT;
        
        lscData.OriginalZOff = INT32_MAX; 
        lscData.ZOff_diff_dir = 0xFF00; 
        dputs_colour("[PINK]Flash initialised[WHITE]\r\n");
#ifdef NVM           
    }
    else
    {
        /** @brief if not def macro always retune start from memorised resonance frequency decreased by FREQ_START_OFFSET */        
#ifndef  ALWAYS_RETUNE        
        lscData.LRADriveFreq = lscData.LRAResonantFreq;
        lscData.LRADriveAMP = lscData.LRAResonantAMP;
        /** @brief if def macro always retune look for resonance frequency starting from FREQ_START */     
#else
        lscData.LRADriveFreq = FREQ_START; 
        lscData.LRAResonantFreq = FREQ_START;
        lscData.FreqStart = FREQ_START;
        lscData.FreqLimit = FREQ_LIMIT;
        lscData.StatusFlags.QTUN = false;
            #ifdef FINDMAX
            lscData.LRADriveAMP = DAC_VOLTAGE_START;
            lscData.LRAResonantAMP = DAC_VOLTAGE_START;
            #else
            lscData.LRADriveAMP = DAC_VOLTAGE_START;
            lscData.LRAResonantAMP = DAC_VOLTAGE_START;
#endif
        #endif
        lscData.ScanOffset = 0L;
        lscData.ScanMin = 0L;
        lscData.ScanMax = 0L; 
        lscData.MeanScanOffset = 0L;
        lscData.MeanScanMin = 0L;
        lscData.MeanScanMax = 0L;
        
        dputs_colour("[PINK]Flash read complete[WHITE]\r\n");
    }
#endif
    
	lscData.ScanCount = 0L;            // Set no. of scans to zero
    lscData.StatusFlags.LS = false;
    scanning = false;
    // pdab / lsc com
    pic_communications_init();
}

/* ************************************************************************** */
/* Section: Main Application                                                  */
/* ************************************************************************** */

/* ************************************************************************** */
/** 
 * @brief            SCCP7 Primary Timer Callback function 
 *
 * @note             Called by void SCCP7_TMR_PrimaryTimerTasks( void )
 *                   if the Timer Interrupt/Status flag is set.
 *                   If Direct Memory Access is not set, it set the motor power output
 *                   from DAC to the motor controller.              
 * 
 * @return           None.
 */
/* ************************************************************************** */
void SCCP7_TMR_PrimaryTimerCallBack(void)
{
#ifndef DMA
    CMP1_SetDACDataHighValue( VM[VM_INDEX] );
    if( ++VM_INDEX >= DAC_SAMPLES )
    {
       VM_INDEX = 0U; 

#ifdef DAC_DIFFERENTIAL        
       LATDbits.LATD4 = !LATDbits.LATD4;
#endif
    }
#endif
}

/* ************************************************************************** */
/** 
 * @brief            Timer 1 Callback 
 *
 * @note             Called by timer 1 interrupt. Called with 1/50 ms frequency
 *                   It calls void debug_millisecond_timer_interrupt(void)           
 * 
 * @return           None.
 */
/* ************************************************************************** */
void TMR1_CallBack(void)
{
    static uint16_t one_fifthy_of_milisecond = 0;
    one_fifthy_of_milisecond ++;
    encoder_interrupt();
    
    if(one_fifthy_of_milisecond == 49U)
    {   
        one_fifthy_of_milisecond = 0;
        debug_millisecond_timer_interrupt();
        transmit_timer();
        message_exchange_millisecond_timer_interrupt();
        
        Tuning_tick(); 
        
        //timeouts_update_tick(); 
        
        //timeouts_test_tick();
        
        if(stop_timeout > 0){
            
            stop_timeout --; 
        }
        
        millisecond_tick =true; 
    }
}
/* ************************************************************************** */
/** 
 * @brief            Get Position. Returns the position of the RM stage 
 *
 * @note             Called by void EX_INT1_CallBack(void), static bool check_for_efh_command(void)
 *                   and void DefineLimits(void)   
 *
 * @return           Position
 */
/* ************************************************************************** */
int32_t GetPosition(void)
{
    _TYPE_BUFFER position;    
    
    /* @brief Read current position from encoder position counter register */
    position.Short[0] = POS1CNTL;                         
    position.Short[1] = POS1HLD;
    
    return (position.Long[0]);
}  

/* ************************************************************************** */
/** 
 * @brief            Count Scans. Keeps track of scan count and stops scanning if SCAN_LIMIT 
 *                   is reached. 
 *
 * @note             The use of WAIT will not start data acquisition until the 
 *                   desired number of full scans has been reached. 
 *
 * @param[in/out]    bool dir: direction of current scan
 *
 * @return           True if scan count is zero
 */
/* ************************************************************************** */
bool ScnCount(bool dir)
{  
    bool acqData = false;
    
#ifdef WAIT
    static uint16_t fwdCount = 0;
    static uint16_t bckCount = 0;   
    
    if (lscData.StatusFlags.QOE)
    {
        if (dir)
        {
            bckCount++;               
        }
        else
        {       
            fwdCount++;
        }
        
        if (bckCount > WAIT_LIMIT)
        {
            if (fwdCount > WAIT_LIMIT)
            {  
                fwdCount = 0U;
                bckCount = 0U;
                lscData.StatusFlags.QOE = false; 
                acqData = true;
            }
            else
            {
                acqData = false;
            }
        }
        else
        {
            acqData = false;
        }
    }
    else
    {
        lscData.ScanCount = lscData.ScanCount - 1L;

        if (lscData.ScanCount <= 0L)
        {                          // Basic scan count
            lscData.StatusFlags.STOP = true;         
            acqData = false;
        }
        else
        {
            acqData = true;
        }
    }
 /** @brief if not def wait until the desired number of full scans has been reached before starting data acquisition */   
#else
    lscData.ScanCount = lscData.ScanCount - 1L;
    
    // WHAT DOES IT MEAN? IT RETURNS acqDATA AS FALSE WHEN SCAN COUNT REACHS ZERO ................????
    /** @brief basic scan count. If meets the scan count requirement sets stop scanning flag */    
    if (lscData.ScanCount <= 0L)                           
    {
        lscData.StatusFlags.STOP = true;       
        acqData = false;
    }
    else
    {
        acqData = true;
    }    
#endif    
    
    return (acqData);
}

/* ************************************************************************** */
/** 
 * @brief            Find true amplitude and frequency.Defines the limits of 
 *                   the linear motion based on the min/max positions from a number
 *                   of open loop revolutions
 *
 * @note             Called by static bool processing_task(void) if define limit flag set
 * 
 * @return           None.
 */
/* ************************************************************************** */
//void send_status( void )
//{
//    static LSC_STATUS_t status;
//        
//    status.Position = GetPosition();
//    status.Scan.Frequency = lscData.LRAResonantFreq;
//    status.Scan.Length = lscData.ScanStop - lscData.ScanStart;
//    status.Scan.Range = lscData.ScanRange;
//    status.RefPositions[0] = lscData.LsPosition;
//    status.RefPositions[1] = lscData.RefPosition;
//    status.Version = VERSION;
//    UART2_WriteBuffer((uint8_t *) &status, sizeof(_LSC_STATUS));
//}
///** @brief LSC enum defining states of LSC task  */
//typedef enum
//{
//    /** @brief LSC idle state */
//    LSC_TASK_IDLE, 
//    /** @brief LSC initialisation state */        
//    LSC_TASK_INIT,
//    /** @brief LSC define limits state */        
//    LSC_TASK_DEFINE_LIMITS,
//    /** @brief LSC perform scan state */
//    LSC_TASK_SCAN,
//    /** @brief LSC message exchange state */
//    LSC_TASK_MESSAGE_EXCHANGE,
//    /** @brief LSC error state */
//    LSC_TASK_ERROR,        
//} _LSC_TASK_STATE;
//
//static bool task(void)
//{
//    
//}
/* perform any processing */
/* returns true if processing was performed, false if not */
static bool processing_task(void)
{
//    DBG_LEDG_Toggle();
    static uint32_t sleep_countdown = 500000;
    
    static uint16_t test_timer = 0; 
    
    static bool error_state = 1;
    
    if (millisecond_tick){
        test_timer++; 
        if(test_timer  == 10){
            //timeouts_test(); 
            test_timer = 0; 
        }
        
    }
   
    uint32_t crc;
    bool result = false; 
    if(lscData.StatusFlags.INIT == true && lsc_tuning.tuning_process_flag == TUNING_IN_PROG)
    {    
        DefineLimits_task();
        result = true; 
    }
    if (pic_comms_task())
    {
        sleep_countdown = 500000;
        result = true;
    }
    // remember to delate it is for test -> check uart speed on lsc side

    /** @brief check UART 2 for command received from the PIC EFH (PDAB) */
//////    if (check_for_efh_command())
//////    {
//////        /** @brief make sure that we stay awake for a bit. Set countdown to sleep counter to 10000 */
//////        sleep_countdown = 10000;
//////        return (true);
//////    }

    /** @brief process task accordingly to set status flags by pic32 EFH or previously by the software */
   
    if (!lscData.StatusFlags.INIT)
    {
        /** @brief hardware initialization routine */
        Initialisation();
        /** @brief signal that initialization is done */
        lscData.StatusFlags.INIT = true;   
        DSP_BUSY_SetHigh(); 
#ifdef  ALWAYS_RETUNE
        /** @brief go through tuning regardless of commends from other software */
        lscData.StatusFlags.DLIM = true;    
#endif
        
        
        return (true);
    }

    /** @brief if define limits flag set */
    if (lscData.StatusFlags.DLIM)
    {
        lscData.StatusFlags.DLIM = false;
//        DSP_BUSY_SetLow(); 
        if (lsc_tuning.tuning_process_flag != TUNING_IN_PROG)
        {
            dputs_colour("[PINK]Define limits initiated.[WHITE]\r\n");
            /** @brief clean re-tune flag */
            lscData.StatusFlags.CFG = false;
            lsc_tuning.tuning_process_flag = TUNING_IN_PROG;
            lsc_tuning.tuning_phase = TUNING_PHASE_INIT;
            lsc_tuning.prev_tuning_phase = TUNING_PHASE_IDLE;      
            //dputs_colour("[GREEN]Limits defined.[WHITE]\r\n"); 
        }    
        return (true);
    }

    if (lscData.StatusFlags.START)
    {
        StartMotion(SCAN_LIMIT, true);
        lscData.StatusFlags.START = false;
        stop_TO_cnt = 0; 
        stop_timeout = 0; 
        dputs_colour("[GREEN]Scanning started.[WHITE]\r\n");
        return (true);
    }

    if (lscData.StatusFlags.STOP)
    {
        //StopMotion();
        //lscData.StatusFlags.STOP = false;
        
        if (stop_timeout == 0){
            
            dputs_colour("[GREEN]Scanning stopping...[WHITE]\r\n");
            stop_timeout = 10; 
            stop_TO_cnt++; 
            
            if(stop_TO_cnt == 2){
                StopMotion();
                lscData.StatusFlags.STOP = false;
                stop_TO_cnt = 0; 
                dputs_colour("[YELLOW]Forced scan stop.[WHITE]\r\n");
            }
        }
        
        return (true);
    }

    if (lscData.StatusFlags.SAVE)
    {
        if(lscData.StatusFlags.ROFF == false)
        {    
            dputs_colour("[CYAN]Save settings ...[WHITE]\r\n");

            /* save the settings */
            #ifdef NVM    
            /* clear save flag so it was not memorised as set by NVM */
            lscData.StatusFlags.SAVE = false;
            if (!nvmCtl(NVM_ERASE_PAGE, NULL, NULL))
            {
                lscData.StatusFlags.FLASH = true;
                dputs_colour("[GREEN]Flash erase successful.[WHITE]\r\n");    

                /* calculate and set the CRC on the settings */
                crc = crc32_nvm(0, (const uint8_t *) lscData.Buffer, sizeof(_LSC_DATA) - sizeof(uint32_t));
                dprintf_colour("[GREEN]Calculated CRC value is 0x%lx[WHITE]\r\n", crc);

                /* set the CRC on the settings */
                lscData.crc32 = crc;

                if (nvmCtl(NVM_WRITE, (uint16_t *) &lscData.Buffer[0], NULL))
                {
                    lscData.StatusFlags.ERR = true;
                    lscData.StatusFlags.FLASH = false;
                    dputs_colour("[RED]Flash write error.[WHITE]\r\n");
                }
                else
                {   
                    dputs_colour("[GREEN]Flash write successful.[WHITE]\r\n");          
                }
            }
            else
            {
                dputs_colour("[RED]Flash erase error.[WHITE]\r\n");
                lscData.StatusFlags.ERR = true;
            }         
            #endif

        }
        
        lscData.StatusFlags.SAVE = false;
        return (true);
    }

    /* return true if we're scanning */
    if (scanning)
    {
        
                
        if(enc_move_wdt_check_clear()){ //TODO:fix enc move wdt check
            
            //dputs_colour("[RED]Error:Scans have not exceeded QEI thresholds\r\n");
            
            
        }
        
        return (true);
    }else{
       
        if((stop_TO_cnt > 0)&&(lscData.StatusFlags.STOP==false)){
            
            dputs_colour("[GREEN]Normal Scan stop.[WHITE]\r\n");
            
            stop_TO_cnt=0; 
        }
         
    }

//    /* return true if we're busy sending data to the EFH */
//    if ((UART2_TransferStatusGet() & UART2_TRANSFER_STATUS_TX_EMPTY) == 0)
//    {
//        return (true);
//    }

    /* return true if we're busy sending debug logging */
    if ((UART1_TransferStatusGet() & UART1_TRANSFER_STATUS_TX_EMPTY) == 0)
    {
        return (true);
    }

    /* detect a change in the error flag state */
    /* switch timer 1 between timing LED flash and debug timing */
    if (error_state != lscData.StatusFlags.ERR)
    {
        error_state = lscData.StatusFlags.ERR;

        if (error_state)
        {
            TMR1_Period16BitSet(0xFFFF);        /* slowest value for LED flash (167ms) */
            TMR1_Counter16BitSet(0);
        }
        else
        {
            TMR1_Period16BitSet(0x7);         /* 1ms for debug timing */
        }
    }

    /* if there is an error then toggle the LED and then idle to save power */
    /* timer 1 interrupt will wake MPU after 167ms */
    if (lscData.StatusFlags.ERR)
    {
        /* allow UART2 to continue while idle */
        U2MODEbits.USIDL = 0;
        m_LED1_Toggle();
        Idle();
        return (true);
    }

    /* delay before going to sleep after receiving a command */
    if (sleep_countdown > 0)
    {
        sleep_countdown--;
        return (true);
    }
    
    
    
    return (result);
}
/* ************************************************************************** */
/** 
 * @brief            Put device to sleep as long as it is not processing transfer from Debug UART
 *                   and wait for a command from the PDAB on UART2 to wake up the MPU
 *
 * @note             Called by int main(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */

static void sleep(void)
{
    dputs_colour("[BLUE]Going to sleep![WHITE]\r\n");
    /* @brief wait for transfer from Debug UART to end */
    while ((UART1_TransferStatusGet() & UART1_TRANSFER_STATUS_TX_EMPTY) == 0);

    /* @brief allow a command from the PDAB on UART2 to wake up the MPU */
    U2MODEbits.WAKE = 1;
    DELAY_microseconds(10);
    /* @brief turn off the voltage regulator during sleep */
//    RCONbits.VREGS = 0;

    /* @brief leave the voltage regulator on during sleep, otherwise the device does not wake up properly */
//    RCONbits.VREGS = 1;

    /* @brief put CPU to sleep */
//    Sleep();

    /* @brief stop timer 1 */
    TMR1_Stop();
    /* @brief put CPU to idle state */
    Idle();
    TMR1_Start();
    /* potential work around for the sleep with the regulator off - not yet working */
    /* see errata */
    //GoToSleep();

    dprintf_colour("[MAGENTA]Awake!! RCONbits.SLEEP is %d, RCONbits.IDLE is %d[WHITE]\r\n", RCONbits.SLEEP, RCONbits.IDLE);
//    DELAY_milliseconds(100);
}

LSC_STATUS_t update_lsc_status_data( void )
{
    LSC_STATUS_t status;
        
    status.Position = GetPosition();
    status.Frequency = lscData.LRAResonantFreq;
    status.Length = lscData.ScanStop - lscData.ScanStart;
    status.Range = lscData.ScanRange;
    status.RefPositions[0] = lscData.LsPosition;
    status.RefPositions[1] = lscData.RefPosition;
    status.flags.Short = 0;
    
    if(lsc_tuning.tuning_process_flag == TUNING_IN_PROG){
        
        status.flags.TUNE_INPROG = true; 
    }else if(lsc_tuning.tuning_process_flag == TUNING_FINISHED){
        
        status.flags.TUNE_FINISHED = true; 
    }
    
     
    status.flags.TUNE_ERROR = lscData.StatusFlags.ERR;
    
    status.Version = VERSION;
 
    return status;
}

//************************************************************************// 
// Main Application
//************************************************************************// 
int main(void)
{
    /* @brief Initialize the device */
    SYSTEM_Initialize();

    /* @brief Initialise the debug logging module */
    debug_initialise();
    /* @brief timer 1 set to 1KHz and used for debug timing */
    TMR1_Start();                   

    /* @brief display debug actions / logging to be performed during startup */
    initialisation_debug();
    
    /* @brief main program loop */
    while (1)                                               
    {
        //lwd_toglge
        /* @brief perform any processing that is needed */
        if (!processing_task())
        {
            sleep();
        }

        /* @brief perform debug task */
//        debug_task(&wake_up);
        millisecond_tick = false; 
    }

    return (1);
}
/**
 End of File
*/
