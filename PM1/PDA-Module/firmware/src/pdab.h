/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    pcm.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "PDAB_Initialize" and "PDAB_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "PDAB_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _PDAB_H
#define _PDAB_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "configuration.h"
#include "definitions.h"

#include "pdab_types.h"
#include "pdab_scan_functions.h"
#include "pdab_usb_functions.h"

#include "drv_dpot_ad5247.h"
#include "drv_dac_ad5667r.h"
#include "drv_i2c4.h"
#include "drv_lsc.h"
#include "drv_ext_adc.h"

#include "drv_laser.h"
#include "npda.h"

// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
#define VERSION 1.15f
#define BUILD   ((uint16_t)0u)
#define SILICON_REVISION_B2 6
#define SILICON_REVISION_A3 3

//define DISABLE_PERIPHERALS              // Disable peripheral initialisation
#define DISABLE_LASER_POWER
//#define DISABLE_CMP_PEAK_FINDING

//#define DEBUG_AUTOGAIN
//#define DEBUG_LASER
//#define DEBUG_DAQ
//#define DEBUG_LSC
//#define DEBUG_ADC
//#define DEBUG_EXT_ADC
//#define DEBUG_SCAN
//#define DEBUG_PROCESSING
//#define DEBUG_COMMS
//#define DEBUG_DSPIC_COMMS
//#define DEBUG_MESSAGE_EXCHANGE
//#define DEBUG_AGB                        // Enable Automatic Gain Boost Debug
//#define DEBUG_NPDA
//#define DEBUG_USB
//#define DEBUG_LEDS
//#define DISABLE_PIC24

#ifndef DISABLE_PERIPHERALS               //  Dont enable peripheral functionality if peripheral initialisation is disabled.

//#define DISABLE_LASER_SWITCHING
//#define DISABLE_LASER_CHECK
//#define DISABLE_PWR_MGMT
#define DISABLE_DEBUG_LEDS

//#define DISABLE_LDA
//#define DISABLE_LSC
#define DISABLE_AUTO_ZERO
//#define DISABLE_NPDA

#endif
/******************************************************************************/
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */
/******************************************************************************/
typedef enum
{
    PDAB_CMD_NONE       = 0xFF,
	PDAB_CMD_INITIALISE = 0x00,            // 0
    PDAB_CMD_RESET,                        // 1
    PDAB_CMD_SET_GAIN,                     // 2
    PDAB_CMD_RESERVED_0,                   // 3 - Obsolete
    PDAB_CMD_RESERVED_1,                   // 4
    PDAB_CMD_GET_STATUS,                   // 5
    PDAB_CMD_SCAN,                         // 6 - Obsolete
    PDAB_CMD_GET_SCAN_DATA,                // 7 - Obsolete
    PDAB_CMD_START_SCANNING,               // 8
    PDAB_CMD_STOP_SCANNING,                // 9
    PDAB_CMD_RESERVED_2,                   // 10 - Obsolete
    PDAB_CMD_RESERVED_3,                   // 11 - Obsolete
    PDAB_CMD_RESERVED_4,                   // 12
/***********DEBUGGGING COMMANDS**********/
    PDAB_CMD_SELF_TEST,                    // 13
/****************************************/
	PDAB_CMD_ZERO_OFFSET,                  // 14
    PDAB_CMD_ADJUST_OFFSET,                // 15
	PDAB_CMD_SET_LASER_POWER,              // 16
    PDAB_CMD_SET_SCAN_SETTINGS,            // 17
    PDAB_CMD_READ_NPDA_BUFFER,             // 18
    PDAB_CMD_LASER_CHECK,                  // 19
    PDAB_CMD_SETTINGS_REQUEST,
    PDAB_CMD_SETTINGS_UPDATE
} PDAB_COMMANDS;

/* Commands received from PIB */
typedef enum
{
    COMMAND_NONE = 0,
    COMMAND_ZERO_OFFSET = 1,
    COMMAND_RESET = 2,
    COMMAND_START_SCAN = 3,
    COMMAND_GET_STATUS = 4,
    COMMAND_STOP_SCAN = 5,
    COMMAND__IS_SHUTDOWN_SAFE = 6,
    COMMAND_LASER_CHECK = 7,
    COMMAND_REQUEST_SETTINGS = 8,
    COMMAND_UPDATE_SETTINGS = 9,
} PIB_COMMAND_t;

typedef struct
{
//*********************** State Machine Section ******************************//

    /* Application states*/
    PDAB_STATES state;
    PDAB_STATES previous_state;

     /* Error code should an error occur*/
    uint16_t error;

    _STATUS_BUFFER* status;

    COMM_STATES comm_interface;

    bool usb_enable;

    bool USB_Overrun;

    bool manual_offset;

    bool power_off_busy;

    USB_SOFTWARE_t usb_software;
    
    bool eeprom_stats_read_correct;
    bool eeprom_stats_need_update;
    
    uint32_t calibration_id;
    uint32_t device_id;
    
    char device_name[16];
    uint32_t scans_counter;
    
    bool scan_from_usb;
} PDAB_DATA;

// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************



// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************


/*******************************************************************************
  Function:
    void PDAB_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    PDAB_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    PDAB_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void PDAB_Initialize ( void );
uint16_t PDAB_Peripheral_Init( void );

/*******************************************************************************
  Function:
    void PDAB_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    PDAB_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void PDAB_Tasks ( void );

void PDAB_Status( void );
void PDAB_Error_Status(uint16_t id, uint16_t subid);
void PDAB_Command_Received( PDAB_COMMANDS cmd, uint8_t len, const uint8_t* data, COMM_STATES interface );
void PDAB_Command_Complete( void );
void PDAB_Transmit_Status(void);
void PDAB_Check_Zero_State( void );
bool PDAB_Zero_Busy( void );
void PDAB_Zero_Offset( void );
uint16_t PDAB_Update_Status( void );
uint16_t PDAB_Set_Gain( uint8_t channel, uint8_t gain );
uint16_t PDAB_Set_Power( uint8_t channel, uint8_t power );

void blocking_delay(uint ms);

#endif /* _PDAB_H */
/*******************************************************************************
 End of File
 */
