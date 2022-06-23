/*****************************************************************************
 *   File        : Dbg.c
 *
 *   Description : Debugging Utilities module.
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

#include "Dbg.h"

/************************************************
*  @brief   
*  @param   None
*  @return  EC_OK_E or error code 
*           (currently always EC_OK_E)
*
*************************************************/

#define DBG_RECORD_WAIT_COUNT (10)
#define DBG_RECORD_SIZE (50)

uint16_t DbgBuffer_1[DBG_RECORD_SIZE];
uint8_t DbgIndex = 0;

void Dbg_RecordPwmFrequency(const uint16_t Frequency)
{
  if ((DBG_RECORD_WAIT_COUNT <= DbgIndex) && ((DBG_RECORD_WAIT_COUNT + DBG_RECORD_SIZE) > DbgIndex))
  {
    DbgBuffer_1[DbgIndex - DBG_RECORD_WAIT_COUNT] = Frequency;
  }
  
  if((DBG_RECORD_WAIT_COUNT + DBG_RECORD_SIZE) > DbgIndex)
  {
    DbgIndex++;
  }
  else
  {
    DbgIndex = 0xFF;  
  } 
}

void Dbg_StartPwmFrequencyRecording(void)
{
  DbgIndex = 0;
}
