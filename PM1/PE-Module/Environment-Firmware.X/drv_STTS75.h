/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_STTS75.h

  @Summary
    Driver for the STTS75 temperature chip

  @Description
     SSTTS75 driver.
 */
/* ************************************************************************** */

#ifndef _DRV_STTS75_H                        /* Guard against multiple inclusion */
#define _DRV_STTS75_H

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include <xc.h>
#include "debug.h"
#include "drv_i2c1.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */


// *****************************************************************************
// Section: Data Types
// *****************************************************************************

#define STTS75_FRAQ_BITS    8  
#define STTS75_MIN_VAL      ((-55)<<STTS75_FRAQ_BITS)
#define STTS75_MAX_VAL      ((125)<<STTS75_FRAQ_BITS)             
    
typedef union{
    int16_t full; 
    struct{
        unsigned fractional: STTS75_FRAQ_BITS ;
        signed whole: (16 -STTS75_FRAQ_BITS); 
    } part;

}STTS75_int_t;

typedef union{
    
    struct{
        unsigned SHUTDOWN:      1; // 1 = shutdown device 
        unsigned MODE_TSTAT:    1; // 1 = Interrupt Mode, 0 = Comparator mode
        unsigned OUTPUT_PL:     1; // 0 = Active low, 
        unsigned FAULT_TOL:     2; // Number of trip temperature events for output active (1,2, 4, 6)
        unsigned RESOLUTION:    2; // Resolution: 0b00 = 9bit (0.5*C), 0b01 = 10bit (0.25*C), 0b10 = 11bit (0.125*C), 0b01 = 12bit (0.0625*C) 
        unsigned ONE_SHOT:      1; // 1 = Only do one conversion, 0 = Continuous conversion
    }Bits;
    uint8_t Byte; 
    
}STTS75_config_t; 
    
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

DRV_I2C1_STATUS STTS75_read_temperature_register(STTS75_int_t* temperature);

DRV_I2C1_STATUS STTS75_write_configuration(STTS75_config_t config);

DRV_I2C1_STATUS STTS75_get_temperature(float *temperature); 

DRV_I2C1_STATUS STTS75_write_over_temp_threshold(STTS75_int_t temp);

DRV_I2C1_STATUS STTS75_write_OT_hyst_threshold(STTS75_int_t temp); 

DRV_I2C1_STATUS STTS75_start_one_shot_measurement(); 


float STTS75_val_to_float(STTS75_int_t input);

STTS75_int_t STTS75_float_to_val(float input);

static inline bool STTS75_valid_val(STTS75_int_t val){
    if((val.full > STTS75_MAX_VAL) || (val.full < STTS75_MIN_VAL) ){
        return false;
    }else{
        
        return true; 
    }
}


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_STTS75_H */
