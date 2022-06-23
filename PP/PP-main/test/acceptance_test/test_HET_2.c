/*****************************************************************************
 *   File        : test_HET_2.c
 *
 *   Description : Acceptance test for HET-2
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

//The device detects a Battery Low event only in PUMP DOWN (i.e. when the pump is activated) and will turn the LED's OFF
void test_TurnOffTheLEDsWhenDetectBatteryLowEventInIdleAndPumpDownAndDisableTheDeviceToDeliverFurtherTherapy(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  I2E_Write_IgnoreAndReturn(EC_OK_E);
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
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);

  
  //similate Battery Low in IDLE, hence no pump activity; the device stays in IDLE, no LED status change
  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  PicoTestFramework_Tick();
  Application_Run();
  
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);


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
  
  
  //simulate next tick, no pump activity, no button press, target vacuum is not achieved
  PicoTestFramework_SetPushButton(FALSE);
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_TRUE(PUMP_DOWN_E == DeviceStatus_GetState());

  //simulate next 2 ticks, some pump activity, no button press, target vacuum is not achieved
  //the device goes in NRE
  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  
  PicoTestFramework_Tick();
  Application_Run();
  
  
  PicoTestFramework_Tick();
  Application_Run();
  
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  //simulate more ticks where the device cannot deliver any therapy, no pump activity, LEDs OFF
  
  for (uint32_t i = 0; i < 20; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.pumpActivateTickCount);
    TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  }
}


//The device detects a Battery Low event only in THERAPY DELIVERY (i.e. when the pump is activated) and will turn the LEDSs OFF
void test_TurnOffTheLEDsWhenDetectBatteryLowEventInTherapyDeliveryAndDisableTheDeviceToDeliverFurtherTherapy(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  I2E_Write_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  // In MPD, set Battery Low, pump activity, the device goes in NRE, LEDs go OFF and the device cannot get out of NRE with any button press
  // In LEAK, set Battery Low, no pump activity, the device stays in LEAK, LED status doe go OFF and and LED status is not always OFF
  
  //simulate first timer tick with button press, no LED activity

  TEST_ASSERT_EQUAL_INT(POST_E,DeviceStatus_GetState());
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);

  
  //similate Battery Low in IDLE, hence no pump activity; the device stays in IDLE, no LED status change
  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  PicoTestFramework_Tick();
  Application_Run();
  
  
  TEST_ASSERT_EQUAL_INT(IDLE_E,DeviceStatus_GetState());
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);


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

  // tick into therapy 
  for ( int16_t i = 0; i<=200; i++)
  {
      PicoTestFramework_Tick();
      Application_Run();
  }

  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());
  
  //simulate as many ticks are needed to get the next pressure reading,
  //followed by another tick where the pump is supposed to be activated
  //because the target vacuum is not achieved. As the device detects a 
  //Battery Low event it will go into NRE. And in the next tick the LED
  //will go off
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;  
  for(uint32_t i = 0; 0 == picoTestFrameworkIo.getVacuumTickCount; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  
  PicoTestFramework_Tick();
  Application_Run();
  
  
  PicoTestFramework_Tick();
  Application_Run();
  
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(1, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_TRUE(NRE_E == DeviceStatus_GetState());
}

