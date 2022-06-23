/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    date_and_time.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DATE_AND_TIME_H    /* Guard against multiple inclusion */
#define _DATE_AND_TIME_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "time.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */



// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

void incrementTime(RTCCFORM *time);
char isLeapYear(int year);
char dayOfTheWeek(int year, char month, char date);
uint8_t getNumberOfDaysInMonth(int month, int year);
    
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DATE_AND_TIME_H */