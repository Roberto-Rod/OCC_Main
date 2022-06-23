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

#include <stdint.h>
#include <math.h>

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */


/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */


/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/*******************************************************************************
 * Function:        void sort( float* data, uint16_t length )
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
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/
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
                temp = data[j + 1];             // swapping element 
                data[j + 1] = data[j];
                data[j] = temp;
            }
        }
    }
}
/*******************************************************************************
 * Function:        calculate_stddev(float * data, float mean, uint16_t length, uint16_t start)
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
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/
float calculate_stddev(float * data, float mean, uint16_t length, uint16_t start)
{
    float sd = 0.0f;    
    
    if( length > 0 )
    {
        float sum = 0.0f;
        uint16_t i;
        uint16_t stop = length + start;

        for (i = start; i < stop; i++)
        {
            sum += powf((data[i] - mean), 2);
        }

        sd = sqrtf(sum / length);
    }
        
    return sd;
}

/*******************************************************************************
 * Function:        float calculate_mean(float * data, uint16_t length, uint16_t start)
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
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/
float calculate_mean(float * data, uint16_t length, uint16_t start)
{
    float mean = 0.0f;
    
    if( length > 0 )
    {    
        float sum = 0.0f;        
        uint16_t i;
        uint16_t stop = length + start;

        for (i = start; i < stop; i++)
        {
            sum += data[i];
        }

        mean = sum / length;
    }
         
    return mean;
}

/* *****************************************************************************
 End of File
 */
