/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_STTS75.c

  @Summary
    Driver for the STTS75 temperature chip

  @Description
     SSTTS75 driver.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "drv_STTS75.h"
#include "drv_i2c1.h"

#define STTS75_I2C_ADDRESS         0b01001000 // Will be shifted in I2C functions

#define REG_TEMPERATURE            0x00u
#define REG_CONFIG                 0x01u
#define REG_HYST_SETTING           0x02u
#define REG_OVER_TEMP_SET          0x03u

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

#define I2C_READ_BYTES(addr, reg, data, length)     DRV_I2C1_Read_Bytes(addr, reg, data, length)
#define I2C_WRITE_BYTES(addr, reg, data, length)    DRV_I2C1_Write_Bytes(addr, reg, data, length)





/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

DRV_I2C1_STATUS STTS75_read_temperature_register(STTS75_int_t* temperature)
{
    uint8_t data[2];

    DRV_I2C1_STATUS op_rtn = I2C_READ_BYTES(STTS75_I2C_ADDRESS, REG_TEMPERATURE , data, 2);
    
    temperature->part.fractional = data[1];
    temperature->part.whole = data[0];

    return op_rtn;
}

static STTS75_config_t dev_config = {.Byte = 0u}; 


DRV_I2C1_STATUS STTS75_write_configuration(STTS75_config_t config)
{
    dev_config.Byte = config.Byte; 
    return I2C_WRITE_BYTES(STTS75_I2C_ADDRESS, REG_CONFIG , &dev_config.Byte, 1);      // write STTS75 configuration
}

float STTS75_val_to_float(STTS75_int_t input)
{
    return (((float)input.full)/ (float)(1<< STTS75_FRAQ_BITS));   // conversion from 8q8 to float
}

STTS75_int_t STTS75_float_to_val(float input){
    
    STTS75_int_t out;
    
    out.full= (int16_t)(input * (1 << STTS75_FRAQ_BITS));
    
    return out;
}

DRV_I2C1_STATUS STTS75_get_temperature(float *temperature)
{
    STTS75_int_t dev_temp; 
    DRV_I2C1_STATUS op_rtn = STTS75_read_temperature_register(&dev_temp); 
    
    *temperature = 300.0f; 
    
    if(op_rtn == DRV_I2C1_READ_COMPLETE){
        
        *temperature = STTS75_val_to_float(dev_temp); 
        
    }

    return op_rtn; 
    
}

DRV_I2C1_STATUS STTS75_write_over_temp_threshold(STTS75_int_t temp){
    
    if(temp.full > STTS75_MAX_VAL){
        return DRV_I2C1_WRITE_ERROR; 
    }
    uint8_t data[2];
    data[1] = temp.part.fractional;
    data[0] = temp.part.whole;
    
    return I2C_WRITE_BYTES(STTS75_I2C_ADDRESS, REG_OVER_TEMP_SET , data, 2);
    
}

DRV_I2C1_STATUS STTS75_write_OT_hyst_threshold(STTS75_int_t temp){
    
    if(temp.full > STTS75_MAX_VAL){
        return DRV_I2C1_WRITE_ERROR; 
    }
    uint8_t data[2];
    data[1] = temp.part.fractional;
    data[0] = temp.part.whole;
    
    return I2C_WRITE_BYTES(STTS75_I2C_ADDRESS, REG_OVER_TEMP_SET, data, 2);
    
}

DRV_I2C1_STATUS STTS75_start_one_shot_measurement(){
    
    dev_config.Bits.ONE_SHOT =1; 
    
    return I2C_WRITE_BYTES(STTS75_I2C_ADDRESS, REG_CONFIG , &dev_config.Byte, 1);
    
}

/* *****************************************************************************
 End of File
 */
