#include "temperature_monitor.h"
#include "drv_STTS75.h"
#include "drv_i2c1.h"
#include "app.h"

#define INIT_STEPS 4

const STTS75_int_t temp_warn_low = {.part.whole = 5};
const STTS75_int_t temp_warn_high = {.part.whole = 50};


static bool sensor_ready = false; 

uint8_t temperature_mon_init(void){
    
#ifdef DEBUG_TEMP_MON

            dputs("Temp Monitor Init\r\n");

#endif
    
    STTS75_config_t config; 
    config.Byte = 0; 
    config.Bits.SHUTDOWN = 1; 
    config.Bits.RESOLUTION = 0b01;
    
    
    DRV_I2C1_STATUS i2c_state = 0;  
    uint8_t step  =0; 
    
    STTS75_int_t temp_hyst = temp_warn_high; 
    temp_hyst.part.whole = temp_hyst.part.whole -2;  
    
    for(step = 0; step < INIT_STEPS; step++){
        switch(step){
            
            case 0:
                i2c_state = STTS75_write_configuration(config);
                
#ifdef DEBUG_TEMP_MON

            dputs("Setting Temp sensor Config...\r\n");

#endif
                
                break; 
                
            case 1:
                i2c_state = STTS75_write_over_temp_threshold(temp_warn_high);
#ifdef DEBUG_TEMP_MON

            dputs("Setting Temp OT val...\r\n");

#endif
                break; 
                
            case 2:
                
                i2c_state = STTS75_write_OT_hyst_threshold(temp_hyst); 
#ifdef DEBUG_TEMP_MON

            dputs("Setting Temp sensor Hyst val ...\r\n");

#endif
                break;             

            case 3:
                i2c_state = STTS75_start_one_shot_measurement(); 
                sensor_ready = true; 
                break; 
#ifdef DEBUG_TEMP_MON

            dputs("Temp sensor request one shot...\r\n");

#endif                
            default:
#ifdef DEBUG_TEMP_MON

            dputs("Temp mon init invalid state...\r\n");

#endif                
                break; 
        }
        
        if(!I2C_CHECK_OP_SUCCESS(i2c_state)){
            
            app_set_flag(ERROR_TEMP_SENSOR); 
            sensor_ready = false; 
#ifdef DEBUG_TEMP_MON

            dputs("Temp mon init fail\r\n");

#endif  
            break; 
        }

    }
    
    return (INIT_STEPS - step); 
    
}

#define MIN_EXCEED_CNT  4


void temperature_monitor_min_200ms(void){
    
    static uint16_t over_temp_cnt = 0;
    static uint16_t under_temp_cnt = 0; 
    static uint16_t invalid_val_cnt = 0; 
    
    if(sensor_ready  == false){
        
        temperature_mon_init(); 
    }else{
        
        DRV_I2C1_STATUS i2c_state = 0;  
        
        STTS75_int_t temp_val; 

        i2c_state = STTS75_read_temperature_register(&temp_val);
        
#ifdef DEBUG_TEMP_MON

            dputs("Temp sensor reading value...\r\n");

#endif  

        if(I2C_CHECK_OP_SUCCESS(i2c_state)){
            
            if(STTS75_valid_val(temp_val)){
                invalid_val_cnt = 0; 
                app_update_temperature(temp_val.full); 
#ifdef DEBUG_TEMP_MON

            dputs("Temp sensor Valid value...\r\n");

#endif                
                if(temp_val.full > temp_warn_high.full){

#ifdef DEBUG_TEMP_MON

            dputs("Temp sensor Value over high temperature value...\r\n");

#endif 
                    under_temp_cnt = 0; 
                    
                    if(over_temp_cnt < MIN_EXCEED_CNT){
                        
                        over_temp_cnt ++; 
                    }else{
                        
 #ifdef DEBUG_TEMP_MON

            dputs("Setting temperature high warning flag...\r\n");

#endif 
                        
                        over_temp_cnt = (MIN_EXCEED_CNT - 1); 
                        app_set_flag(WARNING_FLAG_OVERTEMPERATURE); 
                    }
                    
                }else if(temp_val.full < temp_warn_low.full){
                    
#ifdef DEBUG_TEMP_MON

                    dputs("Temp sensor Value under low temperature value...\r\n");

#endif 

                    over_temp_cnt = 0; 
                    
                    if(under_temp_cnt< MIN_EXCEED_CNT){
                        
                        under_temp_cnt ++; 
                    }else{
#ifdef DEBUG_TEMP_MON

                        dputs("Setting temperature low warning flag...\r\n");

#endif 
                        under_temp_cnt = (MIN_EXCEED_CNT - 1); 
                        app_set_flag(WARNING_FLAG_UNDERTEMPERATURE); 
                    }
                    
                }else{
                    
                    if(over_temp_cnt > 0){
                        
                        over_temp_cnt--; 
                    }else if(under_temp_cnt  > 0){
                        
                        under_temp_cnt--; 
                    }
                    
#ifdef DEBUG_TEMP_MON

                        dputs("Temperature in normal range...\r\n");

#endif 
                    
                }
                
            }else if (invalid_val_cnt < 2){
                
                invalid_val_cnt++; 
            }else{
                
                 app_set_flag(ERROR_TEMP_SENSOR); 
            }
            
            i2c_state = STTS75_start_one_shot_measurement(); 
#ifdef DEBUG_TEMP_MON

                    dputs("Temp sensor mon start new measurement...\r\n");

#endif 
        }



        if(!I2C_CHECK_OP_SUCCESS(i2c_state)){

            app_set_flag(ERROR_TEMP_SENSOR); 
            sensor_ready = false; 
            
#ifdef DEBUG_TEMP_MON

                    dputs("Temp sensor mon I2C fail...\r\n");

#endif 
        }
    }
    
}
