/* 
 * File:   temperature_monitor.h
 * Author: SL
 *
 * Created on August 17, 2021, 5:07 PM
 */

#ifndef TEMPERATURE_MONITOR_H
#define	TEMPERATURE_MONITOR_H

//#define DEBUG_TEMP_MON

#include "drv_STTS75.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    const extern STTS75_int_t temp_warn_low; 
    const extern STTS75_int_t temp_warn_high;
    
    void  temperature_monitor_min_200ms(void); 
    uint8_t temperature_mon_init(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TEMPERATURE_MONITOR_H */

