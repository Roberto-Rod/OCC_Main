/*****************************************************************************
 *   File        : Transmit.c
 *
 *   Description : Source Code to transmit data over the serial port (EUSART). TX only.
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

#include "Transmit.h"
#include "eusart.h"
#include "Assert.h"

/****************************************************************************
Function Name  :  TX_Init

Parameters     :  None

Return Value   :  EC_OK_E or error code

Description    :  Initialise the TX serial port transmission (abstraction function)
*****************************************************************************/
void TX_Init(void)
{
  EUSART_Initialize();
}

/****************************************************************************
Function Name  :  TX_Write

Parameters     :  data     : pointer to data to write to the TX pin
                  numBytes : number of bytes to write to the TX pin

Return Value   :  EC_OK_E or error code

Description    :  Writes stuff out the TX serial port
*****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'data' in left argument to operator '['. */
ErrorCode_t TX_Write(const uint8_t *data, uint8_t numBytes)
{
  ASSERT(data != NULL);
  ASSERT(numBytes > 0);

  for (uint8_t loopVar = 0; loopVar < numBytes; loopVar++)
  {
    EUSART_Write(data[loopVar]);
  }

  return EC_OK_E; //dummy function just for compilation purposes
}
