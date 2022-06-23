#include "MockBattery.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "MockWatchdog.h"
#include "PerformanceLogger.h"
#include "LoggingManager.h"
#include "Assert.h"
#include "PushButton.h"
#include "DutyCycle.h"
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














static bool_t therapyVacuumAchieved;

static uint32_t eepromAddress;

static uint8_t eepromBytesWritten;

static int eepromWriteNumCall;



bool_t Stub_isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum, int NumCall)

{

  return therapyVacuumAchieved;

}





ErrorCode_t StubI2E_Write(uint32_t address, uint8_t *data, uint8_t numBytes, int numCall)

{

  eepromAddress = address;

  eepromBytesWritten = numBytes;

  eepromWriteNumCall++;

  return EC_OK_E;

}



void setUp(void)

{

  PicoTestFramework_Setup();

  isTargetTherapyDeliveryVacuumAchieved_StubWithCallback(Stub_isTargetTherapyDeliveryVacuumAchieved);

  MP_EnableExternalPeripheralsSupply_CMockIgnore();





  I2E_Write_StubWithCallback(StubI2E_Write);



  eepromAddress = 0;

  eepromBytesWritten = 0;

  eepromWriteNumCall = 0;



}



void tearDown(void)

{}





void test_PerformanceDataIsStoredEveryMinuteDuringMPD(void)

{

  I2E_Read_CMockIgnoreAndReturn(98, EC_OK_E);

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(102), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(108), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(114), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(121), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(127), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(134), UNITY_DISPLAY_STYLE_INT);



  const uint32_t oneMinuteTickCount = 600;

  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  MP_EnableMainCircuitPower_CMockIgnore();

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(139, (bool_t) 

 0

 );

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  therapyVacuumAchieved = (bool_t) 

                         1

                             ;

  State_t expectedState = PUMP_DOWN_E;

  picoTestFrameworkIo.getVacuumMeasurement = 107;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;











  uint32_t tickCount = (200);

  for (uint32_t i = 0; i < tickCount; i++)

  {



    if (i >= ((200)))

    {

      expectedState = THERAPY_DELIVERY_E;

    }



    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

  }





  for (uint32_t i = 0; i < oneMinuteTickCount - 6 -(200); i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(171), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

   ((void *)0)

   ), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

  }





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromAddress)), (

 ((void *)0)

 ), (_U_UINT)(181), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((eepromBytesWritten)), (

 ((void *)0)

 ), (_U_UINT)(182), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);



  for (uint32_t i = 0; i < oneMinuteTickCount; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((eepromWriteNumCall)), (

   ((void *)0)

   ), (_U_UINT)(187), UNITY_DISPLAY_STYLE_INT);

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(191), UNITY_DISPLAY_STYLE_INT);

  }



  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((eepromAddress)), (

 ((void *)0)

 ), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((eepromBytesWritten)), (

 ((void *)0)

 ), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);

}
