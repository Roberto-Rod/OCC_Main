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


// SCU 
void logError ( const uint16_t errorNo );

static int autoFreqInstancCount = 0;

static int  Auto_Voltage_Range_Count = 0;


static int autoVoltRangeInstancCount = 0;
void Auto_Voltage_Out_Of_Range()
{
  Auto_Voltage_Range_Count = 1;    
}

static int  Auto_Voltage_End_Of_Life_Count = 0;

void Auto_Voltage_End_Of_Life()
{
  Auto_Voltage_End_Of_Life_Count = 1;    
}

static int  Auto_Tracker_Freq_Fail_Count = 0;

void Auto_Tracker_Freq_Fail()
{
  Auto_Tracker_Freq_Fail_Count = 1;    
}


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
  
    
  // SCU Code If we want an error we have to be in the active state 
  if  (( Auto_Voltage_Range_Count != 0 ) || ( Auto_Voltage_End_Of_Life_Count != 0 ) ||    
     ( Auto_Tracker_Freq_Fail_Count != 0 ))
  {
      Activate = TRUE;
  }
  // SCU Code to here 
  
  
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
    
    
     // SCU Code 
     if (  Auto_Tracker_Freq_Fail_Count != 0 )
     {
         Auto_Tracker_Freq_Fail_Count = 0;
         result = EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E;
     } 
     if ( result == EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E) 
     {
           logError ( (2<<8)+autoFreqInstancCount++ );
     }
    // SCU Code to here
     
    
    if (EC_OK_E == result)
    {
      result = Battery_CheckVoltageBounds();
    }
    
        
    // SCU code 
    if (  Auto_Voltage_Range_Count != 0 )
    {    
        Auto_Voltage_Range_Count = 0;
        result = EC_VOLTAGE_OUT_OF_RANGE_E;    
    } 
    
    if (result == EC_VOLTAGE_OUT_OF_RANGE_E )
    {
       logError ( (4<<8)+autoVoltRangeInstancCount++ );    
    }
       // SCU code 
     if (  Auto_Voltage_End_Of_Life_Count != 0 )
     {
         Auto_Voltage_End_Of_Life_Count = 0;
          result = EC_BATTERY_END_OF_LIFE_E;
     } 
     // SCU Code to here
    
    
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

