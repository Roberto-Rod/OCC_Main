/*****************************************************************************
 *   File        : test_HET_39.c
 *
 *   Description: Acceptance test for HET-39
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

                                                        //  phase name  - duration - timeline
                                                        //                  (s)        (s)
uint8_t StartUpGreenLedPattern[] = {                    //                              0
  1,1,1,1,1,1,1,1,1,1,                                  //   Phase 1         1          1 
  1,0,1,0,1,0,1,0,1,0,                                  //   Phase 2         1          2 
  1,0,1,0,1,0,1,0,1,0,                                  //                   1          3
  1,0,1,0,1,0,1,0,1,0,                                  //                   1          4 
  1,0,1,0,1,0,1,0,1,0,                                  //                   1          5 
  1,0,1,0,1,0,1,0,1,0,                                  //                   1          6
  1,0,1,0,1,0,                                          //   Phase 3         0.6        6.6       
  1,0,0,1,0,0,1,0,0,                                    //                   0.9        7.5                 
  1,0,0,0,1,0,0,0,1,0,0,0,                              //                   1.2        8.7
  1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,                        //                   1.5        10.2
  1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,                  //                   1.8        12
  1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,            //                   2.1        14.1 
  1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,      //                   2.4        16.5
  1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,//                   2.7        19.2
  1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,                  //                   1.8        21
  1,1,1,1,1,1,1,1,1,1,                                  //   Phase 4         1          22                   
  1,1,1,1,1,1,1,1,1,1,                                  //                   2          23
};

void setUp(void)
{
  PicoTestFramework_Setup();
  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);
}

void tearDown(void)
{}

// The device goes from IDLE to PUMP DOWN to THERAPY DELIVERY with the correct LED pattern
// when target vacuum is achieved in PUMP DOWN
void test_DuringIPDWhenTargetPressureIsReachedTransitToMPD(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
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
  //the first button press, no LED change, no pressure reading, no pump activity
  //(the chage state will be detected the next tick around by the Alert Manager)
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
  
  uint32_t index = 0; // This handles the first entry from the table  
  // First Green LED of the Pump Down 
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_TRUE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_TRUE((StartUpGreenLedPattern[index])? 
                  picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  
  index++; 
  
  //simulate third timer tick , no button pressed, GREEN LED according to
  //given pattern (StartUpGreenLedPattern), ORANGE LED off

  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
 
  
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
  TEST_ASSERT_TRUE((StartUpGreenLedPattern[index])? 
                    picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_TRUE(PUMP_DOWN_E == DeviceStatus_GetState());

  //simulate next 149 thicks (well within the StartUpGreenLedPattern duration), no button pressed, 
  //GREEN LED according to given pattern (StartUpGreenLedPattern), ORANGE LED off, pump activity
  //assuming the target vacuum is not achieved
  for (uint8_t i = 0; i < 149; i++)
  {
    index++;
    PicoTestFramework_Tick();
    Application_Run();

    TEST_ASSERT_TRUE((0 == i%2) ? 
                      picoTestFrameworkIo.isPumpActivated : !picoTestFrameworkIo.isPumpActivated);
    TEST_ASSERT_TRUE((StartUpGreenLedPattern[index])? 
                    picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
    TEST_ASSERT_TRUE(PUMP_DOWN_E == DeviceStatus_GetState());
  }
 
 
  //simulate the target vacuum is achieved, no button pressed, GREEN LED according to given pattern
  //(StartUpGreenLedPattern), ORANGE LED off, the device goes THERAPY DELIVERY mode
  //Step 1. Get to the point a Vacuum Read is scheduled (we do not know at what point of the
  //        cycle pump or read the device is before running this step). Since it is alternating between
  //        running pump and reading pressure, we try two times.
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;

  uint8_t tickCount = 2;
  while(tickCount-- > 0)
  {
    index++;
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_TRUE((StartUpGreenLedPattern[index])? 
                    picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled);
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  }
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //Step 2. The therapy is being delivered, no pump activity, the GREEN LED flashes according to given
  //        pattern (StartUpGreenLedPattern) with a solid ON period for its latter part , ORANGE LED off.
  //        After the given LED pattern is completed (let's tick well beyond the length of the pattern),
  //        both LEDs go OFF
  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = FALSE;
  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = TRUE;
  TherapyDeliveryTargetVacuumUpdate_Ignore();
  const uint32_t ptrnLength = sizeof(StartUpGreenLedPattern);
  State_t expectedState = PUMP_DOWN_E;

  for (uint32_t i = 0; i < ptrnLength*2; i++)
  {
    index++;
    PicoTestFramework_Tick();
    Application_Run();
    
    
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isPumpActivated);
    if (index < ptrnLength)
    {
      TEST_ASSERT_TRUE((StartUpGreenLedPattern[index])? 
                       picoTestFrameworkIo.isGreenLEDEnabled : !picoTestFrameworkIo.isGreenLEDEnabled);
    }
    else
    {
      TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
    }
    TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);

    if (i >= ( 48 ))    // PUMP_DOWN_COUNT_TICK_DURATION = 20
    {
       expectedState   = THERAPY_DELIVERY_E;
    }
    TEST_ASSERT_EQUAL_INT(expectedState, DeviceStatus_GetState());
  }
}

