/*****************************************************************************
 *   File        : PumpFrequencyTracker.h
 *
 *   Description : Header for implementation of Pump Frequency Tracker
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

#ifndef PICOONBOARD_PUMPFREQUENCYTRACKER_H
#define PICOONBOARD_PUMPFREQUENCYTRACKER_H


#include "ErrorCode.h"

void PumpFrequencyTracker_Init();
ErrorCode_t PumpFrequencyTracker_Optimise(void);

#endif //PICOONBOARD_PUMPFREQUENCYTRACKER_H
