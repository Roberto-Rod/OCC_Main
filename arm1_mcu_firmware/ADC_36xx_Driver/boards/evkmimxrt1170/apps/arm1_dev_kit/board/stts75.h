/*****************************************************************************/
/**
 * @file 
 *   stts75.h
 * @brief 
 *   API for STTS75 digital temperature sensor and thermal watchdog
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(STTS75_H)
#define STTS75_H

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "fsl_common.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

status_t STTS75_read_temperature(uint8_t *p_value);

#endif // defined(STTS75_H)


/*** end of file ***/
