#include "DeviceStatus.h"
#include "Assert.h"
#include "MockHardwareInterface.h"
#include "MockStateMachineCommon.h"
#include "MockPressure_Part1.h"
#include "MockTimer.h"
#include "MockPowerControl.h"
#include "MockPushButton.h"
#include "StateMachineIdle.h"
#include "unity.h"




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



  hasPressed = (bool_t) 

              0

                   ;

  hasShortPress = (bool_t) 

                 0

                      ;

}



void tearDown(void)

{}



void test_OnInitClearSystemTimerReferenceReturnOk(void)

{

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Idle_Init())), (

 ((void *)0)

 ), (_U_UINT)(56), UNITY_DISPLAY_STYLE_INT);

}



void test_IdleCheckStateReturnsInvalidParameter(void)

{

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((Idle((bool_t) 

 0

 , 

 ((void *)0)

 ))), (

 ((void *)0)

 ), (_U_UINT)(61), UNITY_DISPLAY_STYLE_INT);

  UnityFail( (("Code should be asserted and this function should not be called")), (_U_UINT)(62));

}



void test_OnEntryInitialiseUIAndPowerSettingAndWhenSwitchIsNotPressedGoToIdle(void)

{



  MP_DisablePeripheral_CMockIgnore();

  TimerCounter_Status_CMockIgnoreAndReturn(69, RUNNING_COUNTER_E);



  TimerCounter_Disable_CMockExpectAndReturn(71, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(72, STATE_MACHINE_COUNTER_E, 10*60*60, EC_OK_E);

  MP_SetReferenceVoltageBoost_CMockExpect(73, (0));

  MP_DisablePumpPWM_CMockExpect(74);

  MP_DisableExternalPeripheralsSupply_CMockExpect(75);

  MP_DisableMainCircuitPower_CMockExpect(76);

  SetInitialExternalPressure_CMockExpect(77, 0);

  PushButton_ResetEvent_CMockExpect(78);





  State_t nextState = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Idle((bool_t) 

 1

 , &nextState))), (

 ((void *)0)

 ), (_U_UINT)(82), UNITY_DISPLAY_STYLE_INT);





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((nextState)), (

 ((void *)0)

 ), (_U_UINT)(85), UNITY_DISPLAY_STYLE_INT);

}



void test_IdleStateRunsWhenSwitchIsPressedNotLongEnoughToSwitchOnAndStayInIdle(void)

{

  TimerCounter_Status_CMockIgnoreAndReturn(90, RUNNING_COUNTER_E);



  hasPressed = (bool_t) 

              1

                  ;



  State_t nextState = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Idle((bool_t) 

 0

 , &nextState))), (

 ((void *)0)

 ), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((nextState)), (

 ((void *)0)

 ), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);





  hasPressed = (bool_t) 

              1

                  ;



  nextState = NONE_E;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Idle((bool_t) 

 0

 , &nextState))), (

 ((void *)0)

 ), (_U_UINT)(102), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((nextState)), (

 ((void *)0)

 ), (_U_UINT)(103), UNITY_DISPLAY_STYLE_INT);

}





void test_IdleStateRunsWhenSwitchIsPressedLongEnoughToGoIntoPumpDown(void)

{



  hasPressed = (bool_t) 

              1

                  ;

  hasShortPress = (bool_t) 

                 1

                     ;





  State_t nextState = NONE_E;

  HardwareInterface_SystemInitialise_CMockExpect(115);

  TimerCounter_Disable_CMockExpectAndReturn(116, STATE_MACHINE_COUNTER_E, EC_OK_E);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Idle((bool_t) 

 0

 , &nextState))), (

 ((void *)0)

 ), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((nextState)), (

 ((void *)0)

 ), (_U_UINT)(118), UNITY_DISPLAY_STYLE_INT);

}



void test_OnRunIfPushButtonIsNotPressedDisablePeripheral(void)

{

  hasPressed = (bool_t) 

              0

                   ;

  TimerCounter_Status_CMockIgnoreAndReturn(124, RUNNING_COUNTER_E);



  MP_DisablePeripheral_CMockExpect(126);



  State_t nextState = NONE_E;

  Idle((bool_t) 

      0

           , &nextState);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((nextState)), (

 ((void *)0)

 ), (_U_UINT)(130), UNITY_DISPLAY_STYLE_INT);

}



void test_IfTimerExpireGoToIPDEvenIfNoButtonIsPressed(void)

{

  hasPressed = (bool_t) 

              0

                   ;

  hasShortPress = (bool_t) 

                 0

                      ;

  MP_DisablePeripheral_CMockIgnore();





  TimerCounter_Status_CMockExpectAndReturn(140, STATE_MACHINE_COUNTER_E, RUNNING_COUNTER_E);

  State_t nextState = NONE_E;

  Idle((bool_t) 

      0

           , &nextState);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((nextState)), (

 ((void *)0)

 ), (_U_UINT)(143), UNITY_DISPLAY_STYLE_INT);





  TimerCounter_Status_CMockExpectAndReturn(146, STATE_MACHINE_COUNTER_E, EXPIRED_COUNTER_E);

  nextState = NONE_E;



  HardwareInterface_SystemInitialise_CMockExpect(149);

  TimerCounter_Disable_CMockExpectAndReturn(150, STATE_MACHINE_COUNTER_E, EC_OK_E);

  Idle((bool_t) 

      0

           , &nextState);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((nextState)), (

 ((void *)0)

 ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);



}
