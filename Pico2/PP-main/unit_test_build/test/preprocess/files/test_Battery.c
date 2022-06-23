#include "Debug.h"
#include "MockTimer.h"
#include "MockPerformanceLogger.h"
#include "MockPowerControl.h"
#include "Mockadc.h"
#include "Battery.h"
#include "unity.h"


static uint16_t batteryVoltageAdc;

static uint16_t fixRefVoltageAdc;

static uint16_t boostReferenceVoltage;

static uint8_t initBoostDemand;

static uint8_t boostDemand;



adc_result_t StubADC_GetConversion(adc_channel_t channel, int numCall)

{

  if (channel == Boost_Voltage)

  {



    return (adc_result_t)(batteryVoltageAdc);

  }

  else if (channel == channel_FVR)

  {



    return (adc_result_t)(fixRefVoltageAdc );

  }



  UnityFail( (("Incorrect ADC channel passed")), (_U_UINT)(45));



  return (adc_result_t) 0;

}



void StubMP_SetReferenceVoltageBoost(uint8_t demand, int numCall)

{

  boostReferenceVoltage = demand;

}



void StubMP_SetInitBoostDemand(uint8_t demand, int numCall)

{

  initBoostDemand = demand;

}



void StubMP_SetBoostDemand(uint8_t demand, int numCall)

{

  boostDemand = demand;

}



uint8_t StubMP_GetInitBoostDemand(int numCall)

{

  return initBoostDemand;

}



static uint16_t toFixRefVoltageAdc(float32_t vddVolt)

{

  return (uint16_t) (1.024 / vddVolt * 1024.0);

}



void setUp(void)

{

  ADC_GetConversion_StubWithCallback(StubADC_GetConversion);

  MP_SetReferenceVoltageBoost_StubWithCallback(StubMP_SetReferenceVoltageBoost);

  MP_SetBoostDemand_StubWithCallback(StubMP_SetBoostDemand);

  MP_SetInitBoostDemand_StubWithCallback(StubMP_SetInitBoostDemand);

  MP_GetInitBoostDemand_StubWithCallback(StubMP_GetInitBoostDemand);

  PerformanceLogger_SetBatteryVoltage_CMockIgnore();



  batteryVoltageAdc = 0;

  fixRefVoltageAdc = 0;

  boostReferenceVoltage = 0;

  initBoostDemand = (((uint8_t)18));

  boostDemand = (((uint8_t)18));

}



void tearDown(void)

{}



void test_BatteryOutOfRangeWhenVddIsOver3V6(void)

{

  fixRefVoltageAdc = toFixRefVoltageAdc(3.61f);

  batteryVoltageAdc = 200;



  for (int i = 0; i < 51; i++)

  {



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

   ((void *)0)

   ), (_U_UINT)(102), UNITY_DISPLAY_STYLE_INT);



  }

  UnityAssertEqualNumber((_U_SINT)((EC_VOLTAGE_OUT_OF_RANGE_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

 ((void *)0)

 ), (_U_UINT)(105), UNITY_DISPLAY_STYLE_INT);

}



void test_BoostVoltageIsOutOfRangeWhenBoostVoltageIsAbove33V(void)

{

  fixRefVoltageAdc = toFixRefVoltageAdc(3.0f);

  batteryVoltageAdc = 281;



  for (int i = 0; i < 51; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

   ((void *)0)

   ), (_U_UINT)(115), UNITY_DISPLAY_STYLE_INT);



  }

  UnityAssertEqualNumber((_U_SINT)((EC_VOLTAGE_OUT_OF_RANGE_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

 ((void *)0)

 ), (_U_UINT)(118), UNITY_DISPLAY_STYLE_INT);

}



void test_BoostVoltageIsOutOfRangeWhenBoostVoltageIsBelow16V(void)

{

  fixRefVoltageAdc = toFixRefVoltageAdc(3.0f);

  batteryVoltageAdc = 135;



  for (int i = 0; i < 51; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

   ((void *)0)

   ), (_U_UINT)(128), UNITY_DISPLAY_STYLE_INT);



  }

  UnityAssertEqualNumber((_U_SINT)((EC_VOLTAGE_OUT_OF_RANGE_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

 ((void *)0)

 ), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);

}



void test_BatteryEndOfLifeWhenVddIsBelow1V9AndInitBoostDemandBelow18V(void)

{

  fixRefVoltageAdc = toFixRefVoltageAdc(1.89f);

  batteryVoltageAdc = 300;

  initBoostDemand = ((uint8_t)12) - 1;

  UnityAssertEqualNumber((_U_SINT)((EC_BATTERY_END_OF_LIFE_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

 ((void *)0)

 ), (_U_UINT)(139), UNITY_DISPLAY_STYLE_INT);

}



void test_ReduceInitBootstDemandWhenVddIsBelow2V2(void)

{

  fixRefVoltageAdc = toFixRefVoltageAdc(2.19f);

  batteryVoltageAdc = 200;

  const uint16_t startBoostDemand = ((uint8_t)14) + 1;

  initBoostDemand = startBoostDemand;



  for (int i = 0; i < 11; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

   ((void *)0)

   ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((startBoostDemand)), (_U_SINT)((initBoostDemand)), (

   ((void *)0)

   ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);

  }



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

 ((void *)0)

 ), (_U_UINT)(155), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((startBoostDemand - 1)), (_U_SINT)((initBoostDemand)), (

 ((void *)0)

 ), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);



}



void test_ReduceInitBootstDemandDownTo18VWhenVddIsBelow2V2(void)

{

  fixRefVoltageAdc = toFixRefVoltageAdc(2.00f);

  batteryVoltageAdc = 300;

  uint16_t startBoostDemand = ((uint8_t)14);

  initBoostDemand = startBoostDemand;



  while (((uint8_t)12) <= initBoostDemand)

  {

    for (int i = 0; i < 11; i++)

    {

      UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

     ((void *)0)

     ), (_U_UINT)(171), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)((startBoostDemand)), (_U_SINT)((initBoostDemand)), (

     ((void *)0)

     ), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

    }



    UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

   ((void *)0)

   ), (_U_UINT)(175), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((--startBoostDemand)), (_U_SINT)((initBoostDemand)), (

   ((void *)0)

   ), (_U_UINT)(176), UNITY_DISPLAY_STYLE_INT);

  }



  UnityAssertEqualNumber((_U_SINT)((EC_BATTERY_END_OF_LIFE_E)), (_U_SINT)((Battery_CheckVoltageBounds())), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((startBoostDemand)), (_U_SINT)((initBoostDemand)), (

 ((void *)0)

 ), (_U_UINT)(180), UNITY_DISPLAY_STYLE_INT);



}
