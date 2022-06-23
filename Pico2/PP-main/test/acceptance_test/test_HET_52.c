/*****************************************************************************
 *   File        : test_HET_52.c
 *
 *   Description: Acceptance test for HET-52
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
#include "MockLoggingManager.h"
#include "StateMachine.h"
#include "StateMachineCommon.h"
#include "StateMachinePumpDown.h"
#include "StateMachineShutdown.h"
#include "StateMachineIdle.h"
#include "StateMachineTherapyDelivery.h"
#include "StateMachineFault.h"
#include "StateMachineNre.h"
#include "Battery.h"

#include "StateMachinePOST.h"
#include "StateMachinePOST_internal.h"

#include "Timer.h"
#include "UIInterfaces.h"

#include "PushButton.h"
#include "DutyCycle.h"
#include "Assert.h"


#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockPerformanceLogger.h"
#include "MockWatchdog.h"

void setUp(void)
{
  PicoTestFramework_Setup();
  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);
  PerformanceLogger_SetPumpHistory_Ignore();
}

void tearDown(void)
{}

void test_WhenButtonIsNotPressedIndleTheTherapyIsStartedAfter60Minutes(void)
{
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  Application_Init();

  //simulate timer tick, POST => IDLE
  PicoTestFramework_Tick();

  Application_Run();
  

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //IDLE for 60 minutes
  const uint16_t tickCount60Mins = 10 * 60 * 60;
  for (uint16_t i = 0; i < tickCount60Mins; i++)
  {
    PicoTestFramework_Tick();

    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  }

  //wake up and goes into IPD after 60 mins
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

}
