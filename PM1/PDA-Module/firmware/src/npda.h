/**
 * @file npda.h
 * @author rzeller, voccoto Ltd
 * @brief Occuity NPDA main module (npda.c) definitions. 
 * @version 0.3
 * @date 2020-09-17
 * 
 * @copyright Copyright (c) 2020
 * 
 * @note To generate documentation use the command "doxygen npda-dox.cfg"
 * 
 */

#ifndef __NPDA_H__
#define __NPDA_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "pdab_types.h"
#include "pdab.h"

/** @brief 8 bit unsigned type */
typedef unsigned char   byte;
/** @brief 16 bit unsigned type */
typedef unsigned short  word;
/** @brief 32 bit unsigned type */
typedef unsigned int    dword;

/** @brief min(a, b) */
#define MIN(a,b)    ((a)<(b)?(a):(b))
/** @brief max(a, b) */
#define MAX(a,b)    ((a)>(b)?(a):(b))


/**
 * @brief Floating point type to be used: 1-double, 0-float (mostly)
 * 
 */
#define USE_DOUBLE_PRECISION        0

/**
 * @brief Assuming that blocks can contain different number of scans.
 *          Setting this to 1, will calculate the max value and position in the averaged array for every single call to npda_scan, while
 *          setting it to 0 will expect all blocks to contain MAX_SCANS scans and avg max only calculated after the last scan is added to the block.
 * @note Set to 1 if using restricted data sets and the calling module is NOT filtering out scans with 0 offset values.
 */
#define ASSUME_VARIABLE_SIZE_BLOCKS 1

/**
 * @brief Floating point type (float or double) used in the algorithm. Changes fptype accordingly.
 * @note 0 to use 4 byte, single precision "float" 
 * @note 1 to use 8 byte, double precision "double"
 */
#if USE_DOUBLE_PRECISION
    /** @brief Current floating point type used. Depends on USE_DOUBLE_PRECISION */
    typedef double fptype;
    /** @brief Maximum value of the current floating point type fptype. DBL_MAX from float.h */
    #define FPTYPE_MAX              DBL_MAX
#else
    /** @brief Current floating point type used. Depends on USE_DOUBLE_PRECISION */
    typedef float fptype;
    /** @brief Maximum value of the current floating point type fptype. FLT_MAX from float.h */
    #define FPTYPE_MAX              FLT_MAX
#endif

/** @brief Use this macro to force reporting values that are erroneous */
#define FORCE_REPORTING_ERRONEOUS_VALUES
/** @brief Apply slope correction to assymetric PC peaks. */
//#define PC_PEAK_CORRECTION   
/** @brief Use this macro if PC peak is supposed to be calculated relative to local scan data */
#define RELATIVE_PC_PEAK_CALC
/** @brief Number of blocks in a measurement */
#define MAX_BLOCKS              10
/** @brief Number of scans within a block */
#define MAX_SCANS               10
/** @brief Number of measurements within a scan. @warning This might be different from the restricted window size in MAX_WINDOW_SIZE */
#define MAX_WINDOW_SIZE     1000
/** @brief Max size of AC half-height window (q2 - q1 + 1). See __npda_hhw */
#define MAX_AC_HHW              128
/** @brief Max number of PC peak candidates supported. See __npda_pcpc */
#define MAX_PCPC                128 //WARNING, to be 100% sure we cover all peaks, this should be ~250
/** @brief Position data interpolation step. Distance between interpolated points (resolution) */
#define INTERPOLATION_DISTANCE  0.001
/** @brief Index within __npda_avg where scans' AC peaks are merged at. Use Window Header/Preamble size - see WINDOW_HEADER in ./tools/csv2header-window.c */
#define AC_REFERENCE_INDEX      200
/** @brief Minimum central corneal thickness. Original matlab script 0.2. */
#define MIN_CENT_CORNEAL_THICK  0.30
/** @brief Maximum central corneal thickness. Original matlab script 0.9. */
#define MAX_CENT_CORNEAL_THICK  0.90
//#define MAX_CENT_CORNEAL_THICK  0.55
/** @brief Cornea refractive index */
#define CORNEA_REFRACTIVE_IDX   1.3989
//#define CORNEA_REFRACTIVE_IDX   1.0000   
/** @brief MIPS compiler doesn't like x != 0.0 comparison. FLT_MIN = 1.175494e-38. See polyfit2() */
#define PRACTICAL_ZERO          FLT_MIN
/** @brief This is x-value offset used during PC paek correction for slope */
#define HALF_WIDTH               0.1
/** @brief Experimental AC height criterion */
#define EXP_AC_HEIGTH_CRITERION  16000
/** @brief Hempel filter multiplier */
#define HEMPEL_FILTER_MULTIPLIER 1.4826
/** @brief Minimum number of valid blocks */    
#define MINIMUM_VALID_BLOCKS    3U
/** @brief Minimum mean weight */    
#define MINIMUM_MEAN_WEIGHT     0.700f   
/** @brief Maximum weighted thickness sdtandard deviation */    
#define MAXIMUM_WEIGHTED_SD     0.008f
/** @brief Hempel filter multiplier */
#define ACCEPTABLE_VALID_BLOCKS 6U    
/** @brief Acceptable number of valid blocks */       
#define ACCEPTABLE_MEAN_WEIGHT  0.780f
/** @brief Acceptable weighted thickness sdtandard deviation */   
#define ACCEPTABLE_WEIGHTED_SD  0.005f

/** @brief Offseted position of first element in NPDA_X */
extern fptype __npda_offsetted_x_start;
/** @brief Offseted interpolated position value at index a */
#define NPDA_X(x)   (__npda_offsetted_x_start + (x)*INTERPOLATION_DISTANCE)

extern fptype __npda_y[MAX_WINDOW_SIZE];
extern fptype __npda_avg[MAX_WINDOW_SIZE];
extern fptype *__npda_conv;

extern byte __npda_hhw[MAX_AC_HHW];
extern uint16_t __npda_pcpc[MAX_PCPC];

extern fptype __AC_height[MAX_BLOCKS];
extern fptype __AC_height_conv[MAX_BLOCKS];
extern fptype __PC_weight[MAX_BLOCKS];
extern fptype __thickness[MAX_BLOCKS];
extern fptype __madse[MAX_BLOCKS];

typedef enum {
            SUCCESS = 0,
            ERROR_CAL_NOT_STR_MON_INCREASING,
            ERROR_UNEXPECTED_FAILURE,
            WARNING_FEW_VALID_BLOCKS,
            WARNING_PC_PEAKS_SMALL,
            WARNING_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS,
            WARNING_HIGH_DATA_SPREAD,
            WARNING_HIGH_DATA_SPREAD_AND_FEW_VALID_BLOCKS,
            WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL,
            WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS,
            ERROR_TOO_FEW_BLOCKS,
            ERROR_PC_PEAKS_TOO_SMALL,
            ERROR_SPREAD_TOO_HIGH
} NPDA_RETVAL;

/* Interface function prototypes */
NPDA_RETVAL run_npda( _NPDA_SCAN_BUFFER*, _SCAN_BUFFER*, const fptype*);

#ifdef TEST
    #ifndef STATIC
        #define STATIC
    #endif
    
    // Static functions, only need to define as non-static if used outside the module dureing testing
    STATIC int npda_measurement_end(fptype*, fptype*, word*);
    STATIC int npda_block_end(unsigned int, uint16_t, unsigned int);
    STATIC int npda_scan(fptype*, word*, int, unsigned int*, uint16_t*, fptype, word*);

#else
    #ifndef STATIC
        #define STATIC static
    #endif
#endif


#endif
