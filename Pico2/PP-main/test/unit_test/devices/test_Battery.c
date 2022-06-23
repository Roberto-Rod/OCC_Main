/*****************************************************************************
 *   File        : test_Battery.c
 *
 *   Description: Source Code for test Battery Monitoring.
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
#include "Battery.h"
#include "Mockadc.h"
#include "MockPowerControl.h"
#include "MockPerformanceLogger.h"
#include "MockTimer.h"
#include "Debug.h"

static uint16_t batteryVoltageAdc;
static uint16_t fixRefVoltageAdc;
static uint16_t boostReferenceVoltage;
static uint8_t initBoostDemand;
static uint8_t boostDemand;

adc_result_t StubADC_GetConversion(adc_channel_t channel, int numCall)
{
  if (channel == Boost_Voltage)
  {
//    printf("Battery adc: %d\n", batteryVoltageAdc);
    return (adc_result_t)(batteryVoltageAdc);
  }
  else if (channel == channel_FVR)
  {
//    printf("FBR adc: %d\n", fixRefVoltageAdc);
    return (adc_result_t)(fixRefVoltageAdc );
  }

  TEST_FAIL_MESSAGE("Incorrect ADC channel passed");

  return (adc_result_t) 0;
}

void StubMP_SetReferenceVoltageBoost(uint8_t demand, int numCall)
{
  boostReferenceVoltage = demand;
}

void StubMP_SetInitBoostDemand(uint8_t demand, int numCall)
{
  initBoostDemand = demand;
}

void StubMP_SetBoostDemand(uint8_t demand, int numCall)
{
  boostDemand = demand;
}

uint8_t StubMP_GetInitBoostDemand(int numCall)
{
  return initBoostDemand;
}

static uint16_t toFixRefVoltageAdc(float32_t vddVolt)
{
  return (uint16_t) (1.024 / vddVolt * 1024.0);
}

void setUp(void)
{
  ADC_GetConversion_StubWithCallback(StubADC_GetConversion);
  MP_SetReferenceVoltageBoost_StubWithCallback(StubMP_SetReferenceVoltageBoost);
  MP_SetBoostDemand_StubWithCallback(StubMP_SetBoostDemand);
  MP_SetInitBoostDemand_StubWithCallback(StubMP_SetInitBoostDemand);
  MP_GetInitBoostDemand_StubWithCallback(StubMP_GetInitBoostDemand);
  PerformanceLogger_SetBatteryVoltage_Ignore();

  batteryVoltageAdc = 0;
  fixRefVoltageAdc = 0;
  boostReferenceVoltage = 0;
  initBoostDemand = VBOOST_REF;
  boostDemand = VBOOST_REF;
}

void tearDown(void)
{}

void test_BatteryOutOfRangeWhenVddIsOver3V6(void)
{
  fixRefVoltageAdc = toFixRefVoltageAdc(3.61f);
  batteryVoltageAdc = 200;

  for (int i = 0; i < 51; i++)
  {
//    printf("%d\n", i);
    TEST_ASSERT_EQUAL_INT(EC_OK_E, Battery_CheckVoltageBounds());

  }
  TEST_ASSERT_EQUAL_INT(EC_VOLTAGE_OUT_OF_RANGE_E, Battery_CheckVoltageBounds());
}

void test_BoostVoltageIsOutOfRangeWhenBoostVoltageIsAbove33V(void)
{
  fixRefVoltageAdc = toFixRefVoltageAdc(3.0f);
  batteryVoltageAdc = 281;

  for (int i = 0; i < 51; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OK_E, Battery_CheckVoltageBounds());

  }
  TEST_ASSERT_EQUAL_INT(EC_VOLTAGE_OUT_OF_RANGE_E, Battery_CheckVoltageBounds());
}

void test_BoostVoltageIsOutOfRangeWhenBoostVoltageIsBelow16V(void)
{
  fixRefVoltageAdc = toFixRefVoltageAdc(3.0f);
  batteryVoltageAdc = 135;

  for (int i = 0; i < 51; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OK_E, Battery_CheckVoltageBounds());

  }
  TEST_ASSERT_EQUAL_INT(EC_VOLTAGE_OUT_OF_RANGE_E, Battery_CheckVoltageBounds());
}

void test_BatteryEndOfLifeWhenVddIsBelow1V9AndInitBoostDemandBelow18V(void)
{
  fixRefVoltageAdc = toFixRefVoltageAdc(1.89f);
  batteryVoltageAdc = 300;
  initBoostDemand = VBOOST_REF_18V - 1;
  TEST_ASSERT_EQUAL_INT(EC_BATTERY_END_OF_LIFE_E, Battery_CheckVoltageBounds());
}

void test_ReduceInitBootstDemandWhenVddIsBelow2V2(void)
{
  fixRefVoltageAdc = toFixRefVoltageAdc(2.19f);
  batteryVoltageAdc = 200;
  const uint16_t startBoostDemand = VBOOST_REF_22V + 1;
  initBoostDemand = startBoostDemand;

  for (int i = 0; i < 11; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OK_E, Battery_CheckVoltageBounds());
    TEST_ASSERT_EQUAL_INT(startBoostDemand, initBoostDemand);
  }

  TEST_ASSERT_EQUAL_INT(EC_OK_E, Battery_CheckVoltageBounds());
  TEST_ASSERT_EQUAL_INT(startBoostDemand - 1, initBoostDemand);

}

void test_ReduceInitBootstDemandDownTo18VWhenVddIsBelow2V2(void)
{
  fixRefVoltageAdc = toFixRefVoltageAdc(2.00f);
  batteryVoltageAdc = 300;
  uint16_t startBoostDemand = VBOOST_REF_22V;
  initBoostDemand = startBoostDemand;

  while (VBOOST_REF_18V <= initBoostDemand)
  {
    for (int i = 0; i < 11; i++)
    {
      TEST_ASSERT_EQUAL_INT(EC_OK_E, Battery_CheckVoltageBounds());
      TEST_ASSERT_EQUAL_INT(startBoostDemand, initBoostDemand);
    }

    TEST_ASSERT_EQUAL_INT(EC_OK_E, Battery_CheckVoltageBounds());
    TEST_ASSERT_EQUAL_INT(--startBoostDemand, initBoostDemand);
  }
  
  TEST_ASSERT_EQUAL_INT(EC_BATTERY_END_OF_LIFE_E, Battery_CheckVoltageBounds());
  TEST_ASSERT_EQUAL_INT(startBoostDemand, initBoostDemand);
 
}

