/*****************************************************************************/
/**
 * @file 
 *   lis2de12.h
 * @brief 
 *   API for ST LIS2DE12 digital output motion sensor
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(LIS2DE12_H)
#define LIS2DE12_H

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

status_t LIS2DE12_initialise(void);

#endif // defined(LIS2DE12_H)


/*** end of file ***/
