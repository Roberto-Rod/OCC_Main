#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "MockWatchdog.h"
#include "Assert.h"
#include "PushButton.h"
#include "DutyCycle.h"
#include "UIInterfaces.h"
#include "Timer.h"
#include "MockBattery.h"
#include "PerformanceLogger.h"
#include "LoggingManager.h"
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

  Battery_CheckVoltageBounds_CMockIgnoreAndReturn(80, EC_OK_E);

  MP_GetBoostDemand_CMockIgnoreAndReturn(81, ((uint8_t)19));

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







void test_LogInitialPumpDownDurationInPersistentMemoryWhenInTherapyDelivery(void)

{

  I2E_Read_CMockIgnoreAndReturn(102, EC_OK_E);

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(106), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(112), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(119), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(132), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(139), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  picoTestFrameworkIo.getVacuumMeasurement = 90;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  uint32_t const expectedPumpDownDuration = 10;



  for (uint32_t i = 0; expectedPumpDownDuration > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(155), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(157), UNITY_DISPLAY_STYLE_INT);











  picoTestFrameworkIo.getVacuumMeasurement = 107;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      1

                                                          ;

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(166, (bool_t) 

 0

 );



  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(173), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((expectedPumpDownDuration)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(174), UNITY_DISPLAY_STYLE_INT);









  const uint32_t oneMinuteTickCount = 600;

  MP_EnableMainCircuitPower_CMockIgnore();

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(181, (bool_t) 

 0

 );

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  therapyVacuumAchieved = (bool_t) 

                         1

                             ;

  State_t expectedState = PUMP_DOWN_E;



  for (uint32_t i = 0; i < oneMinuteTickCount - 17; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();





    if (i >= 189 )

    {

       expectedState = THERAPY_DELIVERY_E;

    }



    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(197), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

   ((void *)0)

   ), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((expectedPumpDownDuration)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

   ((void *)0)

   ), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);

  }







  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(209), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(210), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(211), UNITY_DISPLAY_STYLE_INT);







  for (uint32_t i = 0; i < oneMinuteTickCount; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((eepromWriteNumCall)), (

   ((void *)0)

   ), (_U_UINT)(217), UNITY_DISPLAY_STYLE_INT);

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

  }



  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(224), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(225), UNITY_DISPLAY_STYLE_INT);



}





void test_LogUnsuccessfulInitialPumpDownDurationInPersistentMemoryWhenInFault(void)

{

  I2E_Read_CMockIgnoreAndReturn(232, EC_OK_E);

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(236), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(242), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(249), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_SetPushButton((bool_t) 

                                 1

                                     );

  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(257), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(264), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(271), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  picoTestFrameworkIo.getVacuumMeasurement = 90;

  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = (bool_t) 

                                                      0

                                                           ;

  uint32_t const expectedPumpDownDuration = 200;



  for (uint32_t i = 0; expectedPumpDownDuration > i; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



  }



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(288), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(289), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(290), UNITY_DISPLAY_STYLE_INT);







  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(298), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(299), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(301), UNITY_DISPLAY_STYLE_INT);









  const uint32_t oneMinuteTickCount = 600;

  MP_EnableMainCircuitPower_CMockIgnore();

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(308, (bool_t) 

 0

 );

  TherapyDeliveryTargetVacuumUpdate_CMockIgnore();

  therapyVacuumAchieved = (bool_t) 

                         1

                             ;



  for (uint32_t i = 0; i < oneMinuteTickCount - 207; i++)

  {

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(317), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

   ((void *)0)

   ), (_U_UINT)(318), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

   ((void *)0)

   ), (_U_UINT)(319), UNITY_DISPLAY_STYLE_INT);

  }







  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(328), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(329), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(330), UNITY_DISPLAY_STYLE_INT);







  for (uint32_t i = 0; i < oneMinuteTickCount; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((eepromWriteNumCall)), (

   ((void *)0)

   ), (_U_UINT)(336), UNITY_DISPLAY_STYLE_INT);

    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(340), UNITY_DISPLAY_STYLE_INT);

  }



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(343), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(344), UNITY_DISPLAY_STYLE_INT);

}
