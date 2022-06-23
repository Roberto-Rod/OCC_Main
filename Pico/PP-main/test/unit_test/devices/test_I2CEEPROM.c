/*****************************************************************************
 *   File        : test_I2CEEPROM.c
 *
 *   Description: Source Code for test I2C EEPROM.
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

#include <xc.h>
#include "unity.h"
#include <limits.h>
#include "I2CEEPROM.h"
#include "Mocki2c.h"
#include <stdio.h>




//global variables
I2C_MESSAGE_STATUS insertStatus = I2C_MESSAGE_COMPLETE;
uint8_t doChecks = 0;
uint8_t expectedCount = 2;




// Stub for getting a Vacuum
static void
Stub_insertTRB(uint8_t count, I2C_TRANSACTION_REQUEST_BLOCK *ptrb_list, I2C_MESSAGE_STATUS *pflag, int NumCall)
{
  *pflag = insertStatus;
  if (doChecks)
  {
    TEST_ASSERT_EQUAL_INT(expectedCount, count);
  }
}

                    

void setUp(void)
{
}

void tearDown(void)
{}

// Check the Init does nothing currently
void test_InitJustCallsTheLowerLevelInit(void)
{
  I2C_Initialize_Expect();
  I2E_Init();
}

// The dummy Read does range check for NULL pointer and zero bytes to send.
void test_ReadDoesRangeChecking(void)
{
  ErrorCode_t result = EC_OK_E;
  uint8_t      data[4] = {1, 4, 9, 16};

  I2C_MasterWriteTRBBuild_Ignore();
  I2C_MasterReadTRBBuild_Ignore();
  I2C_MasterTRBInsert_StubWithCallback(Stub_insertTRB);
  insertStatus = I2C_MESSAGE_COMPLETE;

  //checks for Null Address
  result = I2E_Read(0, NULL, 4);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
  
  //checks for zero data to be read
  result = I2E_Read(0, data, 0);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
  
  //checks First byte to be read is within range
  result = I2E_Read(I2E_MAX_ADDR, data, 1);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);

  //checks last byte to be read is within range
  result = I2E_Read(I2E_MAX_ADDR-1, data, 1);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);

  //check that we cant read over a 256 page boundary
  result = I2E_Read(250, data, 7);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
 
  //passes reading at the start of range
  result = I2E_Read(0, data, 4);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);

  //passes reading at the end of range
  result = I2E_Read(I2E_MAX_ADDR-5, data, 4);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
}

// The Read stuff
void test_ReadHappyCase(void)
{
  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;
  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t      data[4] = {1, 4, 9, 16};
  uint8_t addrData[2] = {0, 3};
  
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 2, 0x50);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();

  I2C_MasterReadTRBBuild_Expect(NULL, data, 4, 0x50);
  I2C_MasterReadTRBBuild_IgnoreArg_ptrb();

  I2C_MasterTRBInsert_Expect(2, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);

  result = I2E_Read(3, data, 4);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
 }

// The Read stuff single retry passes
void test_ReadHappyRetry(void)
{
  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;
  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t data[5] = {1, 4, 9, 16, 25};
  uint8_t addrData[2] = {0, 17};
  
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 2, 0x50);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();

  I2C_MasterReadTRBBuild_Expect(NULL, data, 5, 0x50);
  I2C_MasterReadTRBBuild_IgnoreArg_ptrb();

  I2C_MasterTRBInsert_Expect(2, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal1);

  I2C_MasterTRBInsert_Expect(2, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal2);

  result = I2E_Read(17, data, 5);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
}

// The Read stuff single retry fails
void test_ReadRetryFailure(void)
{
  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;
  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_ADDRESS_NO_ACK;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t data[6] = {1, 4, 9, 16, 25, 36};
  uint8_t addrData[2] = {1, 4};
  
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 2, 0x50);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();

  I2C_MasterReadTRBBuild_Expect(NULL, data, 6, 0x50);
  I2C_MasterReadTRBBuild_IgnoreArg_ptrb();

  I2C_MasterTRBInsert_Expect(2, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal1);

  I2C_MasterTRBInsert_Expect(2, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal2);

  result = I2E_Read(260, data, 6);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, result);
}

// The write does range check for NULL pointer and zero bytes to send.
void test_WriteDoesRangeChecking(void)
{
  ErrorCode_t result = EC_OK_E;
  uint8_t      data[4] = {1, 4, 9, 16};

  I2C_MasterWriteTRBBuild_Ignore();
  I2C_MasterReadTRBBuild_Ignore();
  I2C_MasterTRBInsert_StubWithCallback(Stub_insertTRB);
  insertStatus = I2C_MESSAGE_COMPLETE;

  //checks for Null Address
  result = I2E_Write(0, NULL, 4);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
  
  //checks for zero data to be read
  result = I2E_Write(0, data, 0);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
  
  //checks First byte to be read is within range
  result = I2E_Write(I2E_MAX_ADDR, data, 1);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);

  //checks last byte to be read is within range
  result = I2E_Write(I2E_MAX_ADDR-1, data, 1);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);

  //check that we cant write over a 256 page boundary
  result = I2E_Write(250, data, 7);
  TEST_ASSERT_EQUAL_INT(EC_INVALID_INPUT_PARAMETER_E, result);
 
  //passes reading at the start of range
  result = I2E_Write(0, data, 4);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);

  //passes reading at the end of range
  result = I2E_Write(I2E_MAX_ADDR-5, data, 4);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
}

// The Write stuff
void test_WriteHappyCase(void)
{
  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;
  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t      data[4] = {1, 4, 9, 16};
  uint8_t addrData[2] = {0, 3};
  uint8_t EEPROMBusAddr = 0x50;

  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 6, EEPROMBusAddr);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();

  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal);

  result = I2E_Write(3, data, 4);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
 }

// The Write stuff single retry passes
void test_WriteHappyRetry(void)
{
  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;
  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t data[5] = {1, 4, 9, 16, 25};
  uint8_t addrData[2] = {1, 1};
  
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 7, 0x50);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();

  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal1);

  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal2);

  result = I2E_Write(257, data, 5);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
}

// The Write stuff single retry fails
void test_WriteRetryFailure(void)
{
  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;
  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_ADDRESS_NO_ACK;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t data[6] = {1, 4, 9, 16, 25, 36};
  uint8_t addrData[2] = {0, 7};
  
  I2C_MasterWriteTRBBuild_ExpectWithArray(NULL, 0, addrData, 2, 8, 0x50);
  I2C_MasterWriteTRBBuild_IgnoreArg_ptrb();

  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal1);

  I2C_MasterTRBInsert_Expect(1, NULL, NULL);
  I2C_MasterTRBInsert_IgnoreArg_ptrb_list();
  I2C_MasterTRBInsert_IgnoreArg_pflag();
  I2C_MasterTRBInsert_ReturnThruPtr_pflag(&ptrVal2);

  result = I2E_Write(7, data, 6);
  TEST_ASSERT_EQUAL_INT(EC_FAILED_E, result);
}

