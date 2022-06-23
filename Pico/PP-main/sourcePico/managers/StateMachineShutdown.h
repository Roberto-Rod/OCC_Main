/********************************************************************************
* File : StateMachineShutdown.h
*
* Description : Implements the STOPPED state for the device state machin
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

#ifndef PICOONBOARD_STATEMACHINE_SHUTDOWN_H
#define PICOONBOARD_STATEMACHINE_SHUTDOWN_H

#include "StateMachineCommon.h"

#define SHUT_DOWN_COUNT_TICK_DURATION (30-1)   // 30 seconds minus 100ms to ensure flashing and 
                                               // state change happen at the same time 

ErrorCode_t Shutdown (bool_t, State_t*);

#endif //PICOONBOARD_STATEMACHINE_SHUTDOWN_H
