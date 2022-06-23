/********************************************************************************
* File : StateMachinePumpDown.h
*
* Description : Implements the PUMP DOWN state for the device state machine
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#ifndef PICOONBOARD_STATEMACHINE_PUMPDOWN_H
#define PICOONBOARD_STATEMACHINE_PUMPDOWN_H

#include "StateMachineCommon.h"

#define PUMP_DOWN_COUNT_TICK_DURATION (200)

ErrorCode_t PumpDown (bool_t,State_t*);
ErrorCode_t PumpDown_Init (void);

#endif //PICOONBOARD_STATEMACHINE_PUMPDOWN_H
