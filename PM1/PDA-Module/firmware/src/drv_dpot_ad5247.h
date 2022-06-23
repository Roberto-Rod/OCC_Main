/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_dpot_ad5247.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DRV_DPOT_AD5247_H
#define _DRV_DPOT_AD5247_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include "definitions.h"

/*******************************************************************************
                            Definitions
*******************************************************************************/

/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
typedef enum
{
    DRV_DPOT_1 = 0,     
    DRV_DPOT_2,
    DRV_DPOT_3,
    DRV_DPOT_4,            
} DRV_DPOT_INDEX;   

#define DRV_AMP_GAIN_DPOT        DRV_DPOT_1
#define DRV_LASER_POWER_DPOT     DRV_DPOT_2

#define DRV_DPOT1_DEFAULT        61U
#define DRV_DPOT2_DEFAULT        64U
/*******************************************************************************
                             External Functions
*******************************************************************************/

bool drv_dpot_ad5247_controller_task(void);
void drv_dpot_set_resistance(DRV_DPOT_INDEX dpot, uint8_t value);
void drv_dpot_read_resistance(DRV_DPOT_INDEX dpot);
uint8_t drv_dpot_get_resistance(DRV_DPOT_INDEX dpot);
bool drv_dpot_set_resistance_realtime(DRV_DPOT_INDEX dpot, uint8_t value); 
bool drv_dpot_busy(void);
bool drv_dpot_idling(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_DAC_AD5667R_H */
