/*****************************************************************************
 *   File        : PushButton.h
 *
 *   Description : API to calculate the duty cycle between Pump On and Off
 * during Therapy Delivery
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

#ifndef PICOONBOARD_DUTYCYCLE_H
#define PICOONBOARD_DUTYCYCLE_H

#include "PaTypes.h"

#define DUTY_CYCLE_UPDATE_TICK_DURATION     (10) // Interval (currently multiple of 100ms) between consecutive duty cycle updates
#define MAINTANENCE_DUTY_CYCLE               (3) // (2)
#define LEAK_DUTY_CYCLE                     (15) // WARNING: MAX depends on the size of DC History in seconds (currently 32) 

#define LEAK_DUTY_CYCLE_PERIOD              (30) // max 32
#define VACUUM_OFFSET_DUTY_CYCLE_PERIOD      (9) // max 32

void DCHistoryReset (void);
void DCCalculateAll(void);
void DCPumpOnUpdate(void);
void DCPumpOffUpdate(void);
uint8_t DCVaccumOffsetUpdateGet(void);
uint8_t  DCLeakGet(void);

#endif //PICOONBOARD_DUTYCYCLE_H
