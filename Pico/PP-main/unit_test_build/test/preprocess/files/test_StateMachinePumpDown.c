#include "Assert.h"
#include "MockPerformanceLogger.h"
#include "MockPushButton.h"
#include "MockStateMachineCommon.h"
#include "MockPowerControl.h"
#include "MockUIInterfaces.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockTimer.h"
#include "DeviceStatus.h"
#include "StateMachinePumpDown.h"
#include "unity.h"








static uint16_t TestInternal = 0;

static uint16_t TestExternal = 0;

static uint16_t TestVacuum = 0;

static uint32_t GetVacuumCalls = 0;

static bool_t GetVacuumForceFail = (bool_t) 

                                  0

                                       ;

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



static void Stub_PerformanceLogger_SetPumpDownDuration(const uint8_t duration100Ms, int NumCalls)

{

  PumpDownDuration = duration100Ms;

}





void setUp(void)

{

  TestVacuum = 0;

  GetVacuumCalls = 0;

  GetVacuumForceFail = (bool_t) 

                      0

                           ;

  GetVacuum_StubWithCallback(Stub_GetVacuum);

  PushButton_IsPressed_StubWithCallback(StubPushButton_IsPressed);

  PushButton_IsLongPress_StubWithCallback(StubPushButton_IsLongPress);

  PerformanceLogger_SetPumpDownDuration_StubWithCallback(Stub_PerformanceLogger_SetPumpDownDuration);



  hasPressed = (bool_t) 

              0

                   ;

  hasLongPress = (bool_t) 

                0

                     ;



}



void tearDown(void)

{}





void test_OnInitDisableStateTimerInitialiseStateVacuumAndReurnOk(void)

{

  TimerCounter_Disable_CMockExpectAndReturn(102, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(103);



  ErrorCode_t errorCode = PumpDown_Init();

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((errorCode)), (

 ((void *)0)

 ), (_U_UINT)(106), UNITY_DISPLAY_STYLE_INT);

}





void test_PumpDownStateReturnsInvalidInputParameter(void)

{

  PumpDown((bool_t) 

          0

               , 

                 ((void *)0)

                     );

  UnityFail( (("Assert should be called prior to this function")), (_U_UINT)(113));

}

void test_PumpDownRunsUntilReachingTargetVacuumWithVacuumReadAndPumpActivateAlternating(void)

{



  PushButton_ResetEvent_CMockIgnore();

  UI_IsPushButtonPressed_CMockIgnoreAndReturn(129, (bool_t) 

 0

 );

  TimerCounter_Disable_CMockExpectAndReturn(130, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(131, STATE_MACHINE_COUNTER_E, (200), EC_OK_E);

  InitPumpDownVacuum_CMockExpect(132);



  TimerCounter_GetTimeout_CMockExpectAndReturn(134, STATE_MACHINE_COUNTER_E, 200);

  PumpActivate_CMockExpectAndReturn(135, (bool_t) 

 0

 , EC_OK_E);

  TestVacuum = 200;

  isTargetPumpDownVacuumAchieved_CMockExpectAndReturn(137, TestVacuum, (bool_t) 

 0

 );

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 1

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(140), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(141), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(142), UNITY_DISPLAY_STYLE_INT);







  TimerCounter_GetTimeout_CMockExpectAndReturn(146, STATE_MACHINE_COUNTER_E, 140);

  PumpActivate_CMockExpectAndReturn(147, (bool_t) 

 1

 , EC_OK_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);





  TimerCounter_GetTimeout_CMockExpectAndReturn(155, STATE_MACHINE_COUNTER_E, 50);

  PumpActivate_CMockExpectAndReturn(156, (bool_t) 

 0

 , EC_OK_E);

  TestVacuum = 200;

  isTargetPumpDownVacuumAchieved_CMockExpectAndReturn(158, TestVacuum, (bool_t) 

 1

 );

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(163), UNITY_DISPLAY_STYLE_INT);





  TimerCounter_GetTimeout_CMockExpectAndReturn(166, STATE_MACHINE_COUNTER_E, 0);

  TestVacuum = (107);

  TimerCounter_Disable_CMockExpectAndReturn(168, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(169);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(173), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(174), UNITY_DISPLAY_STYLE_INT);

}





void test_PumpDownDurationUpdatedWithPerformanceLogger(void)

{

  test_PumpDownRunsUntilReachingTargetVacuumWithVacuumReadAndPumpActivateAlternating();

  UnityAssertEqualNumber((_U_SINT)((150)), (_U_SINT)((PumpDownDuration)), (

 ((void *)0)

 ), (_U_UINT)(181), UNITY_DISPLAY_STYLE_INT);

}

void test_PumpDownRunsFor20SecondWhenPressureReachedButOutwith5SecondWindow(void)

{



  PushButton_ResetEvent_CMockIgnore();

  UI_IsPushButtonPressed_CMockIgnoreAndReturn(200, (bool_t) 

 0

 );

  TimerCounter_Disable_CMockExpectAndReturn(201, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(202, STATE_MACHINE_COUNTER_E, (200), EC_OK_E);

  InitPumpDownVacuum_CMockExpect(203);



  TimerCounter_GetTimeout_CMockExpectAndReturn(205, STATE_MACHINE_COUNTER_E, 200);

  PumpActivate_CMockExpectAndReturn(206, (bool_t) 

 0

 , EC_OK_E);

  TestVacuum = 200;

  isTargetPumpDownVacuumAchieved_CMockExpectAndReturn(208, TestVacuum, (bool_t) 

 0

 );

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 1

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(211), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(212), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(213), UNITY_DISPLAY_STYLE_INT);







  TimerCounter_GetTimeout_CMockExpectAndReturn(217, STATE_MACHINE_COUNTER_E, 140);

  PumpActivate_CMockExpectAndReturn(218, (bool_t) 

 1

 , EC_OK_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(222), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);







  TimerCounter_GetTimeout_CMockExpectAndReturn(227, STATE_MACHINE_COUNTER_E, 51);

  PumpActivate_CMockExpectAndReturn(228, (bool_t) 

 0

 , EC_OK_E);

  TestVacuum = 200;

  isTargetPumpDownVacuumAchieved_CMockExpectAndReturn(230, TestVacuum, (bool_t) 

 1

 );

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(233), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(234), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(235), UNITY_DISPLAY_STYLE_INT);





  TimerCounter_GetTimeout_CMockExpectAndReturn(238, STATE_MACHINE_COUNTER_E, 0);

  TestVacuum = (107);

  TimerCounter_Disable_CMockExpectAndReturn(240, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(241);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(244), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(245), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(246), UNITY_DISPLAY_STYLE_INT);

}







void test_PumpDownRunsCannotReachTargetVacuum(void)

{



  UI_IsPushButtonPressed_CMockIgnoreAndReturn(254, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(255, STATE_MACHINE_COUNTER_E, 0);

  TimerCounter_Disable_CMockExpectAndReturn(256, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(257);

  State_t new_state = NONE_E;





  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(261), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(262), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);

  if (!(DeviceStatus_IsReadingPressureSensor())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(264)));};

}











void test_PumpDownFailsToTakeVacuumReadingAndReturnsError(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(274, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(275);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(279, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(280, STATE_MACHINE_COUNTER_E, 1);

   PumpActivate_CMockIgnoreAndReturn(281, EC_OK_E);

   GetVacuumForceFail = (bool_t) 

                       1

                           ;

   State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(285, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(286);

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_READ_FAILED_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(287), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(288), UNITY_DISPLAY_STYLE_INT);

}







void test_PumpDownDetectButtonPressAndEventuallyGoesInShutdown(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(296, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(297);

  PumpDown_Init();







  hasPressed = (bool_t) 

              1

                  ;

  hasLongPress = (bool_t) 

                0

                     ;



  TimerCounter_GetTimeout_CMockExpectAndReturn(305, STATE_MACHINE_COUNTER_E, 1);

  isTargetPumpDownVacuumAchieved_CMockIgnoreAndReturn(306, (bool_t) 

 0

 );

  PumpActivate_CMockIgnoreAndReturn(307, EC_OK_E);

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(310), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(311), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(312), UNITY_DISPLAY_STYLE_INT);

  if ((DeviceStatus_IsReadingPressureSensor())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(313)));};











  hasLongPress = (bool_t) 

                1

                    ;

  TimerCounter_Disable_CMockExpectAndReturn(320, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(321);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(324), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(325), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(326), UNITY_DISPLAY_STYLE_INT);

  if (!(DeviceStatus_IsReadingPressureSensor())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(327)));};



}

void test_PumpDownRunsButExternalPressureIncreasesCausingNoneReturnValveError(void)

{



  PushButton_ResetEvent_CMockIgnore();

  UI_IsPushButtonPressed_CMockIgnoreAndReturn(347, (bool_t) 

 0

 );

  TimerCounter_Disable_CMockExpectAndReturn(348, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(349, STATE_MACHINE_COUNTER_E, (200), EC_OK_E);

  InitPumpDownVacuum_CMockExpect(350);



  TimerCounter_GetTimeout_CMockExpectAndReturn(352, STATE_MACHINE_COUNTER_E, 200);

  PumpActivate_CMockExpectAndReturn(353, (bool_t) 

 0

 , EC_OK_E);

  TestVacuum = 200;

  TestExternal = 200;

  isTargetPumpDownVacuumAchieved_CMockExpectAndReturn(356, TestVacuum, (bool_t) 

 0

 );

  State_t new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 1

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(359), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(360), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(361), UNITY_DISPLAY_STYLE_INT);







  TimerCounter_GetTimeout_CMockExpectAndReturn(365, STATE_MACHINE_COUNTER_E, 140);

  PumpActivate_CMockExpectAndReturn(366, (bool_t) 

 1

 , EC_OK_E);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(369), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(370), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(371), UNITY_DISPLAY_STYLE_INT);









  TimerCounter_GetTimeout_CMockExpectAndReturn(376, STATE_MACHINE_COUNTER_E, 51);

  PumpActivate_CMockExpectAndReturn(377, (bool_t) 

 0

 , EC_OK_E);

  TestVacuum = 200;

  TestExternal = 300;

  TimerCounter_Disable_CMockExpectAndReturn(380, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(381);

  new_state = NONE_E;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(384), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((new_state)), (

 ((void *)0)

 ), (_U_UINT)(386), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((GetVacuumCalls)), (

 ((void *)0)

 ), (_U_UINT)(387), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningDetectsExternalOverTemperatureEventAndEntersNRE(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(394, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(395);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(399, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(400, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(401, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(402, EC_EXT_TEMPERATURE_HIGH);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(407, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(408);



  UnityAssertEqualNumber((_U_SINT)((EC_EXT_TEMPERATURE_HIGH)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(410), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_EXT_SENSOR_OVERHEAT_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(411), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningDetectsInternalOverTemperatureEventAndEntersNRE(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(418, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(419);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(423, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(424, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(425, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(426, EC_INT_TEMPERATURE_HIGH);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(431, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(432);

  UnityAssertEqualNumber((_U_SINT)((EC_INT_TEMPERATURE_HIGH)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(433), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_INT_SENSOR_OVERHEAT_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(434), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntInitalise(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(441, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(442);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(446, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(447, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(448, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(449, EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(454, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(455);

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(456), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_INT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(457), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntStart(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(464, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(465);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(469, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(470, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(471, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(472, EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(477, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(478);

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(479), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_INT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(480), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntNotReady(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(487, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(488);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(492, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(493, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(494, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(495, EC_INT_PRESSURE_SENSOR_NOT_READY_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(500, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(501);

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_NOT_READY_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(502), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_INT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(503), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntReadFailed(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(510, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(511);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(515, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(516, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(517, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(518, EC_INT_PRESSURE_SENSOR_READ_FAILED_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(523, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(524);

  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_READ_FAILED_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(525), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_INT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(526), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtInitalise(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(533, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(534);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(538, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(539, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(540, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(541, EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(546, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(547);

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(548), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_EXT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(549), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtStart(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(556, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(557);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(561, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(562, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(563, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(564, EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(569, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(570);

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(571), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_EXT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(572), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtNotReady(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(579, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(580);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(584, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(585, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(586, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(587, EC_EXT_PRESSURE_SENSOR_NOT_READY_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(592, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(593);

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_NOT_READY_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(594), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_EXT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(595), UNITY_DISPLAY_STYLE_INT);



}



void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtReadFailed(void)

{



  TimerCounter_Disable_CMockExpectAndReturn(602, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(603);

  PumpDown_Init();





  UI_IsPushButtonPressed_CMockIgnoreAndReturn(607, (bool_t) 

 0

 );

  TimerCounter_GetTimeout_CMockExpectAndReturn(608, STATE_MACHINE_COUNTER_E, 1);

  PumpActivate_CMockIgnoreAndReturn(609, EC_OK_E);

  GetVacuum_CMockIgnoreAndReturn(610, EC_EXT_PRESSURE_SENSOR_READ_FAILED_E);

  DeviceStatus_GetNRE_Event();

  GetVacuumForceFail = (bool_t) 

                      1

                          ;

  State_t new_state = NONE_E;



  TimerCounter_Disable_CMockExpectAndReturn(615, STATE_MACHINE_COUNTER_E, EC_OK_E);

  InitPumpDownVacuum_CMockExpect(616);

  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_READ_FAILED_E)), (_U_SINT)((PumpDown((bool_t) 

 0

 , &new_state))), (

 ((void *)0)

 ), (_U_UINT)(617), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_EXT_SENSOR_UNRELIABLE_EVENT_E)), (_U_SINT)((DeviceStatus_GetNRE_Event())), (

 ((void *)0)

 ), (_U_UINT)(618), UNITY_DISPLAY_STYLE_INT);



}
