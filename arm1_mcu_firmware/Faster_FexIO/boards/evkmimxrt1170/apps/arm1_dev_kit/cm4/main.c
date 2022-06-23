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

#define LED_INIT()                                                      \
    USER_LED_INIT(0);                                                   \
    USER_CLK_INIT(0);
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

static void configure_systick(void);

/**
 * @brief
 *   System tick interrupt handler
 */
void SysTick_Handler(void)
{
}

/**
 * @brief
 *   Configure the system tick at 1s for one interrupt
 */
static void configure_systick(void)
{
    uint32_t coreclk = CLOCK_GetFreq(kCLOCK_CoreSysClk);

    SysTick_Config(coreclk / 1000);
}

/**
 * @brief
 *   Code entry / main function
 * @return
 *   Never returns
 */
int main(void)
{
    volatile uint32_t t1, t2;
    volatile uint32_t time;
        
    uint32_t startup_data = 0;

    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

    /* Init board hardware.*/
    BOARD_ConfigMPU();
    BOARD_BootClockRUN();
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

    configure_systick();
    
    /* Configure LED */
    LED_INIT();

    /* Clock setting for BUS clock */
    CLOCK_SetRootClockMux(kCLOCK_Root_Bus, 4);
    CLOCK_SetRootClockDiv(kCLOCK_Root_Bus, 1);
        
    for (;;)
    {
        USER_CLK_ON();
      
        t1 = SysTick->VAL;
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        USER_LED_ON();
        USER_LED_OFF();
        t2 = SysTick->VAL;
        
        USER_CLK_OFF();

        time = 
            (((uint64_t)(t1 - t2) * 1000000000u) / 
            CLOCK_GetFreq(kCLOCK_CoreSysClk));
    }
}
