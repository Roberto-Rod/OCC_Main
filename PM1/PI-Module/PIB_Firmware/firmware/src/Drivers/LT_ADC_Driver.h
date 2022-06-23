/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   iScan
 File Name: LT_ADC-Driver.h   
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

#ifndef _LT_ADC_DRIVER_H
#define _LT_ADC_DRIVER_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include <xc.h>
#include <stddef.h>
#include <stdlib.h>

#include "Delay.h"
#include "FPGA_Driver.h"
#include "AD_DAC_Driver.h"
#include "AD_DPOT_Driver.h"

/*******************************************************************************
                             Definitions
*******************************************************************************/
//#define LT_ADC_DEBUG
//#define LT_ADC_DMA
#define AUTO_ADC_OFFSET

#define LT_ADC_FIFO_DELAY   1

#define LT_ADC_VAMP         0L
#define LT_ADC_VDIFF        1L
#define LT_ADC_CHANNEL1     0L
#define LT_ADC_CHANNEL2     1L
#define LT_ADC_MAX_CHANNELS 2L

#define LT_ADC_MAX          65535L      // ADC max count -> 16 bit -> 65535
#define LT_MAX_OFFSET       57535L      // DAC max offset (Define by electronic design due to dynamic range limitations)

#define LT_ADC_TIMEOUT      1000L        // Timeout during ADC sample acquisition 

#define LT_ZERO_UTHRESH     10000L      // Threshold at which the offset is incremented by large inrecents
#define LT_ZERO_MTHRESH     1000L       // Threshold at which the offset is incremented by small inrecents
#define LT_ZERO_LTHRESH     200L        // Zero target for the first amplifier stage

#define LT_ZERO_SAMPLES     100L       // Number of samples to acquire for each average
#define LT_ZERO_LINCR       100L       // Large zero offset (DAC) increment)
#define LT_ZERO_MINCR       10L         // Medium zero offset (DAC) increment)
#define LT_ZERO_SINCR       1L          // Small zero offset (DAC) increment)
/*******************************************************************************
                            Macros
*******************************************************************************/

/*******************************************************************************
                              Variables
*******************************************************************************/
extern double 	    LT_ADC_CONVERSION_FACTOR;
extern uint16_t  	LT_ADC_OFFSET[2];
/*******************************************************************************
                            Function Prototypes 
 ******************************************************************************/
bool AdcInit(void);
bool AdcZero( uint16_t channel, bool adcOffset );
bool AdcOffset( uint16_t channel );
uint16_t AdcSamples( uint16_t channel, uint16_t len );
/*******************************************************************************/

#endif
