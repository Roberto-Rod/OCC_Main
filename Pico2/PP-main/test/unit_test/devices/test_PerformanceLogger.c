/*****************************************************************************
 *   File        : test_PerformanceLogger.c
 *
 *   Description: Source Code for test performance Logger.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include <mem.h>
#include "unity.h"
#include "PerformanceLogger.h"
#include "MockI2CEEPROM.h"
#include "MockPowerControl.h"
#include "MockTimer.h"
#include "Debug.h"
#include "ErrorCode.h"

typedef struct
{
  uint32_t address;
  uint8_t data[16];
  uint8_t length;
} eepromWriteData_t;

static eepromWriteData_t eepromWriteData;

static ErrorCode_t StubI2E_Write(uint32_t address, const uint8_t *data, uint8_t numBytes, int numCall)
{
  TEST_ASSERT_EQUAL_INT(16, numBytes);

  eepromWriteData.address = address;
  memcpy(eepromWriteData.data, data, numBytes);
  eepromWriteData.length = numBytes;

 // printf("data: address %xh \n", address);
 // for (int i = 0; i < 16; i++)
 // {
   // printf("%d (%xh),", eepromWriteData.data[i], eepromWriteData.data[i]);
 // }
  // printf("\n");

  return EC_OK_E;
}

void setUp()
{}

void tearDown()
{}

// void test_SetTemperature(void)
// {
//   const uint16_t testValue = 1234;
//   //PerformanceLogger_SetTemperature(testValue);
//   TEST_ASSERT_EQUAL_INT(testValue, PerformanceLogger_Get()->deviceTemperatureCentiDegCelcius);
// }

void test_SetInternalTemperature(void)
{
  const uint16_t testValue = 1234;
  PerformanceLogger_SetInternalTemperature(testValue);
  TEST_ASSERT_EQUAL_INT(testValue, PerformanceLogger_Get()->intTemperatureRaw);
}

void test_SetExternalTemperature(void)
{
  const uint16_t testValue = 1234;
  PerformanceLogger_SetExternalTemperature(testValue);
  TEST_ASSERT_EQUAL_INT(testValue, PerformanceLogger_Get()->extTemperatureRaw);
}

void test_SetDifferentialPressure(void)
{
  const uint16_t testValue = 1234;
  PerformanceLogger_SetDifferentialPressure(testValue);
  TEST_ASSERT_EQUAL_INT(testValue, PerformanceLogger_Get()->differentialPressureMilliBar);
}

void test_SetExternalPressure(void)
{
  const uint16_t testValue = 1234;
  PerformanceLogger_SetExternalPressure(testValue);
  TEST_ASSERT_EQUAL_INT(testValue, PerformanceLogger_Get()->externalPressureMilliBar);
}

void test_SetPumpHistory(void)
{
  const uint32_t testValue = 0x12345678;
  PerformanceLogger_SetPumpHistory(testValue);
  TEST_ASSERT_EQUAL_INT(testValue, PerformanceLogger_Get()->pumpHistory);
}

void test_SetBatteryVoltage(void)
{
  const uint16_t testValue = 1234;
  PerformanceLogger_SetBatteryVoltage(testValue);
  TEST_ASSERT_EQUAL_INT(testValue, PerformanceLogger_Get()->batteryVoltageMilliVolts);
}

void test_InitResetCounter(void)
{
  I2E_Init_Expect();
  PerformanceLogger_Init();
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetCurrentAddress());

  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_Get()->intTemperatureRaw);
   TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_Get()->extTemperatureRaw);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_Get()->batteryVoltageMilliVolts);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_Get()->pumpHistory);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_Get()->externalPressureMilliBar);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_Get()->differentialPressureMilliBar);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_Get()->deviceStatus);
}


void test_FailedEEPROMWriteDoesNotAdvanceAddress(void)
{
  PerformanceLogger_SetCurrentAddress(0x0f);

  I2E_Write_IgnoreAndReturn(EC_FAILED_E);
  MP_EnableExternalPeripheralsSupply_Expect();
  PM_Delay_Expect(8); //8 ms delay to wait for power supply to stable
  PM_Delay_Expect(10); //10 ms delay to wait for the EEPROM HW to coplete the write operation before switching the supply off
  MP_DisableExternalPeripheralsSupply_Expect();
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, PerformanceLogger_Persist());
  TEST_ASSERT_EQUAL_INT32(0x0f, PerformanceLogger_GetCurrentAddress());
}

void test_PersistWriteToEEPROMAndAdvanceAddress(void)
{
  I2E_Write_StubWithCallback(StubI2E_Write);
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_Delay_Ignore(); //8 ms delay to wait for power supply to stable
  MP_DisableExternalPeripheralsSupply_Ignore();


  PerformanceLogger_SetCurrentAddress(0x0f);

  PerformanceLogger_SetDifferentialPressure(0x1234);
  PerformanceLogger_SetExternalPressure(0x3456);
  PerformanceLogger_SetPumpHistory(0x5678ABCD);
  PerformanceLogger_SetBatteryVoltage(0x7890);
  //PerformanceLogger_SetTemperature(0x90AB);
  PerformanceLogger_SetInternalTemperature(0x90AB);
  PerformanceLogger_SetExternalTemperature(0x90AB);
  PerformanceLogger_SetStatus(0xDA);
  PerformanceLogger_SetPumpDownDuration(0xCE);


  TEST_ASSERT_EQUAL_INT(0x1234, PerformanceLogger_Get()->differentialPressureMilliBar);
  TEST_ASSERT_EQUAL_INT(0x3456, PerformanceLogger_Get()->externalPressureMilliBar);
  TEST_ASSERT_EQUAL_INT(0x5678ABCD, PerformanceLogger_Get()->pumpHistory);
  TEST_ASSERT_EQUAL_INT(0x7890, PerformanceLogger_Get()->batteryVoltageMilliVolts);
  TEST_ASSERT_EQUAL_INT(0xDA, PerformanceLogger_Get()->deviceStatus);
  TEST_ASSERT_EQUAL_INT(0x90AB, PerformanceLogger_Get()->intTemperatureRaw);
  TEST_ASSERT_EQUAL_INT(0x90AB, PerformanceLogger_Get()->extTemperatureRaw);
  TEST_ASSERT_EQUAL_INT(0xCE, PerformanceLogger_Get()->lastPumpDownDuration100Ms);

  TEST_ASSERT_EQUAL_INT(EC_OK_E, PerformanceLogger_Persist());
  TEST_ASSERT_EQUAL_INT32(0x0f + 16, PerformanceLogger_GetCurrentAddress());

  TEST_ASSERT_EQUAL_INT(0x34, eepromWriteData.data[0]);
  TEST_ASSERT_EQUAL_INT(0x12, eepromWriteData.data[1]);
  TEST_ASSERT_EQUAL_INT(0x56, eepromWriteData.data[2]);
  TEST_ASSERT_EQUAL_INT(0x34, eepromWriteData.data[3]);
  TEST_ASSERT_EQUAL_INT(0xCD, eepromWriteData.data[4]);
  TEST_ASSERT_EQUAL_INT(0xAB, eepromWriteData.data[5]);
  TEST_ASSERT_EQUAL_INT(0x78, eepromWriteData.data[6]);
  TEST_ASSERT_EQUAL_INT(0x56, eepromWriteData.data[7]);
  TEST_ASSERT_EQUAL_INT(0x90, eepromWriteData.data[8]);
  TEST_ASSERT_EQUAL_INT(0x78, eepromWriteData.data[9]);
  TEST_ASSERT_EQUAL_INT(0xAB, eepromWriteData.data[10]);
  TEST_ASSERT_EQUAL_INT(0x90, eepromWriteData.data[11]);
  TEST_ASSERT_EQUAL_INT(0xAB, eepromWriteData.data[12]);
  TEST_ASSERT_EQUAL_INT(0x90, eepromWriteData.data[13]);
  TEST_ASSERT_EQUAL_INT(0xDA, eepromWriteData.data[14]);
  TEST_ASSERT_EQUAL_INT(0xCE, eepromWriteData.data[15]);
}

void test_IPDDuration(void)
{
  const uint8_t duration = 123;
  PerformanceLogger_SetPumpDownDuration(duration);
  TEST_ASSERT_EQUAL_INT(duration, PerformanceLogger_GetPumpDownDuration100Ms());
}

void test_SkipToNextBlock(void)
{
  const uint32_t address = PerformanceLogger_GetCurrentAddress();
  PerformanceLogger_SkipToNextTimeline();
  TEST_ASSERT_EQUAL_INT(address+16, PerformanceLogger_GetCurrentAddress());
}
