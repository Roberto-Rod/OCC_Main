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
#include "PushButton.h"
#include "DutyCycle.h"
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
#include "PicoTestFramework.h"
#include "unity.h"














void setUp(void)

{

  PicoTestFramework_Setup();

}



void tearDown(void)

{}



void test_GoFromIdleToPumpDownAndClearTheWatchdogAtEveryExecution(void)

{



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(69), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(70), UNITY_DISPLAY_STYLE_INT);

  I2E_Read_CMockIgnoreAndReturn(71, EC_OK_E);

  Application_Init();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(74), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(75), UNITY_DISPLAY_STYLE_INT);









  PicoTestFramework_Tick();



  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(85), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(86), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(105), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(106), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(116), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(125), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(127), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(135), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(136), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(137), UNITY_DISPLAY_STYLE_INT);







  MP_EnableMainCircuitPower_CMockExpect(141);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

 ((void *)0)

 ), (_U_UINT)(145), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((7)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

 ((void *)0)

 ), (_U_UINT)(146), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(147), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  for (uint8_t i = 0; i < 5; i++)

  {

    MP_EnableMainCircuitPower_CMockExpect(153);

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.countWatchdogInit)), (

   ((void *)0)

   ), (_U_UINT)(157), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((8+i)), (_U_SINT)((picoTestFrameworkIo.countWatchdogClear)), (

   ((void *)0)

   ), (_U_UINT)(158), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(159), UNITY_DISPLAY_STYLE_INT);

  }

}
