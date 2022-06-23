/*****************************************************************************
 *   File        : Battery.h
 *
 *   Description : Checking whether battery voltage is out of bounds or depleted
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#ifndef PICOONBOARD_BATTERY_H
#define PICOONBOARD_BATTERY_H

#include "PaTypes.h"
#include "ErrorCode.h"

ErrorCode_t Battery_CheckVoltageBounds(void);

#endif //PICOONBOARD_BATTERY_H
