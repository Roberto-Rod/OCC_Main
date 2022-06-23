/*****************************************************************************
 *   File        : test_HET_59.c
 *
 *   Description: Acceptance test for HET-59
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
#include "Battery.h"  

#include "MockLoggingManager.h"

#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockPerformanceLogger.h"

#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
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


//The device detects a Voltage Out of Range error in PUMP DOWN, goes into IDLE (deep sleep) and restarts only
//as result of a button press
// old test_DetectAnOutOfRangeVoltageDuringPumpDownGoIntoIdleAndStartTheDeviceOnlyWithShortButtonPress
void test_DetectAnOutOfRangeVoltageDuringPumpDownGoIntoNRE(void)
{ 
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  Application_Init();
  
  //One ticks with no button press, no LED activity, POST => IDLE
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());
  
  //One ticks with no button press, no LED activity, stay in IDLE
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());


  //simulate three timer ticks (full 200 ms) since idle state and the device detected
  //the first button press, no LED change
  //(the chage state will be detected the next tick around by the Alert Manager)
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  
  PicoTestFramework_Tick();
  Application_Run();
  
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
 
 
  //simulate detection of Voltage Out Of Range error triggering the device to go into IDLE (deep sleep mode);
  //we need to detect when a vacuum reading is performed and set the Pump to throw the error in the following tick
  //No activation of Deep Sleep mode yet
  PicoTestFramework_SetPushButton(FALSE);
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.countDeepSleep = 0;
  picoTestFrameworkIo.countDisablePeripheral = 0;
  for (uint32_t i = 0; 0 == picoTestFrameworkIo.getVacuumTickCount; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();   
  }
  picoTestFrameworkIo.pumpActivateResult = EC_VOLTAGE_OUT_OF_RANGE_E;
  picoTestFrameworkIo.pumpActivateTickCount = 0;

  PicoTestFramework_Tick();
  Application_Run();
   
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.countDeepSleep);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.countDisablePeripheral);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  
 
  // //simulate one tick in IDLE with no button press that will result in activating the Deep Sleep mode
  // PicoTestFramework_Tick();
  // Application_Run(); 
  
  // TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countDeepSleep);
  // TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.countDisablePeripheral);
  // TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  
  // //simulate a few more ticks in IDLE and check that device keeps activating the Deep Sleep mode
  // //Note: in deep sleep mode the MCU is halted and the relaxation ocillator disabled therefore the
  // //      application cannot run and the timer measuring the periodic restart from FAULT
  // //      (i.e. the FAULT_COUNT_TICK_DURATION) would not get updated. As result the following test
  // //      is only a fictitious situation
  // const uint32_t tickInIdle = 20;
  // for (uint32_t i = 0; tickInIdle > i; i++)
  // {
  //   PicoTestFramework_Tick();
  //   Application_Run();
  // }
  // TEST_ASSERT_EQUAL_INT(tickInIdle + 1, picoTestFrameworkIo.countDeepSleep);
  // //TEST_ASSERT_EQUAL_INT(tickInIdle + 1, picoTestFrameworkIo.countDisablePeripheral);
  // TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
}



