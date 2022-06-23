/*****************************************************************************
 *   File        : test_HET_5.c
 *
 *   Description: Acceptance test for HET-5
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
#include "MockLoggingManager.h"

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
#include "MockPerformanceLogger.h"
#include "Assert.h"

#include "MockBattery.h"


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

// During IPD is target pressure is not reached then goto fault
void test_DuringIPDWhenTargetPressureIsNotAchievedTransitToFault(void)
{
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  Application_Init();

  //we start in POST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  
  //first time tick. POST doesnt check button press
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //second timer tick, we're in IDLE, this is the first IDLE tick with the button depressed
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //third timer tick, we're in IDLE, this is the first IDLE tick with the button depressed
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //fourth timer tick, we're in IDLE, this is the second IDLE tick with the button depressed
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate fifth timer tick, with button pressed (being pressed for 200ms), no LED change
  //(the chage state will be detected the next tick around by the Alert Manager)
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
 
  //simulate the next 20 seconds to get to pump down timeout and into FAULT
  //in the last tick
  PicoTestFramework_SetPushButton(FALSE);
  MP_EnableMainCircuitPower_Ignore();
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  for (uint8_t i = 0; i < 200; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    

    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);

    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }
  
  //simulate next 20 ticks where the device stays in FAULT state, with
  //GREEN LED always OFF, AMBER LED being solid (2 s) followed by the repetition of the
  //pattern (0.2s ON, 1.8s OFF) as long it is in FAULT state  
  for (uint32_t i = 0; i < 20; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  }
  
  
  //simulate next 80 ticks where the device stays in FAULT state, with
  //GREEN LED always OFF, and the AMBER LED repeating the pattern (0.2s ON, 1.8s OFF)
  //as long it is in FAULT state
  bool_t orange_status = FALSE;
  uint32_t count = 0;
  for (uint32_t i = 0; i < 80; i++)
  {
    count = i%20;
    orange_status = ((0 == count) || (1 == count)) ? TRUE:FALSE;
    
    PicoTestFramework_Tick();
    Application_Run();   
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_EQUAL_INT(orange_status, picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());
  }

}
