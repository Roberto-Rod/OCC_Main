/*****************************************************************************
 *   File        : test_StateMachine.c
 *
 *   Description: Source Code for test of the State Machine.
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
#include "StateMachine.h"
#include "DeviceStatus.h"
#include "MockAlertManager.h"
#include "MockStateMachineIdle.h"
#include "MockStateMachinePumpDown.h"
#include "MockStateMachinePOST.h"
#include "MockStateMachineNre.h"
#include "MockStateMachineTherapyDelivery.h"
#include "MockStateMachineShutdown.h"
#include "MockStateMachineFault.h"

static State_t TestIdleReturnState = NONE_E;
static State_t TestPumpDownReturnState = NONE_E;
static State_t TestPOSTReturnState = IDLE_E;
static State_t TestSingleStateReturnError = EC_OK_E;
static ErrorCode_t TestPOSTReturnVal = EC_OK_E;


// Stub to emulate state changes from IDLE state
static ErrorCode_t Stub_Idle(bool_t aCurrentStateOnEntry, State_t *aNewState, int NumCall)
{
  *aNewState = TestIdleReturnState;
  
  return TestSingleStateReturnError;
}

// Stub to emulate state changes from IDLE state
static ErrorCode_t Stub_POST(bool_t aCurrentStateOnEntry, State_t *aNewState, int NumCall)
{
  *aNewState = TestPOSTReturnState;
  
  return TestPOSTReturnVal;
}

// Stub to emulate state changes from PUMP DOWN state
ErrorCode_t Stub_PumpDown(bool aCurrentStateOnEntry, State_t *aNewState, int NumCall)
{
  *aNewState = TestPumpDownReturnState;
  
  return TestSingleStateReturnError;
}


void setUp(void)
{
  TestIdleReturnState = NONE_E;
  TestPumpDownReturnState = NONE_E;
  TestSingleStateReturnError = EC_OK_E;
  
  Idle_Init_ExpectAndReturn(EC_OK_E);
  PumpDown_Init_ExpectAndReturn(EC_OK_E);
  TherapyDelivery_Init_ExpectAndReturn(EC_OK_E);
  POST_Init_ExpectAndReturn(EC_OK_E);
}

void tearDown(void)
{}

// State Machine is initialised to POST state
void test_OnInitReturnIdleState(void)
{  
  StateMachine_Init();
  
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TEST_ASSERT_TRUE(DeviceStatus_GetOnEntry);
}

// State Machine runs through POST to IDLE state with no button switch detected, stays in IDLE
void test_RunInIdleStateWithNoButtonPresses(void)
{
  Idle_StubWithCallback(Stub_Idle);
  TestIdleReturnState = IDLE_E;
  TestSingleStateReturnError = EC_OK_E;  

  POST_Run_StubWithCallback(Stub_POST);
  TestPOSTReturnVal = EC_OK_E;
  TestPOSTReturnState = IDLE_E;
  
  StateMachine_Init();

  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_FALSE(DeviceStatus_GetOnEntry());
}

// State Machine runs in IDLE state returning error, stays in same state
void test_RunInIdleStateWithError(void)
{
  Idle_StubWithCallback(Stub_Idle);
  TestIdleReturnState = IDLE_E;
  TestSingleStateReturnError = EC_FAILED_E;  

  POST_Run_StubWithCallback(Stub_POST);
  TestPOSTReturnVal = EC_OK_E;
  TestPOSTReturnState = IDLE_E;

  StateMachine_Init();

  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_FALSE(DeviceStatus_GetOnEntry());
}

// State Machine runs in IDLE state, go to PUMP DOWN state
void test_RunInIdleStateAndGoToPumpDownStateAndTherapyDelivery(void)
{
  Idle_StubWithCallback(Stub_Idle);
  
  // From IDLE to PUMP DOWN
  TestIdleReturnState = PUMP_DOWN_E;
  TestSingleStateReturnError = EC_OK_E;  

  POST_Run_StubWithCallback(Stub_POST);
  TestPOSTReturnVal = EC_OK_E;
  TestPOSTReturnState = IDLE_E;

  StateMachine_Init();

  StartLEDSequence_Expect(LED_CTRL_PUMP_DOWN_E);

  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  TEST_ASSERT_TRUE(DeviceStatus_GetOnEntry());
  
  // From PUMP DOWN to THERAPY DELIVERY state
  TestPumpDownReturnState = THERAPY_DELIVERY_E;
  TestSingleStateReturnError = EC_OK_E;
  PumpDown_StubWithCallback(Stub_PumpDown);
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  TEST_ASSERT_TRUE(DeviceStatus_GetOnEntry());
}

// State Machine runs in PUMP DOWN state returning an unknown state, go to FAULT state
void test_RunInPumpDownStateReturningUnknownStateAndGoToFaultState(void)
{
  Idle_StubWithCallback(Stub_Idle);
  TestIdleReturnState = PUMP_DOWN_E;
  TestSingleStateReturnError = EC_OK_E;  
  POST_Run_StubWithCallback(Stub_POST);
  TestPOSTReturnVal = EC_OK_E;
  TestPOSTReturnState = IDLE_E;
  StateMachine_Init();
  StartLEDSequence_Expect(LED_CTRL_PUMP_DOWN_E);

  StateMachine_Run();  //POST to IDLE
  StartLEDSequence_Expect(LED_CTRL_LEAK_E);
  StateMachine_Run();  //IDLE to PUMP_DOWN
  TestIdleReturnState = NONE_E;
  PumpDown_StubWithCallback(Stub_PumpDown);

  TEST_ASSERT_EQUAL_INT(EC_OK_E, StateMachine_Run());
  TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  TEST_ASSERT_TRUE(DeviceStatus_GetOnEntry());
}

