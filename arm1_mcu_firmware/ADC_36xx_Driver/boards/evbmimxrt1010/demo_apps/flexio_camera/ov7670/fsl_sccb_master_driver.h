/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SCCB_MASTER_DRIVER_H_
#define _SCCB_MASTER_DRIVER_H_

#include "ov7670_driver.h"

/*!
 * @brief Initialize LPI2C instance
 * @param base pointer to LPI2C structure
 */
void FLEXIO_Ov7670SccbInit(LPI2C_Type *base);

/*!
 * @brief Read the OV7670 reg.
 *
 * @param base pointer to I2C structure
 * @param device_addr I2C device address
 * @param regAddr I2C device reg address
 * @param rxBuff buff to get the data
 * @param rxSize number of size to read
 */
ov7670_status_t I2C_Read_OV7670_Reg(LPI2C_Type *base, uint8_t device_addr, uint8_t regAddr, uint8_t *rxBuff, uint32_t rxSize);

/*!
 * @brief write the OV7670 reg.
 *
 * @param base pointer to I2C structure
 * @param device_addr I2C device address
 * @param regAddr I2C device reg address
 * @param val data to write
 */

ov7670_status_t I2C_Write_OV7670_Reg(LPI2C_Type *base, uint8_t device_addr, uint8_t regAddr, uint8_t val);

#endif /* _SCCB_MASTER_DRIVER_H_ */
