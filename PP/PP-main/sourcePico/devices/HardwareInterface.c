/*****************************************************************************
 *   File        : HardwareInterface.c
 *
 *   Description : Temporary hardware interface to which requires mcc.h to do
 * bit bashing.
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

#include "HardwareInterface.h"
#include "mcc.h"

void HardwareInterface_EnableGlobalInterrupt(void)
{
  INTERRUPT_GlobalInterruptEnable();
}

void HardwareInterface_DisableGlobalInterrupt(void)
{
  INTERRUPT_GlobalInterruptDisable();
}

void HardwareInterface_EnablePeripheralInterrupt(void)
{
  INTERRUPT_PeripheralInterruptEnable();
}

void HardwareInterface_SystemInitialise(void)
{
  SYSTEM_Initialize();
}
