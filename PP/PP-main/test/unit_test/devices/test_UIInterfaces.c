/*****************************************************************************
 *   File        : test_UIInterfaces.c
 *
 *   Description: Source Code for Unit test for UI Interface including LEDs and User Button Switch
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
#include "UIInterfaces.h"
#include "MockLED.h"
#include "MockPushButton.h"
#include "MockTimer.h"
#include "MockPowerControl.h"

static bool_t isGreenSet;
static bool_t isOrangeSet;

static void StubLED_SetGreen(bool_t on, int numCall)
{
  isGreenSet = on;
}

static void StubLED_SetOrange(bool_t on, int numCall)
{
  isOrangeSet = on;
}

static uint32_t tickCount = 0;

void setUp(void)
{
  isOrangeSet = false;
  isGreenSet = false;
  tickCount = 0;
  LED_SetGreen_StubWithCallback(StubLED_SetGreen);
  LED_SetOrange_StubWithCallback(StubLED_SetOrange);
}

void tearDown(void)
{}


void test_SetLEDToOrangeEnablesPowerAndDrivesLEDOrange(void)
{ 
  UI_SetLED(LD_ORANGE_E, 10, 0);
  UI_SetLED(LD_GREEN_E, 0, 0);
  
  MP_EnableMainCircuitPower_Expect();
 
  UI_UpdateLEDs();
  TEST_ASSERT_TRUE(isOrangeSet);
  TEST_ASSERT_FALSE(isGreenSet);
}

void test_SetLEDToGreenEnablesPowerAndDrivesLEDGreen(void)
{
  UI_SetLED(LD_ORANGE_E, 0, 0);
  UI_SetLED(LD_GREEN_E, 10, 0);

  MP_EnableMainCircuitPower_Expect();
  
  UI_UpdateLEDs();
  TEST_ASSERT_FALSE(isOrangeSet);
  TEST_ASSERT_TRUE(isGreenSet);

  // Note: the test above could be written as follows
  // (i.e. tell ceedlign what is going to happen as 
  // result of calling the API, and then calling the
  // API to test). However this would rely on the mocked
  // functions to be executed in the same order and as 
  // many times as written in the test:
  //LED_SetOrange_Expect(false);
  //LED_SetGreen_Expect(true);
  //UI_UpdateLEDs();
}

void test_SetLEDDisablesLEDAtOffPeriod(void)
{
  // note that we test that MP_EnablePower is not called
  // rather than the power to be driven to off because
  // there could be other devices that need power
  
  // Set GREEN ON
  UI_SetLED(LD_ORANGE_E, 0, 0);
  UI_SetLED(LD_GREEN_E, 10, 40);
  
  // Drive GREEN ON
  MP_EnableMainCircuitPower_Expect();
  UI_UpdateLEDs();
  TEST_ASSERT_FALSE(isOrangeSet);
  TEST_ASSERT_TRUE(isGreenSet);
  
  // Set GREEN OFF
  UI_SetLED(LD_ORANGE_E, 0, 0);
  UI_SetLED(LD_GREEN_E, 0, 0);
  
  // Drive GREEN OFF
  UI_UpdateLEDs();
  TEST_ASSERT_FALSE(isOrangeSet);
  TEST_ASSERT_FALSE(isGreenSet);
}

void test_PushButtonPressed(void)
{
  PushButton_IsPressed_ExpectAndReturn(false);
  TEST_ASSERT_FALSE(UI_IsPushButtonPressed());

  PushButton_IsPressed_ExpectAndReturn(true);
  TEST_ASSERT_TRUE(UI_IsPushButtonPressed());
}

void test_FlashPattern(void)
{
  MP_EnableMainCircuitPower_Ignore();

  const uint8_t onCount = 3;
  const uint8_t offCount = 5;

  UI_SetLED(LD_GREEN_E, onCount, offCount);

  for (uint32_t sequence = 0; sequence < 5; sequence++)
  {
    for (uint32_t i = 0; i < onCount; i++, tickCount++)
    {
      UI_UpdateLEDs();
//      printf("Green: %d\n", isGreenSet);
      TEST_ASSERT_TRUE(isGreenSet);
    }

    for (uint32_t i = 0; i < offCount; i++, tickCount++)
    {
      UI_UpdateLEDs();
//      printf("Green: %d\n", isGreenSet);
      TEST_ASSERT_FALSE(isGreenSet);
    }
  }
}

void test_FlashPatternForTwoLeds(void)
{
  MP_EnableMainCircuitPower_Ignore();

  const uint8_t greenLedOnCount = 3;
  const uint8_t greenLedOffCount = 5;
  const uint8_t orangeLedOnCount = 7;
  const uint8_t orangeLedOffCount = 11;

  UI_SetLED(LD_GREEN_E, greenLedOnCount, greenLedOffCount);
  UI_SetLED(LD_ORANGE_E, orangeLedOnCount, orangeLedOffCount);

  for (uint32_t ticks = 0; ticks < 50; ticks++)
  {
    UI_UpdateLEDs();

    TEST_ASSERT_EQUAL_INT((ticks % (greenLedOnCount + greenLedOffCount) < greenLedOnCount), isGreenSet);
    TEST_ASSERT_EQUAL_INT((ticks % (orangeLedOnCount + orangeLedOffCount) < orangeLedOnCount), isOrangeSet);

//    printf("Tick: %d\t%d %d\n", ticks, isGreenSet, isOrangeSet);

  }
}


