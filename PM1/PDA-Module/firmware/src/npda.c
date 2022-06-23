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

#include "npda.h"
#include "npda_tools.h"
#include "debug.h"

#if defined(TEST)
    #include "unity.h"
#endif

/** @brief Interpolated position for the beginning of the current data window in __npda_y0. Based on the offset */
fptype __npda_offsetted_x_start;
/** @brief Interpolated scan data from __npda_y0. Written by NPDA. Updated once for each scan. */
fptype __npda_y[MAX_WINDOW_SIZE];
/** @brief Accumulating average of AC alligned __npda_y values. Written by NPDA. Updated once for each scan. */
fptype __npda_avg[MAX_WINDOW_SIZE];
/** @brief Convoluted scan data. Written by NPDA. Updated once for each block. @warning "Recycles" the __npda_y buffer. */
fptype *__npda_conv = NULL;
/** @brief Helper buffer used in find_ac_quad() to mark points used in quadratic fitting. */
byte __npda_hhw[MAX_AC_HHW];
/** @brief Used by find_pc_peak_candidates() to store all PC peak candidate indexes. */
uint16_t __npda_pcpc[MAX_PCPC];
/** @brief AC height values in signal before convolution for each block */
fptype __AC_height[MAX_BLOCKS];
/** @brief AC height values in convolved signal for each block */
fptype __AC_height_conv[MAX_BLOCKS];
/** @brief PC weight values for each block */
fptype __PC_weight[MAX_BLOCKS];
/** @brief Corneal thickness values for each block */
fptype __thickness[MAX_BLOCKS];
/** @brief Helper used in aggregated thickness calculation in npda_measurement_end(). */
fptype __madse[MAX_BLOCKS];

/**
 * @brief End of measurement. Returning aggregated corneal thickness, etc
 * 
 * @param[out] thickness - Corneal thickness
 * @param[out] sd - Measure of uncertainty
 * @param[out] blocks - Measure of uncertainty
 * 
 * @return int 
 * @return 0 - Success
 * @return 200 - Error: no valid blocks collected
 * @return 300 - Error: no valid blocks after hempel filter
 * @return 400 - Error: PC peaks VERY small
 * @return 500 - Error: too few valid blocks
 * @return 600 - Error: PC peaks too small
 * @return 700 - Error: data spread too high
 * @return 100, 110, 111, 010, 011, 001 = XXX
 * @return XX1 - Warning: Dubious measurement: few valid scans
 * @return X1X - Warning: Dubious measurement: PC peak small
 * @return 1XX - Warning: Dubious measurement: high data spread
 * 
 */
STATIC int npda_measurement_end(fptype* thickness, fptype* sd, word* blocks) {
    uint8_t i;
    int iret = 0;
    fptype mt, mmt; /* Medians */
    word valid_blocks = 0;
    word outlier_blocks = 0;
    fptype weighted_thickness = 0.0; /* Weighted mean thickness (mean_w) */
    fptype weighted_thickness_sd = 0.0; /* Weighted mean thickness standard deviation (sd_w) */
    fptype weight_sum = 0.0;
    fptype max_height = -FPTYPE_MAX; /* Max AC height */
    fptype mean_weight;

    for (i=0; i<MAX_BLOCKS; i++) {
        if (fabs(__thickness[i]) > PRACTICAL_ZERO && __AC_height_conv[i] > max_height) {
            max_height = __AC_height_conv[i];
        }
    }

    /* Removing blocks under the threshold. New size in valid_blocks, reusing existing buffers */
    for (i=0; i<MAX_BLOCKS; i++) {
        if (fabs(__thickness[i]) > PRACTICAL_ZERO && __AC_height_conv[i] >= 0.2*max_height && __AC_height[i] > EXP_AC_HEIGTH_CRITERION) {
            __thickness[valid_blocks] = __thickness[i];
            __PC_weight[valid_blocks] = __PC_weight[i];
            valid_blocks ++;
        }
    }

    if (valid_blocks <= 0) {
        /* No valid measurements in all blocks */
        return 200;
    }

    mt = median(__thickness, valid_blocks, __npda_avg); //WARNING: recycling __npda_avg for median calculation
    for (i=0; i<valid_blocks; i++) {
        __madse[i] = fabs(__thickness[i] - mt);
    }
    
    mmt = median(__madse, valid_blocks, __npda_avg) * HEMPEL_FILTER_MULTIPLIER; //WARNING: recycling __npda_avg for median calculation
    for (i=0; i<valid_blocks; i++) {
        if (fabs(__thickness[i] - mt) > 1.5*mmt) {
            __thickness[i] = mt;
            __PC_weight[i] = 0.0;
            outlier_blocks ++;
        }
        else {
            weighted_thickness += __PC_weight[i] * __thickness[i];
            weight_sum += __PC_weight[i];
        }
    }
    
    if (valid_blocks - outlier_blocks <= 0) {
        /* No valid measurements in all blocks after hempel filter */
        return 300;
    }

    if( fabs(weight_sum) <= PRACTICAL_ZERO )
    {
        /* PC peak uber-small, sum of all weights is zero */
        return 400;
    }
    
    weighted_thickness /= weight_sum;
  
    for (i=0; i<valid_blocks; i++) {
        weighted_thickness_sd += __PC_weight[i] * pow(__thickness[i] - weighted_thickness, 2);
    }
    weighted_thickness_sd /= weight_sum;
    weighted_thickness_sd = sqrt(weighted_thickness_sd);        

    mean_weight = weight_sum / ((fptype)(valid_blocks - outlier_blocks)); 

#ifdef FORCE_REPORTING_ERRONEOUS_VALUES
    *thickness = weighted_thickness * 1000.0;
    *sd = weighted_thickness_sd * 1000.0;
    *blocks = (word)valid_blocks;//(word)(valid_blocks - outlier_blocks); //WARNING: I suggest using this measure
#endif
    
    if(valid_blocks < MINIMUM_VALID_BLOCKS ) //WARNING: should not this be valid - outlier_blocks?
    {
        /* Bad measurement: too few valid scans */
        return 500;
    }

    if(mean_weight < MINIMUM_MEAN_WEIGHT)
    {
        /* Bad measurement: PC peaks too small */
        return 600;
    }

   if( weighted_thickness_sd > MAXIMUM_WEIGHTED_SD )
    {
        /* Bad measurement: data spread too high */
        return 700;
    }

#ifndef FORCE_REPORTING_ERRONEOUS_VALUES
    *thickness = weighted_thickness * 1000.0;
    *sd = weighted_thickness_sd * 1000.0;
    *blocks = (word)valid_blocks;//(word)(valid_blocks - outlier_blocks); //WARNING: I suggest using this measure
#endif
    
    if(valid_blocks < ACCEPTABLE_VALID_BLOCKS ) //WARNING: should not this be valid - outlier_blocks?
    {
        /* Dubious measurement: few valid scans */
        iret = iret+1;
    }

    if(mean_weight < ACCEPTABLE_MEAN_WEIGHT )
    {
        /* Dubious measurement: PC peaks small */
        iret = iret+10;
    }

    if(weighted_thickness_sd > ACCEPTABLE_WEIGHTED_SD )
    {
        /* Dubious measurement: high data spread */
        iret = iret+100;
    }
    
    return iret;
}

/**
 * @brief End of measurement block processing. Finding AC and PC peaks in the averaged data.
 * 
 * @param[in] valid_scans - Number of valid scans within the block
 * @param[in] npda_avg_len - Length of the valid data in __npda_avg
 * @param[in] block_cnt - Block count
 * 
 * @return int
 * @return 0 - Success
 * @return 101 - Error: No valid scans, or consecutive scans in the block are too offset apart! Discarding block
 * @return 201 - Error: maxpos is less than 1 or higher than scany_len-1
 * @return 202 - Error: q2 is larger than last idx in scany
 * @return 301 - Error: No PC peak candidates found
 * @return 401 - Error: AC peak near 0.0
 * @return 402 - Error: No PC peak found
 * 
 *  */
STATIC int npda_block_end(unsigned int valid_scans, uint16_t npda_avg_len, unsigned int block_cnt) {
    int iret = 0;
    int q1, q2; /* AC Peak FWHM window in block average */
    int AC_idx; /* AC peak index */
    int pc_peak_cnt = 0; /* Number of PC candidates found */
    int avg_maxpos; /* Index of maximum value in the averaged data __npda_avg */
        
    //WARNING: in the original MATLAB algorithm median value of the scan average is subtracted, however, this should be 0, if all scans had their mean subtracted
    
    if (valid_scans <= 0 || npda_avg_len < AC_REFERENCE_INDEX) { //WARNING: is single valid scan sufficient?
        __thickness[block_cnt] = 0.0;
        __PC_weight[block_cnt] = 0.0;
        __AC_height[block_cnt] = 0.0;
        __AC_height_conv[block_cnt] = 0.0;
        return 101;
    }
    
    /* Calculating peak value in the averaged data */
    __AC_height[block_cnt] = vmax(__npda_avg, npda_avg_len, &avg_maxpos);
        
    /* AC peak in averaged data */
    if((iret = find_ac_peak(__npda_avg, npda_avg_len, __AC_height[block_cnt], avg_maxpos, &q1, &q2)) != 0)
    {
        __thickness[block_cnt] = 0.0;
        __PC_weight[block_cnt] = 0.0;
        __AC_height[block_cnt] = 0.0;
        __AC_height_conv[block_cnt] = 0.0;
        return 200 + iret;
    }

    /* Convolving averaged data with AC peak */
    /* NOTE: RZ: In the original MATLAB version find_ac_peak() would have been called to determine the AC position based on the index of the maximum value. Conv can already find the max, so we don't need to call find_ac_peak() */
    conv(__npda_conv, __npda_avg, __npda_avg + q1, npda_avg_len, q2 - q1 + 1,  __AC_height_conv + block_cnt, &AC_idx);

    /* Find all PC peak candidates with their weights */
    find_pc_peak_candidates(__npda_conv, npda_avg_len, AC_idx, &pc_peak_cnt);
    
    if (pc_peak_cnt <= 0) {
        __thickness[block_cnt] = 0.0;
        __PC_weight[block_cnt] = 0.0;
        return 301;
    }

    int PC_idx;

    /* Select PC peak from candidates */
    if((iret = find_pc_peak(__npda_conv, npda_avg_len, __AC_height_conv[block_cnt], AC_idx, pc_peak_cnt, &PC_idx, __PC_weight + block_cnt, __thickness + block_cnt)) != 0)
    {
        __thickness[block_cnt] = 0.0;
        __PC_weight[block_cnt] = 0.0;
        return 400 + iret;
    }

    return 0;
}

/**
 * @brief Processes scan data: performs interpolation, finds AC peak and averages over previous scans.
 * 
 * @param[in] calibration - Pointer to calibration data.
 * @param[in] raw_scany - Pointer to raw scan data (i.e. before interpolation).
 * @param[in] scan_count - Count of scans within the block.
 * @param[out] valid_scan_count - Count of scans within the block.
 * @param[out] npda_avg_len - Length of valid data in __npda_avg.
 * @param[in] scan_med - Median of the full scan data.
 * @param[in] offsets - Offset applied to the scan data during windowing.
 * 
 * @return int 
 * @return 0 - Success, result is saved to __npda_avg
 * @return 101 - Error: wrong offset
 * @return 201, 202 - Error: failed to transform to uniform distribution
 * @return 301, 302, 303, 304 - Error: failed during interpolation
 * @return 401, 411, 412, 421, 431, 441, 442, 443, 451, 452, 461 - Error: failed
 *         during calculating average 
 */
STATIC int npda_scan(fptype * calibration, word * raw_scany, int scan_count, unsigned int * valid_scan_count, uint16_t * npda_avg_len, fptype scan_med, word * offset) {
    int iret = 0;

    /* Ensuring the offsets are within allowable limits */
    if(*offset > PDAB_SCAN_LENGTH_16 - MAX_WINDOW_SIZE)
    {
        return 101;
    }

    /* Calculating offsetted pointer (i.e. this points to the first element of the offsetted calibration data) */
    fptype * npda_offsetted_x0 = calibration + *offset; 

    /* Calculate uniformly distributed x, which will be later used for interpolation */
    int scany_length;
    if((iret = transform_to_uniform_distribution(npda_offsetted_x0, MAX_WINDOW_SIZE, INTERPOLATION_DISTANCE, &__npda_offsetted_x_start, &scany_length)) != 0)
    {
        return 200 + iret;
    }

    /* Calculate __npda_y */
    if((iret = interpolate_scan(npda_offsetted_x0, raw_scany, (int) MAX_WINDOW_SIZE, __npda_y, scany_length )) != 0)
    {
        return 300 + iret;
    }

    if((iret = update_average(__npda_y, scany_length, scan_med, *valid_scan_count, npda_avg_len)) != 0)
    {
        return 400 + iret;
    }

    (*valid_scan_count) ++;

    return 0;
}


/**
 * @brief Processes measured data using NPDA algorithm, find corneal thickness, measurement accuracy, etc.
 * 
 * @param[in] data - Pointer to scan data.
 * @param[out] result - Pointer to structure which is used for reporting outcomes from the NPDA.
 * @param[in] calibration - Pointer to calibration data.
 * 
 * @return NPDA_RETVAL
 * @return 0 - Success, result is saved to __npda_avg
 */
NPDA_RETVAL run_npda( _NPDA_SCAN_BUFFER* data, _SCAN_BUFFER* result, const fptype* calibration)
{
    if( !is_increasing_monotonically(calibration, PDAB_SCAN_LENGTH_16) )
    {
        return ERROR_CAL_NOT_STR_MON_INCREASING;
    }
    
    int iret = 0; //Variable used for storing return values from functions
    uint16_t scan_index = 0; //Variable used to refer to consecutive scans
    unsigned int scan_cnt;
    unsigned int valid_scans;
    unsigned int block_cnt; /** Current block index within a measurement */
    uint16_t npda_avg_len;
#if defined(TEST)
    bool npda_scan_fail = false;
    bool npda_block_end_fail = false;
#endif
    __npda_conv = __npda_y;

    block_cnt = 0; 

    do 
    {
        scan_cnt = 0;
        valid_scans = 0;
        npda_avg_len = 0;
        do 
        { 
            // Process scan
            if((iret = npda_scan((fptype*) calibration, (word*)&data->Scans[scan_index].Data[0], scan_cnt, &valid_scans, &npda_avg_len, data->DC_Level[scan_index], &data->Positions[scan_index])) != 0)
            {
#if defined(TEST)
                UnityPrint("[NPDA_SCAN() ERROR] iret="); UnityPrintNumber(iret); UnityPrint(", block_cnt="); UnityPrintNumber(block_cnt); UnityPrint(", scan_cnt="); UnityPrintNumber(scan_cnt); UnityPrint("; ");
                npda_scan_fail = true;
#else
                dprintf_colour("[RED]ERROR: NPDA Error A %d[WHITE]\r\n", iret);
#endif
                //return ERROR_UNEXPECTED_FAILURE;
                #ifdef TEST
                #endif
                //TODO: add error handling: report that the scan is discarded on the debug port - possibly stream ydata?
            }
            scan_cnt ++;
            scan_index ++;
        } while (scan_cnt < MAX_SCANS);

        if ((iret = npda_block_end(valid_scans, npda_avg_len, block_cnt)) != 0) 
        {
#if defined(TEST)
            UnityPrint("[NPDA_BLOCK_END() ERROR] iret="); UnityPrintNumber(iret); UnityPrint(", block_cnt="); UnityPrintNumber(block_cnt); UnityPrint("; ");
            npda_block_end_fail = true;
#else
            dprintf_colour("[RED]ERROR: NPDA Error B %d[WHITE]\r\n", iret);
#endif
            //return ERROR_UNEXPECTED_FAILURE;
            #ifdef TEST
            #endif
            //TODO: add error handling: report that the block is discarded on the debug port - possibly stream ydata?
        }
        block_cnt ++;

    } while (block_cnt < MAX_BLOCKS);

    iret = npda_measurement_end( &result->Header.Measurement.Separation[0], &result->Header.Measurement.Precision[0], &result->Header.Blocks );

    result->Header.Measurement.Separation[0] /= CORNEA_REFRACTIVE_IDX;
    result->Header.Measurement.Precision[0] /= CORNEA_REFRACTIVE_IDX;    

    #ifdef DEBUG_NPDA
    dprintf("Thickness %1.0f +/- %1.0f um\r\n", result->Header.Measurement.Separation[0], result->Header.Measurement.Precision[0] );
    dprintf("NPDA Error %d\r\n", iret);
    #endif

#if defined(TEST)
    UnityPrint("NPDA iret="); UnityPrintNumber(iret); UnityPrint("; ");
    if (npda_block_end_fail || npda_scan_fail) return 1000; // Uncomment to trigger TEST error if npda_scan() or npda_block_end() failed
#else
    dprintf("NPDA Error %d\r\n", iret); 
#endif
   
    //TODO: add debugging info
    switch(iret)
    {
        case   0:
            return SUCCESS;
        case   1:
            return WARNING_FEW_VALID_BLOCKS;
        case  10:
            return WARNING_PC_PEAKS_SMALL;
        case  11:
            return WARNING_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS;
        case 100:
            return WARNING_HIGH_DATA_SPREAD;
        case 101:
            return WARNING_HIGH_DATA_SPREAD_AND_FEW_VALID_BLOCKS;
        case 110:
            return WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL;
        case 111:
            return WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS;
        case 200:
        case 300:
        case 500:
            return ERROR_TOO_FEW_BLOCKS;
        case 600:
            return ERROR_PC_PEAKS_TOO_SMALL;
        case 700:
            return ERROR_SPREAD_TOO_HIGH;
        case 400:
        default:
            return ERROR_UNEXPECTED_FAILURE;

    }
    
    return SUCCESS;
}
