#include "MockPowerControl.h"
#include "MockTimer.h"
#include "MockPushButton.h"
#include "MockLED.h"
#include "UIInterfaces.h"
#include "unity.h"


static bool_t isGreenSet;

static bool_t isOrangeSet;



static void StubLED_SetGreen(bool_t on, int numCall)

{

  isGreenSet = on;

}



static void StubLED_SetOrange(bool_t on, int numCall)

{

  isOrangeSet = on;

}



static uint32_t tickCount = 0;



void setUp(void)

{

  isOrangeSet = 

               0

                    ;

  isGreenSet = 

              0

                   ;

  tickCount = 0;

  LED_SetGreen_StubWithCallback(StubLED_SetGreen);

  LED_SetOrange_StubWithCallback(StubLED_SetOrange);

}



void tearDown(void)

{}





void test_SetLEDToOrangeEnablesPowerAndDrivesLEDOrange(void)

{

  UI_SetLED(LD_ORANGE_E, 10, 0);

  UI_SetLED(LD_GREEN_E, 0, 0);



  MP_EnableMainCircuitPower_CMockExpect(58);



  UI_UpdateLEDs();

  if ((isOrangeSet)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(61)));};

  if (!(isGreenSet)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(62)));};

}



void test_SetLEDToGreenEnablesPowerAndDrivesLEDGreen(void)

{

  UI_SetLED(LD_ORANGE_E, 0, 0);

  UI_SetLED(LD_GREEN_E, 10, 0);



  MP_EnableMainCircuitPower_CMockExpect(70);



  UI_UpdateLEDs();

  if (!(isOrangeSet)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(73)));};

  if ((isGreenSet)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(74)));};

}



void test_SetLEDDisablesLEDAtOffPeriod(void)

{











  UI_SetLED(LD_ORANGE_E, 0, 0);

  UI_SetLED(LD_GREEN_E, 10, 40);





  MP_EnableMainCircuitPower_CMockExpect(98);

  UI_UpdateLEDs();

  if (!(isOrangeSet)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(100)));};

  if ((isGreenSet)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(101)));};





  UI_SetLED(LD_ORANGE_E, 0, 0);

  UI_SetLED(LD_GREEN_E, 0, 0);





  UI_UpdateLEDs();

  if (!(isOrangeSet)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(109)));};

  if (!(isGreenSet)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(110)));};

}



void test_PushButtonPressed(void)

{

  PushButton_IsPressed_CMockExpectAndReturn(115, 

 0

 );

  if (!(UI_IsPushButtonPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(116)));};



  PushButton_IsPressed_CMockExpectAndReturn(118, 

 1

 );

  if ((UI_IsPushButtonPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(119)));};

}



void test_FlashPattern(void)

{

  MP_EnableMainCircuitPower_CMockIgnore();



  const uint8_t onCount = 3;

  const uint8_t offCount = 5;



  UI_SetLED(LD_GREEN_E, onCount, offCount);



  for (uint32_t sequence = 0; sequence < 5; sequence++)

  {

    for (uint32_t i = 0; i < onCount; i++, tickCount++)

    {

      UI_UpdateLEDs();



      if ((isGreenSet)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(137)));};

    }



    for (uint32_t i = 0; i < offCount; i++, tickCount++)

    {

      UI_UpdateLEDs();



      if (!(isGreenSet)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(144)));};

    }

  }

}



void test_FlashPatternForTwoLeds(void)

{

  MP_EnableMainCircuitPower_CMockIgnore();



  const uint8_t greenLedOnCount = 3;

  const uint8_t greenLedOffCount = 5;

  const uint8_t orangeLedOnCount = 7;

  const uint8_t orangeLedOffCount = 11;



  UI_SetLED(LD_GREEN_E, greenLedOnCount, greenLedOffCount);

  UI_SetLED(LD_ORANGE_E, orangeLedOnCount, orangeLedOffCount);



  for (uint32_t ticks = 0; ticks < 50; ticks++)

  {

    UI_UpdateLEDs();



    UnityAssertEqualNumber((_U_SINT)(((ticks % (greenLedOnCount + greenLedOffCount) < greenLedOnCount))), (_U_SINT)((isGreenSet)), (

   ((void *)0)

   ), (_U_UINT)(165), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)(((ticks % (orangeLedOnCount + orangeLedOffCount) < orangeLedOnCount))), (_U_SINT)((isOrangeSet)), (

   ((void *)0)

   ), (_U_UINT)(166), UNITY_DISPLAY_STYLE_INT);







  }

}
