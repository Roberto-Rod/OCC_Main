/**
 * @file npda.c
 * @author rzeller, voccoto Ltd
 * @brief Occuity NPDA main interface module.
 * @version 0.3
 * @date 2020-09-17
 * 
 * @copyright Copyright (c) 2020
 * 
 * @note To generate documentation use the command "doxygen npda-dox.cfg"
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "npda_benchmark.h"
#include "npda_tools_benchmark.h"

#if ALLOCATE_X0Y0
    /** @brief Calibration data (scan position data). Control writes into this buffer. Updated once in a block/measurement/(from boot)? */
    fptype __npda_x0[MAX_POSITIONS];
    /** @brief Scan measurement data (2 byte word for each value). Control writes into this buffer. Updated once for each scan. */
    word __npda_y0[MAX_WINDOW_SIZE];
#else
    /** @brief Calibration data (scan's position data). Control writes into this buffer. Updated once in a block. Updated once in a block/measurement/(from boot)? */
    fptype *__npda_x0 = NULL;
    /** @brief Scan measurement data (2 byte word for each value). Control writes into this buffer. Content updated once for each scan. */
    word *__npda_y0 = NULL;
#endif

#if USE_RESTRICTED_SCANS
    /** @brief Scan data has been pre-processed to reduce size. Offset array contains the starting positions of these MAX_WINDOW_SIZE size packets within __npda_x0 */
    word * __npda_offsets;
    /** @brief __npda_x0 offsetted for current scan = __npda_x0 + current_scan_offset */
    fptype *__npda_offsetted_x0;
    #if USE_INTERPOLATED_POS_BUFFER
        /** @brief Current scan's interpolated data from x0. NPDA writes this. Not used if using __npda_x_start instead */
        fptype __npda_x[MAX_POSITIONS];
        /** @brief __npda_x offsetted for current scan */
        fptype *__npda_offsetted_x;
    #else
        /** @brief Interpolated position for the beginning of the current data window in __npda_y0. Based on the offset */
        fptype __npda_offsetted_x_start;
    #endif
#else
    #if USE_INTERPOLATED_POS_BUFFER
        /** @brief Current scan's interpolated data from x0. NPDA writes this. Not used if using __npda_x_start instead */
        fptype __npda_x[MAX_POSITIONS];
    #endif
#endif
/** @brief Interpolated scan data from __npda_y0. Written by NPDA. Updated once for each scan. */
fptype __npda_y[MAX_WINDOW_SIZE];
/** @brief Accumulating average of AC alligned __npda_y values. Written by NPDA. Updated once for each scan. */
fptype __npda_avg[MAX_WINDOW_SIZE];
/** @brief Convoluted scan data. Written by NPDA. Updated once for each block. @warning "Recycles" the __npda_y buffer. */
fptype *__npda_conv = NULL;
/** @brief Helper vector used in interpolation. */
fptype __npda_intercept[MAX_WINDOW_SIZE];
/** @brief Helper vector used in interpolation. */
fptype __npda_slope[MAX_WINDOW_SIZE];
/** @brief Helper buffer for the median() function. Written by NPDA. Used in multiple steps after interpolation. @warning "Recycles" the __npda_intercept buffer. */
fptype *__npda_median = NULL;
/** @brief Helper buffer used in find_ac_quad() to mark points used in quadratic fitting. */
byte __npda_hhw[MAX_AC_HHW];
/** @brief Used by find_pc_peak_candidates() to store all PC peak candidate indexes. */
int __npda_pcpc[MAX_PCPC];

/** @brief Current block index within a measurement */
unsigned int __block_cnt = 0;
/** @brief Current scan index within a block */
unsigned int __scan_cnt = 0;
/** @brief Number of valid scans within a block. Can be different from __scan_cnt if using restricted scans and the offset for the scan is 0 or otherwise discarded */
unsigned int __valid_scans = 0;
/** @brief Size of __npda_x and y after interpolation */
int __interpolated_size = 0;
/** @brief Maximum value in the averaged data __npda_avg */
fptype __avg_maxval = 0.0;
/** @brief Index of maximum value in the averaged data __npda_avg */
int __avg_maxpos = -1;
/** @brief Value of __npda_x[0] */
fptype __npda_x_start = 0.0;

/** @brief AC position values for each block */
fptype __AC_position[MAX_BLOCKS];
/** @brief AC height values for each block */
fptype __AC_height[MAX_BLOCKS];
/** @brief PC weight values for each block */
fptype __PC_weight[MAX_BLOCKS];
/** @brief Corneal thickness values for each block */
fptype __thickness[MAX_BLOCKS];
/** @brief Helper used in aggregated thickness calculation in npda_measurement_end(). */
fptype __madse[MAX_BLOCKS];

/**
 * @brief Starting a new measurement. Call before npda_block_start() for the first block.
 * 
 * @return int 0 on success
 */
int npda_measurement_start(void) {
    __block_cnt = 0;
    return 0;
}

/**
 * @brief End of measurement. Returning aggregated corneal thickness, etc
 * 
 * @return int on success
 */
int npda_measurement_end(fptype* thickness, fptype* sd, word* blocks) {
    word b;
    fptype mt, mmt; /* Medians */
    word valid_blocks = 0;
    #ifdef DEBUG_NPDA
    fptype valid_blocks_perc; /* Percentage of valid blocks (pp) */
    #endif
    word outlier_blocks = 0;
    #ifdef DEBUG_NPDA
    fptype outlier_blocks_perc; /* (qq) */
    #endif
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
    #ifdef DEBUG_NPDA
    valid_blocks_perc = 100.0 * valid_blocks / MAX_BLOCKS;
    #endif

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
        }
        else {
            weighted_thickness += __PC_weight[b] * __thickness[b];
            weight_sum += __PC_weight[b];
        }
    }
    
    if( weight_sum != 0 )
    {
        weighted_thickness /= weight_sum;
        #ifdef DEBUG_NPDA
        outlier_blocks_perc = 100.0 * outlier_blocks / MAX_BLOCKS;
        #endif
  
        for (b=0; b<valid_blocks; b++) {
            weighted_thickness_sd += __PC_weight[b] * pow(__thickness[b] - weighted_thickness, 2);
        }
        weighted_thickness_sd /= weight_sum;
        weighted_thickness_sd = sqrt(weighted_thickness_sd);        
    }


    *thickness = weighted_thickness * 1000.0;
    *sd = weighted_thickness_sd * 1000.0;
    *blocks = (word)valid_blocks;
    
    #ifdef DEBUG_NPDA
    dprintf("\tNumber of valid blocks is %d (%1.3f %%).\r\n", valid_blocks, valid_blocks_perc);    
    dprintf("\tNumber of outlier blocks is %d (%1.3f %%).\r\n", outlier_blocks, outlier_blocks_perc);    
    dprintf("\tWeighted mean thickness %1.3f um +/- %1.3f um.\r\n", 1000.0*weighted_thickness, 1000.0*weighted_thickness_sd);
    #endif

    return 0;
}

/**
 * @brief Starting new measurement block
 * 
 * @return int 0 on success
 */
int npda_block_start(void) {
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
int npda_block_end(void) {
    int iret = 0;
    int q1, q2; /* AC Peak left-right in __npda_avg */
    int AC_idx; /* AC peak index */
    int pc_peak_cnt = 0; /* Number of PC candidates found */

    if (__valid_scans > 0) {
#if ASSUME_VARIABLE_SIZE_BLOCKS
        /* Calculating  */
        __avg_maxval = vmax(__npda_avg, __interpolated_size, &__avg_maxpos);
#endif
        
#if CONVOLVE_WITH_AC_PEAK
        /* AC peak in averaged data */
        find_ac_peak(__npda_avg, __avg_maxval, __avg_maxpos, &q1, &q2);

        /* Convolving averaged data with AC peak */
        /* NOTE: RZ: In the original matlab version find_ac_peak() would have been called to determine the AC position based on the index of the maximum value. Conv can already find the max, so we don't need to call find_ac_peak() */
        conv(__npda_conv, __npda_avg, __npda_avg + q1, __interpolated_size, q2 - q1 + 1,  __AC_height + __block_cnt, &AC_idx);
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
            __thickness[__block_cnt] = CORNEA_REFRACTIVE_IDX*fabs(NPDA_X(PC_idx) - NPDA_X(AC_idx));
            __AC_position[__block_cnt] = NPDA_X(AC_idx);
            
            if( (  __AC_height[__block_cnt] < 1.00 ) || ( PC_height < 0.02 ) )
            {
                __thickness[__block_cnt] = 0.0;
                __PC_weight[__block_cnt] = 0.0;
                iret = 100;

                #ifdef DEBUG_NPDA
                printf("\t\t\t***** No PC peak candidates found! Discarding block %d.\n", __block_cnt);
                printf("\t\t\tAC is %g at index %d with x %1.3f.\n", __AC_height[__block_cnt], AC_idx, __AC_position[__block_cnt]);
                #endif           
            }

            #ifdef DEBUG_NPDA
            printf("\t\t\tAC is %g at index %d with x %1.3f.\n", __AC_height[__block_cnt], AC_idx, __AC_position[__block_cnt]);
            printf("\t\t\tPC is %f at index %d with x %1.3f and weight %1.2f.\n", PC_height, PC_idx, NPDA_X(PC_idx), __PC_weight[__block_cnt]);
            printf("\t\t\tThickness for this block is %1.0f um\n", 1000.0 * __thickness[__block_cnt]);
            #endif

        } else {
            __thickness[__block_cnt] = 0.0;
            __PC_weight[__block_cnt] = 0.0;
            iret = 100;
            
            #ifdef DEBUG_NPDA
            printf("\t\t\t***** No PC peak candidates found! Discarding block %d.\n", __block_cnt);
            printf("\t\t\tAC is %g at index %d with x %1.3f.\n", __AC_height[__block_cnt], AC_idx, __AC_position[__block_cnt]);
            #endif
        }
    }
    else {
        __thickness[__block_cnt] = 0.0;
        __PC_weight[__block_cnt] = 0.0;
        __AC_height[__block_cnt] = 0.0;
        __AC_position[__block_cnt] = -1;
        iret = 101;

        #ifdef DEBUG_NPDA
        printf("\t\t\t***** No valid scans within the block! Discarding block %d.\n", __block_cnt);
        #endif
    }

    __block_cnt ++;

    return iret;
}

/**
 * @brief Called after new scan data presented within __npda_x0 and __npda_y0
 * 
 * @param[in] scan_med - Median of the full __npda_y0 scan data. Only used if USE_RESTRICTED_SCANS are active! Ignored otherwise.
 * @return int 
 * @return 0 - Success
 * @return 301 401, 501 - Invalid scan, cannot find max position
 * @return 321, 421, 521 - Not enough active members for polyfit2()!
 * @return 322, 422, 522 - polyfit2() cannot work with singular matrices
 */
int npda_scan(word scan_med) {
    int iret = 0;

    if (__scan_cnt == 0) {
        fptype e = INTERPOLATION_DISTANCE * floor(__npda_x0[MAX_WINDOW_SIZE - 1] / INTERPOLATION_DISTANCE);
        __npda_x_start = INTERPOLATION_DISTANCE * ceil(__npda_x0[0] / INTERPOLATION_DISTANCE); /* __npda_x[0] */
        __interpolated_size = MIN(((e - __npda_x_start) / INTERPOLATION_DISTANCE) + 2, MAX_WINDOW_SIZE);
#if USE_INTERPOLATED_POS_BUFFER
    #if USE_RESTRICTED_SCANS
        fptype e0 = INTERPOLATION_DISTANCE * floor(__npda_x0[MAX_POSITIONS - 1] / INTERPOLATION_DISTANCE);
        int is0 = ((e0 - __npda_x_start) / INTERPOLATION_DISTANCE) + 2;
        int i;
        /* calculating __npda_x for the first scan only */
        for (i=0; i<is0; i++) {
            __npda_x[i] = i*INTERPOLATION_DISTANCE + __npda_x_start;
        }
    #else
        int i;
        /* calculating __npda_x for the first scan only */
        for (i=0; i<__interpolated_size; i++) {
            __npda_x[i] = i*INTERPOLATION_DISTANCE + __npda_x_start;
        }
    #endif
#endif
    }

#if USE_RESTRICTED_SCANS
    /* Calculating offsetted pointers */
    __npda_offsetted_x0 = __npda_x0 + __npda_offsets[__scan_cnt];
    #if USE_INTERPOLATED_POS_BUFFER
        __npda_offsetted_x = __npda_x + (int)ceil(__npda_x0[__npda_offsets[__scan_cnt]] / INTERPOLATION_DISTANCE);
    #else
//        __npda_offsetted_x_start = INTERPOLATION_DISTANCE * ceil(__npda_x0[__npda_offsets[__scan_cnt]] / INTERPOLATION_DISTANCE);
        __npda_offsetted_x_start = __npda_x0[__npda_offsets[__scan_cnt]];        
    #endif
#endif

#if USE_RESTRICTED_SCANS
    if (__npda_offsets[__scan_cnt] > 0) {
        /* Rejecting scans with 0 offset */
#else
    {
        /* All scans assumed valid */
#endif
        /* Calculate __npda_y */
        interpolate_scan();

#if USE_RESTRICTED_SCANS
        fptype med = (fptype)scan_med;
#else
        fptype med = median(__npda_y, __interpolated_size);
#endif

#if ASSUME_VARIABLE_SIZE_BLOCKS
        /* Not calculating avg max within update, but in npda_block_end() instead */
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
int npda_initialise(void) {
    /* Setting "recycled" buffers */
#if CONVOLVE_WITH_AC_PEAK
    /* Using __npda_y as the convolve data buffer */
    __npda_conv = __npda_y;
#else
    /* No convolution necessary. Just using averaged data */
    __npda_conv = __npda_avg;
#endif
    __npda_median = __npda_intercept;

    return 0;
}

/*******************************************************************************
 * Function:        void Process_Valid_Measurement( _MEASUREMENT* measurement,  _SCAN_SETTINGS* settings, bool post )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        Update scan settings received from the PIB
 *
 * Notes:           None
 ******************************************************************************/
bool run_npda( _NPDA_SCAN_BUFFER* data, _SCAN_BUFFER* result, const fptype* calibration )
{
    int iret = 0;
    int scan_index = 0;
    npda_initialise();

    __npda_x0 = (fptype*) calibration;
    __npda_offsets = data->Positions;    
    __valid_scans = 0;
    
    if ( !(iret = npda_measurement_start() ))
    {
        do 
        {
            #ifdef DEBUG_NPDA
            dprintf("\tProcessing block %d...\r\n", __block_cnt);
            #endif
            
            if (!(iret = npda_block_start())) 
            {
                #ifdef DEBUG_NPDA
                dprintf("\t\tProcessing %d scans of the file as one block...\r\n", MAX_SCANS);
                #endif

                do 
                {
                    // Get scan data from static buffer
                    __npda_y0 = (word*)&data->Scans[scan_index++].Data[0];
                            
                    // Process scan
                    iret = npda_scan(result->Header.DC_Level);
                    
                    #ifdef DEBUG_NPDA
                    if (iret) {
                        dprintf("\t\t\t~~~~~ ERROR: npda_scan() = %d in scan %u\r\n", iret, __scan_cnt - 1);
                    }
                    if (__scan_cnt == 1) {
                        dprintf("\t\tInterpolated-size = %d\r\n", __interpolated_size);
                    }  
                    #endif                  

                } while (!iret && __scan_cnt < MAX_SCANS);
                
                #ifdef DEBUG_NPDA
                if (iret) 
                {
                    dprintf("ERROR: npda_scan() = %d in scan %u\r\n", iret, __scan_cnt - 1);
                }
                #endif

                if ( (iret = npda_block_end()) ) 
                {
                    #ifdef DEBUG_NPDA
                    dprintf("ERROR: npda_block_end() = %d\r\n", iret);
                    #endif
                }

                #ifdef DEBUG_NPDA
                dprintf("Number of valid scans used %d vs %d\r\n", __valid_scans, __scan_cnt);
                #endif
                
            }
            else 
            {
                #ifdef DEBUG_NPDA
                dprintf("ERROR: npda_block_start() = %d\r\n", iret);
                #endif
            }
        } while (!iret && __block_cnt < MAX_BLOCKS);

        if ((iret = npda_measurement_end( &result->Header.Measurement.Separation[0], &result->Header.Measurement.Precision[0], &result->Header.Blocks ))) 
        {
            #ifdef DEBUG_NPDA
            dprintf("ERROR: npda_measurement_end() = %d\r\n", iret);
            #endif
        }
        
        #ifdef DEBUG_NPDA
        dprintf("Separation: %1.3f +/- %1.3f um.%d\r\n", result->Header.Measurement.Separation[0], result->Header.Measurement.Precision[0]);
        #endif        
        
        #ifdef DEBUG_NPDA
        dprintf("Done.\r\n"); 
        #endif
        return false;
    }
    else 
    {
        #ifdef DEBUG_NPDA
        dprintf("ERROR: npda_measurement_start() = %d\r\n", iret);
        #endif
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}
