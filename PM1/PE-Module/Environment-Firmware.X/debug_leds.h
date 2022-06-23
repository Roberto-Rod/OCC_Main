/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    debug_leds.h

  @Summary
    Drive the debugging LEDs.

  @Description
    Debug LED driver.
 */
/* ************************************************************************** */

#ifndef _DEBUG_LEDS_H    /* Guard against multiple inclusion */
#define _DEBUG_LEDS_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Macros                                                    */
/* ************************************************************************** */

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Data Types                                                        */
/* ************************************************************************** */

    
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */

void initialise_leds(void);
void red_led(uint8_t led_on);
void red_led_toggle(void);
void green_led(uint8_t led_on);
void green_led_toggle(void);
    
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_LEDS_H */
