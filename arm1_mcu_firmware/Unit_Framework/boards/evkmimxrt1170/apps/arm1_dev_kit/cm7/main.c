/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "debug.h"
#include "pin_mux.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Private (file scope only) variables
 ******************************************************************************/

char const gp_tip_message[] =
    "LPUART functional API interrupt example\r\n"
    "Board receives characters then sends them out\r\n"
    "Now please input:\r\n";

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
   
/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    
    DEBUG_initialise();

    DEBUG_printf("Hello World!\r\n");
    DEBUG_printf("%sHello World in colour!\r\n%s", DEBUG_RED, DEBUG_WHITE);
    DEBUG_printf("Format test: %s%d%s\r\n", DEBUG_BLUE, 123, DEBUG_WHITE);
    
    DEBUG_printf(gp_tip_message);
    
    while (1)
    {
        DEBUG_rx_handler();
    }
}
