/* ************************************************************************** */
/** @file test_m_npda_066.c
 *
 *  @brief Module tests verifying npda.c module.
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
#include "init_minimum_plus_timer.h" 
/* Library containing the test harness. */
#include "unity.h" 
/* Header file for memory monitoring. */
#include "stack_monitoring.h"

/* ************************************************************************** */
/* Include additional files to compile here                                   */
/* ************************************************************************** */
//TEST_FILE("file_to_compile.c")

/* ************************************************************************** */
/* Include files to test here                                                 */
/* ************************************************************************** */
#include "pdab_types.h"
#include "test_m_npda_SB-2020-09-18-10-37-11-15-300-Raw_cal_02.h"
#include "test_m_npda_SB-2020-09-18-10-38-18-15-300-Raw_cal_02.h"
#include "npda.h"
#include "npda_tools.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/** This enum variable ensures that the stack_monitoring code has been executed once */
typedef enum {FIRST, CONSECUTIVE} run_time;
/** This variable stores amount of unused stack (in bytes) */
unsigned int unused_stack;

/** This variable stores SCAN_BUFFER data, which is output from the NPDA alogithm  */
//_SCAN_BUFFER result;
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
 * @note             For testing npda.c, memory monitoring is enabled. 
 */
/* ************************************************************************** */
void setUp(void)
{
    static run_time run_time = FIRST;
    if(run_time == FIRST)
    {
        MEMORY_OBJ mem_state;
        stack_monitoring_init(&mem_state);
        unused_stack = stack_monitoring_measure_unused_stack();
        UnityPrint("TEST FILE: test_m_npda.c: ");
        UnityPrint("Data mem usage: ");
		  UnityPrintNumberUnsigned(mem_state.data_size);
        UnityPrint("b. Heap size: ");
		  UnityPrintNumberUnsigned(mem_state.heap_size);
        UnityPrint("b. Stack size: ");
		  UnityPrintNumberUnsigned(mem_state.stack_size);
        UnityPrint("b of which ");
		  UnityPrintNumberUnsigned(mem_state.stack_size - unused_stack);
        UnityPrint("b are used. ");
		  
        run_time = CONSECUTIVE;
        
    }

}

/* ************************************************************************** */
/** 
 * @brief            This function contains code to be executed after unit
 *                   tests.
 *
 * @note             For testing npda.c nothing needs to be set up. 
 */
/* ************************************************************************** */
void tearDown(void)
{
}

/* ************************************************************************** */
/** 
 * @brief            Function tested: run_npda()
 *
 * @test             Runs run_npda() fuction and measures execution time, max
 *                   stack usage and whether peak separation is correct based on
 *                   data and calibration from test_m_npda_SB-2020-09-18-10-37-11-15-300-Raw_cal_02.h.
 *
 * @note             None
 */
/* ************************************************************************** */
void test_npda_SB_2020_09_18_10_37_11_15_300_Raw_cal_02(void)
{
    int iret;
    _SCAN_BUFFER result;
    unsigned int time;
    unsigned int stack_usage;
    
    unity_helper_tic();
    iret = run_npda( &scanData_SB_2020_09_18_10_37_11_15_300_Raw_cal_02, &result, cal_data_SB_2020_09_18_10_37_11_15_300_Raw_cal_02 );
    time = unity_helper_toc();
    stack_usage = unused_stack - stack_monitoring_measure_unused_stack();
    
    UnityPrint("TEST: run_npda: ");
    UnityPrint("Execution time: "); UnityPrintNumberUnsigned(time); UnityPrint("us");
    UnityPrint(", Max stack usage: "); UnityPrintNumberUnsigned(stack_usage); UnityPrint("bytes");
    UnityPrint(", iret: "); UnityPrintNumber(iret); UnityPrint(" vs "); UnityPrintNumber(expected_iret_SB_2020_09_18_10_37_11_15_300_Raw_cal_02);
    UnityPrint(", Thickness: "); UnityPrintFloat(CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Separation[0]); UnityPrint(" vs "); UnityPrintFloat(expected_cor_thickness_SB_2020_09_18_10_37_11_15_300_Raw_cal_02);
    UnityPrint(", Precision: "); UnityPrintFloat(CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Precision[0]); UnityPrint(" vs "); UnityPrintFloat(expected_cor_thickness_acuracy_SB_2020_09_18_10_37_11_15_300_Raw_cal_02);
    UnityPrint(", Blocks: "); UnityPrintFloat(result.Header.Blocks); UnityPrint(" vs "); UnityPrintFloat(expected_valid_blocks_SB_2020_09_18_10_37_11_15_300_Raw_cal_02);

    TEST_ASSERT_EQUAL_INT(expected_iret_SB_2020_09_18_10_37_11_15_300_Raw_cal_02, iret);
    if(expected_iret_SB_2020_09_18_10_37_11_15_300_Raw_cal_02 != ERROR_TOO_FEW_BLOCKS && expected_iret_SB_2020_09_18_10_37_11_15_300_Raw_cal_02 != ERROR_PC_PEAKS_TOO_SMALL && expected_iret_SB_2020_09_18_10_37_11_15_300_Raw_cal_02 != ERROR_SPREAD_TOO_HIGH) {
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_cor_thickness_SB_2020_09_18_10_37_11_15_300_Raw_cal_02, CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Separation[0]);
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_cor_thickness_acuracy_SB_2020_09_18_10_37_11_15_300_Raw_cal_02, CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Precision[0]);
        TEST_ASSERT_EQUAL_INT(expected_valid_blocks_SB_2020_09_18_10_37_11_15_300_Raw_cal_02, result.Header.Blocks);
   }
}

/* ************************************************************************** */
/** 
 * @brief            Function tested: run_npda()
 *
 * @test             Runs run_npda() fuction and measures execution time, max
 *                   stack usage and whether peak separation is correct based on
 *                   data and calibration from test_m_npda_SB-2020-09-18-10-38-18-15-300-Raw_cal_02.h.
 *
 * @note             None
 */
/* ************************************************************************** */
void test_npda_SB_2020_09_18_10_38_18_15_300_Raw_cal_02(void)
{
    int iret;
    _SCAN_BUFFER result;
    unsigned int time;
    unsigned int stack_usage;
    
    unity_helper_tic();
    iret = run_npda( &scanData_SB_2020_09_18_10_38_18_15_300_Raw_cal_02, &result, cal_data_SB_2020_09_18_10_38_18_15_300_Raw_cal_02 );
    time = unity_helper_toc();
    stack_usage = unused_stack - stack_monitoring_measure_unused_stack();
    
    UnityPrint("TEST: run_npda: ");
    UnityPrint("Execution time: "); UnityPrintNumberUnsigned(time); UnityPrint("us");
    UnityPrint(", Max stack usage: "); UnityPrintNumberUnsigned(stack_usage); UnityPrint("bytes");
    UnityPrint(", iret: "); UnityPrintNumber(iret); UnityPrint(" vs "); UnityPrintNumber(expected_iret_SB_2020_09_18_10_38_18_15_300_Raw_cal_02);
    UnityPrint(", Thickness: "); UnityPrintFloat(CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Separation[0]); UnityPrint(" vs "); UnityPrintFloat(expected_cor_thickness_SB_2020_09_18_10_38_18_15_300_Raw_cal_02);
    UnityPrint(", Precision: "); UnityPrintFloat(CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Precision[0]); UnityPrint(" vs "); UnityPrintFloat(expected_cor_thickness_acuracy_SB_2020_09_18_10_38_18_15_300_Raw_cal_02);
    UnityPrint(", Blocks: "); UnityPrintFloat(result.Header.Blocks); UnityPrint(" vs "); UnityPrintFloat(expected_valid_blocks_SB_2020_09_18_10_38_18_15_300_Raw_cal_02);

    TEST_ASSERT_EQUAL_INT(expected_iret_SB_2020_09_18_10_38_18_15_300_Raw_cal_02, iret);
    if(expected_iret_SB_2020_09_18_10_38_18_15_300_Raw_cal_02 != ERROR_TOO_FEW_BLOCKS && expected_iret_SB_2020_09_18_10_38_18_15_300_Raw_cal_02 != ERROR_PC_PEAKS_TOO_SMALL && expected_iret_SB_2020_09_18_10_38_18_15_300_Raw_cal_02 != ERROR_SPREAD_TOO_HIGH) {
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_cor_thickness_SB_2020_09_18_10_38_18_15_300_Raw_cal_02, CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Separation[0]);
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_cor_thickness_acuracy_SB_2020_09_18_10_38_18_15_300_Raw_cal_02, CORNEA_REFRACTIVE_IDX*result.Header.Measurement.Precision[0]);
        TEST_ASSERT_EQUAL_INT(expected_valid_blocks_SB_2020_09_18_10_38_18_15_300_Raw_cal_02, result.Header.Blocks);
   }
}

#endif //TEST_FILE_C
