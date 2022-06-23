/*****************************************************************************
 *   File        : test_HET_6.c
 *
 *   Description: Acceptance test for HET-6
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
#include "Assert.h"
#include "MockWatchdog.h"
#include "Battery.h"

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


#define PHASE_1_PUMP_DOWN_ALERT_TICK_DURATION              (10) //should be 10 ticks = 1 second
#define PHASE_2_PUMP_DOWN_ALERT_TICK_DURATION              (50) // 
#define PHASE_3_PUMP_DOWN_ALERT_TICK_DURATION             (150) // 
#define PHASE_4_PUMP_DOWN_ALERT_TICK_DURATION              (20) //
#define PHASE_5_PUMP_DOWN_ALERT_TICK_DURATION              (20) //

static bool_t  therapyVacuumAchieved;
bool_t Stub_isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum, int NumCall)
{
  return therapyVacuumAchieved;
}

void setUp(void)
{
  PicoTestFramework_Setup();
  isTargetTherapyDeliveryVacuumAchieved_StubWithCallback(Stub_isTargetTherapyDeliveryVacuumAchieved);
  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);
  PerformanceLogger_SetPumpHistory_Ignore();
  PerformanceLogger_SetPumpDownDuration_Ignore();
}

void tearDown(void)
{}



void test_TherapyIsMaintained(void)
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

  //second timer tick
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
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
      
  //simulate the next 21 seconds during which the PUMP DOWN achieves target vacuum,
  //the device goes into THERAPY DELIVERY but does not alert the user yet with the
  //GREEN LED ON for 2 seconds
  uint32_t tickCount = 
      PHASE_1_PUMP_DOWN_ALERT_TICK_DURATION +
      PHASE_2_PUMP_DOWN_ALERT_TICK_DURATION + 
      PHASE_3_PUMP_DOWN_ALERT_TICK_DURATION -1;  // -1 as one tick already used
  PicoTestFramework_SetPushButton(FALSE);
  MP_EnableMainCircuitPower_Ignore();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  TherapyDeliveryTargetVacuumUpdate_Ignore();
  therapyVacuumAchieved = TRUE;
  State_t expectedState = PUMP_DOWN_E;
  // Go forward for a number of ticks which simulate the PHASE 1-3 of the pump down.
  // Half way through simulate the pressure being achieved and the state being changed to 
  // THERAPY_DELIVERY_E
  for (uint32_t i = 0; i < tickCount; i++)
  {
    // If in the 5 second window for 1 tick then ensure that you
    // will still goto therapy at the end.
    if (i == ( PUMP_DOWN_COUNT_TICK_DURATION-(50+0)))   // +1 ok      
    {
      picoTestFrameworkIo.getVacuumMeasurement = 107;
      picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
    }

    if (i == ( PUMP_DOWN_COUNT_TICK_DURATION-(49+0)))   // +1 ok     
    {
      picoTestFrameworkIo.getVacuumMeasurement = 80;
      picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
    }

    if (i >= (PUMP_DOWN_COUNT_TICK_DURATION))         
    {
      // Now enough ticks to be in therapy so check you are
      // in therapy 
      expectedState = THERAPY_DELIVERY_E;
    }

    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(expectedState, DeviceStatus_GetState());
  }

  
  //check that the Green LED is ON for PHASE_4_PUMP_DOWN_ALERT_TICK_DURATION seconds and
  //the orange LED is off for two seconds 
  tickCount = PHASE_4_PUMP_DOWN_ALERT_TICK_DURATION;
  int  numOrangeOns = 0;
  int  numGreenOns  = 0;
  for (uint16_t i = 0; i < tickCount; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
    numOrangeOns += picoTestFrameworkIo.isOrangeLEDEnabled;
    numGreenOns += picoTestFrameworkIo.isGreenLEDEnabled;
  }
  TEST_ASSERT_EQUAL_INT(0, numOrangeOns); //check average duty cycle
  TEST_ASSERT_EQUAL_INT(tickCount, numGreenOns); //check average duty cycle
  
  //check that the Green and Orange LEDs are OFF in normal operation
  numOrangeOns = 0;
  numGreenOns  = 0;
  for (uint16_t i = 0; i < 30; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
    numOrangeOns += picoTestFrameworkIo.isOrangeLEDEnabled;
    numGreenOns += picoTestFrameworkIo.isGreenLEDEnabled;
  }
  TEST_ASSERT_EQUAL_INT(0, numOrangeOns); //check average duty cycle
  TEST_ASSERT_EQUAL_INT(0, numGreenOns); //check average duty cycle
  
  //check that the pump is ativated if the vacuum falls below the target value
  //for the next 3 seconds
  therapyVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint16_t i = 0; i < 30; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  }
  TEST_ASSERT_EQUAL_INT(picoTestFrameworkIo.pumpActivateTickCount, 3);
  
  //check that the pump is no longer ativated if the vacuum has achieved again its target value
  therapyVacuumAchieved = TRUE;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint16_t i = 0; i < 30; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  }
  TEST_ASSERT_EQUAL_INT(picoTestFrameworkIo.pumpActivateTickCount, 0);
 
}
