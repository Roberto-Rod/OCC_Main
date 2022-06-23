/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    app_ui_state.c

  @Summary
    Functions for updating the state of the main User Interface.

  @Description
    Update state of battery, USB icon, LASER icon, etc.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "app_ui_state.h"
#include "gfx/libaria/inc/libaria_utils.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

extern APP_DATA appData;

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */



/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
bool app_logo_animation(bool reset)
{
    static uint16_t counter = 0U;
    static uint32_t line_length = 0U;
    static int32_t arc_length = 0L;
    static int32_t start_angle = 180L;

    if(reset == true){
        counter = 0U;
        line_length = 0U;
        arc_length = 0L;
        start_angle = 180L;
    }

    if( counter < 200 )
    {
        if( counter++ == 0U )
        {
            laWidget_SetVisible((laWidget *) StartCircle, LA_TRUE );
            laWidget_SetVisible((laWidget *) LogoLine, LA_TRUE );
            laWidget_SetVisible((laWidget *) LogoCircle, LA_TRUE );
        }
        else
        {
            if( !( counter % 8 ) && ( start_angle > 130 ) )
            {
                start_angle -= 4;
                laCircularSliderWidget_SetStartAngle( LogoCircle, start_angle );
            }

            if( !( counter % 4 ) && arc_length < 100 )
            {
                arc_length += 4;
                laCircularSliderWidget_SetValue( LogoCircle, arc_length );
            }

            if( !( counter % 4 ) && (  line_length < 110 ) )
            {
                line_length += 4;
                laProgressBarWidget_SetValue( LogoLine, line_length );
            }
        }

        return false;
    }
    else
    {
        return true;
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_update_status_bar(void)
{

    if (appData.status_updated)
    {
        appData.status_updated = false;

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

        #ifndef DISABLE_USB_ILLUMINATION
        // Update UI scan state
        if (appData.status.DAB.Flags.Scanning && appData.status.DAB.Flags.USB && !appData.scanState)
        {
            app_set_scan_state(true);
        }
        else if (!appData.status.DAB.Flags.Scanning && appData.status.DAB.Flags.USB && appData.scanState)
        {
            app_set_scan_state(false);
        }
        #endif
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_update_error_state(void)
{
    static bool updated = false;
    char errorstring[512];

    if( false == updated )
    {
        sprintf(errorstring,
                "Last State: %d\nError Code: %d\n%s",
                appData.prevstate,
                appData.error_code,
                appData.error_string );

        laString errorStr = laString_CreateFromCharBuffer(errorstring, &Apertura_14);
        laLabelWidget_SetText(ErrorLabelWidget, errorStr);
        laString_Destroy(&errorStr);
        laWidget_Invalidate((laWidget*) ErrorLabelWidget);
        updated = true;
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
/* update the battery icon */
void app_set_battery_state(uint8_t battery_charge_percentage, bool battery_charging, bool low_battery)
{
    static uint8_t old_battery_charge_percentage = 100U;
    static bool old_battery_charging = false;
    static bool old_low_battery = false;

    /* only update if changed */
    if (old_battery_charge_percentage != battery_charge_percentage)
    {
        // show battery percentage
        laProgressBarWidget_SetValue(BatteryWidget, battery_charge_percentage);
    }

    if (old_battery_charging != battery_charging)
    {
        // show the battery charging or not charging
        laWidget_SetVisible((laWidget *) ChargeWidget, battery_charging ? LA_TRUE : LA_FALSE);
    }

    // show low battery / battery OK
    if (low_battery != old_low_battery)
    {
        if (low_battery)
        {
            laWidget_SetScheme((laWidget *) BatteryWidget, &BatteryVolumeLow);
            laWidget_SetScheme((laWidget *) BatteryWidget2, &BatteryVolumeLow);
        }
        else
        {
            laWidget_SetScheme((laWidget *) BatteryWidget, &BatteryVolume);
            laWidget_SetScheme((laWidget *) BatteryWidget2, &BatteryVolume);
        }
    }

    old_battery_charge_percentage = battery_charge_percentage;
    old_battery_charging = battery_charging;
    old_low_battery = low_battery;
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
/* update the USB icon (shown or not shown) */
void app_set_usb_state(bool state)
{
    static bool usb_state = true;
    
    if(state){
        //never go sleep when USB is connected
        reset_sleep_counter();
    }
    
    if (usb_state != state)
    {
        if(state == false)
        {
            dputs_colour("[RED]USB is disconnected, reducing menu.[WHITE]\r\n");

            laWidget_SetEnabled((laWidget *)CameraSettingsMenuButtonWidget,LA_FALSE);
            laWidget_SetVisible((laWidget *)CameraSettingsMenuButtonWidget,LA_FALSE);
            
            laWidget_SetY((laWidget *)DeviceSettingsMenuButtonWidget,154);

            laWidget_SetEnabled((laWidget *)DisplaySettingsMenuButtonWidget,LA_FALSE);
            laWidget_SetVisible((laWidget *)DisplaySettingsMenuButtonWidget,LA_FALSE);
        }
        else
        {
            dputs_colour("[RED]USB is connected, expanding menu.[WHITE]\r\n");

            laWidget_SetEnabled((laWidget *)CameraSettingsMenuButtonWidget,LA_TRUE);
            laWidget_SetVisible((laWidget *)CameraSettingsMenuButtonWidget,LA_TRUE);
            
            laWidget_SetY((laWidget *)DeviceSettingsMenuButtonWidget,104);

            laWidget_SetEnabled((laWidget *)DisplaySettingsMenuButtonWidget,LA_TRUE);
            laWidget_SetVisible((laWidget *)DisplaySettingsMenuButtonWidget,LA_TRUE);
        }
        laWidget_SetVisible((laWidget *) UsbWidget, state ? LA_TRUE : LA_FALSE);
        usb_state = state;
    }
    
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
/* update the scanning icon (shown or not shown) */
void app_set_scanning_state(bool state)
{
    static bool scanning_state = false;

    if (scanning_state != state)
    {
        laWidget_SetVisible((laWidget *) ScanWidget, state ? LA_TRUE : LA_FALSE);
        scanning_state = state;
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
/* update the saturated icon (shown or not shown) */
void app_set_saturated_state(bool state)
{
    static bool saturated_state = false;

    if (saturated_state != state)
    {
        laWidget_SetVisible((laWidget *) SaturatedWidget, state ? LA_TRUE : LA_FALSE);
        saturated_state = state;
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
/* update the LASER icon (shown or shown flashing to indicate error) */
void app_set_laser_state(bool laser_on, bool laser_power_on)
{
    static bool old_laser_symbol_on = false;
    static bool error_symbol_on = false;
    bool laser_symbol_on;

    if (laser_on)
    {
        if (laser_power_on)
        {
            // show LASER on
            laser_symbol_on = true;
        }
        else
        {
            // show LASER error
            error_symbol_on = true;
            laser_symbol_on = old_laser_symbol_on;                              // Ensure symbol is redrawn
            dprintf_colour("[RED]Showing LASER error[WHITE]\r\n", laser_on);

            appData.prevstate = appData.state;
            appData.state = APP_STATE_ERROR;
            sprintf(appData.error_string, "Laser power detected\nSafety circuit may have tripped\n" );
        }
    }
    else
    {
        /* un-commanded LASER activation - SW1 is probably in the test position */
        if (laser_power_on)
        {
            error_symbol_on = true;
            laser_symbol_on = !old_laser_symbol_on;                             // Ensure symbol is redrawn
            play_notification(play_LASER_ERROR);

            appData.prevstate = appData.state;
            appData.state = APP_STATE_ERROR;
            sprintf(appData.error_string, "Laser power detected when disabled\nSafety circuit may be disabled\n" );
        }
        else
        {
            // show LASER off
            laser_symbol_on = false;
        }
    }

    if (old_laser_symbol_on != laser_symbol_on)
    {
        /* only update if changed */
        laWidget_SetVisible((laWidget *) LaserWidget, laser_symbol_on ? LA_TRUE : LA_FALSE);
        laWidget_SetVisible((laWidget *) LaserErrorWidget, error_symbol_on ? LA_TRUE : LA_FALSE);
        
    }
    old_laser_symbol_on = laser_symbol_on;
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_update_frame( void )
{
    app_update_alignment_ui();

    laImagePlusWidget_SetImage(CameraWidget, appData.image);                        // Image data has been processed so we can now update the frame without issue
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void App_ScanButtonWidget_PressedEvent(laButtonWidget* btn)
{
    dprintf_colour("[YELLOW]SCAN BTN[WHITE]\r\n");

    //if( appData.measurement_display_timer > 0U )
    if(DRV_CAMERA_OVM7692_Is_Paused(sysObj.drvOVM7692) == true)
    {
		app_update_gui_measurements();
#ifdef PAUSE_CAMERA
        DRV_CAMERA_OVM7692_Resume(sysObj.drvOVM7692);
#endif
        appData.measurement_display_timer = 0U;
        appData.remove_measurement = false;
    }

    if( true == appData.scanState )
    {
        if(DRV_CAMERA_OVM7692_Is_Paused(sysObj.drvOVM7692) == false)
        {
            appData.scan_stop_btn_press_counter++;
        }
        appData.start_scanning = false;
        appData.wait_for_alignment = false;
        appData.stop_scanning = true;
    }
    else
    {
        appData.scan_start_btn_press_counter++;
        appData.press_to_scan_timer = _CP0_GET_COUNT();
        if(settings_get_wait_for_alignment())
        {
            appData.start_scanning = false;
            appData.wait_for_alignment = true;
        }
        else
        {
            appData.start_scanning = true;
        }

        /* if we need to wait for the device to be aligned */
        app_set_scan_state(true);
        /* Reset scan progress parameters */
        scan_reset();
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_show_main_screen_buttons(laBool visible)
{
    laWidget_SetVisible((laWidget *) MenuButtonWidget, visible);
    laWidget_SetVisible((laWidget *) ScanButtonWidget, visible);
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_enable_main_screen_buttons(laBool enabled)
{
    laWidget_SetEnabled((laWidget *) MenuButtonWidget, enabled);
}
/*******************************************************************************
  Function:


  Remarks:
    show / hide the scanning progress bar and set its value
*******************************************************************************/
void app_update_measurement_value( _NPDA_MEASUREMNT* result, uint16_t index, uint8_t alpha, bool visible )
{
    char temp_string[40];
    laLabelWidget* thk = MeasurementWidget0; 
    laLabelWidget* std = StdevWidget0; 
    laLabelWidget* sc = ScanLabelWidget0;
        
    if( index == 1 )
    {
        thk = MeasurementWidget1; 
        std = StdevWidget1; 
        sc = ScanLabelWidget1;
    }
    else if( index == 2 )
    {
        thk = MeasurementWidget2; 
        std = StdevWidget2; 
        sc = ScanLabelWidget2;
    }
    else if( index == 3 )
    {
        thk = MeasurementWidget3; 
        std = StdevWidget3; 
        sc = ScanLabelWidget3;
    }    
    
    if( visible )
    {
        sprintf(temp_string, "%03.0f", result->thickness );
        laString measurementStr = laString_CreateFromCharBuffer(temp_string, &Apertura_48);
        laLabelWidget_SetText(thk, measurementStr);
        
        sprintf(temp_string, "±%1.1f\num", result->std );
        laString stdevStr = laString_CreateFromCharBuffer(temp_string, &Apertura_24);
        laLabelWidget_SetText(std, stdevStr);

        sprintf(temp_string, "%d/\n%d", result->valid_blocks, result->total_blocks );
        laString scStr = laString_CreateFromCharBuffer(temp_string, &Apertura_24);
        laLabelWidget_SetText(sc, scStr); 
        
        
        if( result->error == SUCCESS )
        {           
            laWidget_SetScheme((laWidget*)thk, &OverlayGreen);                 
            laWidget_SetScheme((laWidget*)std, &OverlayGreen);
            laWidget_SetScheme((laWidget*)sc, &OverlayGreen);                
        }
        else if( result->error == WARNING_FEW_VALID_BLOCKS ||
                 result->error == WARNING_PC_PEAKS_SMALL ||
                 result->error == WARNING_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS ||
                 result->error == WARNING_HIGH_DATA_SPREAD ||
                 result->error == WARNING_HIGH_DATA_SPREAD_AND_FEW_VALID_BLOCKS ||
                 result->error == WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL ||
                 result->error == WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS )
        {
            laWidget_SetScheme((laWidget*)thk, &OverlayYellow);                 
            laWidget_SetScheme((laWidget*)std, &OverlayYellow);
            laWidget_SetScheme((laWidget*)sc, &OverlayYellow);               
        }
        else if( result->error == ERROR_TOO_FEW_BLOCKS ||
                 result->error == ERROR_PC_PEAKS_TOO_SMALL ||
                 result->error == ERROR_SPREAD_TOO_HIGH )
        {
            laWidget_SetScheme((laWidget*)thk, &OverlayRed);
            laWidget_SetScheme((laWidget*)std, &OverlayRed);            
            laWidget_SetScheme((laWidget*)sc, &OverlayRed);        
        }
        else if( result->error == ERROR_CAL_NOT_STR_MON_INCREASING)
        {
            appData.prevstate = appData.state;
            appData.state = APP_STATE_ERROR;
            sprintf(appData.error_string, "ERROR_CAL_NOT_STR_MON_INCREASING\n" );
        }
        else if( result->error == ERROR_UNEXPECTED_FAILURE)
        {
            laWidget_SetScheme((laWidget*)thk, &OverlayRed);
            laWidget_SetScheme((laWidget*)std, &OverlayRed);            
            laWidget_SetScheme((laWidget*)sc, &OverlayRed); 
            
//            appData.prevstate = appData.state;
//            appData.state = APP_STATE_ERROR;
//            sprintf(appData.error_string, "ERROR UNEXPECTED FAILURE A\n" );
        }
        else
        {
            appData.prevstate = appData.state;
            appData.state = APP_STATE_ERROR;
            sprintf(appData.error_string, "ERROR_UNKNOWN_NPDA_ERROR_VALUE\n" );
        }
        laString_Destroy(&measurementStr);
        laString_Destroy(&stdevStr);
        laString_Destroy(&scStr);     
        laWidget_SetAlphaAmount((laWidget*) thk, alpha);
        laWidget_SetVisible((laWidget*) thk, LA_TRUE);      
    }
    else
    {
       laWidget_SetVisible((laWidget*) thk, LA_FALSE); 
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
/* update the alignment marks on the UI */
void app_update_alignment_ui_state(laScheme* scheme1, laScheme* scheme2, bool visible )
{
    appData.alignment_ui_scheme_1 = scheme1;
    appData.alignment_ui_scheme_2 = scheme2;
    appData.alignment_ui_visible = visible;
}


#define CIRCLE_RADIUS_MIN 20
#define CIRCLE_RADIUS_MAX 60
#define CIRCLE_RADIUS_DEFAULT 36
#define PROGRESSARC_RADIUS_DELTA 5

static uint16_t calculate_avgerage_rad(int32_t rad)
{
    static float average;
    if(rad == -99){
        average=CIRCLE_RADIUS_DEFAULT;
        return 0;
    }
    average += (rad - average) / 8.0f;
    return (uint16_t)average;
}
int32_t calculate_avgerage_z(int32_t z){
    static float average;
    if(z == -99){
        average=0;
        return 0;
    }
    average += (z - average) / 5.0f;
    return (int32_t)average;
}
/*******************************************************************************
  Function:


  Remarks:
    update the alignment marks on the UI
*******************************************************************************/
void app_update_alignment_ui(void)
{
    static bool visible = true;
    static uint32_t progress = 0U;
    
    uint32_t yellow_timeout_def = 50;
    static uint32_t yellow_timeout = 0;
    uint32_t green_timeout_def = 25;
    static uint32_t green_timeout = 0;
    
    static laScheme * color_scheme_prev;
    static laScheme * color_scheme = &OverlayRed;
    static int32_t middle_of_scan = 2500;
    static float z_factor = 0.01f;
    static uint16_t c_radius = CIRCLE_RADIUS_DEFAULT;
    static bool circle_out_of_range = false;

    int32_t z = scan_get_z_position();
    
    if( appData.alignment_ui_visible )
    {
        if(visible == false)
        {
            calculate_avgerage_rad(-99);//reset average
            progress = 0;
            visible = true;
            c_radius = CIRCLE_RADIUS_DEFAULT;
            laArcWidget_SetCenterAngle((laArcWidget*) ScanningProgressArcWidget, 0);//reset progress
            laArcWidget_SetStartAngle((laArcWidget*) ScanningProgressArcWidget, -90);//reset progress
            laWidget_SetVisible((laWidget*)CameraAlignmentArcWidget, LA_TRUE );
            //laWidget_SetVisible((laWidget*)ScanningProgressArcWidget, LA_TRUE );
            color_scheme = &OverlayRed;
        }
    }
    else
    {
        if(visible == true)
        {
            visible = false;
            laWidget_SetVisible((laWidget*)CameraAlignmentArcWidget, LA_FALSE );
            laWidget_SetVisible((laWidget*)ScanningProgressArcWidget, LA_FALSE );
        }
        return;
    }

    if ((z > MIN_SCAN_RANGE) && (z < MAX_SCAN_RANGE))
    {
        int zp = (int32_t)((float)(z - middle_of_scan) * z_factor);
        c_radius = CIRCLE_RADIUS_DEFAULT + zp;
        
        if(c_radius > CIRCLE_RADIUS_MAX){
            c_radius = CIRCLE_RADIUS_MAX;
            color_scheme = &OverlayRed;
            circle_out_of_range = true;
        }
        if(c_radius < CIRCLE_RADIUS_MIN){
            c_radius = CIRCLE_RADIUS_MIN;
            color_scheme = &OverlayRed;
            circle_out_of_range = true;
        }
        
        if (scan_get_progress() != progress) // Only update the widget is progress has changed
        {
            if (laWidget_GetVisible((laWidget*) ScanningProgressArcWidget) == LA_FALSE) {
                laWidget_SetVisible((laWidget*) ScanningProgressArcWidget, LA_TRUE);
            }
            green_timeout = green_timeout_def;
            progress = (uint16_t) scan_get_progress();
            uint16_t progress_radial = progress * 3.6f;
            laArcWidget_SetCenterAngle((laArcWidget*) ScanningProgressArcWidget, progress_radial);
            laArcWidget_SetStartAngle((laArcWidget*) ScanningProgressArcWidget, -progress_radial + 90);
        }
        
        if(yellow_timeout > 0 || green_timeout > 0)
        {
            if (yellow_timeout > 0) {
                yellow_timeout--;
                color_scheme = &OverlayYellow;
            }
            if (green_timeout > 0) {
                green_timeout--;
                color_scheme = &OverlayGreen;
            }
        }
        else
        {
            if( ( z > TARGET_RANGE_MIN ) && ( z < TARGET_RANGE_MAX ) )
            {
                color_scheme = &OverlayYellow;
            }
            else
            {
                color_scheme = &OverlayRed;
            }
        }
        
        if(color_scheme == &OverlayYellow && color_scheme_prev != &OverlayYellow){
            yellow_timeout = yellow_timeout_def;
        }
        if(color_scheme == &OverlayGreen && color_scheme_prev != &OverlayGreen){
            green_timeout = green_timeout_def;
        }
    }
    
    //dprintf_colour("[CYAN]c: %d[WHITE]\r\n", c_radius);
    c_radius = calculate_avgerage_rad(c_radius);
    if(visible == true)
    {
        laArcWidget_SetRadius(CameraAlignmentArcWidget, (c_radius));
        laArcWidget_SetRadius(ScanningProgressArcWidget, (c_radius + PROGRESSARC_RADIUS_DELTA));
    }
    if(color_scheme != color_scheme_prev){
        laWidget_SetScheme((laWidget*)CameraAlignmentArcWidget, color_scheme );
        color_scheme_prev = color_scheme;
    }
    
    laWidget_Invalidate((laWidget*) CameraWidget);
}

void app_update_alignment_ui2(void)
{    
    static bool visible = false;
    static uint32_t progress = 0U;
    static uint32_t z_count = 0U;
    
    static uint16_t timeout_def = 50;
    static laScheme * color_scheme_prev;
    static laScheme * color_scheme;
    static int32_t middle_of_scan = 2500;
    static uint16_t low_range = 500;
    static uint16_t high_range = 4500;
    static float z_factor = 0.01f;
    static uint16_t c_radius = CIRCLE_RADIUS_DEFAULT;
    static bool circle_out_of_range = false;

    if( appData.alignment_ui_visible )
    {
        int32_t z = scan_get_z_position();                                     // Retrieve the Z position
        z = calculate_avgerage_z(z);
        //dprintf_colour("[CYAN]Z: %d[WHITE]\r\n", z);
        
        //z = calculate_avgerage_z(z);
        
        if( ( z > MIN_SCAN_RANGE ) && ( z < MAX_SCAN_RANGE ) )
        {
            if(z<=low_range)
            {
                z=middle_of_scan;
            }
            if(z>high_range)
            {
                z=middle_of_scan;
            }
            
            
            circle_out_of_range = false;
            z = (int32_t)((float)(z - middle_of_scan) * z_factor);
            c_radius = CIRCLE_RADIUS_DEFAULT - z;
            if(c_radius > CIRCLE_RADIUS_MAX){
                c_radius = CIRCLE_RADIUS_MAX;
                color_scheme = &OverlayRed;
                circle_out_of_range = true;
            }
            if(c_radius < CIRCLE_RADIUS_MIN){
                c_radius = CIRCLE_RADIUS_MIN;
                color_scheme = &OverlayRed;
                circle_out_of_range = true;
            }
            laArcWidget_SetRadius(CameraAlignmentArcWidget, (c_radius));
            laArcWidget_SetRadius(ScanningProgressArcWidget, (c_radius + PROGRESSARC_RADIUS_DELTA)); 
            
            if( ( z > TARGET_RANGE_MIN ) && ( z < TARGET_RANGE_MAX ) )
            {
                if(false == circle_out_of_range)
                {
                    if(appData.delay_after_scan < timeout_def)
                    {
                        appData.delay_after_scan++;
                    }
                    else
                    {
                        if(progress == 100){
                            //laWidget_SetVisible((laWidget*)ScanningProgressArcWidget, LA_FALSE );
                            //laArcWidget_SetRadius(CameraAlinmentArcWidget,( ( PK1_MAX_RADIUS + PK1_MIN_RADIUS ) - circle->radius ) ); 
                        }
                        color_scheme = &OverlayYellow;
                    }
                }
            }
            else
            {
                color_scheme = &OverlayRed;
            }
        }
        else
        {
            laArcWidget_SetRadius(ScanningProgressArcWidget, (CIRCLE_RADIUS_DEFAULT + PROGRESSARC_RADIUS_DELTA));
            laArcWidget_SetRadius(CameraAlignmentArcWidget,(CIRCLE_RADIUS_DEFAULT)); 
            color_scheme = &OverlayRed;
        }
        
        if( scan_get_progress() != progress)                                    // Only update the widget is progress has changed
        {
            if(scan_get_progress() == 10){
                laWidget_SetVisible((laWidget*)ScanningProgressArcWidget, LA_TRUE );
            }
            progress = (uint16_t)scan_get_progress();
            uint16_t progress_radial = progress * 3.6f;
            laArcWidget_SetCenterAngle((laArcWidget*)ScanningProgressArcWidget,progress_radial);
            laArcWidget_SetStartAngle((laArcWidget*)ScanningProgressArcWidget,-progress_radial+90);
        }
        if(visible != appData.alignment_ui_visible)
        {
#ifdef PAUSE_CAMERA        
            DRV_CAMERA_OVM7692_Resume(sysObj.drvOVM7692); 
#endif

            
            laArcWidget_SetRadius(CameraAlignmentArcWidget,PK1_MAX_RADIUS);             
            laWidget_SetVisible((laWidget*)CameraAlignmentArcWidget, LA_TRUE );
            laWidget_SetVisible((laWidget*)ScanningProgressArcWidget, LA_TRUE );
            
            z_count = 0U;
            visible = appData.alignment_ui_visible;
        }
    }
    else
    {
        dputs_colour("[WHITE](o.O) false[WHITE]\r\n");
        laWidget_SetVisible((laWidget*)CameraAlignmentArcWidget, LA_FALSE );
        laWidget_SetVisible((laWidget*)ScanningProgressArcWidget, LA_FALSE );         
        visible = appData.alignment_ui_visible;
    } 
    
    if(color_scheme != color_scheme_prev){
        laWidget_SetScheme((laWidget*)CameraAlignmentArcWidget, color_scheme );
        color_scheme_prev = color_scheme;
    }
}

/*******************************************************************************
  Function:


  Remarks:
    set scanning state (scanning or not scanning)
*******************************************************************************/
void app_set_scan_state(bool state)
{
    if (state)
    {
        app_update_alignment_ui_state(&OverlayRed, &OverlayRed, true);
        power_management_suspend(true);
        set_pca9530_leds_on();
        appData.ledState = DRV_LED_ON;
        appData.scanState = true;
        app_enable_main_screen_buttons( LA_FALSE );
    }
    else
    {
        set_pca9530_leds_off();
        app_update_alignment_ui_state(&OverlayGreen, &OverlayGreen, false);
        power_management_suspend(false);
        appData.ledState = DRV_LED_OFF;
        appData.scanState = false;
        app_enable_main_screen_buttons( LA_TRUE );
    }
}
/*******************************************************************************
  Function:


  Remarks:

*******************************************************************************/
void app_update_gui_measurements( void )
{
    uint8_t index = scan_get_measurement_index();

    if( index == 0U )
    {
        app_update_measurement_value( NULL, 0, 255, false );
        app_update_measurement_value( NULL, 1, 255, false );
        app_update_measurement_value( NULL, 2, 255, false );
        app_update_measurement_value( NULL, 3, 255, false );
    }
}
/* *****************************************************************************
 End of File
 */
