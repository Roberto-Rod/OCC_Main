/*****************************************************************************/
/**
 * @file 
 *   debug.c
 * @brief 
 *   Functions for logging to a console via UART
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
#include <stdio.h>

#include "debug.h"
#include "cmd.h"
#include "board.h"
#include "fsl_lpuart.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define MINIMUM_TOKEN_LENGTH            (5u)
#define MAXIMUM_TOKEN_LENGTH            (10u)

#define MAXIMUM_BUFFER_LENGTH           (256u)
#define RING_BUFFER_SIZE                (16u)

#define DEBUG_LPUART                    ((LPUART_Type*)BOARD_DEBUG_UART_BASEADDR)
#define DEBUG_LPUART_CLK_FREQ           (BOARD_DebugConsoleSrcFreq())
#define DEBUG_LPUART_IRQn               (BOARD_UART_IRQ)
#define DEBUG_LPUART_IRQHandler         (BOARD_UART_IRQ_HANDLER)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*
  Ring buffer for data input and output, in this example, input data are saved
  to ring buffer in IRQ handler. The main function polls the ring buffer status,
  if there are new data, then send them out.
  Ring buffer full: (((g_rx_index + 1) % RING_BUFFER_SIZE) == g_tx_index)
  Ring buffer empty: (g_rx_index == g_tx_index)
*/
uint8_t gp_ring_buffer[RING_BUFFER_SIZE];
volatile uint16_t g_tx_index; // Index of the data to send out
volatile uint16_t g_rx_index; // Index of the memory to save new arrived data

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/**
 * @brief
 *   Interrupt Request handler for characters received on the debug UART
 */
void DEBUG_LPUART_IRQHandler(void)
{
    uint8_t data;
    uint16_t tmp_rx_index = g_rx_index;
    uint16_t tmp_tx_index = g_tx_index;

    /* If new data arrived. */
    if ((kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(DEBUG_LPUART))
    {
        data = LPUART_ReadByte(DEBUG_LPUART);

        /* If ring buffer is not full, add data to ring buffer. */
        if (((tmp_rx_index + 1) % RING_BUFFER_SIZE) != tmp_tx_index)
        {
            gp_ring_buffer[g_rx_index] = data;
            g_rx_index++;
            g_rx_index %= RING_BUFFER_SIZE;
        }
    }

    SDK_ISR_EXIT_BARRIER;
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the debug UART and interrupts
 */
void DEBUG_initialise(void)
{
    BOARD_InitDebugConsole();

    /* Enable RX interrupt. */
    LPUART_EnableInterrupts(DEBUG_LPUART, kLPUART_RxDataRegFullInterruptEnable);
    EnableIRQ(DEBUG_LPUART_IRQn);
}

/**
 * @brief
 *   Handler for characters received from the console, via ring buffer
 */
void DEBUG_rx_handler(void)
{
    /* Send data only when LPUART TX register is empty and ring buffer has data to send out. */
    while (kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(DEBUG_LPUART))
    {
        if (g_rx_index != g_tx_index)
        {
            const uint8_t data = gp_ring_buffer[g_tx_index];
            
            /* Attempt to process as part of a command */
            if (false == CMD_data_handler(data))
            {
                /* If not part of command, just echo the character back */
                LPUART_WriteByte(DEBUG_LPUART, data);
            }
            
            g_tx_index++;
            g_tx_index %= RING_BUFFER_SIZE;
        }
    }
}

/**
 * @brief
 *   Put a single character to the debug console
 * @param
 *   character The character to be sent
 */
void DEBUG_putchar(char character)
{
    PUTCHAR(character);
}

/**
 * @brief
 *   Get a single character from the debug console
 * @return
 *   The character received
 */
char DEBUG_getchar(void)
{
    return GETCHAR();
}


/*** end of file ***/
