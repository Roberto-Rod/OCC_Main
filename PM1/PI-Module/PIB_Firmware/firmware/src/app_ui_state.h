/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    app_ui_state.h

  @Summary
    Functions for updating the state of the main User Interface.

  @Description
    Update state of battery, USB icon, LASER icon, etc.
 */
/* ************************************************************************** */

#ifndef _APP_UI_STATE_H    /* Guard against multiple inclusion */
#define _APP_UI_STATE_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "definitions.h"
#include "npda.h"
#include "maths_library.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */



// *****************************************************************************
// Section: Data Types
// *****************************************************************************



// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
    
bool app_logo_animation(bool reset);
void app_set_battery_state(uint8_t battery_charge_percentage, bool battery_charging, bool low_battery);
void app_set_usb_state(bool state);
void app_set_scanning_state(bool state);
void app_set_saturated_state(bool state);
void app_set_laser_state(bool laser_on, bool laser_power_on );
void app_set_scan_state(bool state);

void App_ScanButtonWidget_PressedEvent(laButtonWidget* btn);
void app_scan_trigger(bool state);

void app_update_status_bar(void);
void app_update_error_state(void);
void app_update_frame( void );
void app_update_alignment_ui_state(laScheme* scheme1, laScheme* scheme2, bool visible);
void app_update_alignment_ui(void);
void app_update_measurement_value( _NPDA_MEASUREMNT* result, uint16_t index, uint8_t alpha, bool visible );
void app_update_gui_measurements( void );

void app_show_main_screen_buttons(laBool visible);
void app_enable_main_screen_buttons(laBool enabled);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_UI_STATE_H */

/* *****************************************************************************
 End of File
 */
