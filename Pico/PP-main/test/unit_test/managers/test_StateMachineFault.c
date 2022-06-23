/*****************************************************************************
 *   File        : test_StateMachineFault.c
 *
 *   Description: Source Code for test of the State Machine Fault.
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
#include "StateMachineFault.h"
#include "MockStateMachineCommon.h"
#include "MockTimer.h"
#include "MockUIInterfaces.h"
#include "MockPowerControl.h"
#include "MockPushButton.h"
#include "DeviceStatus.h"
#include "MockBattery.h"
#include "Mockadc.h"
#include "MockPerformanceLogger.h"

#include "Assert.h"

void setUp()
{
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF_29V); 
}

void tearDown()
{}

void test_StateChecksAgainstNullPointer(void)
{
  Fault(TRUE, NULL);
  TEST_FAIL_MESSAGE("Assert should be called before this statement");

}

void test_OnEntryInitialiseDependencyModules(void)
{
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, FAULT_COUNT_TICK_DURATION, EC_OK_E);

  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);
  MP_DisablePumpPWM_Expect();
  MP_DisableExternalPeripheralsSupply_Expect();
  PushButton_ResetEvent_Expect();

  //we are going to ignore other calls
  PushButton_IsPressed_IgnoreAndReturn(TRUE);
  PushButton_IsShortPress_IgnoreAndReturn(TRUE);

  State_t newState = NONE_E;
  Fault(TRUE, &newState);
}

void test_OnShortPressTransitToPumpDown(void)
{
  TimerCounter_Status_IgnoreAndReturn(DISABLED_COUNTER_E);
  TimerCounter_Disable_IgnoreAndReturn(EC_OK_E);

  

  State_t newState = NONE_E;

  //stay at fault state
  PushButton_IsPressed_ExpectAndReturn(FALSE);
  MP_SetReferenceVoltageBoost_Ignore();
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF_29V);
  Battery_CheckVoltageBounds_ExpectAndReturn(EC_OK_E);
  PM_Delay_Ignore();  
  Fault(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(FAULT_E, newState);

  PushButton_IsPressed_ExpectAndReturn(TRUE);
  PushButton_IsShortPress_ExpectAndReturn(FALSE);
  MP_SetReferenceVoltageBoost_Ignore();
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF_29V);
  Battery_CheckVoltageBounds_ExpectAndReturn(EC_OK_E);
  PM_Delay_Ignore();  
  Fault(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(FAULT_E, newState);

  //Transition when button is pressed long enough
  //to qualify as a short press
  PushButton_IsPressed_ExpectAndReturn(TRUE);
  PushButton_IsShortPress_ExpectAndReturn(TRUE);
  Fault(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, newState);
}



void test_AfterSetNumberOfMinutesTransitToIPD(void)
{
  CounterStatus_t counterStatus = DISABLED_COUNTER_E;

  PushButton_IsPressed_IgnoreAndReturn(FALSE);

  CounterStatus_t stubTimerCounter_Status(CounterName_t counterName, int numCall)
  {
    TEST_ASSERT_EQUAL_INT(STATE_MACHINE_COUNTER_E, counterName);
    return counterStatus;
  }
  TimerCounter_Status_StubWithCallback(stubTimerCounter_Status);

  State_t newState = NONE_E;

  //Timer has not expired
  MP_SetReferenceVoltageBoost_Ignore();
  PM_Delay_Ignore(); 
  Battery_CheckVoltageBounds_ExpectAndReturn(EC_OK_E);
  Fault(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(FAULT_E, newState);

  //Timer has expired
  counterStatus = EXPIRED_COUNTER_E;
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  
  Fault(FALSE, &newState);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, newState);
}