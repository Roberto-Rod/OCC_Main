/********************************************************************************
* File : StateMachinePOST_Internal.h
*
* Description : Implements the POST state for the device state machine
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

#ifndef PICOONBOARD_STATEMACHINE_POST_INTERNAL_H
#define PICOONBOARD_STATEMACHINE_POST_INTERNAL_H

#include "StateMachineCommon.h"
#include "ErrorCode.h"
#include "Transmit.h"
#include "I2CEEPROM.h"

typedef enum 
{
    POST_STATE_INITIAL = 0xFF,
    POST_STATE_00 = 0,
    POST_STATE_01,
    POST_STATE_02,
    POST_STATE_03,
    POST_STATE_04,
    POST_STATE_05,
    POST_STATE_06,
    POST_STATE_07,
    POST_STATE_08,
    POST_STATE_09,
    POST_STATE_10,
    POST_STATE_MAX
} POSTSubState_t;

POSTSubState_t iPOST_getSubStateNum(void);

uint8_t  iPOST_doPOST(void);

void iPOST_updateSubStateNum(void);

void iPOST_setSubStateNum(POSTSubState_t  newStateNum);

ErrorCode_t iPOST_State00(void);

ErrorCode_t iPOST_State01(void);

ErrorCode_t iPOST_State02(void);

ErrorCode_t iPOST_State03(void);

ErrorCode_t iPOST_State04(void);

ErrorCode_t iPOST_State05(void);

ErrorCode_t iPOST_State06(void);

ErrorCode_t iPOST_State07(void);

ErrorCode_t iPOST_State08(void);

ErrorCode_t iPOST_State09(void);

ErrorCode_t iPOST_State10(void);

ErrorCode_t iPOST_StateError(void);

void iPOST_Init(void);


#endif //PICOONBOARD_STATEMACHINE_POST_INTERNAL_H
