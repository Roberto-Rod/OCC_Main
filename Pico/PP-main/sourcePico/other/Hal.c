/*****************************************************************************
 *   File        : Hal.c
 *
 *   Description : Hardware Abstraction Layer (HAL).
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

#include "hal.h"
#include "i2c.h"
#include <stdint.h>

uint32_t myAbstLayerI2c()
{
    uint8_t i2cData[4] = {0};
    I2C_MESSAGE_STATUS status;
    void I2C_MasterRead(
            i2cData,
            4,
            0x12,
            &status);

    return pressure;
    
}


   


