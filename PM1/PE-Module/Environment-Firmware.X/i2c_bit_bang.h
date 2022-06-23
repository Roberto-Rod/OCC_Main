/* 
 * File:   I2C-Bit-Bang.h
 * Author: Clive
 *
 * Created on 04 October 2013, 09:05
 */

#ifndef I2C_BIT_BANG_H
#define	I2C_BIT_BANG_H

#include <xc.h>

void i2c_initialise(void);
void i2c_write_bytes(uint8_t address, uint8_t register, uint8_t *data, uint8_t length);
void i2c_read_register_bytes(uint8_t address, uint8_t register, uint8_t *data, uint8_t length);

#endif	/* I2C_BIT_BANG_H */
