/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    maths_library.h

  @Summary
    Maths functions.

  @Description
    Maths function library.
 */
/* ************************************************************************** */

#ifndef _MATHS_LIBRARY_H    /* Guard against multiple inclusion */
#define _MATHS_LIBRARY_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include "drv_camera.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
#define FIND_CIRCLE_THRESHOLD       100U
#define FIND_CIRCLE_GRADIENT        10L  
    
#define FIND_CIRCLE_LINE_STEP       4U
#define FIND_CIRCLE_MAX_POINTS      64U
    
#define FIND_RECTANGLE_THRESHOLD    60U
#define FIND_RECTANGLE_GRADIENT     -10L  
#define FIND_RECTANGLE_LINE_STEP    1U    
    
#define FIT_CIRCLE_FLOAT    
#define FIT_CIRCLE_MAX_ITERATIONS   16U
#define FIT_CIRCLE_TOLERANCE_FLOAT  0.01F
    
#define FIT_CIRCLE_TOLERANCE_U32    4U
#define FIT_CIRCLE_FP_SCALE_U32     100U
    
#define FIND_CIRCLE_INSIDE_OUT
    
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
    typedef struct
    {
        int16_t     x;
        int16_t     y;
        int16_t     radius;
        bool        visible;
        bool        valid;
        void*       color;
    } _CIRCLE;
    
    typedef struct
    {
        uint16_t    height;
        uint16_t    width;
        uint16_t    start_x;
        uint16_t    start_y;
    } _WINDOW;    
    
    typedef struct
    {
        int16_t     centre_x;
        int16_t     centre_y;
        uint16_t    height;
        uint16_t    width;
        uint16_t    start_x;
        uint16_t    start_y;
        bool        visible;
        bool        valid;
        void*       color;        
    } _RECTANGLE;    
    
    typedef struct
    {
        union
        {
            uint8_t     byte[2];
            uint16_t    word;
            struct
            {
                uint16_t  red:5;
                uint16_t  green:6;
                uint16_t  blue:5;
            };
        };
    } _RGB_565_PIXEL;       
    
#define rgb_565_to_red(p) { ( p & 0x1F ); }
#define rgb_565_to_green(p) { ( ( p >> 5 ) & 0x3F ); }    
#define rgb_565_to_blue(p) { ( ( p >> 11 ) & 0x1F ); }
   
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void sort(float * data, uint16_t length);
float calculate_stdev(float * data, float mean, uint16_t length, uint16_t start);
float calculate_mean(float * data, uint16_t length, uint16_t start);
float calculate_mode(float * data, uint16_t length, uint16_t * count);

uint16_t integer_square_root( uint32_t value );

uint16_t fit_circle_float( uint16_t len, uint16_t* x, uint16_t* y, _CIRCLE* circle );
uint16_t fit_circle_int32( uint16_t len, uint16_t* x, uint16_t* y, _CIRCLE* circle );
uint16_t find_circle_points( uint16_t* image, uint16_t width, _WINDOW* window, uint16_t threshold, uint16_t* px, uint16_t* py );
bool find_rectangle( uint16_t* image, _WINDOW* start_window, _WINDOW* stop_window, uint8_t threshold, uint8_t gradient, _RECTANGLE* rectangle );
uint8_t rgb_565_to_gs_approximation( uint16_t pixel );

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MATHS_LIBRARY_H */

/* *****************************************************************************
 End of File
 */
