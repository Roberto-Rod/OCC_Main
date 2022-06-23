/**
 * @file npda_tools.h
 * @author rzeller, voccoto Ltd
 * @brief Definitions for npda_tools.c
 * @version 0.3
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __NPDA_TOOLS_H__
#define __NPDA_TOOLS_H__

#include <float.h>
#include "npda.h"

/* Exported functions */
void interpolate_scan(void);

#define STATIC 

STATIC inline int nearest_neighbour(fptype, int, fptype*);
void interpolate_scan2(void);


#endif
