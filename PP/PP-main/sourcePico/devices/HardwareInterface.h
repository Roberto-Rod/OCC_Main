/*****************************************************************************
 *   File        : HardwareInterface.h
 *
 *   Description : Temporary hardware interface to which requires mcc.h to do
 * bit bashing
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

#ifndef PICOONBOARD_HARDWAREINTERFACE_H
#define PICOONBOARD_HARDWAREINTERFACE_H

/* TODO this is a temporary file to separate dependency headers which contains register bit bashing in
  #defines. This is done to enable host based testing. To be rearranged into appropriate lower level modules.
 */

void HardwareInterface_EnableGlobalInterrupt(void);
void HardwareInterface_DisableGlobalInterrupt(void);

void HardwareInterface_EnablePeripheralInterrupt(void);

void HardwareInterface_SystemInitialise(void);


#endif //PICOONBOARD_HARDWAREINTERFACE_H
