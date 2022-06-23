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
#include "scan_processing.h"
#include "pdab_types.h"
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
void test_Scan_Selection_success(void)
{
    _MEASUREMENT measurement;
    _SCAN_SETTINGS settings;
    
    measurement.Count = 2;
    measurement.Peak[0].Amplitude = 60000;
    settings.peak_thresholds[0] = 50000;
    measurement.Peak[0].Position = 700U;
    measurement.Peak[1].Amplitude = 5000;
    settings.peak_thresholds[1] = 4000;
    measurement.Peak[0].FWHM = 55;
    settings.fwhm_limits[0] = 35;
    settings.fwhm_limits[1] = 75;
    measurement.Peak[1].Position = 1200;
    settings.separation_limits[0] = 300;
    settings.separation_limits[1] = 800;
    
    bool res;
    
    res = Scan_Selection(&measurement , &settings);
    
    
    
    
    
	TEST_ASSERT_TRUE(res);
}

#endif //TEST_FILE_C
