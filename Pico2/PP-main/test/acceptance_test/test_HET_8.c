/*****************************************************************************
 *   File        : test_HET_8.c
 *
 *   Description: Acceptance test for HET-8
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


//The device detects a LEAK event in THERAPY DELIVERY and alerts the user accordingly
void test_DetectLeakInTherapyDeliveryAndAlertTheUserOfTheErrorCondition(void)
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

  // tick into therapy 
  for ( int i = 0; i <= 200; i++)
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

  // Verify now in therapy 
  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());
 
  
  //simulate as many ticks are needed to detect a LEAK.
  //As result the device goes into FAULT. And in the next tick the LED will go off  
  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = TRUE;

  for (uint32_t i = 0; THERAPY_DELIVERY_E == DeviceStatus_GetState(); i++)
  {
    // Verify both LEDs are off	  
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    PicoTestFramework_Tick();
    Application_Run();
        
  }

  // Orange LED has now come on 
  TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);

  //simulate next 19 further ticks where the device stays in FAULT state, with
  //GREEN LED always OFF, AMBER LED being solid (2 s) followed by the repetition of the
  //pattern (0.2s ON, 1.8s OFF) as long it is in FAULT state  
  for (uint32_t i = 0; i < 19; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_TRUE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());
  }
  
  
  //simulate next 80 ticks where the device stays in FAULT state, with
  //GREEN LED always OFF, and the AMBER LED repeating the pattern (0.2s ON, 1.8s OFF)
  //as long it is in FAULT state
  bool_t orange_status = FALSE;
  uint32_t count = 0;
  for (uint32_t i = 0; i < 80; i++)
  {
    count = i%20;
    orange_status = ((0 == count) || (1 == count)) ? TRUE:FALSE;
    
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_EQUAL_INT(orange_status, picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_TRUE(FAULT_E == DeviceStatus_GetState());
  }

}


//The device detects and ignores a LEAK event when the Boost Voltage Demand is below 
//its reference value of 27V (i.e. not optimal working conditions) in THERAPY DELIVERY.
//No alert is raised to the user, the devices stays in THERAPY DELIVERY and tries its
//best to cope with the leak
void test_DetectAndIgnoreLeakInTherapyDeliveryWhenBoostVoltageDenandIsBelow27V(void)
{ 
  TherapyDeliveryTargetVacuumUpdate_Ignore();
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

  // tick into therapy 
  for ( int i = 0; i <= 200; i++)
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
 
  
  //simulate 400 ticks where the target vacuum is not actieved and the pump is activated well above
  //the LEAK duty cycle.
  //As result the device ignores the Leak condition and remains into THERAPY DELIVERY with no alert
  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = TRUE;
  picoTestFrameworkIo.isBoostVoltageDemandAtReference27V = FALSE;
  
  for (uint32_t i = 0; i < 400; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
        
  }

  TEST_ASSERT_TRUE(THERAPY_DELIVERY_E == DeviceStatus_GetState());
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
}
