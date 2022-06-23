/* ************************************************************************** */
/** Descriptive File Name

  @Company
   Occuity Limited

  @File Name
    device_settings_screen.c

  @Summary
    Device settings dialogue box.

  @Description
    Allows the user to change device settings.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "gfx/libaria/libaria_events.h"
#include "definitions.h"

#define DIGI_POT_POSITIONS          128
#define PGA_FEEDBACK_RESISTOR       10000
#define DIGI_POT_WIPER_RESISTANCE   50
#define DIGI_POT_TRACK_RESISTANCE   10000
#define DIGI_POT_SERIES_RESISTOR    100

#define VALUE_FONT                  Apertura_14

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */



/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */


// calculate the gain of the amplifier, this ranges from 2 to 51
// with only 128 settings, this could be replaced by a lookup table
double calculate_amplifier_gain(uint16_t digipot_setting)
{
    double gain;
    double Rf;
    double Rg;
    double digipot_resistance;

    // for an op-amp, gain = 1 + (Rf / Rg) where Rf is the feedback resistor,
    // and Rg is the resistor connecting the inverting input to ground

    Rf = PGA_FEEDBACK_RESISTOR;
    digipot_resistance = (2 * DIGI_POT_WIPER_RESISTANCE) + (DIGI_POT_TRACK_RESISTANCE * ((double) digipot_setting / DIGI_POT_POSITIONS));

    /* total up the resistances that comprise Rg */
    Rg = DIGI_POT_SERIES_RESISTOR + digipot_resistance;

    gain = 1.0f + (Rf / Rg);

    return (gain);
}

static uint8_t laser_power_to_percentage(uint8_t power)
{
    float percentage;

    percentage = power;
    percentage /= 127;
    percentage *= 100;

    return ((uint8_t) percentage);
}

static void update_label_value_widget_percentage(laLabelWidget *label_widget, uint8_t percentage)
{
    char percentage_string[10];
    laString la_percent_string;

    sprintf(percentage_string, "%d%%", percentage);

    la_percent_string = laString_CreateFromCharBuffer(percentage_string, &VALUE_FONT);
    laLabelWidget_SetText(label_widget, la_percent_string);
    laString_Destroy(&la_percent_string);
}

static void update_label_value_widget_value(laLabelWidget *label_widget, double value)
{
    char percentage_string[10];
    laString la_percent_string;

    sprintf(percentage_string, "%.2f", value);

    la_percent_string = laString_CreateFromCharBuffer(percentage_string, &VALUE_FONT);
    laLabelWidget_SetText(label_widget, la_percent_string);
    laString_Destroy(&la_percent_string);
}

// App_DeviceSettingsLcdSliderWidget - ValueChangedEvent
void App_DeviceSettingsLcdSliderWidget_ValueChangedEvent(laSliderWidget* sld)
{
    uint8_t lcd_brightness = laSliderWidget_GetSliderValue(sld) + 20U;
//    dprintf_colour("[GREEN]LCD slider value = %d[WHITE]\r\n", lcd_brightness + 20U);
    app_set_lcd_brightness(lcd_brightness);
}

// App_DeviceSettingsCancelButtonWidget - PressedEvent
void App_DeviceSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
//    dputs_colour("[YELLOW]cancel button pressed[WHITE]\r\n");
    app_exit_configure();

    /* cancel any settings that have been changed */
    //laButtonWidget_SetPressed(LaserCheckButtonWidget, LA_FALSE);
    //app_set_lcd_brightness(settings_get_lcd_brightness());
    //app_set_led_brightness(settings_get_led_brightness(), false);
}

// App_DeviceSettingsApplyButtonWidget - PressedEvent
void App_DeviceSettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
    //settings_set_peak_2_threshold_voltage(laSliderWidget_GetSliderValue(DeviceSettingsPeak2AmplitudeSliderWidget) * P2_SCALE_FACTOR);
    //settings_set_laser_power(127U - laSliderWidget_GetSliderValue(DeviceSettingsLaserPowerSliderWidget));    
    
    //settings_set_led_brightness(laSliderWidget_GetSliderValue(DeviceSettingsLEDSliderWidget)  );    
    //settings_set_wait_for_alignment((bool) laButtonWidget_GetPressed(AutoScanButtonWidget));
    
    //laButtonWidget_SetPressed(LaserCheckButtonWidget, LA_FALSE);
    
    
    settings_set_lcd_brightness(laSliderWidget_GetSliderValue(DeviceSettingsLcdSliderWidget) + 20U);
    app_set_lcd_brightness(settings_get_lcd_brightness());
    
    save_settings();

    app_exit_configure();
}

// App_DeviceSettings - ShowEvent
void App_DeviceSettings_ShowEvent(laScreen* scr)
{
    /* set the values for the UI elements */
    laSliderWidget_SetSliderValue(DeviceSettingsLcdSliderWidget, settings_get_lcd_brightness() - 20U );
}

/* *****************************************************************************
 End of File
 */
