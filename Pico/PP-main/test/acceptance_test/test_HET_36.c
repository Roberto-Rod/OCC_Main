/*****************************************************************************
 *   File        : test_HET_36.c
 *
 *   Description: Acceptance test for HET-36
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
#include "DutyCycle.h"
#include "PushButton.h"
#include "Assert.h"

#include "LoggingManager.h"
#include "PerformanceLogger.h"

#include "MockWatchdog.h"
#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockBattery.h"

static bool_t therapyVacuumAchieved;
static uint32_t eepromAddress;
static uint8_t eepromBytesWritten;
static int eepromWriteNumCall;

bool_t Stub_isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum, int NumCall)
{
  return therapyVacuumAchieved;
}


ErrorCode_t StubI2E_Write(uint32_t address, uint8_t *data, uint8_t numBytes, int numCall)
{
  eepromAddress = address;
  eepromBytesWritten = numBytes;
  eepromWriteNumCall++;
  return EC_OK_E;
}

void setUp(void)
{
  PicoTestFramework_Setup();
  isTargetTherapyDeliveryVacuumAchieved_StubWithCallback(Stub_isTargetTherapyDeliveryVacuumAchieved);
  MP_EnableExternalPeripheralsSupply_Ignore();
 

  I2E_Write_StubWithCallback(StubI2E_Write);
  
  eepromAddress = 0;
  eepromBytesWritten = 0;
  eepromWriteNumCall = 0;

}

void tearDown(void)
{}


void test_PerformanceDataIsStoredEveryMinuteDuringMPD(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //we start in POST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //first time tick. POST doesnt check button press
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //second timer tick, we're in IDLE, this is the first IDLE tick with the button depressed
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //third timer tick, we're in idle, button pressed for 100ms
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate fourth timer tick, with button pressed (being pressed for 200ms), no LED change
  //(the chage state will be detected the next tick around by the Alert Manager)
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  const uint32_t oneMinuteTickCount = 600;
  PicoTestFramework_SetPushButton(FALSE);
  MP_EnableMainCircuitPower_Ignore();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  TherapyDeliveryTargetVacuumUpdate_Ignore();
  therapyVacuumAchieved = TRUE;
  State_t expectedState = PUMP_DOWN_E;
  picoTestFrameworkIo.getVacuumMeasurement = 107;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;


  // Since the pump down last for 20 seconds we need to advance the time until
  // we reach therapy.
  // In this test the pressure will be met for the entire period 
  uint32_t tickCount =  PUMP_DOWN_COUNT_TICK_DURATION;
  for (uint32_t i = 0; i < tickCount; i++)
  {

    if (i >= (PUMP_DOWN_COUNT_TICK_DURATION))          // PUMP_DOWN_COUNT_TICK_DURATION = 20
    {
      expectedState = THERAPY_DELIVERY_E;
    }

    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(expectedState, DeviceStatus_GetState());
  }

  //we have already completed 6 ticks
  for (uint32_t i = 0; i < oneMinuteTickCount - 6 -PUMP_DOWN_COUNT_TICK_DURATION; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
    TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
  }

  //write to log on next tick
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());

  TEST_ASSERT_EQUAL_INT(0, eepromAddress);
  TEST_ASSERT_EQUAL_INT(16, eepromBytesWritten);
  TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);

  for (uint32_t i = 0; i < oneMinuteTickCount; i++)
  {
    TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  }

  TEST_ASSERT_EQUAL_INT(2, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(16, eepromAddress);
  TEST_ASSERT_EQUAL_INT(16, eepromBytesWritten);
}
