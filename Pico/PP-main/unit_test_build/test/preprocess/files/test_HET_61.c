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









void test_RestartTheTherapyWithShortButtonPressFromLeakErrorCondition(void)

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





  for ( uint16_t i = 0; i <= 200; i++ )

  {

     PicoTestFramework_Tick();

     Application_Run();

  }

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(123), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  for(uint32_t i = 0; 30 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(138)));};









  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     1

                                                         ;



  for (uint32_t i = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState(); i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(152)));};









  for (uint32_t i = 0; i < 20; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(163)));};

    if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(164)));};

    if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(165)));};

  }











  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  for (uint32_t i = 0; i < 1; i++)

  {

      PicoTestFramework_Tick();

      Application_Run();

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(178)));};

      if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(179)));};

   }





  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(186)));};

  if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(187)));};





  PicoTestFramework_Tick();

  Application_Run();



  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(193)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(194)));};

  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(195)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );



  PicoTestFramework_Tick();

  Application_Run();





  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(206)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(207)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(208), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;



  PicoTestFramework_Tick();

  Application_Run();





  PicoTestFramework_Tick();

  Application_Run();





  for ( uint16_t i = 0; i <= 205; i++ )

  {

     PicoTestFramework_Tick();

     Application_Run();

  }





  if (((0) != (picoTestFrameworkIo.pumpActivateTickCount))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(231)));};

  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(232)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(233)));};

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(234), UNITY_DISPLAY_STYLE_INT);

}
