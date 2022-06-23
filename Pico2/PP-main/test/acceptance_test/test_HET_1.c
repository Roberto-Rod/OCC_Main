/*****************************************************************************
 *   File        : test_HET_1.c
 *
 *   Description : Acceptance test for HET-1
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
#include "StateMachine.h"
#include "LoggingManager.h"
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
#include "PerformanceLogger.h"
#include "Battery.h"

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
#include "MockWatchdog.h"


void setUp(void)
{
  PicoTestFramework_Setup();
}

void tearDown(void)
{}

void test_WhenButtonIsPressedGreenLEDIsEnabled(void)
{
  //I2E_Read_ExpectAndReturn();
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  PicoTestFramework_Tick();

  // nothing happens still inPOST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  Application_Run(); 
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  // Now move to idle 
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  PicoTestFramework_Tick();

  Application_Run();
  

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate second timer tick, with button pressed, no LED change
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();

  Application_Run();
  
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate third timer tick, with no button pressed (i.e. released), no LED change
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();

  Application_Run(); 
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate forth timer tick, with button pressed, no LED change
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate fifth timer tick, with button pressed, no LED change
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate sixth timer tick, with button pressed (being pressed for 200ms), the LED change
  // will change state 
  PicoTestFramework_Tick();
  Application_Run();
  
  // The green led will come on 
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //simulate seventh timer tick, with button pressed, GREEN LED on
  //the PUMP DOWN state is run for the first time
  MP_EnableMainCircuitPower_Expect();
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //simulate the next 8 timer ticks, with no button pressed, GREEN LED on
  //the state will not change and the LED will stay on
  PicoTestFramework_SetPushButton(FALSE);
  for (uint8_t i = 0; i < 8; i++)
  {
    MP_EnableMainCircuitPower_Expect();
    PicoTestFramework_Tick();
    Application_Run();
    

    TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }
}
