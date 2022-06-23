/**
 * @file ndpa_tools.h
 * @author rzeller, voccoto Ltd
 * @brief Definitions for ndpa_tools.c
 * @version 0.3
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __NDPA_TOOLS_H__
#define __NDPA_TOOLS_H__

#include <float.h>
#include "ndpa.h"

/* Exported functions */
fptype vmax(fptype*, int, int*);
fptype median(fptype*, int);
void conv(fptype*, fptype*, fptype*, int, int, fptype*, int*);
void interpolate_scan(void);
void find_ac_peak(fptype*, fptype, int, int*, int*);
int update_average(fptype med, fptype*, int*);
void find_pc_peak_candidates(int, int*);
void find_pc_peak(fptype, int, int, fptype*, int*, fptype*);

#endif
