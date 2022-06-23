/*****************************************************************************
 *   File        : test_HET_24.c
 *
 *   Description: Acceptance test for HET-24
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
#include "Assert.h"
#include "PerformanceLogger.h"
#include "Battery.h"


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

void test_TurnOffDeviceDuringIPDWhenPushButtonIsHeldForTwoSeconds(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //tick timer State: POST => Idle
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //Push button pressed
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //release button for starting therapy
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //button pressed again to signify shutdown intention
  PicoTestFramework_SetPushButton(TRUE);
  for (int i=0; i < PUSHBUTTON_LONG_PRESS_TICK_COUNT; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    // During initial press orange LED is off
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);  

    // The green LED will be flashing at this point      
     
    TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  }

  //2 second time-up, go to Shutdown
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);   

  //device is in Shutdown for 3 seconds... first tick handled in the previous statments 
  PicoTestFramework_SetPushButton(FALSE);
  const uint8_t tickCountThreeSeconds = 29;
  for (int i=0; i< tickCountThreeSeconds; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();

      
    if (i<19)
    {
      // This has the green on and the orange offf 
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
  
  //3 second time-up, go to Idle
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);        
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //no visual alert when in Idle, check for the next minute second
  for (int i=0; i< 600; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled); 
    TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  }

}


void test_DeviceCanBeTurnedOffDuringMPD(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //tick timer State: POST => Idle
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //Push button pressed
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //release button for starting therapy
  PicoTestFramework_SetPushButton(FALSE);

  uint32_t tickCount =  PUMP_DOWN_COUNT_TICK_DURATION;
  State_t expectedState = PUMP_DOWN_E;

  // Since the pump down last for 20 seconds we need to advance the time until
  // we reach therapy.
  // Only set the correct pressure on the very last moment  
  for (uint32_t i = 0; i < tickCount; i++)
  {
    // Check just at the last moment that the pressure is good and you goto therapy
    // Note: The last time is -2 ticks as the pressure is only measured every other tick
    // and you pump the other.
    if (i == ( PUMP_DOWN_COUNT_TICK_DURATION-(2)))   // +1 ok       // PUMP_DOWN_COUNT_TICK_DURATION = 20
    {
      picoTestFrameworkIo.getVacuumMeasurement = 107;
      picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
    }

    if (i >= (PUMP_DOWN_COUNT_TICK_DURATION))          // PUMP_DOWN_COUNT_TICK_DURATION = 20
    {
      expectedState = THERAPY_DELIVERY_E;
    }

    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(expectedState, DeviceStatus_GetState());
  }

  //Pump down state first tick, read pressure
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());

  //Therapy delivery first tick
  InitTherapyDeliveryVacuum_Ignore();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  isTargetTherapyDeliveryVacuumAchieved_IgnoreAndReturn(FALSE);

  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());

  //button pressed again to signify shutdown intention
  PicoTestFramework_SetPushButton(TRUE);

  for (int i=0; i < PUSHBUTTON_LONG_PRESS_TICK_COUNT; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  }

  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
     
  // 2 second time-up for key press, go to shutdown
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(SHUT_DOWN_E, DeviceStatus_GetState());
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);        
  

  // device is in Shutdown for 3 seconds
  PicoTestFramework_SetPushButton(FALSE);
  const uint8_t tickCountThreeSeconds = 29;
  for (int i=0; i< tickCountThreeSeconds; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
      
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

  //3 second time-up, go to Idle
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);        
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //no visual alert when in Idle, check for the next minute second
  for (int i=0; i< 600; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled); 
    TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  }
}
