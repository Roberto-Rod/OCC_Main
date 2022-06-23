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


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */



// *****************************************************************************
// Section: Data Types
// *****************************************************************************



// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void sort(float * data, uint16_t length);
float calculate_stddev(float * data, float mean, uint16_t length, uint16_t start);
float calculate_mean(float * data, uint16_t length, uint16_t start);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MATHS_LIBRARY_H */

/* *****************************************************************************
 End of File
 */
