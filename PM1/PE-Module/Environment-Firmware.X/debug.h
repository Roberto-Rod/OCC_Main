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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "drv_rtc.h"
//#include "definitions.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#define mRTCCBin2Dec(Bin) (((Bin/10)<<4)|(Bin%10))
    
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
    
typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} DebugTime;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************


void debug_initialise(void);
void debug_transmit_interrupt_callback(void);
void debug_millisecond_timer_interrupt(void);

void debug_increment_time(DebugTime *time);

/* Logging functions */
void dprintf_colour(const char *format, ...);
void dprintf(const char *format, ...);
void dputs_colour(const char *string);
void dputs(const char *string);
void dputc(char ch);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */
