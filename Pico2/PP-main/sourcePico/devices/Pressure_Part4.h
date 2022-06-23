/*****************************************************************************
 *   File        : Pressure_Part4.h
 *
 *   Description : Header for implementation of pressure measurements including
 * I2C comms
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

#ifndef PRESSURE_SENSOR_H
#define	PRESSURE_SENSOR_H

#include "PaTypes.h"
#include "ErrorCode.h"

#define NEXT_VAR_READ 0x80
#define I2C_ADD_REF_P_XL 0x0F
#define I2C_ADD_PRESS_OUT_XL 0x28
#define I2C_ADD_CTRL_REG1 0x20
#define I2C_ADD_CTRL_REG2 0x21
#define I2C_ADD_EXT_SENSOR 0x5D // J2 SA0 to 3V
#define I2C_ADD_INT_SENSOR 0x5C // J4 SA0 to 0V
#define I2C_TIMEOUT_MS 20
#define I2C_ADD_STATUS 0x27
#define LEN_PRES_DATA 5 // Length of pressure data. 3 bytes of the pressure reading and 
                        // 2 bytes of the temperature reading 
#define LEN_PRES_INIT 2 // Length of data register writes during initialisation
#define LEN_PRES_START 1 // Length of data register writes during data capture
#define LEN_PRES_STAT 1 // Length of pressure control registers
#define SENSOR_BOOT 0x80 // Boot bit 
#define PRESS_DATA_READY 0x02
#define PRESS_ONE_SHOT 0x01
#define PDIFF_FAULT_CODE 0xDEAD


bool_t PM_WritePressureSensors(uint8_t Device, uint8_t DataLength, uint8_t *DataBuffer);
bool_t PM_ReadPressureSensors(uint8_t Device, uint8_t DataLength, uint8_t DataAddress, uint8_t *DataBuffer);



#endif	/* PMPRESSURE_SENSOR_H */

