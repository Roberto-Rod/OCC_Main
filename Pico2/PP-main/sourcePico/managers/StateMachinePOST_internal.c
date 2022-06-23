/********************************************************************************
* File : StateMachinePOST_internal.c
*
* Description : Implements the POST state for the device state machine
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#include "StateMachinePOST.h"
#include "StateMachinePOST_internal.h"
#include "pic16lf1509.h"
#include "pin_manager.h"
#include "PowerControl.h"
#include "Pressure_Part1.h"
#include "adc.h"
#include "Timer.h"

static POSTSubState_t subStateNum = POST_STATE_INITIAL;
static uint8_t prevRA = 0x02;  //entry into test mode TP13 = RA0 = Ground
                               //                     TP14 = RA1 = 3.0V

/****************************************************************************
Function Name  :  iPOST_doPOST

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  Checks the pins to see if we should go into POST mode or not
*****************************************************************************/
uint8_t  iPOST_doPOST(void)
{
  uint8_t returnVal = 0;
  
  if (subStateNum == POST_STATE_INITIAL)
  {
    subStateNum = POST_STATE_MAX;
    if ((0 == IO_RA0_GetValue()) && 
        (1 == IO_RA1_GetValue()))
    {
      subStateNum = POST_STATE_00;
      prevRA = 0x02; //RA1 set, RA0 cleared.
      returnVal = 1;
      IO_RC2_SetLow();
      IO_RC3_SetLow();
      IO_RC4_SetLow();
      IO_RC5_SetLow();
      RC6_SetLow();  //NCO1
      IO_RC7_SetLow();
      IO_RB5_SetLow();
      MP_SetReferenceVoltageBoost(VBOOST_REF_0V);    
    }
  }
  if(POST_STATE_MAX != subStateNum)
  {
    returnVal = 1  ;
  }
  
  return(returnVal);
}

/****************************************************************************
Function Name  :  iPOST_getSubStateNum

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  Returns the sub state
*****************************************************************************/
POSTSubState_t iPOST_getSubStateNum(void)
{
  return subStateNum;
}

/****************************************************************************
Function Name  :  iPOST_updateSubStateNum

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  Gets the latest value of the RA port, compares it to the
                  stored value. If RA0 and RA1 have both toggled then the state
                  number is increased up to the threshold
*****************************************************************************/
void iPOST_updateSubStateNum(void)
{
  uint8_t  currentRA = (uint8_t) (IO_RA0_GetValue() + (IO_RA1_GetValue() << 1)); 
  
  if (3 == ((currentRA ^ prevRA) & 0x03))
  {
    prevRA = currentRA;
    if (POST_STATE_MAX <= ++subStateNum)
    {
      subStateNum = POST_STATE_00;
    }
  }
}

/****************************************************************************
Function Name  :  iPOST_setSubStateNum

Parameters     :  newStateNum - value to set the sub state number to

Return Value   :  EC_OK_E or error code

Description    :  Sets the internal sub state variable to the desired value
*****************************************************************************/
void iPOST_setSubStateNum(POSTSubState_t  newStateNum)
{
  subStateNum = newStateNum;
}

/****************************************************************************
Function Name  :  iPOST_State00

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Only Set RC4 (uC_LAT)
                  DAC    : 0.0V
                  ADC    : None
                  I2C    : None
                  EUSART : None
*****************************************************************************/
ErrorCode_t iPOST_State00(void)
{
  ErrorCode_t result = EC_OK_E;
  
  IO_RC4_SetHigh();
  
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State01

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Clear All
                  DAC    : 1.7V
                  ADC    : None
                  I2C    : None
                  EUSART : None
*****************************************************************************/
ErrorCode_t iPOST_State01(void)
{
  ErrorCode_t result;
  uint8_t  message[4];
  
  MP_SetReferenceVoltageBoost(VBOOST_REF_27V);
  
  uint16_t ADCResult = ADC_GetConversion(Boost_Voltage);

  //send message on the TX
  message[0] = 1;
  message[1] = (uint8_t) (ADCResult & 0x00FFU);
  message[2] = (uint8_t) (ADCResult >> 8);
  message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
  result = TX_Write(message, 4);
  
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State02

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Only Set RC7 (green LED)
                  DAC    : 0.0V
                  ADC    : None
                  I2C    : None
                  EUSART : None
*****************************************************************************/
ErrorCode_t iPOST_State02(void)
{
  ErrorCode_t result = EC_OK_E;
  
  MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
  IO_RC7_SetHigh();
  
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State03

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Only set RC5 (Orange LED)
                  DAC    : 0.0V
                  ADC    : None
                  I2C    : None
                  EUSART : None
*****************************************************************************/
ErrorCode_t iPOST_State03(void)
{
  ErrorCode_t result = EC_OK_E;
  IO_RC7_SetLow();
  IO_RC5_SetHigh();
  
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State04

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Only set RC2 (uC_SensorSupply)
                  DAC    : 0.0V
                  ADC    : None
                  I2C    : Read from internal pressure sensor
                  EUSART : Tx internal pressure value
*****************************************************************************/
ErrorCode_t iPOST_State04(void)
{
  ErrorCode_t result;
  uint16_t    currentVacuum;
  uint16_t    internalPressure;
  uint16_t    externalPressure;
  IO_RC5_SetLow();
  IO_RC2_SetHigh();
  uint8_t  message[4];
  
  //get reading from the external pressure sensor
  result = GetVacuum(&internalPressure, &externalPressure, &currentVacuum);
  
  if(EC_OK_E == result)
  {
    //send message on the TX
    message[0] = 4;
    message[1] = (uint8_t) (externalPressure & 0x00FFU);
    message[2] = (uint8_t) (externalPressure >> 8);
    message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
    result = TX_Write(message, 4);
  }  
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State05

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Clear All
                  DAC    : 0.0V
                  ADC    : None
                  I2C    : Read from external pressure sensor
                  EUSART : Tx external pressure value
*****************************************************************************/
ErrorCode_t iPOST_State05(void)
{
  ErrorCode_t result;
  uint16_t    currentVacuum;
  uint16_t    internalPressure;
  uint16_t    externalPressure;
  
  uint8_t  message[4];
 
  IO_RC2_SetLow();

  //get reading from the internal pressure sensor
  result = GetVacuum(&internalPressure, &externalPressure, &currentVacuum);
  
  //send message on the TX
  if(EC_OK_E == result)
  {
    message[0] = 5;
    message[1] = (uint8_t) (internalPressure & 0x00FFU);
    message[2] = (uint8_t) (internalPressure >> 8);
    message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
    result = TX_Write(message, 4);
  }
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State06

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Clear All
                  DAC    : 0.0V
                  ADC    : None
                  I2C    : Write to EEPROM and Read Back
                  EUSART : Tx pass/fail if read back data matches written data
*****************************************************************************/
ErrorCode_t iPOST_State06(void)
{
  ErrorCode_t readResult  = EC_OK_E;
  ErrorCode_t writeResult;
  ErrorCode_t TXResult;
  uint8_t  writtenData[2] = {0xAA, 0x55};
  uint8_t  resetData[2] = {0xFF, 0xFF};
  uint8_t  readData[2] = {0x00, 0x00};
  uint8_t  message[4];
  uint8_t  tempData; // temporary result
  const uint32_t eepromAddress = 0; // 0x10000 64K

  MP_EnableExternalPeripheralsSupply();
  /*lint -e{522} Suppress: Highest String ?PM_Delay? lacks side-effects.*/
  PM_Delay((uint32_t) 8);

  //Memory_Write
  writeResult = I2E_Write(eepromAddress, writtenData, 2);
    
  //Memory_Read.
  // Keep retrying because there is a write delay flashing EEPROM from previous write operation.
  // See http://www.mouser.com/ds/2/389/m24m02-dr-954993.pdf
  /*lint -e{522} Suppress: Highest String ?PM_Delay? lacks side-effects.*/
  PM_Delay((uint32_t) 10);
  uint8_t delayAfterWriteCount = 5;
  while(delayAfterWriteCount-- > 0)
  {
    readResult = I2E_Read(eepromAddress, readData, 2);
    if (readResult == EC_OK_E) {break;}
  }

  //send message on the TX
  message[0] = 6;
  
  // The following line, 
  // message[1] = (EC_OK_E == writeResult) + ((EC_OK_E == readResult) << 1);
  // has been re-written below to avoid the lint Warning 514: Unusual use of a Boolean expression.
  // It also saves program memory.
  tempData = 0x00U; // reset all bits
  tempData = tempData; // avoids Compiler Warning (1090) "variable is not used".
  if (writeResult == EC_OK_E)
  {
    tempData |= 0x01U; // set bit 0
  }
  if (readResult == EC_OK_E)
  {
    tempData |= 0x02U; // set bit 1
  }
  // result is in bits 0-1: bit 0=writeResult, bit1=readResult
  message[1] = tempData;
  
  // The following line, 
  // message[2] = (uint8_t) ((readData[0] == writtenData[0]) + ((readData[1] == writtenData[1]) << 1));
  // has been re-written below to avoid the lint Warning 514: Unusual use of a Boolean expression.
  // It also saves program memory.
  tempData = 0x00U; // reset all bits
  if (readData [0] == writtenData [0])
  {
    tempData |= 0x01U; // set bit 0
  }
  if (readData [1] == writtenData [1])
  {
    tempData |= 0x02U; // set bit 1
  }
  // result is in bits 0-1: bit 0=Data Byte 0 Result, bit1=Data Byte 1 Result 
  message[2] = tempData;
  
  message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
  
  TXResult = TX_Write(message, 4);
  
  // Allow the longest write time of 10ms
  I2E_Write(eepromAddress, resetData, 2);
  /*lint -e{522} Suppress: Highest String ?PM_Delay? lacks side-effects.*/
  PM_Delay((uint32_t) 10);

  MP_DisableExternalPeripheralsSupply();

  return TXResult;
}

/****************************************************************************
Function Name  :  iPOST_State07

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Toggle RC6 (PWM-1) at 10Hz - 5Hz 50% duty cycle,
                           clear RC3 (PWM-2)
                  DAC    : 1.7V
                  ADC    : Read AN4/RC0
                  I2C    : None
                  EUSART : Tx the values read by the ADC
*****************************************************************************/
ErrorCode_t iPOST_State07(void)
{
  ErrorCode_t result;
  uint8_t  message[4];
  
  NCO1CON = 0x00;
  IO_RC2_SetHigh();
  
  RC6_Toggle();  //NCO1: assume POST is running at 100ms interval
  IO_RC3_SetLow();
  MP_SetReferenceVoltageBoost(VBOOST_REF_27V);
    
  uint16_t ADCResult = ADC_GetConversion(HBridge_Current);

  //send message on the TX
  message[0] = 7;
  message[1] = (uint8_t) (ADCResult & 0x00FFU);
  message[2] = (uint8_t) (ADCResult >> 8);
  message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
  result = TX_Write(message, 4);
   
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State08

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Toggle RC6 (PWM-1) at 10Hz - 5Hz 50% duty cycle,
*                          set RC3 (PWM-2)
                  DAC    : 1.7V
                  ADC    : Read AN4/RC0
                  I2C    : None
                  EUSART : Tx the values read by the ADC
*****************************************************************************/
ErrorCode_t iPOST_State08(void)
{
  ErrorCode_t result;
  uint8_t  message[4];
  
  NCO1CON = 0x00;
  IO_RC2_SetHigh();
  
  RC6_Toggle();  //NCO1: assume POST is running at 100ms interval
  IO_RC3_SetHigh();
  MP_SetReferenceVoltageBoost(VBOOST_REF_27V);
    
  uint16_t ADCResult = ADC_GetConversion(HBridge_Current);

  //send message on the TX
  message[0] = 8;
  message[1] = (uint8_t) (ADCResult & 0x00FFU);
  message[2] = (uint8_t) (ADCResult >> 8);
  message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
  result = TX_Write(message, 4);
 
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State09

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Read value of RA5
                  DAC    : None
                  ADC    : None
                  I2C    : None
                  EUSART : Tx Value of RA5
*****************************************************************************/
ErrorCode_t iPOST_State09(void)
{
  ErrorCode_t result;
  uint8_t  message[4];

  MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
  IO_RC3_SetLow();
  
  uint8_t RA5Result = IO_RA5_GetValue();
  
  //send message on the TX
  message[0] = 9;
  message[1] = RA5Result;
  message[2] = 0;
  message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
  result = TX_Write(message, 4);
     
  return result;
}

/****************************************************************************
Function Name  :  iPOST_State10

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Set RB5 pin (OSC_Supply)
                  DAC    : None
                  ADC    : Take
                  I2C    : None
                  EUSART : None
*****************************************************************************/
ErrorCode_t iPOST_State10(void)
{
  ErrorCode_t result = EC_OK_E;
  IO_RB5_SetHigh();

  /* Note this is the last state. We should not do any Tx here
   */
  return result;
}

/****************************************************************************
Function Name  :  iPOST_StateError

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  GPIO   : Set RB5 pin (OSC_Supply)
                  DAC    : None
                  ADC    : Take
                  I2C    : None
                  EUSART : None
*****************************************************************************/
ErrorCode_t iPOST_StateError(void)
{
 ErrorCode_t result;
 uint8_t  message[4];
  
  //send message on the TX
  message[0] = 0xFF;
  message[1] = 0x0A;
  message[2] = 0xA0;
  message[3] = (uint8_t) (message[0] ^ message[1] ^ message[2]);
  result = TX_Write(message, 4);
     
  return result;
}

/****************************************************************************
Function Name  :  iPOST_Init

Parameters     :  None

Return Value   :  None

Description    :  Initialises the UART transmit and I2C EEPROM
 
*****************************************************************************/
void iPOST_Init(void)
{
  TX_Init();
  I2E_Init();
}
