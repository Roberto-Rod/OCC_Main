/*****************************************************************************/
/**
 * @file 
 *   fpga.c
 * @brief 
 *   API layer for interfacing with the FPGA, including FlexIO and EDMA
 * @todo
 *   Put scan complete pin onto an interrupt (outside FlexIO) and use this to 
 *   toggle between the two scan buffers
 *   Evaluate the scan size - it's just an arbitrary number for now, which is 
 *   hopefully in the right ballpark
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "fpga.h"
#include "fsl_flexio.h"
#include "fsl_dmamux.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define FPGA_FLEXIO_INST        (FLEXIO2)
#define FPGA_TIMER_INST         (0)
#define FPGA_PIN_START_INDEX    (8u)
#define FPGA_DATA_WIDTH         (16u)
#define FPGA_PIN_CLK_INDEX      (7u)
#define FPGA_PIN_REF_INDEX      (3u)

#define FPGA_BUFFER_COUNT       (2u)
#define FPGA_DMA_CHANNEL        (1u)
#define FPGA_SCAN_WORDS         (280000u)
#define FPGA_SCAN_BYTES         (FPGA_SCAN_WORDS / sizeof(uint16_t))
#define FPGA_BUFFER_ALIGN       (64u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static uint8_t g_scan_buffer_index = 0;

#ifdef USE_SDRAM

AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t gp_scan_buffer[FPGA_BUFFER_COUNT][FPGA_SCAN_WORDS],
    FPGA_BUFFER_ALIGN
);

#else

#pragma default_variable_attributes = @ "IMAGES"
static uint16_t gp_scan_buffer[FPGA_BUFFER_COUNT][FPGA_SCAN_WORDS];
#pragma default_variable_attributes =

#endif

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static void configure_flexio(void);
static void configure_dma(void);

/**
 * @brief
 *   Configure the FlexIO interface for receiving 16-bit parallel data
 */
static void configure_flexio(void)
{
    flexio_shifter_config_t cfg_shifter = {
        .timerSelect   = FPGA_TIMER_INST,
        .timerPolarity = kFLEXIO_ShifterTimerPolarityOnNegitive,
        .pinConfig     = kFLEXIO_PinConfigOutputDisabled,
        .pinSelect     = FPGA_PIN_START_INDEX,
        .pinPolarity   = kFLEXIO_PinActiveHigh,
        .shifterMode   = kFLEXIO_ShifterModeReceive,
        .parallelWidth = FPGA_DATA_WIDTH - 1u,
        .inputSource   = kFLEXIO_ShifterInputFromNextShifterOutput,
        .shifterStop   = kFLEXIO_ShifterStopBitDisable,
        .shifterStart  = kFLEXIO_ShifterStartBitDisabledLoadDataOnEnable
    };
    
    flexio_timer_config_t cfg_timer = {
        .triggerSelect   = FLEXIO_TIMER_TRIGGER_SEL_PININPUT(FPGA_PIN_REF_INDEX),
        .triggerPolarity = kFLEXIO_TimerTriggerPolarityActiveHigh,
        .triggerSource   = kFLEXIO_TimerTriggerSourceInternal,
        .pinConfig       = kFLEXIO_PinConfigOutputDisabled,
        .pinSelect       = FPGA_PIN_CLK_INDEX,
        .pinPolarity     = kFLEXIO_PinActiveHigh,
        .timerMode       = kFLEXIO_TimerModeDual8BitBaudBit,
        .timerOutput     = kFLEXIO_TimerOutputOneNotAffectedByReset,
        .timerDecrement  = kFLEXIO_TimerDecSrcOnPinInputShiftPinInput,
        .timerReset      = kFLEXIO_TimerResetOnTimerTriggerRisingEdge,
        .timerDisable    = kFLEXIO_TimerDisableOnTimerCompare,
        .timerEnable     = kFLEXIO_TimerEnableOnTriggerHigh,
        .timerStop       = kFLEXIO_TimerStopBitDisabled,
        .timerStart      = kFLEXIO_TimerStartBitDisabled,
        .timerCompare    = (((FPGA_DATA_WIDTH * 2u) - 1u) << 8u) | 1u
    };

    FLEXIO_Reset(FPGA_FLEXIO_INST);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate flexio clock */
    CLOCK_EnableClock(s_flexioClocks[FLEXIO_GetInstance(FPGA_FLEXIO_INST)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    
    volatile uint32_t flexio_ctrl = FPGA_FLEXIO_INST->CTRL;

    /** @todo 
     *   Investigate whether we need to enable any of the following features
     */  
    flexio_ctrl &= ~(
        FLEXIO_CTRL_DOZEN_MASK |
        FLEXIO_CTRL_DBGE_MASK |
        FLEXIO_CTRL_FASTACC_MASK |
        FLEXIO_CTRL_FLEXEN_MASK);
    flexio_ctrl |= (
        FLEXIO_CTRL_DOZEN(false) |
#ifdef DEBUG
        FLEXIO_CTRL_DBGE(true) |
#else
        FLEXIO_CTRL_DBGE(false) |
#endif
        FLEXIO_CTRL_FASTACC(false) |
        FLEXIO_CTRL_FLEXEN(false));
    FPGA_FLEXIO_INST->CTRL = flexio_ctrl;

    /* Configure the shifters as a FIFO buffer */
    for (uint8_t idx = 0; idx < FLEXIO_SHIFTBUF_COUNT; idx++)
    {
        if ((FLEXIO_SHIFTBUF_COUNT - 1u) == idx)
        {
            cfg_shifter.inputSource = kFLEXIO_ShifterInputFromPin;
        }
      
        FLEXIO_SetShifterConfig(FPGA_FLEXIO_INST, idx, &cfg_shifter);
    }

    FLEXIO_SetTimerConfig(FPGA_FLEXIO_INST, FPGA_TIMER_INST, &cfg_timer);
    
    /* Clear flags */
    FLEXIO_ClearShifterErrorFlags(
        FPGA_FLEXIO_INST, 
        ((1ul << FLEXIO_SHIFTBUF_COUNT) - 1u));
    FLEXIO_ClearTimerStatusFlags(
        FPGA_FLEXIO_INST, 
        1ul << FPGA_TIMER_INST);
    
    /* Enable data */
    FPGA_FLEXIO_INST->CTRL |= FLEXIO_CTRL_FLEXEN_MASK;
}

/**
 * @brief
 *   Configure the DMA channel for moving the data to memory
 * @todo
 *   Work out where this lives (possibly in DMA module for consistency?)
 */
static void configure_dma(void)
{
    /* Configure DMA TCD */
    DMA0->TCD[FPGA_DMA_CHANNEL].SADDR = FLEXIO_GetShifterBufferAddress(
        FPGA_FLEXIO_INST, kFLEXIO_ShifterBuffer, 0u);
    DMA0->TCD[FPGA_DMA_CHANNEL].SOFF = 0u;
    DMA0->TCD[FPGA_DMA_CHANNEL].ATTR = DMA_ATTR_SMOD(0u) |
                                            DMA_ATTR_SSIZE(5u) |
                                            DMA_ATTR_DMOD(0u) |
                                            DMA_ATTR_DSIZE(5u);
    DMA0->TCD[FPGA_DMA_CHANNEL].NBYTES_MLNO = 32u;
    DMA0->TCD[FPGA_DMA_CHANNEL].SLAST = 0u;
    DMA0->TCD[FPGA_DMA_CHANNEL].DADDR = (uint32_t)(gp_scan_buffer[0]);
    DMA0->TCD[FPGA_DMA_CHANNEL].DOFF = 32u;
    DMA0->TCD[FPGA_DMA_CHANNEL].CITER_ELINKNO = (FPGA_SCAN_BYTES / 32u);
    DMA0->TCD[FPGA_DMA_CHANNEL].DLAST_SGA = 0;
    DMA0->TCD[FPGA_DMA_CHANNEL].CSR = 0u;
    DMA0->TCD[FPGA_DMA_CHANNEL].CSR |= DMA_CSR_DREQ_MASK;
    DMA0->TCD[FPGA_DMA_CHANNEL].BITER_ELINKNO = (FPGA_SCAN_BYTES / 32u);

    /* Configure DMA MUX Source */
    DMAMUX0->CHCFG[FPGA_DMA_CHANNEL] = 
        DMAMUX0->CHCFG[FPGA_DMA_CHANNEL] &
        (~DMAMUX_CHCFG_SOURCE_MASK) | 
        DMAMUX_CHCFG_SOURCE(kDmaRequestMuxFlexIO2Request0Request1 & 0xFF);
    
    /* Enable DMA channel */
    DMAMUX0->CHCFG[FPGA_DMA_CHANNEL] |= DMAMUX_CHCFG_ENBL_MASK;
    
    /* Send enable request */
    DMA0->SERQ = DMA_SERQ_SERQ(FPGA_DMA_CHANNEL);

    /* Enable DMA from shifter 0 (FIFO full) */
    FLEXIO_EnableShifterStatusDMA(FPGA_FLEXIO_INST, 1ul, true);
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the interface with the FPGA
 */
void FPGA_initialise(void)
{
    memset(gp_scan_buffer, 0, sizeof(gp_scan_buffer));
  
    configure_flexio();
    configure_dma();
}


/*** end of file ***/
