/*****************************************************************************
 *   File        : test_HET_7.c
 *
 *   Description: Acceptance test for HET-7
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
#include "Assert.h"
#include "PushButton.h"
#include "DutyCycle.h"


#include "MockLoggingManager.h"
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
  PerformanceLogger_SetPumpDownDuration_Ignore();
}

void tearDown(void)
{}


void test_InIdleStateWhenNoButtonIsPressedGoToLowPowerDisablingPeripherals(void)
{
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  Application_Init();

  //Power on, button not pressed, tick timer: POST => IDLE 
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //Push button eventually pressed for the last 1 tick while in IDLE
  //The peripherals (apart from the push button) are disabled every time
  //the application runs the IDLE state
  uint32_t count = 0;
  const uint32_t expectedPheripheralDisableCount = 19;
  for(; 20 > count; count++)
  {
    if(expectedPheripheralDisableCount == count)
    {
      PicoTestFramework_SetPushButton(TRUE);
    }
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());    
  }
  
  // Second tick with push button pressed
  PicoTestFramework_Tick();
  Application_Run();

  //Third tick with push button pressed - IDLE => PUMP DOWN
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //No push button pressed, target vacuum achieved
  PicoTestFramework_SetPushButton(FALSE);
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
  PicoTestFramework_Tick();
  Application_Run();
  
  
  PicoTestFramework_Tick();
  Application_Run();
 
  // Confirm still in pump down state  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //No push button pressed, target vacuum achieved, stay in THERAPY DELIVERY
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //The application should have gone in a low power mode disabling the pheripherals only when in IDLE
  //Note: in reality there are cases when the MCU is halted in IDLE on the real HW therefore it should not run (deep sleep mode).
  //      However we are testing that the peripherals (apart from Button Switch and Relaxation Oscillator) are ALWAYS disabled
  //      when in IDLE and never in any other state
  TEST_ASSERT_EQUAL_INT(expectedPheripheralDisableCount, picoTestFrameworkIo.countDisablePeripheral);
}


// Note (13 Oct 2017). The following test is no longer applicable as result of removing the use of the
//                     relaxation oscillator. However we leave it commented out in case there is a need
//                     to reintroduce use of the relaxation oscillator
/*
void test_ApplicationStopsInBetweenTicks(void)
{
  Application_Init();

  //Power on, button not pressed, tick timer: POST => IDLE 
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //Push button not pressed
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //Push button pressed - no state change
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //Push button pressed - no state change
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //Push button pressed - IDLE => PUMP DOWN
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //No push button pressed, target vacuum achieved, change state after 2 ticks - PUMP DOWN => THERAPY DELIVEY 
  PicoTestFramework_SetPushButton(FALSE);
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
  PicoTestFramework_Tick();
  Application_Run();
  
  
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());

  //No push button pressed, target vacuum achieved, stay in THERAPY DELIVERY
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  
  //Push button pressed for long time (>2s) - THERAPY DELIVERY => SHUT DOWN
  PicoTestFramework_SetPushButton(TRUE);
  for(uint32_t i = 0; 30 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());
  
  //Push button pressed - stay in SHUT DOWN
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());
  
  //The application should have stopped (i.e. paused or slept) for the same number of timer count
  TEST_ASSERT_EQUAL_INT(picoTestFrameworkIo.countTimerTick,
                        picoTestFrameworkIo.countSleepUntilWokenByRelaxationOscillator);
}
*/
