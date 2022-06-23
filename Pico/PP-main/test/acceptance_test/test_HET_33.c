/*****************************************************************************
 *   File        : test_HET_33.c
 *
 *   Description: This is a copy of HET-18, which tests the EEPROM read and write in POST state 6
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
#include "DeviceStatus.h"
#include "pic16lf1509.h"
#include "Application.h"

#include "MockAlertManager.h"
#include "MockLoggingManager.h"
#include "MockUIInterfaces.h"

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
#include "I2CEEPROM.h"
#include "MockPerformanceLogger.h"

#include "Timer.h"

#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPushButton.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockDutyCycle.h"
#include "Battery.h"
#include "Mocki2c.h"
#include "MockWatchdog.h"


#include "Assert.h"

extern void TMR1_CallBack(void);

static bool_t PushButtonPress = FALSE;
static bool_t GreenLEDEnabled = FALSE;
static bool_t OrangeLEDEnabled = FALSE;

static bool_t Stub_PushButton_IsPressed(int NumCall)
{
  return (PushButtonPress);
}

static void Stub_LED_SetGreen(bool_t on, int NumCall)
{
  GreenLEDEnabled = on;
}

static void Stub_LED_SetOrange(bool_t on, int NumCall)
{
  OrangeLEDEnabled = on;
}

// Ignore low power in this test 
static void StubMP_WaitForInterrupInLowPowerIfPossible(int numCall)
{
}


void setUp(void)
{
  HardwareInterface_SystemInitialise_Ignore();
  HardwareInterface_EnableGlobalInterrupt_Ignore();
  HardwareInterface_DisableGlobalInterrupt_Ignore();
  HardwareInterface_EnablePeripheralInterrupt_Ignore();

  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);

  MP_SetReferenceVoltageBoost_Ignore();
  MP_DisablePumpPWM_Ignore();
  MP_EnableExternalPeripheralsSupply_Ignore();
  MP_DisableExternalPeripheralsSupply_Ignore();
  MP_DisableMainCircuitPower_Ignore();
  MP_EnableRelaxationOscillator_Ignore();
  SetInitialExternalPressure_Ignore();
  GetVacuum_IgnoreAndReturn(EC_OK_E); // to review
  InitPumpDownVacuum_Ignore();
  InitTherapyDeliveryVacuum_Ignore();
  DCHistoryReset_Ignore();
  isTargetPumpDownVacuumAchieved_IgnoreAndReturn(FALSE);

  PushButtonPress = FALSE;
  GreenLEDEnabled = FALSE;
  OrangeLEDEnabled = FALSE;
  PushButton_IsPressed_StubWithCallback(Stub_PushButton_IsPressed);
  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);
  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);

  AlertManager_Init_IgnoreAndReturn(EC_OK_E);
  AlertManager_Run_IgnoreAndReturn(EC_OK_E);

  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);

  Watchdog_Init_Ignore();
  Watchdog_Clear_Ignore();

  TX_Init_Ignore();
  I2C_Initialize_Ignore();

  MP_SleepUntilWokenByRelaxationOscillator_Ignore();
  MP_DisablePeripheral_Ignore();

  //skip through POST
  PORTAbits.RA0 = 0;
  PORTAbits.RA1 = 1;
}

void tearDown(void)
{}

void test_TestEEPROMWriteAndReadHappyCase(void)
{

  Application_Init();

  // verify in POST 
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  iPOST_setSubStateNum(0);  //reset after the last test

  // timer callback
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  // timer callback, nothing happens still in POST
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  TMR1_CallBack();

  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //run through post 0 to post 5
  POSTSubState_t expectedState = POST_STATE_00;
  ADC_GetConversion_IgnoreAndReturn(0x2000);
  for (int count = 1; count < 6; count++)
  {
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());

    //drive to the next POST state
    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;
    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;
    if ((1 == count) || (4 == count) || (5 == count)) //post states 1, 4 and 5 transmit stuff but we don't care right now
    {
      TX_Write_ExpectAnyArgsAndReturn(EC_OK_E);
    }

    TMR1_CallBack();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
    expectedState++;
  }
  TEST_ASSERT_EQUAL_INT(POST_STATE_05, iPOST_getSubStateNum());

  //post 6 is the first one with I2C EEPROM stuff
  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;
  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;

  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;
  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t data[2] = {0xAA, 0x55};
  uint8_t addrData[2] = {0, 0};
  uint8_t readData[2] = {0xAA, 0x55};  //read data matches written data
  uint8_t EEPROMBusAddr = 0x50;

  //EEPROM write set up for POST 6
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 4, EEPROMBusAddr);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();
  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);

  //EEPROM read set up for POST 6
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 2, EEPROMBusAddr);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();
  I2C_MasterReadTRBBuild_Expect(NULL, NULL, 2, EEPROMBusAddr);
  I2C_MasterReadTRBBuild_IgnoreArg_ptrb();
  I2C_MasterReadTRBBuild_IgnoreArg_pdata();
  I2C_MasterReadTRBBuild_ReturnMemThruPtr_pdata(readData, 2);  //copy the desired bytes here already
  I2C_MasterTRBInsert_Expect(2, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);

  //define what message we expect to see
  uint8_t TXMessage[4] = {0x06, 0x03, 0x03, 0x06 ^ 0x03 ^ 0x03};
  TX_Write_ExpectWithArrayAndReturn(TXMessage, 4, 4, EC_OK_E);

  //EEPROM write to reinitialise the EEPROM to a default value for POST 6
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 4, EEPROMBusAddr);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();
  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);
  
  //run POST 6
  TMR1_CallBack();
  Application_Run();

}

void test_TestEEPROMWriteAndReadWithIncorrectBytesRead(void)
{
  I2C_MasterWriteTRBBuild_Ignore();
  I2C_MasterReadTRBBuild_Ignore();
  Application_Init();
  iPOST_setSubStateNum(0);  //reset after the last test

  // timer callback, nothing happens still inPOST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //timer callback, nothing happens still in POST
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  TMR1_CallBack();

  Application_Run();
  

  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //run through post 0 to post 5
  POSTSubState_t expectedState = POST_STATE_00;
  ADC_GetConversion_IgnoreAndReturn(0x2000);
  for (int count = 1; count < 6; count++)
  {
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());

    //drive to the next POST state
    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;
    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;
    if ((1 == count) || (4 == count) || (5 == count)) //post states 1, 4 and 5 transmit stuff but we don't care right now
    {
      TX_Write_ExpectAnyArgsAndReturn(EC_OK_E);
    }

    TMR1_CallBack();
    Application_Run();
    
    TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
    expectedState++;
  }
  TEST_ASSERT_EQUAL_INT(POST_STATE_05, iPOST_getSubStateNum());

  //post 6 is the first one with I2C EEPROM stuff
  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;
  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;

  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;
  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t data[2] = {0xAA, 0x55};
  uint8_t addrData[2] = {0, 0};
  uint8_t readData[2] = {0xAA, 0x42};  //read data doesnot written data
  uint8_t EEPROMBusAddr = 0x50;

  //EEPROM write set up for POST 6
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 4, EEPROMBusAddr);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();
  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);

  //EEPROM read set up for POST 6
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 2, EEPROMBusAddr);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();
  I2C_MasterReadTRBBuild_Expect(NULL, NULL, 2, EEPROMBusAddr);
  I2C_MasterReadTRBBuild_IgnoreArg_ptrb();
  I2C_MasterReadTRBBuild_IgnoreArg_pdata();
  I2C_MasterReadTRBBuild_ReturnMemThruPtr_pdata(readData, 2);  //copy the desired bytes here already
  I2C_MasterTRBInsert_Expect(2, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);

  //define what message we expect to see
  uint8_t TXMessage[4] = {0x06, 0x03, 0x01, 0x06 ^ 0x03 ^ 0x01};
  TX_Write_ExpectWithArrayAndReturn(TXMessage, 4, 4, EC_OK_E);

  //EEPROM write to reinitialise the EEPROM to a default value for POST 6
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 4, EEPROMBusAddr);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();
  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);
  
  //run POST 6
  TMR1_CallBack();
  Application_Run();
  
  
}

