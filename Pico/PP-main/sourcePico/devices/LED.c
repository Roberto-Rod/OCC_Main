/*****************************************************************************
 *   File        : LED.c
 *
 *   Description : Source Code for Turning on and off LEDs
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

#include <xc.h>
#include "pin_manager.h"
#include "LED.h"
#include "mcc.h"


void LED_SetOrange(bool_t on)
{
  if(on)
  {
    IO_RC5_SetHigh();
  }
  else
  {
    IO_RC5_SetLow();
  }
}

void LED_SetGreen(bool_t on)
{
  if(on)
  {
    IO_RC7_SetHigh();
  }
  else
  {
    IO_RC7_SetLow();
  }
}
