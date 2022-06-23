/*****************************************************************************/
/**
 * @file 
 *   stts22h.c
 * @brief 
 *   API for STTS22H digital temperature sensor
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

#include "stts22h.h"
#include "i2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* I2C slave address */
#define STTS22H_I2C_ID                  (0x7Eu)

/* Register mapping */
#define STTS22H_WHOAMI                  (0x01u)
#define STTS22H_TEMP_H_LIMIT            (0x02u)
#define STTS22H_TEMP_L_LIMIT            (0x03u)
#define STTS22H_CTRL                    (0x04u)
#define STTS22H_STATUS                  (0x05u)
#define STTS22H_TEMP_L_OUT              (0x06u)
#define STTS22H_TEMP_H_OUT              (0x07u)
#define STTS22H_SOFTWARE_RESET          (0x0Cu)

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
 *   Read temperature from the STTS22H temperature sensor
 * @param
 *   p_value Address where 16-bit value is to be returned 
 * @return
 *   Status
 */
status_t STTS22H_read_temperature(uint8_t *p_value)
{
    status_t status = I2C3_receive(
        STTS22H_I2C_ID >> 1u, 
        STTS22H_TEMP_L_OUT, 
        sizeof(uint8_t), 
        p_value, 
        sizeof(uint16_t));
  
    return status;
}

/*** end of file ***/
