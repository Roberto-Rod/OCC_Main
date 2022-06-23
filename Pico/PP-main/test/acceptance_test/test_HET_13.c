/*****************************************************************************
 *   File        : test_HET_13.c
 *
 *   Description : Acceptance test for HET-13
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018 - 2021 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "unity.h"
#include "PicoTestFramework.h"

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
#include "DutyCycle.h"
#include "PushButton.h"
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

void test_GoFromIdleToPumpDownAndClearTheWatchdogAtEveryExecution(void)
{
  //simulate application initialisation
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.countWatchdogClear);
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.countWatchdogClear);
  

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE,
  //watchdog cleared for the first time
  PicoTestFramework_Tick();
  
  Application_Run();
  
  //TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogClear);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate second timer tick, with button pressed, no LED change
  //watchdog cleared for the second time
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(2, picoTestFrameworkIo.countWatchdogClear);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate third timer tick, with no button pressed (i.e. released), no LED change
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  
  Application_Run(); 
  
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(3, picoTestFrameworkIo.countWatchdogClear);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate forth timer tick, with button pressed, no LED change
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(4, picoTestFrameworkIo.countWatchdogClear);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate fifth timer tick, with button pressed, no LED change
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(5, picoTestFrameworkIo.countWatchdogClear);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate sixth timer tick, with button pressed (being pressed for 200ms), no LED change
  //(the chage state will be detected the next tick around by the Alert Manager)
  PicoTestFramework_Tick();
  
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(6, picoTestFrameworkIo.countWatchdogClear);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //simulate seventh timer tick, with button pressed, GREEN LED on
  //the PUMP DOWN state is run for the first time
  MP_EnableMainCircuitPower_Expect();
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
  TEST_ASSERT_EQUAL_INT(7, picoTestFrameworkIo.countWatchdogClear);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //simulate the next five timer ticks, with no button pressed, GREEN LED on
  PicoTestFramework_SetPushButton(FALSE);
  for (uint8_t i = 0; i < 5; i++)
  {
    MP_EnableMainCircuitPower_Expect();
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countWatchdogInit);
    TEST_ASSERT_EQUAL_INT(8+i, picoTestFrameworkIo.countWatchdogClear);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }
}
