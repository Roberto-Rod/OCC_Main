#include "MockWatchdog.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "MockPerformanceLogger.h"
#include "MockBattery.h"
#include "Assert.h"
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
#include "MockLoggingManager.h"
#include "AlertManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "test_helpers/PicoTestFramework.h"
#include "unity.h"
















void setUp(void)

{

  Battery_CheckVoltageBounds_CMockIgnoreAndReturn(61, EC_OK_E);

  MP_GetBoostDemand_CMockIgnoreAndReturn(62, ((uint8_t)19));

  PicoTestFramework_Setup();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(65, EC_OK_E);

  PerformanceLogger_SetPumpHistory_CMockIgnore();

  PerformanceLogger_SetPumpDownDuration_CMockIgnore();

}



void tearDown(void)

{}



void test_After60MinInFaultStateRestartIPD(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(75, (bool_t) 

 0

 );

  Application_Init();



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(81), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();



  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(89), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();



  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(102), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);



  MP_EnableMainCircuitPower_CMockIgnore();

  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  for (uint8_t i = 0; i < 20 * 10; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(120), UNITY_DISPLAY_STYLE_INT);

    PicoTestFramework_Tick();

    Application_Run();



  }



  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  const uint16_t sixtyMinuteTicks = 60 * 60 * 10;



  bool_t orangeOn = (bool_t) 

                   0

                        ;

  int OnOffCount = 0;



  for (uint16_t i = 0; i < sixtyMinuteTicks; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(140), UNITY_DISPLAY_STYLE_INT);

    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(141)));};







    if (i < 19)

    {

            orangeOn = (bool_t) 

                      1

                          ;

    }

    else

    {

       orangeOn = (bool_t) 

                 0

                      ;

       if (OnOffCount < 2)

       {

               orangeOn = (bool_t) 

                         1

                             ;

       }

       if (++OnOffCount >= 20)

       {

               OnOffCount = 0;

       }



    }



    if (orangeOn)

    {

        if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(165)));};

    }

    else

    {

        if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(169)));};

    }



    PicoTestFramework_Tick();

    Application_Run();

  }





  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(177), UNITY_DISPLAY_STYLE_INT);

  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(178)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(179)));};



}
