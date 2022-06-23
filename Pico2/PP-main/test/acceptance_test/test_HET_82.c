/*****************************************************************************
 *   File        : test_HET_82.c
 *
 *   Description: Acceptance test for HET-82
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

#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockPerformanceLogger.h"
#include "MockWatchdog.h"

//Make sure this is defined in the source code with the same value
#define MAX_VACUUM_READ_ERROR_COUNT  ((uint8_t) 20)

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


//The device fails to take a successful vacuum reading for a maximim number of consecutive times in THERAPY DELIVERY
//and alerts the user accordingly. If the user check the status device while the vacuum cannot be read but the device
//is still in THERAPY DELIVERY, the device will signal everything is OK as it has not been long enogh since the last
//valid reading was taken. 
void test_FailToReadVacuumInTherapyDeliveryAndAlertTheUserOfTheErrorConditionAndEnterNRE(void)
{  
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  PerformanceLogger_Persist_IgnoreAndReturn(TRUE);
  PerformanceLogger_SetStatus_ExpectAnyArgs();
  PerformanceLogger_SetNRE_ExpectAndReturn(FALSE);
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

  for ( uint16_t i = 0; i <= 200; i++)
  {
     PicoTestFramework_Tick();
     Application_Run();
  }
  
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());
  
  
  //simulate 6 seconds (i.e. 61 ticks because it takes a tick to run the new state for the first time) in THERAPY DELIVERY
  //where the vacuum cannot be measured for various reasons, no pump activation occurrs, the device stays in the same
  //state as more than 20 seconds of failing reading are needed to raise an alert.
  //Note that changing the value isTargetPumpDownVacuumAchieved has no effect because this condition
  //is not checked when no valid reading is available. The error code associated to getVacuumResult is changed in the middle
  //of the 1 second interval between vacuum readings
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;  

  for(uint32_t i = 0; 61 > i; i++)
  {
    switch (i)
    {
      case 0:
        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E;
        break;
      default:
        break;       
    }
    PicoTestFramework_Tick();
    Application_Run(); 
  }
  TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  //TEST_ASSERT_EQUAL_INT(6, picoTestFrameworkIo.getVacuumTickCount);


  picoTestFrameworkIo.getVacuumResult = EC_OK_E;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  for(uint32_t i = 15; 61 > i; i++)
  {
    switch (i)
    {
      case 15:
        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E;
        break;
      default:
        break;       
    }
    PicoTestFramework_Tick();
    Application_Run(); 
  }

  TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  //TEST_ASSERT_EQUAL_INT(6, picoTestFrameworkIo.getVacuumTickCount);

  picoTestFrameworkIo.getVacuumResult = EC_OK_E;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  for(uint32_t i = 25; 61 > i; i++)
  {
    switch (i)
    {
      case 25:
        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_READ_FAILED_E;
        break;
      default:
        break;       
    }
    PicoTestFramework_Tick();
    Application_Run(); 
  }

  TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  //TEST_ASSERT_EQUAL_INT(6, picoTestFrameworkIo.getVacuumTickCount);

  picoTestFrameworkIo.getVacuumResult = EC_OK_E;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  for(uint32_t i = 35; 61 > i; i++)
  {
    switch (i)
    {
      case 35:
        picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_NOT_READY_E;
        break;
      default:
        break;       
    }
    PicoTestFramework_Tick();
    Application_Run(); 
  }

  TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  //TEST_ASSERT_EQUAL_INT(6, picoTestFrameworkIo.getVacuumTickCount);
  
  picoTestFrameworkIo.getVacuumResult = EC_OK_E;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  for(uint32_t i = 45; 61 > i; i++)
  {
    switch (i)
    {
      case 45:
        picoTestFrameworkIo.getVacuumResult = EC_PRESSURE_DIFF_FAULT_CODE_E;
        break;
      default:
        break;       
    }
    PicoTestFramework_Tick();
    Application_Run(); 
  }

  TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  //TEST_ASSERT_EQUAL_INT(6, picoTestFrameworkIo.getVacuumTickCount);
  
  //simulate next second needed for the following vacuum reading attempt to be successfull this time (error condition no longer present)
  //but still below target in THERAPY DELIVERY. The device stays in the same state 

  // picoTestFrameworkIo.getVacuumResult = EC_OK_E;
  // picoTestFrameworkIo.pumpActivateTickCount = 0;
  // picoTestFrameworkIo.getVacuumTickCount = 0;
  
  // for(uint32_t i = 0; 10 > i; i++)
  // {
  //   PicoTestFramework_Tick();
  //   Application_Run();    
  // }
  
  // TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  // TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  // TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  

  //simulate next tick for the pump to be activated in THERAPY DELIVERY. The device stays in the same state 

  // picoTestFrameworkIo.getVacuumResult = EC_OK_E;
  // picoTestFrameworkIo.pumpActivateTickCount = 0;
  // picoTestFrameworkIo.getVacuumTickCount = 0;

  // PicoTestFramework_Tick();
  // Application_Run();
    
  // TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  // TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  // TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  
  
  //simulate another 20 seconds (i.e. in reality 199 ticks as the first tick of the new second slot was executed earlier
  //when activating the pump) in THERAPY DELIVERY where the vacuum cannot be measured no pump activation occurrs,
  //the device stays in the same state as more than 20 seconds of failing reading is needed to raise an alert.
  //Note that the value FALSE for isTargetPumpDownVacuumAchieved has no effect because this condition
  //is not checked when no valid reading is available.

  // picoTestFrameworkIo.getVacuumResult = EC_EXT_PRESSURE_SENSOR_READ_FAILED_E;
  // picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  // picoTestFrameworkIo.pumpActivateTickCount = 0;
  // picoTestFrameworkIo.getVacuumTickCount = 0;
  
  // for(uint32_t i = 0; 199 > i; i++)
  // {
  //   PicoTestFramework_Tick();
  //   Application_Run();
  // }
  
  // TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  // TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  // TEST_ASSERT_EQUAL_INT(MAX_VACUUM_READ_ERROR_COUNT, picoTestFrameworkIo.getVacuumTickCount);
  
  
  //check that it takes another second (10 ticks) in THERAPY DELIVERY to build up a number of failed vacuum readings
  //bigger than the MAX allowed (i.e. MAX_VACUUM_READ_ERROR_COUNT)
  //As result the device goes into FAULT. And in the next tick the LED will go off
  // uint32_t tickCount = 0;
  // for (tickCount = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState();tickCount++)
  // {
  //   PicoTestFramework_Tick();
  //   Application_Run();        
  // }

  // TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());
  // TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  // TEST_ASSERT_EQUAL_INT(MAX_VACUUM_READ_ERROR_COUNT + 1, picoTestFrameworkIo.getVacuumTickCount);
  // TEST_ASSERT_EQUAL_INT(10, tickCount);

  // TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);
  
  //simulate next 20 ticks where the device stays in FAULT state, with
  //GREEN LED always OFF, AMBER LED being solid (2 s) followed by the repetition of the
  //pattern (0.2s ON, 1.8s OFF) as long it is in FAULT state  
  // Now count of 19 as Ornage LED comes on earlier
  // for (uint32_t i = 0; i < 19; i++)
  // {
  //   PicoTestFramework_Tick();
  //   Application_Run();
    
  //   TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  //   TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);
  //   TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
  // }
  
  
  //simulate next 80 ticks where the device stays in FAULT state, with
  //GREEN LED always OFF, and the AMBER LED repeating the pattern (0.2s ON, 1.8s OFF)
  //as long it is in FAULT state
//   bool_t orange_status = FALSE;
//   uint32_t count = 0;
//   for (uint32_t i = 0; i < 80; i++)
//   {
//     count = i%20;
//     orange_status = ((0 == count) || (1 == count)) ? TRUE:FALSE;
    
//     PicoTestFramework_Tick();
//     Application_Run();

       
//     TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
//     TEST_ASSERT_EQUAL_INT(orange_status, picoTestFrameworkIo.isOrangeLEDEnabled);
//     TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
//   }
}

