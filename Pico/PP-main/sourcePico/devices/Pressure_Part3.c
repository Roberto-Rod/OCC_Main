/*****************************************************************************
 *   File        : Pressure_Part3.c
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
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "Pressure_Part3.h"
#include "Pressure_Part4.h"
#include "Timer.h"
#include "i2c.h"

#define DEFAULT_PRESSURE_DIFFERENCE (0)

/****************************************************************************
Function Name  :  PM_InitSensors

Parameters     :  None

Return Value   :  EC_OK_E if the pressures sensors are initialised Ok, 
                  or errors otherwise.

Description    :  Initialise the internal and external pressure sensors and 
                  ensure they have booted up succesfully.
*****************************************************************************/
ErrorCode_t PM_InitSensors(void)
{
  ErrorCode_t result = EC_OK_E;
  uint8_t DataBuffer[LEN_PRES_INIT + 1] = {0};
  uint8_t *pDataBuffer;

  //memset(DataBuffer, '\0', sizeof(DataBuffer));
  DataBuffer[0] = NEXT_VAR_READ | I2C_ADD_CTRL_REG1;
  DataBuffer[1] = 0x84;   //CTRL_REG1
  DataBuffer[2] = SENSOR_BOOT;   //CTRL_REG2
  pDataBuffer = &DataBuffer[0];

  // Send Init command to external pressure sensor
  if (FALSE == PM_WritePressureSensors(I2C_ADD_EXT_SENSOR, LEN_PRES_INIT + 1, pDataBuffer))
  {
    result = EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E;
  }
  // Send Init command to internal pressure sensors
  else if (FALSE == PM_WritePressureSensors(I2C_ADD_INT_SENSOR, LEN_PRES_INIT + 1, pDataBuffer))
  {
    result = EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E;
  }
  // Check Internal and External pressure sensors are initialised
  // Note. These are the same operations as PM_GetPressureSensorBootOk
  //       but that API is not used here to allow unit testing this code
  else
  {
    bool_t bootup_OK_ext = FALSE;
    bool_t bootup_OK_int = FALSE;
    uint32_t TimeOut = 0;
    while ((I2C_TIMEOUT_MS > TimeOut) && ((TRUE != bootup_OK_ext) || (TRUE != bootup_OK_int)))
    {
      // Internal pressure sensor boot-up OK (i.e. SENSOR_BOOT bit cleared)
      //memset(DataBuffer, '\0', sizeof(DataBuffer));
      if (TRUE == PM_ReadPressureSensors(I2C_ADD_EXT_SENSOR, LEN_PRES_START, I2C_ADD_CTRL_REG2, pDataBuffer))
      {
        bootup_OK_ext = (bool_t) ((!(DataBuffer[0] & SENSOR_BOOT)) ? TRUE:FALSE);
      }
      // External pressure sensor boot-up OK
      //memset(DataBuffer, '\0', sizeof(DataBuffer));
      if (TRUE == PM_ReadPressureSensors(I2C_ADD_INT_SENSOR, LEN_PRES_START, I2C_ADD_CTRL_REG2, pDataBuffer))
      {
        bootup_OK_int = (bool_t) ((!(DataBuffer[0] & SENSOR_BOOT)) ? TRUE:FALSE);
      }
      // Retry count with delay
      TimeOut++;
      PM_Delay((uint32_t) 1);
    }
    // Check both sensors booted up OK
    if (FALSE == bootup_OK_ext)
    {
      result = EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E;
    }
    else if (FALSE == bootup_OK_int)
    {
      result = EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E;
    }
  }
  
  return result;
}

/****************************************************************************
Function Name  :  PM_StartSensors

Parameters     :  None

Return Value   :  EC_OK_E if the pressures sensors started Ok, 
                  or errors otherwise.

Description    :  Start the internal and external pressure sensors.
*****************************************************************************/
ErrorCode_t PM_StartSensors(void)
{
  ErrorCode_t result = EC_OK_E;
  uint8_t DataBuffer[4] = {0};
  uint8_t *pDataBuffer;

  DataBuffer[0] = NEXT_VAR_READ | I2C_ADD_CTRL_REG1;
  DataBuffer[1] = 0x84;   //CTRL_REG1
  DataBuffer[2] = PRESS_ONE_SHOT;   //CTRL_REG2

  pDataBuffer = &DataBuffer[0];

  if(TRUE != PM_WritePressureSensors(I2C_ADD_EXT_SENSOR, 3, pDataBuffer))
  {
    result = EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E;
  }
  else if(TRUE != PM_WritePressureSensors(I2C_ADD_INT_SENSOR, 3, pDataBuffer))
  {
    result = EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E;
  }
  
  return result;
}

/****************************************************************************
Function Name  :  isPressureSensorReady

Parameters     :  PressureSensor_t Sensor - which of the two sensors to check

Return Value   :  TRUE if data is ready
                  FALSE if data not ready

Description    :  Check if pressure data is ready.
*****************************************************************************/
bool_t isPressureSensorReady(PressureSensor_t Sensor)
{
  bool_t result = TRUE;
  uint8_t device = 0;
  uint8_t dataBuffer[9];
  uint8_t *pDataBuffer = NULL;

  // initialize dataBuffer
  for (uint8_t i = 0; i < sizeof (dataBuffer); i++)
  {
    dataBuffer[i] = '\0';
  }

  // Check input parameters
  if (PS_EXTERNAL_PRESSURE_E == Sensor)
  {
    device = I2C_ADD_EXT_SENSOR;
  }
  else if (PS_INTERNAL_PRESSURE_E == Sensor)
  {
    device = I2C_ADD_INT_SENSOR;
  }
  else
  {
    result = FALSE;
  }
  
  // Get the READY bit from the pressure sensor
  if (TRUE == result)
  {
    pDataBuffer = &dataBuffer[0];

    result = PM_ReadPressureSensors(device,
                                    0x08, //LEN_PRES_STAT,
                                    I2C_ADD_CTRL_REG1, //I2C_ADD_STATUS, 
                                    pDataBuffer);
  }
  
  // CHeck the READY bit status
  if (TRUE == result)
  {
      result = ((bool_t) (((dataBuffer[7] & PRESS_DATA_READY) == PRESS_DATA_READY) ? TRUE:FALSE));
  }

  return result;
}

/****************************************************************************
Function Name  :  PM_GetPressureSensorBootOk

Parameters     :  uint8_t Sensor - which of the two sensors to check

Return Value   :  TRUE if boot still in progress
                  FALSE if boot complete

Description    :  Check boot status during power-up.
*****************************************************************************/
bool_t PM_GetPressureSensorBootOk(uint8_t Sensor)
{
  bool_t result = FALSE;
  uint8_t DataBuffer[LEN_PRES_STAT + 1];
  uint8_t *pDataBuffer;

  pDataBuffer = &DataBuffer[0];

  if(TRUE == PM_ReadPressureSensors(Sensor,
                                    LEN_PRES_START,
                                    I2C_ADD_CTRL_REG2, 
                                    pDataBuffer))
  {
    result = ((bool_t) (((DataBuffer[0] & SENSOR_BOOT) == SENSOR_BOOT) ? TRUE:FALSE));
  }
  
  return result;
}

/****************************************************************************
Function Name  :  PM_GetPressure

Parameters     :  PressureSensor_t Sensor - which of the two sensors to check
                  uint16_t pPressure - pointer to sensor pressure
                  uint16_t* pTemperature - pointer to sensor temperature

Return Value   :  EC_OK_E if the pressure sensor was read Ok, 
                  or errors otherwise.

Description    :  Get pressure and temperature values for the desired pressure sensor (mBar) .
*****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'pPressure' and 'pTemperature' in argument to operator 'unary *'. */
ErrorCode_t PM_GetPressure(PressureSensor_t Sensor, uint16_t* pPressure, uint16_t* pTemperature)
{
  ErrorCode_t result = EC_OK_E;
  
  uint8_t DataBuffer[LEN_PRES_DATA + 1];
  uint8_t *pDataBuffer;
  uint8_t device = 0;
                                                                     
  if ( (NULL == pPressure) || (NULL == pTemperature) || ((PS_EXTERNAL_PRESSURE_E != Sensor) && (PS_INTERNAL_PRESSURE_E != Sensor)))
  {
    result = EC_INVALID_INPUT_PARAMETER_E;
  }
  
  // Get the raw value from sensor and turn it into a pressure value
  if (EC_OK_E == result)
  {
    // Select correct pressure sensor type
    if (PS_EXTERNAL_PRESSURE_E == Sensor)
    {
      device = I2C_ADD_EXT_SENSOR;
    }
    else
    {
      device = I2C_ADD_INT_SENSOR;
    }

    pDataBuffer = &DataBuffer[0];

    // Get pressure reading
    if(TRUE == PM_ReadPressureSensors(device, 
                                      LEN_PRES_DATA,
                                      I2C_ADD_PRESS_OUT_XL, 
                                      pDataBuffer))
    {
      // By reading at the correct offset, this equates to the shift of 12 bits
      *pPressure = ((((uint16_t)DataBuffer[2]) << 4) |
                    (((uint16_t)DataBuffer[1]) >> 4));
      // Pass the temperature back 
      *pTemperature = ((((uint16_t)DataBuffer[4]) << 8) |
                    ((uint16_t)DataBuffer[3]));
    }
    else
    {
      if (PS_EXTERNAL_PRESSURE_E == Sensor)
      {
        result = EC_EXT_PRESSURE_SENSOR_READ_FAILED_E;
      }
      else
      {
        result = EC_INT_PRESSURE_SENSOR_READ_FAILED_E;
      }
    }
  }
  
  return result;
}

/****************************************************************************
Function Name  :  PM_CalcDiffPressure

Parameters     :  uint16_t PresExt - external pressure in mBar
                  uint16_t PresInt - internal pressure in mBar
                  uint16_t* pDiff - pointer to the pressure difference in mBar

Return Value   :  EC_OK_E if the pressure difference was calculated Ok, 
                  or errors otherwise.

Description    :  Given an internal and external pressure, calculate the difference in mBar.
*****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'pDiff' in argument to operator 'unary *'. */
ErrorCode_t PM_CalcDiffPressure(uint16_t PresExt, uint16_t PresInt, uint16_t* pDiff)
{
  ErrorCode_t result = EC_OK_E;

  if (NULL == pDiff)
  {
    result = EC_INVALID_INPUT_PARAMETER_E;
  }
  
  if (EC_OK_E == result)
  {
    if((0 == PresInt) || (0 == PresExt))
    {
      result = EC_PRESSURE_DIFF_FAULT_CODE_E;
    }
    else if(PresInt <= PresExt)
    {
      *pDiff = PresExt - PresInt;
    }
    else
    {
      // At start up when internal and external pressures are the same
      // the sensors could have a small error margin leading the Internal > External
      // In this case overrule the readings, provide the smallest possible difference
      // (i.e. 0 mBar) and result = EC_OK_E so that the device needs to pump up.
      *pDiff = DEFAULT_PRESSURE_DIFFERENCE;
    }
  }
  
  return result;    
}

