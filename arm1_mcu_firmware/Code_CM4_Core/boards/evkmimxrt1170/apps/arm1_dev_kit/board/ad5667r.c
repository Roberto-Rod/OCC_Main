/*****************************************************************************/
/**
 * @file 
 *   ad5667r.c
 * @brief 
 *   Driver for Analog Devices AD5667R Digital to Analog Converter
 * @todo
 *   Complete this low level driver with reference to data sheet and 
 *   drv_dac_ad5667r.c module in PDA project 
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

#include "ad5667r.h"
#include "i2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* I2C slave address */
#define AD5667R_I2C_ID                  (0x1Eu)

/* Commands */
#define AD5667R_WRITE                   (0x00u)
#define AD5667R_UPDATE_DAC              (0x01u)
#define AD5667R_WRITE_UPDATE_ALL        (0x02u)
#define AD5667R_WRITE_UPDATE            (0x03u)
#define AD5667R_POWER                   (0x04u)
#define AD5667R_RESET                   (0x05u)
#define AD5667R_LDAC_SETUP              (0x06u)
#define AD5667R_INTERNAL_REF            (0x07u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef struct {
  uint8_t dac_address           : 3;
  uint8_t command               : 3;
  uint8_t byte_selection        : 1;
  uint8_t _reserved             : 1;
} ad5667r_command_byte_t;

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
 *   Initialise the AD5667R Digital to Analog Converter
 */
void AD5667R_initialise(void)
{
}

/*** end of file ***/
