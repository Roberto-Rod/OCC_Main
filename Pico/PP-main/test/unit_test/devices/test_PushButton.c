/*****************************************************************************
 *   File        : test_PushButton.c
 *
 *   Description: Source Code for test of Push Button.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018 - 2021 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "unity.h"
#include "pic16lf1509.h"
#include "PushButton.h"

void setUp()
{
  PORTAbits.RA5 = 0;
}

void tearDown()
{}

void test_IsPressedReadRA5(void)
{
  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());

  PORTAbits.RA5 = 1;
  TEST_ASSERT_TRUE(PushButton_IsPressed());
}

void test_HasDepressedForDurationIncrementWhenButtonIsDepressed()
{
  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  TEST_ASSERT_EQUAL_INT(0, PushButton_GetDepressedTickCount());
}

void test_DepressedCountIsResetWhenButtonIsReleased()
{
  PORTAbits.RA5 = 1;
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  TEST_ASSERT_EQUAL_INT(1, PushButton_GetDepressedTickCount());

  TEST_ASSERT_TRUE(PushButton_IsPressed());
  TEST_ASSERT_EQUAL_INT(2, PushButton_GetDepressedTickCount());

  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  TEST_ASSERT_EQUAL_INT(0, PushButton_GetDepressedTickCount());
}

void test_HasDepressedForDuration(void)
{
  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));

  PORTAbits.RA5 = 1;
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));

  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));

  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));

  //the pushbutton module has gone over 3 periods of ticks at the next evaluation.
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_TRUE(PushButton_HasDepressedForDuration(3));

  TEST_ASSERT_EQUAL_INT(4, PushButton_GetDepressedTickCount());

  //depressed reset to zero
  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));
  TEST_ASSERT_EQUAL_INT(0, PushButton_GetDepressedTickCount());

}

void test_PushButtonStuckDoesNotRegisterAsLongPress(void)
{
  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));

  PORTAbits.RA5 = 1;  //button pressed and hold
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_TRUE(PushButton_HasDepressedForDuration(3));  //should register long press here

  //button stuck
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(3));

  //button released
  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());

  //button pressed again
  PORTAbits.RA5 = 1;
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(1));
}

void test_IfPushButtonIsNotReleaseAfterInitNotPressEventIsRegistered(void)
{
  //simulate stuck button
  PORTAbits.RA5 = 1;
  PushButton_ResetEvent();

  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(1));

  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(1));
}

void test_PressEventStartsWithReleaseState(void)
{
  //button is pressed
  PORTAbits.RA5 = 1;
  PushButton_ResetEvent();

  //Release button required
  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(1));

  //Before press is registered and counted.
  PORTAbits.RA5 = 1;
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_FALSE(PushButton_HasDepressedForDuration(1));

  TEST_ASSERT_TRUE(PushButton_IsPressed());
  //TEST_ASSERT_TRUE(PushButton_HasDepressedForDuration(1));
}

void test_ShortPressRequiresMoreThanTwoTicks(void)
{
  PushButton_ResetEvent();

  PORTAbits.RA5 = 0;
  TEST_ASSERT_FALSE(PushButton_IsPressed());
  TEST_ASSERT_FALSE(PushButton_IsShortPress());

  PORTAbits.RA5 = 1;
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  TEST_ASSERT_FALSE(PushButton_IsShortPress());
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  TEST_ASSERT_FALSE(PushButton_IsShortPress());
  // More than two ticks are required to detect a short button press
  // to guarantee that a minimum of 200ms have passed
  TEST_ASSERT_TRUE(PushButton_IsPressed());
  TEST_ASSERT_TRUE(PushButton_IsShortPress());

}