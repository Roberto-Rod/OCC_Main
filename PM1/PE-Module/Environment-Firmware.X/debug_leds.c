/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    debug_leds.c

  @Summary
    Drive the debugging LEDs.

  @Description
    Drive the debugging LEDs.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "mcc_generated_files/pin_manager.h"

#include "debug_leds.h"
#include "board.h"

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

// Main board, development board B
// RB12 Red
// RB11 Green

// Development board A
// RB1  Red
// RB0  Green

#ifdef DEV_BOARD_A
#define RED_LED_TRIS        _TRISB1
#define GREEN_LED_TRIS      _TRISB0

#define RED_LED_LAT         _LATB1
#define GREEN_LED_LAT       _LATB0
#else
#define RED_LED_TRIS        _TRISB12
#define GREEN_LED_TRIS      _TRISB11

#define RED_LED_LAT         _LATB12
#define GREEN_LED_LAT       _LATB11
#endif

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */



/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */



/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */
/* Function: initialise_leds                                                  */
/* Set the RB0 and RB1 GPIO ports to output to allow the LEDs to be used      */
/* ************************************************************************** */
void initialise_leds(void)
{
    RED_LED_TRIS = 0;
    GREEN_LED_TRIS = 0;
}
/* End of function initialise_leds                                            */

/* ************************************************************************** */
/* Function: red_led                                                          */
/* Turn the red LED on or off                                                 */
/* ************************************************************************** */
void red_led(uint8_t led_on)
{
    RED_LED_LAT = (led_on == 0) ? 1 : 0;
}
/* End of function red_led                                                    */

/* ************************************************************************** */
/* Function: red_led_toggle                                                   */
/* Toggle the state of the red LED                                            */
/* ************************************************************************** */
void red_led_toggle(void)
{
    RED_LED_LAT ^= 1;
}
/* End of function red_led_toggle                                             */

/* ************************************************************************** */
/* Function: red_led                                                          */
/* Turn the green LED on or off                                               */
/* ************************************************************************** */
void green_led(uint8_t led_on)
{
    GREEN_LED_LAT = (led_on == 0) ? 1 : 0;
}
/* End of function green_led                                                  */

/* ************************************************************************** */
/* Function: green_led_toggle                                                 */
/* Toggle the state of the green LED                                          */
/* ************************************************************************** */
void green_led_toggle(void)
{
    GREEN_LED_LAT ^= 1;
}
/* End of function green_led_toggle                                           */


/* *****************************************************************************
 End of File
 */
