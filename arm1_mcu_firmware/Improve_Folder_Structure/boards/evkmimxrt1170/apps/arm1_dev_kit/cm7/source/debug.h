/*****************************************************************************/
/**
 * @file 
 *   debug.h
 * @brief 
 *   Functions for logging to a console via UART
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(DEBUG_H)
#define DEBUG_H

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "fsl_debug_console.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* Colour tokens */
#define DEBUG_BLACK     "\x1B[30m"
#define DEBUG_RED       "\x1B[91m"
#define DEBUG_GREEN     "\x1B[92m"
#define DEBUG_YELLOW    "\x1B[93m"
#define DEBUG_BLUE      "\x1B[94m"
#define DEBUG_MAGENTA   "\x1B[95m"
#define DEBUG_CYAN      "\x1B[96m"
#define DEBUG_WHITE     "\x1B[97m"
#define DEBUG_ORANGE    "\x1B[38;5;208m"
#define DEBUG_PINK      "\x1B[38;5;212m"
#define DEBUG_BROWN     "\x1B[38;5;94m"
#define DEBUG_PURPLE    "\x1B[35m"

#define DEBUG_printf(...) PRINTF(__VA_ARGS__)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

void DEBUG_initialise(void);
void DEBUG_rx_handler(void);
void DEBUG_putchar(char character);
char DEBUG_getchar(void);

#endif // defined(DEBUG_H)


/*** end of file ***/
