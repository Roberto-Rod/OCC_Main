/*****************************************************************************
 *   File        : test_HET_53.c
 *
 *   Description: Acceptance test for HET-53
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


//The user starts the device from Idle and keeps the button pressed throughout Pump Down and Therapy Delivery,
//and it does not see the device switching off (i.e. long button press ignored when originated in IDLE)
void test_LongButtonPressStartedInIdleDoesNotSwitchTheDeviceOffDuringInitialPumpDownOrTherapyDelivery(void)
{
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  Application_Init();
 
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  
  //simulate first two timer ticks with no button press, no LED activity
  PicoTestFramework_Tick();
  Application_Run();
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled); 
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());


  //simulate three timer ticks (full 200 ms) since idle state and the device detected
  //the first button press, no LED change
  //(the state change will be detected the next tick around by the Alert Manager)
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  PicoTestFramework_SetPushButton(TRUE);
  
  for (uint32_t i = 0; 3 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
  } 

  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);   
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  
  //simulate 10 seconds (i.e. 100 ticks) in PUMPDOWN, no target pressure achieved and button being presses
  //the device ignores the button press because no release has been detected, pump activated with 50% duty cycle
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  
  for (uint32_t i = 0; 100 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
  } 
  
  TEST_ASSERT_EQUAL_INT(50, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //simulate next tick, button still being pressed, and target vacuum achieved and
  //the device stays in the PUMP DOWN mode
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  
  //simulate 5 seconds (i.e. 50 ticks) in PUMP DOWN  where the target pressure is maintained,
  //button still being pressed, and the device ignores the button press because no release has been detected
  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = TRUE;
  
  for(uint32_t i = 0; 50 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
 
  //simulate 3 seconds (i.e. 30 ticks) in PUMP DOWN where the target pressure is maintained,
  //button released
  PicoTestFramework_SetPushButton(FALSE);
  
  for(uint32_t i = 0; 30 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
}



//The device detects a LEAK event in THERAPY DELIVERY, goes into Error and a long button press causes the device to go back to the
//PUMP_DOWN state back to the THERAPY_DELIVERY state and then the POWER_DOWN state and then into the IDLE state, a momentary button
//release and then press again will cause it to go back into PUMP DOWN and THERAPY

//
void test_LongButtonPressStartedInIdleDoesNotSwitchTheDeviceOffDuringInitialPumpDownOrTherapyDeliveryAfterGoingFromLeakToIdle(void)
{ 
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE); 
  Application_Init();
    
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  
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
  //(the change state will be detected the next tick around by the Alert Manager)
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

  // Now in LEAK 
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

  // Been In Leak for 2 seconds .... going to press the button 
  
  //simulate three timer ticks (full 200 ms) where the leak state detects
  //a short button press and goes into PUMP DOWN on the third tick, no LED change
  // (i.e. OFF) as the Alert Manager will detect the state change the next tick around
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  PicoTestFramework_SetPushButton(TRUE);
  
  PicoTestFramework_Tick();
  Application_Run();
  
  
  PicoTestFramework_Tick();
  Application_Run();
  
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  // Now in PUMP_DOWN_E .... the button is still pressed

  //simulate a few ticks (not as many as needed for a button press to be detected
  //20 consecutive times i.e. >2 seconds) with device in PUMP DOWN and target vacuum not achieved,
  uint32_t button_press_ticks = 3;
  for (; 10 > button_press_ticks; button_press_ticks++)
  {   
    PicoTestFramework_Tick();
    Application_Run();
    
    // Green LED on, ORANGE off 
    TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());    
  }
  
  //simulate a couple of ticks with the target vacuum achieved (but still not as many as needed for
  //a long button press to be detected, ie 20 consecutive times i.e. >2 seconds) with device transitioning in THERAPY DELIVERY
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
  for (; 12 > button_press_ticks; button_press_ticks++)
  {
    PicoTestFramework_Tick();
    Application_Run();
  
    // The Green LED will be flashing  
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    
  }  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());    
  
  
  //simulate as many ticks are needed to have a button press detected 20 consecutevely times (i.e. 2 seconds),
  //the device stays in PUMP DOWN and follows the corresponding LED pattern
  for (; PUSHBUTTON_LONG_PRESS_TICK_COUNT > button_press_ticks; button_press_ticks++)
  {   
    PicoTestFramework_Tick();
    Application_Run();
    
    // The Green LED will be flashing  
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());    
  }
 
  
  //simulate one tick to have a button press detected from more than 20 consecutevely times (i.e. 2.1 seconds),
  //the device goes in SHUT DOWN, and following the corresponding LED pattern (the Alert Manager will detect
  //the state change the next tick around
  button_press_ticks++;
  PicoTestFramework_Tick();
  Application_Run();
  
  
  // Now in SHUT_DOWN_E  
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());    

    //simulate 3 seconds with the device in SHUT DOWN, the button released half way through
  for(uint32_t i = 0; 29 > i; i++)
  {
    if (10  <i)
    {
      PicoTestFramework_SetPushButton(FALSE);
    }
    
    PicoTestFramework_Tick();
    Application_Run();

   
    if (i<19)
    {
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    }
    else 
    {
      // next 1 seconds the orange is on and the green off
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);        
    }

    TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());    
  }
  
  
  //simulate one tick with button being released, device goes in IDLE,
  PicoTestFramework_SetPushButton(FALSE);

  PicoTestFramework_Tick();
  Application_Run();
  
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  
  //simulate first two timer ticks with no button press, no LED activity
  PicoTestFramework_Tick();
  Application_Run();
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled); 
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());


  //simulate three timer ticks (full 200 ms) since idle state and the device detected
  //the first button press, no LED change
  //(the state change will be detected the next tick around by the Alert Manager)
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  PicoTestFramework_SetPushButton(TRUE);
  
  for (uint32_t i = 0; 3 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
  } 

  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);   
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  
  //simulate 10 seconds (i.e. 100 ticks) in PUMPDOWN, no target pressure achieved and button being presses
  //the device ignores the button press because no release has been detected, pump activated with 50% duty cycle
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  
  for (uint32_t i = 0; 100 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
  } 
  
  TEST_ASSERT_EQUAL_INT(50, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //simulate next tick, button still being pressed, and target vacuum achieved and
  //the device stays in PUMP DOWN mode 
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  
  //simulate 1 second (i.e. 10 ticks) in PUMP DOWN where the target pressure is maintained,
  //button still being pressed, and the device ignores the button press because no release has been detected
  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = TRUE;
  
  for(uint32_t i = 0; 10 > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();  

    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }
  
}
