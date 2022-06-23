/********************************************************************************
* File : DutyCycle.c
*
* Description: Source Code to calculate the duty cycle between Pump On and Off during
*              Therapy Delivery
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

#include "DutyCycle.h"
#include "limits.h"
#include "PerformanceLogger.h"

static uint32_t DutyCycleHistory = 0;  // Bits indicate if pump was on/off each second for last 32 seconds
                                       // 1 = on, least significant bit is the latest
static uint8_t LeakDutyCycle = 0;      // Calculated total on for last 30 second, > 15 indicates failure 
static uint8_t TargetVaccumOffsetDutyCycle = 0;  // Calculated total on for last 9 seconds, indicates
                                                 // Gives efficency if not on 

/****************************************************************************
Function Name  :  DCHistoryReset

Parameters     :  None

Return Value   :  None

Description    :  Reset all the duty cycle statistics
*****************************************************************************/
void DCHistoryReset (void)
{
  DutyCycleHistory = 0;
  LeakDutyCycle = 0;
  TargetVaccumOffsetDutyCycle = 0;
}

/****************************************************************************
Function Name  :  DCCalculateAll

Parameters     :  None

Return Value   :  None

Description    :  Update all the duty cycle statistics parsing the DC Duty Cycle) History.
                  It has to be invoked at regular intervals (currently every
                  second) whose value depends on the history duration 
*****************************************************************************/
void DCCalculateAll(void)
{
  uint32_t history = DutyCycleHistory;
  uint8_t dutyCycle = 0;
  
  // Zero the duty cycle for all the relevant periods
  TargetVaccumOffsetDutyCycle = 0;
  LeakDutyCycle = 0;
  
  // Count how many bits are set in history (the count starts from 1 so it's
  // easier to compare with given periods)
  // Does it for all 32 bits even thought only 30 are used
  for (uint8_t i = 1; i<(CHAR_BIT*sizeof(history)); i++, history >>= 1)
  {
    dutyCycle += (history & 1);
    
    // At certain points during the bitmap scan take copies of the counts  
    // Update the the duty cycle for all the relevant periods
    if (VACUUM_OFFSET_DUTY_CYCLE_PERIOD == i)
    {
      TargetVaccumOffsetDutyCycle = dutyCycle;
    }
    
    // The first 9 count total gives how effective the pumping is working
    if (LEAK_DUTY_CYCLE_PERIOD == i)
    {
      LeakDutyCycle = dutyCycle;
    }
  }

  PerformanceLogger_SetPumpHistory(DutyCycleHistory);
}

/****************************************************************************
Function Name  :  DCLeakGet

Parameters     :  None

Return Value   :  uint8_t - number of Pump On events over the leak monitoring
                            period

Description    :  Returns the number of Pump On events over the leak monitoring
                  period
*****************************************************************************/
uint8_t  DCLeakGet(void)
{
  return LeakDutyCycle;
}

/****************************************************************************
Function Name  :  DCVaccumOffsetUpdateGet

Parameters     :  None

Return Value   :  None

Description    :  Returns the target duty cycle for the system. This is the number 
                  of pumps in the last 9 seconds and indicates if the system is working
                  efficiently. This allows the target pressure to be modified depending 
 on this value.
         
*****************************************************************************/
uint8_t DCVaccumOffsetUpdateGet(void)
{
  return TargetVaccumOffsetDutyCycle;
}

/****************************************************************************
Function Name  :  DCPumpOnUpdate

Parameters     :  None

Return Value   :  None

Description    :  Set the pump down for the current second
*****************************************************************************/
void DCPumpOnUpdate(void)
{
  DutyCycleHistory |= 1;
}

/****************************************************************************
Function Name  :  DCPumpOffUpdate

Parameters     :  None

Return Value   :  None

Description    :  Shifts along to allow a new second to be updated. The second 
                  will default to off.
*****************************************************************************/
void DCPumpOffUpdate(void)
{
  DutyCycleHistory <<= 1;
}
