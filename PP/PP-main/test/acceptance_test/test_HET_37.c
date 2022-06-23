/*****************************************************************************
 *   File        : test_HET_37.c
 *
 *   Description: Acceptance test for HET-37
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
#include "LoggingManager.h"
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
#include "PerformanceLogger.h"
#include "Battery.h"
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

// The device is turned off from PUMP DOWN going into SHUTDOWN first and then IDLE
// The shutdown occurs during the first 5 seconds of the pump down when the green LED is flashing on and off
// A dummy button press of less than 2 seconds is first tried but this is ignored
// A second button press is then perfromed which is greater than 2 seconds and this is activated
//
void test_UserCanTurnOffDeviceDuringPumpDown(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();
  TEST_ASSERT_EQUAL_INT(POST_E,DeviceStatus_GetState());

  //simulate first timer tick with button press, no LED activity
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());

  //simulate three timer ticks (full 200 ms) since idle state and the device detected
  //the first button press, no LED change, no pressure reading, no pump activity
  //(the change state will be detected the next tick around by the Alert Manager)
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  //  Green LED on the first time 
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  
  //simulate third timer tick , no button pressed, GREEN LED on,
  //ORANGE LED off
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  // Green LED on the second time 
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  //simulate next 8 ticks giving a total of 10 ticks, GREEN LED on, ORANGE LED off,
  //pump activity assuming the target vacuum is not achieved
  PicoTestFramework_SetPushButton(FALSE);

  for (uint8_t i = 0; i < 8; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    

    TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }
  
  //simulate the switch being pressed for less that 2 seconds (e.g. 1s) while the
  //GREEN LED flashing with the following pattern for PHASE_2_PUMP_DOWN_ALERT_TICK_DURATION (i.e. 5s = 50 ticks):
  //(100 ms  ON, 100 ms OFF)
  // The LED should work OK with no impact
  for (uint8_t j = 0; j < 10; j++)
  {
    picoTestFrameworkIo.isGreenLEDEnabled = FALSE;
    picoTestFrameworkIo.isOrangeLEDEnabled = FALSE;
    PicoTestFramework_SetPushButton(TRUE);
    PicoTestFramework_Tick();
    Application_Run();  

    if(0==j%2)
    {
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
    }
    else
    {
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    }
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());      
  }

  //simulate that after releasing the switch the GREEN LED is still
  //flashing with the following pattern (e.g. for 1s) as part of PHASE_2_PUMP_DOWN_ALERT_TICK_DURATION:
  //(100 ms  ON, 100 ms OFF)
  for (uint8_t j = 0; j < 10; j++)
  {
    picoTestFrameworkIo.isGreenLEDEnabled = FALSE;
    picoTestFrameworkIo.isOrangeLEDEnabled = FALSE;
    PicoTestFramework_SetPushButton(FALSE);
    PicoTestFramework_Tick();
    Application_Run();
    

    if(0==j%2)
    {
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
    }
    else
    {
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    }
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());      
  }
 
  //simulate that after pressing the button for longer than 2 sec
  //the device goes into SHUTDOWN.
  //Note. State machine in PUMP DOWN for 0..19 loops, SHUTDOWN for 20
  //      but the LED will stay unchanged in this tick because the Alert
  //      Manager kicks in one tick later.
  //      (13 Oct 2017): the LED pattern in SHUTDOWN is not checked
  //      because it is done in HET-24 with an updated pattern from when
  //      this test (HET-37) was created.
  for (uint32_t j = 0; j < (PUSHBUTTON_LONG_PRESS_TICK_COUNT + 1); j++)
  {    
    picoTestFrameworkIo.isGreenLEDEnabled = FALSE;
    picoTestFrameworkIo.isOrangeLEDEnabled = FALSE;
    PicoTestFramework_SetPushButton(TRUE);
    PicoTestFramework_Tick();
    Application_Run();
    
    if(PUSHBUTTON_LONG_PRESS_TICK_COUNT == j)
    {
      // Device off but LED ON as the Alert Manager has a 1 tick delay
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
      // Now in SHUTDOWN state 
      TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());       
    } 
    else
    {
      // usual pattern during Pump Down
      if(0==j%2)
      {
        TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
      }
      else
      {
        TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
      }
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
      TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());      
    } 
  }
  
  //simulate the device stays in SHUTDOWN for 3 seconds before transitioning
  //into IDLE regardless of the status of the button (i.e. pressed or released)
  //Note (13 Oct 2017). Earlier the SHUTDOWN->IDLE transition happened based on
  //                    the button being released. With the introduction of new
  //                    LED pattern for SHUTDOWN this is no longer valid
  // Total sequence is 3 seconds but the green LED was on for 1 tick in the last sequence 
  for (uint32_t j = 0; j < 29; j++)
  {
    if(15 < j)
    {
      PicoTestFramework_SetPushButton(FALSE);
    }

    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());
     
    // Orange is on for 2 seconds. ( already been on for 100ms) 
    if (j<19)
    {
       TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
       TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);        
    }
    else
    {
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
      TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);        
    }
  }
  
  //simulate that after entering in IDLE the LEDs are off
  for (uint32_t j = 0; j < 10; j++)
  {
    PicoTestFramework_SetPushButton(FALSE);
    PicoTestFramework_Tick();
    Application_Run();
    

    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());      
  }
}
