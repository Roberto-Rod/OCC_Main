/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    app.h

  @Summary
    Contains global definitions.

  @Description
    Contains global definitions
 */
/* ************************************************************************** */

#ifndef _APP_H    /* Guard against multiple inclusion */
#define _APP_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "drv_rtc.h"
#include "pe_interface.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
#define DISABLE_LEDS
//#define DEBUG_COMS_STAY_ON
//#define DEBUG_POWER_SW
//#define DEBUG_TEMPERATURE

#define _APP_STATUS PE_STATUS
#define _FLAG       PE_FLAG

typedef struct {
    uint8_t major;
    uint8_t minor;

    uint16_t build;
} _SW_VERSION;

/* ************************************************************************** */
/* Section: Data Types                                                        */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */

_APP_STATUS app_get_status(void);
uint16_t SYS_version(void);
_SW_VERSION SYS_full_version(void);
void app_initialize(uint16_t);
void app_update_battery_charge(uint8_t);
void app_update_date_time(void);
void app_set_flag(_FLAG flg);
void app_clear_flag(_FLAG flg);
bool app_check_flag(_FLAG flg);
void app_reset_temperature_flags(bool and_values);
void app_update_temperature(int16_t val);

void app_get_temperature(int16_t* out, uint8_t length); // length = 1 -> current value, length = 3 -> [current, min, max]


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_H */
