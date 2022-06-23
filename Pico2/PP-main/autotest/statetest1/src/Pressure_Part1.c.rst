/*****************************************************************************
 *   File        : Pressure_Part1.c
 *
 *   Description : Source for implementation of pressure measurements
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

#include <limits.h>
#include "Pressure_Part1.h"
#include "Pressure_Part2.h"
#include "Pressure_Part3.h"
#include "Pressure_Part4.h"
#include "PowerControl.h"
#include "Timer.h"
#include "DutyCycle.h"


void logError ( const uint16_t errorNo );
static int  Auto_Leak_Count = 0; 
static int autoLeakInstanceCount = 0;
void Auto_Leak_Detected()
{
  Auto_Leak_Count = 1;    
}

static uint32_t InitialExtPress = 0; // External pressure on initial pump down
static uint8_t TargetPumpDownVaccumDebounceCount = 0;
static uint16_t TargetTherapyDeliveryVacuumOffset = 0; 

/****************************************************************************
Function Name  :  InitPumpDownVacuum

Parameters     :  None

Return Value   :  None

Description    :  Initialise the pressure variables for Pump Down state
*****************************************************************************/
void InitPumpDownVacuum (void)
{
  InitialExtPress = 0;
  TargetPumpDownVaccumDebounceCount = 0;
}

/****************************************************************************
Function Name  :  InitTherapyDeliveryVacuum

Parameters     :  None

Return Value   :  None

Description    :  Initialise the pressure variables for Therapy Delivery state
*****************************************************************************/
void InitTherapyDeliveryVacuum(void)
{
  TargetTherapyDeliveryVacuumOffset = 0;
}

/****************************************************************************
Function Name  :  GetVacuum

Parameters     :  uint16_t* pInternal - Pointer to the internal vacuum 
                  uint16_t* pExternal - Pointer to the external vacuum  
                  uint16_t* pVacuum - Pointer to vacuum variable to update

Return Value   :  EC_OK_E if the vacuum are read OK, or error otherwise

Description    :  Reads the external and internal pressure sensors and
                  calculate their difference
*****************************************************************************/
ErrorCode_t GetVacuum(uint16_t* pInternal,uint16_t* pExternal, uint16_t* pDiff)
{
  ErrorCode_t result = EC_OK_E;
  
  if  ((NULL == pInternal ) || (NULL == pExternal ) ||  (NULL == pDiff))
  {
    result = EC_INVALID_INPUT_PARAMETER_E;
  }
  
  if(EC_OK_E == result)
  {
    MP_EnableExternalPeripheralsSupply();

    // this needs replacing with a better check
    PM_Delay((uint32_t) 8);
    
    // Initialise pressure sensors
    result = PM_InitSensors();
  }
  
  // Start pressure capture
  if(EC_OK_E == result)
  {
    result = PM_StartSensors();
  }
  
  if(EC_OK_E == result)
  {
    PM_Delay((uint32_t) TWENTY_MILLISECONDS_DELAY);
    
    uint8_t retry_count = GET_VACUUM_MAX_RETRIES;
    result = EC_PRESSURE_SENSOR_READ_FAILED_E;
    while((0 != retry_count) && (EC_OK_E != result))
    {
      result = TryToGetSingleVacuumMeasurement(pInternal, pExternal, pDiff);
      
      if(EC_OK_E == result)
      {        
        retry_count = 0;
      }
      else
      {
        retry_count--;
        //ONE_MILLISECOND_DELAY
        PM_Delay((uint32_t) 5);
      }
    }
  }
  
  MP_DisableExternalPeripheralsSupply();
  
  return result;
}

/****************************************************************************
Function Name  :  isTargetPumpDownVacuumAchieved

Parameters     :  uint16_t Vacuum - vacuum to compare against target

Return Value   :  TRUE if Vacuum is at target for number of consecutive times,
                  FALSE otherwise

Description    :  Compares the input Vacuum against the nominal vacuum target
                  plus its current offset when in Pump Down state. This has to
                  be met a number of consecutive times to return TRUE
                  (Note that the function does not increment debounce counter
                  above 255 which is an unlikely event)
*****************************************************************************/
bool_t  isTargetPumpDownVacuumAchieved(uint16_t Vacuum)
{
  bool_t result;
  
  if (PUMP_DOWN_TARGET_VACUUM < Vacuum)
  {
    if (TargetPumpDownVaccumDebounceCount < UCHAR_MAX)
    {
      TargetPumpDownVaccumDebounceCount++; // increment count
    }
    else
    {
      TargetPumpDownVaccumDebounceCount = UCHAR_MAX; // set to maximum value
    }
  }
  else
  {
    TargetPumpDownVaccumDebounceCount = 0;
  }
  
  result = (bool_t) ((PUMP_DOWN_DEBOUNCE_VACUUM_MAX <= TargetPumpDownVaccumDebounceCount) ? TRUE:FALSE);
  
  return result;
}

/****************************************************************************
Function Name  :  GetTargetPumpDownVaccumDebounceCount

Parameters     :  None

Return Value   :  uint32_t - value for initial ext pressure

Description    :  Gets initial ext pressure sensor reading 
*****************************************************************************/
uint32_t GetInitialExternalPressure(void)
{
    return(InitialExtPress);
}

/****************************************************************************
Function Name  :  SetInitialExternalPressure

Parameters     :  uint32_t PressureValue - value to set initial ext pressure to

Return Value   :  None

Description    :  Sets initial ext pressure sensor reading 
*****************************************************************************/
void SetInitialExternalPressure(uint32_t PressureValue)
{
    InitialExtPress = PressureValue;
}

/****************************************************************************
Function Name  :  GetTargetPumpDownVaccumDebounceCount

Parameters     :  None

Return Value   :  Current number of consecutive Vacuum readings above target

Description    :  Returns current number of consecutive Vacuum readings above
                  target 
*****************************************************************************/
uint32_t GetTargetPumpDownVaccumDebounceCount(void)
{
    return(TargetPumpDownVaccumDebounceCount);
}

/****************************************************************************
Function Name  :  TherapyDeliveryTargetVacuumUpdate

Parameters     :  None

Return Value   :  None

Description    :  Adjusts the Off set for the Target Vacuum (currently in
                  function of the Pump On duty cycle over a set period period)
                  This is done only if the battery is not depleting.
*****************************************************************************/
void TherapyDeliveryTargetVacuumUpdate(void)
{
  uint8_t dutyCycle = DCVaccumOffsetUpdateGet();
  
  // Update the Vacuum Offset (hence Target Vacuum) only if the battery is not depleting
  if (VBOOST_REF == MP_GetInitBoostDemand())
  {
    // Pumping on too frequently - reduce vacuum offset
    if ((MAINTANENCE_DUTY_CYCLE < dutyCycle)   &&
        (0 < TargetTherapyDeliveryVacuumOffset))
    {
      TargetTherapyDeliveryVacuumOffset--;
    }
    // Pumping on not frequently - increase the vacuum offset
    else if((MAINTANENCE_DUTY_CYCLE > dutyCycle) &&
            (THERAPY_DELIVERY_MAX_PRESSURE_OFFSET > TargetTherapyDeliveryVacuumOffset)) 
    {
      TargetTherapyDeliveryVacuumOffset++;
    }
    //                    !!WARNING!!
    // We may need to add a BLOCK detection when the pump is not being
    // activated for too long 
  }
}


/****************************************************************************
Function Name  :  isLeakDutyCycleDecteded

Parameters     :  None

Return Value   :  TRUE if LEAK detected, FALSE otherwise

Description    :  Check if a LEAK event has been seen (currently based on a
                  a specific value of the Pump On duty cycle). This is done
                  only if the battery is not depleting)
*****************************************************************************/
 
bool_t  isTherapyDeliveryLeakDetected(void)
{
  bool_t result = FALSE;
  
  if (VBOOST_REF == MP_GetInitBoostDemand())
  {
    result = ((bool_t) (LEAK_DUTY_CYCLE < DCLeakGet()));
  }
 
  // SCU generate or record  error 
  if ( Auto_Leak_Count != 0 )
  {  
      Auto_Leak_Count--;
      result = TRUE;
  }
  if ( result)
  {
      logError((8<<8)+autoLeakInstanceCount++);
  } 
  // SCU 
  
  return result;
}


/****************************************************************************
Function Name  :  isTargetTherapyDeliveryVacuumAchieved

Parameters     :  uint16_t Vacuum - vacuum to compare against target 

Return Value   :  TRUE if Vacuum is at target, FALSE otherwise

Description    :  Compares the input Vacuum against the nominal vacuum target
                  plus its current offset when in Therapy Delivery state
*****************************************************************************/
bool_t  isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum)
{
  return ((bool_t) ((THERAPY_DELIVERY_TARGET_VACUUM + TargetTherapyDeliveryVacuumOffset)<= Vacuum));
}
