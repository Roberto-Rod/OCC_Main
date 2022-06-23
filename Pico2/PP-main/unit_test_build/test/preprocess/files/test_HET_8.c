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
#include "AlertManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "test_helpers/PicoTestFramework.h"
#include "unity.h"


















void setUp(void)

{

  Battery_CheckVoltageBounds_CMockIgnoreAndReturn(62, EC_OK_E);

  MP_GetBoostDemand_CMockIgnoreAndReturn(63, ((uint8_t)19));

  PicoTestFramework_Setup();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(66, EC_OK_E);

  PerformanceLogger_SetPumpHistory_CMockIgnore();

  PerformanceLogger_SetPumpDownDuration_CMockIgnore();

}



void tearDown(void)

{}







void test_DetectLeakInTherapyDeliveryAndAlertTheUserOfTheErrorCondition(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(78, (bool_t) 

 0

 );

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(82), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(86), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(92), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  PicoTestFramework_Tick();

  Application_Run();



  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(109)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(110), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;





  for ( int i = 0; i <= 200; i++)

  {

      PicoTestFramework_Tick();

      Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);

  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(125)));};









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  for(uint32_t i = 0; 30 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }





  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(140)));};









  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     1

                                                         ;



  for (uint32_t i = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState(); i++)

  {



    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(150)));};

    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(151)));};

    PicoTestFramework_Tick();

    Application_Run();



  }





  if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(158)));};

  if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(159)));};

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(160)));};









  for (uint32_t i = 0; i < 19; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(171)));};

    if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(172)));};

    if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(173)));};

  }











  bool_t orange_status = (bool_t) 

                        0

                             ;

  uint32_t count = 0;

  for (uint32_t i = 0; i < 80; i++)

  {

    count = i%20;

    orange_status = ((0 == count) || (1 == count)) ? (bool_t) 

                                                    1

                                                        :(bool_t) 

                                                         0

                                                              ;



    PicoTestFramework_Tick();

    Application_Run();



    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(190)));};

    UnityAssertEqualNumber((_U_SINT)((orange_status)), (_U_SINT)((picoTestFrameworkIo.isOrangeLEDEnabled)), (

   ((void *)0)

   ), (_U_UINT)(191), UNITY_DISPLAY_STYLE_INT);

    if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(192)));};

  }



}













void test_DetectAndIgnoreLeakInTherapyDeliveryWhenBoostVoltageDenandIsBelow27V(void)

{

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  PerformanceLogger_GetNRE_CMockExpectAndReturn(205, (bool_t) 

 0

 );

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(209), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(213), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(219), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  PicoTestFramework_Tick();

  Application_Run();



  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(236)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(237), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;





  for ( int i = 0; i <= 200; i++)

  {

      PicoTestFramework_Tick();

      Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(251), UNITY_DISPLAY_STYLE_INT);

  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(252)));};









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  for(uint32_t i = 0; 30 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(266)));};











  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     1

                                                         ;

  picoTestFrameworkIo.isBoostVoltageDemandAtReference27V = (bool_t) 

                                                          0

                                                               ;



  for (uint32_t i = 0; i < 400; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(282)));};

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(283)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(284)));};

}
