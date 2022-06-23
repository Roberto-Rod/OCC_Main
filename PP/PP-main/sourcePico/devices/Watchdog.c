/*****************************************************************************
 *   File        : Watchdog.c
 *
 *   Description : Source Code for implementation of Watchdog Timer.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "Watchdog.h"
#include <pic16lf1509.h>

void Watchdog_Init()
{
    //see status register Datasheet 3.3.1.1
    //STATUSbits.nPD = not Power down bit
    //    1 = After power-up or by the CLRWDT instruction
    //    0 = By execution of the SLEEP instruction

    //STATUSbits.nTO = !Time out bit 
    //    1 = After power-up, CLRWDT instruction or SLEEP instruction
    //    0 = A WDT time-out occurred
            
  WDTCONbits.WDTPS = 0x09;    // 1:16384 (Interval 512 ms nominal)
  
}

void Watchdog_Clear()
{
  asm("clrwdt");
}

