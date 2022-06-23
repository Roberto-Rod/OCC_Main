/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_touch_cst130.h

  @Summary
    Driver for the CST130 capacitive touch driver.

  @Description
    Driver for the CST130 capacitive touch driver.
 */
/* ************************************************************************** */

#ifndef _DRV_TOUCH_CST130_H    /* Guard against multiple inclusion */
#define _DRV_TOUCH_CST130_H

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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


void drv_cst130_touch_controller_task(void);
void drv_cst130_touch_callback_set(void (*app_touch_callback)(uint16_t * context));
bool get_touch_in_progress(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_TOUCH_CST130_H */
