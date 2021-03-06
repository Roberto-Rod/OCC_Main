/*****************************************************************************/
/**
 * @file 
 *   display.h
 * @brief 
 *   Top-level LCD display API
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(DISPLAY_H)
#define DISPLAY_H

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "display_support.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* LCD input frame buffer is RGB565, converted by PXP. */
#define DISPLAY_BUFFER_BPP      (2u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

void DISPLAY_reset(void);
void DISPLAY_initialise(void);
uint32_t DISPLAY_wait_for_buffer(void);
void DISPLAY_show_new_frame(void);

#endif // defined(DISPLAY_H)


/*** end of file ***/
