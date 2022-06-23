/******************************************************************************

 Company:   Occuity Limited
 Project:   Pachymeter
 File Name: drv_ext_adc.h   
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

#ifndef DRV_EXT_ADC_H
#define DRV_EXT_ADC_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "definitions.h"
/*******************************************************************************
                             Typedefs
*******************************************************************************/
typedef enum
{
    DRV_EXT_ADC_1 = 0x00,     
    DRV_EXT_ADC_2,
    DRV_EXT_ADC_3,
    DRV_EXT_ADC_4,            
} DRV_EXT_ADC_INDEX; 

typedef enum
{
    DRV_EXT_ZERO_OFFSET_1 = 0x00,     
    DRV_EXT_ZERO_OFFSET_2,
    DRV_EXT_ZERO_OFFSET_3,
    DRV_EXT_ZERO_OFFSET_4,            
} DRV_EXT_ZERO_OFFSET_INDEX;
/*******************************************************************************
                             Definitions
*******************************************************************************/
//#define DEBUG_EXT_ADC

#define DRV_EXT_EN_DITHER 

#define DRV_EXT_ADC_AUTO_OFFSET

#define DRV_EXT_ADC_COUNT                       1U   
#define DRV_EXT_ADC_CHANNELS_PER_DEVICE         2U
#define DRV_EXT_ADC_CHANNELS                    DRV_EXT_ADC_COUNT * DRV_EXT_ADC_CHANNELS_PER_DEVICE 

#define DRV_EXT_ADC_DMA_CHANNEL_1               DMAC_CHANNEL_0
#define DRV_EXT_ADC_DMA_CHANNEL_2               DMAC_CHANNEL_2
#define DRV_EXT_ADC_DMA_CHANNEL_3               DMAC_CHANNEL_1

#define DRV_EXT_ADC_DMA_CH1_COUNT               DCH0DPTR
#define DRV_EXT_ADC_DMA_CH2_COUNT               DCH2DPTR
#define DRV_EXT_ADC_DMA_CH3_COUNT               DCH1DPTR

#define DRV_EXT_ADC_EXTERNAL_CLOCK              INT_SOURCE_EXTERNAL_0           // External clock from DSPIC 
#define DRV_EXT_ADC_DTR                         INT_SOURCE_EXTERNAL_1           // ADC data ready
#define DRV_EXT_ADC_OEN                         SYS_PORT_PIN_RF8
#define DRV_EXT_ADC_SHDN                        SYS_PORT_PIN_RD11
#define DRV_EXT_ADC_PGA                         SYS_PORT_PIN_RD10
#define DRV_EXT_ADC_DITHER                      SYS_PORT_PIN_RD9
#define DRV_EXT_ADC_AMP_EN                      SYS_PORT_PIN_RC14
#define DRV_EXT_ADC_PORT                        PMDIN

#define DRV_EXT_ADC_DATA_WIDTH                  2U                              // Width in bytes

#define DRV_EXT_ADC_DMA1_BUFFER_SIZE            1U
#define DRV_EXT_ADC_DMA2_BUFFER_SIZE            128U
#define DRV_EXT_ADC_ADC_MAX_SAMPLES             65536L / DRV_EXT_ADC_DATA_WIDTH // ADC max samples per transfer 
/******************************************************************************/

#define DRV_EXT_ADC_VAMP             0L
#define DRV_EXT_ADC_VDIFF            1L
#define DRV_EXT_ADC_CHANNEL1         0L
#define DRV_EXT_ADC_CHANNEL2         1L
#define DRV_EXT_ADC_MAX_CHANNELS     2L

#define DRV_EXT_ADC_START_DELAY      10L      
#define DRV_EXT_ADC_SHORT_DELAY      1L 
#define DRV_EXT_ADC_LONG_DELAY       100L 

#define DRV_EXT_ADC_DAC_DEFAULT      32768L      

#define DRV_EXT_ADC_MIN              0L      
#define DRV_EXT_ADC_MAX              65535L      // ADC max count -> 16 bit -> 65535

#define DRV_EXT_DAC_MIN_OFFSET       0L          // DAC min offset (Nominal output 0V)
#define DRV_EXT_DAC_MAX_OFFSET       57343L      // DAC max offset (Define by electronic design due to dynamic range limitations)

#define DRV_EXT_ADC_TIMEOUT          1000L       // Timeout during ADC sample acquisition 

#define DRV_EXT_ADC_ZERO_UTHRESH     20000L      // Threshold at which the offset is incremented by large increments
#define DRV_EXT_ADC_ZERO_MTHRESH     2000L       // Threshold at which the offset is incremented by small increments
#define DRV_EXT_ADC_ZERO_LTHRESH     1000L       // Zero target for the first amplifier stage

#define DRV_EXT_ADC_ZERO_XINCR       1000L       // Max zero offset (DAC) increment)
#define DRV_EXT_ADC_ZERO_LINCR       300L        // Large zero offset (DAC) increment)
#define DRV_EXT_ADC_ZERO_MINCR       10L         // Medium zero offset (DAC) increment)
#define DRV_EXT_ADC_ZERO_SINCR       1L          // Small zero offset (DAC) increment)

#define DRV_EXT_ADC_RW  50L
#define DRV_EXT_ADC_RAB 10000L
#define DRV_EXT_ADC_RS  100L
#define DRV_EXT_ADC_R2 	10000L
#define	DRV_EXT_ADC_POS 128L

/*******************************************************************************
                            Macros
*******************************************************************************/

/*******************************************************************************
                              Variables
*******************************************************************************/

/*******************************************************************************
                            Function Prototypes 
 ******************************************************************************/
bool drv_ext_adc_initialise(void);
bool drv_ext_adc_tasks(void);
bool drv_ext_adc_set_channel(DRV_EXT_ADC_INDEX channel);
bool drv_ext_adc_start( void );
bool drv_ext_adc_stop(void);
void drv_ext_adc_offset_task(void);
void drv_ext_adc_zero_task(void);
void drv_ext_adc_offset(void);
void drv_ext_adc_zero(void);
uint16_t calculate_digipot_setting(double);
bool drv_ext_adc_sample(void* buffer, uint16_t samples );
bool drv_ext_adc_sample_start( void* buffer, uint16_t samples );
void* drv_ext_adc_get_buffer(void);
bool drv_ext_adc_get_value( uint16_t* value );
uint16_t drv_ext_adc_get_offset( DRV_EXT_ADC_INDEX channel );
uint16_t drv_ext_adc_get_zero( DRV_EXT_ZERO_OFFSET_INDEX index );
bool drv_ext_adc_busy(void);
bool drv_ext_adc_zero_busy(void);

double calculate_amplifier_gain(uint16_t digipot_setting);
/*******************************************************************************/

#endif
