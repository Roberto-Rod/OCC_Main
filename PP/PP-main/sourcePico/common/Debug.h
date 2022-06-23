/*****************************************************************************
 *   File        : Debug.h
 *
 *   Description : Debug macros mapping.
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

#ifndef PICOONBOARD_DEBUG_H
#define PICOONBOARD_DEBUG_H

/*
 * Debug print is disabled. To print debug message to UART, add the following #define below:
 * #define ENABLE_DEBUG_PRINT
*/

#define ENABLE_DEBUG_PRINT

#include "PaTypes.h"

#if defined(ENABLE_DEBUG_PRINT) && defined(UNIT_TEST)
#include <stdio.h>
#define DEBUG_PRINT(arguments) (printf arguments)
#else
#define DEBUG_PRINT(arguments) ((void)0)
#endif  //ifdef ENABLE_DEBUG_PRINT


#endif //PICOONBOARD_DEBUG_H
