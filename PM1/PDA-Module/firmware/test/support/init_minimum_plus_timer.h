#ifndef INIT_MINIMUM_PLUS_TIMER_H
#define INIT_MINIMUM_PLUS_TIMER_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

//#define TEST_DISABLE_CLK
//#define TEST_DISABLE_PRE
//#define TEST_DISABLE_GPIO
#define TEST_DISABLE_DMAC
#define TEST_DISABLE_CVR
#define TEST_DISABLE_CMP
#define TEST_DISABLE_CORETIMER
#define TEST_DISABLE_ADCHS
#define TEST_DISABLE_TMR1
//#define TEST_DISABLE_TMR2
#define TEST_DISABLE_TMR3
#define TEST_DISABLE_TMR4
#define TEST_DISABLE_I2C4
#define TEST_DISABLE_UART2
#define TEST_DISABLE_SQI
#define TEST_DISABLE_PMP
#define TEST_DISABLE_USB
#define TEST_DISABLE_PDAB
#define TEST_DISABLE_EVIC
#define TEST_DISABLE_DEBUG
//#define TEST_DISABLE_HELPER_UART_INIT
//#define TEST_DISABLE_HELPER_TMR2_INIT
#define TEST_DISABLE_INTER_PIC_COMMS
#define TEST_DISABLE_PIC_COMMS
#define TEST_DISABLE_DSPIC_PIC_COMMS

#include "unity_helper.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#include "unity_helper.c"

#include "peripheral/clk/plib_clk.c"
#include "peripheral/tmr/plib_tmr2.c"
#include "peripheral/gpio/plib_gpio.c"
#include "peripheral/coretimer/plib_coretimer.c"

#include "initialization.c"

#endif // INIT_MINIMUM_PLUS_TIMER_H
