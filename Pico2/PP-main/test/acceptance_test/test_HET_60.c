/*****************************************************************************
 *   File        : test_HET_60.c
 *
 *   Description: Acceptance test for HET-60
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
#include "LoggingManager.h"

#include "PerformanceLogger.h"
#include "MockBattery.h"
#include "Timer.h"
#include "UIInterfaces.h"
#include "DutyCycle.h"
#include "PushButton.h"
#include "Assert.h"

#include "MockWatchdog.h"
#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"


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
  Battery_CheckVoltageBounds_IgnoreAndReturn(EC_OK_E);
  MP_GetBoostDemand_IgnoreAndReturn(VBOOST_REF_29V);
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



void test_LogInitialPumpDownDurationInPersistentMemoryWhenInTherapyDelivery(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //we start in POST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //first time tick. POST doesnt check button press
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //second timer tick
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //third timer tick, we're in IDLE, this is the first IDLE tick with the button depressed
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //fourth timer tick, we're in IDLE, this is the second IDLE tick with the button depressed
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate fifth timer tick, with button pressed (being pressed for 200ms), no LED change
  //(the chage state will be detected the next tick around by the Alert Manager)
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //run for 10 ticks in PUMP DOWN before achieving the target vacuum, no storing of
  //Pump Down duration in RAM, no logging to EEPROM
  PicoTestFramework_SetPushButton(FALSE);
  picoTestFrameworkIo.getVacuumMeasurement = 90;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  uint32_t const expectedPumpDownDuration = 10;
  
  for (uint32_t i = 0; expectedPumpDownDuration > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());

  //simulate another time tick where the target vacuum is achieved, state change on THERAPY DELIVERY,
  //store initial Pump Down duration in RAM, no logging to EEPROM
  //(note:the device stayed in PUMP DOWN for full 10 ticks before detecting the switch to Therapy Delivery
  //at the beginning of the 11th tick therefore the overall pump down duration is 10 ticks)  
  picoTestFrameworkIo.getVacuumMeasurement = 107;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = TRUE;
  TherapyDeliveryTargetVacuumUpdate_Ignore();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);

  PicoTestFramework_Tick();
  Application_Run();
  
    
  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(expectedPumpDownDuration, PerformanceLogger_GetPumpDownDuration100Ms());
  
  //simulate enough ticks in PUMP DOWN and THERAPY DELIVERY to get to the 60 seconds logging period
  //(we have already completed 17 ticks), no storing of Pump Down duration in RAM (already done),
  //no logging to EEPROM
  const uint32_t oneMinuteTickCount = 600;
  MP_EnableMainCircuitPower_Ignore();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  TherapyDeliveryTargetVacuumUpdate_Ignore();
  therapyVacuumAchieved = TRUE;
  State_t expectedState = PUMP_DOWN_E;
  
  for (uint32_t i = 0; i < oneMinuteTickCount - 17; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();

    // 2 ticks were done separately 
    if (i >= 189 ) 
    {
       expectedState = THERAPY_DELIVERY_E;
    }

    TEST_ASSERT_EQUAL_INT(expectedState, DeviceStatus_GetState());

    TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
    TEST_ASSERT_EQUAL_INT(expectedPumpDownDuration, PerformanceLogger_GetPumpDownDuration100Ms());
  }
  
  //simulate another tick, it's time to log the device perfomances to the EEPROM, and reinitialise
  //their value in RAM
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());

  //simulate enough ticks in THERAPY DELIVERY to get to the 60 seconds logging period
  //(no storing of Pump Down duration in RAM as we are in THERAPY DELIVERY),
  for (uint32_t i = 0; i < oneMinuteTickCount; i++)
  {
    TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());
  }

  TEST_ASSERT_EQUAL_INT(2, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());
  
}


void test_LogUnsuccessfulInitialPumpDownDurationInPersistentMemoryWhenInFault(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //we start in POST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //first time tick. POST doesnt check button press
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //second timer tick
  PicoTestFramework_SetPushButton(FALSE);
  PicoTestFramework_Tick();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //third timer tick, we're in IDLE, this is the first IDLE tick with the button depressed
  PicoTestFramework_SetPushButton(TRUE);
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //fourth timer tick, we're in IDLE, this is the second IDLE tick with the button depressed
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  //simulate fifth timer tick, with button pressed (being pressed for 200ms), no LED change
  //(the chage state will be detected the next tick around by the Alert Manager)
  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

  //PUMP DOWN runs for 20s without achieving a terget vacuum, no storing of
  //Pump Down duration in RAM, no logging to EEPROM
  PicoTestFramework_SetPushButton(FALSE);
  TherapyDeliveryTargetVacuumUpdate_Ignore();
  picoTestFrameworkIo.getVacuumMeasurement = 90;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  uint32_t const expectedPumpDownDuration = 200;
  
  for (uint32_t i = 0; expectedPumpDownDuration > i; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
  }

  TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());  
  TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());

  //simulate another time tick where the PUMP DOWN is considered unsuccessful, state change on FAULT,
  //store initial Pump Down duration in RAM, no logging to EEPROM
  PicoTestFramework_Tick();
  Application_Run();
  
    
  TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);

  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());

  //simulate enough ticks in FAULT_E to get to the 60 seconds logging period
  //(we have already completed 207 ticks), no storing of Pump Down duration in RAM (already done),
  //no logging to EEPROM
  const uint32_t oneMinuteTickCount = 600;
  MP_EnableMainCircuitPower_Ignore();
  isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
  TherapyDeliveryTargetVacuumUpdate_Ignore();
  therapyVacuumAchieved = TRUE;
  
  for (uint32_t i = 0; i < oneMinuteTickCount - 207; i++)
  {
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
    TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
    TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());
  }
  
  //simulate another tick, it's time to log the device perfomances to the EEPROM, and reinitialise
  //their value in RAM
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());

  //simulate enough ticks in THERAPY DELIVERY to get to the 60 seconds logging period
  //(no storing of Pump Down duration in RAM as we are in THERAPY DELIVERY),
  for (uint32_t i = 0; i < oneMinuteTickCount; i++)
  {
    TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);
    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(FAULT_E, DeviceStatus_GetState());
  }

  TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());
  TEST_ASSERT_EQUAL_INT(2, eepromWriteNumCall);
}



// void test_LogUnsuccessfulInitialPumpDownDurationInPersistentMemoryWhenInNonRecoverableError(void)
// {
//   I2E_Read_IgnoreAndReturn(EC_FAILED_E);
//   Application_Init();

//   //we start in POST
//   TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

//   //first time tick. POST doesnt check button press
//   PicoTestFramework_Tick();
//   Application_Run();
  
//   TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

//   //second timer tick
//   PicoTestFramework_SetPushButton(FALSE);
//   PicoTestFramework_Tick();
//   Application_Run();
  
//   TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

//   //third timer tick, we're in IDLE, this is the first IDLE tick with the button depressed
//   PicoTestFramework_SetPushButton(TRUE);
//   PicoTestFramework_Tick();
//   Application_Run();

//   TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

//   //fourth timer tick, with button pressed (being pressed for 100ms), no LED change
//   //(the chage state will be detected the next tick around by the Alert Manager)
//   PicoTestFramework_Tick();
//   Application_Run();

//   TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());

//   //10 more ticks in PUMP DOWN, no storing of
//   //Pump Down duration in RAM, no logging to EEPROM
//   PicoTestFramework_SetPushButton(FALSE);
//   isTherapyDeliveryLeakDetected_IgnoreAndReturn(FALSE);
//   picoTestFrameworkIo.getVacuumMeasurement = 90;
//   picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
//   picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
//   uint32_t expectedPumpDownDuration = 10;
  
//   for (uint32_t i = 0; expectedPumpDownDuration > i; i++)
//   {
//     PicoTestFramework_Tick();
//     Application_Run();
        
//   }

//   TEST_ASSERT_EQUAL_INT(PUMP_DOWN_E, DeviceStatus_GetState());
//   TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
//   TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());
  
//   //1 tick in PUMP Down where an unrecoverable error is generated, state change into NRE_E
//   //store initial Pump Down duration in RAM, no logging to EEPROM 
//   picoTestFrameworkIo.pumpActivateResult = EC_BATTERY_END_OF_LIFE_E;
  
//   PicoTestFramework_Tick();
//   Application_Run();
  
  
//   TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
//   TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
//   // replace with next line TEST_ASSERT_EQUAL_INT(expectedPumpDownDuration, PerformanceLogger_GetPumpDownDuration100Ms());
//   TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());
  

//   //simulate enough ticks in NRE_E to get to the 60 seconds logging period
//   //(we have already completed 16 ticks), no storing of Pump Down duration in RAM (already done),
//   //no logging to EEPROM
//   const uint32_t oneMinuteTickCount = 600;
  
//   for (uint32_t i = 0; i < oneMinuteTickCount - 16; i++)
//   {
//     PicoTestFramework_Tick();
//     Application_Run();
    
//     TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
//     TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
//     // check that the time logged is the time when pressure is achieved 
//     TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());
//   }

//   //simulate another tick, it's time to log the device perfomances to the EEPROM, and reinitialise
//   //their value in RAM
//   PicoTestFramework_Tick();
//   Application_Run();
  

//   TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
//   TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);
//   TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());

//   //simulate enough ticks in NRE to get to the 60 seconds logging period
//   //(no storing of Pump Down duration in RAM as we are in NRE),
//   for (uint32_t i = 0; i < oneMinuteTickCount; i++)
//   {
//     TEST_ASSERT_EQUAL_INT(1, eepromWriteNumCall);
//     PicoTestFramework_Tick();
//     Application_Run();
    
//     TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());
//   }

//   TEST_ASSERT_EQUAL_INT(0, PerformanceLogger_GetPumpDownDuration100Ms());
//   TEST_ASSERT_EQUAL_INT(2, eepromWriteNumCall);
// }


