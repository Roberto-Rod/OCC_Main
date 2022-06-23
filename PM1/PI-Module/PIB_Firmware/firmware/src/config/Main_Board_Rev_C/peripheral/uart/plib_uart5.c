/*******************************************************************************
  UART5 PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_uart5.c

  Summary:
    UART5 PLIB Implementation File

  Description:
    None

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "device.h"
#include "plib_uart5.h"

// *****************************************************************************
// *****************************************************************************
// Section: UART5 Implementation
// *****************************************************************************
// *****************************************************************************

UART_OBJECT uart5Obj;

void static UART5_ErrorClear( void )
{
    /* rxBufferLen = (FIFO level + RX register) */
    uint8_t rxBufferLen = UART_RXFIFO_DEPTH;
    uint8_t dummyData = 0u;

    /* If it's a overrun error then clear it to flush FIFO */
    if(U5STA & _U5STA_OERR_MASK)
    {
        U5STACLR = _U5STA_OERR_MASK;
    }

    /* Read existing error bytes from FIFO to clear parity and framing error flags */
    while(U5STA & (_U5STA_FERR_MASK | _U5STA_PERR_MASK))
    {
        dummyData = (uint8_t )(U5RXREG );
        rxBufferLen--;

        /* Try to flush error bytes for one full FIFO and exit instead of
         * blocking here if more error bytes are received */
        if(rxBufferLen == 0u)
        {
            break;
        }
    }

    // Ignore the warning
    (void)dummyData;

    /* Clear error interrupt flag */
    IFS5CLR = _IFS5_U5EIF_MASK;

    /* Clear up the receive interrupt flag so that RX interrupt is not
     * triggered for error bytes */
    IFS5CLR = _IFS5_U5RXIF_MASK;

    return;
}

void UART5_Initialize( void )
{
    /* Set up UxMODE bits */
    /* STSEL  = 0*/
    /* PDSEL = 0 */
    /* BRGH = 0 */
    /* RXINV = 0 */
    /* ABAUD = 0 */
    /* LPBACK = 0 */
    /* WAKE = 0 */
    /* SIDL = 0 */
    /* RUNOVF = 0 */
    /* CLKSEL = 0 */
    /* SLPEN = 0 */
    U5MODE = 0x0;

    /* Enable UART5 Receiver, Transmitter and TX Interrupt selection */
    U5STASET = (_U5STA_UTXEN_MASK | _U5STA_URXEN_MASK | _U5STA_UTXISEL0_MASK);

    /* BAUD Rate register Setup */
    U5BRG = 53;

    /* Disable Interrupts */
    IEC5CLR = _IEC5_U5EIE_MASK;

    IEC5CLR = _IEC5_U5RXIE_MASK;

    IEC5CLR = _IEC5_U5TXIE_MASK;

    /* Initialize instance object */
    uart5Obj.rxBuffer = NULL;
    uart5Obj.rxSize = 0;
    uart5Obj.rxProcessedSize = 0;
    uart5Obj.rxBusyStatus = false;
    uart5Obj.rxCallback = NULL;
    uart5Obj.txBuffer = NULL;
    uart5Obj.txSize = 0;
    uart5Obj.txProcessedSize = 0;
    uart5Obj.txBusyStatus = false;
    uart5Obj.txCallback = NULL;

    /* Turn ON UART5 */
    U5MODESET = _U5MODE_ON_MASK;
}

bool UART5_SerialSetup( UART_SERIAL_SETUP *setup, uint32_t srcClkFreq )
{
    bool status = false;
    uint32_t baud = setup->baudRate;
    uint32_t brgValHigh = 0;
    uint32_t brgValLow = 0;
    uint32_t brgVal = 0;
    uint32_t uartMode;

    if((uart5Obj.rxBusyStatus == true) || (uart5Obj.txBusyStatus == true))
    {
        /* Transaction is in progress, so return without updating settings */
        return status;
    }

    if (setup != NULL)
    {
        /* Turn OFF UART5 */
        U5MODECLR = _U5MODE_ON_MASK;

        if(srcClkFreq == 0)
        {
            srcClkFreq = UART5_FrequencyGet();
        }

        /* Calculate BRG value */
        brgValLow = ((srcClkFreq / baud) >> 4) - 1;
        brgValHigh = ((srcClkFreq / baud) >> 2) - 1;

        /* Check if the baud value can be set with low baud settings */
        if((brgValHigh >= 0) && (brgValHigh <= UINT16_MAX))
        {
            brgVal =  (((srcClkFreq >> 2) + (baud >> 1)) / baud ) - 1;
            U5MODESET = _U5MODE_BRGH_MASK;
        }
        else if ((brgValLow >= 0) && (brgValLow <= UINT16_MAX))
        {
            brgVal = ( ((srcClkFreq >> 4) + (baud >> 1)) / baud ) - 1;
            U5MODECLR = _U5MODE_BRGH_MASK;
        }
        else
        {
            return status;
        }

        if(setup->dataWidth == UART_DATA_9_BIT)
        {
            if(setup->parity != UART_PARITY_NONE)
            {
               return status;
            }
            else
            {
               /* Configure UART5 mode */
               uartMode = U5MODE;
               uartMode &= ~_U5MODE_PDSEL_MASK;
               U5MODE = uartMode | setup->dataWidth;
            }
        }
        else
        {
            /* Configure UART5 mode */
            uartMode = U5MODE;
            uartMode &= ~_U5MODE_PDSEL_MASK;
            U5MODE = uartMode | setup->parity ;
        }

        /* Configure UART5 mode */
        uartMode = U5MODE;
        uartMode &= ~_U5MODE_STSEL_MASK;
        U5MODE = uartMode | setup->stopBits ;

        /* Configure UART5 Baud Rate */
        U5BRG = brgVal;

        U5MODESET = _U5MODE_ON_MASK;

        status = true;
    }

    return status;
}

bool UART5_Read(void* buffer, const size_t size )
{
    bool status = false;
    uint8_t* lBuffer = (uint8_t* )buffer;

    if(lBuffer != NULL)
    {
        /* Check if receive request is in progress */
        if(uart5Obj.rxBusyStatus == false)
        {
            /* Clear errors before submitting the request.
             * ErrorGet clears errors internally. */
            UART5_ErrorGet();

            uart5Obj.rxBuffer = lBuffer;
            uart5Obj.rxSize = size;
            uart5Obj.rxProcessedSize = 0;
            uart5Obj.rxBusyStatus = true;
            status = true;

            /* Enable UART5_FAULT Interrupt */
            IEC5SET = _IEC5_U5EIE_MASK;

            /* Enable UART5_RX Interrupt */
            IEC5SET = _IEC5_U5RXIE_MASK;
        }
    }

    return status;
}

bool UART5_Write( void* buffer, const size_t size )
{
    bool status = false;
    uint8_t* lBuffer = (uint8_t*)buffer;

    if(lBuffer != NULL)
    {
        /* Check if transmit request is in progress */
        if(uart5Obj.txBusyStatus == false)
        {
            uart5Obj.txBuffer = lBuffer;
            uart5Obj.txSize = size;
            uart5Obj.txProcessedSize = 0;
            uart5Obj.txBusyStatus = true;
            status = true;

            /* Initiate the transfer by sending first byte */
            if(!(U5STA & _U5STA_UTXBF_MASK))
            {
                U5TXREG = *lBuffer;
                uart5Obj.txProcessedSize++;
            }

            IEC5SET = _IEC5_U5TXIE_MASK;
        }
    }

    return status;
}

UART_ERROR UART5_ErrorGet( void )
{
    UART_ERROR errors = UART_ERROR_NONE;
    uint32_t status = U5STA;

    errors = (UART_ERROR)(status & (_U5STA_OERR_MASK | _U5STA_FERR_MASK | _U5STA_PERR_MASK));

    if(errors != UART_ERROR_NONE)
    {
        UART5_ErrorClear();
    }

    /* All errors are cleared, but send the previous error state */
    return errors;
}

bool UART5_AutoBaudQuery( void )
{
    if(U5MODE & _U5MODE_ABAUD_MASK)
        return true;
    else
        return false;
}

void UART5_AutoBaudSet( bool enable )
{
    if( enable == true )
    {
        U5MODESET = _U5MODE_ABAUD_MASK;
    }

    /* Turning off ABAUD if it was on can lead to unpredictable behavior, so that
       direction of control is not allowed in this function.                      */
}

void UART5_ReadCallbackRegister( UART_CALLBACK callback, uintptr_t context )
{
    uart5Obj.rxCallback = callback;

    uart5Obj.rxContext = context;
}

bool UART5_ReadIsBusy( void )
{
    return uart5Obj.rxBusyStatus;
}

size_t UART5_ReadCountGet( void )
{
    return uart5Obj.rxProcessedSize;
}

void UART5_WriteCallbackRegister( UART_CALLBACK callback, uintptr_t context )
{
    uart5Obj.txCallback = callback;

    uart5Obj.txContext = context;
}

bool UART5_WriteIsBusy( void )
{
    return uart5Obj.txBusyStatus;
}

size_t UART5_WriteCountGet( void )
{
    return uart5Obj.txProcessedSize;
}
