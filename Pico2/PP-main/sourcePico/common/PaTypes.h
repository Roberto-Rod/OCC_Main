/*****************************************************************************
 *   File        : PaTypes.h
 *
 *   Description : Header for defining variable types. This project uses some
 * machine generated source code that follows the MPLAB standards (e.g. uint8_t).
 * As result it has been decided to adopt the MPLAB standards and this file
 * redefines only those types that for some reason do not follow the "_t" naming
 * convention
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

#ifndef PATYPES_H
#define	PATYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <stdio.h>

/******************************************************************************
*  Type definitions
******************************************************************************/


typedef float float32_t;

/* making stdbool.h conforming with PA coding standards (i.e. _t for type, CAPITAL letters for defines) */
typedef bool bool_t;

#define TRUE (bool_t) true
#define FALSE (bool_t) false

/* Limits */

#endif	/* PATYPES_H */

