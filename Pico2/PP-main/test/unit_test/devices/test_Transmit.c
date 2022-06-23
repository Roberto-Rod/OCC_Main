/*****************************************************************************
 *   File        : test_Transmit.c
 *
 *   Description: Source Code for test of transmit data over the serial port (EUSART). TX only
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
#include <limits.h>
#include "Transmit.h"
#include "Mockeusart.h"
#include "Assert.h"

void setUp(void)
{
}

void tearDown(void)
{}


// Tx Init calls eusart init
void test_InitDoesNothing(void)
{
  EUSART_Initialize_Expect();
  TX_Init();
}

// The dummy Write does range check for NULL pointer and zero bytes to send.
void test_TransmitDoesRangeCheckingOnDataPointer(void)
{
  uint8_t data[4] = {1, 4, 9, 16};
  ErrorCode_t result = TX_Write(NULL, 4);
  TEST_FAIL_MESSAGE("Assert should be called prior to this function");
}

void test_TransmitDoesRangeCheckingonDataSize(void)
{
  uint8_t data[4] = {1, 4, 9, 16};
  ErrorCode_t result = TX_Write(data, 0);
  TEST_FAIL_MESSAGE("Assert should be called prior to this function");
}


// The calls the EUSART write command repeatedly once for each character
void test_TransmitCallsEUSARTWriteForEachCharacter(void)
{
  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;
  uint8_t data[4] = {1, 4, 9, 16};

  EUSART_Write_Expect(1);
  EUSART_Write_Expect(4);
  EUSART_Write_Expect(9);
  EUSART_Write_Expect(16);
  result = TX_Write(data, 4);
  TEST_ASSERT_EQUAL_INT(EC_OK_E, result);
}
