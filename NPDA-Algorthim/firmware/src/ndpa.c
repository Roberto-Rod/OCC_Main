/**
 * @file ndpa.c
 * @author rzeller, voccoto Ltd
 * @brief Occuity NDPA main interface module.
 * @version 0.3
 * @date 2020-09-17
 * 
 * @copyright Copyright (c) 2020
 * 
 * @note To generate documentation use the command "doxygen ndpa-dox.cfg"
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ndpa.h"
#include "ndpa_tools.h"

#if ALLOCATE_X0Y0
    /** @brief Calibration data (scan position data). Control writes into this buffer. Updated once in a block/measurement/(from boot)? */
    fptype __ndpa_x0[MAX_POSITIONS];
    /** @brief Scan measurement data (2 byte word for each value). Control writes into this buffer. Updated once for each scan. */
    word __ndpa_y0[MAX_WINDOW_SIZE];
#else
    /** @brief Calibration data (scan's position data). Control writes into this buffer. Updated once in a block. Updated once in a block/measurement/(from boot)? */
    fptype *__ndpa_x0 = NULL;
    /** @brief Scan measurement data (2 byte word for each value). Control writes into this buffer. Content updated once for each scan. */
    word *__ndpa_y0 = NULL;
#endif

#if USE_RESTRICTED_SCANS
    /** @brief Scan data has been pre-processed to reduce size. Offset array contains the starting positions of these MAX_WINDOW_SIZE size packets within __ndpa_x0 */
    word __ndpa_offsets[MAX_SCANS];
    /** @brief __ndpa_x0 offsetted for current scan = __ndpa_x0 + current_scan_offset */
    fptype *__ndpa_offsetted_x0;
    #if USE_INTERPOLATED_POS_BUFFER
        /** @brief Current scan's interpolated data from x0. NDPA writes this. Not used if using __ndpa_x_start instead */
        fptype __ndpa_x[MAX_POSITIONS];
        /** @brief __ndpa_x offsetted for current scan */
        fptype *__ndpa_offsetted_x;
    #else
        /** @brief Interpolated position for the beginning of the current data window in __ndpa_y0. Based on the offset */
        fptype __ndpa_offsetted_x_start;
    #endif
#else
    #if USE_INTERPOLATED_POS_BUFFER
        /** @brief Current scan's interpolated data from x0. NDPA writes this. Not used if using __ndpa_x_start instead */
        fptype __ndpa_x[MAX_POSITIONS];
    #endif
#endif
/** @brief Interpolated scan data from __ndpa_y0. Written by NDPA. Updated once for each scan. */
fptype __ndpa_y[MAX_WINDOW_SIZE];
/** @brief Accumulating average of AC alligned __ndpa_y values. Written by NDPA. Updated once for each scan. */
fptype __ndpa_avg[MAX_WINDOW_SIZE];
/** @brief Convoluted scan data. Written by NDPA. Updated once for each block. @warning "Recycles" the __ndpa_y buffer. */
fptype *__ndpa_conv = NULL;
/** @brief Helper vector used in interpolation. */
fptype __ndpa_intercept[MAX_WINDOW_SIZE];
/** @brief Helper vector used in interpolation. */
fptype __ndpa_slope[MAX_WINDOW_SIZE];
/** @brief Helper buffer for the median() function. Written by NDPA. Used in multiple steps after interpolation. @warning "Recycles" the __ndpa_intercept buffer. */
fptype *__ndpa_median = NULL;
/** @brief Helper buffer used in find_ac_quad() to mark points used in quadratic fitting. */
byte __ndpa_hhw[MAX_AC_HHW];
/** @brief Used by find_pc_peak_candidates() to store all PC peak candidate indexes. */
int __ndpa_pcpc[MAX_PCPC];

/** @brief Current block index within a measurement */
unsigned int __block_cnt = 0;
/** @brief Current scan index within a block */
unsigned int __scan_cnt = 0;
/** @brief Number of valid scans within a block. Can be different from __scan_cnt if using restricted scans and the offset for the scan is 0 or otherwise discarded */
unsigned int __valid_scans = 0;
/** @brief Size of __ndpa_x and y after interpolation */
int __interpolated_size = 0;
/** @brief Maximum value in the averaged data __ndpa_avg */
fptype __avg_maxval = 0.0;
/** @brief Index of maximum value in the averaged data __ndpa_avg */
int __avg_maxpos = -1;
/** @brief Value of __ndpa_x[0] */
fptype __ndpa_x_start = 0.0;

/** @brief AC position values for each block */
fptype __AC_position[MAX_BLOCKS];
/** @brief AC height values for each block */
fptype __AC_height[MAX_BLOCKS];
/** @brief PC weight values for each block */
fptype __PC_weight[MAX_BLOCKS];
/** @brief Corneal thickness values for each block */
fptype __thickness[MAX_BLOCKS];
/** @brief Helper used in aggregated thickness calculation in ndpa_measurement_end(). */
fptype __madse[MAX_BLOCKS];

/**
 * @brief Starting a new measurement. Call before ndpa_block_start() for the first block.
 * 
 * @return int 0 on success
 */
int ndpa_measurement_start(void) {
    __block_cnt = 0;
    return 0;
}

/**
 * @brief End of measurement. Returning aggregated corneal thickness, etc
 * 
 * @return int on success
 */
int ndpa_measurement_end(void) {
    int b;
    fptype mt, mmt; /* Medians */
    int valid_blocks = 0;
    fptype valid_blocks_perc; /* Percentage of valid blocks (pp) */
    int outlier_blocks = 0;
    fptype outlier_blocks_perc; /* (qq) */
    fptype weighted_thickness = 0.0; /* Weighted mean thickness (mean_w) */
    fptype weighted_thickness_sd = 0.0; /* Weighted mean thickness standard deviation (sd_w) */
    fptype weight_sum = 0.0;
    fptype max_height = -FPTYPE_MAX; /* Max AC height */

    for (b=0; b<__block_cnt; b++) {
        if (__AC_height[b] > max_height) {
            max_height = __AC_height[b];
        }
    }
    /* Removing blocks under the threshold. New size in valid_blocks, reusing existing buffers */
    for (b=0; b<__block_cnt; b++) {
        if (__AC_height[b] >= 0.2*max_height) {
            __thickness[valid_blocks] = __thickness[b];
            __PC_weight[valid_blocks] = __PC_weight[b];
            valid_blocks ++;
        }
    }
    valid_blocks_perc = 100.0 * valid_blocks/MAX_BLOCKS;

printf("\tNumber of valid blocks is %d (%f %%).\n", valid_blocks, valid_blocks_perc);
    if (valid_blocks == 0) {
        /* No valid measurements in all blocks */
        return 900;
    }

    mt = median(__thickness, valid_blocks);
    for (b=0; b<valid_blocks; b++) {
        __madse[b] = fabs(__thickness[b] - mt);
    }
    mmt = median(__madse, valid_blocks);
    for (b=0; b<valid_blocks; b++) {
        if (fabs(__thickness[b] - mt) > 1.5*mmt) {
            __thickness[b] = mt;
            __PC_weight[b] = 0.0;
            outlier_blocks ++;
printf("\t\tOutlier block %d\n", b);
        }
        else {
            weighted_thickness += __PC_weight[b] * __thickness[b];
            weight_sum += __PC_weight[b];
        }
    }
    weighted_thickness /= weight_sum;
    outlier_blocks_perc = 100.0 * outlier_blocks/MAX_BLOCKS;
printf("\tNumber of outlier blocks is %d (%f %%).\n", outlier_blocks, outlier_blocks_perc);

    for (b=0; b<valid_blocks; b++) {
        weighted_thickness_sd += __PC_weight[b] * pow(__thickness[b] - weighted_thickness, 2);
    }
    weighted_thickness_sd /= weight_sum;
    weighted_thickness_sd = sqrt(weighted_thickness_sd);


printf("\tWeighted mean thickness %f um.\n", 1000.0*weighted_thickness);
printf("\tWeighted mean thickness %f um standard deviation.\n", 1000.0*weighted_thickness_sd);

    return 0;
}

/**
 * @brief Starting new measurement block
 * 
 * @return int 0 on success
 */
int ndpa_block_start(void) {
    __scan_cnt = 0;
    __valid_scans = 0;
    return 0;
}

/**
 * @brief End of measurement block processing. Finding AC and PC peaks in the averaged data.
 * 
 * @return int
 * @return 0 - Success
 * @return 100 - No PC peak candidates found! Discarding block
 * @return 101 - No valid scans within the block! Discarding block
 */
int ndpa_block_end(void) {
    int iret = 0;
    int q1, q2; /* AC Peak left-right in __ndpa_avg */
    int AC_idx; /* AC peak index */
    int pc_peak_cnt = 0; /* Number of PC candidates found */

    if (__valid_scans > 0) {
#if ASSUME_VARIABLE_SIZE_BLOCKS
        /* Calculating  */
        __avg_maxval = vmax(__ndpa_avg, __interpolated_size, &__avg_maxpos);
#endif
        
#if CONVOLVE_WITH_AC_PEAK
        /* AC peak in averaged data */
        find_ac_peak(__ndpa_avg, __avg_maxval, __avg_maxpos, &q1, &q2);

        /* Convolving averaged data with AC peak */
        /* NOTE: RZ: In the original matlab version find_ac_peak() would have been called to determine the AC position based on the index of the maximum value. Conv can already find the max, so we don't need to call find_ac_peak() */
        conv(__ndpa_conv, __ndpa_avg, __ndpa_avg + q1, __interpolated_size, q2 - q1 + 1,  __AC_height + __block_cnt, &AC_idx);
#else
        /* Just using the max value and position as AC */
        __AC_height[__block_cnt] = __avg_maxval;
        AC_idx = __avg_maxpos;
#endif

        /* Find all PC peak candidates with their weights */
        find_pc_peak_candidates(AC_idx, &pc_peak_cnt);
        if (pc_peak_cnt > 0) {
            fptype PC_height;
            int PC_idx;

            /* Select PC peak from candidates */
            find_pc_peak(__AC_height[__block_cnt], AC_idx, pc_peak_cnt, &PC_height, &PC_idx, __PC_weight + __block_cnt);

            /* Storing results */
            __thickness[__block_cnt] = CORNEA_REFRACTIVE_IDX*fabs(NDPA_X(PC_idx) - NDPA_X(AC_idx));
            __AC_position[__block_cnt] = NDPA_X(AC_idx);

printf("\t\t\tAC is %g at index %d with x %f.\n", __AC_height[__block_cnt], AC_idx, __AC_position[__block_cnt]);
printf("\t\t\tPC is %f at index %d with x %f and weight %f.\n", PC_height, PC_idx, NDPA_X(PC_idx), __PC_weight[__block_cnt]);
printf("\t\t\tThickness for this block is %f um\n", 1000.0 * __thickness[__block_cnt]);

        } else {
            __thickness[__block_cnt] = 0.0;
            __PC_weight[__block_cnt] = 0.0;
            iret = 100;

printf("\t\t\t***** No PC peak candidates found! Discarding block %d.\n", __block_cnt);
printf("\t\t\tAC is %g at index %d with x %f.\n", __AC_height[__block_cnt], AC_idx, __AC_position[__block_cnt]);
        }
    }
    else {
        __thickness[__block_cnt] = 0.0;
        __PC_weight[__block_cnt] = 0.0;
        __AC_height[__block_cnt] = 0.0;
        __AC_position[__block_cnt] = -1;
        iret = 101;

printf("\t\t\t***** No valid scans within the block! Discarding block %d.\n", __block_cnt);
    }

    __block_cnt ++;

    return iret;
}

/**
 * @brief Called after new scan data presented within __ndpa_x0 and __ndpa_y0
 * 
 * @param[in] scan_med - Median of the full __ndpa_y0 scan data. Only used if USE_RESTRICTED_SCANS are active! Ignored otherwise.
 * @return int 
 * @return 0 - Success
 * @return 301 401, 501 - Invalid scan, cannot find max position
 * @return 321, 421, 521 - Not enough active members for polyfit2()!
 * @return 322, 422, 522 - polyfit2() cannot work with singular matrices
 */
int ndpa_scan(word scan_med) {
    int iret = 0;

    if (__scan_cnt == 0) {
        fptype e = INTERPOLATION_DISTANCE * floor(__ndpa_x0[MAX_WINDOW_SIZE - 1] / INTERPOLATION_DISTANCE);
        __ndpa_x_start = INTERPOLATION_DISTANCE * ceil(__ndpa_x0[0] / INTERPOLATION_DISTANCE); /* __ndpa_x[0] */
        __interpolated_size = MIN(((e - __ndpa_x_start) / INTERPOLATION_DISTANCE) + 2, MAX_WINDOW_SIZE);
#if USE_INTERPOLATED_POS_BUFFER
    #if USE_RESTRICTED_SCANS
        fptype e0 = INTERPOLATION_DISTANCE * floor(__ndpa_x0[MAX_POSITIONS - 1] / INTERPOLATION_DISTANCE);
        int is0 = ((e0 - __ndpa_x_start) / INTERPOLATION_DISTANCE) + 2;
        int i;
        /* calculating __ndpa_x for the first scan only */
        for (i=0; i<is0; i++) {
            __ndpa_x[i] = i*INTERPOLATION_DISTANCE + __ndpa_x_start;
        }
    #else
        int i;
        /* calculating __ndpa_x for the first scan only */
        for (i=0; i<__interpolated_size; i++) {
            __ndpa_x[i] = i*INTERPOLATION_DISTANCE + __ndpa_x_start;
        }
    #endif
#endif
    }

#if USE_RESTRICTED_SCANS
    /* Calculating offsetted pointers */
    __ndpa_offsetted_x0 = __ndpa_x0 + __ndpa_offsets[__scan_cnt];
    #if USE_INTERPOLATED_POS_BUFFER
        __ndpa_offsetted_x = __ndpa_x + (int)ceil(__ndpa_x0[__ndpa_offsets[__scan_cnt]] / INTERPOLATION_DISTANCE);
    #else
        __ndpa_offsetted_x_start = INTERPOLATION_DISTANCE * ceil(__ndpa_x0[__ndpa_offsets[__scan_cnt]] / INTERPOLATION_DISTANCE);
    #endif
#endif

#if USE_RESTRICTED_SCANS
    if (__ndpa_offsets[__scan_cnt] > 0) {
        /* Rejecting scans with 0 offset */
#else
    {
        /* All scans assumed valid */
#endif
        /* Calculate __ndpa_y */
        interpolate_scan();

#if USE_RESTRICTED_SCANS
        fptype med = (fptype)scan_med;
#else
        fptype med = median(__ndpa_y, __interpolated_size);
#endif

#if ASSUME_VARIABLE_SIZE_BLOCKS
        /* Not calculating avg max within update, but in ndpa_block_end() instead */
        if ((iret = update_average(med, NULL, NULL))) {
            iret += 500;
        }
#else
        /* Update average vector */
        if (__valid_scans == MAX_SCANS - 1) {
            /* Last scan of the block, also calculate max value and position */
            if ((iret = update_average(med, &__avg_maxval, &__avg_maxpos))) {
                iret += 300;
            }
        }
        else {
            if ((iret = update_average(med, NULL, NULL))) {
                iret += 400;
            }
        }

#endif
#if USE_RESTRICTED_SCANS
        if (!iret) {
            __valid_scans ++;
        }
#endif
    }

    /* Advance to next scan */
    __scan_cnt ++;
#if !USE_RESTRICTED_SCANS
    if (!iret) {
        /* All scans are valid unless there was an error */
        __valid_scans ++;
    }
#endif

    return iret;
}

/**
 * @brief Allocating global buffers
 * 
 * @return int 0 on success
 */
int ndpa_initialise(void) {
    /* Setting "recycled" buffers */
#if CONVOLVE_WITH_AC_PEAK
    /* Using __ndpa_y as the convolve data buffer */
    __ndpa_conv = __ndpa_y;
#else
    /* No convolution necessary. Just using averaged data */
    __ndpa_conv = __ndpa_avg;
#endif
    __ndpa_median = __ndpa_intercept;

    return 0;
}

