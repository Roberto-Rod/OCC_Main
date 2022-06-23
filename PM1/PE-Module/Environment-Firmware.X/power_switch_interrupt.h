/* ************************************************************************** */
/** @file power_switch_interrupt.h
 *
 *  @brief Power toggle switch header file.
 *
 *  @copyright Occuity Limited (c) 2020
 */
/* ************************************************************************** */
/* ************************************************************************** */


#ifndef POWER_TOGGLE_SWITCH_H             /* Guard against multiple inclusion */
#define	POWER_TOGGLE_SWITCH_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <xc.h>
#include "debug.h"

/* Provide C++ Compatibility */
#ifdef	__cplusplus
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
    
/** @brief device state enum defining states of the device  */
typedef enum
{
/** @brief device in init check state*/            
    DEVICE_STATE_INIT,
/** @brief device is on */
    DEVICE_STATE_ON,
/** @brief device is off */
    DEVICE_STATE_OFF,
/** @brief Delayed turn off */            
    DEVICE_STATE_DELAYED_OFF        
            
} DEVICE_STATE;
    
// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

void disabling_uart_modules(void);   
void turn_on_device(void);
void turn_off_device(void);
void delayed_turn_off(void); 
void power_switch_millisecond_timer_interrupt(void);
void power_switch_interrupt(void);
//Test Purpose. Testing how can be sleep mode utilised
bool is_device_on(void);

DEVICE_STATE get_device_state(void); 
    
/* Provide C++ Compatibility */
#ifdef	__cplusplus
}
#endif

#endif	/* POWER_TOGGLE_SWITCH_H */

