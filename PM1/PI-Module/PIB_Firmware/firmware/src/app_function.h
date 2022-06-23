/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occutity Limited

  @File Name
    app_function.h

  @Summary
    Miscellaneous app functions.

  @Description
    App functions.
 */
/* ************************************************************************** */

#ifndef _APP_FUNCTION_H    /* Guard against multiple inclusion */
#define _APP_FUNCTION_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "time.h"

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

void app_set_led_brightness(uint8_t pwm, bool state);
void app_set_lcd_brightness(uint8_t percent);
void app_set_time(RTCCFORM * time);
RTCCFORM * app_get_time(void);
void app_send_laser_check_command(void);
void app_send_zero_offset_command(void);
void app_send_pdab_settings_command(void);

void app_time_callback(RTCCFORM * time);
void app_touch_callback(uint16_t * context);
void app_power_up_callback( uint16_t * context);
void app_power_down_callback( uint16_t * context);
void app_power_off_callback( uint16_t * context);

 /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_FUNCTION_H */

/* *****************************************************************************
 End of File
 */
