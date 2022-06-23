#include "MockWatchdog.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "Battery.h"
#include "PerformanceLogger.h"
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
#include "MockLoggingManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "test_helpers/PicoTestFramework.h"
#include "unity.h"




















uint8_t StartUpGreenLedPattern[] = {

  1,1,1,1,1,1,1,1,1,1,

  1,0,1,0,1,0,1,0,1,0,

  1,0,1,0,1,0,1,0,1,0,

  1,0,1,0,1,0,1,0,1,0,

  1,0,1,0,1,0,1,0,1,0,

  1,0,1,0,1,0,1,0,1,0,

  1,0,1,0,1,0,

  1,0,0,1,0,0,1,0,0,

  1,0,0,0,1,0,0,0,1,0,0,0,

  1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,

  1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,

  1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,

  1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,

  1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,

  1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,

  1,1,1,1,1,1,1,1,1,1,

  1,1,1,1,1,1,1,1,1,1,

};



void setUp(void)

{

  PicoTestFramework_Setup();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(85, EC_OK_E);

}



void tearDown(void)

{}











void test_PeriodicallyRefreshLedsAndPwmOutputPinsSoThatNoiseDoesNotPreventTherapyDelivery(void)

{

  I2E_Read_CMockIgnoreAndReturn(97, EC_OK_E);

  Application_Init();





  uint32_t greenLedRefreshExpectedCount = 0;

  uint32_t orangeLedRefreshExpectedCount = 0;

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(103), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

 ((void *)0)

 ), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

 ((void *)0)

 ), (_U_UINT)(108), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(109), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

 ((void *)0)

 ), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

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



  UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

 ((void *)0)

 ), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

 ((void *)0)

 ), (_U_UINT)(127), UNITY_DISPLAY_STYLE_INT);

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(128)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(129)));};

  if ((IDLE_E==DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(130)));};



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

 ((void *)0)

 ), (_U_UINT)(135), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

 ((void *)0)

 ), (_U_UINT)(136), UNITY_DISPLAY_STYLE_INT);

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(137)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(138)));};

  if ((IDLE_E==DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(139)));};



  PicoTestFramework_Tick();

  Application_Run();









  ++greenLedRefreshExpectedCount;

  ++orangeLedRefreshExpectedCount;



  UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

 ((void *)0)

 ), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

 ((void *)0)

 ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);

  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(153)));};



  uint32_t index = 0;

  if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(157)));}

                                                                                                   ;

  index++;

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(159)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);











  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  for (uint8_t i = 0; i < 150; i++, index++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

   ((void *)0)

   ), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

   ((void *)0)

   ), (_U_UINT)(173), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((i+1)/2)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

   ((void *)0)

   ), (_U_UINT)(174), UNITY_DISPLAY_STYLE_INT);

    if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(176)));}

                                                                                                   ;

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(177)));};

    if ((PUMP_DOWN_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(178)));};

  }















  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;

  picoTestFrameworkIo.pumpActivateTickCount = 0;



  uint8_t tickCount = 2;

  while(tickCount-- > 0)

  {

    index++;

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

   ((void *)0)

   ), (_U_UINT)(197), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

   ((void *)0)

   ), (_U_UINT)(198), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

   ((void *)0)

   ), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);

  }



  if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(203)));}

                                                                                                   ;

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(204)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(205), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     0

                                                          ;

  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = (bool_t) 

                                                             1

                                                                 ;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  const uint32_t ptrnLength = sizeof(StartUpGreenLedPattern);

  for (uint32_t i = 0; i < ptrnLength*2; i++, index++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

   ((void *)0)

   ), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

   ((void *)0)

   ), (_U_UINT)(222), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

   ((void *)0)

   ), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);

    if (index < ptrnLength)

    {

      if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(227)));}

                                                                                                      ;

    }

    else

    {

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(231)));};

    }





    if ( i <= 47 )

    {

        UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

       ((void *)0)

       ), (_U_UINT)(237), UNITY_DISPLAY_STYLE_INT);

    }

    else

    {

        UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

       ((void *)0)

       ), (_U_UINT)(241), UNITY_DISPLAY_STYLE_INT);

    }



    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(244)));};

  }





  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = (bool_t) 

                                                             0

                                                                  ;

  for (uint32_t i = 0; 60 >= i ; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((++greenLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetGreenLED)), (

   ((void *)0)

   ), (_U_UINT)(254), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((++orangeLedRefreshExpectedCount)), (_U_SINT)((picoTestFrameworkIo.countSetOrangeLED)), (

   ((void *)0)

   ), (_U_UINT)(255), UNITY_DISPLAY_STYLE_INT);

  }

  UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(257), UNITY_DISPLAY_STYLE_INT);

}
