/*****************************************************************************
 *   File        : test_HET_65.c
 *
 *   Description: Acceptance test for HET-65
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


//The device detects a LEAK event in THERAPY DELIVERY, goes into Error and the User successfully switches the 
//device off with a long button press 
void test_SwitchTheDeviceOffWithLongButtonPressStartedInLeakErrorConditionAndDetectedInPumpDown(void)
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

  // Enough ticks to go thru pump down 
  for ( int i = 0; i <= 200; i ++ ) 
  {	  
      PicoTestFramework_Tick();
      Application_Run();
  }

  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());

  //THERAPY_DELIVERY_E state 
  //simulate some ticks in THERAPY DELIVERY where the target pressure is not achieved,
  //the device does not detect a leak yet and stays in the same state
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;  
  for(uint32_t i = 0; 30 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
  
  //THERAPY_DELIVERY_E  
  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());
 
  
  //simulate as many ticks are needed to detect a LEAK.
  //As result the device goes into FAULT. And in the next tick the LED will go off  
  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = TRUE;

  //wait until the state from THERAPY_DELIVERY_E
  for (uint32_t i = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState(); i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
        
  }

  // FAULT_E  
  //Check it must be in fault 
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
  
  //This is a start of a long button press
  //simulate three timer ticks (full 200 ms) where the leak state detects
  //a short button press and goes into PUMP DOWN on the second tick, no LED change
  // (i.e. OFF) as the Alert Manager will detect the state change the next tick around
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  PicoTestFramework_SetPushButton(TRUE);
  
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  
  PicoTestFramework_Tick();
  Application_Run();
 
  // Now in the pump down state, green on, orange off, 
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  // The system transits through the pump down state
  
  //simulate as many ticks are needed to have a button press detected 20 consecutevely times (i.e. 2 seconds),
  //the device stays in PUMP DOWN and following the corresponding LED pattern
  uint32_t button_press_ticks = 3;
  uint32_t green_on_count = 0;
  uint32_t green_off_count = 0;
  for (; PUSHBUTTON_LONG_PRESS_TICK_COUNT > button_press_ticks; button_press_ticks++)
  {   
    PicoTestFramework_Tick();
    Application_Run();
    
    // The green LED will be flashing at this stage 
    if (picoTestFrameworkIo.isGreenLEDEnabled) 
    {
	    green_on_count++;
    }
    else
    {
	    green_off_count++;
    }
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());    
  }

  // Reversed engineer the on off to verify it was flashing 
  TEST_ASSERT_EQUAL_INT(13,green_on_count);
  TEST_ASSERT_EQUAL_INT(4,green_off_count);
  
  //simulate one tick to have a button press detected from more than 20 consecutevely times (i.e. 2.1 seconds),
  //the device goes in SHUT DOWN, and following the corresponding LED pattern (the Alert Manager will detect
  //the state change the next tick around
  button_press_ticks++;
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());    
  
  //simulate 3 seconds with the device in SHUT DOWN, the button released half way through
  for(uint32_t i = 0; 29 > i; i++)
  {
    if (10<i)
    {
      PicoTestFramework_SetPushButton(FALSE);
    }
    
    PicoTestFramework_Tick();
    Application_Run();
    
    // One Green tick already accounted for so 19 left 
    if (i<19)
    {
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    }
    else
    {
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);      
    }

    TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());    

  }
  
  //simulate one tick with button being released, device goes in IDLE, and LEDs go OFF
  PicoTestFramework_SetPushButton(FALSE);

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
}

