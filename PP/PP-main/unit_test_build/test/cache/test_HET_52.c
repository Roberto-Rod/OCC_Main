#include "MockWatchdog.h"
#include "MockPerformanceLogger.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "Assert.h"
#include "DutyCycle.h"
#include "PushButton.h"
#include "UIInterfaces.h"
#include "Timer.h"
#include "StateMachinePOST_internal.h"
#include "StateMachinePOST.h"
#include "Battery.h"
#include "StateMachineNre.h"
#include "StateMachineFault.h"
#include "StateMachineTherapyDelivery.h"
#include "StateMachineIdle.h"
#include "StateMachineShutdown.h"
#include "StateMachinePumpDown.h"
#include "StateMachineCommon.h"
#include "StateMachine.h"
#include "MockLoggingManager.h"
#include "AlertManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "test_helpers/PicoTestFramework.h"
#include "unity.h"
















void setUp(void)

{

  PicoTestFramework_Setup();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(63, EC_OK_E);

  PerformanceLogger_SetPumpHistory_CMockIgnore();

}



void tearDown(void)

{}



void test_WhenButtonIsNotPressedIndleTheTherapyIsStartedAfter60Minutes(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(72, (bool_t) 

 0

 );

  Application_Init();





  PicoTestFramework_Tick();



  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(81)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(82)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(83), UNITY_DISPLAY_STYLE_INT);





  const uint16_t tickCount60Mins = 10 * 60 * 60;

  for (uint16_t i = 0; i < tickCount60Mins; i++)

  {

    PicoTestFramework_Tick();



    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(93), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(101), UNITY_DISPLAY_STYLE_INT);



}
