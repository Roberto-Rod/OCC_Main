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



void test_DetectBatteryDepletedDuringIPDAndTryToStartDeviceAgainWithNoLuck(void)

{

  I2E_Read_CMockIgnoreAndReturn(69, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(70, EC_OK_E);

  Application_Init();





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(77), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(83), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(90), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);





  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(120), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(121), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(122), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  for (uint8_t i = 0; i < 5; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(132), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(133), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(141), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(142), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(143), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  for (uint8_t i = 0; i < 30; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(153), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(154), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(163), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(164), UNITY_DISPLAY_STYLE_INT);

}



void test_DetectBatteryDepletedDuringMPDAndTryToStartDeviceAgainWithNoLuck(void)

{

  I2E_Read_CMockIgnoreAndReturn(169, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(170, EC_OK_E);

  Application_Init();





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(177), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(190), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );



  picoTestFrameworkIo.getVacuumMeasurement = 107;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;







  uint32_t tickCount = (200);

  State_t expectedState = PUMP_DOWN_E;









  for (uint32_t i = 0; i < tickCount; i++)

  {







    if (i == ( (200)-(2)))

    {

      picoTestFrameworkIo.getVacuumMeasurement = 107;

      picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                          1

                                                              ;

    }



    if (i >= ((200)))

    {

      expectedState = THERAPY_DELIVERY_E;

    }



    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(235), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(242), UNITY_DISPLAY_STYLE_INT);





  InitTherapyDeliveryVacuum_CMockIgnore();

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(246, (bool_t) 

 0

 );

  isTargetTherapyDeliveryVacuumAchieved_CMockIgnoreAndReturn(247, (bool_t) 

 0

 );



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(252), UNITY_DISPLAY_STYLE_INT);





  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(259), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(265), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(266), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(267), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  for (uint8_t i = 0; i < 5; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(276), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(277), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(278), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(287), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(288), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  for (uint8_t i = 0; i < 30; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(297), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(298), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((bool_t) 

   0

   )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(299), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(307), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isGreenLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(308), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

 ((void *)0)

 ), (_U_UINT)(309), UNITY_DISPLAY_STYLE_INT);

}
