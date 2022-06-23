/*****************************************************************************
 *   File        : test_PMTimer.c
 *
 *   Description: Source Code for Unit test for Timer.
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
#include "Timer.h"
#include "Assert.h"
#include "MockHardwareInterface.h"

extern void TMR1_CallBack();

void setUp(void)
{
  HardwareInterface_EnableGlobalInterrupt_Ignore();
  HardwareInterface_DisableGlobalInterrupt_Ignore();
}

void tearDown(void)
{}

void test_TimerCountersInit(void)
{
  CounterStatus_t status;

  TimerCounters_Init();

  status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);
  TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, status);

  status = TimerCounter_Status(POWER_OFF_COUNTER_E);
  TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, status);

  status = TimerCounter_Status(LED_ALERT_COUNTER_1_E);
  TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, status);
}

void test_TimerCountersStartAndCheck(void)
{
  CounterStatus_t status = INERROR_COUNTER_E;;
  ErrorCode_t result = EC_TIMER_COUNT_UNAVAILABLE_E;
  uint32_t const MaxDuration = 1000;

  // Zero the System Tick and the Timer Counters
  TimerCounters_Init();
  // Check all the available timers can be successfully started
  for (uint8_t i = STATE_MACHINE_COUNTER_E; i < MAX_SOFTWARE_COUNTER_E; i++)
  {
    result = TimerCounter_Start((CounterName_t)i, MaxDuration);
    TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
    status = TimerCounter_Status((CounterName_t)i);
    TEST_ASSERT_EQUAL_INT(RUNNING_COUNTER_E, status);
  }
}

void test_TimerCountersRunAndCheckAndDisable(void)
{
  uint32_t const MaxDuration = 1000;

  // Initialise and start a Timer Counter
  TimerCounters_Init();
  ErrorCode_t result = TimerCounter_Start(STATE_MACHINE_COUNTER_E, MaxDuration);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);

  // Check the Timer Counter is Running after number of tick < Max Interval
  for (uint32_t i = 0; i < MaxDuration - 1; i++)
  {
    TMR1_CallBack();
  }
  CounterStatus_t status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);
  TEST_ASSERT_EQUAL_INT(RUNNING_COUNTER_E, status);

  // Check the Timer Counter is Expired after number of tick > Max Interval
  for (uint32_t i = 0; i < 10; i++)
  {
    TMR1_CallBack();
  }
  status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);
  TEST_ASSERT_EQUAL_INT(EXPIRED_COUNTER_E, status);
}

void test_TimerCountersStopCheck(void)
{
  uint32_t const MaxDuration = 1000;

  // Initialise, start and run a Timer Counter
  TimerCounters_Init();
  ErrorCode_t result = TimerCounter_Start(STATE_MACHINE_COUNTER_E, MaxDuration);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
  for (uint32_t i = 0; i < 10; i++)
  {
    TMR1_CallBack();
  }

  // Check the Timer Counter can be Stopped
  result = TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
  CounterStatus_t status = TimerCounter_Status(STATE_MACHINE_COUNTER_E);
  TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, status);
}