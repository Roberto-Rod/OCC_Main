#include "MockHardwareInterface.h"
#include "Assert.h"
#include "Timer.h"
#include "unity.h"


extern void TMR1_CallBack();



void setUp(void)

{

  HardwareInterface_EnableGlobalInterrupt_CMockIgnore();

  HardwareInterface_DisableGlobalInterrupt_CMockIgnore();

}



void tearDown(void)

{}



void test_TimerCountersInit(void)

{

  CounterStatus_t status;



  TimerCounters_Init();



  status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);

  UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((status)), (

 ((void *)0)

 ), (_U_UINT)(41), UNITY_DISPLAY_STYLE_INT);



  status = TimerCounter_Status(POWER_OFF_COUNTER_E);

  UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((status)), (

 ((void *)0)

 ), (_U_UINT)(44), UNITY_DISPLAY_STYLE_INT);



  status = TimerCounter_Status(LED_ALERT_COUNTER_1_E);

  UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((status)), (

 ((void *)0)

 ), (_U_UINT)(47), UNITY_DISPLAY_STYLE_INT);

}



void test_TimerCountersStartAndCheck(void)

{

  CounterStatus_t status = INERROR_COUNTER_E;;

  ErrorCode_t result = EC_TIMER_COUNT_UNAVAILABLE_E;

  uint32_t const MaxDuration = 1000;





  TimerCounters_Init();



  for (uint8_t i = STATE_MACHINE_COUNTER_E; i < MAX_SOFTWARE_COUNTER_E; i++)

  {

    result = TimerCounter_Start((CounterName_t)i, MaxDuration);

    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

   ((void *)0)

   ), (_U_UINT)(62), UNITY_DISPLAY_STYLE_INT);

    status = TimerCounter_Status((CounterName_t)i);

    UnityAssertEqualNumber((_U_SINT)((RUNNING_COUNTER_E)), (_U_SINT)((status)), (

   ((void *)0)

   ), (_U_UINT)(64), UNITY_DISPLAY_STYLE_INT);

  }

}



void test_TimerCountersRunAndCheckAndDisable(void)

{

  uint32_t const MaxDuration = 1000;





  TimerCounters_Init();

  ErrorCode_t result = TimerCounter_Start(STATE_MACHINE_COUNTER_E, MaxDuration);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(75), UNITY_DISPLAY_STYLE_INT);





  for (uint32_t i = 0; i < MaxDuration - 1; i++)

  {

    TMR1_CallBack();

  }

  CounterStatus_t status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);

  UnityAssertEqualNumber((_U_SINT)((RUNNING_COUNTER_E)), (_U_SINT)((status)), (

 ((void *)0)

 ), (_U_UINT)(83), UNITY_DISPLAY_STYLE_INT);





  for (uint32_t i = 0; i < 10; i++)

  {

    TMR1_CallBack();

  }

  status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);

  UnityAssertEqualNumber((_U_SINT)((EXPIRED_COUNTER_E)), (_U_SINT)((status)), (

 ((void *)0)

 ), (_U_UINT)(91), UNITY_DISPLAY_STYLE_INT);

}



void test_TimerCountersStopCheck(void)

{

  uint32_t const MaxDuration = 1000;





  TimerCounters_Init();

  ErrorCode_t result = TimerCounter_Start(STATE_MACHINE_COUNTER_E, MaxDuration);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(101), UNITY_DISPLAY_STYLE_INT);

  for (uint32_t i = 0; i < 10; i++)

  {

    TMR1_CallBack();

  }





  result = TimerCounter_Disable(STATE_MACHINE_COUNTER_E);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(109), UNITY_DISPLAY_STYLE_INT);

  CounterStatus_t status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);

  UnityAssertEqualNumber((_U_SINT)((DISABLED_COUNTER_E)), (_U_SINT)((status)), (

 ((void *)0)

 ), (_U_UINT)(111), UNITY_DISPLAY_STYLE_INT);

}
