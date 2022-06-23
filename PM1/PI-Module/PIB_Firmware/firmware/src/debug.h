/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    debug.h

  @Summary
    Functions for logging to a console via a UART.

  @Description
    Console logging functions.
 */
/* ************************************************************************** */

#ifndef _DEBUG_H    /* Guard against multiple inclusion */
#define _DEBUG_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdio.h>

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
void debug_initialise(void);
void debug_transmit_interrupt_callback(void);
void debug_millisecond_timer_interrupt(void);

/* Logging functions */
void dprintf_colour(const char *format, ...);
void dprintf(const char *format, ...);
void dputs_colour(const char *string);
void dputs(const char *string);
void dputc(char ch);

void logging_start_timer(void);
void get_elapsed_time(RTCCFORM *debug_time, uint32_t *milliseconds);
uint32_t log_elapsed_time(const char *string);

bool debug_busy(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */
