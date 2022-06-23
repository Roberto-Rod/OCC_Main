#include "ErrorCode.h"
#include "Debug.h"
#include "MockTimer.h"
#include "MockPowerControl.h"
#include "MockI2CEEPROM.h"
#include "PerformanceLogger.h"
#include "unity.h"




typedef struct

{

  uint32_t address;

  uint8_t data[16];

  uint8_t length;

} eepromWriteData_t;



static eepromWriteData_t eepromWriteData;



static ErrorCode_t StubI2E_Write(uint32_t address, const uint8_t *data, uint8_t numBytes, int numCall)

{

  UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((numBytes)), (

 ((void *)0)

 ), (_U_UINT)(38), UNITY_DISPLAY_STYLE_INT);



  eepromWriteData.address = address;

  memcpy(eepromWriteData.data, data, numBytes);

  eepromWriteData.length = numBytes;

  return EC_OK_E;

}



void setUp()

{}



void tearDown()

{}

void test_SetInternalTemperature(void)

{

  const uint16_t testValue = 1234;

  PerformanceLogger_SetInternalTemperature(testValue);

  UnityAssertEqualNumber((_U_SINT)((testValue)), (_U_SINT)((PerformanceLogger_Get()->intTemperatureRaw)), (

 ((void *)0)

 ), (_U_UINT)(71), UNITY_DISPLAY_STYLE_INT);

}



void test_SetExternalTemperature(void)

{

  const uint16_t testValue = 1234;

  PerformanceLogger_SetExternalTemperature(testValue);

  UnityAssertEqualNumber((_U_SINT)((testValue)), (_U_SINT)((PerformanceLogger_Get()->extTemperatureRaw)), (

 ((void *)0)

 ), (_U_UINT)(78), UNITY_DISPLAY_STYLE_INT);

}



void test_SetDifferentialPressure(void)

{

  const uint16_t testValue = 1234;

  PerformanceLogger_SetDifferentialPressure(testValue);

  UnityAssertEqualNumber((_U_SINT)((testValue)), (_U_SINT)((PerformanceLogger_Get()->differentialPressureMilliBar)), (

 ((void *)0)

 ), (_U_UINT)(85), UNITY_DISPLAY_STYLE_INT);

}



void test_SetExternalPressure(void)

{

  const uint16_t testValue = 1234;

  PerformanceLogger_SetExternalPressure(testValue);

  UnityAssertEqualNumber((_U_SINT)((testValue)), (_U_SINT)((PerformanceLogger_Get()->externalPressureMilliBar)), (

 ((void *)0)

 ), (_U_UINT)(92), UNITY_DISPLAY_STYLE_INT);

}



void test_SetPumpHistory(void)

{

  const uint32_t testValue = 0x12345678;

  PerformanceLogger_SetPumpHistory(testValue);

  UnityAssertEqualNumber((_U_SINT)((testValue)), (_U_SINT)((PerformanceLogger_Get()->pumpHistory)), (

 ((void *)0)

 ), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

}



void test_SetBatteryVoltage(void)

{

  const uint16_t testValue = 1234;

  PerformanceLogger_SetBatteryVoltage(testValue);

  UnityAssertEqualNumber((_U_SINT)((testValue)), (_U_SINT)((PerformanceLogger_Get()->batteryVoltageMilliVolts)), (

 ((void *)0)

 ), (_U_UINT)(106), UNITY_DISPLAY_STYLE_INT);

}



void test_InitResetCounter(void)

{

  I2E_Init_CMockExpect(111);

  PerformanceLogger_Init();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_GetCurrentAddress())), (

 ((void *)0)

 ), (_U_UINT)(113), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_Get()->intTemperatureRaw)), (

 ((void *)0)

 ), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_Get()->extTemperatureRaw)), (

  ((void *)0)

  ), (_U_UINT)(116), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_Get()->batteryVoltageMilliVolts)), (

 ((void *)0)

 ), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_Get()->pumpHistory)), (

 ((void *)0)

 ), (_U_UINT)(118), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_Get()->externalPressureMilliBar)), (

 ((void *)0)

 ), (_U_UINT)(119), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_Get()->differentialPressureMilliBar)), (

 ((void *)0)

 ), (_U_UINT)(120), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PerformanceLogger_Get()->deviceStatus)), (

 ((void *)0)

 ), (_U_UINT)(121), UNITY_DISPLAY_STYLE_INT);

}





void test_FailedEEPROMWriteDoesNotAdvanceAddress(void)

{

  PerformanceLogger_SetCurrentAddress(0x0f);



  I2E_Write_CMockIgnoreAndReturn(129, EC_FAILED_E);

  MP_EnableExternalPeripheralsSupply_CMockExpect(130);

  PM_Delay_CMockExpect(131, 8);

  PM_Delay_CMockExpect(132, 10);

  MP_DisableExternalPeripheralsSupply_CMockExpect(133);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((PerformanceLogger_Persist())), (

 ((void *)0)

 ), (_U_UINT)(134), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(_US32)((0x0f)), (_U_SINT)(_US32)((PerformanceLogger_GetCurrentAddress())), (

 ((void *)0)

 ), (_U_UINT)(135), UNITY_DISPLAY_STYLE_INT32);

}



void test_PersistWriteToEEPROMAndAdvanceAddress(void)

{

  I2E_Write_StubWithCallback(StubI2E_Write);

  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_Delay_CMockIgnore();

  MP_DisableExternalPeripheralsSupply_CMockIgnore();





  PerformanceLogger_SetCurrentAddress(0x0f);



  PerformanceLogger_SetDifferentialPressure(0x1234);

  PerformanceLogger_SetExternalPressure(0x3456);

  PerformanceLogger_SetPumpHistory(0x5678ABCD);

  PerformanceLogger_SetBatteryVoltage(0x7890);



  PerformanceLogger_SetInternalTemperature(0x90AB);

  PerformanceLogger_SetExternalTemperature(0x90AB);

  PerformanceLogger_SetStatus(0xDA);

  PerformanceLogger_SetPumpDownDuration(0xCE);





  UnityAssertEqualNumber((_U_SINT)((0x1234)), (_U_SINT)((PerformanceLogger_Get()->differentialPressureMilliBar)), (

 ((void *)0)

 ), (_U_UINT)(159), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x3456)), (_U_SINT)((PerformanceLogger_Get()->externalPressureMilliBar)), (

 ((void *)0)

 ), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x5678ABCD)), (_U_SINT)((PerformanceLogger_Get()->pumpHistory)), (

 ((void *)0)

 ), (_U_UINT)(161), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x7890)), (_U_SINT)((PerformanceLogger_Get()->batteryVoltageMilliVolts)), (

 ((void *)0)

 ), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xDA)), (_U_SINT)((PerformanceLogger_Get()->deviceStatus)), (

 ((void *)0)

 ), (_U_UINT)(163), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x90AB)), (_U_SINT)((PerformanceLogger_Get()->intTemperatureRaw)), (

 ((void *)0)

 ), (_U_UINT)(164), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x90AB)), (_U_SINT)((PerformanceLogger_Get()->extTemperatureRaw)), (

 ((void *)0)

 ), (_U_UINT)(165), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xCE)), (_U_SINT)((PerformanceLogger_Get()->lastPumpDownDuration100Ms)), (

 ((void *)0)

 ), (_U_UINT)(166), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PerformanceLogger_Persist())), (

 ((void *)0)

 ), (_U_UINT)(168), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(_US32)((0x0f + 16)), (_U_SINT)(_US32)((PerformanceLogger_GetCurrentAddress())), (

 ((void *)0)

 ), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT32);



  UnityAssertEqualNumber((_U_SINT)((0x34)), (_U_SINT)((eepromWriteData.data[0])), (

 ((void *)0)

 ), (_U_UINT)(171), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x12)), (_U_SINT)((eepromWriteData.data[1])), (

 ((void *)0)

 ), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x56)), (_U_SINT)((eepromWriteData.data[2])), (

 ((void *)0)

 ), (_U_UINT)(173), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x34)), (_U_SINT)((eepromWriteData.data[3])), (

 ((void *)0)

 ), (_U_UINT)(174), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xCD)), (_U_SINT)((eepromWriteData.data[4])), (

 ((void *)0)

 ), (_U_UINT)(175), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAB)), (_U_SINT)((eepromWriteData.data[5])), (

 ((void *)0)

 ), (_U_UINT)(176), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x78)), (_U_SINT)((eepromWriteData.data[6])), (

 ((void *)0)

 ), (_U_UINT)(177), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x56)), (_U_SINT)((eepromWriteData.data[7])), (

 ((void *)0)

 ), (_U_UINT)(178), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x90)), (_U_SINT)((eepromWriteData.data[8])), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x78)), (_U_SINT)((eepromWriteData.data[9])), (

 ((void *)0)

 ), (_U_UINT)(180), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAB)), (_U_SINT)((eepromWriteData.data[10])), (

 ((void *)0)

 ), (_U_UINT)(181), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x90)), (_U_SINT)((eepromWriteData.data[11])), (

 ((void *)0)

 ), (_U_UINT)(182), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAB)), (_U_SINT)((eepromWriteData.data[12])), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x90)), (_U_SINT)((eepromWriteData.data[13])), (

 ((void *)0)

 ), (_U_UINT)(184), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xDA)), (_U_SINT)((eepromWriteData.data[14])), (

 ((void *)0)

 ), (_U_UINT)(185), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xCE)), (_U_SINT)((eepromWriteData.data[15])), (

 ((void *)0)

 ), (_U_UINT)(186), UNITY_DISPLAY_STYLE_INT);

}



void test_IPDDuration(void)

{

  const uint8_t duration = 123;

  PerformanceLogger_SetPumpDownDuration(duration);

  UnityAssertEqualNumber((_U_SINT)((duration)), (_U_SINT)((PerformanceLogger_GetPumpDownDuration100Ms())), (

 ((void *)0)

 ), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);

}



void test_SkipToNextBlock(void)

{

  const uint32_t address = PerformanceLogger_GetCurrentAddress();

  PerformanceLogger_SkipToNextTimeline();

  UnityAssertEqualNumber((_U_SINT)((address+16)), (_U_SINT)((PerformanceLogger_GetCurrentAddress())), (

 ((void *)0)

 ), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);

}
