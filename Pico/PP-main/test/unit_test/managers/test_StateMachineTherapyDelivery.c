/*****************************************************************************
 *   File        : test_StateMachineTherapyDelivery.c
 *
 *   Description: Source Code for test of the State Machine Therapy Delivery module.
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
#include "StateMachineTherapyDelivery.h"
#include "MockTimer.h"
#include "MockPump.h"
#include "MockPushButton.h"
#include "MockPressure_Part1.h"
#include "MockPressure_Part3.h"
#include "MockPowerControl.h"
#include "MockDutyCycle.h"
#include "MockDeviceStatus.h"
#include "MockStateMachineCommon.h"
#include "Assert.h"
#include "MockPerformanceLogger.h"

#define TEST_PUMP_DOWN_TARGET_VACUUM (107)

static uint16_t TestInternal = 0;
static uint16_t TestExternal = 0;
static uint16_t TestVacuum = 0;
static uint32_t GetVacuumCalls = 0;
static bool_t GetVacuumForceFail = FALSE;
static uint8_t DCHistory = 0;
static bool_t VacuumAtTarget = FALSE;
static bool_t hasPressed;
static bool_t hasLongPress;
static uint8_t DepressedTickCount = 0;
static bool_t CheckStatusAlertEnabled = FALSE;
static bool_t isPressureSensorReading = FALSE;

// This is the pressure which will indicate that a blockage has taken place
// It is the first read pressure during pump down plus a 30 percent margin
uint16_t ExternalPressureForNRVBlockage = 0; 

// Helper function for common initialisation used by most but not all the tests
static void TestInit_Helper(void)
{
  // Initialise the state and prepare for the test
  InitTherapyDeliveryVacuum_Expect();
  DCHistoryReset_Expect();
  TherapyDelivery_Init();

  // Run not for the first time, it's time to read Vacuum, check it is at target
  DeviceStatus_GetLedsOnStatus_IgnoreAndReturn(TRUE);
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

bool_t Stub_isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum, int NumCalls)
{
  return VacuumAtTarget;
}

static bool_t StubPushButton_IsPressed(int numCall)
{
  return hasPressed;
}

static bool_t StubPushButton_IsLongPress(int numCall)
{
  return hasLongPress;
}

uint8_t Stub_PushButton_GetDepressedTickCount(int numCall)
{
  return DepressedTickCount;
}

void Stub_DeviceStatus_SetCheckStatusAlert(bool_t EnableCheck, int numCall)
{
  CheckStatusAlertEnabled = EnableCheck;
}

bool_t Stub_DeviceStatus_GetCheckStatusAlert(int numCall)
{
  return CheckStatusAlertEnabled;
}

void Stub_DeviceStatus_SetPressureSensorIsReading(bool_t isReading, int numCall)
{
  isPressureSensorReading = isReading;
}

void setUp(void)
{
  TestVacuum = 0;
  GetVacuumCalls = 0;
  GetVacuumForceFail = FALSE;
  DCHistory = 0;
  hasPressed = FALSE;
  hasLongPress = FALSE;
  DepressedTickCount = 0;
  CheckStatusAlertEnabled = FALSE;

  GetVacuum_StubWithCallback(Stub_GetVacuum);
  isTargetTherapyDeliveryVacuumAchieved_StubWithCallback(Stub_isTargetTherapyDeliveryVacuumAchieved);
  PushButton_IsPressed_StubWithCallback(StubPushButton_IsPressed);
  PushButton_IsLongPress_StubWithCallback(StubPushButton_IsLongPress);
  PushButton_GetDepressedTickCount_StubWithCallback(Stub_PushButton_GetDepressedTickCount);
  DeviceStatus_GetCheckStatusAlert_StubWithCallback(Stub_DeviceStatus_GetCheckStatusAlert);
  DeviceStatus_SetCheckStatusAlert_StubWithCallback(Stub_DeviceStatus_SetCheckStatusAlert);
  DeviceStatus_SetPressureSensorIsReading_StubWithCallback(Stub_DeviceStatus_SetPressureSensorIsReading);
}

void tearDown(void)
{}

// TherapyDelivery initialises the various variable used within the state (e.g. timer, etc.)
void test_InitialiseInternalVariablesAndReturnOk(void)
{
  InitTherapyDeliveryVacuum_Expect();
  DCHistoryReset_Expect();

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery_Init());
}

// Therapy Delivery can handle a wrong input parameter for the "new state" variable
void test_InvalidParameterForDeliveryTherapyStateFunctionThatReurnsAnError(void)
{
  TherapyDelivery(FALSE, NULL);
  TEST_FAIL_MESSAGE("Assert should be called prior to this function");
}

// Switch off the device when in Therapy Delivery
void test_TherapyDeliveryStateReturnsInvalidInputParameter(void)
{
  hasPressed = TRUE;
  hasLongPress = TRUE;
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, new_state);
}


// Therapy Delivery state is run for the first time moving from a different state.
// Check timers and duty cycle history are initialised
void test_TherapyDeliveryOnEntryFromDifferntState(void)
{

  // Run for the first time, detect the button has not been pressed from LEAK,
  // reset the push button events
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  InitTherapyDeliveryVacuum_Expect();
  DCHistoryReset_Expect();
  DeviceStatus_GetButtonPressFromLeak_ExpectAndReturn(FALSE);
  PushButton_ResetEvent_Expect();
  DeviceStatus_GetLedsOnStatus_IgnoreAndReturn(TRUE);
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);
  State_t new_state = NONE_E;
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(TRUE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
  
  // Run for the first time, detect the button has been pressed from LEAK,
  // do not reset the push button events
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  InitTherapyDeliveryVacuum_Expect();
  DCHistoryReset_Expect();
  DeviceStatus_GetButtonPressFromLeak_ExpectAndReturn(TRUE);
  DeviceStatus_GetLedsOnStatus_IgnoreAndReturn(TRUE);
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);
  new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(TRUE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
}


// Therapy Delivery state detects there is a LEAK and goes in to FAULT state
void test_TherapyDeliveryDetectLeakAndGoIntoFault(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  // Run not for the first time, it's time to read Vacuum, but a leak is detected
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(TRUE);
  DCPumpOffUpdate_Expect();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(FAULT_E, new_state);
}

// Therapy Delivery state fails and NRE due to external preasure sensor failing to initalise  
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtInitalise(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
 
  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
}

// Therapy Delivery state fails and NRE due to external preasure sensor failing to start
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtStart(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}

// Therapy Delivery state fails and NRE due to external preasure sensor not ready
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtNotReady(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_NOT_READY_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_NOT_READY_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}

// Therapy Delivery state fails and NRE due to external preasure sensor read fail
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtReadExtReadFail(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_READ_FAILED_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_READ_FAILED_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}

// Therapy Delivery state fails and NRE due to internal preasure sensor failing to initalise  
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntInitalise(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
 
  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
}

// Therapy Delivery state fails and NRE due to internal preasure sensor failing to start
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntStart(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}

// Therapy Delivery state fails and NRE due to internal preasure sensor not ready
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntNotReady(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_NOT_READY_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_NOT_READY_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}

// Therapy Delivery state fails and NRE due to internal preasure sensor read fail
void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntReadIntReadFail(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_READ_FAILED_E);
  DeviceStatus_SetNRE_Event_Ignore();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_READ_FAILED_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}

// Therapy Delivery state detects oveheating and goes in to NRE state
void test_TherapyDeliveryDetectExternalTemperatureThreshholdAndEnterNRE(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  GetVacuum_IgnoreAndReturn(EC_EXT_TEMPERATURE_HIGH);
  DeviceStatus_SetNRE_Event_Ignore();
  
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_EXT_TEMPERATURE_HIGH, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}

// Therapy Delivery state detects oveheating and goes in to NRE state
void test_TherapyDeliveryDetectInternalTemperatureThreshholdAndEnterNRE(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_ExpectAndReturn(FALSE);
 
  GetVacuum_IgnoreAndReturn(EC_INT_TEMPERATURE_HIGH);
  DeviceStatus_SetNRE_Event_Ignore();
  DCPumpOffUpdate_Expect();

  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
 
  State_t new_state = NONE_E;
 
  TEST_ASSERT_EQUAL_INT(EC_INT_TEMPERATURE_HIGH, TherapyDelivery(FALSE, &new_state));
  //TEST_ASSERT_EQUAL_INT(NRE_INT_SENSOR_OVERHEAT_EVENT_E, DeviceStatus_GetNRE_Event());
  TEST_ASSERT_EQUAL_INT(NRE_E, new_state);
  
}


// Press the switch button and check the device indicates its status only after pressing long enough
void test_TherapyDeliveryDetectsShortButtonPressAndEnablesTheAlertsForTheDeviceStatusCheck(void)
{
  // Run not for the first time, detect the button has not been pressed
  // for long enough to indicate a therapy delivery status has to be alerted, run as normal
  hasPressed = TRUE;
  hasLongPress = FALSE;
  DepressedTickCount = 1;
  DeviceStatus_GetLedsOnStatus_IgnoreAndReturn(TRUE);
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_IgnoreAndReturn(RUNNING_COUNTER_E);
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);

  // Run and detect the button has been pressed for long enough to indicate
  // a therapy delivery status has to be alerted, run as normal
  DepressedTickCount = PUSHBUTTON_TICK_PRESSES_FOR_STATUS;
  CheckStatusAlertEnabled = FALSE;
  new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
  TEST_ASSERT_TRUE(CheckStatusAlertEnabled);

  // Run and detect the button has been pressed for long enough to indicate
  // a therapy delivery status has to be alerted, but a this event has already
  // been handled the Status flag is not being set, run as normal
  for (uint32_t i = 0; i < 20; i++)
  {
    DepressedTickCount++;
    CheckStatusAlertEnabled = FALSE;
    new_state = NONE_E;

    TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
    TEST_ASSERT_FALSE(CheckStatusAlertEnabled);
  }
}


// Press the switch button and check the device shuts down only after pressing long enough
void test_TherapyDeliveryDetectLongButtonPressAndEventuallyGoesInShutdown(void)
{
  // Run not for the first time, detect the button has not been pressed
  // for long enough to swicth the device off, run as normal
  hasPressed = TRUE;
  hasLongPress = FALSE;
  DeviceStatus_GetLedsOnStatus_IgnoreAndReturn(TRUE);
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  TimerCounter_Status_IgnoreAndReturn(RUNNING_COUNTER_E);
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);

  // Run and detect the button has been pressed for long enough
  // to swicth the device off, by pass normal operations, clean
  // up Therapy Delivery state and go into Shutdown
  hasLongPress = TRUE;
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, new_state);
}


// Therapy Delivery state read the current Vacuum, detects it is at target
// therefore the Pump is not activated the following run (update the Pump Off
// duty cycle each time after a vacuum reading)
void test_TherapyDeliveryVacuumAtTargetValueDoNotPumpOn(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  // Run not for the first time, it's time to read Vacuum, check it is at target
  // (update the Pump Off duty cycle each time after a vacuum reading)
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  VacuumAtTarget = TRUE;
  TestVacuum = THERAPY_DELIVERY_TARGET_VACUUM + THERAPY_DELIVERY_MAX_PRESSURE_OFFSET;
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);

  // Run again, it is not time to read Vacuum, but no Pump On either bacuase
  // the Vacuum was at target in the previous cycle
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);
  new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
}


// Therapy Delivery state read the current Vacuum, detects it is below target
// therefore the Pump is activated the following run (update the Pump On duty
// cycle after activating the pump)
void test_TherapyDeliveryVacuumBelowTargetValueThereforeDoPumpOn(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  // Run not for the first time, it's time to read Vacuum, check it is below target
  // (update the Pump Off duty cycle each time after a vacuum reading)
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  VacuumAtTarget = FALSE;
  TestVacuum = THERAPY_DELIVERY_TARGET_VACUUM + THERAPY_DELIVERY_MAX_PRESSURE_OFFSET;
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);

  // Run again, it is not time to read Vacuum, but do Pump On either bacuase
  // the Vacuum was below target in the previous cycle
  PumpActivate_ExpectAndReturn(TRUE, EC_OK_E);
  MP_DisableExternalPeripheralsSupply_Expect();
  DCPumpOnUpdate_Expect();
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);
  new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);

  // Run again, it is not time to read Vacuum, but no Pump On either bacuase
  // the the pump was activated in the previous cycle
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);
  new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
}


// Update the Target Vacuum every THERAPY_DELIVERY_TARGET_VACCUM_UPDATE_PERIOD_SECONDS
// This allows to increase the target vacuum to its max (currently 107 mBar) or to
// reduce it to its minimum (currently 96 mBar) depending on the air leakage, saving
// battery power but mantaining vacuum within acceptable range
void test_TherapyDeliveryUpdateTargetVacuumPeriodicallyToSaveBattery(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  for (uint32_t i = 1; i < (THERAPY_DELIVERY_TARGET_VACCUM_UPDATE_PERIOD_SECONDS * 3); i++)
  {
    PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
    TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
    DCCalculateAll_Expect();
    isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);

    // Update target vacuum periodically
    if (0 == (i % THERAPY_DELIVERY_TARGET_VACCUM_UPDATE_PERIOD_SECONDS))
    {
      TherapyDeliveryTargetVacuumUpdate_Expect();
    }

    DCPumpOffUpdate_Expect();
    TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
    TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
    VacuumAtTarget = TRUE;
    TestVacuum = THERAPY_DELIVERY_TARGET_VACUUM + THERAPY_DELIVERY_MAX_PRESSURE_OFFSET;
    State_t new_state = NONE_E;

    TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);
  }
}


// Therapy Delivery state fails to activate Pump and goes into FAULT or NRE state
// depending on the error
void test_TherapyDeliveryFailToActivatePumpAndGoToEitherFaultOrNonRecoverableError(void)
{
  DeviceStatus_SetNRE_Event_Ignore();
  ErrorCode_t pump_activate_errror = EC_OK_E;
  State_t new_error_state = NONE_E;

  for (uint32_t i = 0; i < 4; i++)
  {
    // Initialise the state and prepare for the test
    TestInit_Helper();

    // Run not for the first time, it's time to read Vacuum, check it is below target
    // (update the Pump Off duty cycle each time after a vacuum reading)
    PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
    TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
    DCCalculateAll_Expect();
    isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
    DCPumpOffUpdate_Expect();
    TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
    TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
    VacuumAtTarget = FALSE;
    TestVacuum = THERAPY_DELIVERY_TARGET_VACUUM + THERAPY_DELIVERY_MAX_PRESSURE_OFFSET;
    State_t new_state = NONE_E;

    TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, new_state);

    // Pump activation returns various errors
    switch (i)
    {
      case 0:
        pump_activate_errror = EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E;
        new_error_state = FAULT_E;
        break;
      case 1:
        pump_activate_errror = EC_VOLTAGE_OUT_OF_RANGE_E;
        new_error_state = NRE_E;
        break;
      case 2:
        pump_activate_errror = EC_BATTERY_END_OF_LIFE_E;
        new_error_state = NRE_E;
        break;
      case 3:
      default:
        pump_activate_errror = EC_FAILED_E;
        // unexpected errors will be handled by the application
        // therefore the Therapy Delivery state does not change in this case
        new_error_state = THERAPY_DELIVERY_E;
        break;
    }
    PumpActivate_ExpectAndReturn(TRUE, pump_activate_errror);
    MP_DisableExternalPeripheralsSupply_Expect();
    DCPumpOnUpdate_Expect();
    if (3 > i)
    {
      TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
    }
    new_state = NONE_E;
 
    TEST_ASSERT_EQUAL_INT(pump_activate_errror, TherapyDelivery(FALSE, &new_state));
    TEST_ASSERT_EQUAL_INT(new_error_state, new_state);
  }
}


// Therapy Delivery state detects external pressure is higher that first read so 
// leak is entered 
void test_TherapyDeliveryDetectHighExternalPressureAndGoIntoFault(void)
{
  // Initialise the state and prepare for the test
  TestInit_Helper();

  // Make external prssure higher than the first read 
  ExternalPressureForNRVBlockage = 200;
  TestExternal = 300;

  // Run not for the first time, it's time to read Vacuum, but a leak is detected
  PumpActivate_ExpectAndReturn(FALSE, EC_OK_E);
  TimerCounter_Status_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);
  DCCalculateAll_Expect();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  DCPumpOffUpdate_Expect();
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  TimerCounter_Start_ExpectAndReturn(STATE_MACHINE_COUNTER_E, DUTY_CYCLE_UPDATE_TICK_DURATION, EC_OK_E);
  TimerCounter_Disable_ExpectAndReturn(STATE_MACHINE_COUNTER_E, EC_OK_E);
  State_t new_state = NONE_E;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, TherapyDelivery(FALSE, &new_state));
  TEST_ASSERT_EQUAL_INT(FAULT_E, new_state);
}

