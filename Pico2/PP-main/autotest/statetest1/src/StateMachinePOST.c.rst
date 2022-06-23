/********************************************************************************
* File : StateMachinePOST.c
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

#include "UIInterfaces.h"
#include "PowerControl.h"
#include "Timer.h"
#include "Pressure_Part1.h"
#include "StateMachinePOST.h"
#include "StateMachinePOST_internal.h"
#include "StateMachineCommon.h"

/****************************************************************************
Function Name  :  POST_Init

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  Initialises POST state
 *****************************************************************************/
ErrorCode_t POST_Init(void)
{
  ErrorCode_t result = EC_OK_E;

  iPOST_setSubStateNum(POST_STATE_INITIAL);

  return result;
}

/****************************************************************************
Function Name  :  POST_Run

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  Implements the POST state for the device state machine
 *****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'aNewState' in argument to operator 'unary *'. */
ErrorCode_t POST_Run(bool_t aCurrentStateOnEntry, State_t *aNewState)
{
  ErrorCode_t result = EC_OK_E;

  *aNewState = IDLE_E;
  if (aCurrentStateOnEntry)
  {
    if (iPOST_doPOST())
    {
      *aNewState = POST_E;
    }
  }
  else
  {
    *aNewState = POST_E;
  }

  
#ifdef SCU_OUT 
  //check to see if we must run POST
  if (POST_E == *aNewState)
  {
    iPOST_updateSubStateNum();
    POSTSubState_t subStateNum = iPOST_getSubStateNum();
    *aNewState = POST_E;

    switch (subStateNum)
    {
      case POST_STATE_00:
        iPOST_Init();
        result = iPOST_State00();
        break;

      case POST_STATE_01:
        result = iPOST_State01();
        break;

      case POST_STATE_02:
        result = iPOST_State02();
        break;

      case POST_STATE_03:
        result = iPOST_State03();
        break;

      case POST_STATE_04:
        result = iPOST_State04();
        break;

      case POST_STATE_05:
        result = iPOST_State05();
        break;

      case POST_STATE_06:
        result = iPOST_State06();
        break;

      case POST_STATE_07:
        result = iPOST_State07();
        break;

      case POST_STATE_08:
        result = iPOST_State08();
        break;

      case POST_STATE_09:
        result = iPOST_State09();
        break;

      case POST_STATE_10:
        result = iPOST_State10();
        break;

      default:
        result = iPOST_StateError();
        break;
    }
  }
  
#endif 

  //the device is ready to go into deep sleep
  if (IDLE_E == *aNewState)
  {
    DeviceStatus_SetDeepSleepModeStatus(TRUE);
  }
  
  return result;
}


