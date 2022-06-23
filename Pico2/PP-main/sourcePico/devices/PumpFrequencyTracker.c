/*****************************************************************************
 *   File        : PumpFrequencyTracker.c
 *
 *   Description : This module adjusts frequency of the NCO with the objective
 * to get the maximum current the pump can deliver.
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

#include "PumpFrequencyTracker.h"
#include "PaTypes.h"
#include "adc.h"

#ifdef UNIT_TEST
    #include "pic16lf1509.h"
    extern volatile uint8_t  NCO1INCL;
    extern volatile uint8_t  NCO1INCH;
#endif

/* Power tracking definitions */
#define FREQ_STEP_SIZE_POWEROF2   (2)
#define FREQ_STEP_SIZE            (1 << FREQ_STEP_SIZE_POWEROF2)
#define FREQ_RANGE                (32 * FREQ_STEP_SIZE)
#define FREQ_START_CENTRE         (2752)
#define FREQ_RANGE_MIN_ERROR      (FREQ_START_CENTRE - 5*(FREQ_RANGE >> 1))
#define FREQ_RANGE_MAX_ERROR      (FREQ_START_CENTRE + 5*(FREQ_RANGE >> 1))

static uint16_t previousCurrentAdc = 0;
static uint8_t deltaPwmFreq = 0;

//Re-initialise static variables for unit testing purpose.
void PumpFrequencyTracker_Init()
{
  previousCurrentAdc = 0;
  deltaPwmFreq = 0;
}

ErrorCode_t PumpFrequencyTracker_Optimise()
{
  ErrorCode_t errorCode = EC_OK_E;
  uint16_t latestCurrentAdc;

  // get current ncoFrequency, i.e. (NCO1INC) register value
  uint16_t ncoFrequency = ((((uint16_t) NCO1INCH) << 8) | NCO1INCL);
  
  latestCurrentAdc = (uint16_t) ADC_GetConversion(HBridge_Current) & 0x03FF;

  // set new ncoFrequency, i.e. (NCO1INC) register value
  if ((latestCurrentAdc > previousCurrentAdc) && deltaPwmFreq)
  {
    ncoFrequency += FREQ_STEP_SIZE;
    deltaPwmFreq = 1;
  }
  else if ((latestCurrentAdc > previousCurrentAdc) && !deltaPwmFreq)
  {
    ncoFrequency -= FREQ_STEP_SIZE;
    deltaPwmFreq = 0;
  }
  else if ((latestCurrentAdc < previousCurrentAdc) && deltaPwmFreq)
  {
    ncoFrequency -= FREQ_STEP_SIZE;
    deltaPwmFreq = 0;
  }
  else if ((latestCurrentAdc < previousCurrentAdc) && !deltaPwmFreq)
  {
    ncoFrequency += FREQ_STEP_SIZE;
    deltaPwmFreq = 1;
  }
  else
  {
    // no change
  }
  
  // Check to see if power tracker frequency has reached 24kHz
  if (ncoFrequency < FREQ_RANGE_MIN_ERROR)
  {
    // Error, no update to ncoFrequency, i.e. (NCO1INC) register
    //ncoFrequency = FREQ_RANGE_MIN_ERROR;
    errorCode = EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E; // Return as fault
  }
    // Check to see if power tracker frequency has reached 18kHz
  else if (ncoFrequency > FREQ_RANGE_MAX_ERROR)
  {
    // Error, no update to ncoFrequency, i.e. (NCO1INC) register
    //ncoFrequency = FREQ_RANGE_MAX_ERROR;
    errorCode = EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E; // Return as fault
  }
  else
  {
    // No error, Update to ncoFrequency, i.e. (NCO1INC) register
    NCO1INCH = (uint8_t)((0xFF00 & ncoFrequency) >> 8);
    NCO1INCL = (uint8_t)(0x00FF & ncoFrequency);
  }

  previousCurrentAdc = latestCurrentAdc;
  return errorCode;
}
