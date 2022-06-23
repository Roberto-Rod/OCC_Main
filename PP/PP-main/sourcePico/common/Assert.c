/*****************************************************************************
 *   File        : Assert.c
 *
 *   Description : Implementation of Assert interface to verifying conditions
 * during debug.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "Assert.h"

/*lint -esym(715, expr, file, line) Suppress: Symbol 'expr', 'file', 'line' not referenced. */
void Assert(const char *expr, const char *file, const uint16_t line)
{
  //put the program in an infinite loop in debug loop. If in unit test, print out the assert location.
  //This code is not compiled in release mode.

#ifdef UNIT_TEST
  printf("Assert at line %lu: %s - %s", line, file, expr);
  return;
#endif

#ifdef __XC   //indicates MPLAB XC compiler for Microchip is being used
  //hang the main thread here and wait for watchdog to expire to rescue
  while(TRUE)
  {
    //forever loop.
    ;
  }
#endif
}
