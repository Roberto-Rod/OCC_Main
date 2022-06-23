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

#ifndef PICOONBOARD_ASSERT_H
#define PICOONBOARD_ASSERT_H

#include "PaTypes.h"

#if defined(__DEBUG) || defined(UNIT_TEST)
//trap ASSERT statement in debug or UNIT TEST mode
#define ASSERT(expr) ((expr) ? (void)0 : Assert( #expr, __FILE__, ((uint16_t) __LINE__)))
#else
//ignore ASSERT in release mode
#define ASSERT(expr)  (void)0
#endif

void Assert(const char *expr, const char *file, const uint16_t line);


#endif //PICOONBOARD_ASSERT_H
