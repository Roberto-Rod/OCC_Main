/*****************************************************************************
 *   File        : I2CEEPROM.h
 *
 *   Description : Header file for read and write to the I2CEEPROM
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#ifndef PICOONBOARD_I2CEEPROM_H
#define PICOONBOARD_I2CEEPROM_H

#include "PaTypes.h"
#include "ErrorCode.h"

#define I2E_MAX_ADDR  (262144)
#define I2E_EEPROM_BUS_ADDR (0x50)


void I2E_Init(void);

ErrorCode_t  I2E_Read(uint32_t  address, uint8_t *data, uint8_t numBytes);

ErrorCode_t  I2E_Write(uint32_t  address, const uint8_t *data, uint8_t numBytes);

#endif //PICOONBOARD_I2CEEPROM_H
