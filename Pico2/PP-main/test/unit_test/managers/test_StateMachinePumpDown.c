/*****************************************************************************
 *   File        : test_StateMachinePumpDown.c
 *
 *   Description: Source Code for test of the State Machine Pump Down.
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
#include "StateMachinePumpDown.h"
#include "DeviceStatus.h"
#include "MockTimer.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockUIInterfaces.h"
#include "MockPowerControl.h"
#include "MockStateMachineCommon.h"
#include "MockPushButton.h"
#include "MockPerformanceLogger.h"
#include "Assert.h"

#define TEST_PUMP_DOWN_TARGET_VACUUM (107)

static uint16_t TestInternal = 0;
static uint16_t TestExternal = 0;
static uint16_t TestVacuum = 0;
static uint32_t GetVacuumCalls = 0;
static bool_t GetVacuumForceFail = FALSE;
static uint8_t PumpDownDuration = 0;

static bool_t hasPressed;
static bool_t hasLongPress;

static bool_t StubPushButton_IsPressed(int numCall)
{
  return hasPressed;
}

static bool_t StubPushButton_IsLongPress(int numCall)
{
  return hasLongPress;
}

// Stub for gettingt the vacuum reading , whose return value can be forced based on GetVacuumForceFail
static ErrorCode_t Stub_GetVacuum(uint16_t* pInternal, uint16_t* pExternal, uint16_t* pVacuum, int NumCalls)
{
  ErrorCode_t result = EC_OK_E;
  
  GetVacuumCalls++;
  
  if(TRUE == GetVacuumForceFail)
  {
    result = EC_EXT_PRESSURE_SENSOR_READ_FAILED_E;
  }
  else
  {
    *pInternal = TestInternal;
    *pExternal = TestExternal;
    *pVacuum = TestVacuum;
    result = EC_OK_E;
  }
  
  return result;
}

static void Stub_PerformanceLogger_SetPumpDownDuration(const uint8_t duration100Ms, int NumCalls)
{
  PumpDownDuration = duration100Ms;
}


void setUp(void)
{
  TestVacuum = 0;
  GetVacuumCalls = 0;
  GetVacuumForceFail = FALSE;
  GetVacuum_StubWithCallback(Stub_GetVacuum);
  PushButton_IsPressed_StubWithCallback(StubPushButton_IsPressed);
  PushButton_IsLongPress_StubWithCallback(StubPushButton_IsLongPress);
  PerformanceLogger_SetPumpDownDuration_StubWithCallback(Stub_PerformanceLogger_SetPumpDownDuration);

  hasPressed = FALSE;
  hasLongPress = FALSE;
  
}

void tearDown(void)
{}

// PumpDown_Init initialises the various variable used within the state (e.g. timer, etc.)
void test_OnInitDisableStateTimerInitialiseStateVacuumAndReurnOk(void)
{
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E,EC_OK_E);
  InitPumpDownVacuum_Expect();
  
  ErrorCode_t errorCode = PumpDown_Init();
  TEST_ASSERT_EQUAL_INT(EC_OK_E, errorCode);
}

// PumpDown can handle a wrong input parameter for the "new state" variable
void test_PumpDownStateReturnsInvalidInputParameter(void)
{  
  PumpDown(FALSE, NULL);
  TEST_FAIL_MESSAGE("Assert should be called prior to this function");
}

// PumpDown runs four consecutive times and goes in to Therapy Delivery after timeout  
// having reached the target vacuum:
// first time -  OK (i.e starts the state timeout correctly, stays in the same state
//               as the timeout has not been reached, and reads the vacuum).
// second time - OK (i.e. it does not read the vacuum but starts the pump, and stays in
//               the same state)
// third time  - OK (i.e. it read the pressure and decides that it can goto therapy on the 
//               time out. Note The timeout value indicates time has passed  
// fourth time - OK and target has been reached in last 5 second Down target vacuum (i.e go to Therapy Delivery state)
void test_PumpDownRunsUntilReachingTargetVacuumWithVacuumReadAndPumpActivateAlternating(void)
{  
  // Run first time (OnEntryState), do not activate pump, read vacuum
  PushButton_ResetEvent_Ignore();
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E,EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, PUMP_DOWN_COUNT_TICK_DURATION, EC_OK_E);
  InitPumpDownVacuum_Expect();

  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 200);  
  PumpActivate_ExpectAndReturn(FALSE,EC_OK_E);
  TestVacuum = 200;
  isTargetPumpDownVacuumAchieved_ExpectAndReturn(TestVacuum, FALSE);
  State_t new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(TRUE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
 

  // Run second time, activate pump, do not read vacuum
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 140); 
  PumpActivate_ExpectAndReturn(TRUE,EC_OK_E);
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
 
  // Run third time, read the pressure within the 5 second window 
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 50 ); 
  PumpActivate_ExpectAndReturn(FALSE,EC_OK_E);
  TestVacuum = 200;
  isTargetPumpDownVacuumAchieved_ExpectAndReturn(TestVacuum, TRUE);
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(2, GetVacuumCalls);
 
  // Run fourth time, timeout so now goto therapy 
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 0); 
  TestVacuum = TEST_PUMP_DOWN_TARGET_VACUUM;
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
  TEST_ASSERT_EQUAL_INT(2, GetVacuumCalls);
}


void test_PumpDownDurationUpdatedWithPerformanceLogger(void)
{
  test_PumpDownRunsUntilReachingTargetVacuumWithVacuumReadAndPumpActivateAlternating();
  TEST_ASSERT_EQUAL_INT(150, PumpDownDuration);
}


// This is the same as the first test but the pressure is reached but not in the last 5 seconds
// so on timeout the system goes to failure 
// PumpDown runs four consecutive times and goes in to Therapy Delivery after timeout  
// having reached the target vacuum:
// first time -  OK (i.e starts the state timeout correctly, stays in the same state
//               as the timeout has not been reached, and reads the vacuum).
// second time - OK (i.e. it does not read the vacuum but starts the pump, and stays in
//               the same state)
// third time  - OK (i.e. it read the pressure and decides that it can goto therapy on the 
//               time out. Note The timeout value indicates the time has passed  
// fourth time - OK and target has not been reached in last 5 second Down target vacuum (i.e go to Fault state)
void test_PumpDownRunsFor20SecondWhenPressureReachedButOutwith5SecondWindow(void)
{  
  // Run first time (OnEntryState), do not activate pump, read vacuum
  PushButton_ResetEvent_Ignore();
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E,EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, PUMP_DOWN_COUNT_TICK_DURATION, EC_OK_E);
  InitPumpDownVacuum_Expect();

  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 200);  
  PumpActivate_ExpectAndReturn(FALSE,EC_OK_E);
  TestVacuum = 200;
  isTargetPumpDownVacuumAchieved_ExpectAndReturn(TestVacuum, FALSE);
  State_t new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(TRUE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
 

  // Run second time, activate pump, do not read vacuum
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 140); 
  PumpActivate_ExpectAndReturn(TRUE,EC_OK_E);
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
 
  // Run third time, read the pressure outwith the 5 second window 
  // Note: Only change here is that the timeout is 51 
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 51 ); 
  PumpActivate_ExpectAndReturn(FALSE,EC_OK_E);
  TestVacuum = 200;
  isTargetPumpDownVacuumAchieved_ExpectAndReturn(TestVacuum, TRUE);
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(2, GetVacuumCalls);
 
  // Run fourth time, timeout so now goto therapy 
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 0); 
  TestVacuum = TEST_PUMP_DOWN_TARGET_VACUUM;
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(FAULT_E, new_state);
  TEST_ASSERT_EQUAL_INT(2, GetVacuumCalls);
}


// PumpDown cannot reach target vacuum within Pump Down timeout
void test_PumpDownRunsCannotReachTargetVacuum(void)
{  
  // Run not for first time and, do not activate pump, read vacuum
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 0);  
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  State_t new_state = NONE_E;

  // Module under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(FAULT_E, new_state);
  TEST_ASSERT_EQUAL_INT(0, GetVacuumCalls);
  TEST_ASSERT_FALSE(DeviceStatus_IsReadingPressureSensor());
}


// PumpDown fails to take vacuum reading, stays in Pump Down state but returns error
// (it will eventually time out if the Vacuum reading keeps failing, in case the state
//  machine decides to retry)
void test_PumpDownFailsToTakeVacuumReadingAndReturnsError(void)
{ 
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
   PumpActivate_IgnoreAndReturn(EC_OK_E);
   GetVacuumForceFail = TRUE;
   State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_READ_FAILED_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
}


// Test long button press causes shutdown
void test_PumpDownDetectButtonPressAndEventuallyGoesInShutdown(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();
  
  // Run not for the first time, detect the button has not been pressed
  // for long enough to swicth the device off, run as normal
  hasPressed = TRUE;
  hasLongPress = FALSE;

  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  isTargetPumpDownVacuumAchieved_IgnoreAndReturn(FALSE);
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  State_t new_state = NONE_E;
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
  TEST_ASSERT_TRUE(DeviceStatus_IsReadingPressureSensor());


  // Run and detect the button has been pressed for long enough
  //  to swith the device off, by pass normal operations, clean
  // up Pump Down state and go into Shutdown
  hasLongPress = TRUE;
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  new_state = NONE_E;
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
  TEST_ASSERT_FALSE(DeviceStatus_IsReadingPressureSensor());

}

// This tests an NRV problem. Non Return Valve. The initial external pressure is read but 
// on the next reading the external pressure increases which causes a fault condition.
//
// PumpDown runs three consecutive times and goes into the FAULT when the external pressure 
// increases which indicates that a blockage has taken place   
// first time -  OK (i.e starts the state timeout correctly, stays in the same state
//               as the timeout has not been reached, and reads the vacuum).
//               It also reads the initial external pressure
// second time - OK (i.e. it does not read the vacuum but starts the pump, and stays in
//               the same state)
// third time  - OK (i.e. it read the external pressure which has not increaed more that 
//               the permitted amount and this causes an error 
void test_PumpDownRunsButExternalPressureIncreasesCausingNoneReturnValveError(void)
{  
  // Run first time (OnEntryState), do not activate pump, read vacuum
  PushButton_ResetEvent_Ignore();
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E,EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, PUMP_DOWN_COUNT_TICK_DURATION, EC_OK_E);
  InitPumpDownVacuum_Expect();

  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 200);  
  PumpActivate_ExpectAndReturn(FALSE,EC_OK_E);
  TestVacuum = 200;
  TestExternal = 200;
  isTargetPumpDownVacuumAchieved_ExpectAndReturn(TestVacuum, FALSE);
  State_t new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(TRUE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
 

  // Run second time, activate pump, do not read vacuum
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 140); 
  PumpActivate_ExpectAndReturn(TRUE,EC_OK_E);
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, new_state);
  TEST_ASSERT_EQUAL_INT(1, GetVacuumCalls);
 
  // Run third time, read the pressure but it has increased so this will cause 
  // the system to goto fault 
  // Note: Only change here is that the timeout is 51 
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 51 ); 
  PumpActivate_ExpectAndReturn(FALSE,EC_OK_E);
  TestVacuum = 200;
  TestExternal = 300;  // xxxyyyxx 
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  new_state = NONE_E;
  // Unit under test 
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpDown(FALSE, &new_state));

  TEST_ASSERT_EQUAL_INT(FAULT_E, new_state);
  TEST_ASSERT_EQUAL_INT(2, GetVacuumCalls);
  
}

void test_PumpDownRunnningDetectsExternalOverTemperatureEventAndEntersNRE(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_EXT_TEMPERATURE_HIGH);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  
  TEST_ASSERT_EQUAL_INT(EC_EXT_TEMPERATURE_HIGH, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_EXT_SENSOR_OVERHEAT_EVENT_E, DeviceStatus_GetNRE_Event() );   

}

void test_PumpDownRunnningDetectsInternalOverTemperatureEventAndEntersNRE(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_INT_TEMPERATURE_HIGH);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_INT_TEMPERATURE_HIGH, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_INT_SENSOR_OVERHEAT_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntInitalise(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_INT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntStart(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_INT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntNotReady(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_NOT_READY_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_NOT_READY_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_INT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntReadFailed(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_READ_FAILED_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_READ_FAILED_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_INT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtInitalise(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_EXT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtStart(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_EXT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtNotReady(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_NOT_READY_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_NOT_READY_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_EXT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtReadFailed(void)
{
  // Prepare for the test making sure the Pump Down state reads the Vacuum when called
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  PumpDown_Init();

  // Run not for first time, do not activate pump, read vacuum and fail
  UI_IsPushButtonPressed_IgnoreAndReturn(FALSE);
  TimerCounter_GetTimeout_ExpectAndReturn(STATE_MACHINE_COUNTER_E, 1);  
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_READ_FAILED_E);
  DeviceStatus_GetNRE_Event();
  GetVacuumForceFail = TRUE;
  State_t new_state = NONE_E;

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  InitPumpDownVacuum_Expect();
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_READ_FAILED_E, PumpDown(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_EXT_SENSOR_UNRELIABLE_EVENT_E, DeviceStatus_GetNRE_Event());   

}

