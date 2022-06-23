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
bool is_increasing_monotonically(const fptype*, int);
uint16_t median_uint16_t(uint16_t*, int);
fptype median(fptype*, int, fptype*);
void conv(fptype*, fptype*, fptype*, int, int, fptype*, int*);
int interpolate_scan(fptype*, uint16_t*, int, fptype*, int);
int find_ac_peak(fptype*, int, fptype, int, int*, int *);
int update_average(fptype*, int, fptype, int, uint16_t*);
void find_pc_peak_candidates(fptype*, uint16_t, int, int*);
int find_pc_peak(fptype*, uint16_t, fptype, int, int, int*, fptype*, fptype*);
fptype vmax(fptype*, int, int*);
int transform_to_uniform_distribution(fptype*, int, fptype, fptype*, int*);

#ifdef TEST
    #ifndef STATIC
        #define STATIC
    #endif
    
    // Static functions, only need to define as non-static if used outside the module dureing testing
    fptype vmin(fptype*, int, int*);
    int nearest_neighbour(fptype, int, fptype*, int len);
    void average_incremental(fptype*, int, int, int, uint16_t*);

    int find_active_points(fptype*, int, fptype, byte*);
    int polyfit2(fptype*, int, byte*, int, double*);
    int calc_parabola_max(double*, int*);
    int find_ac_quad(fptype*, int, int, fptype, int*);
#else
    #ifndef STATIC
        #define STATIC static
    #endif
#endif

#endif
