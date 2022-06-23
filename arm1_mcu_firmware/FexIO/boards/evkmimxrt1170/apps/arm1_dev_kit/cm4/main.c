/*****************************************************************************/
/**
 * @file 
 *   main.c
 * @brief 
 *   Top-level code entry and initialisation
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#if (1 == MULTICORE_APP)
#include "core.h"
#endif

#include "fsl_gpio.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define LED_INIT() USER_LED_INIT(0);
#define LED_TOGGLE()                                                     \
    if (gb_pinSet)                                                        \
    {                                                                    \
        USER_LED_OFF();                                                  \
        gb_pinSet = false;                                                \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        USER_LED_ON();                                                   \
        gb_pinSet = true;                                                 \
    }

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static volatile bool gb_pinSet = false;

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/**
 * @brief
 *   Code entry / main function
 * @return
 *   Never returns
 */
int main(void)
{
    uint32_t startup_data = 0;

    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

    /* Init board hardware.*/
    BOARD_ConfigMPU();
    BOARD_InitPins();

#if (1 == MULTICORE_APP)
    status_t core_status = CORE_initialise();
    if (kStatus_Success == core_status)
    {
        startup_data = CORE_get_startup_data();
    }
#endif

    /* Make a noticable delay after the reset */
    /* Use startup parameter from the master core... */
    for (uint32_t count = 0; count < startup_data; count++)
    {
        SDK_DelayAtLeastUs(1000000u, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }

#if (1 == MULTICORE_APP)
    if (kStatus_Success == core_status)
    {
        core_status = CORE_trigger_event(CORE_EVENT_REMOTE_READY);
    }
#endif
    
    /* Configure LED */
    LED_INIT();

    for (;;)
    {
        SDK_DelayAtLeastUs(500000u, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        LED_TOGGLE();
    }
}
