/*****************************************************************************
 *   File        : test_HET_68.c
 *
 *   Description: Acceptance test for HET-68 (EEPROM is unchanged when getting into IDLE at power up)
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "unity.h"
#include <string.h>
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
#include "Battery.h"
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

static uint8_t eepromBytesWritten;
static int eepromWriteNumCall;
static uint8_t eepromBytes[2048]; //actual eeprom is 256k


// Stub for writing to the EEPROM
static ErrorCode_t Stub_I2E_Write(uint32_t address, uint8_t *data, uint8_t numBytes, int numCall)
{
  eepromWriteNumCall++;
  
  if (2048 > address + numBytes)
  {
    for(int count = 0; count < numBytes; count++)
    {
      eepromBytes[count + address] = data[count];
    }
    eepromBytesWritten = numBytes;
  }
  
  return EC_OK_E;
}



void setUp(void)
{
  PicoTestFramework_Setup();
  
  eepromBytesWritten = 0;
  eepromWriteNumCall = 0;
  memset(eepromBytes, 0xFF, sizeof(eepromBytes));
  
  I2E_Write_StubWithCallback(Stub_I2E_Write);
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  ADC_GetConversion_IgnoreAndReturn(0x2000);
  TX_Write_IgnoreAndReturn(EC_OK_E);
}

void tearDown(void)
{}

void test_CompleteIctPostAndCheckTheEepromIsUnchangedThenRestartDeviceSkipPostAndCheckTheEepromIsStillUnchanged(void)
{ 
  // do POST
  PORTAbits.RA0 = 0;
  PORTAbits.RA1 = 1;
  
  //initialise device
  Application_Init();
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  
  //simulate first timer tick, no button pressed, no LED change, device in POST
  PicoTestFramework_Tick();
  Application_Run();
  

  TEST_ASSERT_FALSE(picoTestFrameworkIo.isGreenLEDEnabled);
  TEST_ASSERT_FALSE(picoTestFrameworkIo.isOrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //run through post 0 to post 10 and check the EEPROM has not been changed
  uint8_t eepromInitialised[2048];
  memset(eepromInitialised, 0xFF, sizeof(eepromInitialised));
  
  POSTSubState_t expectedState = POST_STATE_00;
  for (int count = 0; count < 11; count++)
  {
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());

    //drive to the next POST state
    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;
    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;

    PicoTestFramework_Tick();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
    expectedState++;
  }
 
  TEST_ASSERT_EQUAL_INT(2, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(0, memcmp(eepromBytes, eepromInitialised, sizeof(eepromInitialised)));
  

  //switch the device off, set the pins so to skip POST, restart the application,
  //go into IDLE with no button press, check the EEPROM has not been changed
  PORTAbits.RA0 = 1;
  PORTAbits.RA1 = 0;
  eepromWriteNumCall = 0;
  
  Application_Init();    
  PicoTestFramework_Tick();
  Application_Run();
  
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(0, eepromWriteNumCall);
  TEST_ASSERT_EQUAL_INT(0, memcmp(eepromBytes, eepromInitialised, sizeof(eepromInitialised)));
}


