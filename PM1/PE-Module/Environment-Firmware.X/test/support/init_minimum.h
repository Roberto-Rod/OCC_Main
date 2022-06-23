#ifndef INIT_MINIMUM_H
#define INIT_MINIMUM_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#define TEST_DISABLE_GPIO
//#define TEST_DISABLE_CLOCK
#define TEST_DISABLE_INTERRUPT
#define TEST_DISABLE_UART2
#define TEST_DISABLE_UART1
#define TEST_DISABLE_ADC1
#define TEST_DISABLE_TMR1
#define TEST_DISABLE_RTCC
//#define TEST_DISABLE_HELPER_UART_INIT

#include "unity_helper.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#include "unity_helper.c"

#include "clock.c"

#include "system.c"

#endif // INIT_MINIMUM_H
