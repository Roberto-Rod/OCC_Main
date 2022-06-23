/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    test.c

  @Summary
    Test code.

  @Description
    Test code goes here to keep it out of the main files.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "definitions.h"
#include "test.h"

//#define ENABLE_DEBUG

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */



/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */




/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/* Test task called in the main task loop */
void Test_Task(void)
{
#ifdef ENABLE_DEBUG
    static uint32_t loop_counter = 0;

    loop_counter++;

    if (loop_counter > 10000)
    {
        loop_counter = 0;
        //test_sqi_fram();
        #ifdef PIC_COMMS_TEST
        p2pic_communications_test();
        #endif
    }
#endif
}

/* *****************************************************************************
 End of File
 */
