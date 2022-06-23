/*****************************************************************************/
/**
 * @file 
 *   dma.c
 * @brief 
 *   API for handling Direct Memory Access transfers
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

#include "dma.h"
#include "debug.h"
#include "fsl_edma.h"
#include "fsl_dmamux.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define TEST_BUFF_LEN           (4096u)

#define TEST_PATTERN            (0x1234FFFFu)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static edma_handle_t g_EDMA_Handle;
static volatile bool g_Transfer_Done = false;
static volatile uint32_t g_SysTick = 0;

AT_NONCACHEABLE_SECTION_INIT(uint32_t src_buffer[TEST_BUFF_LEN]) = { 0 };
AT_NONCACHEABLE_SECTION_INIT(uint32_t dst_buffer[TEST_BUFF_LEN]) = { 0 };

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/**
 * @brief
 *   User callback function for EDMA transfer
 * @param
 *   ph_handle EDMA handle
 * @param
 *   p_param Pointer to parameters
 * @param
 *   b_tx_done Transfer completed flag
 * @param
 *   tcds How many tcds are finished between last callback and this
 */
void EDMA_Callback(
    edma_handle_t *ph_handle, void *p_param, bool b_tx_done, uint32_t tcds)
{
    if (b_tx_done)
    {
        g_Transfer_Done = true;
        g_SysTick = SysTick->VAL;
    }
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise DMA transfers
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t DMA_initialise(void)
{
    edma_config_t config;
    edma_transfer_config_t transfer_config;
    
    /* Configure DMAMUX */
    DMAMUX_Init(DMAMUX0);
#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON
    DMAMUX_EnableAlwaysOn(DMAMUX0, 0, true);
#else
    #error Not supported DMA feature
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON */
    DMAMUX_EnableChannel(DMAMUX0, 0);
    
    /* Configure EDMA one shot transfer */
    /*
     * config.enableRoundRobinArbitration = false;
     * config.enableHaltOnError = true;
     * config.enableContinuousLinkMode = false;
     * config.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(DMA0, &config);
    EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0);
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
    
    EDMA_PrepareTransfer(
        &transfer_config, 
        src_buffer, 
        sizeof(src_buffer[0]), 
        dst_buffer, 
        sizeof(dst_buffer[0]),
        sizeof(src_buffer[0]), 
        sizeof(src_buffer[0]) * TEST_BUFF_LEN, 
        kEDMA_MemoryToMemory);
    
    return EDMA_SubmitTransfer(&g_EDMA_Handle, &transfer_config);
}

/**
 * @brief
 *   Initialise DMA transfers
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t DMA_test(void)
{
    uint32_t t1;
    uint32_t t2;
    uint32_t time;

    for (uint32_t i = 0; i < TEST_BUFF_LEN; i ++)
    {
        src_buffer[i] = TEST_PATTERN - i;
    }
    
    EDMA_StartTransfer(&g_EDMA_Handle);
    t1 = SysTick->VAL;
    
    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done != true);
    t2 = g_SysTick;
    
    time = 
        (((uint64_t)(t2 - t1) * 1000000000u) / 
        CLOCK_GetFreq(kCLOCK_CoreSysClk));
    DEBUG_printf(
        "DMA time taken per 32-bit word transfer: %dns\r\n", 
        time/TEST_BUFF_LEN);

    for (uint32_t i = 0; i < TEST_BUFF_LEN; i ++)
    {
        if ((TEST_PATTERN - i) != dst_buffer[i])
        {
             return kStatus_Fail;
        }
    }
    
    return kStatus_Success;
}


/*** end of file ***/
