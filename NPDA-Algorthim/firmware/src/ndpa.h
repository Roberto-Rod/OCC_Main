/**
 * @file ndpa.h
 * @author rzeller, voccoto Ltd
 * @brief Occuity NDPA main module (ndpa.c) definitions. 
 * @version 0.3
 * @date 2020-09-17
 * 
 * @copyright Copyright (c) 2020
 * 
 * @note To generate documentation use the command "doxygen ndpa-dox.cfg"
 * 
 */

#ifndef __NDPA_H__
#define __NDPA_H__

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
 * @brief 1-Allocate __ndpa_x0 and __ndpa_y0; 0-__ndpa_x0 and __ndpa_y0 provided by control
 * 
 */
#define ALLOCATE_X0Y0               1

/**
 * @brief Assuming that blocks can contain different number of scans.
 *          Setting this to 1, will calculate the max value and position in the averaged array for every single call to ndpa_scan, while
 *          setting it to 0 will expect all blocks to contain MAX_SCANS scans and avg max only calculated after the last scan is added to the block.
 * @note Set to 1 if using restricted data sets and the calling module is NOT filtering out scans with 0 offset values.
 */
#define ASSUME_VARIABLE_SIZE_BLOCKS 1

/** 
 * @brief Use __ndpa_x in calculations
 * @note 1 to use __ndpa_x
 * @note 0 to use __ndpa_x_start and INTERPOLATION_DISTANCE instead of __ndpa_x
 * @note Although 0 value saves RAM space, but takes about 5% longer and result is very slightly different (e.g. 535.778723um vs 535.778700)!
 * @warning Does not work with restricted scans!
 */
#define USE_INTERPOLATED_POS_BUFFER 0

/** @brief Each scan comes with an offset to __ndpa_x0, see __ndpa_offsets */
/** @note 1 to use */
/** @note 0 Not to use */
#define USE_RESTRICTED_SCANS        1

#if (USE_RESTRICTED_SCANS && USE_INTERPOLATED_POS_BUFFER)
    #error  "Restricted scans cannot be used together with __ndpa_x buffer. Change USE_INTERPOLATED_POS_BUFFER to 0!"
#endif


/** @brief Convolve averaged data with AC peak if set */
/** @note 1 convolve in ndpa_block_end() */
/** @note 0 Do not convolve */
#define CONVOLVE_WITH_AC_PEAK       1

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

/** @brief Number of blocks in a measurement */
#define MAX_BLOCKS              10
/** @brief Number of scans within a block */
#define MAX_SCANS               10
/** @brief Number of measurements within a scan. @warning This might be different from the restricted window size in MAX_WINDOW_SIZE */
#define MAX_POSITIONS           5000
#if USE_RESTRICTED_SCANS
    /** @brief Number of measurements used from a scan of MAX_POSITIONS when using restricted data sets @warning MAX_WINDOW_SIZE <= MAX_POSITIONS */
    #define MAX_WINDOW_SIZE     1000
#else
    /** @brief Restricted data set size is the same as the complete scan if restrictions are not used */
    #define MAX_WINDOW_SIZE     MAX_POSITIONS
#endif
/** @brief Max size of AC half-height window (q2 - q1 + 1). See __ndpa_hhw */
#define MAX_AC_HHW              128
/** @brief Max number of PC peak candidates supported. See __ndpa_pcpc */
#define MAX_PCPC                128
/** @brief Position data interpolation step. Distance between interpolated points (resolution) */
#define INTERPOLATION_DISTANCE  0.001
#if USE_RESTRICTED_SCANS
    /** @brief Index within __ndpa_avg where scans' AC peaks are merged at. Use Window Header/Preamble size - see WINDOW_HEADER in ./tools/csv2header-window.c */
    #define AC_REFERENCE_INDEX      200
#else
    /** @brief Index within __ndpa_avg where scans' AC peaks are merged at. This was 1250 in original Matlab code */
    #define AC_REFERENCE_INDEX      500
#endif
/** @brief Minimum central corneal thickness. Original matlab script 0.2. Changed by Robin to 0.3 */
#define MIN_CENT_CORNEAL_THICK  0.3
/** @brief Maximum central corneal thickness. Original matlab script 0.9. Changed by Robin to 0.7 */
#define MAX_CENT_CORNEAL_THICK  0.7
/** @brief Cornea refractive index */
#define CORNEA_REFRACTIVE_IDX   1.3989
// #define CORNEA_REFRACTIVE_IDX   1.4468      // Fused silica    
/** @brief MIPS compiler doesn't like x != 0.0 comparison. FLT_MIN = 1.175494e-38. See polyfit2() */
#define PRACTICAL_ZERO          FLT_MIN

/* Global variable prototypes. See ndpa.c for more information! */
#if ALLOCATE_X0Y0
    extern fptype __ndpa_x0[MAX_POSITIONS];
    extern word __ndpa_y0[MAX_WINDOW_SIZE];
#else
    extern fptype *__ndpa_x0;
    extern word *__ndpa_y0;
#endif

#if USE_RESTRICTED_SCANS
    /* Using window offsets */
    extern word __ndpa_offsets[MAX_SCANS];
    extern fptype *__ndpa_offsetted_x0;
    /** @brief Offseted value in __ndpa_x0 at index a */
    #define NDPA_X0(a)  (__ndpa_offsetted_x0[(a)])
    #if USE_INTERPOLATED_POS_BUFFER
        extern fptype __ndpa_x[MAX_POSITIONS];
        extern fptype *__ndpa_offsetted_x;
        /** @brief Offseted position value in __ndpa_x at index a */
        #define NDPA_X(a)   (__ndpa_offsetted_x[(a)])
    #else
        extern fptype __ndpa_offsetted_x_start;
        /** @brief Offseted interpolated position value at index a */
        #define NDPA_X(x)   (__ndpa_offsetted_x_start + (x)*INTERPOLATION_DISTANCE)
    #endif
#else
    /* No window offsets */
    /** @brief Value of __ndpa_x0 at index a */
    #define NDPA_X0(a)  (__ndpa_x0[(a)])
    #if USE_INTERPOLATED_POS_BUFFER
        extern fptype __ndpa_x[MAX_POSITIONS];
        /** @brief Position value in __ndpa_x at index a */
        #define NDPA_X(a)   (__ndpa_x[(a)])
    #else
        #define __ndpa_x    NULL
        /** @brief Interpolated position value at index a */
        #define NDPA_X(x)   (__ndpa_x_start + (x)*INTERPOLATION_DISTANCE)
    #endif
#endif

extern fptype __ndpa_y[MAX_WINDOW_SIZE];
extern fptype __ndpa_avg[MAX_WINDOW_SIZE];
extern fptype *__ndpa_conv;
extern fptype __ndpa_intercept[MAX_WINDOW_SIZE];
extern fptype __ndpa_slope[MAX_WINDOW_SIZE];
extern fptype *__ndpa_median;
extern byte __ndpa_hhw[MAX_AC_HHW];
extern int __ndpa_pcpc[MAX_PCPC];

extern unsigned int __block_cnt;
extern unsigned int __scan_cnt;
extern unsigned int __valid_scans;
extern int __interpolated_size;
extern fptype __avg_maxval;
extern int __avg_maxpos;
extern fptype __ndpa_x_start;

extern fptype __AC_position[MAX_BLOCKS];
extern fptype __AC_height[MAX_BLOCKS];
extern fptype __PC_weight[MAX_BLOCKS];
extern fptype __thickness[MAX_BLOCKS];
extern fptype __madse[MAX_BLOCKS];

/* Interface function prototypes */
int ndpa_measurement_start(void);
int ndpa_measurement_end(void);
int ndpa_block_start(void);
int ndpa_block_end(void);
int ndpa_scan(word);
int ndpa_initialise(void);

#endif
