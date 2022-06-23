/*****************************************************************************
 *   File        : Pressure_Part4.c
 *
 *   Description : Source for implementation of pressure measurements including
 * I2C comms
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

#include "Pressure_Part4.h"
#include "i2c.h"


#define SLAVE_I2C_PRESSURE_SENSOR_RETRY_MAX 500


/************************************************
*  @brief   Write data to the pressure sensors 
*  @param   Device - the 7 bit I2C address of slave 
*           DataLength - the number of data registers to read
*           DataAddress - the start address to read from
*           *DataBuffer - a pointer to the buffer to write the outgoing data
*                          
*  @return  Error Message: 0 OK; 1 for failed message
*
*************************************************/
bool_t PM_WritePressureSensors(uint8_t Device, uint8_t DataLength, uint8_t *DataBuffer)
{
  bool_t result = TRUE;

  uint32_t timeOut1 = 0;
  uint32_t timeOut2 = 0;

  I2C_MESSAGE_STATUS status;
  I2C_TRANSACTION_REQUEST_BLOCK GetDataTRB[1];

  // Build TRB for sending address
  I2C_MasterWriteTRBBuild(&GetDataTRB[0], DataBuffer, DataLength, Device);
  
  status = I2C_MESSAGE_PENDING;
  while( (status != I2C_MESSAGE_FAIL) &&
         (SLAVE_I2C_PRESSURE_SENSOR_RETRY_MAX >= timeOut1) &&
         (SLAVE_I2C_PRESSURE_SENSOR_RETRY_MAX >= timeOut2) )
  {
    // now send the transactions
    I2C_MasterTRBInsert(1, GetDataTRB, &status);

    // wait for the message to be sent or status has changed.
    timeOut1 = 0;
    while(status == I2C_MESSAGE_PENDING)
    {
      if (SLAVE_I2C_PRESSURE_SENSOR_RETRY_MAX <= timeOut1++)
      {
          result = FALSE;
          break;
      } 
    }
    // wait for the message to be sent or status has changed.
    if (status == I2C_MESSAGE_COMPLETE)
    {
      break;
    }
  }
    
  if(status == I2C_MESSAGE_FAIL)
  {
    result = FALSE;
  }

  return result;    
}


/************************************************
*  @brief   Get data from the pressure sensors 
*  @param   Device -      the 7 bit I2C address
*                         of slave  
*           DataLength -  the number of data
*                         registers to read
*           DataAddress - the start address to
*                         read from 
*           *DataBuffer - a pointer to the buffer
*                         to write the incoming data 
*                          
*  @return  TRUE for OK; FALSE for error
*
*************************************************/
bool_t PM_ReadPressureSensors(uint8_t Device, uint8_t DataLength, uint8_t DataAddress, uint8_t *DataBuffer)
{
  bool_t result = FALSE;
  uint8_t writeBuffer[3] = {0};
  uint32_t timeOut1 = 0;
  uint32_t timeOut2 = 0;

  I2C_MESSAGE_STATUS status;
  I2C_TRANSACTION_REQUEST_BLOCK GetDataTRB[2];

  writeBuffer[0] = (uint8_t) (NEXT_VAR_READ | DataAddress);

  // Build TRB for sending address
  I2C_MasterWriteTRBBuild(&GetDataTRB[0], writeBuffer, 1, Device);
  I2C_MasterReadTRBBuild(&GetDataTRB[1], DataBuffer, DataLength, Device);

  status = I2C_MESSAGE_PENDING;
  while( (status != I2C_MESSAGE_FAIL) &&
         (SLAVE_I2C_PRESSURE_SENSOR_RETRY_MAX >= timeOut1) &&
         (SLAVE_I2C_PRESSURE_SENSOR_RETRY_MAX >= timeOut2) )
  {
    // now send the transactions
    I2C_MasterTRBInsert(2, GetDataTRB, &status);
    // wait for the message to be sent or status has changed.
    timeOut1 = 0;
    while(status == I2C_MESSAGE_PENDING)
    {
      if (SLAVE_I2C_PRESSURE_SENSOR_RETRY_MAX <= timeOut1++ )
      {
          result = FALSE;
          break;
      }
    }

    // wait for the message to be sent or status has changed.
    if (status == I2C_MESSAGE_COMPLETE)
    {
      result = TRUE;
      break;
    }
    
    timeOut2++;
  }

  if(status == I2C_MESSAGE_FAIL)
  {
    result = FALSE;
  }

  return result;    
}





