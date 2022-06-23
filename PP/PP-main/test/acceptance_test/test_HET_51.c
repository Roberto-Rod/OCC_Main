/*****************************************************************************
 *   File        : test_HET_51.c
 *
 *   Description: Acceptance test for HET-51
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

#include "StateMachinePOST.h"
#include "StateMachinePOST_internal.h"

#include "Timer.h"
#include "UIInterfaces.h"

#include "PushButton.h"
#include "DutyCycle.h"
#include "Assert.h"
#include "MockBattery.h"

#include "MockPerformanceLogger.h"
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
  Battery_CheckVoltageBounds_IgnoreAndReturn(EC_OK_E);
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF_29V);
  PicoTestFramework_Setup();
  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);
  PerformanceLogger_SetPumpHistory_Ignore();
  PerformanceLogger_SetPumpDownDuration_Ignore();
}

void tearDown(void)
{}

void test_After60MinInFaultStateRestartIPD(void)
{
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  Application_Init();

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();

  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();

  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  MP_EnableMainCircuitPower_Ignore();
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //run pump down for 20 seconds to get into Leak - fault state
  PicoTestFramework_SetPushButton(FALSE);
  for (uint8_t i = 0; i < 20 * 10; i++)
  {
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
    PicoTestFramework_Tick();
    Application_Run();
    
  }

  TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  PicoTestFramework_Tick();
  Application_Run();
  

  //after 60 min in Fault state, restart IPD
  PicoTestFramework_SetPushButton(FALSE);
  const uint16_t sixtyMinuteTicks = 60 * 60 * 10;

  bool_t orangeOn = FALSE;
  int    OnOffCount = 0; 

  for (uint16_t i = 0; i < sixtyMinuteTicks; i++)
  {
    TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);

    // Verify that the Orange LED flashes during the hour 
    // It stays on for the first 2seconds and then is on for 2 ticks and off for 8 ticks repeatedly
    if (i < 19) 
    {
            orangeOn = TRUE;
    }
    else
    {
       orangeOn = FALSE;
       if (OnOffCount < 2)
       {
               orangeOn = TRUE;
       }
       if (++OnOffCount >= 20)
       {
               OnOffCount = 0;
       }

    }

    if (orangeOn)
    {
        TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);
    }
    else
    {
        TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    }

    PicoTestFramework_Tick();
    Application_Run();
  }

  //Device should be back to PUMP DOWN again
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);

}
