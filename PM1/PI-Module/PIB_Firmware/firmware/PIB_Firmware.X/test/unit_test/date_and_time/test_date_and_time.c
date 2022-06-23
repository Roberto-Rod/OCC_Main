/* ************************************************************************** */
/** @file test_date_and_time.c
 *
 *  @brief Unit tests verifying date_and_time.c module.
 *
 *  @copyright Occuity Limited (c) 2022
 */
/* ************************************************************************** */

#ifndef TEST_FILE_C /* Guard against accidental multiple inclusion */
#define TEST_FILE_C

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* Library containing the test harness */
#include "unity.h" 

/* ************************************************************************** */
/* Include additional files to compile here                                   */
/* ************************************************************************** */
//TEST_FILE("file_to_compile.c")

/* ************************************************************************** */
/* Include files to test here                                                 */
/* ************************************************************************** */
#include "date_and_time.h"


/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */
/** 
 * @brief            This function contains code to be executed before unit
 *                   tests.
 *
 * @note             For testing <filename>.c nothing needs to be set up. 
 */
/* ************************************************************************** */
void setUp(void)
{
}

/* ************************************************************************** */
/** 
 * @brief            This function contains code to be executed after unit
 *                   tests.
 *
 * @note             For testing <filename>.c nothing needs to be set up. 
 */
/* ************************************************************************** */
void tearDown(void)
{
}

/* ************************************************************************** */
/** 
 * @brief            Function tested: example()
 *
 * @test             Asserts 42=42
 *
 * @note             None
 */
/* ************************************************************************** */
void test_isLeapYear_Returns_True_When_YR_2004(void)
{
	// TEST_ASSERT_TRUE(isLeapYear(2004));
	//UnityPrint("2004 is a Leap Year");
	if (!isLeapYear(2004)) {TEST_FAIL_MESSAGE("Incorrect result, 2004 is a Leap Year.");}
}

void test_isLeapYear_Returns_True_When_YR_2000(void)
{
	if (!isLeapYear(2000)) {TEST_FAIL_MESSAGE("Incorrect result, 2000 is a Leap Year.");}
}

void test_isLeapYear_Returns_False_When_YR_1999(void)
{
	if (isLeapYear(1999)) {TEST_FAIL_MESSAGE("Incorrect result, 1999 is NOT a Leap Year.");}
}

void test_isLeapYear_Returns_False_When_YR_1009(void)
{
	if (isLeapYear(1009)) {TEST_FAIL_MESSAGE("Incorrect result, 1009 is NOT a Leap Year.");}
}

void test_dayOfTheWeek_Returns_Monday(void)
{
	const char expected = '1';
	char result;

	result = dayOfTheWeek(2022,'6','6');
	printf("dayOfTheWeek returned: %c", result);

    if (result != expected)
	{
		TEST_FAIL_MESSAGE("Incorrect result, should return Monday.");
	}

}

void test_getNumberOfDaysInMonth_Returns_31_When_May_2022(void)
{
	int expected = 31;
	int result = 0;

	result = getNumberOfDaysInMonth(5,2022);

	if (result != expected)
	{
		TEST_FAIL_MESSAGE("Incorrect result, should return 31.");
	}

}

void test_getNumberOfDaysInMonth_Returns_30_When_June_2022(void)
{
	int expected = 30;
	int result = 0;

	result = getNumberOfDaysInMonth(6,2022);

	if (result != expected)
	{
		TEST_FAIL_MESSAGE("Incorrect result, should return 30.");
	}

}

void test_getNumberOfDaysInMonth_Returns_28_When_February_2022(void)
{
	int expected = 28;
	int result = 0;

	result = getNumberOfDaysInMonth(2,2022);

	if (result != expected)
	{
		TEST_FAIL_MESSAGE("Incorrect result, should return 28.");
	}

}

void test_getNumberOfDaysInMonth_Returns_29_When_February_2004(void)
{
	int expected = 29;
	int result = 0;

	result = getNumberOfDaysInMonth(2,2004);

	if (result != expected)
	{
		TEST_FAIL_MESSAGE("Incorrect result, should return 29.");
	}

}

void test_getNumberOfDaysInMonth_Returns_29_When_February_2000(void)
{
	int expected = 29;
	int result = 0;

	result = getNumberOfDaysInMonth(2,2000);

	if (result != expected)
	{
		TEST_FAIL_MESSAGE("Incorrect result, should return 29.");
	}

}

#endif //TEST_FILE_C
