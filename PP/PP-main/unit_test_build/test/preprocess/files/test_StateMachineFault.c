#include "Assert.h"
#include "MockPerformanceLogger.h"
#include "Mockadc.h"
#include "MockBattery.h"
#include "DeviceStatus.h"
#include "MockPushButton.h"
#include "MockPowerControl.h"
#include "MockUIInterfaces.h"
#include "MockTimer.h"
#include "MockStateMachineCommon.h"
#include "StateMachineFault.h"
#include "unity.h"






void setUp()

{

  MP_GetBoostDemand_CMockIgnoreAndReturn(34, ((uint8_t)19));

}



void tearDown()

{}



void test_StateChecksAgainstNullPointer(void)

{

  Fault((bool_t) 

       1

           , 

             ((void *)0)

                 );

  UnityFail( (("Assert should be called before this statement")), (_U_UINT)(43));



}



void test_OnEntryInitialiseDependencyModules(void)

{

  TimerCounter_Disable_CMockExpectAndReturn(49, STATE_MACHINE_COUNTER_E, EC_OK_E);

  TimerCounter_Start_CMockExpectAndReturn(50, STATE_MACHINE_COUNTER_E, (36000u), EC_OK_E);



  MP_SetReferenceVoltageBoost_CMockExpect(52, (0));

  MP_DisablePumpPWM_CMockExpect(53);

  MP_DisableExternalPeripheralsSupply_CMockExpect(54);

  PushButton_ResetEvent_CMockExpect(55);





  PushButton_IsPressed_CMockIgnoreAndReturn(58, (bool_t) 

 1

 );

  PushButton_IsShortPress_CMockIgnoreAndReturn(59, (bool_t) 

 1

 );



  State_t newState = NONE_E;

  Fault((bool_t) 

       1

           , &newState);

}



void test_OnShortPressTransitToPumpDown(void)

{

  TimerCounter_Status_CMockIgnoreAndReturn(67, DISABLED_COUNTER_E);

  TimerCounter_Disable_CMockIgnoreAndReturn(68, EC_OK_E);







  State_t newState = NONE_E;





  PushButton_IsPressed_CMockExpectAndReturn(75, (bool_t) 

 0

 );

  MP_SetReferenceVoltageBoost_CMockIgnore();

  MP_GetBoostDemand_CMockIgnoreAndReturn(77, ((uint8_t)19));

  Battery_CheckVoltageBounds_CMockExpectAndReturn(78, EC_OK_E);

  PM_Delay_CMockIgnore();

  Fault((bool_t) 

       0

            , &newState);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(81), UNITY_DISPLAY_STYLE_INT);



  PushButton_IsPressed_CMockExpectAndReturn(83, (bool_t) 

 1

 );

  PushButton_IsShortPress_CMockExpectAndReturn(84, (bool_t) 

 0

 );

  MP_SetReferenceVoltageBoost_CMockIgnore();

  MP_GetBoostDemand_CMockIgnoreAndReturn(86, ((uint8_t)19));

  Battery_CheckVoltageBounds_CMockExpectAndReturn(87, EC_OK_E);

  PM_Delay_CMockIgnore();

  Fault((bool_t) 

       0

            , &newState);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(90), UNITY_DISPLAY_STYLE_INT);







  PushButton_IsPressed_CMockExpectAndReturn(94, (bool_t) 

 1

 );

  PushButton_IsShortPress_CMockExpectAndReturn(95, (bool_t) 

 1

 );

  Fault((bool_t) 

       0

            , &newState);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);

}







void test_AfterSetNumberOfMinutesTransitToIPD(void)

{

  CounterStatus_t counterStatus = DISABLED_COUNTER_E;



  PushButton_IsPressed_CMockIgnoreAndReturn(106, (bool_t) 

 0

 );



  CounterStatus_t stubTimerCounter_Status(CounterName_t counterName, int numCall)

  {

    UnityAssertEqualNumber((_U_SINT)((STATE_MACHINE_COUNTER_E)), (_U_SINT)((counterName)), (

   ((void *)0)

   ), (_U_UINT)(110), UNITY_DISPLAY_STYLE_INT);

    return counterStatus;

  }

  TimerCounter_Status_StubWithCallback(stubTimerCounter_Status);



  State_t newState = NONE_E;





  MP_SetReferenceVoltageBoost_CMockIgnore();

  PM_Delay_CMockIgnore();

  Battery_CheckVoltageBounds_CMockExpectAndReturn(120, EC_OK_E);

  Fault((bool_t) 

       0

            , &newState);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(122), UNITY_DISPLAY_STYLE_INT);





  counterStatus = EXPIRED_COUNTER_E;

  TimerCounter_Disable_CMockExpectAndReturn(126, STATE_MACHINE_COUNTER_E, EC_OK_E);



  Fault((bool_t) 

       0

            , &newState);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(129), UNITY_DISPLAY_STYLE_INT);

}
