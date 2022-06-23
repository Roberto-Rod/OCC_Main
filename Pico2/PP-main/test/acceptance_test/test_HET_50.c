/*****************************************************************************
 *   File        : test_HET_50.c
 *
 *   Description: Acceptance test for HET-50
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
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF_29V);
  PicoTestFramework_Setup();
  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);
  PerformanceLogger_SetPumpHistory_Ignore();
  PerformanceLogger_SetPumpDownDuration_Ignore();
}

void tearDown(void)
{}


//The device detects a Voltage Out of Range error in THERAPY DELIVERY, goes into NRE cant restart
//old-test_DetectAnOutOfRangeVoltageDuringTherapyDeliveryGoIntoShutDownAndStartTheDeviceAgainWithButtonPress
void test_DetectAnOutOfRangeVoltageDuringTherapyDeliveryGoIntoNRE(void)
{  
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);

  Application_Init();
  
  //simulate first timer tick with button press, no LED activity
  TEST_ASSERT_EQUAL_INT(POST_E,DeviceStatus_GetState());
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());

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
  
  
  //simulate next tick, with no pump activity, no button press, target vacuum is achieved
  PicoTestFramework_SetPushButton(FALSE);
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;

  // Enough tick to take it into THERAPY 
  uint32_t tickCount =  PUMP_DOWN_COUNT_TICK_DURATION;
  State_t expectedState = PUMP_DOWN_E;

  // Since the pump down last for 20 seconds we need to advance the time until
  // we reach therapy.
  for (uint32_t i = 0; i <= tickCount; i++)
  {
      PicoTestFramework_Tick();
      Application_Run();
  }	  

  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());

  
  //simulate some ticks in THERAPY DELIVERY where the target pressure is not achieved,
  //and stays in the same state
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  for(uint32_t i = 0; 30 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
  
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
 
  
  //simulate detection of Voltage Out Of Range error triggering the device to go into FAULT;
  //we need to detect when a vacuum reading is performed and set the Pump to throw the error
  //in the following tick
  picoTestFrameworkIo.getVacuumTickCount = 0;
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
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  
  // //simulate the next FAULT_COUNT_TICK_DURATION (currently 60 minutes) when the device
  // //stays in FAULT
  // picoTestFrameworkIo.pumpActivateResult = EC_OK_E;  
  // for (uint32_t i = 0; i<FAULT_COUNT_TICK_DURATION; i++)
  // {
  //   PicoTestFramework_Tick();
  //   Application_Run();
    
    
  //   TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  // }
  
  
  // //simulate the next tick when the device goes into PUMP DOWN
  // picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  // PicoTestFramework_Tick();
  // Application_Run();
  
  
  // TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  
  // //simulate enough ticks when the device detects the target vacuum being achieved
  // //and goes into THERAPY_DELIVERY_E
  // picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
  
  // // Enough ticks to take it into THERAPY 
  // expectedState = PUMP_DOWN_E;

  // // Since the pump down last for 20 seconds we need to advance the time until
  // // we reach therapy.
  // for (uint32_t i = 0; i <= tickCount; i++)
  // {
  //     PicoTestFramework_Tick();
  //     Application_Run();

  //     if (i >= 200 ) 
  //     { 
  //         expectedState = THERAPY_DELIVERY_E;
  //     }

  //     TEST_ASSERT_EQUAL_INT(expectedState, DeviceStatus_GetState());
  // }	  
   
  // TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
}

