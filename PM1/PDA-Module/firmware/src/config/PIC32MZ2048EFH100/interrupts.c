/*******************************************************************************
 System Interrupts File

  Company:
    Microchip Technology Inc.

  File Name:
    interrupt.c

  Summary:
    Interrupt vectors mapping

  Description:
    This file maps all the interrupt vectors to their corresponding
    implementations. If a particular module interrupt is used, then its ISR
    definition can be found in corresponding PLIB source file. If a module
    interrupt is not used, then its ISR implementation is mapped to dummy
    handler.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "configuration.h"
#include "definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************


void CORE_TIMER_InterruptHandler( void );
void TIMER_1_InterruptHandler( void );
void TIMER_2_InterruptHandler( void );
void TIMER_3_InterruptHandler( void );
void UART1_TX_InterruptHandler( void );
void UART1_RX_InterruptHandler( void );
void CHANGE_NOTICE_B_InterruptHandler( void );
void COMPARATOR_1_InterruptHandler( void );
void DRV_USBHS_InterruptHandler( void );
void DRV_USBHS_DMAInterruptHandler( void );
void DMA0_InterruptHandler( void );
void DMA1_InterruptHandler( void );
void DMA2_InterruptHandler( void );
void UART2_FAULT_InterruptHandler( void );
void UART2_RX_InterruptHandler( void );
void UART2_TX_InterruptHandler( void );
void UART3_FAULT_InterruptHandler( void );
void UART3_RX_InterruptHandler( void );
void UART3_TX_InterruptHandler( void );



/* All the handlers are defined here.  Each will call its PLIB-specific function. */
void __ISR(_CORE_TIMER_VECTOR, ipl1AUTO) CORE_TIMER_Handler (void)
{
    CORE_TIMER_InterruptHandler();
}

void __ISR(_EXTERNAL_0_VECTOR, ipl5AUTO) EXTERNAL_0_Handler (void)
{
}

void __ISR(_TIMER_1_VECTOR, ipl1AUTO) TIMER_1_Handler (void)
{
    TIMER_1_InterruptHandler();
}

void __ISR(_TIMER_2_VECTOR, ipl1AUTO) TIMER_2_Handler (void)
{
    TIMER_2_InterruptHandler();
}

void __ISR(_TIMER_3_VECTOR, ipl1AUTO) TIMER_3_Handler (void)
{
    TIMER_3_InterruptHandler();
}

void __ISR(_UART1_TX_VECTOR, ipl1AUTO) UART1_TX_Handler (void)
{
    UART1_TX_InterruptHandler();
}

void __ISR(_UART1_RX_VECTOR, ipl1AUTO) UART1_RX_Handler (void)
{
    UART1_RX_InterruptHandler();
}

void __ISR(_CHANGE_NOTICE_B_VECTOR, ipl3AUTO) CHANGE_NOTICE_B_Handler (void)
{
    CHANGE_NOTICE_B_InterruptHandler();
}

void __ISR(_COMPARATOR_1_VECTOR, ipl3AUTO) COMPARATOR_1_Handler (void)
{
    COMPARATOR_1_InterruptHandler();
}

void __ISR(_USB_VECTOR, ipl4AUTO) USB_Handler (void)
{
    DRV_USBHS_InterruptHandler();
}

void __ISR(_USB_DMA_VECTOR, ipl4AUTO) USB_DMA_Handler (void)
{
    DRV_USBHS_DMAInterruptHandler();
}

void __ISR(_DMA0_VECTOR, ipl5AUTO) DMA0_Handler (void)
{
    DMA0_InterruptHandler();
}

void __ISR(_DMA1_VECTOR, ipl5AUTO) DMA1_Handler (void)
{
    DMA1_InterruptHandler();
}

void __ISR(_DMA2_VECTOR, ipl5AUTO) DMA2_Handler (void)
{
    DMA2_InterruptHandler();
}

void __ISR(_UART2_FAULT_VECTOR, ipl1AUTO) UART2_FAULT_Handler (void)
{
    UART2_FAULT_InterruptHandler();
}

void __ISR(_UART2_RX_VECTOR, ipl1AUTO) UART2_RX_Handler (void)
{
    UART2_RX_InterruptHandler();
}

void __ISR(_UART2_TX_VECTOR, ipl1AUTO) UART2_TX_Handler (void)
{
    UART2_TX_InterruptHandler();
}

void __ISR(_UART3_FAULT_VECTOR, ipl1AUTO) UART3_FAULT_Handler (void)
{
    UART3_FAULT_InterruptHandler();
}

void __ISR(_UART3_RX_VECTOR, ipl2AUTO) UART3_RX_Handler (void)
{
    UART3_RX_InterruptHandler();
}

void __ISR(_UART3_TX_VECTOR, ipl1AUTO) UART3_TX_Handler (void)
{
    UART3_TX_InterruptHandler();
}





/*******************************************************************************
 End of File
*/
