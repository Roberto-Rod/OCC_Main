/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_LIS2DS12.h

  @Summary
    Driver for the LIS2DS12 accelerometer chip (motion sensor) header file.

  @Description
     LIS2DS12 driver header file.
 */
/* ************************************************************************** */
#ifndef DRV_LIS2DS12_H                       /* Guard against multiple inclusion */
#define	DRV_LIS2DS12_H

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include <xc.h>
#include "debug.h"

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


// *****************************************************************************
// Section: Interface Functions
// ***************************************************************************** 
 //main
void lis2ds12_read_data_simple_set_up(void);
void lis2ds12_read_data_simple(void);
 //uint8_t read_LIS2DS12_WHO_AM_I_register(void);
 //uint8_t read_LIS2DS12_TEMP_registers(void);
// uint16_t read_LIS2DS12_OUT_X_registers(void);
// uint16_t read_LIS2DS12_OUT_Y_registers(void);
//uint16_t read_LIS2DS12_acceleration_register(void);
// float read_LIS2DS12_acceleration(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif	/* DRV_LIS2DS12_H */

