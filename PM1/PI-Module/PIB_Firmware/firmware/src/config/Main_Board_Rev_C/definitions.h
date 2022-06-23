/*******************************************************************************
  System Definitions

  File Name:
    definitions.h

  Summary:
    project system definitions.

  Description:
    This file contains the system-wide prototypes and definitions for a project.

 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "gfx/hal/gfx.h"
#include "peripheral/ocmp/plib_ocmp1.h"
#include "peripheral/uart/plib_uart5.h"
#include "peripheral/ocmp/plib_ocmp3.h"
#include "system/time/sys_time.h"
#include "peripheral/uart/plib_uart6.h"
#include "peripheral/coretimer/plib_coretimer.h"
#include "peripheral/uart/plib_uart3.h"
#include "peripheral/tmr/plib_tmr4.h"
#include "peripheral/tmr/plib_tmr2.h"
#include "peripheral/tmr/plib_tmr3.h"
#include "peripheral/ddr/plib_ddr.h"
#include "system/int/sys_int.h"
#include "system/ports/sys_ports.h"
#include "system/cache/sys_cache.h"
#include "system/dma/sys_dma.h"
#include "peripheral/tmr/plib_tmr9.h"
#include "peripheral/clk/plib_clk.h"
#include "peripheral/gpio/plib_gpio.h"
#include "peripheral/cache/plib_cache.h"
#include "peripheral/dmac/plib_dmac.h"
#include "system/input/sys_input.h"
#include "gfx/libaria/libaria_harmony.h"

#include "app.h"
#include "app_ui_state.h"
#include "app_function.h"

#include "drv_i2c2.h"
#include "drv_i2c3.h"
#include "drv_led_pca9530.h"
#include "drv_display_ST7701S.h"
#include "drv_touch_cst130.h"
#include "drv_camera_OVM7692.h"
#include "drv_camera_sccb.h"
#include "drv_piezo.h"

#include "message_exchange.h"
#include "pic_comms.h"
#include "pic24_comms.h"
#include "settings.h"
#include "maths_library.h"
#include "scan.h"
#include "time.h"
#include "date_and_time.h"
#include "power_management.h"
#include "debug.h"

#include "main_menu.h"
#include "time_settings_screen.h"
#include "device_settings_screen.h"
#include "scan_settings_screen.h"
#include "camera_settings_screen.h"
#include "display_settings_screen.h"
#include "maths_library.h"
#include "npda.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* System Initialization Function

  Function:
    void SYS_Initialize( void *data )

  Summary:
    Function that initializes all modules in the system.

  Description:
    This function initializes all modules in the system, including any drivers,
    services, middleware, and applications.

  Precondition:
    None.

  Parameters:
    data            - Pointer to the data structure containing any data
                      necessary to initialize the module. This pointer may
                      be null if no data is required and default initialization
                      is to be used.

  Returns:
    None.

  Example:
    <code>
    SYS_Initialize ( NULL );

    while ( true )
    {
        SYS_Tasks ( );
    }
    </code>

  Remarks:
    This function will only be called once, after system reset.
*/

void SYS_Initialize( void *data );

// *****************************************************************************
/* System Tasks Function

Function:
    void SYS_Tasks ( void );

Summary:
    Function that performs all polled system tasks.

Description:
    This function performs all polled system tasks by calling the state machine
    "tasks" functions for all polled modules in the system, including drivers,
    services, middleware and applications.

Precondition:
    The SYS_Initialize function must have been called and completed.

Parameters:
    None.

Returns:
    None.

Example:
    <code>
    SYS_Initialize ( NULL );

    while ( true )
    {
        SYS_Tasks ( );
    }
    </code>

Remarks:
    If the module is interrupt driven, the system will call this routine from
    an interrupt context.
*/

void SYS_Tasks ( void );

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
    
// *****************************************************************************
/* System Objects
        
Summary:
    Structure holding the system's object handles
        
Description:
    This structure contains the object handles for all objects in the
    MPLAB Harmony project's system configuration.
        
Remarks:
    These handles are returned from the "Initialize" functions for each module
    and must be passed into the "Tasks" function for each module.
*/
        
typedef struct
{
    SYS_MODULE_OBJ  sysTime;

    SYS_MODULE_OBJ  drvOVM7692;
} SYSTEM_OBJECTS;

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************



extern SYSTEM_OBJECTS sysObj;

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* DEFINITIONS_H */
/*******************************************************************************
 End of File
*/

