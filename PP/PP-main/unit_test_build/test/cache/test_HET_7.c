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
#include "MockLoggingManager.h"
#include "DutyCycle.h"
#include "PushButton.h"
#include "Assert.h"
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
#include "AlertManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "PicoTestFramework.h"
#include "unity.h"














void setUp(void)

{

  PicoTestFramework_Setup();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(62, EC_OK_E);

  PerformanceLogger_SetPumpHistory_CMockIgnore();

  PerformanceLogger_SetPumpDownDuration_CMockIgnore();

}



void tearDown(void)

{}





void test_InIdleStateWhenNoButtonIsPressedGoToLowPowerDisablingPeripherals(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(73, (bool_t) 

 0

 );

  Application_Init();





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(81), UNITY_DISPLAY_STYLE_INT);









  uint32_t count = 0;

  const uint32_t expectedPheripheralDisableCount = 19;

  for(; 20 > count; count++)

  {

    if(expectedPheripheralDisableCount == count)

    {

      PicoTestFramework_SetPushButton((bool_t) 

                                     1

                                         );

    }

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_Tick();

  Application_Run();





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(108), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;

  PicoTestFramework_Tick();

  Application_Run();





  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(121), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(127), UNITY_DISPLAY_STYLE_INT);











  UnityAssertEqualNumber((_U_SINT)((expectedPheripheralDisableCount)), (_U_SINT)((picoTestFrameworkIo.countDisablePeripheral)), (

 ((void *)0)

 ), (_U_UINT)(133), UNITY_DISPLAY_STYLE_INT);

}
