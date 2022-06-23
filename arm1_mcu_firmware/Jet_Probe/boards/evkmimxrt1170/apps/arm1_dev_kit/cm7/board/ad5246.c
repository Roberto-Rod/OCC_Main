/*****************************************************************************/
/**
 * @file 
 *   ad5246.c
 * @brief 
 *   Driver for Analog Devices AD5246 digital resistor
 * @todo
 *   Complete this low level driver with reference to data sheet and 
 *   drv_dpot_ad5247.c module in PDA project 
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "ad5246.h"
#include "i2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* I2C slave address */
#define AD5246_I2C_ID                   (0x2Eu)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the AD5246 digital resistor
 */
void AD5246_initialise(void)
{
}

/*** end of file ***/