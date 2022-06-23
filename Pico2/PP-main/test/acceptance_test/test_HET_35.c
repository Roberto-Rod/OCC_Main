/*****************************************************************************
 *   File        : test_HET_35.c
 *
 *   Description: Acceptance test for HET-35
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
#include "MockLoggingManager.h"
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
#include "Battery.h"

void setUp(void)
{
  PicoTestFramework_Setup();
  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);
}

void tearDown(void)
{}

//The device goes into NRE during IPD and cannot come out of it as a result of either a button press or running the device for a long time (>60mins)
void test_TheDeviceDetectsEndOfLifeErrorDuringPumpdownAndCannotBeRestartedToDeliverFurtherTherapy(void)
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
  
 
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  
  //simulate a short (i.e. >2 ticks) button press where the device stays in NRE,
  //cannot deliver any therapy, no pump activity, no pressure sensor activity
  picoTestFrameworkIo.isPushButtonPress = TRUE;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint32_t i = 0; i < 5; i++)
  {
    if (4 == i)
    {
      picoTestFrameworkIo.isPushButtonPress = FALSE;
    }
    PicoTestFramework_Tick();
    Application_Run();
    
  }
    
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  
  //simulate a long (i.e. >20 ticks) button press where the device stays in NRE,
  //cannot deliver any therapy, no pump activity, no pressure sensor activity
  picoTestFrameworkIo.isPushButtonPress = TRUE;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint32_t i = 0; i < 30; i++)
  {
    if (29 == i)
    {
      picoTestFrameworkIo.isPushButtonPress = FALSE;
    }
    PicoTestFramework_Tick();
    Application_Run();
    
  }
    
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  
  
  //simulate many ticks (i.e. 3h -> 108,000 ticks ) with no button press where the device stays in NRE,
  //cannot deliver any therapy, no pump activity, no pressure sensor activity
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint32_t i = 0; i < 108000; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
    
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  
}

//The device goes into NRE during MPD and cannot come out of it as a result of either a button press or running the device for a long time (>60mins)
void test_TheDeviceDetectsEndOfLifeErrorDuringTherapyDeliveryAndCannotBeRestartedToDeliverFurtherTherapy(void)
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
  
  
  //simulate next 2 ticks, no button press, target vacuum is not achieved
  PicoTestFramework_SetPushButton(FALSE);
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;

  PicoTestFramework_Tick();
  Application_Run();
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //simulate next tick, no button press, target vacuum is achieved
  picoTestFrameworkIo.getVacuumMeasurement = 107;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
  
  // Forward until we go into therapy
  while (THERAPY_DELIVERY_E != DeviceStatus_GetState())
  {
     PicoTestFramework_Tick();
     Application_Run();
  }	  
  
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  
  //simulate next 10 ticks, no pump activity, no button press, target vacuum is not achieved
  picoTestFrameworkIo.getVacuumMeasurement = 90;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  for(uint32_t i = 0; i <10; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
  }

  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());
  
  //simulate next 2 ticks, some pump activity, no button press
  //the device goes in NRE
  picoTestFrameworkIo.getVacuumMeasurement = 90;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  
  PicoTestFramework_Tick();
  Application_Run();
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  
  //simulate a short (i.e. >2 ticks) button press where the device stays in NRE,
  //cannot deliver any therapy, no pump activity, no pressure sensor activity
  picoTestFrameworkIo.isPushButtonPress = TRUE;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint32_t i = 0; i < 5; i++)
  {
    if (4 == i)
    {
      picoTestFrameworkIo.isPushButtonPress = FALSE;
    }
    PicoTestFramework_Tick();
    Application_Run();
    
  }
    
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

  
  //simulate a long (i.e. >20 ticks) button press where the device stays in NRE,
  //cannot deliver any therapy, no pump activity, no pressure sensor activity
  picoTestFrameworkIo.isPushButtonPress = TRUE;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint32_t i = 0; i < 30; i++)
  {
    if (29 == i)
    {
      picoTestFrameworkIo.isPushButtonPress = FALSE;
    }
    PicoTestFramework_Tick();
    Application_Run();
    
  }
    
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  
  
  //simulate many ticks (i.e. 3h -> 108,000 ticks ) with no button press where the device stays in NRE,
  //cannot deliver any therapy, no pump activity, no pressure sensor activity
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.pumpActivateTickCount = 0;
  for (uint32_t i = 0; i < 108000; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }
    
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.pumpActivateTickCount);
  TEST_ASSERT_EQUAL_INT(0, picoTestFrameworkIo.getVacuumTickCount);
  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
  
}

