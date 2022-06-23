/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "MIMXRT1170-EVK"
#ifndef DEBUG_CONSOLE_UART_INDEX
#define DEBUG_CONSOLE_UART_INDEX 1
#endif

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_CLK_FREQ 24000000

#if DEBUG_CONSOLE_UART_INDEX == 1
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART1
#define BOARD_DEBUG_UART_INSTANCE 1U
#define BOARD_UART_IRQ            LPUART1_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART1_IRQHandler
#elif DEBUG_CONSOLE_UART_INDEX == 2
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART2
#define BOARD_DEBUG_UART_INSTANCE 2U
#define BOARD_UART_IRQ            LPUART2_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART2_IRQHandler
#elif DEBUG_CONSOLE_UART_INDEX == 12
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART12
#define BOARD_DEBUG_UART_INSTANCE 12U
#define BOARD_UART_IRQ            LPUART12_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART12_IRQHandler
#else
#error "Unsupported UART"
#endif

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE (115200U)
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief The USER_LED used for board */
#define LOGIC_LED_ON  (0U)
#define LOGIC_LED_OFF (1U)
#ifndef BOARD_USER_LED_GPIO
#define BOARD_USER_LED_GPIO GPIO9
#endif
#ifndef BOARD_USER_LED_GPIO_PIN
#define BOARD_USER_LED_GPIO_PIN (3U)
#endif

#define USER_LED_INIT(output)                                            \
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, output); \
    BOARD_USER_LED_GPIO->GDIR |= (1U << BOARD_USER_LED_GPIO_PIN) /*!< Enable target USER_LED */
#define USER_LED_OFF() \
    GPIO_PortClear(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN)                 /*!< Turn off target USER_LED */
#define USER_LED_ON() GPIO_PortSet(BOARD_USER_LED_GPIO, 1U << BOARD_USER_LED_GPIO_PIN) /*!<Turn on target USER_LED*/
#define USER_LED_TOGGLE()                                       \
    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, \
                  0x1 ^ GPIO_PinRead(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN)) /*!< Toggle target USER_LED */

/*! @brief Define the port interrupt number for the board switches */
#ifndef BOARD_USER_BUTTON_GPIO
#define BOARD_USER_BUTTON_GPIO GPIO13
#endif
#ifndef BOARD_USER_BUTTON_GPIO_PIN
#define BOARD_USER_BUTTON_GPIO_PIN (0U)
#endif
#define BOARD_USER_BUTTON_IRQ         GPIO13_Combined_0_31_IRQn
#define BOARD_USER_BUTTON_IRQ_HANDLER GPIO13_Combined_0_31_IRQHandler
#define BOARD_USER_BUTTON_NAME        "SW7"

/*! @brief The board flash size */
#define BOARD_FLASH_SIZE (0x1000000U)

/* SKIP_SEMC_INIT can also be defined independently */
#ifdef USE_SDRAM
#define SKIP_SEMC_INIT
#endif

/*! @brief The MIPI panel pins. */
#define BOARD_MIPI_PANEL_RST_GPIO   GPIO9
#define BOARD_MIPI_PANEL_RST_PIN    1
#define BOARD_MIPI_PANEL_POWER_GPIO GPIO11
#define BOARD_MIPI_PANEL_POWER_PIN  16
/* Back light pin. */
#define BOARD_MIPI_PANEL_BL_GPIO GPIO9
#define BOARD_MIPI_PANEL_BL_PIN  29

/* Touch panel. */
#define BOARD_MIPI_PANEL_TOUCH_RST_GPIO          GPIO9
#define BOARD_MIPI_PANEL_TOUCH_RST_PIN           0
#define BOARD_MIPI_PANEL_TOUCH_INT_GPIO          GPIO8
#define BOARD_MIPI_PANEL_TOUCH_INT_PIN           31

/*! @brief The camera pins. */
#define BOARD_CAMERA_PWDN_GPIO GPIO9
#define BOARD_CAMERA_PWDN_PIN  25
#define BOARD_CAMERA_RST_GPIO  GPIO11
#define BOARD_CAMERA_RST_PIN   15

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
uint32_t BOARD_DebugConsoleSrcFreq(void);

void BOARD_InitDebugConsole(void);

void BOARD_ConfigMPU(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
