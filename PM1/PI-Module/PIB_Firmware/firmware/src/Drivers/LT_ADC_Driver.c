/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   iScan
 File Name: LT_ADC_Driver.c   
 Processor: PIC32MZ
 Hardware:  Main Processor Board
 Assembler: pic32-gcc
 Linker:    pic32-ld
 
 Description: 
 
 Functions: 
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Intial Version
*******************************************************************************/

#ifndef _LT_ADC_DRIVER_C
#define _LT_ADC_DRIVER_C

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include <LT_ADC_Driver.h>
/*******************************************************************************
                              Variables
*******************************************************************************/
uint16_t LT_ADC_OFFSET[2];
/*******************************************************************************
 * Function:        AdcInit
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function intialises the ADC
 *
 * Notes:           None
 ******************************************************************************/    
 
 bool AdcInit(void)
 {   
	return 0;
 }
 /*******************************************************************************
 * Function:        AdcZero
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function sets the zero offset on the amplifiers
 *
 * Notes:           None
 ******************************************************************************/    
 bool AdcZero( uint16_t channel, bool adcOffset )
 {   
    bool exit = false;
	uint16_t dacIndex = channel * 2L;
	uint16_t temp_adc = 0L;
	double again = 0.00F;
	uint32_t zlimit = 0L;  
    
    if( channel < LT_ADC_MAX_CHANNELS )
    {
#ifdef  AUTO_ADC_OFFSET
        if( adcOffset )
        {
            AdcOffset(channel);
        }
#endif
        DelayMs( 10 );	

        AD_DAC_VOLTAGE[dacIndex] = AD_DAC_MIN;       // Set the ADC offset values to nominal zero (2.5V) 
        AD_DAC_VOLTAGE[dacIndex + 1] = AD_DAC_MIN;	

        if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_1, &AD_DAC_VOLTAGE[dacIndex] ) ) {	// Write the second stage amplifier offset to nominal zero
            return false;
        }    

        if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_2, &AD_DAC_VOLTAGE[dacIndex + 1] ) ) {	// Write the second stage amplifier offset to nominal zero
            return false;
        }

        while( exit == false ) {
		 
#ifdef DEBUG_ADC        
            AD_DAC_VOLTAGE[dacIndex]++;

            if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_1, &AD_DAC_VOLTAGE[dacIndex] ) ) {	
                return false;
            }	

            DelayMs( 1 );
#else

            if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_1, &AD_DAC_VOLTAGE[dacIndex] ) ) {
                return false;
            }        

            DelayUs( 100 );

            temp_adc = AdcSamples( channel, LT_ZERO_SAMPLES);

            if( temp_adc > LT_ZERO_UTHRESH ){

                AD_DAC_VOLTAGE[dacIndex] += LT_ZERO_LINCR;                

                    if( AD_DAC_VOLTAGE[dacIndex] > LT_MAX_OFFSET  ) {
                        AD_DAC_VOLTAGE[dacIndex] = LT_MAX_OFFSET ;
                    exit = true;
                }							
            }			
            else if( temp_adc > LT_ZERO_MTHRESH ){

                AD_DAC_VOLTAGE[dacIndex] += LT_ZERO_MINCR;

                    if( AD_DAC_VOLTAGE[dacIndex] > LT_MAX_OFFSET ) {
                        AD_DAC_VOLTAGE[dacIndex] = LT_MAX_OFFSET ;
                    exit = true;
                }					
            }
            else if(  temp_adc > LT_ZERO_LTHRESH ) {

                AD_DAC_VOLTAGE[dacIndex] += LT_ZERO_SINCR;

                    if( AD_DAC_VOLTAGE[dacIndex] > LT_MAX_OFFSET ) {
                        AD_DAC_VOLTAGE[dacIndex] = LT_MAX_OFFSET ;
                    exit = true;
                }	
            }
            else
            {
                exit = true;
            }   
    #endif		
        }	

#ifdef  AUTO_ADC_OFFSET    
        if( adcOffset )
        {
            temp_adc = AdcSamples( channel, LT_ZERO_SAMPLES);
            LT_ADC_OFFSET[channel] += temp_adc;
            temp_adc = AdcSamples( channel, LT_ZERO_SAMPLES);
        }
#endif

        again = 1.00F + ( (double)R2 / (double)( (double)RW + (double)( (double)RAB * ( (double)AD_DPOT_RESISTANCE[dacIndex] / (double)POS ) ) + (double)( 2.00F * (double)RW ) ) );
        zlimit = (unsigned int)( (double)temp_adc * again );

        exit = false;

        while( exit == false )
        {
            temp_adc = AdcSamples( channel, LT_ZERO_SAMPLES);

                if( temp_adc > zlimit ){

                AD_DAC_VOLTAGE[dacIndex + 1] = AD_DAC_VOLTAGE[dacIndex + 1] + 1L;

                    if( AD_DAC_VOLTAGE[dacIndex + 1] > LT_MAX_OFFSET  ) {
                        AD_DAC_VOLTAGE[dacIndex + 1] = LT_MAX_OFFSET;
                    exit = true;
                }	            

                if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_2, &AD_DAC_VOLTAGE[dacIndex + 1] ) ) {
                    return false;
                }	
            }
            else
            {
                exit = true;
            }

            DelayUs( 100 );
        }

    #ifdef  AUTO_ADC_OFFSET    
        if( adcOffset )
        {
            LT_ADC_OFFSET[channel] += AdcSamples( channel, LT_ZERO_SAMPLES);
        }
    #endif
        return true;
    }
    else
    {
        return false;
    }
 }
  /*******************************************************************************
 * Function:        AdcZero
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function sets the ADC offsets
 *
 * Notes:           None
 ******************************************************************************/    
 bool AdcOffset( uint16_t channel )
 {  
	int dacIndex = channel * 2L;
	uint16_t tempDAC1 = AD_DAC_MAX; 
	uint16_t tempDAC2 = AD_DAC_MIN; 
    
	if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_1, &tempDAC1 ) ){	
		return false;		
	}

	DelayMs( 1L );
	
	if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_2, &tempDAC2 ) ){
		return false;		
	}		

	DelayMs( 1L );
	 	
	LT_ADC_OFFSET[channel] = 0L;
	
	DelayMs( 1L );

	LT_ADC_OFFSET[channel] = AdcSamples( channel, LT_ZERO_SAMPLES);
	
	if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_1, &AD_DAC_VOLTAGE[dacIndex] ) ){
		return false;		
	}	

	DelayMs( 1L );

	if( !AD_DAC_IOCTL( AD_DAC1_ADDRESS, AD_SET_DAC, AD_DAC_2, &AD_DAC_VOLTAGE[dacIndex + 1] ) ){	
		return false;		
	}	 
	
	return true;
 } 
 /*******************************************************************************
 * Function:        AdcRead
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    Keeps system running.
 *
 * Overview:        This function retrieves a series of n samples from the ADC 
 *
 * Notes:           None
 ******************************************************************************/    
 uint16_t AdcSamples( uint16_t channel, uint16_t len )
 {    
    int32_t tempCH1 = 0L;
    int32_t tempCH2 = 0L;
    uint16_t sample = 0L;
    uint16_t i = 0L;
    
    m_FPGA_Reset();             // Initialise the FPGA and reset FIFO
    m_FPGA_Time_Sampling();     // Switch to time based samplling
    
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_1);   
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_2);    
    
#ifndef LT_ADC_DMA    

    m_FPGA_Clock_Low();
    m_FPGA_Clock_High();
    m_FPGA_Clock_Low();
    
    short timeout = LT_ADC_TIMEOUT ;
    
    for( i = 0; i < len; i++ )
    {
        FIFO_SAMPLE_CLOCK = true;        
        timeout = LT_ADC_TIMEOUT ;        
      
        while( !PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_EXTERNAL_2) && ( timeout-- > 0L ) );
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_2);
        tempCH1 = tempCH1 + _SFR_READ(&PMDIN);
        
        timeout = LT_ADC_TIMEOUT ;
        
        while( !PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_EXTERNAL_1) && ( timeout-- > 0L ) );
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_1);
        tempCH2 = tempCH2 + _SFR_READ(&PMDIN);         
        
        m_FPGA_Clock_Low();
    }
    
    m_FPGA_Clock_High();
    m_FPGA_Position_Sampling();      
    
    tempCH1 = ( tempCH1 / len ) - LT_ADC_OFFSET[channel];;
    tempCH2 = ( tempCH2 / len ) - LT_ADC_OFFSET[channel];;
    
    if( channel == 0L )
    {
        if( tempCH1 < 0L )
            sample = 0U;
        else
            sample = tempCH1;
    }
    else if( channel == 1L )
    {
        if( tempCH2 < 0L )
           sample = 0U;
        else
            sample = tempCH2;
    }
	else
        sample = 0U;
	
	return sample; 
    
#else       
    
    #ifndef ISCAN_DMA_DRV
        SYS_DMA_ChannelTransferSet( iScanData.channel0Handle, (const void *)&PMDIN, DMA_SOURCE_SIZE , (uint16_t*)temp1, len * 2, DMA_CELL_SIZE);
        SYS_DMA_ChannelTransferSet( iScanData.channel1Handle, (const void *)&PMDIN, DMA_SOURCE_SIZE , (uint16_t*)temp2, len * 2, DMA_CELL_SIZE);  
    
        SYS_DMA_ChannelEnable(iScanData.channel0Handle);             
        SYS_DMA_ChannelEnable(iScanData.channel1Handle);

        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_DMA_0);               
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_DMA_0);    
        
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_DMA_1);               
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_DMA_1);         
    #else
        DMA_Channel_Enable(DMA_CHANNEL_0);   
        DMA_Channel_Enable(DMA_CHANNEL_1);
    #endif
    
    iScanData.substate = ISCAN_SUB_ACQ_DATA;    
        
    while( iScanData.substate == ISCAN_SUB_ACQ_DATA )
    {
        m_FPGA_Clock();
    }
    
    m_FPGA_Time_Sampling();     // Switch to time based samplling   
    
    if( iScanData.substate == ISCAN_SUB_ACQ_COMPLETE )
    {
        for( i = 0; i < len; i++ )
        {      
            tempCH1 = tempCH1 + temp1[i];
            tempCH2 = tempCH2 + temp2[i];         
        }    

        tempCH1 = ( tempCH1 / len ) - LT_ADC_OFFSET[channel];
        tempCH2 = ( tempCH2 / len ) - LT_ADC_OFFSET[channel];

        if( channel == 0L )
        {
            if( tempCH2 < 0L )
                sample = 0U;
            else
                sample = tempCH2;
        }
        else if( channel == 1L )
        {
            if( tempCH1 < 0L )
               sample = 0U;
            else
                sample = tempCH1;
        }
        else
            sample = 0U;
    }
    else
    {
        sample = 0U;
    }    
    
    PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_DMA_0);            
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_DMA_0);             
    PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_DMA_1);            
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_DMA_1);    
#endif
    
    
 }
/*******************************************************************************/

#endif
