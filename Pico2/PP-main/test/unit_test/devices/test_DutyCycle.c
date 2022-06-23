/*****************************************************************************
 *   File        : test_DutyCycle.c
 *
 *   Description: Source Code for test Duty Cycle.
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
#include "DutyCycle.h"
#include "MockPerformanceLogger.h"

void setUp(void)
{
  PerformanceLogger_SetPumpHistory_Ignore();
}

void tearDown(void)
{}

// Check that the duty cycle history can be reset
// updated with a new Pump On event and read.
// Note: we are not testing the actual value returned by the get
//       but only the fact the history changes from being empty 
void test_PumpOnOffHistoryResetSetAndGetDutyCycleStats(void)
{
  // Stats are zeroed
  DCHistoryReset();
  TEST_ASSERT_EQUAL_INT(0,DCVaccumOffsetUpdateGet());
  TEST_ASSERT_EQUAL_INT(0,DCLeakGet());

  // Stats report one Pump up
  DCPumpOnUpdate();
  DCCalculateAll();
  TEST_ASSERT_EQUAL_INT(1,DCVaccumOffsetUpdateGet());
  TEST_ASSERT_EQUAL_INT(1,DCLeakGet());
  
  // Stats report one Pump up becuase it happened in the same time slot as beforeno
  // (i.e. only calling DCPumpOffUpdate, prepares the DC history for the next time slot
  DCPumpOnUpdate();
  DCCalculateAll();
  TEST_ASSERT_EQUAL_INT(1,DCVaccumOffsetUpdateGet());
  TEST_ASSERT_EQUAL_INT(1,DCLeakGet());
  
  // Stats report two Pump up becuase they happened in different time slots
  DCPumpOffUpdate();
  DCPumpOnUpdate();
  DCCalculateAll();
  TEST_ASSERT_EQUAL_INT(2,DCVaccumOffsetUpdateGet());
  TEST_ASSERT_EQUAL_INT(2,DCLeakGet());
  
  // Stats are zeroed
  DCHistoryReset();
  TEST_ASSERT_EQUAL_INT(0,DCVaccumOffsetUpdateGet());
}

// Each time a Pump On event is detected it registers its occurrency
// in the time slot (a second) currently being recorded by the Duty
// Cycle History.
// This test checks that DC history for Vacuum Offset Update registers
// up to VACUUM_OFFSET_DUTY_CYCLE_PERIOD values, and DC history for Leak
// up to LEAK_DUTY_CYCLE_PERIOD values
void test_PumpOnOffNumberOfTimesToHitTheLimitsOfDutyCycleHistoryAndCheck(void)
{
  // Fill in 35 seconds of history (only last 32 will be recorded) each containing a Pump On event
  for (uint8_t i = 1; i < 35; i++)
  {
    DCPumpOffUpdate();
    DCPumpOnUpdate();
    DCCalculateAll();
    if (LEAK_DUTY_CYCLE_PERIOD < i)
    {
      // Both DC histories have reached their maximum length 
      // Neither DC history goes up
      TEST_ASSERT_EQUAL_INT(VACUUM_OFFSET_DUTY_CYCLE_PERIOD, DCVaccumOffsetUpdateGet());
      TEST_ASSERT_EQUAL_INT(LEAK_DUTY_CYCLE_PERIOD, DCLeakGet());
    }
    else if (VACUUM_OFFSET_DUTY_CYCLE_PERIOD < i)
    {
      // DC history for Vacuum Offset Update has reached its maximum length (VACUUM_OFFSET_DUTY_CYCLE_PERIOD)
      // whereas and DC history for Leak has still space (LEAK_DUTY_CYCLE_PERIOD) to record Pump On events 
      // DC history for Vacuum Offset Update does no changes. DC history for Leak goes up
      TEST_ASSERT_EQUAL_INT(VACUUM_OFFSET_DUTY_CYCLE_PERIOD, DCVaccumOffsetUpdateGet());
      TEST_ASSERT_EQUAL_INT(i, DCLeakGet());
    }
    else
    {
      // DC for Vacuum Offset Update and Leak windows < VACUUM_OFFSET_DUTY_CYCLE_PERIOD
      // Both DC's increase
      TEST_ASSERT_EQUAL_INT(i, DCVaccumOffsetUpdateGet());
      TEST_ASSERT_EQUAL_INT(i, DCLeakGet());
    }
  }
}

// Run a number of Pump Off events without Pump On events and check how the DC histories get updated
void test_PumpOffWithNoPumpOnPhasesOutOlderPumpOnEventsFromHistory(void)
{
  // Prepare for the test - Fill in 35 seconds of history (only last 32 will be recorded)
  //                        each containing a Pump On event
  for (uint8_t i = 1; i < 35; i++)
  {
    DCPumpOffUpdate();
    DCPumpOnUpdate();
    DCCalculateAll();
  }
  
  // Run 35 Pump Off eevnts without any Pump On event and check how the DC histories get updated
  for (uint8_t i = 0; i < 35; i++)
  {
    if (LEAK_DUTY_CYCLE_PERIOD < i)
    {
      // Both DC histories have been zeroed bacuse no Pump On event within their recent history 
      // Neither DC history goes down
      TEST_ASSERT_EQUAL_INT(0, DCVaccumOffsetUpdateGet());
      TEST_ASSERT_EQUAL_INT(0, DCLeakGet());
    }
    else if (VACUUM_OFFSET_DUTY_CYCLE_PERIOD < i)
    {
      // DC history for Vacuum Offset Update has been zeroed bacuse no Pump On event within its recent history
      // whereas DC history still contains older Pump On events
      // DC history for Vacuum Offset Update stays zeroed. DC history for Leak goes down
      TEST_ASSERT_EQUAL_INT(0, DCVaccumOffsetUpdateGet());
      TEST_ASSERT_EQUAL_INT((LEAK_DUTY_CYCLE_PERIOD-i), DCLeakGet());
    }
    else
    {
      // Both DC histories for Vacuum Offset Update and Leak still contain older Pump On events
      // Both DC's go down
      TEST_ASSERT_EQUAL_INT((VACUUM_OFFSET_DUTY_CYCLE_PERIOD-i), DCVaccumOffsetUpdateGet());
      TEST_ASSERT_EQUAL_INT((LEAK_DUTY_CYCLE_PERIOD-i), DCLeakGet());
    }
    
    DCPumpOffUpdate();
    DCCalculateAll();
  }
}
