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
#include "Assert.h"
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
#include "MockLoggingManager.h"
#include "AlertManager.h"
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







void test_DuringIPDWhenTargetPressureIsReachedTransitToMPD(void)

{

  I2E_Read_CMockIgnoreAndReturn(95, EC_OK_E);

  Application_Init();







  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(104), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(110), UNITY_DISPLAY_STYLE_INT);









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



  uint32_t index = 0;



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(136)));};

  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(137)));};

  if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(139)));}

                                                                                                 ;

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(140)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(141), UNITY_DISPLAY_STYLE_INT);



  index++;









  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(153)));};

  if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(155)));}

                                                                                                   ;

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(156)));};

  if ((PUMP_DOWN_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(157)));};









  for (uint8_t i = 0; i < 149; i++)

  {

    index++;

    PicoTestFramework_Tick();

    Application_Run();



    if (((0 == i%2) ? picoTestFrameworkIo.isPumpActivated : !picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(169)));}

                                                                                                 ;

    if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(171)));}

                                                                                                   ;

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(172)));};

    if ((PUMP_DOWN_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(173)));};

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



    if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(192)));}

                                                                                                   ;

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(193)));};

  }

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     0

                                                          ;

  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = (bool_t) 

                                                             1

                                                                 ;

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  const uint32_t ptrnLength = sizeof(StartUpGreenLedPattern);

  State_t expectedState = PUMP_DOWN_E;



  for (uint32_t i = 0; i < ptrnLength*2; i++)

  {

    index++;

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(214)));};

    if (index < ptrnLength)

    {

      if (((StartUpGreenLedPattern[index])? picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(218)));}

                                                                                                      ;

    }

    else

    {

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(222)));};

    }

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(224)));};



    if (i >= ( 48 ))

    {

       expectedState = THERAPY_DELIVERY_E;

    }

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(230), UNITY_DISPLAY_STYLE_INT);

  }

}
