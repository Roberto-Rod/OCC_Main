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

#define DEBUG_LPUART                    ((LPUART_Type*)BOARD_DEBUG_UART_BASEADDR)
#define DEBUG_LPUART_CLK_FREQ           (BOARD_DebugConsoleSrcFreq())
#define DEBUG_LPUART_IRQn               (BOARD_UART_IRQ)
#define DEBUG_LPUART_IRQHandler         (BOARD_UART_IRQ_HANDLER)

#define DEBUG_QUEUE_SIZE                (16u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static TX_QUEUE debug_queue;
static TX_MUTEX printf_mutex;

static ULONG queue_pool[DEBUG_QUEUE_SIZE];

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
    /* If new data arrived. */
    if ((kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(DEBUG_LPUART))
    {
        ULONG data = (ULONG) LPUART_ReadByte(DEBUG_LPUART);

        UINT tx_status = tx_queue_send(&debug_queue, &data, TX_NO_WAIT);
        
        if (TX_SUCCESS != tx_status) 
        {
            /// @todo Handle error
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
 * @param
 *   input Unused
 */
void DEBUG_thread(ULONG input)
{
    TX_THREAD_NOT_USED(input);
    
    /* Create the printf mutex */
    (void)tx_mutex_create(&printf_mutex, "printf mutex", TX_NO_INHERIT);

    /* Create the debug queue */
    UINT tx_status = tx_queue_create(
        &debug_queue, 
        "debug queue", 
        TX_1_ULONG, 
        (VOID *)queue_pool, 
        DEBUG_QUEUE_SIZE * sizeof(ULONG));

    if (TX_SUCCESS != tx_status) 
    {
        return;
    }
    
    while (TX_LOOP_FOREVER)
    {
        ULONG data;
      
        tx_status = tx_queue_receive(&debug_queue, &data, TX_WAIT_FOREVER);
      
        if (TX_SUCCESS == tx_status) 
        {
            /* Attempt to process as part of a command */
            if (false == CMD_data_handler((uint8_t)data))
            {
                /* Lock other threads out of printf */
                UINT tx_status = tx_mutex_get(&printf_mutex, TX_WAIT_FOREVER);

                if (TX_SUCCESS == tx_status)
                {
                    uint32_t status;
              
                    /* Send data only when LPUART TX register is empty */
                    do
                    {
                        status = LPUART_GetStatusFlags(DEBUG_LPUART);
                    } while (0 == (status & kLPUART_TxDataRegEmptyFlag));
              
                    /* If not part of command, just echo the character back */
                    LPUART_WriteByte(DEBUG_LPUART, data);
                    
                    (void)tx_mutex_put(&printf_mutex);
                }
            }
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
    /* Only allow one thread at a time to use this resource */
    UINT tx_status = tx_mutex_get(&printf_mutex, TX_WAIT_FOREVER);
    
    if (TX_SUCCESS == tx_status)
    {
        PUTCHAR(character);
        (void)tx_mutex_put(&printf_mutex);
    }
}

/**
 * @brief
 *   Get a single character from the debug console
 * @return
 *   The character received
 */
int DEBUG_getchar(void)
{
    int result;
    
    /* Only allow one thread at a time to use this resource */
    UINT tx_status = tx_mutex_get(&printf_mutex, TX_WAIT_FOREVER);
    
    if (TX_SUCCESS == tx_status)
    {
        result = GETCHAR();
        (void)tx_mutex_put(&printf_mutex);
    }
  
    return result;
}

/**
 * @brief
 *   Writes formatted output to the standard output stream (thread safe)
 * @param   
 *   fmt_s Format control string
 * @param   
 *   Format arguments
 * @return
 *   Number of characters printed or a negative value if an error occurs
 */
int DEBUG_printf(const char *p_format, ...)
{
    va_list list;
    int result = 0;

    va_start(list, p_format);
    
    /* Only allow one thread at a time to use printf */
    UINT tx_status = tx_mutex_get(&printf_mutex, TX_WAIT_FOREVER);
    
    /* TX_MUTEX_ERROR means that this call was made before RTOS started */
    if ((TX_SUCCESS == tx_status) || (TX_MUTEX_ERROR == tx_status))
    {
        /* Mutex taken, or not needed */
        result = DbgConsole_Vprintf(p_format, list);
    }
    
    if (TX_SUCCESS == tx_status)
    {
        /* Return the mutex to unlock printf in other threads */
        (void)tx_mutex_put(&printf_mutex);
    }

    va_end(list);

    return result;
}


/*** end of file ***/
