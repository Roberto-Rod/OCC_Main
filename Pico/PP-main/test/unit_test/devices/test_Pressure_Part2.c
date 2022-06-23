/*****************************************************************************
 *   File        : test_Pressure_Part2.c
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
 * (c) 2018 - 2021 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "unity.h"
#include <string.h>
#include "Pressure_Part2.h"
#include "MockPressure_Part3.h"
#include "MockPerformanceLogger.h"
#include "MockStateMachine.h"


typedef enum {
    PS_NONE_E = 0,
    PS_EXTERNAL_E,
    PS_INTERNAL_E,
    PS_BOTH_E   //size of the error code
} PressureSensorFail_t; 

// Reasonable range for pressure readings in mBar
#define MAX_PRESSURE_MB ((uint16_t) 0x044C)  // 1100 mBar
#define MIN_PRESSURE_MB ((uint16_t) 0x0226)  //  550 mBar

static uint8_t IsExtSensorReadyCount = 0;
static uint8_t IsIntSensorReadyCount  = 0;
static uint8_t ExtPressureGetCount = 0;
static uint8_t IntPressureGetCount = 0;
static PressureSensorFail_t SensorReadyForceFail = PS_NONE_E;
static PressureSensorFail_t PressureGetForceFail = PS_NONE_E;
static uint16_t ExtPressureTest = 0; // mBar
static uint16_t IntPressureTest = 0; // mBar
static uint16_t VacuumTest = 0; // mBar
static uint16_t ExtTemperatureTest = 0; // Raw temperature value
static uint16_t IntTemperatureTest = 0; // Raw temperature value
static uint16_t IntTemperatureLogged  = 0; // Temperatue value logged 
static uint16_t ExtTemperatureLogged  = 0; // Temperatue value logged 


// Stub for checking if the pressure sensor is ready, whose return value can be forced based on SensorReadyForceFail
static bool_t Stub_isPressureSensorReady(PressureSensor_t Sensor, int NumCall)
{
  bool_t result = TRUE;
  
  if (PS_EXTERNAL_PRESSURE_E == Sensor)
  {
    IsExtSensorReadyCount++;
    result = ((PS_EXTERNAL_E == SensorReadyForceFail) || (PS_BOTH_E == SensorReadyForceFail)) ? FALSE:TRUE;
  }
  else if (PS_INTERNAL_PRESSURE_E == Sensor)
  {
    IsIntSensorReadyCount++;
    result = ((PS_INTERNAL_E == SensorReadyForceFail) || (PS_BOTH_E == SensorReadyForceFail)) ? FALSE:TRUE;
  }
  else
  {
    result = FALSE;
  }
  
  return result;
}

// Stub for checking that the temperature logged is the correct one
static void Stub_PerformanceLogger_SetIntTemperature(uint16_t IntTemperatureValue, int NumCall )
{
   IntTemperatureLogged = IntTemperatureValue;
}

// Stub for checking that the temperature logged is the correct one
static void Stub_PerformanceLogger_SetExtTemperature(uint16_t ExtTemperatureValue, int NumCall )
{
   ExtTemperatureLogged = ExtTemperatureValue;
}

// Stub for getting the pressure from a sensor, whose return value can be forced based on PressureGetForceFail
static ErrorCode_t Stub_PM_GetPressure(PressureSensor_t Sensor, uint16_t* pPressure, uint16_t* pTemperature, int NumCall)
{
  ErrorCode_t result = EC_OK_E;

  if (PS_EXTERNAL_PRESSURE_E == Sensor)
  {
    *pPressure = ExtPressureTest;
    *pTemperature = ExtTemperatureTest;
    ExtPressureGetCount++;
    result = ((PS_EXTERNAL_E == PressureGetForceFail) || (PS_BOTH_E == PressureGetForceFail)) ? EC_EXT_PRESSURE_SENSOR_READ_FAILED_E:EC_OK_E;
  }
  else if (PS_INTERNAL_PRESSURE_E == Sensor)
  {
    *pPressure = IntPressureTest;
    *pTemperature = IntTemperatureTest;
    IntPressureGetCount++;
    result = ((PS_INTERNAL_E == PressureGetForceFail) || (PS_BOTH_E == PressureGetForceFail)) ? EC_INT_PRESSURE_SENSOR_READ_FAILED_E:EC_OK_E;
  }
  else
  {
    result = EC_EXT_PRESSURE_SENSOR_READ_FAILED_E; //Should never happen
  }

  return result;
}

// Stub for calculating a pressure difference
// Note. In principle this implementation should not be needed
//       (what is the point of replicating the calculation of the real function?)
//        but this is a special case
ErrorCode_t Stub_PM_CalcDiffPressure(uint16_t PresExt, uint16_t PresInt, uint16_t* pDiff, int NumCall)
{
  ErrorCode_t result = EC_OK_E;
  
  if (NULL != pDiff)
  {
    *pDiff = VacuumTest;
  }
  else
  {
    result = EC_INVALID_INPUT_PARAMETER_E;
  }
  
  return result;
}

void setUp(void)
{
  IsExtSensorReadyCount = 0;
  IsIntSensorReadyCount  = 0;
  ExtPressureGetCount = 0;
  IntPressureGetCount = 0;
  SensorReadyForceFail = PS_NONE_E;
  PressureGetForceFail = PS_NONE_E;
  ExtPressureTest = 0;
  IntPressureTest = 0;
  ExtTemperatureTest = 0;
  IntTemperatureTest = 0;
  VacuumTest = 0;
  
  isPressureSensorReady_StubWithCallback(Stub_isPressureSensorReady);
  PM_GetPressure_StubWithCallback(Stub_PM_GetPressure);
  PerformanceLogger_SetExternalPressure_Ignore();
  PerformanceLogger_SetDifferentialPressure_Ignore();
  PerformanceLogger_SetInternalTemperature_StubWithCallback(Stub_PerformanceLogger_SetIntTemperature);
  PerformanceLogger_SetExternalTemperature_StubWithCallback(Stub_PerformanceLogger_SetExtTemperature);
}

void tearDown(void)
{}

// Vaccum measurment can be taken
void test_TryToGetSingleDifferentialVacuumMeasurementOkAndCheck(void)
{
  ErrorCode_t result = EC_FAILED_E;
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  ExtPressureTest = 700;
  IntPressureTest = 650;
  ExtTemperatureTest = EXT_TEMPERATURE_THRESHOLD - 0x0010;
  IntTemperatureTest = INT_TEMPERATURE_THRESHOLD - 0x0010;
  VacuumTest = ExtPressureTest - IntPressureTest;
  
  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);


  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0

  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
  TEST_ASSERT_EQUAL_INT(VacuumTest, vacuum);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(1, IntPressureGetCount);

  // Verify the internal temperatue is logged 
  TEST_ASSERT_EQUAL_INT(ExtTemperatureLogged, ExtTemperatureTest);
  TEST_ASSERT_EQUAL_INT(IntTemperatureLogged, IntTemperatureTest);
}

// Vaccum measurment can be taken
void test_TryToGetSingleVacuumInternalMeasurementOkAndCheck(void)
{
  ErrorCode_t result = EC_FAILED_E;
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  ExtPressureTest = 700;
  IntPressureTest = 650;
  ExtTemperatureTest = EXT_TEMPERATURE_THRESHOLD - 0x0010;
  IntTemperatureTest = INT_TEMPERATURE_THRESHOLD - 0x0010;
  VacuumTest = ExtPressureTest - IntPressureTest;
  
  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);

  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 1

  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
  TEST_ASSERT_EQUAL_INT(VacuumTest, vacuum);
  TEST_ASSERT_EQUAL_INT(IntPressureTest, internal_pressure);
  TEST_ASSERT_EQUAL_INT(ExtPressureTest, external_pressure);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(1, IntPressureGetCount);
  // Verify the internal temperatue is logged 
  TEST_ASSERT_EQUAL_INT(ExtTemperatureLogged, ExtTemperatureTest);
  TEST_ASSERT_EQUAL_INT(IntTemperatureLogged, IntTemperatureTest);
}


// Vaccum measurment can be taken
void test_TryToGetSingleVacuumExternalMeasurementOkAndCheck(void)
{
  ErrorCode_t result = EC_FAILED_E;
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  ExtPressureTest = 70;
  IntPressureTest = 69;
  ExtTemperatureTest = EXT_TEMPERATURE_THRESHOLD - 0x0010;
  IntTemperatureTest = INT_TEMPERATURE_THRESHOLD - 0x0010;
  VacuumTest = ExtPressureTest - IntPressureTest;
  
  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);
  
  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 2
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
  TEST_ASSERT_EQUAL_INT(IntPressureTest, internal_pressure);
  TEST_ASSERT_EQUAL_INT(ExtPressureTest, external_pressure);
  TEST_ASSERT_EQUAL_INT(VacuumTest, vacuum);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(1, IntPressureGetCount);
  // Verify the internal temperatue is logged 
  TEST_ASSERT_EQUAL_INT(ExtTemperatureLogged, ExtTemperatureTest);
  TEST_ASSERT_EQUAL_INT(IntTemperatureLogged, IntTemperatureTest);
}

// Vaccum measurment cannot be taken, invalid input parameter
void test_TryToGetSingleVacuumMeasurementInvalidInputParameterAndCheck(void)
{
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  ErrorCode_t result = EC_OK_E;

  // Test any of the parameters being a null pointer 
  result = TryToGetSingleVacuumMeasurement(NULL, &external_pressure, &vacuum);  
  
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
  TEST_ASSERT_EQUAL_INT(0, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(0, IntPressureGetCount);

  
  result = TryToGetSingleVacuumMeasurement(&internal_pressure, NULL, &vacuum);   
  
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
  TEST_ASSERT_EQUAL_INT(0, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(0, IntPressureGetCount);

  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, NULL);  
  
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
  TEST_ASSERT_EQUAL_INT(0, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(0, IntPressureGetCount);

}


// Vaccum measurment cannot be taken, external sensor not ready
void test_TryToGetSingleVacuumMeasurementExternalSensorNotReadyAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  SensorReadyForceFail = PS_EXTERNAL_E;
  uint16_t vacuum = 10;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  
  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_NOT_READY_E, result);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, ExtPressureGetCount);
 // Don't bother checking the internal temperature sensor ready results as they aren't checked if the external one failed
}

// Vaccum measurment cannot be taken, internal sensor not ready
void test_TryToGetSingleVacuumMeasurementInternalSensorNotReadyAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  SensorReadyForceFail = PS_INTERNAL_E;
  uint16_t vacuum = 10;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;

  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_NOT_READY_E, result);
  TEST_ASSERT_EQUAL_INT(1, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, IntPressureGetCount);
    // Don't bother checknig the external temperature sensor ready results as they must have passed for the internal sensor ones to be checked
}


// Vaccum measurment cannot be taken, both sensors not ready
void test_TryToGetSingleVacuumMeasurementBothSensorsNotReadyAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  SensorReadyForceFail = PS_BOTH_E;
  uint16_t vacuum = 10;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  
  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_NOT_READY_E, result);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(0, IntPressureGetCount);
}


// Vaccum measurment cannot be taken, external pressure reading failing
void test_TryToGetSingleVacuumMeasurementFailGettingExtPressureAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  PressureGetForceFail = PS_EXTERNAL_E;
  uint16_t vacuum = 10;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  
  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_EXT_PRESSURE_SENSOR_READ_FAILED_E, result);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);

  TEST_ASSERT_EQUAL_INT(1, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(0, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(0, IntPressureGetCount);
}

// Vaccum measurment cannot be taken, internal pressure reading failing
void test_TryToGetSingleVacuumMeasurementFailGettingIntPressureAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  PressureGetForceFail = PS_INTERNAL_E;
  uint16_t vacuum = 10;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  
  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_INT_PRESSURE_SENSOR_READ_FAILED_E, result);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(1, IntPressureGetCount);
}

// Vaccum measurment cannot be taken, internal pressure reading failing
void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureDiffAndCheck(void)
{
  ErrorCode_t result = EC_OK_E;
  uint16_t vacuum = 10;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  ExtTemperatureTest = EXT_TEMPERATURE_THRESHOLD - 0x0010;
  IntTemperatureTest = INT_TEMPERATURE_THRESHOLD - 0x0010;

  PM_CalcDiffPressure_IgnoreAndReturn(EC_PRESSURE_DIFF_FAULT_CODE_E);
  
  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_PRESSURE_DIFF_FAULT_CODE_E, result);
  TEST_ASSERT_EQUAL_INT(1, IsExtSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, IsIntSensorReadyCount);
  TEST_ASSERT_EQUAL_INT(1, ExtPressureGetCount);
  TEST_ASSERT_EQUAL_INT(1, IntPressureGetCount);
}

// Vaccum measurment cannot be taken, external temperature threshhold reached, devices enters NRE
void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureExternalTemperatureThreshholdReached (void)
{
  ErrorCode_t result = EC_OK_E;
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  ExtPressureTest = 700;
  IntPressureTest = 650;
  ExtTemperatureTest = EXT_TEMPERATURE_THRESHOLD + 0x0010;  // Ext temperature higher than threshold
  IntTemperatureTest = INT_TEMPERATURE_THRESHOLD - 0x0010;
  VacuumTest = ExtPressureTest - IntPressureTest;
  
  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);

  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_EXT_TEMPERATURE_HIGH, result);
 
}

 void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureInternalTemperatureThreshholdReached (void)
{
  ErrorCode_t result = EC_OK_E;
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  ExtPressureTest = 700;
  IntPressureTest = 650;
  ExtTemperatureTest = EXT_TEMPERATURE_THRESHOLD - 0x0010;
  IntTemperatureTest = INT_TEMPERATURE_THRESHOLD + 0x0010;  // Int temperature higher than threshold
  VacuumTest = ExtPressureTest - IntPressureTest;
  
  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);

  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);   // 0
  
  TEST_ASSERT_EQUAL_INT(EC_INT_TEMPERATURE_HIGH, result);
}



