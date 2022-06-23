/*****************************************************************************/
/**
 * @file 
 *   pca8574.c
 * @brief 
 *   API for NXP PCA8574 8-bit IO expander
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

#include "pca8574.h"
#include "i2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* I2C slave address */
#define PCA8574_I2C_ID                  (0x40u)

#define PCA8574_REG_SIZE                (sizeof(uint8_t))

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
 *   Write a value to the PCA8574 IO expander
 * @param
 *   value 8-bit value to be written 
 * @return
 *   Status
 */
status_t PCA8574_write(uint8_t value)
{
    status_t status = I2C1_send(
        PCA8574_I2C_ID >> 1u, 0, 0, &value, sizeof(value));
  
    return status;
}

/**
 * @brief
 *   Read a value from the PCA8574 IO expander
 * @param
 *   p_value Address where 8-bit value is to be returned 
 * @return
 *   Status
 */
status_t PCA8574_read(uint8_t *p_value)
{
    status_t status = I2C1_receive(
        PCA8574_I2C_ID >> 1u, 0, 0, p_value, sizeof(uint8_t));
  
    return status;
}


/*** end of file ***/
