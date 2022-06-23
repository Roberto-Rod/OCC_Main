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
#include "Battery.h"
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

  PicoTestFramework_Setup();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(66, EC_OK_E);

  PerformanceLogger_SetPumpHistory_CMockIgnore();

  PerformanceLogger_SetPumpDownDuration_CMockIgnore();

}



void tearDown(void)

{}













void test_FailToReadVacuumInTherapyDeliveryAndAlertTheUserOfTheErrorConditionAndEnterNRE(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(81, (bool_t) 

 0

 );

  PerformanceLogger_Persist_CMockIgnoreAndReturn(82, (bool_t) 

 1

 );

  PerformanceLogger_SetStatus_CMockExpectAnyArgs(83);

  PerformanceLogger_SetNRE_CMockExpectAndReturn(84, (bool_t) 

 0

 );

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(88), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();



  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(94), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);











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



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(117)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(118), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;



  for ( uint16_t i = 0; i <= 200; i++)

  {

     PicoTestFramework_Tick();

     Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);

  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(132)));};

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;



  for(uint32_t i = 0; 61 > i; i++)

  {

    switch (i)

    {

      case 0:

        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E;

        break;

      default:

        break;

    }

    PicoTestFramework_Tick();

    Application_Run();

  }

  if ((NRE_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(159)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);







  picoTestFrameworkIo.getVacuumResult = EC_OK_E;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  for(uint32_t i = 15; 61 > i; i++)

  {

    switch (i)

    {

      case 15:

        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E;

        break;

      default:

        break;

    }

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((NRE_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(181)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(182), UNITY_DISPLAY_STYLE_INT);





  picoTestFrameworkIo.getVacuumResult = EC_OK_E;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  for(uint32_t i = 25; 61 > i; i++)

  {

    switch (i)

    {

      case 25:

        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_READ_FAILED_E;

        break;

      default:

        break;

    }

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((NRE_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(202)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(203), UNITY_DISPLAY_STYLE_INT);





  picoTestFrameworkIo.getVacuumResult = EC_OK_E;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  for(uint32_t i = 35; 61 > i; i++)

  {

    switch (i)

    {

      case 35:

        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_NOT_READY_E;

        break;

      default:

        break;

    }

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((NRE_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(223)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(224), UNITY_DISPLAY_STYLE_INT);





  picoTestFrameworkIo.getVacuumResult = EC_OK_E;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  for(uint32_t i = 45; 61 > i; i++)

  {

    switch (i)

    {

      case 45:

        picoTestFrameworkIo.getVacuumResult = EC_PRESSURE_DIFF_FAULT_CODE_E;

        break;

      default:

        break;

    }

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((NRE_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(244)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(245), UNITY_DISPLAY_STYLE_INT);

}
