/*****************************************************************************
 *   File        : I2CEEPROM.c
 *
 *   Description : Source Code to read and write to the I2CEEPROM
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include <xc.h>
#include "device_config.h"
#include "I2CEEPROM.h"
#include "i2c.h"

#define ADDRESS_BYTE_SIZE   ((uint8_t) 2)     //first 2 bytes contains eeprom address to access
#define MAX_WRITE_DATA_SIZE ((uint8_t)16)    //limit max write size to 16 bytes
#define MAX_WRITE_BUFFER_SIZE   (MAX_WRITE_DATA_SIZE + ADDRESS_BYTE_SIZE)
#define I2E_WRITE_RETRIES (2)
#define PAGE_BOUNDARY_ADDRESS_BIT   ((uint32_t)0x10100)
#define LOOP_DELAY_US (100)
#define MAX_LOOP_RETRIES (100)

static ErrorCode_t transmitI2CData(I2C_TRANSACTION_REQUEST_BLOCK *transactionRequestBlock, const uint8_t blockCount);

static ErrorCode_t isAccessWithinPageBoundary(const uint32_t address, const uint8_t numBytes);

/****************************************************************************
Function Name  :  I2E_Init

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  Calls the i2c initialisation algorithm
*****************************************************************************/
void I2E_Init(void)
{
  I2C_Initialize();
}

/****************************************************************************
Function Name  :  I2E_Read

Parameters     :  address  : Address to read from
                  data     : pointer to data to read to the EEPROM
                  numBytes : number of bytes to read to the EEPROM

Return Value   :  EC_OK_E or error code

Description    :  Reads data from the specified address on the I2C EEPROM
*****************************************************************************/
ErrorCode_t I2E_Read(uint32_t address, uint8_t *data, uint8_t numBytes)
{
  uint8_t busAddr;
  uint8_t dataAddr[ADDRESS_BYTE_SIZE];
  ErrorCode_t retVal = EC_OK_E;
  I2C_TRANSACTION_REQUEST_BLOCK readTRB[2];

  //range checking
  if ((NULL == data) || ((address + numBytes) >= I2E_MAX_ADDR) || (0 == numBytes))
  {
    retVal = EC_INVALID_INPUT_PARAMETER_E;
  }

  //check that we stay on the same 256 byte page while we write
  if (EC_OK_E == retVal)
  {
    retVal = isAccessWithinPageBoundary(address, numBytes);
  }

  if (EC_OK_E == retVal)
  {

    busAddr = I2E_EEPROM_BUS_ADDR | ((uint8_t) (address >> 16)); //we've already range checked 
    //address so don't need to
    //mask the higher bits
    dataAddr[0] = (uint8_t) (address >> 8);
    dataAddr[1] = (uint8_t) (address);

    I2C_MasterWriteTRBBuild(&readTRB[0], dataAddr, ADDRESS_BYTE_SIZE, busAddr);
    I2C_MasterReadTRBBuild(&readTRB[1], data, numBytes, busAddr);

    retVal = transmitI2CData(readTRB, 2);
  }

  return (retVal);
}

/****************************************************************************
Function Name  :  I2E_Write

Parameters     :  address  : Address to read from
                  data     : pointer to data to write to the EEPROM
                  numBytes : number of bytes to write to the EEPROM

Return Value   :  EC_OK_E or error code

Description    :  Writes data to the specified address on the EEPROM
*****************************************************************************/
// The following line is Commented out to avoid PC-lint (750) issue. local macro 'SLAVE_I2C_GENERIC_RETRY_MAX' (Location) not referenced.
//#define SLAVE_I2C_GENERIC_RETRY_MAX     10

/*lint -e{613} Suppress: Possible use of null pointer 'data' in left argument to operator '['. */
ErrorCode_t I2E_Write(uint32_t address, const uint8_t *data, uint8_t numBytes)
{
  uint8_t busAddr;
  uint8_t i2cData[MAX_WRITE_BUFFER_SIZE];
  ErrorCode_t retVal = EC_OK_E;
  I2C_TRANSACTION_REQUEST_BLOCK transactionRequestBlock[2];

  //range checking
  if ((NULL == data) ||
      ((address + numBytes) >= I2E_MAX_ADDR) ||
      (0 == numBytes) ||
      numBytes > MAX_WRITE_DATA_SIZE)
  {
    retVal = EC_INVALID_INPUT_PARAMETER_E;
  }

  //check that we stay on the same 256 byte page while we write
  if (EC_OK_E == retVal)
  {
    retVal = isAccessWithinPageBoundary(address, numBytes);
  }

  if (EC_OK_E == retVal)
  {
    busAddr = I2E_EEPROM_BUS_ADDR | ((uint8_t) (address >> 16)); //we've already range checked
    //address so don't need to
    //mask the higher bits
    i2cData[0] = (uint8_t) (address >> 8);
    i2cData[1] = (uint8_t) (address);

    for (uint8_t i = 0; i < numBytes && i < MAX_WRITE_BUFFER_SIZE; i++)
    {
      
      // index defined by Constants is OK. Avoid PC-lint message
      /*lint -e{661, 662} Suppress: (662) Possible creation of out-of-bounds pointer (2 beyond end of data) by operator '['. */
      //                  Suppress: (661) Possible access of out-of-bounds pointer (2 beyond end of data) by operator '['. */
      i2cData[(uint8_t) (ADDRESS_BYTE_SIZE + i)] = data[i];
    }

    I2C_MasterWriteTRBBuild(&transactionRequestBlock[0], i2cData, (uint8_t) (ADDRESS_BYTE_SIZE + numBytes), busAddr);

    retVal = transmitI2CData(transactionRequestBlock, 1);
  }

  return (retVal);
}

static ErrorCode_t transmitI2CData(I2C_TRANSACTION_REQUEST_BLOCK *transactionRequestBlock, const uint8_t blockCount)
{
  uint8_t retryLeft = I2E_WRITE_RETRIES;
  I2C_MESSAGE_STATUS status = I2C_MESSAGE_FAIL;

  do
  {
    uint8_t loopCounter = 0;  
    // now send the transactions
    I2C_MasterTRBInsert(blockCount, transactionRequestBlock, &status);

    // wait for the message to be sent or status has changed.
    while ((I2C_MESSAGE_PENDING == status) && (loopCounter < MAX_LOOP_RETRIES))
    {
        __delay_us(LOOP_DELAY_US);
        loopCounter++;
    }

  } while ((--retryLeft > 0) && (status != I2C_MESSAGE_COMPLETE));

  return (status == I2C_MESSAGE_COMPLETE) ? EC_OK_E : EC_FAILED_E;
//  ErrorCode_t retVal = (status != I2C_MESSAGE_COMPLETE);
//  return retVal;
}

static ErrorCode_t isAccessWithinPageBoundary(const uint32_t address, const uint8_t numBytes)
{
  uint32_t lastAddressWritten = address + numBytes - 1;
  uint32_t pageBoundaryBitsChanged = (address ^ lastAddressWritten) & PAGE_BOUNDARY_ADDRESS_BIT;
  bool_t isWithinPage = (bool_t) (pageBoundaryBitsChanged == 0);

  return isWithinPage ? EC_OK_E : EC_INVALID_INPUT_PARAMETER_E;
}

