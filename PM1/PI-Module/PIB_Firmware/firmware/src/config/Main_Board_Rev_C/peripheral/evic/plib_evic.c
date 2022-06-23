/*******************************************************************************
  EVIC PLIB Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    plib_evic.c

  Summary:
    EVIC PLIB Source File

  Description:
    None

*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#include "device.h"
#include "plib_evic.h"

// *****************************************************************************
// *****************************************************************************
// Section: IRQ Implementation
// *****************************************************************************
// *****************************************************************************

void EVIC_Initialize( void )
{
    INTCONSET = _INTCON_MVEC_MASK;

    /* Set up priority / subpriority of enabled interrupts */
    IPC0SET = 0x4 | 0x0;  /* CORE_TIMER:  Priority 1 / Subpriority 0 */
    IPC4SET = 0x4000000 | 0x0;  /* TIMER_4:  Priority 1 / Subpriority 0 */
    IPC5SET = 0x14000000 | 0x0;  /* EXTERNAL_4:  Priority 5 / Subpriority 0 */
    IPC10SET = 0x4 | 0x0;  /* TIMER_9:  Priority 1 / Subpriority 0 */
    IPC29SET = 0x4000000 | 0x0;  /* CHANGE_NOTICE_B:  Priority 1 / Subpriority 0 */
    IPC31SET = 0x400 | 0x0;  /* CHANGE_NOTICE_H:  Priority 1 / Subpriority 0 */
    IPC33SET = 0x180000 | 0x0;  /* DMA0:  Priority 6 / Subpriority 0 */
    IPC33SET = 0x18000000 | 0x0;  /* DMA1:  Priority 6 / Subpriority 0 */
    IPC36SET = 0xc00 | 0x0;  /* UART2_FAULT:  Priority 3 / Subpriority 0 */
    IPC36SET = 0x100000 | 0x0;  /* UART2_RX:  Priority 4 / Subpriority 0 */
    IPC39SET = 0xc00 | 0x0;  /* UART3_FAULT:  Priority 3 / Subpriority 0 */
    IPC39SET = 0x100000 | 0x0;  /* UART3_RX:  Priority 4 / Subpriority 0 */
    IPC39SET = 0xc000000 | 0x0;  /* UART3_TX:  Priority 3 / Subpriority 0 */
    IPC44SET = 0x4000000 | 0x0;  /* UART5_FAULT:  Priority 1 / Subpriority 0 */
    IPC45SET = 0x8 | 0x0;  /* UART5_RX:  Priority 2 / Subpriority 0 */
    IPC45SET = 0x400 | 0x0;  /* UART5_TX:  Priority 1 / Subpriority 0 */
    IPC47SET = 0x4 | 0x0;  /* UART6_FAULT:  Priority 1 / Subpriority 0 */
    IPC47SET = 0x40000 | 0x0;  /* UART6_TX:  Priority 1 / Subpriority 0 */
    IPC48SET = 0x4 | 0x0;  /* GLCD:  Priority 1 / Subpriority 0 */
}

void EVIC_SourceEnable( INT_SOURCE source )
{
    volatile uint32_t *IECx = (volatile uint32_t *) (&IEC0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IECxSET = (volatile uint32_t *)(IECx + 2);

    *IECxSET = 1 << (source & 0x1f);
}

void EVIC_SourceDisable( INT_SOURCE source )
{
    volatile uint32_t *IECx = (volatile uint32_t *) (&IEC0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IECxCLR = (volatile uint32_t *)(IECx + 1);

    *IECxCLR = 1 << (source & 0x1f);
}

bool EVIC_SourceIsEnabled( INT_SOURCE source )
{
    volatile uint32_t *IECx = (volatile uint32_t *) (&IEC0 + ((0x10 * (source / 32)) / 4));

    return (bool)((*IECx >> (source & 0x1f)) & 0x01);
}

bool EVIC_SourceStatusGet( INT_SOURCE source )
{
    volatile uint32_t *IFSx = (volatile uint32_t *)(&IFS0 + ((0x10 * (source / 32)) / 4));

    return (bool)((*IFSx >> (source & 0x1f)) & 0x1);
}

void EVIC_SourceStatusSet( INT_SOURCE source )
{
    volatile uint32_t *IFSx = (volatile uint32_t *) (&IFS0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IFSxSET = (volatile uint32_t *)(IFSx + 2);

    *IFSxSET = 1 << (source & 0x1f);
}

void EVIC_SourceStatusClear( INT_SOURCE source )
{
    volatile uint32_t *IFSx = (volatile uint32_t *) (&IFS0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IFSxCLR = (volatile uint32_t *)(IFSx + 1);

    *IFSxCLR = 1 << (source & 0x1f);
}

