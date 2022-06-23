#include "MockWatchdog.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "Assert.h"
#include "Battery.h"
#include "PerformanceLogger.h"
#include "DutyCycle.h"
#include "PushButton.h"
#include "UIInterfaces.h"
#include "Timer.h"
#include "StateMachinePOST_internal.h"
#include "StateMachinePOST.h"
#include "StateMachineNre.h"
#include "StateMachineFault.h"
#include "StateMachineTherapyDelivery.h"
#include "StateMachineIdle.h"
#include "StateMachineShutdown.h"
#include "StateMachinePumpDown.h"
#include "StateMachineCommon.h"
#include "StateMachine.h"
#include "LoggingManager.h"
#include "AlertManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "test_helpers/PicoTestFramework.h"
#include "unity.h"
















void setUp(void)

{

  PicoTestFramework_Setup();

}



void tearDown(void)

{}













void test_PerformanceStatsSkippedInIdleState(void)

{

  I2E_Read_CMockIgnoreAndReturn(74, EC_OK_E);

  MP_SleepUntilWokenByRelaxationOscillator_CMockIgnore();



  Application_Init();





  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(84), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetCurrentAddress())), (

 ((void *)0)

 ), (_U_UINT)(90), UNITY_DISPLAY_STYLE_INT);



  const uint16_t oneMinuteTick = 60 * 10;



  for (uint16_t i = 0; i < oneMinuteTick; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);

  }



  UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((PerformanceLogger_GetCurrentAddress())), (

 ((void *)0)

 ), (_U_UINT)(103), UNITY_DISPLAY_STYLE_INT);



  for (uint16_t i = 0; i < oneMinuteTick; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(111), UNITY_DISPLAY_STYLE_INT);

  }



  UnityAssertEqualNumber((_U_SINT)((32)), (_U_SINT)((PerformanceLogger_GetCurrentAddress())), (

 ((void *)0)

 ), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);



}
