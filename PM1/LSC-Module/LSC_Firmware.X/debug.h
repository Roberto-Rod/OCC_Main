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
//#include "definitions.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define BLACK       "\x1B[30m"
#define RED         "\x1B[91m"
#define GREEN       "\x1B[92m"
#define YELLOW      "\x1B[93m"
#define BLUE        "\x1B[94m"
#define MAGENTA     "\x1B[95m"
#define CYAN        "\x1B[96m"
#define WHITE       "\x1B[97m"
#define ORANGE      "\x1B[38;5;208m"
#define PINK        "\x1B[38;5;212m"
#define BROWN       "\x1B[38;5;94m"
#define PURPLE      "\x1B[35m"

    
typedef uint16_t timeout_handle_t; 
#define TIMEOUT_EXPIRED 1
#define TIMEOUT_RUNNING 0
#define TIMEOUT_INVALID -1
#define TIMEOUT_HANDLE_INV -2
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

void initialisation_debug(void);
void debug_task(bool *wake_up);

void debug_output_pulse(uint16_t width_ms);

void timeouts_init(void);
bool timeout_start(timeout_handle_t handle,uint32_t delay); 
int8_t timeout_check(timeout_handle_t handle);
bool timeout_alloc(uint16_t* handle); 
bool timeout_free(uint16_t* handle); 
void timeouts_update_tick(void); 

void timeouts_test(void);
void timeouts_test_tick(); 

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */
