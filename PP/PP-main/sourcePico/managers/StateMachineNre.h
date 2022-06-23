/********************************************************************************
* File : StateMachineNre.h
*
*   Description : Implements the Non Recoverable Error state for the device state
*                 machine, that is turning off the device if a NRE or a battery
*                 depleted condition is detected. The device cannot exit this state
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

#ifndef PICOONBOARD_STATEMACHINE_NRE_H
#define PICOONBOARD_STATEMACHINE_NRE_H

#include "StateMachineCommon.h"

ErrorCode_t NonRecoverableError(bool_t, State_t *);

#endif //PICOONBOARD_STATEMACHINE_NRE_H
