/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "gfx/libaria/inc/libaria_string.h"
#include "configuration.h"
#include "definitions.h"
#include "maths_library.h"
#include "message_exchange.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define VERSION 1.16f

#define BUILD ((uint16_t) 01u)

#define PIC32MZ2064DAR169
//#define DISABLE_DEBUG
#define DISABLE_DEBUG_LEDS
//#define DEBUG_COMMS
//#define DEBUG_PIC24
//#define DEBUG_IP

//#define DISABLE_AUDIO             // Disables audio sounder (For debugging whilst watching TV!))
//#define DISABLE_SCANNING

//#define DISABLE_LSC_CHECK         // Disables the LSC check on startup
#define DISABLE_MEASUREMENT_TIMEOUT // Stops the measurement display timing out
#define DISABLE_USB_ILLUMINATION    // LED's are NOT turned on when USB scanning

#define DISABLE_TIMEOUT_BAR         // Hides the scan timeout (10s) bar
#define DISABLE_Z_SLIDER            // Hides the Z slider on the RHS of teh screen
#define DISABLE_TRACKING_CIRCLE     // Hides the tracking circle (the user just uses the PK1 image instead))
#define DISABLE_IP_RADIUS           // Disables the IP radius (Z distance) check for automatic scanning i.e. just based on X and Y

#define PAUSE_CAMERA                // Enables the camera freeze frame after completing a scan

#define MAX_FRAME_BUFFERS   2

#define EFH_PLAYING_UP

//below 60 = 30seconds
#define SYSTEM_INIT_TIMEOUT_30seconds 60U

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    APP_STATE_SPLASH = 0,
    APP_STATE_INIT,
    APP_STATE_START_SERVICE,
    APP_STATE_WAIT_FOR_STATUS,
    APP_STATE_SERVICE_TASKS,
    APP_STATE_SCANNING,
    APP_STATE_WAIT,
    APP_STATE_IDLE,
    APP_STATE_SET_TIME,
    APP_STATE_BEGIN_CONFIGURE,
    APP_STATE_DEVICE_SETUP,
    APP_STATE_CAMERA_SETUP,
    APP_STATE_DISPLAY_SETUP,            
    APP_STATE_ERROR
} APP_STATES;


typedef enum
{
    /* Application's state machine's initial state. */
    APP_SUB_STATE_BUSY = -1,
    APP_SUB_STATE_INIT = 0,
    APP_SUB_STATE_CAMERA_INIT,
    APP_SUB_STATE_SET_TIME,
    APP_SUB_STATE_DEVICE_SETUP,
    APP_SUB_STATE_START_SCAN,
    APP_SUB_STATE_STOP_SCAN,
    APP_SUB_STATE_SCANNING,
    APP_SUB_STATE_COMPLETE,
    APP_SUB_STATE_IDLE,
    APP_SUB_STATE_ERROR,
    /* TODO: Define sub states used by the application state machine. */

} APP_SUB_STATES;

typedef enum
{
    APP_SCREEN_SPLASH = 0,
    APP_SCREEN_MAIN = 1,
    APP_SCREEN_DEVICE_SETUP = 2,
    APP_SCREEN_DISPLAY_SETUP = 3,
    APP_SCREEN_ERROR = 4,
    APP_SCREEN_CAMERA_SETUP = 255,      // Not a screen but a child panel of Main GUI
} APP_SCREENS;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;
    APP_STATES prevstate;
    APP_STATES nextstate;
    APP_SUB_STATES substate;
    APP_SCREENS screen;

    char error_string[32];
    uint16_t error_code;

    /* Camera OVM7692 driver handle */
    DRV_HANDLE drvCameraHandle;
    
    uint32_t count;

    bool ledState;
    bool lcdState;
    bool scanState;

    bool chargeState;
    bool batteryState;
    uint8_t battery_percentage;

    uint32_t currentScreen;
    uint32_t previousScreen;

    /* Timer handle for system delays */
    SYS_TIME_HANDLE sysDelayHandle;

    _STATUS_BUFFER status;

    bool scanning;

    _CIRCLE pk1_image;

    _WINDOW p1_window;

    uint16_t measurement_display_timer;

    GFXU_ImageAsset* image;

    /* Alignment UI State*/
    bool        alignment_ui_visible;
    laScheme*   alignment_ui_scheme_1;
    laScheme*   alignment_ui_scheme_2;
    laScheme*   alignment_ui_scheme_3;
    uint16_t    alignment_ui_z_position;
    uint16_t    alignment_ui_progress;

    uint16_t PEVersion;

    bool get_status;
    bool get_pic24_status;
    bool get_pic24_version;
    bool wait_for_alignment;
    bool wait_for_status;
    bool start_scanning;
    bool stop_scanning;
    bool remove_measurement;
    bool update_status_bar;
    bool status_updated;
    bool process_image;
    bool update_settings;

    bool splash_version_updated;
    bool logo_animation;

    bool trigger_woke_from_sleep;

    bool timer1ms;

    bool get_settings;

    uint32_t scan_start_btn_press_counter;
    uint32_t scan_stop_btn_press_counter;
    float temperature_peak;
    float temperature1;
    uint32_t press_to_scan_timer;
    
    uint32_t delay_after_scan;
} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );

APP_STATES APP_Wait( uint16_t ms, APP_STATES next );

GFXU_ImageAsset* APP_GetFrameBufferPtr ( uint8_t index );

void app_update_system_clock(void);
void app_sub_complete(void);

void app_start_measurement_display_timer(uint32_t timeout);

void app_zero_offset(void);
void app_begin_configure( APP_SCREENS screen );
void app_exit_configure(void);

void app_update_splash_version(void);

void app_update_status( uint8_t* status );

void app_frame_received( GFXU_ImageAsset* image );

void app_gui_tasks( void );

/*******************************************************************************
  Function:
    void APP_Tasks ( void )

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
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );

void clock_full_speed(void);//in tasks.c

#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */
