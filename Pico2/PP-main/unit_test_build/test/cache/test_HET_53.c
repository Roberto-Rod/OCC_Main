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









void test_LongButtonPressStartedInIdleDoesNotSwitchTheDeviceOffDuringInitialPumpDownOrTherapyDelivery(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(78, (bool_t) 

 0

 );

  Application_Init();



  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(81), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();

  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(89)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(90)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(91), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );



  for (uint32_t i = 0; 3 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(106)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(107)));};

  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(108)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(109), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateTickCount = 0;



  for (uint32_t i = 0; 100 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((50)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(123), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);







  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(134), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = (bool_t) 

                                                             1

                                                                 ;



  for(uint32_t i = 0; 50 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(148), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );



  for(uint32_t i = 0; 30 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

}

void test_LongButtonPressStartedInIdleDoesNotSwitchTheDeviceOffDuringInitialPumpDownOrTherapyDeliveryAfterGoingFromLeakToIdle(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(173, (bool_t) 

 0

 );

  Application_Init();



  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(176), UNITY_DISPLAY_STYLE_INT);





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(189), UNITY_DISPLAY_STYLE_INT);











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





  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(209)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(210), UNITY_DISPLAY_STYLE_INT);







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

 ), (_U_UINT)(224), UNITY_DISPLAY_STYLE_INT);

  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(225)));};









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  for(uint32_t i = 0; 30 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(239)));};









  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = (bool_t) 

                                                     1

                                                         ;



  for (uint32_t i = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState(); i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }





  if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(254)));};











  for (uint32_t i = 0; i < 20; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(266)));};

    if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(267)));};

    if ((FAULT_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(268)));};

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



  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(289)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(290)));};

  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(291)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(292), UNITY_DISPLAY_STYLE_INT);











  uint32_t button_press_ticks = 3;

  for (; 10 > button_press_ticks; button_press_ticks++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(305)));};

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(306)));};

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(307), UNITY_DISPLAY_STYLE_INT);

  }







  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;

  for (; 12 > button_press_ticks; button_press_ticks++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(319)));};



  }

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(322), UNITY_DISPLAY_STYLE_INT);









  for (; (20) > button_press_ticks; button_press_ticks++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(333)));};

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(334), UNITY_DISPLAY_STYLE_INT);

  }











  button_press_ticks++;

  PicoTestFramework_Tick();

  Application_Run();







  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(347)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(348)));};

  UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(349), UNITY_DISPLAY_STYLE_INT);





  for(uint32_t i = 0; 29 > i; i++)

  {

    if (10 <i)

    {

      PicoTestFramework_SetPushButton((bool_t) 

                                     0

                                          );

    }



    PicoTestFramework_Tick();

    Application_Run();





    if (i<19)

    {

      if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(365)));};

      if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(366)));};

    }

    else

    {



      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(371)));};

      if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(372)));};

    }



    UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(375), UNITY_DISPLAY_STYLE_INT);

  }







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );



  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(386)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(387)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(388), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_Tick();

  Application_Run();

  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(397)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(398)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(399), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );



  for (uint32_t i = 0; 3 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(414)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(415)));};

  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(416)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(417), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateTickCount = 0;



  for (uint32_t i = 0; 100 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((50)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(431), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(432), UNITY_DISPLAY_STYLE_INT);







  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(442), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = (bool_t) 

                                                             1

                                                                 ;



  for(uint32_t i = 0; 10 > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(454), UNITY_DISPLAY_STYLE_INT);

  }



}
