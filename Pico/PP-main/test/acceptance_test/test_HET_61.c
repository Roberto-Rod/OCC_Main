/*****************************************************************************
 *   File        : test_HET_61.c
 *
 *   Description: Acceptance test for HET-61
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
#include "MockBattery.h"

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


//The device detects a LEAK event in THERAPY DELIVERY, goes into Error and the User successfully restarts the therapy
//with a short button press
void test_RestartTheTherapyWithShortButtonPressFromLeakErrorCondition(void)
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

  // forward a number of tick to get into THERAPY i.e. > 20 second 
  for ( uint16_t i = 0; i <= 200; i++ )
  {
     PicoTestFramework_Tick();
     Application_Run();
  }
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());

  
  //simulate some ticks in THERAPY DELIVERY where the target pressure is not achieved,
  //the device does not detect a leak yet and stays in the same state
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;  
  for(uint32_t i = 0; 30 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
  
  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());
 
  
  //simulate as many ticks are needed to detect a LEAK.
  //As result the device goes into FAULT. And in the next tick the LED will go off  
  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = TRUE;

  for (uint32_t i = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState(); i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
        
  }

  TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());

  //simulate next 10 ticks where the device stays in FAULT state, with
  //GREEN LED always OFF, AMBER LED being solid (2 s) followed by the repetition of the
  //pattern (0.2s ON, 1.8s OFF) as long it is in FAULT state  
  for (uint32_t i = 0; i < 20; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());
  }
  

  //simulate three timer ticks (full 200 ms) where the leak state detects
  //a short button press and goes into PUMP DOWN on the second tick, the green LED will 
  //come on and the pump will start 
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  PicoTestFramework_SetPushButton(TRUE);
  for (uint32_t i = 0; i < 1; i++)
  {
      PicoTestFramework_Tick();
      Application_Run();
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
      TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());
   }  
 
  // Second tick with button pushed
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());

  // Should change state after this tick  
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //simulate a tick, the first that the Alert Manager processes in PUMP DOWN
  //starting the corresponding LED pattern (i.e GREEN ON for 1 second and AMBER OFF)
  PicoTestFramework_SetPushButton(FALSE);
  
  PicoTestFramework_Tick();
  Application_Run();
  
  
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //simulate next two ticks during which the target vacuum is achived (we need two because
  //we do not know where in the pump on\pump off cylce the device is during PUMP DOWN) and
  //the device goes into THERAPY DELIVERY, and the LED's follow the corresponding pattern
  //(i.e GREEN still ON and AMBER OFF and still within the 1st second of the start up pattern)
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;

  PicoTestFramework_Tick();
  Application_Run();
  

  PicoTestFramework_Tick();
  Application_Run();

  // forward a number of tick to get into THERAPY i.e. > 20 second 
  for ( uint16_t i = 0; i <= 205; i++ )
  {
     PicoTestFramework_Tick();
     Application_Run();
  }
  
  
  TEST_ASSERT_NOT_EQUAL(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
}

