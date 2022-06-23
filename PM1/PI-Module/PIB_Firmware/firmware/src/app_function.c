/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occutity Limited

  @File Name
    app_function.c

  @Summary
    Miscellaneous app functions.

  @Description
    App functions.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "definitions.h"
#include "drv_camera_ovm7692.h"

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

// set the LED brightness
void app_set_led_brightness(uint8_t pwm, bool state)
{
    set_pca9530_led_pwm0_rate(PCA9530_PWM_152HZ, pwm);
    set_pca9530_led_pwm1_rate(PCA9530_PWM_152HZ, pwm);
    
    if (DRV_LED_OFF == state)
    {
        set_pca9530_leds_off() ;
        appData.ledState = DRV_LED_OFF;
    }
    else
    {
        set_pca9530_leds_on(); 
        appData.ledState = DRV_LED_ON;
    }
}

// set the brightness of the LCD backlight
void app_set_lcd_brightness(uint8_t percent)
{
    uint16_t dc = 0;
    
    if (0U == percent)
    { 
        OCMP3_Disable();                         // Start PWM 
        TMR2_Stop();                             // Set to run at 20kHz (5000 clock cycles))   
        DISPLAY_BL_OutputEnable();
        DISPLAY_BL_Clear();                                 /* turn off the LCD back light */
        appData.lcdState = false;
    }
    else
    {
        if (percent > 100U)
        {
            percent  = 100U;
        }

        dc = 500 * percent;

        OCMP3_CompareSecondaryValueSet(dc);     // Set duty cycle to 20% (4000/5000)
        OCMP3_Enable();                         // Start PWM 
        TMR2_Start();                           // Set to run at 1kHz (20000 clock cycles)) 
        appData.lcdState = true;
    }
}

// send the update settings command to the PDAB
void app_send_pdab_settings_command(void)
{
    _SCAN_SETTINGS scan_settings;
    
    dputs_colour("[PINK]Sending pdab settings command[WHITE]\r\n");

    /* read the settings */
    read_scan_settings(&scan_settings);

    /* send the scan settings to the PDAB */
    send_command_to_PDAB(COMMAND_UPDATE_SETTINGS, (uint8_t *) &scan_settings, sizeof(_SCAN_SETTINGS));
}

// send the zero offset command to the PDAB
void app_send_zero_offset_command(void)
{
    dputs_colour("[PINK]Sending zero offset command[WHITE]\r\n");

    /* send the command to trigger a zero offset */
    send_command_to_PDAB(COMMAND_ZERO_OFFSET, NULL, 0);
}

// send the zero offset command to the PDAB
void app_send_laser_check_command(void)
{
    dputs_colour("[PINK]Sending laser check command[WHITE]\r\n");

    /* send the command to trigger a zero offset */
    send_command_to_PDAB(COMMAND_LASER_CHECK, NULL, 0);
}

void app_touch_callback( uint16_t* context )
{
    power_management_activity_trigger();     
}

extern const DRV_CAMERA_OVM7692_INIT drvCameraInit;
void app_power_up_callback( uint16_t* context )
{
    dputs_colour("[GREEN]POWERUP CALLBACK[WHITE]\r\n"); 
    /* turn everything back on */
    //DRV_CAMERA_OVM7692_DeInitialize(sysObj.drvOVM7692);
    //DRV_CAMERA_OVM7692_Initialize(sysObj.drvOVM7692,(SYS_MODULE_INIT *) &drvCameraInit);
    //DRV_CAMERA_OVM7692_Resume(sysObj.drvOVM7692);       /* turn the camera back on */
    //ST7701S_Init();                                     /* reinitialise the display */
    //drv_display_set_enable();
    //app_set_lcd_brightness(settings_get_lcd_brightness());  
    
    laWidget_SetEnabled((laWidget *) MenuButtonWidget, LA_TRUE );
    laWidget_SetEnabled((laWidget *) ScanButtonWidget, LA_TRUE );        
}

void app_power_down_callback( uint16_t* context )
{
    /* turn everything off */
    app_set_lcd_brightness(0U);                         /* stop back light PWM */
#ifndef DISPLAY_800X340
    DISPLAY_BL_Set();                                   /* turn off the LCD back light */
#endif
    set_pca9530_leds_off();
    /* buzzer_Off() */                                  /* turn off the buzzer */
    BM71_STBYRST_Clear();                               /* Put the Bluetooth module into standby */
    DRV_CAMERA_OVM7692_Pause(sysObj.drvOVM7692);        /* turn the camera off */
     
    laWidget_SetEnabled((laWidget *) MenuButtonWidget, LA_FALSE );
    laWidget_SetEnabled((laWidget *) ScanButtonWidget, LA_FALSE );    
}

void app_power_off_callback( uint16_t* context )
{
#ifndef DISABLE_PIC24
    app_send_power_down_request();
#endif  
}

void app_send_power_down_request(void)
{
    send_command_to_PDAB(COMMAND_IS_SHUTDOWN_SAFE, NULL, 0);
}
/* *****************************************************************************
 End of File
 */
