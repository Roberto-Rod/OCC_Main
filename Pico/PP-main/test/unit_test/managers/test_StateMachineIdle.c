/*****************************************************************************
 *   File        : test_StateMachineIdle.c
 *
 *   Description: Source Code for test of the State Machine Idle.
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
#include "StateMachineIdle.h"
#include "MockPushButton.h"
#include "MockPowerControl.h"
#include "MockTimer.h"
#include "MockPressure_Part1.h"
#include "MockStateMachineCommon.h"
#include "MockHardwareInterface.h"
#include "Assert.h"
#include "DeviceStatus.h"

static bool_t hasPressed;
static bool_t hasShortPress;

static bool_t StubPushButton_IsPressed(int numCall)
{
  return hasPressed;
}

static bool_t StubPushButton_IsShortPress(int numCall)
{
  return hasShortPress;
}

void setUp(void)
{
  PushButton_IsPressed_StubWithCallback(StubPushButton_IsPressed);
  PushButton_IsShortPress_StubWithCallback(StubPushButton_IsShortPress);

  hasPressed = FALSE;
  hasShortPress = FALSE;
}

void tearDown(void)
{}

void test_OnInitClearSystemTimerReferenceReturnOk(void)
{
  TEST_ASSERT_EQUAL_INT(EC_OK_E, Idle_Init());
}

void test_IdleCheckStateReturnsInvalidParameter(void)
{
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, Idle(FALSE, NULL));
  TEST_FAIL_MESSAGE("Code should be asserted and this function should not be called");
}

void test_OnEntryInitialiseUIAndPowerSettingAndWhenSwitchIsNotPressedGoToIdle(void)
{
  //No button press detected when entering IDLE for the first time
  MP_DisablePeripheral_Ignore();
  TimerCounter_Status_IgnoreAndReturn(RUNNING_COUNTER_E);

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 10*60*60, EC_OK_E);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);
  MP_DisablePumpPWM_Expect();
  MP_DisableExternalPeripheralsSupply_Expect();
  MP_DisableMainCircuitPower_Expect();
  SetInitialExternalPressure_Expect(0);
  PushButton_ResetEvent_Expect();

  //check test results
  State_t nextState = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, Idle(TRUE, &nextState));

  //test that device status stays in IDLE
  TEST_ASSERT_EQUAL_INT(IDLE_E, nextState);
}

void test_IdleStateRunsWhenSwitchIsPressedNotLongEnoughToSwitchOnAndStayInIdle(void)
{
  TimerCounter_Status_IgnoreAndReturn(RUNNING_COUNTER_E);
  //Button press detected when entering IDLE
  hasPressed = TRUE;

  State_t nextState = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, Idle(FALSE, &nextState));
  TEST_ASSERT_EQUAL_INT(IDLE_E, nextState);

  //Button press detected while in IDLE but not long enough to go in Pump Down
  hasPressed = TRUE;

  nextState = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, Idle(FALSE, &nextState));
  TEST_ASSERT_EQUAL_INT(IDLE_E, nextState);
}


void test_IdleStateRunsWhenSwitchIsPressedLongEnoughToGoIntoPumpDown(void)
{
  //Button press detected while in IDLE long enough to go in Pump Down
  hasPressed = TRUE;
  hasShortPress = TRUE;

  //check test results
  State_t nextState = NONE_E;
  HardwareInterface_SystemInitialise_Expect();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, Idle(FALSE, &nextState));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, nextState);
}

void test_OnRunIfPushButtonIsNotPressedDisablePeripheral(void)
{
  hasPressed = FALSE;
  TimerCounter_Status_IgnoreAndReturn(RUNNING_COUNTER_E);

  MP_DisablePeripheral_Expect();

  State_t nextState = NONE_E;
  Idle(FALSE, &nextState);
  TEST_ASSERT_EQUAL_INT(IDLE_E, nextState);
}

void test_IfTimerExpireGoToIPDEvenIfNoButtonIsPressed(void)
{
  hasPressed = FALSE;
  hasShortPress = FALSE;
  MP_DisablePeripheral_Ignore();

  //timer not expired yet
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);
  State_t nextState = NONE_E;
  Idle(FALSE, &nextState);
  TEST_ASSERT_EQUAL_INT(IDLE_E, nextState);

  //timer has expired
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  nextState = NONE_E;

  HardwareInterface_SystemInitialise_Expect();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  Idle(FALSE, &nextState);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, nextState);

}