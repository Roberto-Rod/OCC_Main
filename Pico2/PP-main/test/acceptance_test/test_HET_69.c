/*****************************************************************************
 *   File        : test_HET_69.c
 *
 *   Description: Acceptance test for HET-69
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
#include "test_helpers/PicoTestFramework.h"

#include "DeviceStatus.h"
#include "pic16lf1509.h"
#include "Application.h"

#include "AlertManager.h"
#include "LoggingManager.h"
#include "StateMachine.h"
#include "StateMachineCommon.h"
#include "StateMachinePumpDown.h"
#include "StateMachineShutdown.h"
#include "StateMachineIdle.h"
#include "StateMachineTherapyDelivery.h"
#include "StateMachineFault.h"
#include "StateMachineNre.h"

#include "StateMachinePOST.h"
#include "StateMachinePOST_internal.h"

#include "Timer.h"
#include "UIInterfaces.h"

#include "PushButton.h"
#include "DutyCycle.h"
#include "PerformanceLogger.h"
#include "Battery.h"
#include "Assert.h"


#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockWatchdog.h"

void setUp(void)
{
  PicoTestFramework_Setup();
}

void tearDown(void)
{}

/**
 * When the device is at IDLE state, every minute, instead of writing to EEPROM, the address is advanced a block,
 * effectively skipping this time block.
 *
 */
void test_PerformanceStatsSkippedInIdleState(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  MP_SleepUntilWokenByRelaxationOscillator_Ignore();

  Application_Init();

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate second timer tick, with button pressed, no LED change
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();

  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetCurrentAddress());

  const uint16_t oneMinuteTick = 60 * 10;
  //tick IDLE for 1 minute, expect PerformanceLogger current address to be advanced, but no call to I2CEEPROM write
  for (uint16_t i = 0; i < oneMinuteTick; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    

    TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  }

  TEST_ASSERT_EQUAL_INT(16, PerformanceLogger_GetCurrentAddress());

  for (uint16_t i = 0; i < oneMinuteTick; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    

    TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  }

  TEST_ASSERT_EQUAL_INT(32, PerformanceLogger_GetCurrentAddress());

}
