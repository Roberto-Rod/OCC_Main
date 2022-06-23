/*****************************************************************************/
/**
 * @file 
 *   pca9530.c
 * @brief 
 *   API for NXP 2-bit I2C-bus LED dimmer
 * @todo
 *   Much of this can be ported from drv_led_pca9530.c in PI module, bearing in
 *   mind that this is a low-level device driver layer, so it may need to be
 *   split, with higher level functioanlity going into an "illumination" layer
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

#include "pca9530.h"
#include "i2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* I2C slave address */
#define PCA9530_I2C_ID                  (0xC0u)

#define PCA9530_REG_SIZE                (sizeof(uint8_t))

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
 *   Write a value to the PCA9530 LED dimmer
 * @param
 *   value 8-bit value to be written 
 * @return
 *   Status
 */
status_t PCA9530_write(uint8_t value)
{
    status_t status = I2C6_send(
        PCA9530_I2C_ID >> 1u, 0, 0, &value, sizeof(value));
  
    return status;
}

/**
 * @brief
 *   Read a value from the PCA9530 LED dimmer
 * @param
 *   p_value Address where 8-bit value is to be returned 
 * @return
 *   Status
 */
status_t PCA9530_read(uint8_t *p_value)
{
    status_t status = I2C6_receive(
        PCA9530_I2C_ID >> 1u, 0, 0, p_value, sizeof(uint8_t));
  
    return status;
}


/*** end of file ***/
