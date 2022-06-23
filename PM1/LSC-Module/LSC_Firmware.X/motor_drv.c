/* ************************************************************************** */
/** @file @file motor_drv.c
 *
 *  @brief Motor driver file.
 *
 *  @copyright Occuity Limited (c) 2021
 */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "motor_drv.h"
#include "main.h"
#include "debug.h"
#include "encoder_drv.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Global Variables                                                  */
/* ************************************************************************** */
/** @brief scanning flag */
extern bool scanning;
/** @brief power supply voltage to motor table consisting dac samples  */
extern uint16_t VM[DAC_SAMPLES];
/** @brief LSC data object defining set LSC parameters and firmware */
extern volatile _LSC_DATA lscData;
/** @brief lsc tuning object consisitng data reqiired for tuning process */
extern volatile _LSC_TUNING_OBJ lsc_tuning;

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
//************************************************************************// 
void DMA_Channel0_CallBack(void)
{
/** @brief if used differential DAC */
#ifdef DAC_DIFFERENTIAL        
/** @brief toggle the state of latch 0 port C of RC0 pin (DRV_DIR) */    
    LATCbits.LATC0 = !LATCbits.LATC0;
    if(lscData.StatusFlags.STOP){
        
        StopMotion();
        lscData.StatusFlags.STOP = false;
        
    }
    //DBG_LEDB_Toggle(); 
    
#endif           
}

/* ************************************************************************** */
/** 
 * @brief            Generate Digital to Analogue converted motor power profile
 *
 * @note             Called by static bool processing_task(void) when processing 
 *                   initialisation routine. PID controller update routine
 * 
 * @param[in/out]    _LRA_WAVEFORMS waveform, uint16_t * profile, uint16_t len, uint16_t vmin, uint16_t vmax
 * 
 * @return           None.
 */
/* ************************************************************************** */
void GenerateDACProfile(_LRA_WAVEFORMS waveform, uint16_t * profile, uint16_t len, uint16_t vmin, uint16_t vmax)											
{
    float alpha, inc, vin;    
    uint16_t i, j;

    switch (waveform)
    {
/** @brief crates samples of sinusoidal waveform. Profile of sin waveform is symmetric. Only half of the profile has to be populated and then mirror.
 *  As the output is sent through H-Bridge it is only considered the positive part of the waveform (form 0 to PI)   */  
		case LRA_SINUSOID:
#ifdef DAC_DIFFERENTIAL            
            vin = (vmax - vmin);
			alpha = PI;            
/** @brief horizontal position of a sample */            
			inc = PI / (float) len;
/** @brief if differential DAC used the whole resolution is used. The signal is scaled between the Vmax (upper limit of the range) and Vmin (lower limit of the range) */
			for (i = 0; i < (len / 2); i++)                                   
            {
                j = (len - 1) - i;            
				profile[i] = (uint16_t) (-(vin * sinf(alpha) - vmin));
                profile[j] = profile[i];                                         
				alpha = alpha + inc;	
			}
/** @brief if not differential DAC but single end mode is used only part of scale is used. The signal is scaled between the V ref and ground */            
#else
            vin = (vmax - vmin) / 2U;
			alpha = -(PI / 2.000f);            
			inc = PI / (float) (len / 2);

			for (i = 0; i < (len / 2); i++)
            {
                j = (len - 1) - i; 
				profile[i] = vmin + (uint16_t)((vin * sinf(alpha)) + vin);
                profile[j] = profile[i];
				alpha = alpha + inc;	
			}
#endif            
			break;

		case LRA_SQUAREWAVE:
            profile[0] = vmax;
            profile[1] = vmin;	
            break;
            
		case LRA_SAWTOOTH:
            break;            
    }
}

/* ************************************************************************** */
/** 
 * @brief            Set Start DAC Output flag
 *
 * @note             Called by void StartMotion(uint32_t scans, bool enqei).	
 *                   If the set frequency is the range, conveys motor power output to ADC.
 *                   Called by void DefineLimits(void). Checks if lscData.LRADriveFreq is in the range
 * 
 * @param[in/out]    float frequency, bool start
 * 
 * @return           True if set frequency is in the range
 */
/* ************************************************************************** */

bool StartDACOutput(float frequency, bool start)
{      
    if ((frequency <= FREQ_LIMIT) || (frequency >= FREQ_START))
    {          
        uint16_t period = (int16_t) ((float) FCY / (frequency * 2.0f* (float) DAC_SAMPLES));

        if (start)
        {
/* @brief DSP_DAC enabled */
            CMP1_Enable();
/* @brief DSP_DAC enabled to output value from DAC */            
            CMP1_EnableDACOutput();
/* @brief motor initialisation orders to start with the forward movement */             
            DRV_EN_SetHigh();
            DRV_SLEEP_SetHigh();
/** @brief enable communication with pic32 ehf */ 
//            DSP_BUSY_SetHigh(); 
            DRV_DIR_SetLow();             
            
/** @brief stops the SCCP7 timer and set DAC output */              
#ifndef DMA
            SCCP7_TMR_Stop();
            SCCP7_TMR_Counter16BitPrimarySet( period );            
            SCCP7_TMR_Start();            
//ARE THESE THE PERIPHERIALS USED?
/** @brief if Direct Memory Access macro is enabled, set address for access and transfer the data between peripherals (DAC and DSP_BUSY ) */  
#else     
            SCCP7_TMR_Stop();
            DMA_ChannelDisable(DMA_CHANNEL_0);
            DMA_DestinationAddressSet(DMA_CHANNEL_0, (uint16_t) &DAC1DATH);
            DMA_SourceAddressSet(DMA_CHANNEL_0, (uint16_t) VM);
            DMA_TransferCountSet(DMA_CHANNEL_0, DAC_SAMPLES);
            DMA_ChannelEnable(DMA_CHANNEL_0);
            
/** @brief set the period of the SCCP7 timer based on the chosen frequency and start the timer*/        
            SCCP7_TMR_Period16BitSecondarySet(period);
            SCCP7_TMR_Start(); 
            //DBG_LEDB_SetHigh(); 
#endif
        }
        else
        {
            SCCP7_TMR_Period16BitSecondarySet(period);           
        }   

        return (true);
    }

    return (false);
}
/* ************************************************************************** */
/** 
 * @brief            Start Motion. Configures all the scan parameters, 
 *                   initiates a scan cycle, performs n scans. 
 *
 * @note             Called by void DefineLimits(void).   
 *
 * @param[in/out]    uint32_t scans (scan limits), bool enqei  (is QEI enabled) 
 *
 * @return           None.
 */
/* ************************************************************************** */
void StartMotion(uint32_t scans, bool enqei)
{	
    
    if(scanning){return;}
    
    /** @brief turn off status LED, which indicate that a command from pic32 efh was not recognised */   
    //DSP_LED_SetLow();
    /** @brief set the number of scans */  
	lscData.ScanCount = scans;          
    /** @brief clear STOP scan flag */
    lscData.StatusFlags.STOP = false;
    /** @brief clear Quadrature Encoder Interface output enable flag */
    lscData.StatusFlags.QOE = false; 
    /** @brief set direction flag to forward movement */
    lscData.StatusFlags.DIR = true;
    if (enqei)
    {
        /** @brief set Quadrature Encoder Interface output enable flag */
        lscData.StatusFlags.QOE = true;             
    }

    /** @brief enable position compare interrupts for EMC (Encoder Motion Control?) busy signal. Enable quadrature encoder interface */
    m_EnablePMInts(); 
    if (lsc_tuning.tuning_process_flag == TUNING_FINISHED)
    { 
        DSP_BUSY_SetLow();
    }    
    
    /** @brief set error flag is driving LRA motor frequency is not in the range stops. SCCP7 timer handles DAC output */
    if (!StartDACOutput(lscData.LRADriveFreq, true))
    {
        dprintf_colour("[RED] Starting DAC fail attempt freq: %d", lscData.LRADriveFreq);        
        lscData.StatusFlags.ERR = true;
    }

    /** @brief set scanning flag */
    enc_move_wdt_start(); 
    scanning = true;
    lsc_tuning.new_scan_found = WAIT_FOR_FIRST_CYCLE;
}
/* ************************************************************************** */
/** 
 * @brief            Stop Motion.  Stop the scan cycle and disables all related interrupts.    
 *
 * @note             Called by void DefineLimits(void).
 *
 * @return           None.
 */
/* ************************************************************************** */
void StopMotion(void)                              
{
    /** @brief disable position compare interrupts for EMC (Encoder Motion Control?) busy signal. 
     * Disable quadrature encoder interface */
    m_DisablePMInts();                                

    CMP1_DisableDACOutput();
/* @brief motor brake and put to sleep orders */ 
    DRV_EN_SetLow();
    DRV_SLEEP_SetLow();

/** @brief enable communication with pic32 ehf */ 
    if (lsc_tuning.tuning_process_flag == TUNING_FINISHED)
    {  
        DSP_BUSY_SetHigh();
        //DSP_LED_SetHigh();
    }    
    enc_move_wdt_stop(); 
/** @brief clear scanning flag */    
    scanning = false;
}
