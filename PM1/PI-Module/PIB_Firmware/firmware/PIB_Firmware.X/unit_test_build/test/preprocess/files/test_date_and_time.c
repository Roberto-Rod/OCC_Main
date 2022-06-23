#include "date_and_time.h"
#include "unity.h"
void setUp(void)

{

}

void tearDown(void)

{

}

void test_isLeapYear_Returns_True_When_YR_2004(void)

{





 if (!isLeapYear(2004)) {UnityFail( (("Incorrect result, 2004 is a Leap Year.")), (_U_UINT)(79));}

}



void test_isLeapYear_Returns_True_When_YR_2000(void)

{

 if (!isLeapYear(2000)) {UnityFail( (("Incorrect result, 2000 is a Leap Year.")), (_U_UINT)(84));}

}



void test_isLeapYear_Returns_False_When_YR_1999(void)

{

 if (isLeapYear(1999)) {UnityFail( (("Incorrect result, 1999 is NOT a Leap Year.")), (_U_UINT)(89));}

}



void test_isLeapYear_Returns_False_When_YR_1009(void)

{

 if (isLeapYear(1009)) {UnityFail( (("Incorrect result, 1009 is NOT a Leap Year.")), (_U_UINT)(94));}

}



void test_dayOfTheWeek_Returns_Monday(void)

{

 const char expected = '1';

 char result;



 result = dayOfTheWeek(2022,'6','6');

 printf("dayOfTheWeek returned: %c", result);



    if (result != expected)

 {

  UnityFail( (("Incorrect result, should return Monday.")), (_U_UINT)(107));

 }



}



void test_getNumberOfDaysInMonth_Returns_31_When_May_2022(void)

{

 int expected = 31;

 int result = 0;



 result = getNumberOfDaysInMonth(5,2022);



 if (result != expected)

 {

  UnityFail( (("Incorrect result, should return 31.")), (_U_UINT)(121));

 }



}



void test_getNumberOfDaysInMonth_Returns_30_When_June_2022(void)

{

 int expected = 30;

 int result = 0;



 result = getNumberOfDaysInMonth(6,2022);



 if (result != expected)

 {

  UnityFail( (("Incorrect result, should return 30.")), (_U_UINT)(135));

 }



}



void test_getNumberOfDaysInMonth_Returns_28_When_February_2022(void)

{

 int expected = 28;

 int result = 0;



 result = getNumberOfDaysInMonth(2,2022);



 if (result != expected)

 {

  UnityFail( (("Incorrect result, should return 28.")), (_U_UINT)(149));

 }



}



void test_getNumberOfDaysInMonth_Returns_29_When_February_2004(void)

{

 int expected = 29;

 int result = 0;



 result = getNumberOfDaysInMonth(2,2004);



 if (result != expected)

 {

  UnityFail( (("Incorrect result, should return 29.")), (_U_UINT)(163));

 }



}



void test_getNumberOfDaysInMonth_Returns_29_When_February_2000(void)

{

 int expected = 29;

 int result = 0;



 result = getNumberOfDaysInMonth(2,2000);



 if (result != expected)

 {

  UnityFail( (("Incorrect result, should return 29.")), (_U_UINT)(177));

 }



}
