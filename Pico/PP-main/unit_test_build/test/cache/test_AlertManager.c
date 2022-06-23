#include "MockDeviceStatus.h"
#include "MockTimer.h"
#include "MockUIInterfaces.h"
#include "AlertManager.h"
#include "unity.h"
extern LEDControl_t ledOperation;



State_t DeviceStatus = NONE_E;

CounterStatus_t LedAlertCounter1Status = UNKNOWN_STATE_E;



CounterStatus_t ForcedStatus = UNKNOWN_STATE_E;

bool_t ForceCounter2 = (bool_t) 

                                           0

                                                ;

bool_t CheckDeviceStatusFlag = (bool_t) 

                                           0

                                                ;

uint32_t SetTimerCounterValue = 0;

uint32_t TimerDisableCount = 0;

uint32_t TimerEnableCount = 0;



static State_t Stub_DeviceStatus_GetState(int NumCalls)

{

    return DeviceStatus;

}





static ErrorCode_t Stub_TimerCounter_Disable(CounterName_t TimerCounter, int NumCalls)

{

    ErrorCode_t result = EC_OK_E;



    if (LED_ALERT_COUNTER_1_E == TimerCounter)

    {

        LedAlertCounter1Status = DISABLED_COUNTER_E;

        TimerDisableCount++;

    }

    else

    {

        result = EC_TIMER_COUNT_UNAVAILABLE_E;

    }



    return result;

}





static ErrorCode_t Stub_TimerCounter_Start(CounterName_t TimerCounter, uint32_t CounterValue, int NumCalls)

{

    ErrorCode_t result = EC_OK_E;



    if (LED_ALERT_COUNTER_1_E == TimerCounter)

    {

        LedAlertCounter1Status = RUNNING_COUNTER_E;

        SetTimerCounterValue = CounterValue;

        TimerEnableCount++;

    }

    else

    {

        SetTimerCounterValue = 0;

        result = EC_TIMER_COUNT_UNAVAILABLE_E;

    }



    return result;

}









CounterStatus_t Stub_TimerCounter_Status(CounterName_t CounterName, int NumCalls)

{

    CounterStatus_t status = UNKNOWN_STATE_E;



    switch (CounterName)

    {

        case LED_ALERT_COUNTER_1_E:

        status = LedAlertCounter1Status;

        break;



        default:

        status = UNKNOWN_STATE_E;

        break;

    }



    return status;

}

void Stub_DeviceStatus_SetCheckStatusAlert(bool_t Enable, int NumCalls)

{

    CheckDeviceStatusFlag = Enable;

}



bool_t Stub_DeviceStatus_GetCheckStatusAlert(int NumCalls)

{

    return CheckDeviceStatusFlag;

}



void setUp(void)

{

    LedAlertCounter1Status = UNKNOWN_STATE_E;

    ForcedStatus = UNKNOWN_STATE_E;

    ForceCounter2 = (bool_t) 

                            0

                                 ;

    CheckDeviceStatusFlag = (bool_t) 

                            0

                                 ;



    TimerCounter_Disable_StubWithCallback(Stub_TimerCounter_Disable);

    TimerCounter_Start_StubWithCallback(Stub_TimerCounter_Start);

    TimerCounter_Status_StubWithCallback(Stub_TimerCounter_Status);

    DeviceStatus_GetState_StubWithCallback(Stub_DeviceStatus_GetState);

    DeviceStatus_GetCheckStatusAlert_StubWithCallback(Stub_DeviceStatus_GetCheckStatusAlert);

    DeviceStatus_SetCheckStatusAlert_StubWithCallback(Stub_DeviceStatus_SetCheckStatusAlert);

}



void tearDown(void)

{

}







void test_AlertManagerInitialise(void)

{

    UI_SetLED_CMockExpect(145, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(146, LD_ORANGE_E, 0, 0);



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((AlertManager_Init())), (

   ((void *)0)

   ), (_U_UINT)(148), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(149), UNITY_DISPLAY_STYLE_INT);







    if ((checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(153)));};





    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_COMPLETED_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);

}















void test_RunAlertManagerWhenStateMachineInFaultOrUnknownStateAndCheck(void)

{

    UI_SetLED_CMockExpect(167, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(168, LD_ORANGE_E, 0, 0);



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((AlertManager_Init())), (

   ((void *)0)

   ), (_U_UINT)(170), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(171), UNITY_DISPLAY_STYLE_INT);







    if ((checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(175)));};



    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_COMPLETED_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(177), UNITY_DISPLAY_STYLE_INT);









    for (int i = 0; i < 10; i++)

    {

        UI_SetLED_CMockExpect(184, LD_GREEN_E, 0, 0);

        UI_SetLED_CMockExpect(185, LD_ORANGE_E, 0, 0);

        UI_UpdateLEDs_CMockIgnoreAndReturn(186, (bool_t) 

       1

       );

        DeviceStatus_SetLedsOnStatus_CMockIgnore();

        AlertManager_Run();





        UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

       ((void *)0)

       ), (_U_UINT)(191), UNITY_DISPLAY_STYLE_INT);

    }



    UI_SetLED_CMockExpect(194, LD_GREEN_E, 10, 0);

    UI_SetLED_CMockExpect(195, LD_ORANGE_E, 0, 0);

    StartLEDSequence(LED_CTRL_PUMP_DOWN_E);





    if (!(checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(199)));};





    UI_GetPeriodCount_CMockExpectAndReturn(202, LD_GREEN_E, 1);





    UI_SetLED_CMockExpect(205, LD_GREEN_E, 1, 1);

    UI_SetLED_CMockExpect(206, LD_ORANGE_E, 0, 0);

    AlertManager_Run();





    if (!(checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(210)));};





    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(213), UNITY_DISPLAY_STYLE_INT);





    UI_GetPeriodCount_CMockExpectAndReturn(216, LD_GREEN_E, 25);







    UI_SetLED_CMockExpect(220, LD_GREEN_E, 1, 1);

    UI_SetLED_CMockExpect(221, LD_ORANGE_E, 0, 0);



    AlertManager_Run();





    UnityAssertEqualNumber((_U_SINT)((RUNNING_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(226), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((_U_SINT)((150)), (_U_SINT)((SetTimerCounterValue)), (

   ((void *)0)

   ), (_U_UINT)(229), UNITY_DISPLAY_STYLE_INT);





    UI_GetPeriodCount_CMockExpectAndReturn(232, LD_GREEN_E, 3);



    UI_SetLED_CMockExpect(234, LD_GREEN_E, 1, 2);

    UI_SetLED_CMockExpect(235, LD_ORANGE_E, 0, 0);



    AlertManager_Run();







    UI_GetPeriodCount_CMockExpectAndReturn(241, LD_GREEN_E, 3);



    UI_SetLED_CMockExpect(243, LD_GREEN_E, 1, 3);

    UI_SetLED_CMockExpect(244, LD_ORANGE_E, 0, 0);



    AlertManager_Run();







    LedAlertCounter1Status = EXPIRED_COUNTER_E;





    UI_SetLED_CMockExpect(253, LD_GREEN_E, 20, 0);

    UI_SetLED_CMockExpect(254, LD_ORANGE_E, 0, 0);





    AlertManager_Run();





    UnityAssertEqualNumber((_U_SINT)((EXPIRED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(260), UNITY_DISPLAY_STYLE_INT);





    if (!(checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(263)));};





    UI_GetPeriodCount_CMockExpectAndReturn(266, LD_GREEN_E, 1);





    UI_SetLED_CMockExpect(269, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(270, LD_ORANGE_E, 0, 0);



    AlertManager_Run();





    if ((checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(275)));};

}







void test_RunAlertManagerWhenSwitchingBetweenDisplaySequences(void)

{

    UI_SetLED_CMockExpect(282, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(283, LD_ORANGE_E, 0, 0);



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((AlertManager_Init())), (

   ((void *)0)

   ), (_U_UINT)(285), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);







    if ((checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(290)));};



    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_COMPLETED_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(292), UNITY_DISPLAY_STYLE_INT);









    UI_SetLED_CMockExpect(297, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(298, LD_ORANGE_E, 0, 0);

    UI_UpdateLEDs_CMockIgnoreAndReturn(299, (bool_t) 

   1

   );

    DeviceStatus_SetLedsOnStatus_CMockIgnore();

    AlertManager_Run();





    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(304), UNITY_DISPLAY_STYLE_INT);





    UI_SetLED_CMockExpect(307, LD_GREEN_E, 10, 0);

    UI_SetLED_CMockExpect(308, LD_ORANGE_E, 0, 0);

    StartLEDSequence(LED_CTRL_PUMP_DOWN_E);







    if (!(checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(313)));};



    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_PUMP_DOWN_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(315), UNITY_DISPLAY_STYLE_INT);







    TimerDisableCount = 0;



    UI_SetLED_CMockExpect(321, LD_ORANGE_E, 20, 0);

    UI_SetLED_CMockExpect(322, LD_GREEN_E, 0, 0);

    StartLEDSequence(LED_CTRL_LEAK_E);





    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((TimerDisableCount)), (

   ((void *)0)

   ), (_U_UINT)(326), UNITY_DISPLAY_STYLE_INT);





    if (!(checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(329)));};



    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_LEAK_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(331), UNITY_DISPLAY_STYLE_INT);













    TimerDisableCount = 0;



    UI_SetLED_CMockExpect(340, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(341, LD_ORANGE_E, 0, 0);

    StartLEDSequence(LED_CTRL_OFF_E);



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((TimerDisableCount)), (

   ((void *)0)

   ), (_U_UINT)(344), UNITY_DISPLAY_STYLE_INT);





    if ((checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(347)));};



    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_COMPLETED_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(349), UNITY_DISPLAY_STYLE_INT);

}











void test_RunAlertManagerWhenSwitchingToPowerDownSeq(void)

{

    UI_SetLED_CMockExpect(358, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(359, LD_ORANGE_E, 0, 0);



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((AlertManager_Init())), (

   ((void *)0)

   ), (_U_UINT)(361), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(362), UNITY_DISPLAY_STYLE_INT);







    if ((checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(366)));};



    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_COMPLETED_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(368), UNITY_DISPLAY_STYLE_INT);











    UI_SetLED_CMockExpect(374, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(375, LD_ORANGE_E, 0, 0);

    UI_UpdateLEDs_CMockIgnoreAndReturn(376, (bool_t) 

   1

   );

    DeviceStatus_SetLedsOnStatus_CMockIgnore();

    AlertManager_Run();





    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(381), UNITY_DISPLAY_STYLE_INT);





    TimerDisableCount = 0;

    TimerEnableCount = 0;





    UI_SetLED_CMockExpect(388, LD_GREEN_E, 20, 0);

    UI_SetLED_CMockExpect(389, LD_ORANGE_E, 0, 0);

    StartLEDSequence(LED_CTRL_POWER_DOWN_E);







    if (!(checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(394)));};







    UnityAssertEqualNumber((_U_SINT)((LED_CTRL_POWER_DOWN_E)), (_U_SINT)((ledOperation)), (

   ((void *)0)

   ), (_U_UINT)(398), UNITY_DISPLAY_STYLE_INT);







    UI_GetPeriodCount_CMockExpectAndReturn(402, LD_GREEN_E, 1);









    UI_SetLED_CMockExpect(407, LD_ORANGE_E, 10, 0);

    UI_SetLED_CMockExpect(408, LD_GREEN_E, 0, 0);

    AlertManager_Run();





    if (!(checkLEDSequenceCompleted())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(412)));};





    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((TimerDisableCount)), (

   ((void *)0)

   ), (_U_UINT)(415), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((TimerEnableCount)), (

   ((void *)0)

   ), (_U_UINT)(416), UNITY_DISPLAY_STYLE_INT);

}







void test_RunAlertManagerWhenStateMachineInIdleStateAndCheck(void)

{



    DeviceStatus = IDLE_E;

    UI_SetLED_CMockExpect(425, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(426, LD_ORANGE_E, 0, 0);

    UI_UpdateLEDs_CMockIgnoreAndReturn(427, (bool_t) 

   1

   );

    DeviceStatus_SetLedsOnStatus_CMockIgnore();

    AlertManager_Init();









    DeviceStatus = NONE_E;

    UI_SetLED_CMockExpect(435, LD_GREEN_E, 0, 0);

    UI_SetLED_CMockExpect(436, LD_ORANGE_E, 0, 0);

    UI_UpdateLEDs_CMockIgnoreAndReturn(437, (bool_t) 

   1

   );



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((AlertManager_Run())), (

   ((void *)0)

   ), (_U_UINT)(439), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((LedAlertCounter1Status)), (

   ((void *)0)

   ), (_U_UINT)(440), UNITY_DISPLAY_STYLE_INT);

}
