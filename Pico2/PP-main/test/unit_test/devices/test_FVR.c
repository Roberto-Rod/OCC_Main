/*****************************************************************************
 *   File        : test_FVR.c
 *
 *   Description: Source Code for testing of the FVR (Fixed Voltage Reference) Access.
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

#include "unity.h"
#include "Battery.h"
#include "Mockadc.h"
#include "MockPowerControl.h"
#include "MockPerformanceLogger.h"
#include "MockTimer.h"
#include "Debug.h"

static uint16_t fixRefVoltageAdc;
static uint8_t initBoostDemand;
static uint8_t boostDemand;
static uint8_t batteryVoltageAdc;

adc_result_t StubADC_GetConversion(adc_channel_t channel, int numCall)
{
  if (channel == Boost_Voltage)
  {
//    printf("Battery adc: %d\n", batteryVoltageAdc);
    return (adc_result_t)(batteryVoltageAdc << 6);
  }
  else if (channel == channel_FVR)
  {
//    printf("FBR adc: %d\n", fixRefVoltageAdc);
    return (adc_result_t)(fixRefVoltageAdc << 6);
  }

  TEST_FAIL_MESSAGE("Incorrect ADC channel passed");

  return (adc_result_t) 0;
}


void setUp(void)
{
  ADC_GetConversion_StubWithCallback(StubADC_GetConversion);

  fixRefVoltageAdc = 0;
  batteryVoltageAdc = 100;
}

void tearDown(void)
{}

// Simply check that the FVR is powered on and the correct channel is read
// void test_fvr_usage(void )
// {

   //fixRefVoltageAdc = 100;
  
   //PM_Delay_Expect(1);  //1 ms delay to wait for power supply to stable

   //PerformanceLogger_SetVddForTemperatureMeasurement_Expect(0x28F5);

//}	

