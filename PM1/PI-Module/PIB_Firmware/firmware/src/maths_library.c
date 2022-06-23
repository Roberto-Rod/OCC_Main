/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    maths_library.c

  @Summary
    Maths functions.

  @Description
    Maths function library.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "maths_library.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */



/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/******************************************************************************
  Function:
    void Sort(float * data, uint16_t length)

  Remarks:
    See prototype in app.h.
 */
void sort(float * data, uint16_t length)
{
    uint16_t i;
    uint16_t j;
    float temp = 0.0f;

    for (i = 0U; i < length; i++)
    {
        for (j = 0U; j < (length - i - 1U); j++)
        {
            if (data[j] > data[j + 1])
            {
                temp = data[j + 1];        // swapping element 
                data[j + 1] = data[j];
                data[j] = temp;
            }
        }
    }
}

/******************************************************************************
  Function:
    float calculate_stdev(float * data, float mean, uint16_t length, uint16_t start)

  Remarks:
    See prototype in app.h.
 */
float calculate_stdev(float * data, float mean, uint16_t length, uint16_t start)
{
    float sum = 0.0f;
    float sd = 0.0f;
    uint16_t i;
    uint16_t stop = length + start;
    
    for (i = start; i < stop; i++)
    {
        sum += powf((data[i] - mean), 2);
    }
    
    sd = sqrtf(sum / length);
        
    return (sd);
}

/******************************************************************************
  Function:
    float calculate_mean(float * data, uint16_t length, uint16_t start)

  Remarks:
    See prototype in app.h.
 */
float calculate_mean(float * data, uint16_t length, uint16_t start)
{
    float sum = 0.0f;
    float mean = 0.0f;
    uint16_t i;
    uint16_t stop = length + start;
    
    for (i = start; i < stop; i++)
    {
        sum += data[i];
    }

    mean = sum / length;

    return (mean);
}
/******************************************************************************
  Function:
    float calculate_mode(float * data, uint16_t length, uint16_t* count)

  Remarks:
    See prototype in app.h.
 */
float calculate_mode(float * data, uint16_t length, uint16_t * count)
{
   uint16_t maxCount = 0U;
   uint16_t i;
   uint16_t j;
   uint16_t curCount;
   uint16_t curValue;
   uint16_t newValue;  
   float maxValue = 0U;

    for (i = 0; i < length; i++) 
    {
        curCount = 0;
        curValue = (uint16_t)(data[i] * 1000U);

        for (j = 0; j < length; j++) 
        {
            newValue = (uint16_t)(data[j] * 1000U);

            if (newValue == curValue)
            {
                curCount++;
            }
        }

        if (curCount > maxCount) 
        {
            maxCount = curCount;
            maxValue = data[i];
        }
    }

    *count = maxCount;

    return (maxValue);
}

uint16_t integer_square_root( uint32_t value )
{
    uint16_t sqrt = 0;
    uint16_t bit_shift;

    for(bit_shift = 0x8000; bit_shift > 0; bit_shift >>= 1)
    {
        uint16_t trial = sqrt | bit_shift;
        uint32_t tmp = trial * trial;

        if(tmp <= value)
        {
          sqrt = trial;
        }
    }

    return sqrt;
}
/****************************************************************************
   Least squares fit of circle to set of points by Dave Eberly 

   Input:  (x_i,y_i), 1 <= i <= N, where N >= 3 and not all points
           are collinear
   Output:  circle center (a,b) and radius r
  
   Energy function to be minimized is
  
      E(a,b,r) = sum_{i=1}^N (L_i-r)^2
  
   where L_i = |(x_i-a,y_i-b)|, the length of the specified vector.
   Taking partial derivatives and setting equal to zero yield the
   three nonlinear equations
  
   E_r = 0:  r = Average(L_i)
   E_a = 0:  a = Average(x_i) + r * Average(dL_i/da)
   E_b = 0:  b = Average(y_i) + r * Average(dL_i/db)
  
   Replacing r in the last two equations yields
  
     a = Average(x_i) + Average(L_i) * Average(dL_i/da) = F(a,b)
     b = Average(y_i) + Average(L_i) * Average(dL_i/db) = G(a,b)
  
   which can possibly be solved by fixed point iteration as
  
     a_{n+1} = F(a_n,b_n),  b_{n+a} = G(a_n,b_n)
  
   with initial guess a_0 = Average(x_i) and b_0 = Average(y_i).
   Derivative calculations show that
  
     dL_i/da = (a-x_i)/L_i,  dL_i/db = (b-y_i)/L_i.
  
 ****************************************************************************/
uint16_t fit_circle_float( uint16_t len, uint16_t* x, uint16_t* y, _CIRCLE* circle )
{ 
    /* compute the average of the data points */
    uint16_t i, j;
    float x_mean = 0.0f;
    float y_mean = 0.0f;
    float xc, yc, rc;
    float xc_initial, yc_initial;
    float rc_mean, xc_mean, yc_mean;
    float dx, dy, L;    
    
    if( (len == 0U) | (x == NULL) | ( y == NULL) | ( circle == NULL) )
    {
        circle->x = 0U;
        circle->y = 0U;
        circle->radius = 0U;
        return 0U;
    }

    for (i = 0; i < len; i++) 
    {
        x_mean += x[i];
        y_mean += y[i];
    }
    
    x_mean /= len;
    y_mean /= len;

    /* initial guess */
    xc = x_mean;
    yc = y_mean;

    for (j = 0; j <= FIT_CIRCLE_MAX_ITERATIONS; j++) 
    {
        /* update the iterates */
        xc_initial = xc;
        yc_initial = yc;

        /* compute average L, dL/da, dL/db */
        rc_mean = 0.0f;
        xc_mean = 0.0f;;
        yc_mean = 0.0f;;

        for (i = 0; i < len; i++) 
        {
            dx = (float)x[i] - xc;
            dy = (float)y[i] - yc;
            L = sqrtf( ( dx * dx ) + ( dy * dy ) );
            
            if (fabs(L) > FIT_CIRCLE_TOLERANCE_FLOAT) 
            {
                rc_mean += L;
                xc_mean -= ( dx / L );
                yc_mean -= ( dy / L );
            }
        }
        
        rc_mean /= len;
        xc_mean /= len;
        yc_mean /= len;

        xc = (x_mean + (rc_mean * xc_mean) );                                         // this may be better as floats
        yc = (y_mean + (rc_mean * yc_mean) );
        rc = rc_mean;

        if( fabs(xc - xc_initial) <= FIT_CIRCLE_TOLERANCE_FLOAT ) 
        {
            if( fabs(yc - yc_initial) <= FIT_CIRCLE_TOLERANCE_FLOAT )                  // If the fit tolerance has been met, exit.
                break;
        }
    }

    if( j < FIT_CIRCLE_MAX_ITERATIONS )
    {
        circle->x = (uint16_t)ceilf(xc);
        circle->y = (uint16_t)ceilf(yc);
        circle->radius = (uint16_t)ceilf(rc);
    }
    else
    {
        j = 0U;
    }        

    return j;
}

uint16_t fit_circle_int32( uint16_t len, uint16_t* x, uint16_t* y, _CIRCLE* circle )
{ 
    /* compute the average of the data points */
    uint16_t i, j;
    int32_t x_mean = 0L;
    int32_t y_mean = 0L;
    int32_t xc, yc, rc;
    int32_t xc_initial, yc_initial;
    int32_t rc_mean, xc_mean, yc_mean;
    int32_t dx, dy, L;
    
    if( (len == 0U) | (x == NULL) | ( y == NULL) | ( circle == NULL) )
    {
        circle->x = 0U;
        circle->y = 0U;
        circle->radius = 0U;
        return 0U;
    }    
    
    for (i = 0; i < len; i++) 
    {
        x_mean += x[i];
        y_mean += y[i];
    }
    
    x_mean = ( x_mean * FIT_CIRCLE_FP_SCALE_U32 ) / len;
    y_mean = ( y_mean * FIT_CIRCLE_FP_SCALE_U32 ) / len;

    /* initial guess */
    xc = x_mean;
    yc = y_mean;

    for (j = 0; j < FIT_CIRCLE_MAX_ITERATIONS; j++) 
    {
        /* update the iterates */
        xc_initial = xc;
        yc_initial = yc;

        /* compute average L, dL/da, dL/db */
        rc_mean = 0L;
        xc_mean = 0L;
        yc_mean = 0L;

        for (i = 0; i < len; i++) 
        {
            dx = x[i] * FIT_CIRCLE_FP_SCALE_U32;
            dy = y[i] * FIT_CIRCLE_FP_SCALE_U32;
            dx -= xc;
            dy -= yc;
            L = integer_square_root( ( dx * dx ) + ( dy * dy ) );
            
            dx *= FIT_CIRCLE_FP_SCALE_U32;
            dy *= FIT_CIRCLE_FP_SCALE_U32;
            
            if (abs(L) > FIT_CIRCLE_TOLERANCE_U32) 
            {
                rc_mean += L;
                xc_mean -= ( dx / L );
                yc_mean -= ( dy / L );
            }
        }
        
        rc_mean /= len;
        xc_mean /= len;
        yc_mean /= len;
        
        xc = (x_mean + ( rc_mean * xc_mean / FIT_CIRCLE_FP_SCALE_U32 ) );                                         // this may be better as floats
        yc = (y_mean + ( rc_mean * yc_mean / FIT_CIRCLE_FP_SCALE_U32 ) );
        rc = rc_mean;

        if( abs(xc - xc_initial) <= FIT_CIRCLE_TOLERANCE_U32 ) 
        {
            if( abs(yc - yc_initial) <= FIT_CIRCLE_TOLERANCE_U32 )                     // If the fit tolerance has been met, exit.
                break;
        }
    }

    if( j < FIT_CIRCLE_MAX_ITERATIONS )
    {
        circle->x = (uint16_t)(xc / FIT_CIRCLE_FP_SCALE_U32);
        circle->y = (uint16_t)(yc / FIT_CIRCLE_FP_SCALE_U32);
        circle->radius = (uint16_t)(rc / FIT_CIRCLE_FP_SCALE_U32);
    }
    else
    {
        circle->x = 0U;
        circle->y = 0U;
        circle->radius = 0U;
        j = 0;
    }        

    return j;
}

uint8_t rgb_565_to_gs_approximation( uint16_t pixel )
{
    _RGB_565_PIXEL _pixel;
    
    _pixel.word = pixel;
    
    return (uint8_t)_pixel.red + _pixel.green + _pixel.blue;
}
#ifdef FIND_CIRCLE_INSIDE_OUT
uint16_t find_circle_points( uint16_t* image, uint16_t width, _WINDOW* window, uint16_t threshold, uint16_t* x, uint16_t* y )
{
    /*  To reduce the number of pixels to search the algorithm looks in the forward direction until the threshold is met]
        then it starts from the other side of the image backward. This also ensures the outer pixels are detected.          
        The window definitions define the region of the image to be searched    */ 
                                                                                                                            
    uint16_t i, j, points = 0U;
    
    uint16_t startx = window->start_x + ( window->width / 2U );                 // Starting pixel on each line (forward search)     
    uint16_t stopx1 = window->start_x;                                          // The stop point is the mid position of the window
    uint16_t stopx2 = window->start_x + window->width;                          // The stop point is the mid position of the window
    
    uint16_t starty = window->start_y;                                          // Starting line
    uint16_t stopy = starty + window->height;                                   // End line
    
    DRV_CAMERA_FRAME* frameptr = (DRV_CAMERA_FRAME*)image;                      // Recast to frame structure so you can use line and pixel addressing
    
    for( i = stopy; i > starty; i -= FIND_CIRCLE_LINE_STEP )                    // Looks at every other line to reduce processing requirements, every 4 lines may be sufficient
    {   
        for( j = startx; j > stopx1; j-- )                                      // Forward search
        {
            if( rgb_565_to_gs_approximation( frameptr->Line[i].Pixel[j] ) > threshold )
            {
                x[points] = j;
                y[points] = i;
                points++;
                break;                                                          // Pixel found in this direction, start searching from the other side
            }
        }

        for( j = startx; j < stopx2; j++ )                                      // Backward search
        {
            if( rgb_565_to_gs_approximation( frameptr->Line[i].Pixel[j] ) > threshold )
            {
                x[points] = j;
                y[points] = i;
                points++;
                break;                                                          // Pixel found in this direction, move to the next line.
            }            
        }   
        
        if( points >= FIND_CIRCLE_MAX_POINTS )
            break;
    }
      
    return points;
}
#else
uint16_t find_circle_points( uint16_t* image, uint16_t width, _WINDOW* window, uint16_t threshold, uint16_t* x, uint16_t* y )
{
    /*  To reduce the number of pixels to search the algorithm looks in the forward direction until the threshold is met]
        then it starts from the other side of the image backward. This also ensures the outer pixels are detected.          
        The window definitions define the region of the image to be searched    */ 
                                                                                                                            
    uint16_t i, j, points = 0U;
    uint16_t startx1 = window->start_x;                                         // Starting pixel on each line (forward search)          
    uint16_t startx2 = startx1 + window->width;                                 // Starting pixel on each line (backward search)
    uint16_t stopx = startx1 + ( window->width / 2U );                          // The stop point is the mid position of the window
    uint16_t starty = window->start_y;                                          // Starting line
    uint16_t stopy = starty + window->height;                                   // End line
    
    DRV_CAMERA_FRAME* frameptr = (DRV_CAMERA_FRAME*)image;                      // Recast to frame structure so you can use line and pixel addressing
    
    for( i = stopy; i > starty; i -= FIND_CIRCLE_LINE_STEP )                    // Looks at every other line to reduce processing requirements, every 4 lines may be sufficient
    {   
        for( j = startx1; j < stopx; j++ )                                      // Forward search
        {
            if( rgb_565_to_gs_approximation( frameptr->Line[i].Pixel[j] ) > threshold )
            {
                x[points] = j;
                y[points] = i;
                points++;
                break;                                                          // Pixel found in this direction, start searching from the other side
            }
        }

        for( j = startx2; j > stopx; j-- )                                      // Backward search
        {
            if( rgb_565_to_gs_approximation( frameptr->Line[i].Pixel[j] ) > threshold )
            {
                x[points] = j;
                y[points] = i;
                points++;
                break;                                                          // Pixel found in this direction, move to the next line.
            }            
        }   
        
        if( points >= FIND_CIRCLE_MAX_POINTS )
            break;
    }
      
    return points;
}
#endif

bool find_rectangle( uint16_t* image, _WINDOW* start_window, _WINDOW* stop_window, uint8_t threshold, uint8_t gradient, _RECTANGLE* rectangle )
{
    uint8_t  valid = 0U;
    uint16_t i, j;
    uint16_t startx = start_window->start_x;                                    // Starting pixel on each line (forward search)     
    uint16_t stopx = stop_window->start_x;
    uint16_t starty = start_window->start_y;                                    // Starting line
    uint16_t stopy = start_window->start_y + start_window->height;              // End line
    
    DRV_CAMERA_FRAME* frameptr = (DRV_CAMERA_FRAME*)image;                      // Recast to frame structure so you can use line and pixel addressing
    
    int16_t pixel1 = 0L, pixel2 = 0L;
    int16_t x1 = 120L, x2 = 120L, y1 = 120L, y2 = 120L, midx = 120L, midy = 120L;
    
    rectangle->valid = false;
    
    for( i = starty; i < stopy; i += FIND_RECTANGLE_LINE_STEP )                 // Looks at every other line to reduce processing requirements, every 4 lines may be sufficient
    {   
        for( j = startx; j < stopx; j++ )                                       // Forward search
        {
            pixel1 = rgb_565_to_gs_approximation( frameptr->Line[i].Pixel[j]);
            
            if( pixel1 < threshold )
            {
                if( ( pixel1 - pixel2 ) < gradient )
                {   
                    if( j <= x1 )
                    {
                        x1 = j;
                        midy = i;                   
                        valid = 0x01;
                    }
                    
                    break;                                                      // Pixel found in this direction, start searching from the other side                    
                }
            }
                
            pixel2 = pixel1;            
        } 
    }
   
    startx = start_window->start_x + start_window->width;                                      // Starting pixel on each line (backward search)
    stopx = stop_window->start_x + stop_window->width;                                         // The stop point is the mid position of the window    
    pixel2 = 0L;
    
    for( i = startx; i > stopx; i-- )                                           // Backward search
    {
        pixel1 = rgb_565_to_gs_approximation( frameptr->Line[midy].Pixel[i]);
        
        if( pixel1 < threshold )
        {
            if( ( pixel1 - pixel2 ) < gradient)
            {            
                x2 = i;
                valid |= 0x02;                   
                break;                                                          // Pixel found in this direction, move to the next line.
            }
        }    

        pixel2 = pixel1;
    }      
    
    midx = ( ( x2 - x1 ) / 2U ) + x1;
    starty = start_window->start_y;                                             // Starting line
    stopy = stop_window->start_y;                                               // End line   
    pixel2 = 0L;
    
    for( i = starty; i < stopy; i++ )                                           // Top search
    {
        pixel1 = rgb_565_to_gs_approximation( frameptr->Line[i].Pixel[midx]);
        
        if( pixel1 < threshold )
        {
            if( ( pixel1 - pixel2 ) < gradient )
            {   
                y1 = i;
                valid |= 0x04;          
                break;   
            }                                                                   // Pixel found in this direction, move to the next line.
        }            
        
        pixel2 = pixel1;
    } 

    starty = start_window->start_y + start_window->height;                      // Starting line
    stopy = stop_window->start_y + stop_window->height;                         // End line     
    pixel2 = 0L;
    
    for( i = starty; i > stopy; i-- )                                           // bottom search
    {
        pixel1 = rgb_565_to_gs_approximation( frameptr->Line[i].Pixel[midx]);        
        
        if( pixel1 < threshold )
        {
            if( ( pixel1 - pixel2 ) < gradient )
            {         
                y2 = i;
                valid |= 0x08;        
                break;                                                          // Pixel found in this direction, move to the next line.
            }
        }         
        
        pixel2 = pixel1;
    }       
    
    if( valid == 0x0F )
    {
        rectangle->start_x = x1;
        rectangle->width = x2 - x1;
        rectangle->start_y = y1;
        rectangle->height = y2 - y1;
        rectangle->centre_x = midx;
        rectangle->centre_y = midy;
        rectangle->valid = true;
    }   
      
    return rectangle->valid;
}
/* *****************************************************************************
 End of File
 */
