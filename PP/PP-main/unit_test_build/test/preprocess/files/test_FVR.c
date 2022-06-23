#include "Debug.h"
#include "MockTimer.h"
#include "MockPerformanceLogger.h"
#include "MockPowerControl.h"
#include "Mockadc.h"
#include "Battery.h"
#include "unity.h"


static uint16_t fixRefVoltageAdc;

static uint8_t initBoostDemand;

static uint8_t boostDemand;

static uint8_t batteryVoltageAdc;



adc_result_t StubADC_GetConversion(adc_channel_t channel, int numCall)

{

  if (channel == Boost_Voltage)

  {



    return (adc_result_t)(batteryVoltageAdc << 6);

  }

  else if (channel == channel_FVR)

  {



    return (adc_result_t)(fixRefVoltageAdc << 6);

  }



  UnityFail( (("Incorrect ADC channel passed")), (_U_UINT)(44));



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
