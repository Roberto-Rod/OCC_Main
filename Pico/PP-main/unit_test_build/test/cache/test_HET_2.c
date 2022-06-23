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





void test_TurnOffTheLEDsWhenDetectBatteryLowEventInIdleAndPumpDownAndDisableTheDeviceToDeliverFurtherTherapy(void)

{

  I2E_Read_CMockIgnoreAndReturn(71, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(72, EC_OK_E);

  Application_Init();









  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(78), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(82), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(88), UNITY_DISPLAY_STYLE_INT);

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(89)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(90)));};







  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;

  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(100)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(101)));};











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



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(118)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(119), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;



  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(130), UNITY_DISPLAY_STYLE_INT);

  if ((PUMP_DOWN_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(131)));};







  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;



  PicoTestFramework_Tick();

  Application_Run();





  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(145)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(146)));};

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(147), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(148), UNITY_DISPLAY_STYLE_INT);







  for (uint32_t i = 0; i < 20; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(158)));};

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(159)));};

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

   ((void *)0)

   ), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

  }

}







void test_TurnOffTheLEDsWhenDetectBatteryLowEventInTherapyDeliveryAndDisableTheDeviceToDeliverFurtherTherapy(void)

{

  I2E_Read_CMockIgnoreAndReturn(169, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(170, EC_OK_E);

  Application_Init();













  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(178), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(182), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(188), UNITY_DISPLAY_STYLE_INT);

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(189)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(190)));};







  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;

  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(200)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(201)));};











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



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(218)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(219), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;





  for ( int16_t i = 0; i<=200; i++)

  {

      PicoTestFramework_Tick();

      Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(233), UNITY_DISPLAY_STYLE_INT);

  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(234)));};













  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  for(uint32_t i = 0; 0 == picoTestFrameworkIo.getVacuumTickCount; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }

  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;



  PicoTestFramework_Tick();

  Application_Run();





  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(261)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(262)));};

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);

  if ((NRE_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(264)));};

}
