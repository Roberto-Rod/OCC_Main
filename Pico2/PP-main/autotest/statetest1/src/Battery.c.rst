/*****************************************************************************
 *   File        : Battery.c
 *
 *   Description : Implementation of Battery Monitoring.
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

#include "limits.h"
#include "Battery.h"
#include "adc.h"
#include "PowerControl.h"
#include "Debug.h"
#include "PerformanceLogger.h"
#include "Timer.h"

#define MAX_VBOOST_LIMIT      (280)    // 33V
#define MIN_VBOOST_LIMIT      (136)    // 16V
#define VFRV_AT_3V0           (350.0)  //3v/(2^10) * 1.024V = 349.5
#define MAX_VBATTERY_LIMIT    (291)    // 3.6V, 1.024V/3.6V * (2^10)
#define VBATTERY_LIMIT_2V2    (477)    // 2.2V, 1.024V/2.7V * (2^10)
#define VBST_DEMAND_FILTER_SIZE    (8)

typedef enum {
    BT_NO_LOAD_E, 
    BT_UNDER_LOAD_E
} BatteryLoadCondition_t; 

static uint8_t vBoostDemandFilterIndex = 0;
static float32_t vBoostDemandFilter[VBST_DEMAND_FILTER_SIZE];


// SCU 
uint8_t errorCount = 0;
void logError ( const uint16_t errorNo );

static float32_t vBoostDemandFilterSum;
static uint8_t voltageExceptionCount = 0;

static bool_t isBoostVoltageOutOfRange(uint16_t referenceVoltageAdc, uint32_t vBoostAdc);

static void adjustBoostDemand(const uint16_t referenceVoltageAdc, const uint16_t initBoostDemand);

static void logBatteryVoltage(const uint16_t refVoltageAdc, const BatteryLoadCondition_t batteryLoad);

ErrorCode_t Battery_CheckVoltageBounds(void)
{
  ErrorCode_t errorCode = EC_OK_E;

  /* Read output voltage of the boost converter as boostVoltageAdc */
  uint16_t boostVoltageAdc = (uint16_t) ((ADC_GetConversion(Boost_Voltage) >> 6) & 0x0FFF);

  /* Get the internal reference voltage 1.024 and work out the
   * Vdd supply using the internal Vref.
   * Returned value is 2^10 * 1.024/Vdd
   * 
   * Note: this is the reference fix voltage of the CPU, which is always 1.024V.
   *       Based on the corresponding ADC value, we can then work out the actual
   *       battery voltage. However we use the battery voltage only for logging,
   *       and we use the un-converted ADC values to figure out if the battery voltage
   *       is within acceptable limits
   */
  uint16_t referenceVoltageAdc = (uint16_t) ((ADC_GetConversion(channel_FVR) >> 6) & 0x0FFF);


  logBatteryVoltage(referenceVoltageAdc, BT_UNDER_LOAD_E);

  uint8_t initBoostDemand = MP_GetInitBoostDemand();

  /* Scale the boost converter demand to match the Vdd from the
   * initial value calculated at 3V0. Then update the demand to the
   * boost converter.  This is needed because the DAC output scales
   * to Vdd which varies over battery lifetime.
   */
  adjustBoostDemand(referenceVoltageAdc, initBoostDemand);

  /* Scale the vBoost due to variation of Vdd. */
  uint32_t vBoostAdc = (uint32_t) (((float32_t) (boostVoltageAdc * VFRV_AT_3V0) / referenceVoltageAdc));

  /* Check vBoost is within limits.
   * Also check Vdd (one cell) is also within limits.
   */
  if (isBoostVoltageOutOfRange(referenceVoltageAdc, vBoostAdc))
  {
    if (voltageExceptionCount++ > 50)
    {
       logError((8<<9)+errorCount++);   // SCU   
      
      MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
      voltageExceptionCount = 0;
      errorCode = EC_VOLTAGE_OUT_OF_RANGE_E;
    }
  }
  else if ((VBATTERY_LIMIT_2V2 < referenceVoltageAdc))
  {
    if (voltageExceptionCount++ > 10)
    {
      MP_SetInitBoostDemand((uint8_t) (initBoostDemand - (uint8_t) 1));
      voltageExceptionCount = 0;
    }
    if (VBOOST_REF_18V > initBoostDemand)
    {
      // The use of local variable initBoostDemand as opposed to
      // MP_GetInitBoostDemand() results in the End of Life condition
      // being detected at the next Battery_CheckVoltageBounds() execution
      voltageExceptionCount = 0;
      errorCode = EC_BATTERY_END_OF_LIFE_E;
    }
  }
  else if (voltageExceptionCount > 0)
  {
    voltageExceptionCount--;
  }

  return (errorCode);
}


void Battery_CheckVoltageWithNoLoad(void)
{
  MP_EnableFvr();
  PM_Delay((uint32_t) ONE_MILLISECOND_DELAY);
  
  uint16_t referenceVoltageAdc = (uint16_t) ((ADC_GetConversion(channel_FVR) >> 6) & 0x03FF);

  logBatteryVoltage(referenceVoltageAdc, BT_NO_LOAD_E);
}


static bool_t isBoostVoltageOutOfRange(uint16_t referenceVoltageAdc, uint32_t vBoostAdc)
{
  return ((bool_t) ((MAX_VBOOST_LIMIT < vBoostAdc) ||
                    (MIN_VBOOST_LIMIT > vBoostAdc) ||
                    (MAX_VBATTERY_LIMIT > referenceVoltageAdc))); //reference voltage indicates that Vdd is >3.6V
}


static void adjustBoostDemand(const uint16_t referenceVoltageAdc, const uint16_t initBoostDemand)
{
  float32_t boostVoltage =
      ((float32_t) referenceVoltageAdc * (float32_t) initBoostDemand) / (float32_t) VFRV_AT_3V0;

  vBoostDemandFilterIndex++;
  vBoostDemandFilter[(uint8_t) (vBoostDemandFilterIndex % VBST_DEMAND_FILTER_SIZE)] = boostVoltage;
  vBoostDemandFilterSum = 0.5;  //for ensuring correct rounding from float to int later

  for (uint8_t i = 0; i < 8; i++)
  {
    vBoostDemandFilterSum += vBoostDemandFilter[i];
  }
  MP_SetBoostDemand((uint8_t) (((uint8_t) (vBoostDemandFilterSum)) >> 3));
}

static void logBatteryVoltage(const uint16_t refVoltageAdc, const BatteryLoadCondition_t batteryLoad)
{
  uint32_t supplyVoltageMilliVolt = 0;
  uint16_t supplyVoltageMilliVoltResult = 0;
  // Vdd is calculated as (2^10 - 1)/(ADCvref) * 1.024
  const uint32_t adcAtVdd = 1024u; // should be 1023u but we approximate up to 1024 so it helps with the calculations
  const uint32_t refVoltageMilliVolt = 1024u; //1024 mV

  if (refVoltageAdc > 0)
  {
      supplyVoltageMilliVolt = (adcAtVdd) * refVoltageMilliVolt / ((uint32_t) refVoltageAdc);
      // ensure result can be stored in 16-bits used for logging
      if (supplyVoltageMilliVolt > USHRT_MAX)
      {
          supplyVoltageMilliVoltResult = 0; // error
      }
      else
      {
          supplyVoltageMilliVoltResult = (uint16_t) supplyVoltageMilliVolt;
      }
  }

  if (BT_NO_LOAD_E == batteryLoad)
  {
    PerformanceLogger_SetVddForTemperatureMeasurement(supplyVoltageMilliVoltResult);
  }
  else
  {
    PerformanceLogger_SetBatteryVoltage(supplyVoltageMilliVoltResult);
  }
}
