/******************************************************************************

Company:   Occuity Limited
Project:   pdab
File Name: pdab_scan_functions.c
Processor: PIC32MZ
Hardware:  pdab Digital Board
Assembler: XC32-gcc
Linker:    XC32-ld
 
Description: 
 
Functions: 
 
 *******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Initial Version
 *******************************************************************************/

/*******************************************************************************
                            Includes Files
 *******************************************************************************/
#include "pdab_scan_functions.h"
#include "npda_tools.h"
#include <stdlib.h>
#include <string.h>

extern PDAB_DATA pdabData;
extern DEVICE_SETTINGS_t device_settings;
extern float cal_data[PDAB_SCAN_LENGTH_16];

/*******************************************************************************
                            Global variables
 *******************************************************************************/
_SCAN_BUFFER MAKE_BUFFER_DMA_READY _scan_buffer[PDAB_TOTAL_SCAN_BUFFERS];

#ifndef DISABLE_NPDA
_NPDA_SCAN_BUFFER MAKE_BUFFER_DMA_READY _npda_scan_buffer;
#endif

_NPDA_SCAN _preselection_scan;
static uint16_t dac_zero_for_gain[AUTO_GAIN_STEPS];

static SCAN_DATA scanData = {
    .state = SCAN_INITIALISE,
    .previous_state = SCAN_IDLE,
    .error = NO_ERRORS,

    .scan_count = 0U,
    .scans_to_collect = 100U,
    #ifndef DISABLE_NPDA    
    .npda_scan_buffer = &_npda_scan_buffer,
    #endif   
    .scan_length = PDAB_SCAN_LENGTH_16,
    .data_length = PDAB_DATA_LENGTH_8,
    .dma_length = PDAB_SCAN_LENGTH_8,

    .scan_settings.refractive_index = SCAN_REFRACTIVE_INDEX,

    .scan_settings.comparator_reference_voltage = SCAN_VOLTAGE_REF,

    .scan_settings.peak_thresholds[0] = SCAN_P1_THRESH,
    .scan_settings.peak_thresholds[1] = SCAN_P2_THRESH,

    .scan_settings.fwhm_limits[0] = SCAN_LOW_FWHM_THRESH,
    .scan_settings.fwhm_limits[1] = SCAN_HIGH_FWHM_THRESH,

    .scan_settings.separation_limits[0] = SCAN_LOW_SEP_THRESH,
    .scan_settings.separation_limits[1] = SCAN_HIGH_SEP_THRESH,

    .scan_settings.amplifier_gain = DRV_DPOT1_DEFAULT,
    .scan_settings.laser_power = DRV_DPOT2_DEFAULT,
    .scan_settings.total_scans = 10U,

    .scanning = false,
    .stop_scanning = false,
    .acquisition_complete = false,

    .cmp_index = 0,
    .auto_gain_scan_count = 0,
    .auto_gain_current_gain = AUTO_GAIN_MAX,
    .skip_scan = false,
    .preselection_scan = &_preselection_scan,
};

static _SCAN_BUFFER MAKE_BUFFER_DMA_READY scan_buffer_for_usb;

void Scan_Set_Dac_Zero_For_Gain(uint16_t dac_setting, uint8_t gain_idx) {
    dac_zero_for_gain[gain_idx] = dac_setting;
}

double Scan_Idx_To_Gain(uint8_t idx) {
    double step = (AUTO_GAIN_MAX - AUTO_GAIN_MIN) / (((double) AUTO_GAIN_STEPS) - 1.0);

    return AUTO_GAIN_MIN + ((double) idx) * step;
}

uint8_t* get_npda_buffer_ptr(void) {
    #ifndef DISABLE_NPDA
    return (uint8_t*)&_npda_scan_buffer.Scans[0].Data[0];
    #endif
}

/*******************************************************************************
 * Function:        void Scan_CN_Interrupt_Handler( void )
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
void Scan_CN_Interrupt_Handler(GPIO_PIN pin, uintptr_t context) {
    SCAN_DATA * tempObj = (SCAN_DATA *) context;


    if (pin != LSC_BUSY_PIN) {
        dputs_colour("[RED]Not LSC Busy Interrupt[WHITE]\r\n");
        return;
    }
    
    if (!SYS_PORT_PinRead(LSC_BUSY)) {
        // Enable DMA transfer
        DCH1CONSET = _DCH1CON_CHEN_MASK;
        //Ablocking_dputc('C');

        // Start the scan timer
        Scan_Timer_Start();

        // Clear interrupt flags and enable the CMP interrupt 
        EVIC_SourceStatusClear(INT_SOURCE_COMPARATOR_1);
        EVIC_SourceEnable(INT_SOURCE_COMPARATOR_1);
        // Update scan status structure
        Scan_Append_Status(&tempObj->scan_buffer->Header.Status);
    } else {
        // Clear interrupt flags and enable the CMP interrupt 
        //Ablocking_dputc('D');
        EVIC_SourceDisable(INT_SOURCE_COMPARATOR_1);
        EVIC_SourceStatusClear(INT_SOURCE_COMPARATOR_1);
        Scan_Timer_Stop();
        scanData.cmp_index = 0U;
    }
}

/*******************************************************************************
 * Function:        void Scan_Interrupt_Handler( void )
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
void Scan_DMA_Interrupt_Handler(SYS_DMA_TRANSFER_EVENT event, uintptr_t context) {
    SCAN_DATA * tempObj = (SCAN_DATA *) context;

    if (SYS_DMA_TRANSFER_COMPLETE == event) {
        if (SCAN_SCANNING == tempObj->state) {
            tempObj->previous_state = tempObj->state;
            tempObj->state = SCAN_SETUP_BUFFER;
            //Ablocking_dputc('A');
        } else if (SCAN_STOP_SCANNING == tempObj->state) {
            tempObj->previous_state = tempObj->state;
            tempObj->state = SCAN_WAIT_FOR_STOP;
            //Ablocking_dputc('E');
        }
    } else {
        //Ablocking_dputc('F');
        tempObj->error = DMA_ERROR;
    }
}

static volatile uint16_t cmp_positions[2];
/*******************************************************************************
 * Function:        void Scan_CMP1_Interrupt_Handler( void )
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
void Scan_CMP1_Interrupt_Handler(uintptr_t context) {
    //static uint16_t cmp_positions[2];

    SCAN_DATA * tempObj = (SCAN_DATA *) context;
    _SCAN_HEADER* header = &tempObj->scan_buffer->Header;

    #ifndef DISABLE_CMP_PEAK_FINDING

    uint16_t position = DRV_EXT_ADC_DMA_CH3_COUNT >> 1U;

    if (position > 0U) {
        
        header->Measurement.Peak[header->Measurement.Count].Minimum[scanData.cmp_index] = position; 
        cmp_positions[scanData.cmp_index++] = position;
        
        if(scanData.cmp_index > 1U) {
            
            if (header->Measurement.Count < PDAB_MAX_PEAKS) {
                header->Measurement.Peak[header->Measurement.Count++].Position = (cmp_positions[0] + cmp_positions[1]) >> 1U;
            }

            scanData.cmp_index = 0U;
        }
    #else
    Scan_Append_Measurement(&header->Measurement);
        #endif  
    }

    #ifdef DEBUG_DAQ
    dprintf_colour("[YELLOW]CMP Triggered: %d[WHITE]\r\n", position);
    #endif  
}

/*******************************************************************************
 * Function:        void Scan_Timer_Initialise( void )
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
void Scan_Timer_Initialise(void) {
    scanData.scan_time = 0U;
    scanData.scan_start_time = 0U;
    scanData.scan_stop_time = 0U;
    scanData.average_scan_time = 0.00F;
    scanData.measurement_time = 0.00F;
    TMR4_PeriodSet(0L);
}

/*******************************************************************************
 * Function:        void Scan_Timer_Start( void )
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
void Scan_Timer_Start(void) {
    TMR4_Start();
    scanData.scan_start_time = TMR4_CounterGet();
}

/*******************************************************************************
 * Function:        void Scan_Timer_Stop( void )
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
void Scan_Timer_Stop(void) {
    scanData.scan_stop_time = TMR4_CounterGet();
    scanData.scan_time = (scanData.scan_stop_time - scanData.scan_start_time);
    scanData.average_scan_time += scanData.scan_time;
}

/*******************************************************************************
 * Function:        void Scan_Timer_Stop( void )
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
void Scan_Timer_Report(void) {
    TMR4_Stop();
    scanData.measurement_time = (double) TMR4_CounterGet() / 390625; // (100.00e6F / 256.00F);
}

/*******************************************************************************
 * Function:        void Scan_Buffer_Setup( bool initialised )
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
void Scan_Buffer_Setup(void) // Service from and interrupt so should be passed a pointer rather than use direct addressing
{
    if (scanData.scan_buffer_initialised) {
        // If buffer index exceeds the total number of buffers, go back to first buffer
        scanData.scan_buffer_index++;

        if (scanData.scan_buffer_index >= PDAB_TOTAL_SCAN_BUFFERS) {
            scanData.scan_buffer_index = 0U;
        }
    } else {
        scanData.scan_buffer_index = 0U;
        scanData.scan_buffer_initialised = true;
    }

    scanData.scan_buffer = &_scan_buffer[scanData.scan_buffer_index];
    scanData.dma_destination = (void *) KVA_TO_PA((void *) scanData.scan_buffer->Data);

    #ifndef DEBUG_SCAN    

    if (!Scan_Check_DMA()) {
        DMAC_SetupChannelTransfer(DRV_EXT_ADC_DMA_CHANNEL_3,
                scanData.dma_source,
                DRV_EXT_ADC_DATA_WIDTH,
                scanData.dma_destination,
                scanData.dma_length,
                DRV_EXT_ADC_DATA_WIDTH);
    };

    #else 
    DMAC_ChannelTransfer(DRV_EXT_ADC_DMA_CHANNEL_2,
            scanData.dma_source,
            DRV_EXT_ADC_DATA_WIDTH,
            scanData.dma_destination,
            scanData.dma_length,
            DRV_EXT_ADC_DATA_WIDTH);
    #endif

    memset(&scanData.scan_buffer->Header, 0U, sizeof (scanData.scan_buffer->Header));
    scanData.scan_count++;
}

/*******************************************************************************
 * Function:        void Scan_Start( void )
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
void Scan_Start(void) {
    #ifndef DISABLE_LASER_SWITCHING
    /* abort if there is a problem with the LASER */

    if (scanData.comm_interface == COMM_USB) {
        if (LASER_ERROR_NONE != drv_laser_on(false)) {
            return;
        }
    } else {
        if (LASER_ERROR_NONE != drv_laser_on(true)) {
            return;
        }
    }
    #endif

    Scan_Buffer_Setup();

    Scan_Timer_Initialise(); // Initialise scan timer     
    scanData.scan_count = 0U;
    scanData.scan_valid_count = 0U;
    scanData.scan_buffer_initialised = false;
    #ifndef DISABLE_NPDA
    scanData.collect_block = false;
    scanData.block_count = 0U;
    scanData.block_scan_count = 0U;
    scanData.npda_scan_count = 0U;
    memset(scanData.npda_scan_buffer, 0U, sizeof (_NPDA_SCAN_BUFFER));
    #endif    

    #ifndef DEBUG_ADC
    // Configure the comparator voltage reference
    CVR_Stop();
    CVR_UpdateValue(scanData.scan_settings.comparator_reference_voltage);
    CVR_Start();
    CMP_1_CompareEnable();

    drv_ext_adc_start();

    // Clear interrupt flags and enable the CN and DMA interrupts 
    EVIC_SourceStatusClear(LSC_BUSY_INTERRUPT);
    EVIC_SourceEnable(LSC_BUSY_INTERRUPT);

    // Start the continuous scanning process
    drv_lsc_start_scanning();
    scanData.scanning = true;
    scanData.stop_scanning = false;
    scanData.acquisition_complete = false;
    #endif  
}

/*******************************************************************************
 * Function:        void Scan_Stop( void )
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
void Scan_Stop(void) {
    drv_ext_adc_stop();

    #ifndef DISABLE_LASER_SWITCHING    
    drv_laser_off();
    #endif    

    #ifndef DEBUG_ADC  
    CMP_1_CompareDisable();
    CVR_Stop();

    // Clear interrupt flags and enable the CMP interrupt    
    EVIC_SourceDisable(INT_SOURCE_COMPARATOR_1);
    EVIC_SourceStatusClear(INT_SOURCE_COMPARATOR_1);

    EVIC_SourceDisable(LSC_BUSY_INTERRUPT);
    EVIC_SourceStatusClear(LSC_BUSY_INTERRUPT);

    drv_lsc_stop_scanning();

    scanData.scanning = false;
    scanData.stop_scanning = false;
    scanData.previous_state = scanData.state; // If there is no previous error, try sending        
    scanData.state = SCAN_COMPLETE;
    #else
    scanData.previous_state = scanData.state; // If there is no previous error, try sending
    scanData.state = SCAN_WAIT; // stop command one more time.    
    #endif
}

/*******************************************************************************
 * Function:        bool Scan_Check_DMA(void)
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
bool Scan_Check_DMA(void) {
    return (DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_3));
}

/*******************************************************************************
 * Function:        void Scan_Append_Measurement( void )
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
void Scan_Append_Measurement(_MEASUREMENT* measurement) {
    if (measurement->Count < PDAB_MAX_PEAKS) {
        measurement->Peak[measurement->Count].Position = DRV_EXT_ADC_DMA_CH3_COUNT;

        if (measurement->Peak[measurement->Count].Position > 1U)
            measurement->Count++;
    }
}

/*******************************************************************************
 * Function:        uint16_t Scan_Tasks()
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
void Scan_Append_Status(_SCAN_STATUS* status) {
    // Tag each scan with the direction and channel
    
    if(scanData.scanning){
        status->Flags.Direction = !SYS_PORT_PinRead(LSC_DIR_PIN); // Direction 
        status->Flags.IPValid = SYS_PORT_PinRead(IP_VALID_PIN);
        status->Offset = drv_ext_adc_get_offset(DRV_EXT_ADC_1);
        status->Zero[0] = drv_dac_get_value(DRV_DAC_1);
        status->Zero[1] = drv_dac_get_value(DRV_DAC_2);
        status->Power = drv_dpot_get_resistance(DRV_DPOT_1);
        status->Gain = (uint8_t)calculate_digipot_setting(scanData.auto_gain_current_gain);
        status->Count = scanData.scan_count;
    }
       
//    status->Flags.LED1 = SYS_PORT_PinLatchRead(LED1_PIN);
//    status->Flags.LED2 = SYS_PORT_PinLatchRead(LED2_PIN);
    status->Flags.LON = SYS_PORT_PinLatchRead(LON1_PIN);
    status->Flags.LPON = SYS_PORT_PinRead(LPON1_PIN);
    status->Flags.ILED = 0U;
    status->Flags.Scanning = scanData.scanning;
    status->Flags.Channel = 1U; // This must be 1 as a hotfix to DCS bug. This ensures that the first byte in the status structure is non-zero
    status->Flags.USB = USB_is_device_attached();
    


    status->Length = scanData.scan_length;
    status->Error = scanData.error;
    status->Duration = scanData.scan_time;
    status->Rate = scanData.scanRate;
}

/*******************************************************************************
 * Function:        Scan_Set_Zero_For_Gain()
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
 * Overview:        This function sets zero offset appropriate for the current
 *                  gain setting
 *
 * Notes:           None
 ******************************************************************************/
static void Scan_Set_Zero_For_Gain() {
    double step = (AUTO_GAIN_MAX - AUTO_GAIN_MIN) / (((double) AUTO_GAIN_STEPS) - 1.0);
    uint8_t idx = (uint8_t) (rint((scanData.auto_gain_current_gain - AUTO_GAIN_MIN) / step) + 0.1); //0.1 is there to avoid int casting to round down

    drv_dac_set_value(DRV_DAC_1, dac_zero_for_gain[idx]);

    #ifdef DEBUG_AUTOGAIN
    dprintf_colour("[CYAN]New Offset: %d, %d[WHITE]\r\n", idx, dac_zero_for_gain[idx]);
    #endif
}

/*******************************************************************************
 * Function:        Scan_Auto_Adjust_Gain()
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
 * Overview:        This function detects the gain required and automatically sets .
 *                  it depending on the AC peak size
 *
 * Notes:           None
 ******************************************************************************/
static bool Scan_Auto_Adjust_Gain(SCAN_DATA* scan_data) {
    static uint32_t recent_peaks[AUTOGAIN_SAMPLES];
    static uint8_t next_queue_loc = 0;

    uint16_t* sc_data = scan_data->scan_processing_buffer->Data;
    uint32_t peak_val = 0;
    uint8_t saturation_counter = 0;
    uint16_t i;
    double average_peak_value = 0.0;
    double corrected_gain;

    //First find the peak value
    for (i = 0; i < PDAB_SCAN_LENGTH_16; i++) {
        if ((uint32_t) sc_data[i] > peak_val) {
            peak_val = (uint32_t) sc_data[i];
        }
        if (sc_data[i] >= SCAN_SATURATION_LIMIT) {
            saturation_counter++;
        }
    }

    //If peak saturated, estimate it.
    if (saturation_counter > 0) {
        peak_val = (uint32_t) (65536.0 + (20.27 * ((double) saturation_counter * (double) saturation_counter)) - 41.014 * (double) saturation_counter);
    }

    #ifdef DEBUG_AUTOGAIN
    dprintf_colour("Peak val: %d, saturation: %d\r\n", peak_val, saturation_counter);
    #endif

    //Add the peak to the queue.
    recent_peaks[next_queue_loc++] = peak_val;
    if (next_queue_loc >= AUTOGAIN_SAMPLES) {
        next_queue_loc = 0;
    }
    if (scanData.auto_gain_scan_count < AUTOGAIN_SAMPLES) {
        scanData.auto_gain_scan_count++;
        //If not enough samples in the queue, stop here.
        return false;
    }
    //If block acquisition in progress, stop here.
    if (scan_data->collect_block) {
        #ifdef DEBUG_AUTOGAIN
        dprintf_colour("[RED]Acquiring block, no gain change[WHITE]\r\n");
        #endif
        return false;
    }

    //If reached this point, proceed and find an average of the last peaks.
    for (i = 0; i < AUTOGAIN_SAMPLES; i++) {
        average_peak_value += (double) recent_peaks[i];
    }
    average_peak_value /= (double) (AUTOGAIN_SAMPLES);
    #ifdef DEBUG_AUTOGAIN
    dprintf_colour("[GREEN]Av peak val: %f[WHITE]\r\n", average_peak_value);
    #endif

    //Calculate new gain.
    double best_delta;
    double possible_gain;
    double delta;

    if(fabs(average_peak_value) > PRACTICAL_ZERO) {
        for(i = 0; i < AUTO_GAIN_STEPS; i++)
        {
            possible_gain = Scan_Idx_To_Gain(i);
            delta = fabs(TARGET_PEAK_SIZE - average_peak_value / scanData.auto_gain_current_gain * possible_gain);
            if(i==0 || delta < best_delta)
            {
                best_delta = delta;
                corrected_gain = possible_gain;
            }
        }
    } else {
        corrected_gain = AUTO_GAIN_MAX;
    }

    //Make sure that the new gain is within the bounds.
    if (corrected_gain > AUTO_GAIN_MAX) {
        corrected_gain = AUTO_GAIN_MAX;
    }
    if (corrected_gain < AUTO_GAIN_MIN) {
        corrected_gain = AUTO_GAIN_MIN;
    }

    #ifdef DEBUG_AUTOGAIN
    dprintf_colour("[CYAN]New gain: %f[WHITE]\r\n", corrected_gain);
    #endif

    //If gain has changed, update it
    if (fabs(corrected_gain - scanData.auto_gain_current_gain) > PRACTICAL_ZERO) {
        scanData.auto_gain_current_gain = corrected_gain;
        PDAB_Set_Gain(PDAB_ADC_CHANNEL_1, calculate_digipot_setting(scanData.auto_gain_current_gain));
        Scan_Set_Zero_For_Gain();

        #ifdef DEBUG_AUTOGAIN
        dprintf_colour("[YELLOW]Gain changed to: %d[WHITE]\r\n", calculate_digipot_setting(scanData.auto_gain_current_gain));
        #endif
        scanData.auto_gain_scan_count = 0;
        return true;
    }
    return false;
}

static uint16_t checksum(const uint16_t *data, uint32_t length) {
    uint16_t crc = 0;
    while (length > 0) {
        length--;
        crc += data[length];
    }

    return (~crc);
}

void show_dac_vals(void) {
    int ih;
    for (ih = 0; ih < AUTO_GAIN_STEPS; ih++) {
        dprintf_colour("[BROWN]dac%d: %d[WHITE]\r\n", ih, dac_zero_for_gain[ih]);
    }
}

/*******************************************************************************
 * Function:        uint16_t Scan_Tasks()
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
SCAN_STATES Scan_Tasks(void) {
    //static uint8_t status_message[PDAB_STATUS_LENGTH_8 + 2];
    static uint8_t status_message[PDAB_HEADER_LENGTH_8 + 2];
    #define SCANNING_TIMEOUT_DEFAULT 1250000
    static uint32_t scanning_timeout = SCANNING_TIMEOUT_DEFAULT;
    static int complete = 0;
    static uint16_t peaks_copy[3];
    
    
    switch (scanData.state) {
        case SCAN_IDLE:
            break;

        case SCAN_INITIALISE:
            Scan_Initialise();
            scanData.previous_state = scanData.state;
            scanData.state = SCAN_IDLE;
            break;

        case SCAN_WAIT_FOR_ZERO:

            if (!drv_ext_adc_zero_busy()) {
                #ifdef DEBUG_DAQ
                dprintf_colour("[BROWN]Zero offset complete: %d[WHITE]\r\n", drv_ext_adc_get_zero(PDAB_ADC_CHANNEL_1));
                #endif
                scanData.previous_state = scanData.state;
                scanData.state = SCAN_START_SCANNING;
            }
            break;

        case SCAN_START_SCANNING:
            Scan_Start(); // Start Scanning
            scanData.previous_state = scanData.state;
            scanData.state = SCAN_SCANNING;
            complete = false;
            break;

        case SCAN_SCANNING:
            if (!LSC_BUSY) {

            }

            if (scanData.stop_scanning == true) {
                scanData.previous_state = scanData.state;
                scanData.state = SCAN_STOP_SCANNING;
                scanData.stop_scanning = false;
            }
            //one of the propositions in case of PDAB state not idle error
            else {
                if (scanning_timeout-- == 0) {
                    dputs_colour("[RED]ERROR: SCAN_SCANNING.[WHITE]\r\n");
                    scanning_timeout = SCANNING_TIMEOUT_DEFAULT;
                    scanData.previous_state = scanData.state;
                    scanData.state = SCAN_STOP_SCANNING;
                    scanData.stop_scanning = false;
                }
            }
            break;

        case SCAN_SETUP_BUFFER:
            if (scanData.acquisition_complete == false) {
                scanning_timeout = SCANNING_TIMEOUT_DEFAULT;
                scanData.scan_processing_buffer = scanData.scan_buffer;
                
                memcpy(&scanData.scan_processing_buffer->Header.device_name[0], &pdabData.device_name[0],16);
                scanData.scan_processing_buffer->Header.scans_counter = device_statistics.scans_counter;
                
                Scan_Buffer_Setup();
                scanData.previous_state = scanData.state;
                scanData.state = SCAN_PROCESS_DATA;
            } else {
                scanData.state = scanData.previous_state;
            }
            
            break;

        case SCAN_PROCESS_DATA:
            
            //copy raw data to usb buffer as soon as they arrive
            memcpy(&scan_buffer_for_usb.Buffer, scanData.scan_processing_buffer->Buffer, sizeof (_SCAN_BUFFER));
            
            
            
            peaks_copy[0] = 0;
            peaks_copy[1] = 0;
            peaks_copy[2] = 0;

            if ((scanData.scan_count < PDAB_IGNORE_INIT_SCANS)|| scanData.skip_scan) {
                scanData.skip_scan = false;
                scanData.previous_state = scanData.state;
                scanData.state = SCAN_SCANNING;
            } else 
            {
                peaks_copy[0] = cmp_positions[0];
                peaks_copy[1] = cmp_positions[1];
                peaks_copy[2] = scanData.scan_processing_buffer->Header.Measurement.Peak[0].Position;
                
                
                
                if (false == scanData.collect_block) {
                    if (Scan_Auto_Adjust_Gain(&scanData)) {
                        scanData.skip_scan = true;
                        scanData.previous_state = scanData.state;
                        scanData.state = SCAN_TRANSMIT_DATA_USB;
                        break;
                    }
                }
                
                if (scanData.npda_scan_count < PDAB_NPDA_SCANS) {
                    #ifdef DEBUG_NPDA
                    dprintf_colour("[YELLOW]NPDA Scans: %d[WHITE]\r\n", scanData.npda_scan_count);
                    #endif

                    if (Truncate_Data(scanData.scan_processing_buffer, scanData.npda_scan_buffer, scanData.preselection_scan, scanData.npda_scan_count)) {
                    
                        if (false == scanData.collect_block) {
                            if (Find_Peaks_NPDA(&scanData.scan_processing_buffer->Header, &scanData.preselection_scan->Data[0], &scanData.scan_settings)) {
                                scanData.scan_processing_buffer->Header.Valid = Scan_Selection(&scanData.scan_processing_buffer->Header.Measurement, &scanData.scan_settings);
                                if (scanData.scan_processing_buffer->Header.Valid) {
                                    Process_Valid_Measurement(&scanData.scan_processing_buffer->Header.Measurement, &scanData.scan_settings);
                                    scanData.collect_block = true;
                                    scanData.block_count++;
                                    scanData.block_scan_count = 0U;

                                    #ifdef DEBUG_NPDA
                                    dputs_colour("[YELLOW]Starting block collection...[WHITE]\r\n");
                                    #endif
                                    
                                    //happens only when the C&V RIG is sending scan command
                                    if(pdabData.scan_from_usb){
                                        scanData.collect_block = false;
                                        scanData.block_count--;
                                    }

                                }
                            }
                        }
                        if(true ==scanData.collect_block) {
                            scanData.npda_scan_buffer->DC_Level[scanData.npda_scan_count] = median_uint16_t(scanData.scan_processing_buffer->Data, scanData.scan_processing_buffer->Header.Status.Length);
                            scanData.block_scan_count++; 
                            scanData.npda_scan_count++; 
                            
                            scanData.scan_processing_buffer->Header.Measurement.Scans = scanData.scan_valid_count; //Incremented on each valid scan in Process_Valid_Measurement
                            
                            if (scanData.block_scan_count >= PDAB_NPDA_BLOCK_SIZE) {
                                scanData.collect_block = false;

                                #ifdef DEBUG_NPDA
                                dputs_colour("[YELLOW]Block complete.[WHITE]\r\n");
                                #endif
                            }

                            if (scanData.npda_scan_count >= PDAB_NPDA_SCANS) {
                                #ifdef DEBUG_NPDA
                                dputs_colour("[YELLOW]NPDA acquisition complete.[WHITE]\r\n");
                                #endif

                                scanData.acquisition_complete = true;
                                
                                scanData.previous_state = scanData.state;
                                scanData.state = SCAN_TRANSMIT_DATA_UART;
                                break;
                            }else if(scanData.scan_processing_buffer->Header.Valid){
                                
                                scanData.previous_state = scanData.state;
                                scanData.state = SCAN_TRANSMIT_DATA_UART;
                                break;
                                
                            }
                        }

                    } else {
                        #ifdef DEBUG_PROCESSING
                            dputs_colour("[YELLOW]Truncate failed.[WHITE]\r\n");
                        #endif
                            
                    
                    }
                    if ((scanData.scan_count % 5) == 0) {

                        if (scanData.scan_processing_buffer->Header.Status.Flags.Direction == BCK) {
                            scanData.scan_processing_buffer->Header.Measurement.Peak[0].Position = peaks_copy[2];
                            if (scanData.scan_processing_buffer->Header.Measurement.Peak[0].Position > 0U) {
                                scanData.scan_processing_buffer->Header.Measurement.Peak[0].Position = 5000U - scanData.scan_processing_buffer->Header.Measurement.Peak[0].Position; // Flip peak positions for backward scan so GUI can be updated
                            }
                        }

                        scanData.state = scanData.previous_state;
                        scanData.state = SCAN_TRANSMIT_DATA_UART;
                        break;
                    }
                    scanData.state = scanData.previous_state;
                    scanData.state = SCAN_TRANSMIT_DATA_USB;
                    break;
                } // end if scan_count 

                scanData.previous_state = scanData.state;
                scanData.state = SCAN_SCANNING;                  
            }
            break;

        case SCAN_TRANSMIT_DATA_UART:
        {
            uint32_t command_length = 0;
            status_message[command_length] = (uint8_t) RESPONSE_SCAN_STATUS;
            command_length++;
            status_message[command_length] = ':';
            command_length++;
            memcpy(&status_message[command_length], scanData.scan_processing_buffer->Buffer, sizeof (_SCAN_HEADER));
            command_length += sizeof (_SCAN_HEADER);
            pic_communications_send_message((uint8_t *) status_message, command_length, false); // requires ACK
            #ifdef DEBUG_NPDA
            dputs_colour("[YELLOW]Transmitting scan header.[WHITE]\r\n");
            #endif
            scanData.state = SCAN_TRANSMIT_DATA_USB;
        }
            break;

        case SCAN_TRANSMIT_DATA_USB:
            if (USB_is_device_attached() && (pdabData.usb_software != USB_SOFTWARE_NUL) && pdabData.usb_enable == true)
            {
                //#define TEST_DATA_COLLECTION
                #ifdef TEST_DATA_COLLECTION
                int i;
                for (i = 0; i < 4999; i++) {
                    scanData.scan_processing_buffer->Words[i] = test_usb_data[i];
                }
                scanData.scan_processing_buffer->Words[4999] = scan_counter;
                dprintf_colour("[PINK]SC: %d[WHITE]\r\n", scanData.scan_count);
                scan_counter++;
                #endif

                #define TEST_DATA_COLLECTION2
                #ifdef TEST_DATA_COLLECTION2
                
                #endif
                
                
                scanData.scan_processing_buffer->Header.Status.Flags.USB_Overrun = USB_is_buffer_overrun();
                bool skip_sending = false;
                
                if(pdabData.usb_software == USB_SOFTWARE_DCS && scanData.scan_processing_buffer->Header.Status.Flags.USB_Overrun == 1){
                    scanData.scan_processing_buffer->Header.Status.Flags.USB_Overrun = 0;
                    skip_sending = true;
                    dprintf_colour("[RED]ERROR: USB Overrun.[WHITE]\r\n");
                }
                    
                
                if(skip_sending == false)
                {                    
                    int i;
                    //copy just a header to usb buffer after the processing (just before sending via USB)
                    for (i = 0; i < PDAB_HEADER_LENGTH_8; i++) {
                        scan_buffer_for_usb.Header.Bytes[i] = scanData.scan_processing_buffer->Header.Bytes[i];
                    }
                    //add margins for data integrity check
                    for (i = 0; i < 3; i++) {
                        scan_buffer_for_usb.Words[i] = i + 1;
                    }
                    for (i = 4997; i < 5000; i++) {
                        scan_buffer_for_usb.Words[i] = i + 1;
                    }
                    
                    
                    
                    //calculate and add checksum
                    scan_buffer_for_usb.Header.Scan_data_checksum = checksum(scan_buffer_for_usb.Words, 5000);
                    int state = USB_DEVICE_RESULT_OK;
                    
                    if((pdabData.scan_from_usb)  && (pdabData.usb_software == USB_SOFTWARE_VCT)){
                    //if((scanData.scan_count % 5) == 0 && (pdabData.scan_from_usb)  && (pdabData.usb_software == USB_SOFTWARE_VCT)){
                        state = USB_Return_Data((const void *) scan_buffer_for_usb.Buffer, sizeof(scan_buffer_for_usb.Buffer), USB_DEVICE_TRANSFER_FLAGS_MORE_DATA_PENDING);
                    }
                    if((pdabData.usb_software == USB_SOFTWARE_DCS)){
                        state = USB_Return_Data((const void *) scan_buffer_for_usb.Buffer, sizeof(scan_buffer_for_usb.Buffer), USB_DEVICE_TRANSFER_FLAGS_MORE_DATA_PENDING);
                    }
                    if (USB_DEVICE_RESULT_OK == state) {
                        #ifdef DEBUG_SCAN
                        Scan_Buffer_Setup();
                        #endif
                        // NO BREAK
                    } else if (USB_DEVICE_RESULT_ERROR_TRANSFER_QUEUE_FULL == state) {
                        dprintf_colour("[RED]USB communication error: %d[WHITE]\r\n", state);
                        
                    } else {
                        dprintf_colour("[RED]USB communication error: %d[WHITE]\r\n", state);
                        //scanData.previous_state = scanData.state;
                        //scanData.state = SCAN_ERROR;
                        //USB_Clear_Endpoints(); // Flush USB Endpoints
                        #ifdef DEBUG_USB
                        dprintf_colour("[RED]USB_ERROR_IRP_QUEUE_FULL: %d[WHITE]\r\n", USB_ERROR_IRP_QUEUE_FULL); // Uncomment aid identification of USB error 
                        dprintf_colour("[RED]USB_ERROR_TRANSFER_TERMINATED_BY_HOST: %d[WHITE]\r\n", USB_ERROR_TRANSFER_TERMINATED_BY_HOST);
                        dprintf_colour("[RED]USB communication error: %d[WHITE]\r\n", state);
                        #endif
                        break;
                    }
                }
            }

            if (pdabData.usb_software != USB_SOFTWARE_VCT) 
            {
                scanData.previous_state = scanData.state;
                if (true == complete) {
                    scanData.state = SCAN_IDLE;
                } else if (true == scanData.acquisition_complete) {
                    scanData.state = SCAN_STOP_SCANNING;
                    scanData.stop_scanning = false;
                } else {
                    scanData.state = SCAN_SCANNING;
                }
            }
            else
            {
                scanData.state = SCAN_SCANNING;
            }

            
            break;

        case SCAN_STOP_SCANNING:

            if (complete == true) {
                scanData.previous_state = scanData.state;
                scanData.state = SCAN_IDLE;
                dputs_colour("[RED]-------> EXTRA STOP[WHITE]\r\n");
                break;
            }
            
            if (!DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_3)) {
                scanData.previous_state = scanData.state;
                scanData.state = SCAN_WAIT_FOR_STOP;
                #ifdef DEBUG_DAQ
                dputs_colour("[YELLOW]Stop scanning[WHITE]\r\n");
                #endif                                 
            }

            break;

        case SCAN_WAIT_FOR_STOP:
            Scan_Stop();
            break;

        case SCAN_COMPLETE:

            if (!Scan_Check_DMA()) {
                Scan_Timer_Report(); // Report scan duration and frequency 

                #ifndef DISABLE_NPDA
                if (scanData.acquisition_complete) {
                    scanData.previous_state = scanData.state;
                    scanData.state = SCAN_PROCESS_MEASUREMENT;
                    break;
                }
                #endif    

                scanData.previous_state = scanData.state;
                scanData.state = SCAN_IDLE;

                #ifdef DEBUG_DAQ
                dputs_colour("[YELLOW]Scanning complete[WHITE]\r\n");
                #endif
            }

            break;

        case SCAN_PROCESS_MEASUREMENT:
            if (scanData.scan_processing_buffer->Header.Complete == false) {
                #ifdef DEBUG_NPDA
                dputs_colour("[YELLOW]Processing NPDA data.[WHITE]\r\n");
                #endif
                NPDA_RETVAL npda_ret = run_npda(scanData.npda_scan_buffer, scanData.scan_processing_buffer, &cal_data[0]);
                scanData.scan_processing_buffer->Header.Measurement.Thickness[0] = scanData.scan_processing_buffer->Header.Measurement.Separation[0] * scanData.scan_settings.refractive_index;
                scanData.scan_processing_buffer->Header.Measurement.Count = scanData.block_count;
                scanData.scan_processing_buffer->Header.Complete = true;
                complete = true;
                Scan_Append_Status(&scanData.scan_processing_buffer->Header.Status);
                scanData.scan_processing_buffer->Header.Status.Error = (uint16_t) npda_ret;
                scanData.previous_state = scanData.state;
                scanData.state = SCAN_TRANSMIT_DATA_UART;
            }

            break;

        case SCAN_ERROR:
            Scan_Stop();

            scanData.previous_state = SCAN_ERROR;
            scanData.state = SCAN_STOP_SCANNING;
            break;
            
        case SCAN_RECOVER_USB:
            {
                Scan_Stop();
                if (!DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_3)) {
                    scanData.previous_state = scanData.state;
                    scanData.state = SCAN_WAIT_FOR_STOP;
                    Scan_Stop();
                        /* Perform system unlock sequence */
                        SYSKEY = 0x00000000;
                        SYSKEY = 0xAA996655;
                        SYSKEY = 0x556699AA;

                        RSWRSTSET = _RSWRST_SWRST_MASK;
                        (void) RSWRST;
                        while(1);
                    dputs_colour("[YELLOW]F: SCAN_RECOVER_USB[WHITE]\r\n");
                    break;
                }
            }
            break;
        default:
            scanData.state = SCAN_ERROR;
            scanData.error = SCAN_ERROR;
            break;
    }

    return (scanData.state);
}

/*******************************************************************************
 * Function:        Scan_Initialise
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
void Scan_Initialise(void) {
    #ifndef DEBUG_ADC            
    scanData.dma_source = (void *) KVA_TO_PA(drv_ext_adc_get_buffer());
    GPIO_PortInterruptEnable(GPIO_PORT_B, _CNFB_CNFB12_MASK);
    GPIO_PinInterruptCallbackRegister(LSC_BUSY_PIN, (GPIO_PIN_CALLBACK) Scan_CN_Interrupt_Handler, (uintptr_t) & scanData);
    DMAC_ChannelCallbackRegister(DRV_EXT_ADC_DMA_CHANNEL_3, (DMAC_CHANNEL_CALLBACK) Scan_DMA_Interrupt_Handler, (uintptr_t) & scanData);
    CMP_1_CallbackRegister((CMP_CALLBACK) Scan_CMP1_Interrupt_Handler, (uintptr_t) & scanData);
    #else
    scanData.dma_source = (void *) KVA_TO_PA((void *) &PMDIN);
    DMAC_ChannelCallbackRegister(DRV_EXT_ADC_DMA_CHANNEL_2, (DMAC_CHANNEL_CALLBACK) Scan_DMA_Interrupt_Handler, (uintptr_t) & scanData);
    #endif
}

/*******************************************************************************
 * Function:        Start_Scanning
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
bool Start_Scanning(COMM_STATES interface) {
    if (scanData.state == SCAN_IDLE) {
        #ifdef DEBUG_DAQ
        dputs_colour("[PINK]Initiating scanning...[WHITE]\r\n");
        #endif
        scanData.comm_interface = interface;
        scanData.previous_state = scanData.state;
        scanData.state = SCAN_WAIT_FOR_ZERO;
        return true;
    } else {
        dprintf_colour("[RED]Scan state is not SCAN_IDLE: %d[WHITE]\r\n", scanData.state);
        return false;
    }

}

/*******************************************************************************
 * Function:        Stop_Scanning
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
void Stop_Scanning(void) {
    if (scanData.block_count >= MINIMUM_VALID_BLOCKS) {
        scanData.acquisition_complete = true;
    }
    dputs_colour("[YELLOW]F: Stop_Scanning[WHITE]\r\n");
    scanData.stop_scanning = true;
    //Make sure that, once the scan is stopped, the gain goes back to where it was
    scanData.auto_gain_current_gain = AUTO_GAIN_MAX;
    scanData.auto_gain_scan_count = 0;
    PDAB_Set_Gain(PDAB_ADC_CHANNEL_1, calculate_digipot_setting(scanData.auto_gain_current_gain));
    Scan_Set_Zero_For_Gain();

    #ifdef DEBUG_DAQ
    dputs_colour("[YELLOW]Stop scanning[WHITE]\r\n");
    #endif     
}

/*******************************************************************************
 * Function:        void update_scan_settings(SCAN_SETTINGS *scan_settings)
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
 * Overview:        Update scan settings received from the PIB
 *
 * Notes:           None
 ******************************************************************************/
void update_scan_settings(void) {
    scanData.scan_settings.comparator_reference_voltage = device_settings.VOLTAGE_TRESHOLD;
    scanData.scan_settings.fwhm_limits[0] = device_settings.MIN_FWHM;
    scanData.scan_settings.fwhm_limits[1] = device_settings.MAX_FWHM;
    scanData.scan_settings.peak_thresholds[0] = device_settings.P1_TRESHOLD;
    scanData.scan_settings.peak_thresholds[1] = device_settings.P2_TRESHOLD;
    scanData.scan_settings.separation_limits[0] = device_settings.MIN_SEPARATION;
    scanData.scan_settings.separation_limits[1] = device_settings.MAX_SEPARATION;
    scanData.scan_settings.separation_limits[1] = device_settings.MAX_SEPARATION;
    scanData.scan_settings.amplifier_gain = scanData.auto_gain_current_gain;


    PDAB_Set_Power(PDAB_ADC_CHANNEL_1, scanData.scan_settings.laser_power);
}

/*******************************************************************************
 * Function:        void Process_Valid_Measurement( _MEASUREMENT* measurement,  _SCAN_SETTINGS* settings, bool post )
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
 * Overview:        Update scan settings received from the PIB
 *
 * Notes:           None
 ******************************************************************************/
void Process_Valid_Measurement(_MEASUREMENT* measurement, _SCAN_SETTINGS* settings) {
    // Note that the PIB does not use the values from this calculation, it performs its own
    // calculations based on the peak positions.

    measurement->Scans = ++scanData.scan_valid_count;
    measurement->Thickness[0] = measurement->Separation[0] * settings->refractive_index * SCAN_RESOLUTION;
}

/*******************************************************************************
 * Function:        bool Scan_Busy(void)
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
 * Overview:        Check if the scan state machine is busy
 *
 * Notes:           None
 ******************************************************************************/
bool Scan_Busy(void) {
    if (scanData.state == SCAN_IDLE)
        return false;
    else
        return true;
}
/* *****************************************************************************
 End of File
 */
