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
#include "Battery.h"
#include "MockWatchdog.h"
#include "Assert.h"
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
#include "AlertManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "test_helpers/PicoTestFramework.h"
#include "unity.h"












static bool_t therapyVacuumAchieved;

bool_t Stub_isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum, int NumCall)

{

  return therapyVacuumAchieved;

}



void setUp(void)

{

  PicoTestFramework_Setup();

  isTargetTherapyDeliveryVacuumAchieved_StubWithCallback(Stub_isTargetTherapyDeliveryVacuumAchieved);

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(76, EC_OK_E);

  PerformanceLogger_SetPumpHistory_CMockIgnore();

  PerformanceLogger_SetPumpDownDuration_CMockIgnore();

}



void tearDown(void)

{}







void test_TherapyIsMaintained(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(88, (bool_t) 

 0

 );

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(92), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(98)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(99)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(115)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(116)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(124)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(125)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_Tick();

  Application_Run();





  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(134)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(135)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(136), UNITY_DISPLAY_STYLE_INT);









  uint32_t tickCount =

      (10) +

      (50) +

      (150) -1;

  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  MP_EnableMainCircuitPower_CMockIgnore();

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(147, (bool_t) 

 0

 );

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  therapyVacuumAchieved = (bool_t) 

                         1

                             ;

  State_t expectedState = PUMP_DOWN_E;







  for (uint32_t i = 0; i < tickCount; i++)

  {





    if (i == ( (200)-(50+0)))

    {

      picoTestFrameworkIo.getVacuumMeasurement = 107;

      picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                          1

                                                              ;

    }



    if (i == ( (200)-(49+0)))

    {

      picoTestFrameworkIo.getVacuumMeasurement = 80;

      picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                          0

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

   ), (_U_UINT)(180), UNITY_DISPLAY_STYLE_INT);

  }









  tickCount = (20);

  int numOrangeOns = 0;

  int numGreenOns = 0;

  for (uint16_t i = 0; i < tickCount; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);

    numOrangeOns += picoTestFrameworkIo.isOrangeLEDEnabled;

    numGreenOns += picoTestFrameworkIo.isGreenLEDEnabled;

  }

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((numOrangeOns)), (

 ((void *)0)

 ), (_U_UINT)(198), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((tickCount)), (_U_SINT)((numGreenOns)), (

 ((void *)0)

 ), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);





  numOrangeOns = 0;

  numGreenOns = 0;

  for (uint16_t i = 0; i < 30; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(209), UNITY_DISPLAY_STYLE_INT);

    numOrangeOns += picoTestFrameworkIo.isOrangeLEDEnabled;

    numGreenOns += picoTestFrameworkIo.isGreenLEDEnabled;

  }

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((numOrangeOns)), (

 ((void *)0)

 ), (_U_UINT)(213), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((numGreenOns)), (

 ((void *)0)

 ), (_U_UINT)(214), UNITY_DISPLAY_STYLE_INT);







  therapyVacuumAchieved = (bool_t) 

                         0

                              ;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint16_t i = 0; i < 30; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(225), UNITY_DISPLAY_STYLE_INT);

  }

  UnityAssertEqualNumber((_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (_U_SINT)((3)), (

 ((void *)0)

 ), (_U_UINT)(227), UNITY_DISPLAY_STYLE_INT);





  therapyVacuumAchieved = (bool_t) 

                         1

                             ;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint16_t i = 0; i < 30; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(237), UNITY_DISPLAY_STYLE_INT);

  }

  UnityAssertEqualNumber((_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (_U_SINT)((0)), (

 ((void *)0)

 ), (_U_UINT)(239), UNITY_DISPLAY_STYLE_INT);



}
