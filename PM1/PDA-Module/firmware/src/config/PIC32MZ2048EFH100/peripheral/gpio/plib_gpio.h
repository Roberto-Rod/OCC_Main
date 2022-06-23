/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************

/*** Macros for LED1 pin ***/
#define LED1_Set()               (LATGSET = (1<<15))
#define LED1_Clear()             (LATGCLR = (1<<15))
#define LED1_Toggle()            (LATGINV= (1<<15))
#define LED1_Get()               ((PORTG >> 15) & 0x1)
#define LED1_OutputEnable()      (TRISGCLR = (1<<15))
#define LED1_InputEnable()       (TRISGSET = (1<<15))
#define LED1_PIN                  GPIO_PIN_RG15
/*** Macros for LED2 pin ***/
#define LED2_Set()               (LATASET = (1<<5))
#define LED2_Clear()             (LATACLR = (1<<5))
#define LED2_Toggle()            (LATAINV= (1<<5))
#define LED2_Get()               ((PORTA >> 5) & 0x1)
#define LED2_OutputEnable()      (TRISACLR = (1<<5))
#define LED2_InputEnable()       (TRISASET = (1<<5))
#define LED2_PIN                  GPIO_PIN_RA5
/*** Macros for IP_VALID pin ***/
#define IP_VALID_Set()               (LATGSET = (1<<6))
#define IP_VALID_Clear()             (LATGCLR = (1<<6))
#define IP_VALID_Toggle()            (LATGINV= (1<<6))
#define IP_VALID_Get()               ((PORTG >> 6) & 0x1)
#define IP_VALID_OutputEnable()      (TRISGCLR = (1<<6))
#define IP_VALID_InputEnable()       (TRISGSET = (1<<6))
#define IP_VALID_PIN                  GPIO_PIN_RG6
/*** Macros for LDA0 pin ***/
#define LDA0_Set()               (LATASET = (1<<0))
#define LDA0_Clear()             (LATACLR = (1<<0))
#define LDA0_Toggle()            (LATAINV= (1<<0))
#define LDA0_Get()               ((PORTA >> 0) & 0x1)
#define LDA0_OutputEnable()      (TRISACLR = (1<<0))
#define LDA0_InputEnable()       (TRISASET = (1<<0))
#define LDA0_PIN                  GPIO_PIN_RA0
/*** Macros for LDA2 pin ***/
#define LDA2_Set()               (LATBSET = (1<<1))
#define LDA2_Clear()             (LATBCLR = (1<<1))
#define LDA2_Toggle()            (LATBINV= (1<<1))
#define LDA2_Get()               ((PORTB >> 1) & 0x1)
#define LDA2_OutputEnable()      (TRISBCLR = (1<<1))
#define LDA2_InputEnable()       (TRISBSET = (1<<1))
#define LDA2_PIN                  GPIO_PIN_RB1
/*** Macros for LDA1 pin ***/
#define LDA1_Set()               (LATASET = (1<<10))
#define LDA1_Clear()             (LATACLR = (1<<10))
#define LDA1_Toggle()            (LATAINV= (1<<10))
#define LDA1_Get()               ((PORTA >> 10) & 0x1)
#define LDA1_OutputEnable()      (TRISACLR = (1<<10))
#define LDA1_InputEnable()       (TRISASET = (1<<10))
#define LDA1_PIN                  GPIO_PIN_RA10
/*** Macros for LDA3 pin ***/
#define LDA3_Set()               (LATBSET = (1<<11))
#define LDA3_Clear()             (LATBCLR = (1<<11))
#define LDA3_Toggle()            (LATBINV= (1<<11))
#define LDA3_Get()               ((PORTB >> 11) & 0x1)
#define LDA3_OutputEnable()      (TRISBCLR = (1<<11))
#define LDA3_InputEnable()       (TRISBSET = (1<<11))
#define LDA3_PIN                  GPIO_PIN_RB11
/*** Macros for DBG_LEDR pin ***/
#define DBG_LEDR_Set()               (LATASET = (1<<1))
#define DBG_LEDR_Clear()             (LATACLR = (1<<1))
#define DBG_LEDR_Toggle()            (LATAINV= (1<<1))
#define DBG_LEDR_Get()               ((PORTA >> 1) & 0x1)
#define DBG_LEDR_OutputEnable()      (TRISACLR = (1<<1))
#define DBG_LEDR_InputEnable()       (TRISASET = (1<<1))
#define DBG_LEDR_PIN                  GPIO_PIN_RA1
/*** Macros for DBG_LEDG pin ***/
#define DBG_LEDG_Set()               (LATFSET = (1<<13))
#define DBG_LEDG_Clear()             (LATFCLR = (1<<13))
#define DBG_LEDG_Toggle()            (LATFINV= (1<<13))
#define DBG_LEDG_Get()               ((PORTF >> 13) & 0x1)
#define DBG_LEDG_OutputEnable()      (TRISFCLR = (1<<13))
#define DBG_LEDG_InputEnable()       (TRISFSET = (1<<13))
#define DBG_LEDG_PIN                  GPIO_PIN_RF13
/*** Macros for DBG_LEDB pin ***/
#define DBG_LEDB_Set()               (LATFSET = (1<<12))
#define DBG_LEDB_Clear()             (LATFCLR = (1<<12))
#define DBG_LEDB_Toggle()            (LATFINV= (1<<12))
#define DBG_LEDB_Get()               ((PORTF >> 12) & 0x1)
#define DBG_LEDB_OutputEnable()      (TRISFCLR = (1<<12))
#define DBG_LEDB_InputEnable()       (TRISFSET = (1<<12))
#define DBG_LEDB_PIN                  GPIO_PIN_RF12
/*** Macros for LSC_BUSY pin ***/
#define LSC_BUSY_Set()               (LATBSET = (1<<12))
#define LSC_BUSY_Clear()             (LATBCLR = (1<<12))
#define LSC_BUSY_Toggle()            (LATBINV= (1<<12))
#define LSC_BUSY_Get()               ((PORTB >> 12) & 0x1)
#define LSC_BUSY_OutputEnable()      (TRISBCLR = (1<<12))
#define LSC_BUSY_InputEnable()       (TRISBSET = (1<<12))
#define LSC_BUSY_InterruptEnable()   (CNENBSET = (1<<12))
#define LSC_BUSY_InterruptDisable()  (CNENBCLR = (1<<12))
#define LSC_BUSY_PIN                  GPIO_PIN_RB12
/*** Macros for DAR_EFH1 pin ***/
#define DAR_EFH1_Set()               (LATBSET = (1<<13))
#define DAR_EFH1_Clear()             (LATBCLR = (1<<13))
#define DAR_EFH1_Toggle()            (LATBINV= (1<<13))
#define DAR_EFH1_Get()               ((PORTB >> 13) & 0x1)
#define DAR_EFH1_OutputEnable()      (TRISBCLR = (1<<13))
#define DAR_EFH1_InputEnable()       (TRISBSET = (1<<13))
#define DAR_EFH1_PIN                  GPIO_PIN_RB13
/*** Macros for MUX0 pin ***/
#define MUX0_Set()               (LATBSET = (1<<14))
#define MUX0_Clear()             (LATBCLR = (1<<14))
#define MUX0_Toggle()            (LATBINV= (1<<14))
#define MUX0_Get()               ((PORTB >> 14) & 0x1)
#define MUX0_OutputEnable()      (TRISBCLR = (1<<14))
#define MUX0_InputEnable()       (TRISBSET = (1<<14))
#define MUX0_PIN                  GPIO_PIN_RB14
/*** Macros for MUX1 pin ***/
#define MUX1_Set()               (LATBSET = (1<<15))
#define MUX1_Clear()             (LATBCLR = (1<<15))
#define MUX1_Toggle()            (LATBINV= (1<<15))
#define MUX1_Get()               ((PORTB >> 15) & 0x1)
#define MUX1_OutputEnable()      (TRISBCLR = (1<<15))
#define MUX1_InputEnable()       (TRISBSET = (1<<15))
#define MUX1_PIN                  GPIO_PIN_RB15
/*** Macros for LSC_DIR pin ***/
#define LSC_DIR_Set()               (LATDSET = (1<<14))
#define LSC_DIR_Clear()             (LATDCLR = (1<<14))
#define LSC_DIR_Toggle()            (LATDINV= (1<<14))
#define LSC_DIR_Get()               ((PORTD >> 14) & 0x1)
#define LSC_DIR_OutputEnable()      (TRISDCLR = (1<<14))
#define LSC_DIR_InputEnable()       (TRISDSET = (1<<14))
#define LSC_DIR_PIN                  GPIO_PIN_RD14
/*** Macros for ADC_EN pin ***/
#define ADC_EN_Set()               (LATFSET = (1<<8))
#define ADC_EN_Clear()             (LATFCLR = (1<<8))
#define ADC_EN_Toggle()            (LATFINV= (1<<8))
#define ADC_EN_Get()               ((PORTF >> 8) & 0x1)
#define ADC_EN_OutputEnable()      (TRISFCLR = (1<<8))
#define ADC_EN_InputEnable()       (TRISFSET = (1<<8))
#define ADC_EN_PIN                  GPIO_PIN_RF8
/*** Macros for LREADY pin ***/
#define LREADY_Set()               (LATASET = (1<<4))
#define LREADY_Clear()             (LATACLR = (1<<4))
#define LREADY_Toggle()            (LATAINV= (1<<4))
#define LREADY_Get()               ((PORTA >> 4) & 0x1)
#define LREADY_OutputEnable()      (TRISACLR = (1<<4))
#define LREADY_InputEnable()       (TRISASET = (1<<4))
#define LREADY_PIN                  GPIO_PIN_RA4
/*** Macros for LTSON pin ***/
#define LTSON_Set()               (LATFSET = (1<<4))
#define LTSON_Clear()             (LATFCLR = (1<<4))
#define LTSON_Toggle()            (LATFINV= (1<<4))
#define LTSON_Get()               ((PORTF >> 4) & 0x1)
#define LTSON_OutputEnable()      (TRISFCLR = (1<<4))
#define LTSON_InputEnable()       (TRISFSET = (1<<4))
#define LTSON_PIN                  GPIO_PIN_RF4
/*** Macros for LON1 pin ***/
#define LON1_Set()               (LATFSET = (1<<5))
#define LON1_Clear()             (LATFCLR = (1<<5))
#define LON1_Toggle()            (LATFINV= (1<<5))
#define LON1_Get()               ((PORTF >> 5) & 0x1)
#define LON1_OutputEnable()      (TRISFCLR = (1<<5))
#define LON1_InputEnable()       (TRISFSET = (1<<5))
#define LON1_PIN                  GPIO_PIN_RF5
/*** Macros for LPON1 pin ***/
#define LPON1_Set()               (LATASET = (1<<15))
#define LPON1_Clear()             (LATACLR = (1<<15))
#define LPON1_Toggle()            (LATAINV= (1<<15))
#define LPON1_Get()               ((PORTA >> 15) & 0x1)
#define LPON1_OutputEnable()      (TRISACLR = (1<<15))
#define LPON1_InputEnable()       (TRISASET = (1<<15))
#define LPON1_PIN                  GPIO_PIN_RA15
/*** Macros for ADC_DITHER pin ***/
#define ADC_DITHER_Set()               (LATDSET = (1<<9))
#define ADC_DITHER_Clear()             (LATDCLR = (1<<9))
#define ADC_DITHER_Toggle()            (LATDINV= (1<<9))
#define ADC_DITHER_Get()               ((PORTD >> 9) & 0x1)
#define ADC_DITHER_OutputEnable()      (TRISDCLR = (1<<9))
#define ADC_DITHER_InputEnable()       (TRISDSET = (1<<9))
#define ADC_DITHER_PIN                  GPIO_PIN_RD9
/*** Macros for ADC_PGA pin ***/
#define ADC_PGA_Set()               (LATDSET = (1<<10))
#define ADC_PGA_Clear()             (LATDCLR = (1<<10))
#define ADC_PGA_Toggle()            (LATDINV= (1<<10))
#define ADC_PGA_Get()               ((PORTD >> 10) & 0x1)
#define ADC_PGA_OutputEnable()      (TRISDCLR = (1<<10))
#define ADC_PGA_InputEnable()       (TRISDSET = (1<<10))
#define ADC_PGA_PIN                  GPIO_PIN_RD10
/*** Macros for ADC_SHDN pin ***/
#define ADC_SHDN_Set()               (LATDSET = (1<<11))
#define ADC_SHDN_Clear()             (LATDCLR = (1<<11))
#define ADC_SHDN_Toggle()            (LATDINV= (1<<11))
#define ADC_SHDN_Get()               ((PORTD >> 11) & 0x1)
#define ADC_SHDN_OutputEnable()      (TRISDCLR = (1<<11))
#define ADC_SHDN_InputEnable()       (TRISDSET = (1<<11))
#define ADC_SHDN_PIN                  GPIO_PIN_RD11
/*** Macros for AMP_EN pin ***/
#define AMP_EN_Set()               (LATCSET = (1<<14))
#define AMP_EN_Clear()             (LATCCLR = (1<<14))
#define AMP_EN_Toggle()            (LATCINV= (1<<14))
#define AMP_EN_Get()               ((PORTC >> 14) & 0x1)
#define AMP_EN_OutputEnable()      (TRISCCLR = (1<<14))
#define AMP_EN_InputEnable()       (TRISCSET = (1<<14))
#define AMP_EN_PIN                  GPIO_PIN_RC14


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA2 = 2,
    GPIO_PIN_RA3 = 3,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA5 = 5,
    GPIO_PIN_RA6 = 6,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA9 = 9,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC3 = 35,
    GPIO_PIN_RC4 = 36,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC14 = 46,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD0 = 48,
    GPIO_PIN_RD1 = 49,
    GPIO_PIN_RD2 = 50,
    GPIO_PIN_RD3 = 51,
    GPIO_PIN_RD4 = 52,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD9 = 57,
    GPIO_PIN_RD10 = 58,
    GPIO_PIN_RD11 = 59,
    GPIO_PIN_RD12 = 60,
    GPIO_PIN_RD13 = 61,
    GPIO_PIN_RD14 = 62,
    GPIO_PIN_RD15 = 63,
    GPIO_PIN_RE0 = 64,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE2 = 66,
    GPIO_PIN_RE3 = 67,
    GPIO_PIN_RE4 = 68,
    GPIO_PIN_RE5 = 69,
    GPIO_PIN_RE6 = 70,
    GPIO_PIN_RE7 = 71,
    GPIO_PIN_RE8 = 72,
    GPIO_PIN_RE9 = 73,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RF2 = 82,
    GPIO_PIN_RF3 = 83,
    GPIO_PIN_RF4 = 84,
    GPIO_PIN_RF5 = 85,
    GPIO_PIN_RF8 = 88,
    GPIO_PIN_RF12 = 92,
    GPIO_PIN_RF13 = 93,
    GPIO_PIN_RG0 = 96,
    GPIO_PIN_RG1 = 97,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,
    GPIO_PIN_RG12 = 108,
    GPIO_PIN_RG13 = 109,
    GPIO_PIN_RG14 = 110,
    GPIO_PIN_RG15 = 111,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;

typedef  void (*GPIO_PIN_CALLBACK) ( GPIO_PIN pin, uintptr_t context);

void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortInterruptEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortInterruptDisable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: Local Data types and Prototypes
// *****************************************************************************
// *****************************************************************************

typedef struct {

    /* target pin */
    GPIO_PIN                 pin;

    /* Callback for event on target pin*/
    GPIO_PIN_CALLBACK        callback;

    /* Callback Context */
    uintptr_t               context;

} GPIO_PIN_CALLBACK_OBJ;

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite(pin>>4, (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead(pin>>4) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInterruptEnable(GPIO_PIN pin)
{
    GPIO_PortInterruptEnable(pin>>4, 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInterruptDisable(GPIO_PIN pin)
{
    GPIO_PortInterruptDisable(pin>>4, 0x1 << (pin & 0xF));
}

bool GPIO_PinInterruptCallbackRegister(
    GPIO_PIN pin,
    const   GPIO_PIN_CALLBACK callBack,
    uintptr_t context
);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
