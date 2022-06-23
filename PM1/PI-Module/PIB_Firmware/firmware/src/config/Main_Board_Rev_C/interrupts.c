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
#include "gfx/hal/inc/gfx_hal.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************


void CORE_TIMER_InterruptHandler( void );
void TIMER_4_InterruptHandler( void );
void TIMER_9_InterruptHandler( void );
void CHANGE_NOTICE_B_InterruptHandler( void );
void CHANGE_NOTICE_H_InterruptHandler( void );
void DMA0_InterruptHandler( void );
void DMA1_InterruptHandler( void );
void UART3_FAULT_InterruptHandler( void );
void UART3_RX_InterruptHandler( void );
void UART3_TX_InterruptHandler( void );
void UART5_FAULT_InterruptHandler( void );
void UART5_RX_InterruptHandler( void );
void UART5_TX_InterruptHandler( void );
void UART6_FAULT_InterruptHandler( void );
void UART6_TX_InterruptHandler( void );
void GLCD_Interrupt_Handler( void );
//****************************************************************************//
uint8_t interrupt_source;                       // temp
extern volatile SLEEP_WAKE_CAUSE sleep_wake_cause;

/* All the handlers are defined here.  Each will call its PLIB-specific function. */
//****************************************************************************//
void __ISR(_CORE_TIMER_VECTOR, ipl1AUTO) CORE_TIMER_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 1;
    }    

    CORE_TIMER_InterruptHandler();
}
//****************************************************************************//
void __ISR(_EXTERNAL_1_VECTOR, ipl1AUTO) EXTERNAL_1_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 2;
    }    

    SYS_INT_SourceStatusClear(INT_SOURCE_EXTERNAL_1);
}
//****************************************************************************//
void __ISR(_EXTERNAL_2_VECTOR, ipl1AUTO) EXTERNAL_2_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 3;
    }

    SYS_INT_SourceStatusClear(INT_SOURCE_EXTERNAL_2);
}
//****************************************************************************//
void __ISR(_EXTERNAL_4_VECTOR, ipl5AUTO) EXTERNAL_4_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 4;
    }    

    app_frame_received( DRV_CAMERA_OVM7692_VsyncEventHandler(sysObj.drvOVM7692) );

    SYS_INT_SourceStatusClear(INT_SOURCE_EXTERNAL_4);
}
//****************************************************************************//
void __ISR(_TIMER_4_VECTOR, ipl1AUTO) TIMER_4_Handler (void)
{
    TIMER_4_InterruptHandler();
}
//****************************************************************************//
void __ISR(_TIMER_9_VECTOR, ipl1AUTO) TIMER_9_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 5;
    }

    TIMER_9_InterruptHandler();
}
//****************************************************************************//
void __ISR(_CHANGE_NOTICE_B_VECTOR, ipl1AUTO) CHANGE_NOTICE_B_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 6;
    }

    if (SLEEP_WAKE_CAUSE_SLEEPING == sleep_wake_cause)
    {
        sleep_wake_cause = SLEEP_WAKE_CAUSE_TOUCH;
    }

    dprintf_colour("[PINK]Waking up[WHITE]\r\n");
            
    CHANGE_NOTICE_B_InterruptHandler();
}
//****************************************************************************//
void __ISR(_CHANGE_NOTICE_H_VECTOR, ipl1AUTO) CHANGE_NOTICE_H_Handler (void)
{
    CHANGE_NOTICE_H_InterruptHandler();
}
//****************************************************************************//
void __ISR(_DMA0_VECTOR, ipl6AUTO) DMA0_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 8;
    }

    DMA0_InterruptHandler();
}
//****************************************************************************//
void __ISR(_DMA1_VECTOR, ipl6AUTO) DMA1_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 9;
    }

    DMA1_InterruptHandler();
}
//****************************************************************************//
void __ISR(_UART3_FAULT_VECTOR, ipl3AUTO) UART3_FAULT_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 13;
    }

    UART3_FAULT_InterruptHandler();
}
//****************************************************************************//
void __ISR(_UART3_RX_VECTOR, ipl4AUTO) UART3_RX_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 14;
    }

    UART3_RX_InterruptHandler();
}
//****************************************************************************//
void __ISR(_UART3_TX_VECTOR, ipl3AUTO) UART3_TX_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 15;
    }

    UART3_TX_InterruptHandler();
}
//****************************************************************************//
void __ISR(_SQI1_VECTOR, ipl1AUTO) SQI1_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 16;
    }
}
//****************************************************************************//
void __ISR(_UART6_FAULT_VECTOR, ipl1AUTO) UART6_FAULT_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 17;
    }

    UART6_FAULT_InterruptHandler();
}
//****************************************************************************//
void __ISR(_UART6_TX_VECTOR, ipl1AUTO) UART6_TX_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 19;
    }

    UART6_TX_InterruptHandler();
}
//****************************************************************************//
void __ISR(_GLCD_VECTOR, ipl1AUTO) GLCD_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 20;
    }

    GLCD_Interrupt_Handler();
}
//****************************************************************************//
void __ISR(_UART5_FAULT_VECTOR, ipl1AUTO) UART5_FAULT_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 21;
    }

    UART5_FAULT_InterruptHandler();
}
//****************************************************************************//
void __ISR(_UART5_RX_VECTOR, ipl2AUTO) UART5_RX_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 22;
    }

    UART5_RX_InterruptHandler();
}
//****************************************************************************//
void __ISR(_UART5_TX_VECTOR, ipl1AUTO) UART5_TX_Handler (void)
{
    if (0 == interrupt_source)
    {
        interrupt_source = 23;
    }

    UART5_TX_InterruptHandler();
}
//****************************************************************************//
/*******************************************************************************
 End of File
*/
