#include "Mockadc.h"
#include "PumpFrequencyTracker.h"
#include "unity.h"


uint8_t NCO1INCL;

uint8_t NCO1INCH;



const uint16_t startFrequency = 2752;

const uint16_t minAcceptableFrequency = 3072;

const uint16_t maxAcceptableFrequency = 2432;



static uint16_t adcResult;



adc_result_t StubADC_GetConversion(adc_channel_t channel, int numCall)

{

  UnityAssertEqualNumber((_U_SINT)((HBridge_Current)), (_U_SINT)((channel)), (

 ((void *)0)

 ), (_U_UINT)(33), UNITY_DISPLAY_STYLE_INT);

  return (adc_result_t) adcResult;

}





void setUp(void)

{

  PumpFrequencyTracker_Init();

  ADC_GetConversion_StubWithCallback(StubADC_GetConversion);



  adcResult = 0;

  NCO1INCL = startFrequency & 0xff;

  NCO1INCH = (startFrequency >> 8) & 0xff;

}



void tearDown(void)

{}



static uint16_t toWord(uint8_t hiByte, uint8_t lowByte)

{

  return ((uint16_t)hiByte << 8) | lowByte;

}



void test_WhenCurrentStaysTheSameNoFrequencyAdjustment(void)

{

  adcResult = 0x3f0;





  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(62), UNITY_DISPLAY_STYLE_INT);

  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(64), UNITY_DISPLAY_STYLE_INT);





  previousFreq = newFreq;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(68), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(69), UNITY_DISPLAY_STYLE_INT);





  previousFreq = newFreq;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(73), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(74), UNITY_DISPLAY_STYLE_INT);

}









void test_OnDownwardSlopeWhenCurrentIsIncreasedThenDecreaseFrequency(void)

{

  adcResult = 0x3f0;





  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(86), UNITY_DISPLAY_STYLE_INT);

  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((newFreq)), (

 ((void *)0)

 ), (_U_UINT)(88), UNITY_DISPLAY_STYLE_INT);





  adcResult +=1;

  previousFreq = newFreq;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(93), UNITY_DISPLAY_STYLE_INT);

  newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((newFreq)), (

 ((void *)0)

 ), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);



  adcResult +=1;

  previousFreq = newFreq;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

  newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((newFreq)), (

 ((void *)0)

 ), (_U_UINT)(101), UNITY_DISPLAY_STYLE_INT);



  adcResult += 1;

  previousFreq = newFreq;

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(105), UNITY_DISPLAY_STYLE_INT);

  newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((newFreq)), (

 ((void *)0)

 ), (_U_UINT)(107), UNITY_DISPLAY_STYLE_INT);



}



void test_WhenCurrentIsIncreasedOnIncreasedFrequencyThenKeepIncreasingFrequency(void)

{

  adcResult = startFrequency;





  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);

  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((newFreq)), (

 ((void *)0)

 ), (_U_UINT)(119), UNITY_DISPLAY_STYLE_INT);





  adcResult -= (1 << 6);

  previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq + 4)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(125), UNITY_DISPLAY_STYLE_INT);





  adcResult += (1 << 6);

  previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(130), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq + 4)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);



  adcResult += (1 << 6);

  previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(135), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq + 4)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(136), UNITY_DISPLAY_STYLE_INT);

}



void test_IfCurrentIsDecreasedInResponseToIncreasedFrequencyThenIncreaseFrequency(void)

{

  adcResult = startFrequency;





  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(145), UNITY_DISPLAY_STYLE_INT);

  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((newFreq)), (

 ((void *)0)

 ), (_U_UINT)(147), UNITY_DISPLAY_STYLE_INT);





  adcResult -= (1 << 6);

  previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq + 4)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(153), UNITY_DISPLAY_STYLE_INT);

}



void test_IfCurrentIsDecreasedInResponseToIncreasedFrequencyThenDecreaseFrequency(void)

{

  adcResult = startFrequency;





  uint16_t previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(162), UNITY_DISPLAY_STYLE_INT);

  uint16_t newFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((newFreq)), (

 ((void *)0)

 ), (_U_UINT)(164), UNITY_DISPLAY_STYLE_INT);





  adcResult -= (1 << 6);

  previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq + 4)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(170), UNITY_DISPLAY_STYLE_INT);





  adcResult -= (1 << 6);

  previousFreq = toWord(NCO1INCH, NCO1INCL);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(175), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((previousFreq - 4)), (_U_SINT)((toWord(NCO1INCH, NCO1INCL))), (

 ((void *)0)

 ), (_U_UINT)(176), UNITY_DISPLAY_STYLE_INT);

}



void test_FrequencyOutOfRangeLowerBoundCheck(void)

{

  adcResult = 0;

  NCO1INCL = (minAcceptableFrequency & 0xff) - 1u;

  NCO1INCH = (minAcceptableFrequency >> 8) & 0xff;

  UnityAssertEqualNumber((_U_SINT)((EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(184), UNITY_DISPLAY_STYLE_INT);

}



void test_FrequencyOutOfRangeUpperBoundCheck(void)

{

  adcResult = 0;

  NCO1INCL = (minAcceptableFrequency & 0xff) + 1;

  NCO1INCH = (minAcceptableFrequency >> 8) & 0xff;

  UnityAssertEqualNumber((_U_SINT)((EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E)), (_U_SINT)((PumpFrequencyTracker_Optimise())), (

 ((void *)0)

 ), (_U_UINT)(192), UNITY_DISPLAY_STYLE_INT);

}
