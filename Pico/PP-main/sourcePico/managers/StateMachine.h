/********************************************************************************
* File : StateMachine.h
*
* Description : State Machine for Pump DOwn and Therapy Delivery
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#ifndef PICOONBOARD_STATEMACHINE_H
#define PICOONBOARD_STATEMACHINE_H

#include "StateMachineCommon.h"
#include "DeviceStatus.h"


ErrorCode_t StateMachine_Init(void);
ErrorCode_t StateMachine_Run(void);
void  StateMachine_Enter_NRE(bool_t enteringNewState);

#endif //PICOONBOARD_STATEMACHINE_H
