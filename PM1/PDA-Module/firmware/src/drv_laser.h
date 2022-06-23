/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Ltd

  @File Name
    drv_laser.h

  @Summary
    Driver for the control of the laser.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DRV_LASER_H    /* Guard against multiple inclusion */
#define _DRV_LASER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"
#include "system/ports/sys_ports.h"
#include "system/time/sys_time.h"
#include "debug.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */  
//#define DEBUG_LASER                                                           // Defined in pdab.h
//#define DISABLE_LASER_CHECK
//#define DISABLE_LASER_SWITCHING  
    
#define DRV_LASER_TIMOUT    10000U                                              // Class 1 safety limit for corneal hazard at 1310nm (10 seconds))
    
#define LASER_ENABLE_PIN    SYS_PORT_PIN_RF5                                    // The OUTPUT pin that turns the laser ON and OFF
#define LASER_STATE_PIN     SYS_PORT_PIN_RA15                                   // The INPUT pin that signals the state of the laser
    
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
typedef enum
{
    LASER_OFF = 0,    
	LASER_ON = 1,
    LASER_INIT,
    LASER_ERROR
} LASER_STATES;

typedef enum
{
	LASER_ERROR_NONE = 0,
    LASER_TIMEOUT,
    LASER_FAIL_ON,
    LASER_FAIL_OFF,
    LASER_FAIL_INIT,
    LASER_TIMER_INIT_ERROR,
    LASER_TIMER_BUSY_ERROR
} LASER_ERRORS;

typedef struct
{
//*********************** State Machine Section ******************************//   
    
    /* Application states*/
    LASER_STATES state;
    LASER_STATES previous_state;
    
    LASER_ERRORS error;
    
    uint32_t timeout;
    
} LASER_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

LASER_ERRORS drv_laser_init(void);
LASER_ERRORS drv_laser_off(void);
LASER_ERRORS drv_laser_on(bool enable  );
LASER_ERRORS drv_laser_get_error( void  );
void drv_laser_timer(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
