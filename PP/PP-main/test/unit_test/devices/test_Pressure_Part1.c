/*****************************************************************************
 *   File        : test_Pressure_Part1.c
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
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "unity.h"
#include <limits.h>
#include "Pressure_Part1.h"
#include "MockPressure_Part2.h"
#include "MockPressure_Part3.h"
#include "MockPressure_Part4.h"
#include "MockPowerControl.h"
#include "MockTimer.h"
#include "MockDutyCycle.h"
#include "DeviceStatus.h"


static uint32_t GetVacuumFailRetries = 0; // it is used to indicate the stub TryToGetSingleVacuumMeasurement
                                          // the number of fails before returning OK
static uint32_t SingleVacuumRetries = 0;                                          
static uint16_t InternalMeasuredVacuum = 0; 
static uint16_t ExternalMeasuredVacuum = 0; 
static uint16_t MeasuredVacuum = 0; 
static uint8_t  ExpectedPressureType = 0;

// Stub for getting the vacuum, whose return value can be forced based on GetVacuumFailRetries
// It does not uses NumCall because the counter has to be reset multiple times during the same test
static ErrorCode_t Stub_TryToGetSingleVacuumMeasurementEXT(uint16_t* pInternal, uint16_t* pExternal, uint16_t* pDiff, int NumCall)
{
  ErrorCode_t result = EC_EXT_PRESSURE_SENSOR_NOT_READY_E;
  
  SingleVacuumRetries++;
  
  if (SingleVacuumRetries > GetVacuumFailRetries)
  {
    *pDiff = MeasuredVacuum;
    result = EC_OK_E;
  }
  
  return result;
}

static ErrorCode_t Stub_TryToGetSingleVacuumMeasurementINT(uint16_t* pInternal, uint16_t* pExternal, uint16_t* pDiff, int NumCall)
{
  ErrorCode_t result = EC_INT_PRESSURE_SENSOR_NOT_READY_E;
  
  SingleVacuumRetries++;
  
  if (SingleVacuumRetries > GetVacuumFailRetries)
  {
    *pDiff = MeasuredVacuum;
    result = EC_OK_E;
  }
  
  return result;
}


void setUp(void)
{
  GetVacuumFailRetries = 0;
  MeasuredVacuum = 0;
  SingleVacuumRetries = 0;
}

void tearDown(void)
{}


// Check the Initial External pressure can be set and retrieved
void test_SetInitiaExternalPressureAndCheck(void)
{
  uint32_t pressure = 0;
  SetInitialExternalPressure(pressure);
  TEST_ASSERT_EQUAL_INT(GetInitialExternalPressure(), pressure);
  TEST_ASSERT_NOT_EQUAL(GetInitialExternalPressure(), (pressure+1));
    
  pressure = 200;
  SetInitialExternalPressure(pressure);
  GetInitialExternalPressure();
  TEST_ASSERT_EQUAL_INT(GetInitialExternalPressure(), pressure);
  TEST_ASSERT_NOT_EQUAL(GetInitialExternalPressure(), (pressure+1));
}


// Initialise Pressure variable for Pumpdown state
void test_InitialisePressureForPumpdownAndCheck(void)
{
  InitPumpDownVacuum();
  
  TEST_ASSERT_EQUAL_INT(0, GetInitialExternalPressure());
  TEST_ASSERT_EQUAL_INT(0, GetTargetPumpDownVaccumDebounceCount());
}


// Get the actual status of the vacuum (exercicing target level and debounce)
void test_TargetPumpDownVacuumAchievedOrNotAndCheck(void)
{
  bool_t result = FALSE;
  uint16_t vacuum = PUMP_DOWN_TARGET_VACUUM + 1;
  uint32_t fail_count = 0;
  uint32_t pass_count = 0;
  uint32_t loop = 0;
  
  // Vaccum above target for debounce times
  InitPumpDownVacuum();
  for (loop = 0; loop < (PUMP_DOWN_DEBOUNCE_VACUUM_MAX); loop++)
  {
    if(false == isTargetPumpDownVacuumAchieved(vacuum))
    {
      fail_count++;
    }
    else
    {
      pass_count++;
    }
  }
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_DEBOUNCE_VACUUM_MAX, GetTargetPumpDownVaccumDebounceCount());
  TEST_ASSERT_EQUAL_INT(1, pass_count);
  TEST_ASSERT_EQUAL_INT((PUMP_DOWN_DEBOUNCE_VACUUM_MAX-1), fail_count);
  
  // Vaccum above target for less than debounce times followed by a vacuum below targer
  // (loop.e. debounce reset)
  vacuum = PUMP_DOWN_TARGET_VACUUM + 1;
  fail_count = 0;
  pass_count = 0;
  InitPumpDownVacuum();
  for (loop = 0; loop < (PUMP_DOWN_DEBOUNCE_VACUUM_MAX-1); loop++)
  {
    if(false == isTargetPumpDownVacuumAchieved(vacuum))
    {
      fail_count++;
    }
    else
    {
      pass_count++;
    }
  }
  
  TEST_ASSERT_TRUE(FALSE == isTargetPumpDownVacuumAchieved(vacuum-1))
  TEST_ASSERT_EQUAL_INT(0, GetTargetPumpDownVaccumDebounceCount());
  TEST_ASSERT_EQUAL_INT(0, pass_count);
  TEST_ASSERT_EQUAL_INT((PUMP_DOWN_DEBOUNCE_VACUUM_MAX-1), fail_count);
  
  // Vaccum below target for more than debounce times
  vacuum = PUMP_DOWN_TARGET_VACUUM - 1;
  fail_count = 0;
  pass_count = 0;
  InitPumpDownVacuum();
  for (loop = 0; loop < (PUMP_DOWN_DEBOUNCE_VACUUM_MAX+1); loop++)
  {
    if(false == isTargetPumpDownVacuumAchieved(vacuum))
    {
      fail_count++;
    }
    else
    {
      pass_count++;
    }
  }
  TEST_ASSERT_EQUAL_INT(0, GetTargetPumpDownVaccumDebounceCount());
  TEST_ASSERT_EQUAL_INT(0, pass_count);
  TEST_ASSERT_EQUAL_INT((PUMP_DOWN_DEBOUNCE_VACUUM_MAX+1), fail_count);
  
  // Vaccum above target for more than MAX debounce times (255)
  fail_count = 0;
  pass_count = 0;
  InitPumpDownVacuum();
  vacuum = PUMP_DOWN_TARGET_VACUUM + 1;
  for (loop = 0; loop < (UCHAR_MAX + PUMP_DOWN_DEBOUNCE_VACUUM_MAX); loop++)
  {
    if(false == isTargetPumpDownVacuumAchieved(vacuum))
    {
      fail_count++;
    }
    else
    {
      pass_count++;
    }
  }
  TEST_ASSERT_EQUAL_INT(UCHAR_MAX, GetTargetPumpDownVaccumDebounceCount());
  TEST_ASSERT_EQUAL_INT(UCHAR_MAX+1, pass_count);
  TEST_ASSERT_EQUAL_INT((PUMP_DOWN_DEBOUNCE_VACUUM_MAX-1), fail_count);
}



// Check a Vacuum (i.e. Ext. Pressure - Int. Pressure) cannot be retrieved
void test_GetVacuumFailForInvalidInputParameterOrSensorsNotInitialisedAndCheck(void)
{
    uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  uint16_t vacuum = 0;
  ErrorCode_t result = EC_OK_E;
  
  // Fail due to invalid vacuum pointer
  MP_DisableExternalPeripheralsSupply_Ignore();
  TEST_ASSERT_TRUE(EC_INVALID_INPUT_PARAMETER_E == GetVacuum(NULL, 0, 0));
  
  // Fail due to sensors INT fail to initialise
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_Delay_Ignore();
  MP_DisableExternalPeripheralsSupply_Ignore();
  PM_InitSensors_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);
  TEST_ASSERT_TRUE(EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));

   // Fail due to sensors EXT fail to initialise
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_Delay_Ignore();
  MP_DisableExternalPeripheralsSupply_Ignore();
  PM_InitSensors_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));
  
  // Fail due to sensors INT fail to start
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_InitSensors_IgnoreAndReturn(EC_OK_E);
  PM_StartSensors_IgnoreAndReturn(EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E);
  MP_DisableExternalPeripheralsSupply_Ignore();
  
  TEST_ASSERT_TRUE(EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum)); 

   // Fail due to sensors EXT fail to start
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_InitSensors_IgnoreAndReturn(EC_OK_E);
  PM_StartSensors_IgnoreAndReturn(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E);
  MP_DisableExternalPeripheralsSupply_Ignore();
  
  TEST_ASSERT_TRUE(EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));
}


// Check a Vacuum (i.e. Ext. Pressure - Int. Pressure) can be retrieved
void test_GetVacuumPassFirstTryAndCheck(void)
{
  TryToGetSingleVacuumMeasurement_StubWithCallback(Stub_TryToGetSingleVacuumMeasurementEXT); 
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_InitSensors_IgnoreAndReturn(EC_OK_E);
  PM_StartSensors_IgnoreAndReturn(EC_OK_E);
  MP_DisableExternalPeripheralsSupply_Ignore();
  PM_Delay_Ignore();
  
  // Pass at the first pressure sensor reading
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  GetVacuumFailRetries = 0;
  MeasuredVacuum = 100;
  SingleVacuumRetries = 0;

  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Pass at the middle of the GET_VACUUM_MAX_RETRIES pressure sensor readings
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES/2;
  MeasuredVacuum = 50;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Pass at GET_VACUUM_MAX_RETRIES pressure sensor readings
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES-1;
  MeasuredVacuum = 150;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Fail due to taking more than GET_VACUUM_MAX_RETRIES to get successful vacuum
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES;
  MeasuredVacuum = 75;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E != GetVacuum(&internal_pressure, &external_pressure, &vacuum));
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(0, vacuum);
}

// Check a Vacuum 
void test_GetVacuumProvidesInternalPressureWhenAsked(void)
{
  TryToGetSingleVacuumMeasurement_StubWithCallback(Stub_TryToGetSingleVacuumMeasurementINT); 
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_InitSensors_IgnoreAndReturn(EC_OK_E);
  PM_StartSensors_IgnoreAndReturn(EC_OK_E);
  MP_DisableExternalPeripheralsSupply_Ignore();
  PM_Delay_Ignore();
  ExpectedPressureType = 1;
  
  // Pass at the first pressure sensor reading
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  GetVacuumFailRetries = 0;
  MeasuredVacuum = 100;
  SingleVacuumRetries = 0;

  // 0 - diff
  // 1 - Internal 
  // 2 - External 
  
  TEST_ASSERT_TRUE(EC_OK_E ==  GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 1
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Pass at the middle of the GET_VACUUM_MAX_RETRIES pressure sensor readings
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES/2;
  MeasuredVacuum = 50;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 1
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Pass at GET_VACUUM_MAX_RETRIES pressure sensor readings
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES-1;
  MeasuredVacuum = 150;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 1
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Fail due to taking more than GET_VACUUM_MAX_RETRIES to get successful vacuum
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES;
  MeasuredVacuum = 75;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E != GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 1
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(0, vacuum);
}

// Check a Vacuum 
void test_GetVacuumProvidesExternalPressureWhenAsked(void)
{
  TryToGetSingleVacuumMeasurement_StubWithCallback(Stub_TryToGetSingleVacuumMeasurementEXT); 
  MP_EnableExternalPeripheralsSupply_Ignore();
  PM_InitSensors_IgnoreAndReturn(EC_OK_E);
  PM_StartSensors_IgnoreAndReturn(EC_OK_E);
  MP_DisableExternalPeripheralsSupply_Ignore();
  PM_Delay_Ignore();
  ExpectedPressureType = 2;
  
  // Pass at the first pressure sensor reading
  uint16_t vacuum = 0;
  uint16_t internal_pressure = 0;
  uint16_t external_pressure = 0;
  GetVacuumFailRetries = 0;
  MeasuredVacuum = 100;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 2
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Pass at the middle of the GET_VACUUM_MAX_RETRIES pressure sensor readings
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES/2;
  MeasuredVacuum = 50;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 2
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Pass at GET_VACUUM_MAX_RETRIES pressure sensor readings
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES-1;
  MeasuredVacuum = 150;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 2
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries + 1, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(MeasuredVacuum,vacuum);
  
  // Fail due to taking more than GET_VACUUM_MAX_RETRIES to get successful vacuum
  vacuum = 0;
  GetVacuumFailRetries = GET_VACUUM_MAX_RETRIES;
  MeasuredVacuum = 75;
  SingleVacuumRetries = 0;
  
  TEST_ASSERT_TRUE(EC_OK_E !=GetVacuum(&internal_pressure, &external_pressure, &vacuum));   // 2
  TEST_ASSERT_EQUAL_INT(GetVacuumFailRetries, SingleVacuumRetries);
  TEST_ASSERT_EQUAL_INT(0, vacuum);
}

void test_CheckTheLeakDetectionIsActiveWhenTheReferenceBoostVoltageIs27V(void)
{
  // No leak: Reference Boost Voltage OK and leak duty cycle = (LEAK_DUTY_CYCLE - 1)
  MP_GetInitBoostDemand_ExpectAndReturn(VBOOST_REF);
  DCLeakGet_ExpectAndReturn(LEAK_DUTY_CYCLE-1);
  
  TEST_ASSERT_FALSE(isTherapyDeliveryLeakDetected());
  
  // No leak: Reference Boost Voltage OK and leak duty cycle = LEAK_DUTY_CYCLE
  MP_GetInitBoostDemand_ExpectAndReturn(VBOOST_REF);
  DCLeakGet_ExpectAndReturn(LEAK_DUTY_CYCLE);
  
  TEST_ASSERT_FALSE(isTherapyDeliveryLeakDetected());
  
  // Leak: Reference Boost Voltage OK and leak duty cycle > LEAK_DUTY_CYCLE
  MP_GetInitBoostDemand_ExpectAndReturn(VBOOST_REF);
  DCLeakGet_ExpectAndReturn(LEAK_DUTY_CYCLE+1);
  
  TEST_ASSERT_TRUE(isTherapyDeliveryLeakDetected());
  
  // Leak detection disabled (i.e. no call to DCLeakGet): Reference Boost Voltage LOW
  MP_GetInitBoostDemand_ExpectAndReturn(VBOOST_REF-1);
  
  TEST_ASSERT_FALSE(isTherapyDeliveryLeakDetected());
  
  // Leak detection disabled (i.e. no call to DCLeakGet which would return no leak
  // (i.e. LEAK_DUTY_CYCLE - 1) if it was invoked): Reference Boost Voltage LOW
  MP_GetInitBoostDemand_ExpectAndReturn(VBOOST_REF-1);
  DCLeakGet_IgnoreAndReturn(LEAK_DUTY_CYCLE-1);
  
  TEST_ASSERT_FALSE(isTherapyDeliveryLeakDetected());
  
  // Leak detection disabled (i.e. no call to DCLeakGet which would return leak detected
  // (i.e. LEAK_DUTY_CYCLE + 1) if it was invoked): Reference Boost Voltage LOW
  MP_GetInitBoostDemand_ExpectAndReturn(VBOOST_REF-1);
  DCLeakGet_IgnoreAndReturn(LEAK_DUTY_CYCLE+1);
  
  TEST_ASSERT_FALSE(isTherapyDeliveryLeakDetected());
}

