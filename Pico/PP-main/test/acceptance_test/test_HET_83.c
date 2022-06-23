/*****************************************************************************
 *   File        : test_HET_83.c
 *
 *   Description: Acceptance test for HET-83
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
  
}

void tearDown(void)
{}

// verfiy the system goes into NRE when the NRE is entered from idle  
void test_VerifyNREStateIsEnteredWhenNRErrorRaisedInIdle(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  I2E_Write_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  //we start in POST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //first time tick. POST doesnt check button press
  PicoTestFramework_Tick();
  Application_Run();

  StateMachine_Enter_NRE(TRUE);

  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

}

// verfiy the system goes into NRE when the NRE is netered from therapy 
void test_VerifyNREStateIsEnteredWhenNRErrorRaisedInTherapy(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  I2E_Write_IgnoreAndReturn(EC_OK_E);
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


  TEST_ASSERT_EQUAL_INT(THERAPY_DELIVERY_E, DeviceStatus_GetState());

  StateMachine_Enter_NRE(TRUE);

  PicoTestFramework_Tick();
  Application_Run();

  TEST_ASSERT_EQUAL_INT(NRE_E, DeviceStatus_GetState());

}
