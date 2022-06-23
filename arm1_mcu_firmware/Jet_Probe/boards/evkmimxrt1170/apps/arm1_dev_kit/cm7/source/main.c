/*****************************************************************************/
/**
 * @file 
 *   main.c
 * @brief 
 *   Top-level code entry and initialisation
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "debug.h"
#include "pin_mux.h"
#include "board.h"
#include "semc.h"
#include "video.h"
#include "qdc.h"
#include "dma.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

char const gp_tip_message[] =
    "LPUART functional API interrupt example\r\n"
    "Board receives characters then sends them out\r\n"
    "Now please input:\r\n";

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/**
 * @brief
 *   System tick interrupt handler
 */
void SysTick_Handler(void)
{
}

/**
 * @brief
 *   Configure the system tick at 1ms for one interrupt
 */
void configure_systick(void)
{
    uint32_t coreclk = CLOCK_GetFreq(kCLOCK_CoreSysClk);

    SysTick_Config(coreclk / 1000);
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Code entry / main function
 * @return
 *   Never returns
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_BootClockRUN();
    VIDEO_reset();
    BOARD_InitPins();
    BOARD_InitMipiPanelPins();
    BOARD_InitMipiCameraPins();    
    BOARD_InitDebugConsole();
    
    configure_systick();
    
    DEBUG_initialise();

#ifdef USE_SDRAM
    /* 
     * SEMC has already been configured during boot-up process
     * @todo Need to understand where this happens so that the parameters can
     *       be tweaked, particularly the size of the SDRAM
     */
#else
    BOARD_InitSEMCPins();
    
    if (kStatus_Success != SEMC_initialise())
    {
        DEBUG_printf("SEMC SDRAM Init Failed\r\n");
    }
#endif
    
    if (kStatus_Success != SEMC_self_test())
    {
        DEBUG_printf("SEMC SDRAM Self Test Failed\r\n");
    }
    
    if (kStatus_Success != DMA_initialise())
    {
        DEBUG_printf("DMA Init Failed\r\n");
    }
    else if (kStatus_Success != DMA_test())
    {
        DEBUG_printf("DMA Test Failed\r\n");
    }
      
    VIDEO_initialise();
    QDC_initialise();

    DEBUG_printf("Hello World!\r\n");
    DEBUG_printf("%sHello World in colour!\r\n%s", DEBUG_RED, DEBUG_WHITE);
    DEBUG_printf("Format test: %s%d%s\r\n", DEBUG_BLUE, 123, DEBUG_WHITE);
    
    DEBUG_printf(gp_tip_message);
    
    VIDEO_compliance_test();
    
    while (1)
    {
        DEBUG_rx_handler();
        VIDEO_frame_handler();
    }
}
