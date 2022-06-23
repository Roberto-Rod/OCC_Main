/*****************************************************************************
 *   File        : test_StateMachinePOST_internal.c
 *
 *   Description: Source Code for test of the State Machine POST internal.
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

#include <string.h>
#include "unity.h"
#include "StateMachinePOST_internal.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockpin_manager.h"
#include "MockPowerControl.h"
#include "MockPressure_Part1.h"
#include "Mockadc.h"
#include "MockTimer.h"
#include "pic16lf1509.h"

// replaces the volative variable used in pic16lf1509.h for this register
unsigned char NCO1CON;

ErrorCode_t vacReturnVal = EC_OK_E;

static uint16_t TestInternal = 0x4567;
static uint16_t TestExternal = 0x5678;
uint16_t vacVacuum = 0x1234;

uint8_t TXWBytes[16];
ErrorCode_t TXWReturnVal = EC_OK_E;
uint8_t TXWNumBytes;

uint8_t EEPROM_bytes[2048]; //actual eeprom is 256k
ErrorCode_t EEPROM_writeRetVal;
ErrorCode_t EEPROM_readRetVal;
uint8_t EEPROM_numBytesRead;
uint8_t EEPROM_numBytesWrite;
static bool_t reinitialiseEepromWrite = FALSE;


// Stub for getting the vacuum reading 
static ErrorCode_t Stub_GetVacuum(uint16_t* pInternal, uint16_t* pExternal, uint16_t* theVac, int NumCalls)
{
  ErrorCode_t result = vacReturnVal;
  *pInternal = TestInternal;
  *pExternal = TestExternal;
  *theVac = vacVacuum;
  
  return result;
}

// Stub for transmitting some bytes
static ErrorCode_t Stub_TXWrite(uint8_t *data, uint8_t numBytes, int NumCall)
{
  ErrorCode_t result = TXWReturnVal;
  if(EC_OK_E == result)
  {
    for(int count = 0; count < numBytes; count++)
    {
      TXWBytes[count] = data[count];
    }
    TXWNumBytes = numBytes;
  }
  return result;
}

// Stub for writing to the EEPROM
static ErrorCode_t Stub_EEPROMWrite(uint32_t  address, uint8_t *data, uint8_t numBytes, int NumCall)
{
  ErrorCode_t result = EEPROM_writeRetVal;
  if((EC_OK_E == result) && (2048 > address + numBytes) && !reinitialiseEepromWrite)
  {
    for(int count = 0; count < numBytes; count++)
    {
      EEPROM_bytes[count + address] = data[count];
    }
    //reinitialiseEepromWrite = TRUE;
  }
  
  // State POST 06 writes two test values into the EEPROM, reads them back and then reinitialise
  // the EEPROM to 0xFF, therefore we catch only the first write to check if the test values get
  // written correctly
  reinitialiseEepromWrite = !reinitialiseEepromWrite;
  
  EEPROM_numBytesWrite = numBytes;
  return result;
}

// Stub for reading to the EEPROM
static ErrorCode_t Stub_EEPROMRead(uint32_t  address, uint8_t *data, uint8_t numBytes, int NumCall)
{
  ErrorCode_t result = EEPROM_readRetVal;
  if((EC_OK_E == result) && (2048 > address + numBytes))
  {
    for(int count = 0; count < numBytes; count++)
    {
      data[count] = EEPROM_bytes[count + address];
    }
  }
  EEPROM_numBytesRead = numBytes;
  return result;
}

void setGPIOs(uint8_t RC2Val, uint8_t RC3Val, uint8_t RC4Val, uint8_t RC5Val,
              uint8_t RC6Val, uint8_t RC7Val, uint8_t RB5Val)
{
    PORTCbits.RC2 = RC2Val;
    PORTCbits.RC3 = RC3Val;
    PORTCbits.RC4 = RC4Val;
    PORTCbits.RC5 = RC5Val;
    PORTCbits.RC6 = RC6Val;
    PORTCbits.RC7 = RC7Val;
    PORTBbits.RB5 = RB5Val;            
}

void checkGPIOs(uint8_t RC2Val, uint8_t RC3Val, uint8_t RC4Val, uint8_t RC5Val,
                uint8_t RC6Val, uint8_t RC7Val, uint8_t RB5Val)
{
    TEST_ASSERT_BITS(_PORTC_RC2_MASK, RC2Val, PORTCbits.RC2);
    TEST_ASSERT_BITS(_PORTC_RC3_MASK, RC3Val, PORTCbits.RC3);
    TEST_ASSERT_BITS(_PORTC_RC4_MASK, RC4Val, PORTCbits.RC4);
    TEST_ASSERT_BITS(_PORTC_RC5_MASK, RC5Val, PORTCbits.RC5);
    TEST_ASSERT_BITS(_PORTC_RC6_MASK, RC6Val, PORTCbits.RC6);
    TEST_ASSERT_BITS(_PORTC_RC7_MASK, RC7Val, PORTCbits.RC7);
    TEST_ASSERT_BITS(_PORTB_RB5_MASK, RB5Val, PORTBbits.RB5);
}

void setUp(void)
{
  reinitialiseEepromWrite = FALSE;
  
  PM_Delay_Ignore();
}

void tearDown(void)
{}

void test_getAndSetOfStateNumber(void)
{
  TEST_ASSERT_EQUAL_INT(0xFF, iPOST_getSubStateNum());
  iPOST_setSubStateNum(0x30);
  TEST_ASSERT_EQUAL_INT(0x30, iPOST_getSubStateNum());
}

void test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_go(void)
{
  uint8_t retVal;
  
  //set pins so we go into POST mode
  PORTAbits.RA0 = 0;
  PORTAbits.RA1 = 1;
  iPOST_setSubStateNum(0xFF);
  
  //set the output pin values high so we can see they are all set low afterwards
  setGPIOs(1, 1, 1, 1, 1, 1, 1);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);
  retVal = iPOST_doPOST();

  TEST_ASSERT_EQUAL_INT(1, retVal);
  TEST_ASSERT_EQUAL_INT(POST_STATE_00, iPOST_getSubStateNum());
  checkGPIOs(0, 0, 0, 0, 0, 0, 0);

  //run it again The boost voltage isn't called and the pins are not reset
  setGPIOs(1, 1, 1, 1, 1, 1, 1);
  retVal = iPOST_doPOST();
  TEST_ASSERT_EQUAL_INT(1, retVal);
  TEST_ASSERT_EQUAL_INT(POST_STATE_00, iPOST_getSubStateNum());
  checkGPIOs(1, 1, 1, 1, 1, 1, 1);
}

void test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_no(void)
{
  uint8_t retVal;
  
  //set pins so we go into POST mode
  PORTAbits.RA0 = 1;
  PORTAbits.RA1 = 0;
  iPOST_setSubStateNum(0xFF);
  
  //set the output pin values high so we can see they are all set low afterwards
  setGPIOs(1, 1, 1, 1, 1, 1, 1);
  retVal = iPOST_doPOST();
  TEST_ASSERT_EQUAL_INT(0, retVal);
  TEST_ASSERT_EQUAL_INT(POST_STATE_MAX, iPOST_getSubStateNum());
  checkGPIOs(1, 1, 1, 1, 1, 1, 1);

  //run it again The boost voltage isn't called and the pins are not reset
  setGPIOs(0, 0, 0, 0, 0, 0, 0);
  retVal = iPOST_doPOST();
  TEST_ASSERT_EQUAL_INT(POST_STATE_MAX, iPOST_getSubStateNum());
  TEST_ASSERT_EQUAL_INT(0, retVal);
  checkGPIOs(0, 0, 0, 0, 0, 0, 0);
}

void test_weCycleThroughTheStatesProperly(void)
{
  PORTAbits.RA0 = 0;
  PORTAbits.RA1 = 1;
  POSTSubState_t expectedState = POST_STATE_00;
  iPOST_setSubStateNum(POST_STATE_00);
  
  for(int count = 0; count < POST_STATE_MAX; count++)
  {
    //test from previous iteration through the loop
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());

    //state doesn't change while RA0 and RA1 are constant  
    iPOST_updateSubStateNum();
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());
    iPOST_updateSubStateNum();
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());
    iPOST_updateSubStateNum();
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());
    
    //state doesn't change if only RA-0 toggles
    PORTAbits.RA0 ^= 0x01;
    iPOST_updateSubStateNum();
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());
    
    //state doesn;t change if only RA1 toggles
    PORTAbits.RA0 ^= 0x01;
    PORTAbits.RA1 ^= 0x01;
    iPOST_updateSubStateNum();
    TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());
    
    //state changes when both RA0 and RA1 toggle (tested on next iteration)
    PORTAbits.RA0 ^= 0x01;
    expectedState++;
    iPOST_updateSubStateNum();
  }
  //test that the state wraps around after we reach max
  TEST_ASSERT_EQUAL_INT(POST_STATE_00, iPOST_getSubStateNum());
}

void test_State00SetsRC4(void)
{
  setGPIOs(0, 0, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State00());
  checkGPIOs(0, 0, 1, 0, 0, 0, 0);
  
  setGPIOs(1, 1, 0, 1, 1, 1, 1);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State00());
  checkGPIOs(1, 1, 1, 1, 1, 1, 1);
}

void test_State01SetsReferenceVBoostReadsBoostVoltageADCAndTransmitsOnTX(void)
{
  TX_Write_StubWithCallback(Stub_TXWrite);
  
  //test happy case, RC4 must stays high
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  setGPIOs(0, 0, 1, 0, 0, 0, 0);
  
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(Boost_Voltage, 0xABCD);
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State01());
  checkGPIOs(0, 0, 1, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x01, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0xCD, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0xAB, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //test TX failure, RC4 must stays high
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(Boost_Voltage, 0x1357);

  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State01());
  checkGPIOs(0, 0, 1, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
}

void test_State02SetsRC7AndClearsVBoost(void)
{
  setGPIOs(0, 0, 0, 0, 0, 0, 0);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State02());
  checkGPIOs(0, 0, 0, 0, 0, 1, 0);
  
  setGPIOs(1, 1, 1, 1, 1, 0, 1);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State02());
  checkGPIOs(1, 1, 1, 1, 1, 1, 1);
}

void test_State03SetsRC5ClearsRC7(void)
{
  setGPIOs(0, 0, 0, 0, 0, 1, 0);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State03());
  checkGPIOs(0, 0, 0, 1, 0, 0, 0);
  
  setGPIOs(1, 1, 1, 0, 1, 1, 1);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State03());
  checkGPIOs(1, 1, 1, 1, 1, 0, 1);
}

void test_State04SetsRC2ClearsRC5ReadsAndTransmitsTheExternalVacuum(void)
{
  GetVacuum_StubWithCallback(Stub_GetVacuum);
  TX_Write_StubWithCallback(Stub_TXWrite);

  setGPIOs(0, 1, 1, 1, 1, 1, 1);
  vacReturnVal = EC_OK_E;
  vacVacuum = 0x5678;
  TestExternal = 0x1234;
  TestInternal = 0x3456;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State04());
  checkGPIOs(1, 1, 1, 0, 1, 1, 1);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x04, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x34, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x12, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //vacuum error
  setGPIOs(0, 0, 0, 1, 0, 0, 0);
  vacReturnVal = EC_FAILED_E;
  vacVacuum = 0x5678;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State04());
  checkGPIOs(1, 0, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //reported transmit error
  vacReturnVal = EC_OK_E;
  vacVacuum = 0x5678;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State04());
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
}

void test_State05ClearsRC2ReadsAndTransmitsTheInternalVacuum(void)
{
  GetVacuum_StubWithCallback(Stub_GetVacuum);
  TX_Write_StubWithCallback(Stub_TXWrite);

  //happy case
  setGPIOs(1, 1, 1, 1, 1, 1, 1);
  vacReturnVal = EC_OK_E;
  vacVacuum = 0x2345;
  TestExternal = 0x3456;
  TestInternal = 0x1234;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State05());
  checkGPIOs(0, 1, 1, 1, 1, 1, 1);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x05, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x34, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x12, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //vacuum error
  setGPIOs(1, 0, 0, 0, 0, 0, 0);
  vacReturnVal = EC_FAILED_E;
  vacVacuum = 0x5678;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State05());
  checkGPIOs(0, 0, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //reported transmit error
  vacReturnVal = EC_OK_E;
  vacVacuum = 0x5678;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State05());
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
}

void test_State06WritesToTheEEPROMAndReadsItBack(void)
{
  I2E_Write_StubWithCallback(Stub_EEPROMWrite);
  I2E_Read_StubWithCallback(Stub_EEPROMRead);
  TX_Write_StubWithCallback(Stub_TXWrite);
  
  //test happy case
  EEPROM_writeRetVal = EC_OK_E;
  EEPROM_readRetVal = EC_OK_E;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  MP_EnableExternalPeripheralsSupply_Expect();
  MP_DisableExternalPeripheralsSupply_Expect();
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State06());
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x06, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x03, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x03, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  TEST_ASSERT_EQUAL_INT(0xAA, EEPROM_bytes[0]);
  TEST_ASSERT_EQUAL_INT(0x55, EEPROM_bytes[1]);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesRead);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesWrite);
  
  //test write fail
  EEPROM_writeRetVal = EC_FAILED_E;
  EEPROM_readRetVal = EC_OK_E;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  memset(EEPROM_bytes, 0, 16);
  MP_EnableExternalPeripheralsSupply_Expect();
  MP_DisableExternalPeripheralsSupply_Expect();
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State06());
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x06, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x02, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  TEST_ASSERT_EQUAL_INT(0x00, EEPROM_bytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, EEPROM_bytes[1]);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesRead);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesWrite);
  
  //test read fail
  EEPROM_writeRetVal = EC_OK_E;
  EEPROM_readRetVal = EC_FAILED_E;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  memset(EEPROM_bytes, 0, 16);
  MP_EnableExternalPeripheralsSupply_Expect();
  MP_DisableExternalPeripheralsSupply_Expect();
  
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State06());
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x06, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x01, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  TEST_ASSERT_EQUAL_INT(0xAA, EEPROM_bytes[0]);
  TEST_ASSERT_EQUAL_INT(0x55, EEPROM_bytes[1]);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesRead);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesWrite);
  
  //test transmit error
  EEPROM_writeRetVal = EC_OK_E;
  EEPROM_readRetVal = EC_OK_E;
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);
  MP_EnableExternalPeripheralsSupply_Expect();
  MP_DisableExternalPeripheralsSupply_Expect();
  
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State06());
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  TEST_ASSERT_EQUAL_INT(0xAA, EEPROM_bytes[0]);
  TEST_ASSERT_EQUAL_INT(0x55, EEPROM_bytes[1]);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesRead);
  TEST_ASSERT_EQUAL_INT(2, EEPROM_numBytesWrite); 
}

void test_State07TogglesRC6ClearsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX(void)
{  
  TX_Write_StubWithCallback(Stub_TXWrite);
  
  //test happy case
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  NCO1CON = 0xFF;
  setGPIOs(0, 1, 0, 0, 0, 0, 0);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(HBridge_Current, 0xABCD);

  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State07());
  checkGPIOs(1, 0, 0, 0, 1, 0, 0);
  TEST_ASSERT_EQUAL_INT(0x00, NCO1CON);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x07, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0xCD, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0xAB, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //retest happy case to see it RC6 toggled
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  NCO1CON = 0xFF;
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(HBridge_Current, 0x7654);

  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State07());
  checkGPIOs(1, 0, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(0x00, NCO1CON);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x07, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x54, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x76, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //test TX failure
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);
  setGPIOs(0, 1, 1, 1, 0, 1, 1);
  NCO1CON = 0xFF;
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(HBridge_Current, 0x1357);

  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State07());
  checkGPIOs(1, 0, 1, 1, 1, 1, 1);
  TEST_ASSERT_EQUAL_INT(0x00, NCO1CON);
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
}


void test_State08TogglesRC6SetsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX(void)
{
  TX_Write_StubWithCallback(Stub_TXWrite);
  
  //test happy case
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  setGPIOs(0, 0, 0, 0, 0, 0, 0);
  NCO1CON = 0xFF;
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(HBridge_Current, 0xABCD);

  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State08());
  checkGPIOs(1, 1, 0, 0, 1, 0, 0);
  TEST_ASSERT_EQUAL_INT(0x00, NCO1CON);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x08, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0xCD, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0xAB, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //retest happy case to see it RC6 toggled
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  NCO1CON = 0xFF;
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(HBridge_Current, 0x7654);

  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State08());
  checkGPIOs(1, 1, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(0x00, NCO1CON);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x08, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x54, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x76, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //test TX failure
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);
  setGPIOs(0, 0, 1, 1, 1, 1, 1);
  NCO1CON = 0xFF;
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_27V);
  ADC_GetConversion_ExpectAndReturn(HBridge_Current, 0x1357);

  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State08());
  checkGPIOs(1, 1, 1, 1, 0, 1, 1);
  TEST_ASSERT_EQUAL_INT(0x00, NCO1CON);
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x000, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
}
void test_State09ClearsRC3SetsDACto0ReadsRA5AndTransmitsRA5OnTX(void)
{
  TX_Write_StubWithCallback(Stub_TXWrite);
  
  //test happy case RA5 is 0
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  setGPIOs(1, 1, 1, 1, 1, 1, 1);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);
  PORTAbits.RA5 = 0;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State09());
  checkGPIOs(1, 0, 1, 1, 1, 1, 1);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x09, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x0, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x0, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //retest happy with RA5 = 1
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);
  setGPIOs(0, 1, 0, 0, 0, 0, 0);
  PORTAbits.RA5 = 1;

  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State09());
  checkGPIOs(0, 0, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x09, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x01, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //test TX failure
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);
  MP_SetReferenceVoltageBoost_Expect(VBOOST_REF_0V);

  setGPIOs(0, 1, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_State09());
  checkGPIOs(0, 0, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x000, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
}

void test_State10SetsRB5(void)
{
  setGPIOs(0, 0, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State10());
  checkGPIOs(0, 0, 0, 0, 0, 0, 1);
  
  setGPIOs(1, 1, 1, 1, 1, 1, 0);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_State10());
  checkGPIOs(1, 1, 1, 1, 1, 1, 1);
}

void test_StateErrorSendsAMessageOnTheTXLine(void)
{
  TX_Write_StubWithCallback(Stub_TXWrite);
  
  //test happy case 
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_OK_E;
  memset(TXWBytes, 0, 16);

  TEST_ASSERT_EQUAL_INT(EC_OK_E, iPOST_StateError());
  TEST_ASSERT_EQUAL_INT(4, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0xFF, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x0A, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0xA0, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
  
  //test TX failure
  TXWNumBytes = 0xFF;
  TXWReturnVal = EC_FAILED_E;
  memset(TXWBytes, 0, 16);

  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, iPOST_StateError());
  TEST_ASSERT_EQUAL_INT(0xFF, TXWNumBytes);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[0]);
  TEST_ASSERT_EQUAL_INT(0x00, TXWBytes[1]);
  TEST_ASSERT_EQUAL_INT(0x000, TXWBytes[2]);
  TEST_ASSERT_EQUAL_INT(TXWBytes[0]^TXWBytes[1]^TXWBytes[2], TXWBytes[3]);
}

void test_InitInitialiseTransmit(void)
{
  TX_Init_Expect();
  I2E_Init_Expect();
  iPOST_Init();
}




