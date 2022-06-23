/*****************************************************************************
 *   File        : Assert.c
 *
 *   Description: Implementation of test Assert interface.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Occuity Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2022 Occuity Ltd.
 * 
 *************************************************************************** */

#include "unity.h"

void Assert(const char *expr, const char *func, const uint32_t line, int numCalls)
{
  printf("Assert raised at %s[%d] on test: %s\n", func, line, expr);
  TEST_ABORT(); //emulate program abortion
}