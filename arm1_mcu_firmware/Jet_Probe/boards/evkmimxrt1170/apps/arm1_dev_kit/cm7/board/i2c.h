/*****************************************************************************/
/**
 * @file 
 *   i2c.h
 * @brief 
 *   I2C bus API layer
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(I2C_H)
#define I2C_H

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "fsl_common.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define I2C6_send_sccb I2C6_send

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef enum {
  I2C1 = 0,
  I2C2 = 1,
  I2C3 = 2,
  I2C4 = 3,
  I2C5 = 4,
  I2C6 = 5
} i2c_bus_t;

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

void I2C_initialise(void);

status_t I2C1_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size);
status_t I2C1_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size);
status_t I2C2_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size);
status_t I2C2_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size);
status_t I2C3_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size);
status_t I2C3_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size);
status_t I2C4_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size);
status_t I2C4_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size);
status_t I2C5_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size);
status_t I2C5_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size);
status_t I2C6_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size);
status_t I2C6_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size);
status_t I2C6_receive_sccb(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size);

#endif // defined(I2C_H)


/*** end of file ***/
