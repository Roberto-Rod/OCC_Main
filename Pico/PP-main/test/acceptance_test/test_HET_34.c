/*****************************************************************************
 *   File        : test_HET_34.c
 *
 *   Description: Acceptance test for HET-34
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
#include "DutyCycle.h"
#include "PushButton.h"
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

void test_DetectBatteryDepletedDuringIPDAndTryToStartDeviceAgainWithNoLuck(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  I2E_Write_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //tick timer State: POST => Idle
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(FALSE);
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

  //detect battery depleted and got into NRE state
  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  //turn off all the LEDs the ticj after entering in NRE
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);

  //Push button for short press (< 2s), try to reactivate the device with no luck
  PicoTestFramework_SetPushButton(TRUE);
  for (uint8_t i = 0; i < 5; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);    
  }
  
  //release button and device still stays in NRE
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);    
  
  //Push button for long press (> 2s), try to reactivate the device with no luck
  PicoTestFramework_SetPushButton(TRUE);
  for (uint8_t i = 0; i < 30; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);    
  }
  
  //release button and device still stays in NRE
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);    
}

void test_DetectBatteryDepletedDuringMPDAndTryToStartDeviceAgainWithNoLuck(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  I2E_Write_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //tick timer State: POST => Idle
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(FALSE);
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
  //At pump down, simulate pressure reached
  picoTestFrameworkIo.getVacuumMeasurement = 107;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;

  //At pump down, simulate pressure reached

  uint32_t tickCount =  PUMP_DOWN_COUNT_TICK_DURATION;
  State_t expectedState = PUMP_DOWN_E;

  // Since the pump down last for 20 seconds we need to advance the time until
  // we reach therapy.
  // Only set the correct pressure on the very last moment  
  for (uint32_t i = 0; i < tickCount; i++)
  {
    // Check just at the last moment that the pressure is good and you go to therapy
    // Note: The last time is -2 ticks as the pressure is only measured every other tick
    // and you pump the other.
    if (i == ( PUMP_DOWN_COUNT_TICK_DURATION-(2)))   // +1 ok       
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

  //detect battery depleted and got into NRE state
  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  //turn off all the LEDs the tick after entering in NRE
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);
  
  //Push button for short press (< 2s), try to reactivate the device with no luck
  PicoTestFramework_SetPushButton(TRUE);
  for (uint8_t i = 0; i < 5; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);    
  }
  
    //release button and device still stays in NRE
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);    
  
  //Push button for long press (> 2s), try to reactivate the device with no luck
  PicoTestFramework_SetPushButton(TRUE);
  for (uint8_t i = 0; i < 30; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);    
  }
  
  //release button and device still stays in NRE
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_EQUAL_INT(FALSE, picoTestFrameworkIo.isOrangeLEDEnabled);   
}
