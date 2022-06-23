/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include "definitions.h"
#include "Drivers/delay.h"

// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

const char *screen_name[] = {"Splash",                // APP_SCREEN_SPLASH = 0,
                             "Main",                  // APP_SCREEN_MAIN,
                             "Device setup",          // APP_SCREEN_DEVICE_SETUP,
                             "Display setup",         // APP_SCREEN_DISPLAY_SETUP
                             "Camera setup"};         // APP_SCREEN_CAMERA_SETUP,

// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************


// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************

// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize(void)

  Remarks:
    See prototype in app.h
*******************************************************************************/
void APP_Initialize(void)
{
    /* Place the App state machine in its initial state */
    appData.state = APP_STATE_SPLASH;
    appData.prevstate = APP_STATE_IDLE;
    appData.nextstate = APP_STATE_IDLE;
    appData.substate = APP_SUB_STATE_IDLE;

    appData.ledState = false;
    appData.lcdState = false;
    appData.scanState = false;
    appData.chargeState = false;
    appData.batteryState = false;
    appData.battery_percentage = 0U;

    appData.sysDelayHandle = SYS_TIME_HANDLE_INVALID;
    appData.wait_for_alignment = false;
    appData.wait_for_status = false;
    appData.start_scanning = false;
    appData.stop_scanning = false;

    appData.remove_measurement = false;
    appData.update_status_bar = false;
    appData.status_updated = false;
    appData.process_image = false;

    appData.measurement_display_timer = 0U;

    appData.p1_window.height = 60U;
    appData.p1_window.width = 60U;
    appData.p1_window.start_x = 90U;
    appData.p1_window.start_y = 90U;

    appData.trigger_woke_from_sleep = false;
    
    appData.get_pic24_status = false;
    appData.get_pic24_version = false;

    appData.splash_version_updated = false;

    appData.PEVersion = 0U;

    appData.error_code = 0U;
    sprintf(appData.error_string, "No Error\n" );
    
    appData.logo_animation = true;
    
    //change state to update at power-up
    app_set_usb_state(false);
    //make sure LEDs are off in case of unwanted reset with LEDs on
    set_pca9530_leds_off();
}


/*******************************************************************************
  Function:


  Remarks:
    called ten times per second on interrupt context
*******************************************************************************/
void app_start_measurement_display_timer(uint32_t timeout)
{
#ifdef DISABLE_MEASUREMENT_TIMEOUT
    appData.measurement_display_timer = MEASUREMENT_DISPLAY_TIMEOUT_MAX;
    appData.remove_measurement = false;
#else
    appData.measurement_display_timer = timeout;
    appData.remove_measurement = false;
#endif
}

/*******************************************************************************
  Function:


  Remarks:
    called ten times per second on interrupt context
*******************************************************************************/
void app_update_system_clock(void)
{
    if (!appData.scanState)
    {
        appData.get_status = true;
    }

    if (!appData.scanState)
    {
        appData.get_pic24_status = true;
    }


    if (appData.measurement_display_timer > 0U)
    {
        appData.measurement_display_timer--;

        if (0 == appData.measurement_display_timer)
        {
            appData.remove_measurement = true;
        }
    }
}

/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
APP_STATES APP_Wait(uint16_t ms, APP_STATES next)
{
    if (SYS_TIME_HANDLE_INVALID == appData.sysDelayHandle)
    {
        if (SYS_TIME_DelayMS(ms, &appData.sysDelayHandle) != SYS_TIME_SUCCESS)
        {
            appData.prevstate = appData.state;
            return (APP_STATE_ERROR);
        }
        else
        {
            appData.prevstate = appData.state;
            appData.nextstate = next;
            return (APP_STATE_WAIT);
        }
    }
    else
    {
        appData.prevstate = appData.state;
        return (APP_STATE_ERROR);
    }
}

/*******************************************************************************
  Function:


  Remarks:
    switch to a configuration screen
*******************************************************************************/
void app_begin_configure(APP_SCREENS screen)
{
    if (APP_STATE_IDLE != appData.state)
    {
        dprintf_colour("[RED]ERROR: Main App busy : %d[WHITE]\r\n" , appData.state);
        return;
    }

    /* this looks like a kludge, but it seems to give the UI enough time */
    /* to finish drawing the button and prevent it from flashing when the */
    /* configuration screen is subsequently closed */
    appData.state = APP_STATE_BEGIN_CONFIGURE;
    appData.screen = screen;
    SYS_TIME_DelayMS(100, &appData.sysDelayHandle);
}
/*******************************************************************************
  Function:


  Remarks:
    switch to a configuration screen
*******************************************************************************/
static void app_open_configuration_screen(APP_SCREENS screen)
{
    appData.substate = APP_SUB_STATE_IDLE;

    dprintf_colour("[YELLOW]Switched to %s screen[WHITE]\r\n", screen_name[screen]);

    switch (screen)
    {
        case APP_SCREEN_DEVICE_SETUP:
        {
            appData.state = APP_STATE_DEVICE_SETUP;
            break;
        }

        case APP_SCREEN_CAMERA_SETUP:
        {
            /* hide the buttons at the bottom of the screen */
            app_show_main_screen_buttons(LA_FALSE);
            show_camera_settings_dialog();
            appData.state = APP_STATE_CAMERA_SETUP;
            break;
        }

        case APP_SCREEN_DISPLAY_SETUP:
        {
            appData.state = APP_STATE_DISPLAY_SETUP;
            break;
        }

        default:
            break;
    }
}
/*******************************************************************************
  Function:


  Remarks:
    exit from any of the configuration screens
*******************************************************************************/
void app_exit_configure(void)
{
    appData.substate = APP_SUB_STATE_COMPLETE;
    set_pca9530_leds_off();
}
/*******************************************************************************
  Function:


  Remarks:
    called when a status message has been received from the data acquisition board
*******************************************************************************/
void app_update_status(uint8_t * status)
{
    memcpy(&appData.status, (_STATUS_BUFFER *) status, sizeof(_STATUS_BUFFER));
    
    // update battery state
    app_set_battery_state(appData.battery_percentage, appData.chargeState, appData.batteryState);

    // update LASER state
    app_set_laser_state(appData.status.DAB.Flags.LON, appData.status.DAB.Flags.LPON);

    // update USB state
    app_set_usb_state(appData.status.DAB.Flags.USB);

    // update scanning state
    app_set_scanning_state(appData.status.DAB.Flags.Scanning);

    // update saturated state
    app_set_saturated_state(appData.status.DAB.Flags.Saturated);
    
    laWidget_Invalidate((laWidget*) StatusBarPanelWidget);

    if( ( !appData.splash_version_updated ) && ( appData.status.LSC.Version != 0U ) && ( appData.PEVersion != 0U ) )
    {
        dputs_colour("[PINK]Splash updated....[WHITE]\r\n");
        appData.splash_version_updated = true;
        app_update_splash_version();
    }

    if( appData.wait_for_status )
    {
        appData.wait_for_status = false;
        dputs_colour("[PINK]Status updated.[WHITE]\r\n");
        laWidget_SetEnabled((laWidget *) ScanButtonWidget, LA_TRUE );
    }

    if((appData.status.status_id == 1) && (appData.status.status_sub_id == 2)){
        //dprintf_colour("[PINK]Status ID: %d and SUB ID: $d received.[WHITE]\r\n",appData.status.status_id,appData.status.status_sub_id);
    }
    else if((appData.status.status_id == 0) && (appData.status.status_sub_id == 0)){
        dputs_colour("[RED]ERROR: status id and sub id equals to 0.[WHITE]\r\n");
    }
    else if((appData.status.status_id == 3) && (appData.status.status_sub_id == 25)){
        dputs_colour("[RED]ERROR: EEPROM data corrupted.[WHITE]\r\n");
        appData.prevstate = appData.state;
        appData.state = APP_STATE_ERROR;
        sprintf(appData.error_string, "\nPDAB ERROR.\nID: %d.%d\nEEPROM data corrupted.",appData.status.status_id,appData.status.status_sub_id);
    }
    else
    {
        dprintf_colour("[RED]ERROR: received error states in status message.[%d,%d][WHITE]\r\n",appData.status.status_id,appData.status.status_sub_id);
        appData.prevstate = appData.state;
        appData.state = APP_STATE_ERROR;
        sprintf(appData.error_string, "\nPDAB ERROR.\nID: %d.%d\nNo Description.",appData.status.status_id,appData.status.status_sub_id);
    }
    appData.status_updated = true;
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_update_splash_version(void)
{
    char temp_string[50];
    
    sprintf(temp_string, "Device ID: %s\nScans counter: %d", device_settings_for_PI.device_name, device_settings_for_PI.scans_counter);

    laString verStr0 = laString_CreateFromCharBuffer(temp_string, &Apertura_20);
    laLabelWidget_SetText(DeviceIDLabel, verStr0);
    laString_Destroy(&verStr0);

    sprintf(temp_string, "PE Version %1.2f", ((float)appData.PEVersion) / 100U  );
    dprintf_colour("[PINK]PE Version %1.2f[WHITE]\r\n", ((float)appData.PEVersion) / 100U  );
    laString verStr1 = laString_CreateFromCharBuffer(temp_string, &Apertura_20);
    laLabelWidget_SetText(PEVersionLabel, verStr1);
    laString_Destroy(&verStr1);

    sprintf(temp_string, "PDA Version %1.2f", ((float)appData.status.DAB.Version) / 100U );
    dprintf_colour("[PINK]PDA Version %1.2f[WHITE]\r\n", ((float)appData.status.DAB.Version) / 100U );
    laString verStr2 = laString_CreateFromCharBuffer(temp_string, &Apertura_20);
    laLabelWidget_SetText(PDAVersionLabel, verStr2);
    laString_Destroy(&verStr2);

    sprintf(temp_string, "LSC Version %1.2f", ((float)appData.status.LSC.Version) / 100U );
    dprintf_colour("[PINK]LSC Version %1.2f[WHITE]\r\n", ((float)appData.status.LSC.Version) / 100U );
    laString verStr3 = laString_CreateFromCharBuffer(temp_string, &Apertura_20);
    laLabelWidget_SetText(LSCVersionLabel, verStr3);
    laString_Destroy(&verStr3);

    sprintf(temp_string, "PI Version %1.2f", VERSION );
    dprintf_colour("[PINK]PI Version %1.2f Build %03d[WHITE]\r\n",  VERSION, BUILD );
    laString verStr4 = laString_CreateFromCharBuffer(temp_string, &Apertura_20);
    laLabelWidget_SetText(PIVersionLabel, verStr4);
    laString_Destroy(&verStr4);

    laWidget_SetVisible((laWidget *)DeviceIDLabel, LA_TRUE);
    laWidget_SetVisible((laWidget *)PIVersionLabel, LA_TRUE);
    laWidget_SetVisible((laWidget *)PDAVersionLabel, LA_TRUE);
    laWidget_SetVisible((laWidget *)LSCVersionLabel, LA_TRUE);
    laWidget_SetVisible((laWidget *)PEVersionLabel, LA_TRUE);
}
/*******************************************************************************
  Function:


  Remarks:
    exit from any of the configuration screens
*******************************************************************************/
void app_zero_offset(void)
{
    if( appData.measurement_display_timer > 0U )
    {
        appData.measurement_display_timer = 0U;
        appData.remove_measurement = true;
    }

    scan_reset_measurement_index();

    app_send_zero_offset_command();
    #ifndef DISABLE_AUDIO
    piezo_two_tone(DRV_PIEZO_TONE_1, 100U, 100U,DRV_PIEZO_TONE_2, 100U);
    #endif
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_frame_received( GFXU_ImageAsset* image )
{
    if (image != NULL)
    {
        if( appData.process_image == false )
        {
            appData.image = image;
            appData.process_image = true;
        }
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_gui_tasks( void )
{
    if(DRV_CAMERA_OVM7692_Is_Paused(sysObj.drvOVM7692)){
        //execute screen updates if required
        if (appData.update_status_bar)
        {
            appData.update_status_bar = false;
            app_update_status_bar();
        }
        
        //skip image processing if camera paused
        return;
    }
    
    
    if (appData.process_image)
    {
        if ( app_process_frame(appData.scanState, &appData.pk1_image ) )
        {
            if (appData.wait_for_alignment)
            {
                appData.wait_for_alignment = false;
                appData.start_scanning = true;
            }

            IP_VALID_Set();
        }
        else
        {
            IP_VALID_Clear();
        }

        #ifdef DEBUG_IP
        dprintf_colour("[BROWN]Frame processed.[WHITE]\r\n" );
        #endif

        app_update_frame();
        appData.process_image = false;
    }

    if (appData.get_status)
    {
        if(check_if_pwr_coms_quiet_window() == false)
        {
            appData.get_status = false;
            send_command_to_PDAB(COMMAND_GET_STATUS, NULL, 0);
        }
    }

    if(appData.get_settings)
    {
        send_command_to_PDAB(COMMAND_REQUEST_SETTINGS, NULL, 0);
    }

#ifndef DISABLE_PIC24
    if (appData.get_pic24_status)
    {
        if(check_if_pwr_coms_quiet_window() == false)
        {
            appData.get_pic24_status = false;
            pic24_send_command(PIC24_COMMAND_GET_STATUS, NULL, 0);
        }
    }

    if (appData.get_pic24_version)
    {
        appData.get_pic24_version = false;
        pic24_send_command(PIC24_COMMAND_REQUEST_VERSION, NULL, 0);
    }
#endif

    if (appData.update_status_bar)
    {
        appData.update_status_bar = false;
        app_update_status_bar();
    }

    if (appData.start_scanning)
    {
#ifndef DISABLE_SCANNING
        appData.start_scanning = false;
        scan_start();
#endif
    }

    if (appData.stop_scanning)
    {
        appData.stop_scanning = false;
        scan_stop();
        appData.get_status = true;
    }

    if (appData.remove_measurement)
    {
        appData.remove_measurement = false;
#ifdef PAUSE_CAMERA
        //laWidget_SetVisible((laWidget*)CrosshairWidget, LA_FALSE );
        DRV_CAMERA_OVM7692_Resume(sysObj.drvOVM7692);
#endif
        app_update_gui_measurements();
        power_management_suspend(false);
    }
}
/******************************************************************************
  Function:
    void APP_Tasks(void)

  Remarks:
    See prototype in app.h
*******************************************************************************/
void APP_Tasks(void)
{
    static uint16_t status_timeout = 0U;
    static uint16_t system_init_timeout = 0U;
    app_gui_tasks();
    /* Check the application's current state */
    switch (appData.state)
    {
        /* Application's initial state */
        case APP_STATE_SPLASH:
        {
            dprintf("\033\143");                                                // Clear terminal
            dprintf("\033[3JResetting terminal and clearing scroll-back\r\n");  // Clear scroll back
            dputs_colour("[GREEN]APP_STATE_SPLASH[WHITE]\r\n");
            send_command_to_PDAB(COMMAND_REQUEST_SETTINGS, NULL, 0);

            set_default_settings();

            #ifndef DISABLE_PIC24
            appData.get_pic24_version = true;
            #endif

            laContext_SetActiveScreen(APP_SCREEN_SPLASH);

            appData.prevstate = appData.state;
            appData.state = APP_STATE_INIT;
            break;
        }
        case APP_STATE_INIT:
        {
            dputs_colour("[GREEN]APP_STATE_INIT[WHITE]\r\n");

            drv_cst130_touch_callback_set(app_touch_callback);

            power_up_callback_set(app_power_up_callback);
            power_down_callback_set(app_power_down_callback);
            power_off_callback_set(app_power_off_callback);

            drv_display_set_enable();
            app_set_lcd_brightness(settings_get_lcd_brightness());                      // Set LCD brightness

            /* Put the BT module in standby */
            BM71_STBYRST_Clear();

            appData.drvCameraHandle = DRV_CAMERA_OVM7692_Open(DRV_CAMERA_OVM7692_INDEX_0, DRV_IO_INTENT_BLOCKING);

            if (DRV_HANDLE_INVALID == appData.drvCameraHandle)
            {
                sprintf(appData.error_string, "Camera initialisation failed\n" );
                appData.prevstate = appData.state;
                appData.state = APP_STATE_ERROR;
            }
            else
            {
                appData.prevstate = appData.state;
                appData.state = APP_STATE_WAIT_FOR_STATUS;
            }

            break;
        }

        case APP_STATE_WAIT_FOR_STATUS:
        {
            if( app_logo_animation(false) )
            {
                appData.logo_animation = false;
                //dprintf_colour("[PINK]appData.status.LSC.flags.TUNE_FINISHED = %d[WHITE]\r\n", appData.status.LSC.flags.TUNE_FINISHED);
                //dprintf_colour("[PINK]appData.status.DAB.Flags.Initialised = %d[WHITE]\r\n", appData.status.DAB.Flags.Initialised);
                if( appData.splash_version_updated == true && appData.status.LSC.flags.TUNE_FINISHED == true && appData.status.DAB.Flags.Initialised == true)
                {
                    appData.state = APP_Wait(500U, APP_STATE_START_SERVICE);
                    dputs_colour("[PINK]Starting service...[WHITE]\r\n");
                    
                }
                else if (appData.splash_version_updated == false)
                {
                    if(status_timeout++ > 10U )                                     // ~10 second timeout
                    {
                        appData.prevstate = appData.state;
                        appData.state = APP_STATE_ERROR;
                        sprintf(appData.error_string, "Timed out waiting for versions\n" );
                        dputs_colour("[PINK]Timed out waiting for versions[WHITE]\r\n");
                    }
                    else
                    {
                        appData.get_status = true;
                        reset_sleep_counter();
                        appData.state = APP_Wait( 500U, APP_STATE_WAIT_FOR_STATUS );
                    }
                }else{
                    //timeout is incremented every half-second
                    if(system_init_timeout++ > SYSTEM_INIT_TIMEOUT_30seconds )
                    {
                        appData.prevstate = appData.state;
                        appData.state = APP_STATE_ERROR;
                        sprintf(appData.error_string, "Timed out waiting for LSC/PDA init\n" );
                        dputs_colour("[PINK]Timed out waiting for LSC & PDA init[WHITE]\r\n");
                    }
                    else
                    {
                        appData.get_status = true;
                        reset_sleep_counter();
                        appData.state = APP_Wait( 500U, APP_STATE_WAIT_FOR_STATUS );
                    }
                }
            }
//            else
//            {
//                appData.state = APP_Wait( 1U, APP_STATE_WAIT_FOR_STATUS );
//            }
            break;
        }

        case APP_STATE_START_SERVICE:
        {
            set_pca9530_led_pwm0_rate(PCA9530_PWM_152HZ, settings_get_led_brightness());
            set_pca9530_led_pwm1_rate(PCA9530_PWM_152HZ, settings_get_led_brightness());
            app_set_lcd_brightness(settings_get_lcd_brightness());                      // Set brightness again incase saved settings are different.
            
            dputs_colour("[PINK]SetActiveScreen(APP_SCREEN_MAIN)[WHITE]\r\n");
            laContext_SetActiveScreen(APP_SCREEN_MAIN);
            appData.prevstate = appData.state;
            appData.state = APP_STATE_IDLE;
            reset_sleep_counter();

            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            appData.state = APP_STATE_IDLE;
            break;
        }

        case APP_STATE_SET_TIME:
        case APP_STATE_DEVICE_SETUP:
        case APP_STATE_DISPLAY_SETUP:
        {
            if (APP_SUB_STATE_IDLE == appData.substate)
            {
                laContext_SetActiveScreen(appData.screen);
                appData.prevstate = appData.state;
                appData.substate = APP_SUB_STATE_BUSY;
            }
            else if (APP_SUB_STATE_COMPLETE == appData.substate)
            {
                laContext_SetActiveScreen(APP_SCREEN_MAIN);
                appData.prevstate = appData.state;
                appData.state = APP_STATE_IDLE;
                appData.substate = APP_SUB_STATE_IDLE;
            }
            break;
        }

        case APP_STATE_CAMERA_SETUP:
        {
            if (APP_SUB_STATE_COMPLETE == appData.substate)
            {
                laContext_SetActiveScreen(APP_SCREEN_MAIN);
                app_show_main_screen_buttons(LA_TRUE);
                appData.prevstate = appData.state;
                appData.state = APP_STATE_IDLE;
                appData.substate = APP_SUB_STATE_IDLE;
            }
            break;
        }

        case APP_STATE_WAIT:
        {
            if (appData.sysDelayHandle != SYS_TIME_HANDLE_INVALID)
            {
                // Check if the delay has expired
                if (SYS_TIME_DelayIsComplete(appData.sysDelayHandle))
                {
                   appData.prevstate = appData.state;
                   appData.state = appData.nextstate;
                   appData.nextstate = APP_STATE_IDLE;
                   appData.sysDelayHandle = SYS_TIME_HANDLE_INVALID;
                }
            }
            else
            {
                appData.prevstate = appData.state;
                appData.state = APP_STATE_ERROR;
            }

            break;
        }

        case APP_STATE_IDLE:
        {
            break;
        }

        case APP_STATE_BEGIN_CONFIGURE:
        {
            if ( SYS_TIME_DelayIsComplete(appData.sysDelayHandle) )
            {
                appData.sysDelayHandle = SYS_TIME_HANDLE_INVALID;
                app_open_configuration_screen(appData.screen);
            }
            break;
        }

        case APP_STATE_ERROR:
        {
            if(  laContext_GetActiveScreenIndex() != APP_SCREEN_ERROR )
            {
                dputs_colour("[PINK]SetActiveScreen(APP_SCREEN_ERROR)[WHITE]\r\n");
                laContext_SetActiveScreen(APP_SCREEN_ERROR);
            }
            else
            {
               app_update_error_state();
               DBG_LEDR_Clear();
            }

            break;
        }

        /* The default state should never be executed */
        default:
        {
            /* TODO: Handle error in application's state machine */
            break;
        }
    }
}
/*******************************************************************************
 End of File
 */
