/*****************************************************************************
 *   File        : test_Pressure_Part3.c
 *
 *   Description: Source Code for test of Pressure measurements.
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

#include "unity.h"
#include <string.h>
#include "Pressure_Part3.h"
#include "MockPressure_Part4.h"
#include "MockTimer.h"
#include "Mocki2c.h"


typedef enum {
    PS_NONE_E = 0,
    PS_EXTERNAL_E,
    PS_INTERNAL_E,
    PS_BOTH_E   //size of the error code
} PressureSensorFail_t; 

// Reasonable range for pressure readings in mBar
#define MAX_PRESSURE_MB ((uint16_t) 0x044C)  // 1100 mBar
#define MIN_PRESSURE_MB ((uint16_t) 0x0226)  //  550 mBar

static uint8_t ExtPressureDeviceWriteCount = 0;
static uint8_t IntPressureDeviceWriteCount  = 0;
static uint8_t ExtPressureDeviceReadCount = 0;
static uint8_t IntPressureDeviceReadCount = 0;
static PressureSensorFail_t SensorWriteForceFail = PS_NONE_E;
static PressureSensorFail_t SensorReadForceFail = PS_NONE_E;
static uint8_t WriteDataBufferTest[20];
static uint8_t ReadDataBufferTest[20];

// Stub for Write onto pressure sensor via I2C whose return value can be forced based on SensorWriteForceFail
static bool_t Stub_PM_WritePressureSensors(uint8_t Device, uint8_t DataLength, uint8_t *DataBuffer, int NumCall)
{
  bool_t result = TRUE;
  
  if (I2C_ADD_EXT_SENSOR == Device)
  {
    ExtPressureDeviceWriteCount++;
    result = ((PS_EXTERNAL_E == SensorWriteForceFail) || (PS_BOTH_E == SensorWriteForceFail)) ? FALSE:TRUE;
  }
  else if (I2C_ADD_INT_SENSOR == Device)
  {
    IntPressureDeviceWriteCount++;
    result = ((PS_INTERNAL_E == SensorWriteForceFail)  || (PS_BOTH_E == SensorWriteForceFail))? FALSE:TRUE;
  }
  else
  {
    result = FALSE;
  }
  
  memcpy(WriteDataBufferTest, DataBuffer, DataLength);
  
  return result;
}

// Stub for Read from pressure sensor via I2C whose return value can be forced based on SensorReadForceFail
static bool_t Stub_PM_ReadPressureSensors(uint8_t Device, uint8_t DataLength, uint8_t DataAddress, uint8_t *DataBuffer, int NumCall)
{
  bool_t result = TRUE;
  
  if (I2C_ADD_EXT_SENSOR == Device)
  {
    ExtPressureDeviceReadCount++;
    result = ((PS_EXTERNAL_E == SensorReadForceFail) || (PS_BOTH_E == SensorReadForceFail)) ? FALSE:TRUE;
  }
  else if (I2C_ADD_INT_SENSOR == Device)
  {
    IntPressureDeviceReadCount++;
    result = ((PS_INTERNAL_E == SensorReadForceFail) || (PS_BOTH_E == SensorReadForceFail)) ? FALSE:TRUE;
  }
  else
  {
    result = FALSE;
  }
  
  memcpy(DataBuffer, ReadDataBufferTest,DataLength);
  
  return result;
}


void setUp(void)
{
  ExtPressureDeviceWriteCount = 0;
  IntPressureDeviceWriteCount  = 0;
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  
  SensorWriteForceFail = PS_NONE_E;
  SensorReadForceFail = PS_NONE_E;
  
  memset(ReadDataBufferTest, '\0', sizeof(ReadDataBufferTest));
  memset(WriteDataBufferTest, '\0', sizeof(WriteDataBufferTest));
  
  PM_WritePressureSensors_StubWithCallback(Stub_PM_WritePressureSensors);  
  PM_ReadPressureSensors_StubWithCallback(Stub_PM_ReadPressureSensors);

}

void tearDown(void)
{}


// Check Pressure Sensors can be initialised
void test_InitialisePressureSensorsAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = ((uint8_t)~SENSOR_BOOT); // read buffer must have the SERSOR_BOOT bit cleared
  
  TEST_ASSERT_TRUE(EC_OK_E == PM_InitSensors());
  TEST_ASSERT_EQUAL_INT(1, ExtPressureDeviceWriteCount);
  TEST_ASSERT_EQUAL_INT(1, IntPressureDeviceWriteCount);
  TEST_ASSERT_EQUAL_INT(1, ExtPressureDeviceReadCount);
  TEST_ASSERT_EQUAL_INT(1, IntPressureDeviceReadCount);
}


// Check Pressure Sensors cannot be initialised, External Pressure sensor failing on write
void test_InitialisePressureSensorsWithWriteToExtSensorFailAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  SensorWriteForceFail = PS_EXTERNAL_E;
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = ((uint8_t)~SENSOR_BOOT); // read buffer must have the SERSOR_BOOT bit cleared
  
  result = PM_InitSensors();
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result);
  TEST_ASSERT_EQUAL_INT(1, ExtPressureDeviceWriteCount);
  TEST_ASSERT_EQUAL_INT(0, ExtPressureDeviceReadCount);
  TEST_ASSERT_EQUAL_INT(0, IntPressureDeviceReadCount);
}

// Check Pressure Sensors cannot be initialised, Internal Pressure sensor failing on write
void test_InitialisePressureSensorsWithWriteToIntSensorFailAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  SensorWriteForceFail = PS_INTERNAL_E;
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = ((uint8_t)~SENSOR_BOOT); // read buffer must have the SERSOR_BOOT bit cleared
  
  result = PM_InitSensors();
  
  TEST_ASSERT_TRUE(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result);
  TEST_ASSERT_TRUE(1 == IntPressureDeviceWriteCount);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);
}


// Check Pressure Sensors cannot be initialised, both sensors failing on write
void test_InitialisePressureSensorsWithWriteToIntAndExtSensorsFailAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  SensorWriteForceFail = PS_BOTH_E;
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = ((uint8_t)~SENSOR_BOOT); // read buffer must have the SERSOR_BOOT bit cleared
  
  result = PM_InitSensors();
  

  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);
}


// Check Pressure Sensors cannot be initialised, External Pressure sensor failing on read
void test_InitialisePressureSensorsWithReadFromExtSensorFailAndRetryTimeoutAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = ((uint8_t)~SENSOR_BOOT); // read buffer must have the SERSOR_BOOT bit cleared
  SensorReadForceFail = PS_EXTERNAL_E;
  
  result = PM_InitSensors();
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == IntPressureDeviceReadCount);
}

// Check Pressure Sensors cannot be initialised, Internal Pressure sensor failing on read
void test_InitialisePressureSensorsWithReadFromIntSensorFailAndRetryTimeoutAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = ((uint8_t)~SENSOR_BOOT); // read buffer must have the SERSOR_BOOT bit cleared
  SensorReadForceFail = PS_INTERNAL_E;
  
  result = PM_InitSensors();
  
  TEST_ASSERT_TRUE(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == IntPressureDeviceReadCount);
}

// Check Pressure Sensors cannot be initialised, both sensor failing on read
void test_InitialisePressureSensorsWithReadFromBothSensorsFailAndRetryTimeoutAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = ((uint8_t)~SENSOR_BOOT); // read buffer must have the SERSOR_BOOT bit cleared
  SensorReadForceFail = PS_BOTH_E;
  
  result = PM_InitSensors();
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == IntPressureDeviceReadCount);
}

// Check Pressure Sensors cannot be initialised, sensor has not booted up OK
void test_InitialisePressureSensorsWithReadNoBootStatusFromExternalSensorsAndRetryTimeoutAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  PM_Delay_Ignore();
  ReadDataBufferTest[0] = SENSOR_BOOT;
  
  result = PM_InitSensors();
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(I2C_TIMEOUT_MS == IntPressureDeviceReadCount);
}

// Check Pressure Sensors can be started
void test_StartSensorsAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  result = PM_StartSensors();
  
  TEST_ASSERT_TRUE(EC_OK_E == result);
  TEST_ASSERT_TRUE(1 == IntPressureDeviceWriteCount);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceWriteCount);
  TEST_ASSERT_TRUE((NEXT_VAR_READ | I2C_ADD_CTRL_REG1) == WriteDataBufferTest[0]);
  TEST_ASSERT_TRUE(0x84 == WriteDataBufferTest[1]); //CTRL_REG1
  TEST_ASSERT_TRUE(PRESS_ONE_SHOT == WriteDataBufferTest[2]); //CTRL_REG2
}

// Check Pressure Sensors cannot be started, External Pressure sensor failing on write
void test_StartSensorsWithWriteToExtSensorFailAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  SensorWriteForceFail = PS_EXTERNAL_E;
  
  result = PM_StartSensors();
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E == result);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceWriteCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceWriteCount); // if the write to external press sensor fails, do not run the write to the internal one
}

// Check Pressure Sensors cannot be started, Internal Pressure sensor failing on write
void test_StartSensorsWithWriteToIntSensorFailAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  SensorWriteForceFail = PS_INTERNAL_E;
  
  result = PM_StartSensors();
  
  TEST_ASSERT_TRUE(EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E == result);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceWriteCount);
  TEST_ASSERT_TRUE(1 == IntPressureDeviceWriteCount);
}

// Check Pressure Sensors cannot be started, both sensors failing on write
void test_StartSensorsWithWriteToBotSensorFailAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  SensorWriteForceFail = PS_BOTH_E;
  
  result = PM_StartSensors();
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E == result);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceWriteCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceWriteCount); // if the write to external press sensor fails, do not run the write to the internal one
}

// Get Pressure from Snesors can be taken
// Note. The pressure raw readings from the I2C device have a
//       4 (lsb) bit decimal value that is supposed to be truncated
void test_GetPressureFromSensorsAndCheck(void)
{
  ErrorCode_t result = EC_FAILED_E;
  
  // Pressure from External Pressure sensor, use MAX_PRESSURE_MB, and add 0x0A to be truncated
  ReadDataBufferTest[1] = (uint8_t) (((MAX_PRESSURE_MB << 4) & 0x00F0) | 0x000A);
  ReadDataBufferTest[2] = (uint8_t) ((MAX_PRESSURE_MB >> 4) & 0x00FF);
  ReadDataBufferTest[3] = (uint8_t) 0x55;
  ReadDataBufferTest[4] = (uint8_t) 0xAA;
  uint16_t pressure = 0;
  uint16_t temperature = 0;
  
  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, &pressure, &temperature);
  
  TEST_ASSERT_TRUE(EC_OK_E == result);
  TEST_ASSERT_TRUE(MAX_PRESSURE_MB == pressure);
  TEST_ASSERT_TRUE(0xAA55 == temperature);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);

  // Pressure from Internal Pressure sensor
  result = EC_FAILED_E;
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  ReadDataBufferTest[1] = (uint8_t) (((MIN_PRESSURE_MB << 4) & 0x00F0) | 0x000A);
  ReadDataBufferTest[2] = (uint8_t) ((MIN_PRESSURE_MB >> 4) & 0x00FF);
  ReadDataBufferTest[3] = (uint8_t) 0x00;
  ReadDataBufferTest[4] = (uint8_t) 0x80;
  pressure = 0;
  temperature = 0;
  
  result = PM_GetPressure(PS_INTERNAL_PRESSURE_E, &pressure, &temperature);
  
  TEST_ASSERT_TRUE(EC_OK_E == result);
  TEST_ASSERT_TRUE(MIN_PRESSURE_MB == pressure);
  TEST_ASSERT_TRUE(0x8000 == temperature);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(1 == IntPressureDeviceReadCount);  
}

// Get Pressure from Snesors cannot be taken for because of invalid input parameters
// or sensor failing on read
void test_GetPressureFromSensorsFailsAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  
  // Wrong pressure pointer
  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, NULL, NULL);
  
  TEST_ASSERT_TRUE(EC_INVALID_INPUT_PARAMETER_E == result);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);

  // Wrong temperature pointer
  uint16_t pres = 0; 
  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, &pres, NULL);
  
  TEST_ASSERT_TRUE(EC_INVALID_INPUT_PARAMETER_E == result);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount)

  
  // Wrong sensor ID
  result = EC_OK_E;
  uint16_t pressure = 0;
  uint16_t temperature = 0;
  
  result = PM_GetPressure(PS_MAX_NUM_PRESSURE_SENSORS_E, &pressure, &temperature);
  
  TEST_ASSERT_TRUE(EC_INVALID_INPUT_PARAMETER_E == result);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);

  // Read sensor fail EXT
  result = EC_OK_E;
  pressure = 0;
  SensorReadForceFail = PS_EXTERNAL_E;
  
  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, &pressure, &temperature);
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_READ_FAILED_E == result);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount); 

  // Read sensor fail INT
  // result = EC_OK_E;
  // pressure = 0;
  // SensorReadForceFail = PS_INTERNAL_E;
  
  // result = PM_GetPressure(PS_INTERNAL_PRESSURE_E, &pressure, &temperature);
  
  // TEST_ASSERT_TRUE(EC_INT_PRESSURE_SENSOR_READ_FAILED_E == result);
  // TEST_ASSERT_TRUE(1 == IntPressureDeviceReadCount); 
  // TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);  
  
}


// Test the calculation of the difference between external and internal pressure
void test_CalculatePressureDifferenceAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  uint16_t pressureExt = 0;
  uint16_t pressureInt = 0;
  uint16_t pressureDiff = 0;
  
  // Good External and Internal readings - pass
  result = EC_PRESSURE_DIFF_FAULT_CODE_E;
  pressureExt = 300;
  pressureInt = 200;
  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);
  
  TEST_ASSERT_TRUE(EC_OK_E == result);
  TEST_ASSERT_EQUAL_INT((pressureExt - pressureInt), pressureDiff);

  // External and Internal readings are the same - pass
  result = EC_OK_E;
  pressureExt = 200;
  pressureInt = 200;
  pressureDiff = 0;
  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);
  
  TEST_ASSERT_TRUE(EC_OK_E == result);
  TEST_ASSERT_EQUAL_INT(0, pressureDiff);
  
  // External pressure smaller than internal pressures (e.g. marginal error at start up)
  //  - pass with Vacuum equal to 0
  result = EC_OK_E;
  pressureExt = 200;
  pressureInt = 250; 
  pressureDiff = 10;
  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);
  
  TEST_ASSERT_TRUE(EC_OK_E == result);
  TEST_ASSERT_EQUAL_INT(0, pressureDiff);
  
  // External pressures zero - fail
  result = EC_OK_E;
  pressureExt = 0;
  pressureInt = 200;
  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);
  
  TEST_ASSERT_TRUE(EC_PRESSURE_DIFF_FAULT_CODE_E == result);
  TEST_ASSERT_EQUAL_INT(0, pressureDiff);
  
  // Internal pressures zero - fail
  result = EC_OK_E;
  pressureExt = 150;
  pressureInt = 0;
  pressureDiff = 0;
  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);
  
  TEST_ASSERT_TRUE(EC_PRESSURE_DIFF_FAULT_CODE_E == result);
  TEST_ASSERT_TRUE(0 == pressureDiff);
 
  // Both external and internal pressures zero - fail
  result = EC_OK_E;
  pressureExt = 0;
  pressureInt = 0; 
  pressureDiff = 0;
  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);
  
  TEST_ASSERT_TRUE(EC_PRESSURE_DIFF_FAULT_CODE_E == result);
  TEST_ASSERT_TRUE(0 == pressureDiff);
 
   // Invalid memory address for pressuresDiff - fail
  result = EC_OK_E;
  pressureExt = 500;
  pressureInt = 300; 
  result = PM_CalcDiffPressure(pressureExt, pressureInt, NULL);
  
  TEST_ASSERT_TRUE(EC_INVALID_INPUT_PARAMETER_E == result);
}

// Test is a prerssure sensor ready status can be checked
void test_IfPressureSensorIsReadyAndCheck(void)
{
  bool_t result = TRUE;
  
  // Wrong sensor ID
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  
  result = isPressureSensorReady(PS_MAX_NUM_PRESSURE_SENSORS_E);
  
  TEST_ASSERT_TRUE(FALSE == result);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);
 
  // Ready status cannot be checked, internal sensor failing on read
  result = TRUE;
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  SensorReadForceFail = PS_INTERNAL_E;
  
  result = isPressureSensorReady(PS_INTERNAL_PRESSURE_E);
  
  TEST_ASSERT_TRUE(FALSE == result);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(1 == IntPressureDeviceReadCount);
  
  // Ready status cannot be checked, external sensor failing on read
  result = TRUE;
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  SensorReadForceFail = PS_EXTERNAL_E;
  
  result = isPressureSensorReady(PS_EXTERNAL_PRESSURE_E);
  
  TEST_ASSERT_TRUE(FALSE == result);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);
  
  // Ready status can be checked, external sensor not ready
  result = TRUE;
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  SensorReadForceFail = PS_NONE_E;
  ReadDataBufferTest[7] = 0x00; // PRESS_DATA_READY -> 0x02
  
  result = isPressureSensorReady(PS_EXTERNAL_PRESSURE_E);
  
  TEST_ASSERT_TRUE(FALSE == result);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);
  
  // Ready status can be checked, correct input data for external sensor read
  result = TRUE;
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  SensorReadForceFail = PS_NONE_E;
  ReadDataBufferTest[7] = PRESS_DATA_READY; // PRESS_DATA_READY -> 0x02
  
  result = isPressureSensorReady(PS_EXTERNAL_PRESSURE_E);
  
  TEST_ASSERT_TRUE(TRUE == result);
  TEST_ASSERT_TRUE(1 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(0 == IntPressureDeviceReadCount);

  // Ready status can be checked, correct input data for internal sensor read
  result = TRUE;
  ExtPressureDeviceReadCount = 0;
  IntPressureDeviceReadCount = 0;
  SensorReadForceFail = PS_NONE_E;
  ReadDataBufferTest[7] = PRESS_DATA_READY; // 0x02
  
  result = isPressureSensorReady(PS_INTERNAL_PRESSURE_E);
  
  TEST_ASSERT_TRUE(TRUE == result);
  TEST_ASSERT_TRUE(0 == ExtPressureDeviceReadCount);
  TEST_ASSERT_TRUE(1 == IntPressureDeviceReadCount);
}
