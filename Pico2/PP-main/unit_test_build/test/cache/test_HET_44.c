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

  LoggingManager_Run_CMockIgnoreAndReturn(84, EC_OK_E);

}



void tearDown(void)

{}











void test_AlertTheUserAccordingToACompositeLedFlashinPatternWhenTargetPressureIsReachedAndBeyond(void)

{

  I2E_Read_CMockIgnoreAndReturn(96, EC_OK_E);

  Application_Init();







  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(101), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(105), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(111), UNITY_DISPLAY_STYLE_INT);









  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(120)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(121)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(122), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(127)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(128)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(129), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(134)));};

  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(135)));};

  uint32_t index = 0;

  if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(138)));}

                                                                                                   ;

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(139)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(140), UNITY_DISPLAY_STYLE_INT);











  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  index++;

  for (uint8_t i = 0; i < 150; i++, index++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(155)));}

                                                                                                   ;

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(156)));};

    if ((PUMP_DOWN_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(157)));};

  }















  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;



  uint8_t tickCount = 2;

  while(tickCount-- > 0)

  {

    index++;

    PicoTestFramework_Tick();

    Application_Run();



  }

  if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(177)));}

                                                                                                   ;

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(178)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     0

                                                          ;

  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = (bool_t) 

                                                             1

                                                                 ;

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  State_t expectedState = PUMP_DOWN_E;



  const uint32_t ptrnLength = sizeof(StartUpGreenLedPattern);

  for (uint32_t i = 0; i < ptrnLength*2; i++, index++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    if (index < ptrnLength)

    {

      if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(199)));}

                                                                                                      ;

    }

    else

    {

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(203)));};

    }

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(205)));};





    if (i >= 48 )

    {

       expectedState = THERAPY_DELIVERY_E;

    }



    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(213), UNITY_DISPLAY_STYLE_INT);

  }



}
