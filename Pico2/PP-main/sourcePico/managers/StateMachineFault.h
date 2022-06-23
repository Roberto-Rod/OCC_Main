/********************************************************************************
* File :  StateMachineFault.h
*
* Description : Implements the FAULT state for the device state machin
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

#ifndef PICOONBOARD_STATEMACHINE_FAULT_H
#define PICOONBOARD_STATEMACHINE_FAULT_H

#include "StateMachineCommon.h"

#define FAULT_COUNT_TICK_DURATION (36000u) // i.e. 60 minutes at 10 ticks per second = 3600

ErrorCode_t Fault(bool_t aCurrentStateOnEntry, State_t *nextState);

#endif //PICOONBOARD_STATEMACHINE_FAULT_H
