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













void test_UserCanTurnOffDeviceDuringPumpDown(void)

{

  I2E_Read_CMockIgnoreAndReturn(73, EC_OK_E);

  Application_Init();

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(75), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(81), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(87), UNITY_DISPLAY_STYLE_INT);









  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(96)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(97)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(98), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(103)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(104)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(105), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_Tick();

  Application_Run();



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(110)));};



  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(112)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(113)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);









  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(124)));};



  if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(126)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(127)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(128), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );



  for (uint8_t i = 0; i < 8; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(140)));};

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(141)));};

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(142), UNITY_DISPLAY_STYLE_INT);

  }











  for (uint8_t j = 0; j < 10; j++)

  {

    picoTestFrameworkIo.isGreenLEDEnabled = (bool_t) 

                                           0

                                                ;

    picoTestFrameworkIo.isOrangeLEDEnabled = (bool_t) 

                                            0

                                                 ;

    PicoTestFramework_SetPushButton((bool_t) 

                                   1

                                       );

    PicoTestFramework_Tick();

    Application_Run();



    if(0==j%2)

    {

      if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(159)));};

    }

    else

    {

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(163)));};

    }

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(165)));};

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(166), UNITY_DISPLAY_STYLE_INT);

  }









  for (uint8_t j = 0; j < 10; j++)

  {

    picoTestFrameworkIo.isGreenLEDEnabled = (bool_t) 

                                           0

                                                ;

    picoTestFrameworkIo.isOrangeLEDEnabled = (bool_t) 

                                            0

                                                 ;

    PicoTestFramework_SetPushButton((bool_t) 

                                   0

                                        );

    PicoTestFramework_Tick();

    Application_Run();





    if(0==j%2)

    {

      if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(183)));};

    }

    else

    {

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(187)));};

    }

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(189)));};

    UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(190), UNITY_DISPLAY_STYLE_INT);

  }

  for (uint32_t j = 0; j < ((20) + 1); j++)

  {

    picoTestFrameworkIo.isGreenLEDEnabled = (bool_t) 

                                           0

                                                ;

    picoTestFrameworkIo.isOrangeLEDEnabled = (bool_t) 

                                            0

                                                 ;

    PicoTestFramework_SetPushButton((bool_t) 

                                   1

                                       );

    PicoTestFramework_Tick();

    Application_Run();



    if((20) == j)

    {



      if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(212)));};

      if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(213)));};



      UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

     ((void *)0)

     ), (_U_UINT)(215), UNITY_DISPLAY_STYLE_INT);

    }

    else

    {



      if(0==j%2)

      {

        if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(222)));};

      }

      else

      {

        if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(226)));};

      }

      if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(228)));};

      UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

     ((void *)0)

     ), (_U_UINT)(229), UNITY_DISPLAY_STYLE_INT);

    }

  }















  for (uint32_t j = 0; j < 29; j++)

  {

    if(15 < j)

    {

      PicoTestFramework_SetPushButton((bool_t) 

                                     0

                                          );

    }



    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((SHUT_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(249), UNITY_DISPLAY_STYLE_INT);





    if (j<19)

    {

       if ((picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(254)));};

       if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(255)));};

    }

    else

    {

      if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(259)));};

      if ((picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(260)));};

    }

  }





  for (uint32_t j = 0; j < 10; j++)

  {

    PicoTestFramework_SetPushButton((bool_t) 

                                   0

                                        );

    PicoTestFramework_Tick();

    Application_Run();





    if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(272)));};

    if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(273)));};

    UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);

  }

}
