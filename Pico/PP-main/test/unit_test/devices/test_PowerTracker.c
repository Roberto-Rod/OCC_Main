/*****************************************************************************
 *   File        : test_PowerTracker.c
 *
 *   Description: Source Code for test of Power Tracker.
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
#include "PumpFrequencyTracker.h"
#include "Mockadc.h"

uint8_t NCO1INCL;
uint8_t NCO1INCH;

const uint16_t startFrequency = 2752;
const uint16_t minAcceptableFrequency = 3072; //2752 + 5*64
const uint16_t maxAcceptableFrequency = 2432; //2752 - 5*64

static uint16_t adcResult;

adc_result_t StubADC_GetConversion(adc_channel_t channel, int numCall)
{
  TEST_ASSERT_EQUAL_INT(HBridge_Current, channel);
  return (adc_result_t) adcResult;
}


void setUp(void)
{
  PumpFrequencyTracker_Init();
  ADC_GetConversion_StubWithCallback(StubADC_GetConversion);

  adcResult = 0;
  NCO1INCL = startFrequency & 0xff;
  NCO1INCH = (startFrequency >> 8) & 0xff;
}

void tearDown(void)
{}

static uint16_t toWord(uint8_t hiByte, uint8_t lowByte)
{
  return ((uint16_t)hiByte << 8) | lowByte;
}

void test_WhenCurrentStaysTheSameNoFrequencyAdjustment(void)
{
  adcResult = 0x3f0;

  //adc is higher than previous
  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, toWord(NCO1INCH, NCO1INCL));

  //adc stays the same, no change in ncoFreq
  previousFreq = newFreq;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq, toWord(NCO1INCH, NCO1INCL));

  //adc stays the same, no change in ncoFreq
  previousFreq = newFreq;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq, toWord(NCO1INCH, NCO1INCL));
}

/**
 * When the power tracker has passed the point of optimal current, reduce frequency to increase current
 */
void test_OnDownwardSlopeWhenCurrentIsIncreasedThenDecreaseFrequency(void)
{
  adcResult = 0x3f0;

  //adc is higher than previous
  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, newFreq);

  //adc increasing
  adcResult +=1;
  previousFreq = newFreq;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, newFreq);

  adcResult +=1;
  previousFreq = newFreq;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, newFreq);

  adcResult += 1;
  previousFreq = newFreq;
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, newFreq);

}

void test_WhenCurrentIsIncreasedOnIncreasedFrequencyThenKeepIncreasingFrequency(void)
{
  adcResult = startFrequency;

  //at startup adc is always higher than previous, downward slope is set
  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, newFreq);

  //set positive slope when current is decreased in response to decreased frequency
  adcResult -= (1 << 6);
  previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq + 4, toWord(NCO1INCH, NCO1INCL));

  //in response to increased current when frequency is increased, new frequency is set
  adcResult += (1 << 6);
  previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq + 4, toWord(NCO1INCH, NCO1INCL));

  adcResult += (1 << 6);
  previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq + 4, toWord(NCO1INCH, NCO1INCL));
}

void test_IfCurrentIsDecreasedInResponseToIncreasedFrequencyThenIncreaseFrequency(void)
{
  adcResult = startFrequency;

  //at startup adc is always higher than previous, set downward slope
  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, newFreq);

  //if current is decreased in response to increased frequency => increase frequency
  adcResult -= (1 << 6);
  previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq + 4, toWord(NCO1INCH, NCO1INCL));
}

void test_IfCurrentIsDecreasedInResponseToIncreasedFrequencyThenDecreaseFrequency(void)
{
  adcResult = startFrequency;

  //at startup adc is always higher than previous, set downward slope
  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, newFreq);

  //if current is decreased in response to decreased frequency, increase frequency
  adcResult -= (1 << 6);
  previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq + 4, toWord(NCO1INCH, NCO1INCL));

  //if current is decreased in response to increased frequency, decrease frequency
  adcResult -= (1 << 6);
  previousFreq = toWord(NCO1INCH, NCO1INCL);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, PumpFrequencyTracker_Optimise());
  TEST_ASSERT_EQUAL_INT(previousFreq - 4, toWord(NCO1INCH, NCO1INCL));
}

void test_FrequencyOutOfRangeLowerBoundCheck(void)
{
  adcResult = 0;
  NCO1INCL = (minAcceptableFrequency & 0xff) - 1u;
  NCO1INCH = (minAcceptableFrequency >> 8) & 0xff;
  TEST_ASSERT_EQUAL_INT(EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E, PumpFrequencyTracker_Optimise());
}

void test_FrequencyOutOfRangeUpperBoundCheck(void)
{
  adcResult = 0;
  NCO1INCL = (minAcceptableFrequency & 0xff) + 1;
  NCO1INCH = (minAcceptableFrequency >> 8) & 0xff;
  TEST_ASSERT_EQUAL_INT(EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E, PumpFrequencyTracker_Optimise());
}
