/*****************************************************************************
 *   File        : test_Pump.c
 *
 *   Description: Source Code for test of Pump controls.
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
#include "Pump.h"
#include "MockPowerControl.h"
#include "MockTimer.h"
#include "MockBattery.h"
#include "MockPumpFrequencyTracker.h"
#include "MockBattery.h"
#include "MockDeviceStatus.h"

static bool_t ExternalPeripheralsSupplyEnabled = FALSE;
static uint32_t ExternalPeripheralsSupplyEnableCount = 0;
static uint32_t ExternalPeripheralsSupplyDisableCount = 0;
static bool_t MainCircuitPowerEnabled = FALSE;
static bool_t PumpPwmEnabled = FALSE;
static uint8_t BoostDemand = 0; 
static bool_t PoweTrackerCalled = FALSE;
static bool_t VoltageBoundsCalled = FALSE;
static ErrorCode_t VoltageBoundsOK = EC_OK_E;


static void Stub_MP_EnableExternalPeripheralsSupply(int NumCall)
{
  ExternalPeripheralsSupplyEnabled = TRUE;
  ExternalPeripheralsSupplyEnableCount++;
}
static void Stub_MP_DisableExternalPeripheralsSupply(int NumCall)
{
  ExternalPeripheralsSupplyEnabled = FALSE;
  ExternalPeripheralsSupplyDisableCount++;
}
static void Stub_MP_EnableMainCircuitPower(int NumCall)
{
  MainCircuitPowerEnabled = TRUE;
}
static void Stub_MP_DisableMainCircuitPower(int NumCall)
{
  MainCircuitPowerEnabled = FALSE;
}
static bool_t Stub_isMainCircuitPowerEnabled(int NumCall)
{
  return MainCircuitPowerEnabled;
}
static void Stub_MP_EnablePumpPWM(int NumCall)
{
 PumpPwmEnabled = TRUE;
}
static void Stub_MP_DisablePumpPWM(int NumCall)
{
 PumpPwmEnabled = FALSE;
}
static bool_t Stub_isPumpPwmEnabled(int NumCall)
{
  return PumpPwmEnabled;
}
static void Stub_MP_SetReferenceVoltageBoost(uint8_t Demand, int NumCall)
{
  BoostDemand = Demand;
}
static ErrorCode_t Stub_PumpFrequencyTracker_Optimise(int NumCall)
{
  PoweTrackerCalled = TRUE;
  
  return EC_OK_E;
}

static ErrorCode_t Stub_Battery_CheckVoltageBounds(int NumCall)
{
  VoltageBoundsCalled = TRUE;
  
  return VoltageBoundsOK;
}

void setUp(void)
{
  ExternalPeripheralsSupplyEnabled = FALSE;
  ExternalPeripheralsSupplyEnableCount = 0;
  ExternalPeripheralsSupplyDisableCount = 0;
  MainCircuitPowerEnabled = FALSE;
  PumpPwmEnabled = FALSE;
  BoostDemand = 0; 
  PoweTrackerCalled = FALSE;

  MP_EnableExternalPeripheralsSupply_StubWithCallback(Stub_MP_EnableExternalPeripheralsSupply);
  MP_DisableExternalPeripheralsSupply_StubWithCallback(Stub_MP_DisableExternalPeripheralsSupply);
  MP_EnableMainCircuitPower_StubWithCallback(Stub_MP_EnableMainCircuitPower);
  MP_DisableMainCircuitPower_StubWithCallback(Stub_MP_DisableMainCircuitPower);
  isMainCircuitPowerEnabled_StubWithCallback(Stub_isMainCircuitPowerEnabled);
  MP_EnablePumpPWM_StubWithCallback(Stub_MP_EnablePumpPWM);
  MP_DisablePumpPWM_StubWithCallback(Stub_MP_DisablePumpPWM);
  isPumpPwmEnabled_StubWithCallback(Stub_isPumpPwmEnabled);
  MP_SetReferenceVoltageBoost_StubWithCallback(Stub_MP_SetReferenceVoltageBoost);
  PumpFrequencyTracker_Optimise_StubWithCallback(Stub_PumpFrequencyTracker_Optimise);
  Battery_CheckVoltageBounds_StubWithCallback(Stub_Battery_CheckVoltageBounds);
}

void tearDown(void)
{}

// Activate the Pump which means the MainCircuitPower, PumpPWM are enable,
// the Boost Demand has been set, and the Power Tracker updated
// Is this test to tied too much the Pump activation inner implementation?
void test_ActivateAndDeactivatePumpReturnOk(void)
{
  DeviceStatus_SetPumpIsRunning_Ignore();

  // Activate Pump
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF);
  PM_Delay_Ignore();
  ErrorCode_t errorCode = PumpActivate(TRUE);
  TEST_ASSERT_TRUE((EC_OK_E == errorCode)    &&
                   (FALSE == ExternalPeripheralsSupplyEnabled) &&
                   (1 == ExternalPeripheralsSupplyEnableCount) &&
                   (1 == ExternalPeripheralsSupplyDisableCount) &&
                   (TRUE == MainCircuitPowerEnabled) && 
                   (TRUE == PumpPwmEnabled)  && 
                   (VBOOST_REF==BoostDemand) && 
                   (TRUE == PoweTrackerCalled));
  
  // Deactivate Pump
  PoweTrackerCalled = FALSE;
  errorCode = PumpActivate(FALSE);
  TEST_ASSERT_TRUE((EC_OK_E == errorCode)    &&                
                   (FALSE == PumpPwmEnabled) && 
                   (VBOOST_REF_0V == BoostDemand) &&
                   (FALSE == PoweTrackerCalled));
}

// Check the IsPumpActivatedFunction returns the coorect status for the Pump
void test_ActivatePumpAndCheckResultOfIsPumpActivatedFunction(void)
{
  DeviceStatus_SetPumpIsRunning_Ignore();
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF);
  
  PM_Delay_Ignore();
  
  // Activate Pump and check its status
  PumpActivate(TRUE);
  TEST_ASSERT_TRUE(TRUE == isPumpActivated());
  
  // Deactivate Pump and check its status
  PumpActivate(FALSE);
  TEST_ASSERT_FALSE(TRUE == isPumpActivated());  
}

void test_IsPumpRunningFlagSetOnPumpActivate(void)
{
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF);
  PM_Delay_Ignore();

  DeviceStatus_SetPumpIsRunning_Expect(FALSE);
  PumpActivate(FALSE);

  DeviceStatus_SetPumpIsRunning_Expect(TRUE);
  PumpActivate(TRUE);
}