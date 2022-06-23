/*****************************************************************************
 *   File        : test_LoggingManager.c
 *
 *   Description: Source Code for test of the Logging Manager.
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
#include "LoggingManager.h"
#include "DeviceStatus.h"
#include "StateMachineCommon.h"
#include "MockStateMachine.h"
#include "MockPerformanceLogger.h"
#include "MockBattery.h"

#define TICKS_IN_ONE_MINUTE   (10 * 60)

void setUp()
{}

void tearDown()
{}

void test_Initialise(void)
{
  PerformanceLogger_Init_Expect();
  LoggingManager_Init();

  TEST_ASSERT_EQUAL_INT(TICKS_IN_ONE_MINUTE, LoggingManager_GetTicks());
}

void test_LogEveryMinuteWhenNotIdle(void)
{
  DeviceStatus_StateAndOnEntrySet(FALSE, THERAPY_DELIVERY_E);
  DeviceStatus_SetPressureSensorIsReading(FALSE);
  DeviceStatus_SetPumpIsRunning(FALSE);
  PerformanceLogger_GetCurrentAddress_IgnoreAndReturn(0);

  //no logging for 1 minute
  for (int i = 0; i < TICKS_IN_ONE_MINUTE - 1; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OPS_NOT_EXECUTED_E, LoggingManager_Run());
  }

  PerformanceLogger_SetStatus_Expect(DeviceStatus_GetState());
  PerformanceLogger_Persist_ExpectAndReturn(EC_OK_E);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, LoggingManager_Run());

  //no logging for another minute
  for (int i = 0; i < TICKS_IN_ONE_MINUTE - 1; i++)
  {
    LoggingManager_Run();
  }

  PerformanceLogger_SetStatus_Expect(DeviceStatus_GetState());
  PerformanceLogger_Persist_ExpectAndReturn(EC_OK_E);
  LoggingManager_Run();
}

void test_NoLoggingIfPumpIsRunning(void)
{
  PerformanceLogger_Init_Ignore();
  LoggingManager_Init();

  DeviceStatus_SetPressureSensorIsReading(FALSE);
  DeviceStatus_SetPumpIsRunning(TRUE);
  PerformanceLogger_GetCurrentAddress_IgnoreAndReturn(0);

  for (int i = 0; i < TICKS_IN_ONE_MINUTE -1; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OPS_NOT_EXECUTED_E, LoggingManager_Run());
  }
  TEST_ASSERT_EQUAL_INT(EC_LOGGING_POSTPONE_E, LoggingManager_Run());
}

void test_NoLoggingIfPressureSensorReadingIsPerformed(void)
{
  PerformanceLogger_Init_Ignore();
  LoggingManager_Init();

  DeviceStatus_SetPressureSensorIsReading(TRUE);
  DeviceStatus_SetPumpIsRunning(FALSE);
  PerformanceLogger_GetCurrentAddress_IgnoreAndReturn(0);

  for (int i = 0; i < TICKS_IN_ONE_MINUTE -1; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OPS_NOT_EXECUTED_E, LoggingManager_Run());
  }
  TEST_ASSERT_EQUAL_INT(EC_LOGGING_POSTPONE_E, LoggingManager_Run());
}

void test_SkipLoggingWhenStateIsIdle(void)
{
  PerformanceLogger_Init_Ignore();
  LoggingManager_Init();

  DeviceStatus_StateAndOnEntrySet(FALSE, IDLE_E);
  PerformanceLogger_GetCurrentAddress_IgnoreAndReturn(0);

  for (int i = 0; i < TICKS_IN_ONE_MINUTE -1; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OPS_NOT_EXECUTED_E, LoggingManager_Run());
  }

  PerformanceLogger_SkipToNextTimeline_Expect();
  TEST_ASSERT_EQUAL_INT(EC_OK_E, LoggingManager_Run());

}

// 
// Test going to the NRE for the end of life if the EEPROM is full
// There is a higher level test to ensure the entry to the NRE
void test_LogEveryMinuteButEnterNREWhenEEPROMFull(void)
{
  DeviceStatus_StateAndOnEntrySet(FALSE, THERAPY_DELIVERY_E);
  DeviceStatus_SetPressureSensorIsReading(FALSE);
  DeviceStatus_SetPumpIsRunning(FALSE);
  PerformanceLogger_GetCurrentAddress_IgnoreAndReturn( 60ul * 8 * 24 * 16 );

  //no logging for 1 minute
  for (int i = 0; i < TICKS_IN_ONE_MINUTE - 1; i++)
  {
    TEST_ASSERT_EQUAL_INT(EC_OPS_NOT_EXECUTED_E, LoggingManager_Run());
  }

  StateMachine_Enter_NRE_Expect(TRUE);
  TEST_ASSERT_EQUAL_INT(EC_EEPROM_BUFFER_FULL_EOL, LoggingManager_Run());

}
