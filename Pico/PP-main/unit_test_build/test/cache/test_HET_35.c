#include "Battery.h"
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
















void setUp(void)

{

  PicoTestFramework_Setup();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(63, EC_OK_E);

}



void tearDown(void)

{}





void test_TheDeviceDetectsEndOfLifeErrorDuringPumpdownAndCannotBeRestartedToDeliverFurtherTherapy(void)

{

  I2E_Read_CMockIgnoreAndReturn(72, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(73, EC_OK_E);

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



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(105)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(106), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;



  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);

  if ((PUMP_DOWN_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(118)));};









  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;



  PicoTestFramework_Tick();

  Application_Run();





  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(133), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                         1

                                             ;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint32_t i = 0; i < 5; i++)

  {

    if (4 == i)

    {

      picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                             0

                                                  ;

    }

    PicoTestFramework_Tick();

    Application_Run();



  }



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(152)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(153)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(154), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.getVacuumTickCount)), (

 ((void *)0)

 ), (_U_UINT)(155), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                         1

                                             ;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint32_t i = 0; i < 30; i++)

  {

    if (29 == i)

    {

      picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                             0

                                                  ;

    }

    PicoTestFramework_Tick();

    Application_Run();



  }



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(175)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(176)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(177), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.getVacuumTickCount)), (

 ((void *)0)

 ), (_U_UINT)(178), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint32_t i = 0; i < 108000; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(193)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(194)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.getVacuumTickCount)), (

 ((void *)0)

 ), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(197), UNITY_DISPLAY_STYLE_INT);



}





void test_TheDeviceDetectsEndOfLifeErrorDuringTherapyDeliveryAndCannotBeRestartedToDeliverFurtherTherapy(void)

{

  I2E_Read_CMockIgnoreAndReturn(204, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(205, EC_OK_E);

  Application_Init();







  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(210), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(214), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(220), UNITY_DISPLAY_STYLE_INT);











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



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(237)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(238), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;



  PicoTestFramework_Tick();

  Application_Run();

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(250), UNITY_DISPLAY_STYLE_INT);





  picoTestFrameworkIo.getVacuumMeasurement = 107;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;





  while (THERAPY_DELIVERY_E != DeviceStatus_GetState())

  {

     PicoTestFramework_Tick();

     Application_Run();

  }



  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);





  picoTestFrameworkIo.getVacuumMeasurement = 90;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  for(uint32_t i = 0; i <10; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();

  }



  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(274)));};







  picoTestFrameworkIo.getVacuumMeasurement = 90;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;



  PicoTestFramework_Tick();

  Application_Run();

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(287), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                         1

                                             ;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint32_t i = 0; i < 5; i++)

  {

    if (4 == i)

    {

      picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                             0

                                                  ;

    }

    PicoTestFramework_Tick();

    Application_Run();



  }



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(306)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(307)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(308), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.getVacuumTickCount)), (

 ((void *)0)

 ), (_U_UINT)(309), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(310), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                         1

                                             ;

  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint32_t i = 0; i < 30; i++)

  {

    if (29 == i)

    {

      picoTestFrameworkIo.isPushButtonPress = (bool_t) 

                                             0

                                                  ;

    }

    PicoTestFramework_Tick();

    Application_Run();



  }



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(329)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(330)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(331), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.getVacuumTickCount)), (

 ((void *)0)

 ), (_U_UINT)(332), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(333), UNITY_DISPLAY_STYLE_INT);









  picoTestFrameworkIo.getVacuumTickCount = 0;

  picoTestFrameworkIo.pumpActivateTickCount = 0;

  for (uint32_t i = 0; i < 108000; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(347)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(348)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.pumpActivateTickCount)), (

 ((void *)0)

 ), (_U_UINT)(349), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((picoTestFrameworkIo.getVacuumTickCount)), (

 ((void *)0)

 ), (_U_UINT)(350), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(351), UNITY_DISPLAY_STYLE_INT);



}
