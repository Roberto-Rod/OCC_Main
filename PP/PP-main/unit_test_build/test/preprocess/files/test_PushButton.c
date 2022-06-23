#include "PushButton.h"
#include "pic16lf1509.h"
#include "unity.h"


void setUp()

{

  PORTAbits.RA5 = 0;

}



void tearDown()

{}



void test_IsPressedReadRA5(void)

{

  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(33)));};



  PORTAbits.RA5 = 1;

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(36)));};

}



void test_HasDepressedForDurationIncrementWhenButtonIsDepressed()

{

  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(42)));};

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(43)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PushButton_GetDepressedTickCount())), (

 ((void *)0)

 ), (_U_UINT)(44), UNITY_DISPLAY_STYLE_INT);

}



void test_DepressedCountIsResetWhenButtonIsReleased()

{

  PORTAbits.RA5 = 1;

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(50)));};

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((PushButton_GetDepressedTickCount())), (

 ((void *)0)

 ), (_U_UINT)(51), UNITY_DISPLAY_STYLE_INT);



  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(53)));};

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((PushButton_GetDepressedTickCount())), (

 ((void *)0)

 ), (_U_UINT)(54), UNITY_DISPLAY_STYLE_INT);



  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(57)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PushButton_GetDepressedTickCount())), (

 ((void *)0)

 ), (_U_UINT)(58), UNITY_DISPLAY_STYLE_INT);

}



void test_HasDepressedForDuration(void)

{

  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(64)));};





  PORTAbits.RA5 = 1;

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(68)));};





  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(71)));};





  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(74)));};







  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(78)));};





  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((PushButton_GetDepressedTickCount())), (

 ((void *)0)

 ), (_U_UINT)(81), UNITY_DISPLAY_STYLE_INT);





  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(85)));};



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((PushButton_GetDepressedTickCount())), (

 ((void *)0)

 ), (_U_UINT)(87), UNITY_DISPLAY_STYLE_INT);



}



void test_PushButtonStuckDoesNotRegisterAsLongPress(void)

{

  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(94)));};





  PORTAbits.RA5 = 1;

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(98)));};



  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(100)));};



  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(102)));};



  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(104)));};







  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(108)));};







  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(113)));};





  PORTAbits.RA5 = 1;

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(117)));};



}



void test_IfPushButtonIsNotReleaseAfterInitNotPressEventIsRegistered(void)

{



  PORTAbits.RA5 = 1;

  PushButton_ResetEvent();



  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(127)));};





  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(130)));};



}



void test_PressEventStartsWithReleaseState(void)

{



  PORTAbits.RA5 = 1;

  PushButton_ResetEvent();





  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(142)));};







  PORTAbits.RA5 = 1;

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(147)));};





  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(150)));};



}



void test_ShortPressRequiresMoreThanTwoTicks(void)

{

  PushButton_ResetEvent();



  PORTAbits.RA5 = 0;

  if (!(PushButton_IsPressed())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(159)));};

  if (!(PushButton_IsShortPress())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(160)));};



  PORTAbits.RA5 = 1;

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(163)));};

  if (!(PushButton_IsShortPress())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(164)));};

  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(165)));};

  if (!(PushButton_IsShortPress())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(166)));};





  if ((PushButton_IsPressed())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(169)));};

  if ((PushButton_IsShortPress())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(170)));};



}
