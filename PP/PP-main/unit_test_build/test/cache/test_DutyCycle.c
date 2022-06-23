#include "MockPerformanceLogger.h"
#include "DutyCycle.h"
#include "unity.h"


void setUp(void)

{

  PerformanceLogger_SetPumpHistory_CMockIgnore();

}



void tearDown(void)

{}











void test_PumpOnOffHistoryResetSetAndGetDutyCycleStats(void)

{



  DCHistoryReset();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

 ((void *)0)

 ), (_U_UINT)(38), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DCLeakGet())), (

 ((void *)0)

 ), (_U_UINT)(39), UNITY_DISPLAY_STYLE_INT);





  DCPumpOnUpdate();

  DCCalculateAll();

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

 ((void *)0)

 ), (_U_UINT)(44), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((DCLeakGet())), (

 ((void *)0)

 ), (_U_UINT)(45), UNITY_DISPLAY_STYLE_INT);







  DCPumpOnUpdate();

  DCCalculateAll();

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

 ((void *)0)

 ), (_U_UINT)(51), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((DCLeakGet())), (

 ((void *)0)

 ), (_U_UINT)(52), UNITY_DISPLAY_STYLE_INT);





  DCPumpOffUpdate();

  DCPumpOnUpdate();

  DCCalculateAll();

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

 ((void *)0)

 ), (_U_UINT)(58), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((DCLeakGet())), (

 ((void *)0)

 ), (_U_UINT)(59), UNITY_DISPLAY_STYLE_INT);





  DCHistoryReset();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

 ((void *)0)

 ), (_U_UINT)(63), UNITY_DISPLAY_STYLE_INT);

}















void test_PumpOnOffNumberOfTimesToHitTheLimitsOfDutyCycleHistoryAndCheck(void)

{



  for (uint8_t i = 1; i < 35; i++)

  {

    DCPumpOffUpdate();

    DCPumpOnUpdate();

    DCCalculateAll();

    if ((30) < i)

    {





      UnityAssertEqualNumber((_U_SINT)(((9))), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

     ((void *)0)

     ), (_U_UINT)(84), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)(((30))), (_U_SINT)((DCLeakGet())), (

     ((void *)0)

     ), (_U_UINT)(85), UNITY_DISPLAY_STYLE_INT);

    }

    else if ((9) < i)

    {







      UnityAssertEqualNumber((_U_SINT)(((9))), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

     ((void *)0)

     ), (_U_UINT)(92), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)((i)), (_U_SINT)((DCLeakGet())), (

     ((void *)0)

     ), (_U_UINT)(93), UNITY_DISPLAY_STYLE_INT);

    }

    else

    {





      UnityAssertEqualNumber((_U_SINT)((i)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

     ((void *)0)

     ), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)((i)), (_U_SINT)((DCLeakGet())), (

     ((void *)0)

     ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);

    }

  }

}





void test_PumpOffWithNoPumpOnPhasesOutOlderPumpOnEventsFromHistory(void)

{





  for (uint8_t i = 1; i < 35; i++)

  {

    DCPumpOffUpdate();

    DCPumpOnUpdate();

    DCCalculateAll();

  }





  for (uint8_t i = 0; i < 35; i++)

  {

    if ((30) < i)

    {





      UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

     ((void *)0)

     ), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DCLeakGet())), (

     ((void *)0)

     ), (_U_UINT)(125), UNITY_DISPLAY_STYLE_INT);

    }

    else if ((9) < i)

    {







      UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

     ((void *)0)

     ), (_U_UINT)(132), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)((((30)-i))), (_U_SINT)((DCLeakGet())), (

     ((void *)0)

     ), (_U_UINT)(133), UNITY_DISPLAY_STYLE_INT);

    }

    else

    {





      UnityAssertEqualNumber((_U_SINT)((((9)-i))), (_U_SINT)((DCVaccumOffsetUpdateGet())), (

     ((void *)0)

     ), (_U_UINT)(139), UNITY_DISPLAY_STYLE_INT);

      UnityAssertEqualNumber((_U_SINT)((((30)-i))), (_U_SINT)((DCLeakGet())), (

     ((void *)0)

     ), (_U_UINT)(140), UNITY_DISPLAY_STYLE_INT);

    }



    DCPumpOffUpdate();

    DCCalculateAll();

  }

}
