/*****************************************************************************
 *   File        : Pump.c
 *
 *   Description : Implementation of Pump controls
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

#include "Pump.h"
#include "PowerControl.h"
#include "Timer.h"
#include "Battery.h"
#include "PumpFrequencyTracker.h"
#include "DeviceStatus.h"

/************************************************
*  @brief   
*  @param   None
*  @return  EC_OK_E or error code 
*           (currently always EC_OK_E)
*
*************************************************/
ErrorCode_t PumpActivate(bool_t Activate)
{
  ErrorCode_t result = EC_OK_E;
  
  if (Activate)
  {  
    MP_EnableExternalPeripheralsSupply();
    MP_EnableMainCircuitPower();
    MP_EnablePumpPWM();
    // Set boost converter voltage 
    MP_SetReferenceVoltageBoost(MP_GetBoostDemand());
    // wait for 40 ms for the Pump to stabilise
    PM_Delay((uint32_t) FORTY_MILLISECONDS_DELAY);
    // Adjust the PWM frequency towards an optimal value 
    result = PumpFrequencyTracker_Optimise();
    
    if (EC_OK_E == result)
    {
      result = Battery_CheckVoltageBounds();
    }
    
    MP_DisableExternalPeripheralsSupply();
  }
  else
  {
    MP_DisablePumpPWM();
    // Set boost converter voltage 
    MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
  }

  DeviceStatus_SetPumpIsRunning(Activate);
  
  return result;
}

/************************************************
*  @brief   
*  @param   None
*  @return  None
*
*************************************************/
bool_t isPumpActivated(void)
{
  return ((bool_t) (isMainCircuitPowerEnabled() && isPumpPwmEnabled()));
}

