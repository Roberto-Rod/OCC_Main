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
#include "Battery.h"
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












static uint8_t eepromBytesWritten;

static int eepromWriteNumCall;

static uint8_t eepromBytes[2048];







static ErrorCode_t Stub_I2E_Write(uint32_t address, uint8_t *data, uint8_t numBytes, int numCall)

{

  eepromWriteNumCall++;



  if (2048 > address + numBytes)

  {

    for(int count = 0; count < numBytes; count++)

    {

      eepromBytes[count + address] = data[count];

    }

    eepromBytesWritten = numBytes;

  }



  return EC_OK_E;

}







void setUp(void)

{

  PicoTestFramework_Setup();



  eepromBytesWritten = 0;

  eepromWriteNumCall = 0;

  memset(eepromBytes, 0xFF, sizeof(eepromBytes));



  I2E_Write_StubWithCallback(Stub_I2E_Write);

  I2E_Read_CMockIgnoreAndReturn(91, EC_OK_E);

  ADC_GetConversion_CMockIgnoreAndReturn(92, 0x2000);

  TX_Write_CMockIgnoreAndReturn(93, EC_OK_E);

}



void tearDown(void)

{}



void test_CompleteIctPostAndCheckTheEepromIsUnchangedThenRestartDeviceSkipPostAndCheckTheEepromIsStillUnchanged(void)

{



  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;





  Application_Init();

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);





  PicoTestFramework_Tick();

  Application_Run();





  if (!(picoTestFrameworkIo.isGreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(114)));};

  if (!(picoTestFrameworkIo.isOrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(115)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(116), UNITY_DISPLAY_STYLE_INT);





  uint8_t eepromInitialised[2048];

  memset(eepromInitialised, 0xFF, sizeof(eepromInitialised));



  POSTSubState_t expectedState = POST_STATE_00;

  for (int count = 0; count < 11; count++)

  {

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(125), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;



    PicoTestFramework_Tick();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(134), UNITY_DISPLAY_STYLE_INT);

    expectedState++;

  }



  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(138), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((memcmp(eepromBytes, eepromInitialised, sizeof(eepromInitialised)))), (

 ((void *)0)

 ), (_U_UINT)(139), UNITY_DISPLAY_STYLE_INT);









  PORTAbits.RA0 = 1;

  PORTAbits.RA1 = 0;

  eepromWriteNumCall = 0;



  Application_Init();

  PicoTestFramework_Tick();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(153), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((eepromWriteNumCall)), (

 ((void *)0)

 ), (_U_UINT)(154), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((memcmp(eepromBytes, eepromInitialised, sizeof(eepromInitialised)))), (

 ((void *)0)

 ), (_U_UINT)(155), UNITY_DISPLAY_STYLE_INT);

}
