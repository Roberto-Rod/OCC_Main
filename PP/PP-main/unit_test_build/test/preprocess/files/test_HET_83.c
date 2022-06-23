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



}



void tearDown(void)

{}





void test_VerifyNREStateIsEnteredWhenNRErrorRaisedInIdle(void)

{

  I2E_Read_CMockIgnoreAndReturn(91, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(92, EC_OK_E);

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();



  StateMachine_Enter_NRE((bool_t) 

                        1

                            );



  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(108), UNITY_DISPLAY_STYLE_INT);



}





void test_VerifyNREStateIsEnteredWhenNRErrorRaisedInTherapy(void)

{

  I2E_Read_CMockIgnoreAndReturn(115, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(116, EC_OK_E);

   Application_Init();



  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(119), UNITY_DISPLAY_STYLE_INT);





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(122), UNITY_DISPLAY_STYLE_INT);

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);



  PicoTestFramework_SetPushButton((bool_t) 

                                 0

                                      );

  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(132), UNITY_DISPLAY_STYLE_INT);











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



  if (!(picoTestFrameworkIo.isPumpActivated)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(150)));};

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);







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

 ), (_U_UINT)(165), UNITY_DISPLAY_STYLE_INT);

  if ((THERAPY_DELIVERY_E == DeviceStatus_GetState())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(166)));};





  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT);



  StateMachine_Enter_NRE((bool_t) 

                        1

                            );



  PicoTestFramework_Tick();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((NRE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(176), UNITY_DISPLAY_STYLE_INT);



}
