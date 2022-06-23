/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    system.h

  @Summary:
    This is the sysetm.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33CK128MP203
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB             :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "pin_manager.h"
#include "clock.h"
#include "system.h"
#include "system_types.h"
#include "dma.h"
#include "clc1.h"
#include "clc2.h"
#include "uart1.h"
//#include "uart2.h"
#include "../pdab_comms.h"
#include "interrupt_manager.h"
#include "traps.h"
#include "delay.h"
#include "cmp1.h"
#include "clc3.h"
#include "clc4.h"
#include "sccp2_tmr.h"
#include "memory/flash.h"
#include "sccp7_tmr.h"
#include "tmr1.h"
#include "ext_int.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    CLOCK_Initialize();
    INTERRUPT_Initialize();
    SCCP2_TMR_Initialize();
    SCCP7_TMR_Initialize();
    UART1_Initialize();
    CLC2_Initialize();
    EXT_INT_Initialize();
//    UART2_Initialize();
    pic_communications_init();
    CLC1_Initialize();
    CMP1_Initialize();
    CLC4_Initialize();
    CLC3_Initialize();
    DMA_Initialize();
    TMR1_Initialize();
    INTERRUPT_GlobalEnable();
    /* @brief Choosing options of operating DSP engine via CPU control register */
    SYSTEM_CORCONModeOperatingSet(CORCON_MODE_PORVALUES);
}

/**
 End of File
*/