/*****************************************************************************
 *   File        : test_StateMachinePOST.c
 *
 *   Description: Source Code for test of the State Machine POST.
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

#include "unity.h"
#include "StateMachinePOST.h"
#include "MockStateMachinePOST_internal.h"
#include "MockDeviceStatus.h"

void setUp(void)
{}

void tearDown(void)
{}

void test_OnInitSetsStateToZeroAndReturnsZero(void)
{
  iPOST_setSubStateNum_Expect(0xFF);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, POST_Init());
}

void test_ifNotDoingPOSTRunTransistionsToIdleState(void)
{
  uint8_t     subStateNum = 0;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_doPOST_ExpectAndReturn(0);
  DeviceStatus_SetDeepSleepModeStatus_Expect(TRUE);
  stateResult = POST_Run(TRUE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(IDLE_E, newState);
}

void test_onRunStateTestGoToDefaultWithInvalidSwitch(void)
{
  uint8_t     subStateNum = 0;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(POST_STATE_MAX);
  iPOST_StateError_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(POST_STATE_MAX + 1);
  iPOST_StateError_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(POST_STATE_MAX + 2);
  iPOST_StateError_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState00CalledWhenStateIsZero(void)
{
  uint8_t     subStateNum = 0;
  ErrorCode_t stateResult;
  State_t     newState;

  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_Init_Expect();
  iPOST_State00_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_Init_Expect();
  iPOST_State00_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState01CalledWhenStateIsOne(void)
{
  uint8_t     subStateNum = 1;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State01_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State01_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState02CalledWhenStateIsTwo(void)
{
  uint8_t     subStateNum = 2;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State02_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State02_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState03CalledWhenStateIsThree(void)
{
  uint8_t     subStateNum = 3;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State03_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State03_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState04CalledWhenStateIsFour(void)
{
  uint8_t     subStateNum = 4;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State04_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State04_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState05CalledWhenStateIsFive(void)
{
  uint8_t     subStateNum = 5;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State05_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State05_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState06CalledWhenStateIsSix(void)
{
  uint8_t     subStateNum = 6;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State06_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State06_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState07CalledWhenStateIsSeven(void)
{
  uint8_t     subStateNum = 7;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State07_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State07_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState08CalledWhenStateIsEight(void)
{
  uint8_t     subStateNum = 8;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State08_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State08_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState09CalledWhenStateIsNine(void)
{
  uint8_t     subStateNum = 9;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State09_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State09_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}

void test_onRunState10CalledWhenStateIsTen(void)
{
  uint8_t     subStateNum = 10;
  ErrorCode_t stateResult;
  State_t     newState;
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State10_ExpectAndReturn(EC_OK_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
  
  iPOST_updateSubStateNum_Expect();
  iPOST_getSubStateNum_ExpectAndReturn(subStateNum);
  iPOST_State10_ExpectAndReturn(EC_FAILED_E);
  stateResult = POST_Run(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, stateResult);
  TEST_ASSERT_EQUAL_INT(POST_E, newState);
}




