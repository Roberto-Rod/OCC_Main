/* ************************************************************************** */
/** @file test_example.c
 *
 *  @brief Unit tests verifying <filname>.c module.
 *
 *  @copyright Occuity Limited (c) 2020
 */
/* ************************************************************************** */

#ifndef TEST_FILE_C /* Guard against accidental multiple inclusion */
#define TEST_FILE_C

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* Header file for selective initialisation of hardware modules. */
#include "init_minimum.h" 
/* Library containing the test harness */
#include "unity.h" 

/* ************************************************************************** */
/* Include additional files to compile here                                   */
/* ************************************************************************** */
//TEST_FILE("file_to_compile.c")

/* ************************************************************************** */
/* Include files to test here                                                 */
/* ************************************************************************** */
//#include "file_to_test.h"

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
void test_example(void)
{
	TEST_ASSERT_EQUAL_INT(42,42);
}

void test_example1(void)
{
	TEST_ASSERT_EQUAL_INT(1,4);
}

void test_example2(void)
{
	TEST_ASSERT_EQUAL_INT(0,1);
}

#endif //TEST_FILE_C
