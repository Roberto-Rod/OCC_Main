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









void test_SwitchTheDeviceOffWithLongButtonPressStartedInLeakErrorConditionAndDetectedInTherapyDelivery(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(79, (bool_t) 

 0

 );

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(83), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(87), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(93), UNITY_DISPLAY_STYLE_INT);











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



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(114)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;



  for ( uint16_t i = 0; i <=200; i++)

  {

     PicoTestFramework_Tick();

     Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(128), UNITY_DISPLAY_STYLE_INT);

  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(129)));};









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  for(uint32_t i = 0; 30 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(143)));};









  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     1

                                                         ;



  for (uint32_t i = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState(); i++)

  {

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(156)));};











  for (uint32_t i = 0; i < 20; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(168)));};

    if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(169)));};

    if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(170)));};

  }











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







  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(192)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(193)));};

  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(194)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);









  uint32_t button_press_ticks = 3;

  for (; 10 > button_press_ticks; button_press_ticks++)

  {

    PicoTestFramework_Tick();

    Application_Run();







    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(208)));};

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(209), UNITY_DISPLAY_STYLE_INT);

  }









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;

  for (; 12 > button_press_ticks; button_press_ticks++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(223)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(224), UNITY_DISPLAY_STYLE_INT);









  for (; (20) > button_press_ticks; button_press_ticks++)

  {

    PicoTestFramework_Tick();

    Application_Run();







    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(236)));};

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(237), UNITY_DISPLAY_STYLE_INT);

  }









  button_press_ticks++;

  PicoTestFramework_Tick();

  Application_Run();



  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(247)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(248)));};

  UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(249), UNITY_DISPLAY_STYLE_INT);





  for(uint32_t i = 0; 29 > i; i++)

  {

    if (i<10)

    {

      PicoTestFramework_SetPushButton((bool_t) 

                                     0

                                          );

    }



    PicoTestFramework_Tick();

    Application_Run();



    if (i<19)

    {

      if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(264)));};

      if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(265)));};

    }

    else

    {

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(269)));};

      if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(270)));};

    }



    UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(273), UNITY_DISPLAY_STYLE_INT);

  }







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );



  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(284)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(285)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);



}
