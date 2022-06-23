#include "MockPerformanceLogger.h"
#include "Assert.h"
#include "MockStateMachineCommon.h"
#include "MockDeviceStatus.h"
#include "MockDutyCycle.h"
#include "MockPowerControl.h"
#include "MockPressure_Part3.h"
#include "MockPressure_Part1.h"
#include "MockPushButton.h"
#include "MockPump.h"
#include "MockTimer.h"
#include "StateMachineTherapyDelivery.h"
#include "unity.h"






static uint16_t TestInternal = 0;

static uint16_t TestExternal = 0;

static uint16_t TestVacuum = 0;

static uint32_t GetVacuumCalls = 0;

static bool_t GetVacuumForceFail = (bool_t) 

                                  0

                                       ;

static uint8_t DCHistory = 0;

static bool_t VacuumAtTarget = (bool_t) 

                              0

                                   ;

static bool_t hasPressed;

static bool_t hasLongPress;

static uint8_t DepressedTickCount = 0;

static bool_t CheckStatusAlertEnabled = (bool_t) 

                                       0

                                            ;

static bool_t isPressureSensorReading = (bool_t) 

                                       0

                                            ;







uint16_t ExternalPressureForNRVBlockage = 0;





static void TestInit_Helper(void)

{



  InitTherapyDeliveryVacuum_CMockExpect(55);

  DCHistoryReset_CMockExpect(56);

  TherapyDelivery_Init();





  DeviceStatus_GetLedsOnStatus_CMockIgnoreAndReturn(60, (bool_t) 

 1

 );

}







static ErrorCode_t Stub_GetVacuum(uint16_t* pInternal, uint16_t* pExternal, uint16_t* pVacuum, int NumCalls)

{

  ErrorCode_t result = EC_OK_E;



  GetVacuumCalls++;



  if((bool_t) 

    1 

         == GetVacuumForceFail)

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

  GetVacuumForceFail = (bool_t) 

                      0

                           ;

  DCHistory = 0;

  hasPressed = (bool_t) 

              0

                   ;

  hasLongPress = (bool_t) 

                0

                     ;

  DepressedTickCount = 0;

  CheckStatusAlertEnabled = (bool_t) 

                           0

                                ;



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





void test_InitialiseInternalVariablesAndReturnOk(void)

{

  InitTherapyDeliveryVacuum_CMockExpect(148);

  DCHistoryReset_CMockExpect(149);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery_Init())), (

 ((void *)0)

 ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);

}





void test_InvalidParameterForDeliveryTherapyStateFunctionThatReurnsAnError(void)

{

  TherapyDelivery((bool_t) 

                 0

                      , 

                        ((void *)0)

                            );

  UnityFail( (("Assert should be called prior to this function")), (_U_UINT)(158));

}





void test_TherapyDeliveryStateReturnsInvalidInputParameter(void)

{

  hasPressed = (bool_t) 

              1

                  ;

  hasLongPress = (bool_t) 

                1

                    ;

  TimerCounter_Disable_CMockExpectAndReturn(166, STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(170), UNITY_DISPLAY_STYLE_INT);

}









void test_TherapyDeliveryOnEntryFromDifferntState(void)

{







  TimerCounter_Disable_CMockExpectAndReturn(181, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(182, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  InitTherapyDeliveryVacuum_CMockExpect(183);

  DCHistoryReset_CMockExpect(184);

  DeviceStatus_GetButtonPressFromLeak_CMockExpectAndReturn(185, (bool_t) 

 0

 );

  PushButton_ResetEvent_CMockExpect(186);

  DeviceStatus_GetLedsOnStatus_CMockIgnoreAndReturn(187, (bool_t) 

 1

 );

  PumpActivate_CMockExpectAndReturn(188, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(189, STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 1

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(192), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);







  TimerCounter_Disable_CMockExpectAndReturn(197, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(198, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  InitTherapyDeliveryVacuum_CMockExpect(199);

  DCHistoryReset_CMockExpect(200);

  DeviceStatus_GetButtonPressFromLeak_CMockExpectAndReturn(201, (bool_t) 

 1

 );

  DeviceStatus_GetLedsOnStatus_CMockIgnoreAndReturn(202, (bool_t) 

 1

 );

  PumpActivate_CMockExpectAndReturn(203, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(204, STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 1

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(207), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(208), UNITY_DISPLAY_STYLE_INT);

}







void test_TherapyDeliveryDetectLeakAndGoIntoFault(void)

{



  TestInit_Helper();





  PumpActivate_CMockExpectAndReturn(219, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(220, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(221);

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(222, (bool_t) 

 1

 );

  DCPumpOffUpdate_CMockExpect(223);

  TimerCounter_Disable_CMockExpectAndReturn(224, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(225, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(226, STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(229), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(230), UNITY_DISPLAY_STYLE_INT);

}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtInitalise(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(239, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(240, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(241);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(242, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(243);

  GetVacuum_CMockIgnoreAndReturn(244, EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(246, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(247, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(248, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(251), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(252), UNITY_DISPLAY_STYLE_INT);

}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtStart(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(261, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(262, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(263);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(264, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(265);

  GetVacuum_CMockIgnoreAndReturn(266, EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(268, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(269, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(270, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(273), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);



}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtNotReady(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(284, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(285, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(286);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(287, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(288);

  GetVacuum_CMockIgnoreAndReturn(289, EC_EXT_PRESSURE_SENSOR_NOT_READY_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(291, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(292, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(293, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_NOT_READY_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(296), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(297), UNITY_DISPLAY_STYLE_INT);



}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsExtReadExtReadFail(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(307, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(308, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(309);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(310, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(311);

  GetVacuum_CMockIgnoreAndReturn(312, EC_EXT_PRESSURE_SENSOR_READ_FAILED_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(314, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(315, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(316, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_READ_FAILED_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(319), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(320), UNITY_DISPLAY_STYLE_INT);



}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntInitalise(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(330, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(331, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(332);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(333, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(334);

  GetVacuum_CMockIgnoreAndReturn(335, EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(337, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(338, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(339, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(342), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(343), UNITY_DISPLAY_STYLE_INT);

}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntStart(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(352, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(353, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(354);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(355, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(356);

  GetVacuum_CMockIgnoreAndReturn(357, EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(359, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(360, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(361, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(364), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(365), UNITY_DISPLAY_STYLE_INT);



}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntNotReady(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(375, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(376, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(377);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(378, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(379);

  GetVacuum_CMockIgnoreAndReturn(380, EC_INT_PRESSURE_SENSOR_NOT_READY_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(382, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(383, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(384, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_NOT_READY_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(387), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(388), UNITY_DISPLAY_STYLE_INT);



}





void test_TherapyDeliveryStopAndEnterNREWhenReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsIntReadIntReadFail(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(398, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(399, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(400);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(401, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(402);

  GetVacuum_CMockIgnoreAndReturn(403, EC_INT_PRESSURE_SENSOR_READ_FAILED_E);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  TimerCounter_Disable_CMockExpectAndReturn(405, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(406, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(407, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_READ_FAILED_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(410), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(411), UNITY_DISPLAY_STYLE_INT);



}





void test_TherapyDeliveryDetectExternalTemperatureThreshholdAndEnterNRE(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(421, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(422, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(423);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(424, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(425);

  GetVacuum_CMockIgnoreAndReturn(426, EC_EXT_TEMPERATURE_HIGH);

  DeviceStatus_SetNRE_Event_CMockIgnore();



  TimerCounter_Disable_CMockExpectAndReturn(429, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(430, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(431, STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_EXT_TEMPERATURE_HIGH)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(434), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(435), UNITY_DISPLAY_STYLE_INT);



}





void test_TherapyDeliveryDetectInternalTemperatureThreshholdAndEnterNRE(void)

{



  TestInit_Helper();



  PumpActivate_CMockIgnoreAndReturn(445, EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(446, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(447);

  isTherapyDeliveryLeakDetected_CMockExpectAndReturn(448, (bool_t) 

 0

 );



  GetVacuum_CMockIgnoreAndReturn(450, EC_INT_TEMPERATURE_HIGH);

  DeviceStatus_SetNRE_Event_CMockIgnore();

  DCPumpOffUpdate_CMockExpect(452);



  TimerCounter_Disable_CMockExpectAndReturn(454, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(455, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(456, STATE_MACHINE_COUNTER_E, EC_OK_E);



  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_INT_TEMPERATURE_HIGH)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(460), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(462), UNITY_DISPLAY_STYLE_INT);



}







void test_TherapyDeliveryDetectsShortButtonPressAndEnablesTheAlertsForTheDeviceStatusCheck(void)

{





  hasPressed = (bool_t) 

              1

                  ;

  hasLongPress = (bool_t) 

                0

                     ;

  DepressedTickCount = 1;

  DeviceStatus_GetLedsOnStatus_CMockIgnoreAndReturn(475, (bool_t) 

 1

 );

  PumpActivate_CMockIgnoreAndReturn(476, EC_OK_E);

  TimerCounter_Status_CMockIgnoreAndReturn(477, RUNNING_COUNTER_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(480), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(481), UNITY_DISPLAY_STYLE_INT);







  DepressedTickCount = (2);

  CheckStatusAlertEnabled = (bool_t) 

                           0

                                ;

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(489), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(490), UNITY_DISPLAY_STYLE_INT);

  if ((CheckStatusAlertEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(491)));};









  for (uint32_t i = 0; i < 20; i++)

  {

    DepressedTickCount++;

    CheckStatusAlertEnabled = (bool_t) 

                             0

                                  ;

    new_state = NONE_E;



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

   0

   , &new_state))), (

   ((void *)0)

   ), (_U_UINT)(502), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

   ((void *)0)

   ), (_U_UINT)(503), UNITY_DISPLAY_STYLE_INT);

    if (!(CheckStatusAlertEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(504)));};

  }

}







void test_TherapyDeliveryDetectLongButtonPressAndEventuallyGoesInShutdown(void)

{





  hasPressed = (bool_t) 

              1

                  ;

  hasLongPress = (bool_t) 

                0

                     ;

  DeviceStatus_GetLedsOnStatus_CMockIgnoreAndReturn(516, (bool_t) 

 1

 );

  PumpActivate_CMockIgnoreAndReturn(517, EC_OK_E);

  TimerCounter_Status_CMockIgnoreAndReturn(518, RUNNING_COUNTER_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(521), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(522), UNITY_DISPLAY_STYLE_INT);









  hasLongPress = (bool_t) 

                1

                    ;

  TimerCounter_Disable_CMockExpectAndReturn(528, STATE_MACHINE_COUNTER_E, EC_OK_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(531), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(532), UNITY_DISPLAY_STYLE_INT);

}











void test_TherapyDeliveryVacuumAtTargetValueDoNotPumpOn(void)

{



  TestInit_Helper();







  PumpActivate_CMockExpectAndReturn(546, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(547, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(548);

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(549, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(550);

  TimerCounter_Disable_CMockExpectAndReturn(551, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(552, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  VacuumAtTarget = (bool_t) 

                  1

                      ;

  TestVacuum = (96) + (11);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(557), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(558), UNITY_DISPLAY_STYLE_INT);







  PumpActivate_CMockExpectAndReturn(562, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(563, STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(566), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(567), UNITY_DISPLAY_STYLE_INT);

}











void test_TherapyDeliveryVacuumBelowTargetValueThereforeDoPumpOn(void)

{



  TestInit_Helper();







  PumpActivate_CMockExpectAndReturn(581, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(582, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(583);

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(584, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(585);

  TimerCounter_Disable_CMockExpectAndReturn(586, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(587, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  VacuumAtTarget = (bool_t) 

                  0

                       ;

  TestVacuum = (96) + (11);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(592), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(593), UNITY_DISPLAY_STYLE_INT);







  PumpActivate_CMockExpectAndReturn(597, (bool_t) 

 1

 , EC_OK_E);

  MP_DisableExternalPeripheralsSupply_CMockExpect(598);

  DCPumpOnUpdate_CMockExpect(599);

  TimerCounter_Status_CMockExpectAndReturn(600, STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(603), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(604), UNITY_DISPLAY_STYLE_INT);







  PumpActivate_CMockExpectAndReturn(608, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(609, STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(612), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(613), UNITY_DISPLAY_STYLE_INT);

}













void test_TherapyDeliveryUpdateTargetVacuumPeriodicallyToSaveBattery(void)

{



  TestInit_Helper();



  for (uint32_t i = 1; i < ((9) * 3); i++)

  {

    PumpActivate_CMockExpectAndReturn(628, (bool_t) 

   0

   , EC_OK_E);

    TimerCounter_Status_CMockExpectAndReturn(629, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

    DCCalculateAll_CMockExpect(630);

    isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(631, (bool_t) 

   0

   );





    if (0 == (i % (9)))

    {

      TherapyDeliveryTargetVacuumUpdate_CMockExpect(636);

    }



    DCPumpOffUpdate_CMockExpect(639);

    TimerCounter_Disable_CMockExpectAndReturn(640, STATE_MACHINE_COUNTER_E, EC_OK_E);

    TimerCounter_Start_CMockExpectAndReturn(641, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

    VacuumAtTarget = (bool_t) 

                    1

                        ;

    TestVacuum = (96) + (11);

    State_t new_state = NONE_E;



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

   0

   , &new_state))), (

   ((void *)0)

   ), (_U_UINT)(646), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

   ((void *)0)

   ), (_U_UINT)(647), UNITY_DISPLAY_STYLE_INT);

  }

}









void test_TherapyDeliveryFailToActivatePumpAndGoToEitherFaultOrNonRecoverableError(void)

{

  DeviceStatus_SetNRE_Event_CMockIgnore();

  ErrorCode_t pump_activate_errror = EC_OK_E;

  State_t new_error_state = NONE_E;



  for (uint32_t i = 0; i < 4; i++)

  {



    TestInit_Helper();







    PumpActivate_CMockExpectAndReturn(667, (bool_t) 

   0

   , EC_OK_E);

    TimerCounter_Status_CMockExpectAndReturn(668, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

    DCCalculateAll_CMockExpect(669);

    isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(670, (bool_t) 

   0

   );

    DCPumpOffUpdate_CMockExpect(671);

    TimerCounter_Disable_CMockExpectAndReturn(672, STATE_MACHINE_COUNTER_E, EC_OK_E);

    TimerCounter_Start_CMockExpectAndReturn(673, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

    VacuumAtTarget = (bool_t) 

                    0

                         ;

    TestVacuum = (96) + (11);

    State_t new_state = NONE_E;



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

   0

   , &new_state))), (

   ((void *)0)

   ), (_U_UINT)(678), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

   ((void *)0)

   ), (_U_UINT)(679), UNITY_DISPLAY_STYLE_INT);





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





        new_error_state = THERAPY_DELIVERY_E;

        break;

    }

    PumpActivate_CMockExpectAndReturn(704, (bool_t) 

   1

   , pump_activate_errror);

    MP_DisableExternalPeripheralsSupply_CMockExpect(705);

    DCPumpOnUpdate_CMockExpect(706);

    if (3 > i)

    {

      TimerCounter_Disable_CMockExpectAndReturn(709, STATE_MACHINE_COUNTER_E, EC_OK_E);

    }

    new_state = NONE_E;



    UnityAssertEqualNumber((_U_SINT)((pump_activate_errror)), (_U_SINT)((TherapyDelivery((bool_t) 

   0

   , &new_state))), (

   ((void *)0)

   ), (_U_UINT)(713), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((new_error_state)), (_U_SINT)((new_state)), (

   ((void *)0)

   ), (_U_UINT)(714), UNITY_DISPLAY_STYLE_INT);

  }

}









void test_TherapyDeliveryDetectHighExternalPressureAndGoIntoFault(void)

{



  TestInit_Helper();





  ExternalPressureForNRVBlockage = 200;

  TestExternal = 300;





  PumpActivate_CMockExpectAndReturn(731, (bool_t) 

 0

 , EC_OK_E);

  TimerCounter_Status_CMockExpectAndReturn(732, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  DCCalculateAll_CMockExpect(733);

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(734, (bool_t) 

 0

 );

  DCPumpOffUpdate_CMockExpect(735);

  TimerCounter_Disable_CMockExpectAndReturn(736, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(737, STATE_MACHINE_COUNTER_E, (10), EC_OK_E);

  TimerCounter_Disable_CMockExpectAndReturn(738, STATE_MACHINE_COUNTER_E, EC_OK_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((TherapyDelivery((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(741), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(742), UNITY_DISPLAY_STYLE_INT);

}
