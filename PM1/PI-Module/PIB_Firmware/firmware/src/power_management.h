/* ************************************************************************** */
/** Descriptive File Name
  
  @Company
    Occuity Limited

  @File Name
    power_management_task.c

  @Summary
    Power management.

  @Description
    Manages power.
 */
/* ************************************************************************** */

#ifndef _POWER_MANAGEMT_TASK_H    /* Guard against multiple inclusion */
#define _POWER_MANAGEMT_TASK_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "definitions.h"
#include "app.h"

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

typedef enum
{
    POWER_MANAGEMENT_STATE_INIT,
    POWER_MANAGEMENT_STATE_RUNNING,
    POWER_MANAGEMENT_STATE_POWERED_DOWN,
    POWER_MANAGEMENT_STATE_SUSPENDED,
} POWER_MANAGEMENT_STATE;

typedef enum
{
    SLEEP_WAKE_CAUSE_NONE,
    SLEEP_WAKE_CAUSE_SLEEPING,
    SLEEP_WAKE_CAUSE_TRIGGER,
    SLEEP_WAKE_CAUSE_TOUCH
} SLEEP_WAKE_CAUSE;

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void power_up_callback_set(void (*app_power_up_callback)(uint16_t * context));
void power_down_callback_set(void (*app_power_down_callback)(uint16_t * context));
void power_off_callback_set(void (*app_power_off_callback)(uint16_t * context));

void power_management_task(void);
void power_management_activity_trigger(void);
void power_management_suspend(bool state);
POWER_MANAGEMENT_STATE get_power_state(void);
uint32_t get_millisecond_timer_value(void);
bool trigger_woke_us_from_sleep(void);
void reset_sleep_counter(void);

void app_send_power_down_request(void);

bool check_if_pwr_coms_quiet_window(void);
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* __POWER_MANAGEMT_TASK_H */
