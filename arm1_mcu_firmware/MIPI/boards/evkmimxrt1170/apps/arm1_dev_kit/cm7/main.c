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
#include "video.h"
#include "qdc.h"

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
    
    DEBUG_initialise();
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
