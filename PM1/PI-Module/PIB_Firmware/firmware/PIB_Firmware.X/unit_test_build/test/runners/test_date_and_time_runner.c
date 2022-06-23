/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_isLeapYear_Returns_True_When_YR_2004(void);
extern void test_isLeapYear_Returns_True_When_YR_2000(void);
extern void test_isLeapYear_Returns_False_When_YR_1999(void);
extern void test_isLeapYear_Returns_False_When_YR_1009(void);
extern void test_dayOfTheWeek_Returns_Monday(void);
extern void test_getNumberOfDaysInMonth_Returns_31_When_May_2022(void);
extern void test_getNumberOfDaysInMonth_Returns_30_When_June_2022(void);
extern void test_getNumberOfDaysInMonth_Returns_28_When_February_2022(void);
extern void test_getNumberOfDaysInMonth_Returns_29_When_February_2004(void);
extern void test_getNumberOfDaysInMonth_Returns_29_When_February_2000(void);


/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_date_and_time.c");
  RUN_TEST(test_isLeapYear_Returns_True_When_YR_2004, 75);
  RUN_TEST(test_isLeapYear_Returns_True_When_YR_2000, 82);
  RUN_TEST(test_isLeapYear_Returns_False_When_YR_1999, 87);
  RUN_TEST(test_isLeapYear_Returns_False_When_YR_1009, 92);
  RUN_TEST(test_dayOfTheWeek_Returns_Monday, 97);
  RUN_TEST(test_getNumberOfDaysInMonth_Returns_31_When_May_2022, 112);
  RUN_TEST(test_getNumberOfDaysInMonth_Returns_30_When_June_2022, 126);
  RUN_TEST(test_getNumberOfDaysInMonth_Returns_28_When_February_2022, 140);
  RUN_TEST(test_getNumberOfDaysInMonth_Returns_29_When_February_2004, 154);
  RUN_TEST(test_getNumberOfDaysInMonth_Returns_29_When_February_2000, 168);

  return (UnityEnd());
}