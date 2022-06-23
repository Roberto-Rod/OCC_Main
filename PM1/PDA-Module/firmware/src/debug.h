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
#include "definitions.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define DEBUG_IN_DSIZE  (8)
    

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
void debug_millisecond_timer_interrupt(uint32_t status, uintptr_t context);
void debug_increment_time(DebugTime *time);

/* Logging functions */
void dprintf_colour(const char *format, ...);
void dprintf(const char *format, ...);
void dputs_colour(const char *string);
void dputs(const char *string);
void dputc(char ch);
void logging_start_timer(void);
void get_elapsed_time(DebugTime *debug_time, uint16_t *milliseconds);
void log_elapsed_time(const char *string);
bool debug_busy(void);

void UART2_RX_InterruptHandler(void);

void debug_inpack_process(uint8_t *); 
void debug_receive_process(void); 

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */
