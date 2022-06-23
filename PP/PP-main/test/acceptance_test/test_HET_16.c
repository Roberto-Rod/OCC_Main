/*****************************************************************************
 *   File        : test_HET_16.c
 *
 *   Description : Acceptance test for HET-16
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

void test_AtIdleSpuriousButtonPressDoesNotStartTherapy(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate spurious button press
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();

  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //button returned to unpressed, no state change
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();

  Application_Run(); 
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
}

void test_AtPumpDownOrTherapyDeliverySpuriousButtonPressesDoNotStopTherapy(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  MP_EnableMainCircuitPower_Ignore();

  Application_Init();

  PicoTestFramework_SetPushButton(FALSE);

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();

  PicoTestFramework_Tick();
  Application_Run();
  
  //Transit to IPD
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //At IPD simulate spurious button
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //spurious button press for 1 tick does not shutdown therapy
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //spurious button for 19 ticks
  for (uint8_t i = 0; i < (PUSHBUTTON_LONG_PRESS_TICK_COUNT - 1); i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }

  //spurious button press has recovered
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //spurious button ON/OFF for 2 seconds does not shut down therapy
  for (uint8_t i = 0; i < PUSHBUTTON_LONG_PRESS_TICK_COUNT; i++)
  {
    //simulate alternating ON/OFF push button for 2 seconds
    PicoTestFramework_SetPushButton((uint8_t)(i%2));
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }
}
