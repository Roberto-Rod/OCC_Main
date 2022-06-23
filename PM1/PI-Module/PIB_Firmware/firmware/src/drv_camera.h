/*******************************************************************************
  Camera Driver Interface

  Company:
    Microchip Technology Inc.

  File Name:
    drv_camera.h

  Summary:
    Camera device driver interface file.

  Description:
    The Camera driver provides a abstraction to all camera drivers.

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
//DOM-IGNORE-END


#ifndef _DRV_CAMERA_H
#define _DRV_CAMERA_H


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "configuration.h"
#include "driver/driver_common.h"			// Common Driver Definitions
#include "system/system_common.h"      	// Common System Service Definitions
#include "system/system_module.h"      	// Module/Driver Definitions
#include "system/int/sys_int.h"

#ifdef __cplusplus
    extern "C" {
#endif
        
// *****************************************************************************
/* Camera Driver Module Index Numbers

  Summary:
    Camera driver index definitions.

  Description:
    These constants provide the Camera driver index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.

    These values should be passed into the DRV_CAMERA_Initialize and
    DRV_CAMERA_Open functions to identify the driver instance in use.
*/
              
#define DRV_CAMERA_INDEX_0          0
#define DRV_CAMERA_INDEX_1          1
        
#define DRV_CAMERA_FRAME_BUFFERS    2
#define DRV_DMA_TRANSFERS_PER_BUFFER     2   // Bytes per frame divided by 65536 (rounded up))
        
#ifndef DRV_CAMERA_FRAME_WIDTH        
#define DRV_CAMERA_FRAME_WIDTH      240
#endif
#ifndef DRV_CAMERA_FRAME_HEIGHT        
#define DRV_CAMERA_FRAME_HEIGHT     240 
#endif
         
#define DRV_CAMERA_SENSOR_WIDTH     640
#define DRV_CAMERA_SENSOW_HEIGHT    480     
#define DRV_CAMERA_COLOUR_DEPTH     2       // Colour depth in bytes -> 2 Bytes = 16 Bit       
        
#define DRV_CAMERA_REG_SET_DELAY    10
        
typedef enum
{
    DRV_CAMERA_STATE_INIT_PERIPHERALS = 0,
    DRV_CAMERA_STATE_WAIT_FOR_OPEN,
    DRV_CAMERA_STATE_CONFIGURE,
    DRV_CAMERA_STATE_START,
    DRV_CAMERA_STATE_RUNNING,          
    DRV_CAMERA_STATE_STOP,
    DRV_CAMERA_STATE_READY, 
    DRV_CAMERA_STATE_CLOSE, 
    DRV_CAMERA_STATE_ERROR,
    DRV_CAMERA_STATE_WAIT         
            
}DRV_CAMERA_STATE;

typedef enum
{
    DRV_CAMERA_CONFIG_STATE_INIT = 0,
    DRV_CAMERA_CONFIG_STATE_GET_MID,  
    DRV_CAMERA_CONFIG_STATE_GET_PID,                 
    DRV_CAMERA_CONFIG_STATE_READY,        
    DRV_CAMERA_CONFIG_STATE_ERROR,
    DRV_CAMERA_CONFIG_STATE_WAIT,         
    DRV_CAMERA_CONFIG_STATE_NONE
            
} DRV_CAMERA_CONFIG_STATE;
 
typedef enum
{
    DRV_CAMERA_SUB_STATE_PAUSE,
    DRV_CAMERA_SUB_STATE_RESUME, 
    DRV_CAMERA_SUB_STATE_IDLE        
            
} DRV_CAMERA_SUB_STATE;

typedef enum
{
    DRV_CAMERA_MID,
    DRV_CAMERA_PID,
    DRV_CAMERA_FRAME_COUNT  
} DRV_CAMERA_PARAMETERS;

typedef struct
{
    uint16_t Pixel[DRV_CAMERA_FRAME_WIDTH];
} DRV_CAMERA_LINE;

typedef struct
{
    union
    {
        uint16_t        Pixels[DRV_CAMERA_FRAME_WIDTH*DRV_CAMERA_FRAME_HEIGHT];
        DRV_CAMERA_LINE Line[DRV_CAMERA_FRAME_HEIGHT];
    };
} DRV_CAMERA_FRAME;

extern volatile DRV_CAMERA_FRAME __attribute__(( coherent, aligned(16))) buffer_data[DRV_CAMERA_FRAME_BUFFERS];
// *****************************************************************************
/* CAMERA Driver Module Index Count

  Summary:
    Number of valid CAMERA driver indices.

  Description:
    This constant identifies the number of valid CAMERA driver indices.

  Remarks:
    This constant should be used in place of hard-coded numeric literals.

    This value is derived from device-specific header files defined as part of the
    peripheral libraries.
*/

#define DRV_CAMERA_INDEX_COUNT     1

typedef enum
{
    /* */
    CAMERA_MODULE_OVM7692 /* DOM-IGNORE-BEGIN */ = 0, /* DOM-IGNORE-END */

} CAMERA_MODULE_ID;


#ifdef __cplusplus
    }
#endif
    
#endif //_DRV_CAMERA_H
