/*****************************************************************************
 *   File        : test_DeviceStatus.c
 *
 *   Description: Source Code for test Device Status.
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
#include "DeviceStatus.h"

void setUp(void)
{
}

void tearDown(void)
{}

void test_DeviceStatusSetAndGet(void)
{
  DeviceStatus_StateAndOnEntrySet(FALSE, IDLE_E);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_GetOnEntry());

  DeviceStatus_StateAndOnEntrySet(TRUE, PUMP_DOWN_E);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(TRUE, DeviceStatus_GetOnEntry());

  DeviceStatus_StateAndOnEntrySet(FALSE, THERAPY_DELIVERY_E);
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_GetOnEntry());

  DeviceStatus_StateAndOnEntrySet(FALSE, FAULT_E);
  TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_GetOnEntry());

  // Get the LED On status, whatever that is, set the opposite and check
  bool_t tmp_led_status = DeviceStatus_GetLedsOnStatus();

  DeviceStatus_SetLedsOnStatus(!tmp_led_status);
  TEST_ASSERT_EQUAL_INT(!tmp_led_status, DeviceStatus_GetLedsOnStatus());

  // Set LED On status to TRUE and check
  DeviceStatus_SetLedsOnStatus(TRUE);
  TEST_ASSERT_EQUAL_INT(TRUE, DeviceStatus_GetLedsOnStatus());

  // Set LED On status to FALSE and check
  DeviceStatus_SetLedsOnStatus(FALSE);
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_GetLedsOnStatus());

  // Set Therapy Delivery Check Status flag to FALSE and check
  DeviceStatus_SetCheckStatusAlert(FALSE);
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_GetCheckStatusAlert());

  // Set Therapy Delivery Check Status flag to TRUE and check
  DeviceStatus_SetCheckStatusAlert(TRUE);
  TEST_ASSERT_EQUAL_INT(TRUE, DeviceStatus_GetCheckStatusAlert());

  // Set Go to Deep Sleep Mode status to FALSE and check
  DeviceStatus_SetDeepSleepModeStatus(FALSE);
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_isGoingInDeepSleep());

  // Set Go to Deep Sleep Mode status to TRUE and check
  DeviceStatus_SetDeepSleepModeStatus(TRUE);
  TEST_ASSERT_EQUAL_INT(TRUE, DeviceStatus_isGoingInDeepSleep());

  // Set Go to Deep Sleep Mode status to FALSE and check
  DeviceStatus_SetButtonPressFromLeak(FALSE);
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_GetButtonPressFromLeak());

  // Set Go to Deep Sleep Mode status to TRUE and check
  DeviceStatus_SetButtonPressFromLeak(TRUE);
  TEST_ASSERT_EQUAL_INT(TRUE, DeviceStatus_GetButtonPressFromLeak());
  
  
  // Note: KEEP FOLLOWING TEST AS LAST AND UPDATE AS NEW VARIABLES
  //       ARE TRACKED BY THE DEVICE STATUS

  // Initialise device status and check
  DeviceStatus_SetLedsOnStatus(TRUE);
  DeviceStatus_StateAndOnEntrySet(TRUE, IDLE_E);

  DeviceStatus_Init();
  TEST_ASSERT_EQUAL_INT(NONE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(TRUE, DeviceStatus_GetOnEntry());
  TEST_ASSERT_EQUAL_INT(FALSE, DeviceStatus_GetLedsOnStatus());
}

void test_IsPumpRunning()
{
  DeviceStatus_SetPumpIsRunning(FALSE);
  TEST_ASSERT_FALSE(DeviceStatus_IsRunningPump());

  DeviceStatus_SetPumpIsRunning(TRUE);
  TEST_ASSERT_TRUE(DeviceStatus_IsRunningPump());

  DeviceStatus_SetPumpIsRunning(FALSE);
  TEST_ASSERT_FALSE(DeviceStatus_IsRunningPump());
}

void test_IsPressureSensorReading()
{
  DeviceStatus_SetPressureSensorIsReading(FALSE);
  TEST_ASSERT_FALSE(DeviceStatus_IsReadingPressureSensor());

  DeviceStatus_SetPressureSensorIsReading(TRUE);
  TEST_ASSERT_TRUE(DeviceStatus_IsReadingPressureSensor());

  DeviceStatus_SetPressureSensorIsReading(FALSE);
  TEST_ASSERT_FALSE(DeviceStatus_IsReadingPressureSensor());
}