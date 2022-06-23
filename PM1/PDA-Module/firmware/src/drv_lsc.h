/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_lsc.c

  @Summary
    Driver for Linear Scanning Controller

  @Description
    Uses UART 2 to communicate with the LSC (dsPIC33)
 */
/* ************************************************************************** */

#ifndef _DRV_LSC_H    /* Guard against multiple inclusion */
#define _DRV_LSC_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"
#include "pdab_types.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

#define LSC_BUSY                SYS_PORT_PIN_RB12  
#define LSC_DIR                 SYS_PORT_PIN_RD14    
#define LSC_BUSY_INTERRUPT      INT_SOURCE_CHANGE_NOTICE_B
    
#define NO_MAX_LIMIT

#define LRS_RANGE               5200L
#define LRS_RANGE_TOL           200L

#define LRS_RANGE_MIN           (LRS_RANGE - LRS_RANGE_TOL)

#ifdef NO_MAX_LIMIT
#define LRS_RANGE_MAX           10000L
#else
#define LRS_RANGE_MAX           (LRS_RANGE + LRS_RANGE_TOL)
#endif
    
// *****************************************************************************
// Section: Data Types
// *****************************************************************************

typedef enum
{
    LSC_NONE = 0,
    LSC_GET_VERSION = 1,    
    LSC_DEFINE_LIMITS = 2,
    LSC_START_SCANNING = 3,
    LSC_STOP_SCANNING = 4,
    LSC_GET_STATUS = 5,
    LSC_IS_SHUTDOWN_SAFE = 6,
    LSC_RESET = 255
} LSC_COMMANDS;

typedef enum
{
    LSC_ERROR_NONE =          0,
    LSC_ERROR_POINTER=      0x0001u,
    LSC_ERROR_READ =        0x0002u,
    LSC_ERROR_WRITE =       0x0004u,
    LSC_ERROR_TUNING =      0x0008u,
    LSC_ERROR_SCAN_RANGE =  0x0010u,
    LSC_ERROR_TIMEOUT =     0x0020u,
    LSC_ERROR_INIT_FAIL =   0x0040u,   
} DRV_LSC_ERRORS;

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void drv_lsc_initialise(void);
bool drv_lsc_controller_task(void);
void drv_lsc_millisecond_tick(void); 

//void drv_lsc_get_status(_LSC_STATUS * status, void (*get_status_complete_callback)(void));
//void drv_lsc_get_version(void (*get_version_complete_callback)(void));
void drv_lsc_call_get_status(void);
void drv_lsc_get_last_status( LSC_STATUS_t * status );
//from the pic efh debug code
void read_lsc_status( uint8_t * status );
uint32_t drv_lsc_current_version(void);

bool drv_lsc_is_scanning(void);
void drv_lsc_define_limits(void);
void drv_lsc_start_scanning(void);
void drv_lsc_stop_scanning(void);
void drv_lsc_reset(void);
void drv_lsc_is_shutdown_safe(void);
//bool drv_lsc_awaiting_status(void);
bool drv_lsc_is_busy(void);
bool drv_lsc_is_initialised(void);

DRV_LSC_ERRORS drv_lsc_get_error(void);
 
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_LSC_H */
