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

/*** Macros for CAMERA_ST pin ***/
#define CAMERA_ST_Set()               (LATCSET = (1<<2))
#define CAMERA_ST_Clear()             (LATCCLR = (1<<2))
#define CAMERA_ST_Toggle()            (LATCINV= (1<<2))
#define CAMERA_ST_Get()               ((PORTC >> 2) & 0x1)
#define CAMERA_ST_OutputEnable()      (TRISCCLR = (1<<2))
#define CAMERA_ST_InputEnable()       (TRISCSET = (1<<2))
#define CAMERA_ST_PIN                  GPIO_PIN_RC2
/*** Macros for TP_INT pin ***/
#define TP_INT_Set()               (LATBSET = (1<<4))
#define TP_INT_Clear()             (LATBCLR = (1<<4))
#define TP_INT_Toggle()            (LATBINV= (1<<4))
#define TP_INT_Get()               ((PORTB >> 4) & 0x1)
#define TP_INT_OutputEnable()      (TRISBCLR = (1<<4))
#define TP_INT_InputEnable()       (TRISBSET = (1<<4))
#define TP_INT_InterruptEnable()   (CNENBSET = (1<<4))
#define TP_INT_InterruptDisable()  (CNENBCLR = (1<<4))
#define TP_INT_PIN                  GPIO_PIN_RB4
/*** Macros for DISPLAY_SDI pin ***/
#define DISPLAY_SDI_Set()               (LATBSET = (1<<2))
#define DISPLAY_SDI_Clear()             (LATBCLR = (1<<2))
#define DISPLAY_SDI_Toggle()            (LATBINV= (1<<2))
#define DISPLAY_SDI_Get()               ((PORTB >> 2) & 0x1)
#define DISPLAY_SDI_OutputEnable()      (TRISBCLR = (1<<2))
#define DISPLAY_SDI_InputEnable()       (TRISBSET = (1<<2))
#define DISPLAY_SDI_PIN                  GPIO_PIN_RB2
/*** Macros for DISPLAY_DC pin ***/
#define DISPLAY_DC_Set()               (LATBSET = (1<<12))
#define DISPLAY_DC_Clear()             (LATBCLR = (1<<12))
#define DISPLAY_DC_Toggle()            (LATBINV= (1<<12))
#define DISPLAY_DC_Get()               ((PORTB >> 12) & 0x1)
#define DISPLAY_DC_OutputEnable()      (TRISBCLR = (1<<12))
#define DISPLAY_DC_InputEnable()       (TRISBSET = (1<<12))
#define DISPLAY_DC_PIN                  GPIO_PIN_RB12
/*** Macros for EIB_IRQ pin ***/
#define EIB_IRQ_Set()               (LATHSET = (1<<14))
#define EIB_IRQ_Clear()             (LATHCLR = (1<<14))
#define EIB_IRQ_Toggle()            (LATHINV= (1<<14))
#define EIB_IRQ_Get()               ((PORTH >> 14) & 0x1)
#define EIB_IRQ_OutputEnable()      (TRISHCLR = (1<<14))
#define EIB_IRQ_InputEnable()       (TRISHSET = (1<<14))
#define EIB_IRQ_InterruptEnable()   (CNENHSET = (1<<14))
#define EIB_IRQ_InterruptDisable()  (CNENHCLR = (1<<14))
#define EIB_IRQ_PIN                  GPIO_PIN_RH14
/*** Macros for IP_VALID pin ***/
#define IP_VALID_Set()               (LATASET = (1<<10))
#define IP_VALID_Clear()             (LATACLR = (1<<10))
#define IP_VALID_Toggle()            (LATAINV= (1<<10))
#define IP_VALID_Get()               ((PORTA >> 10) & 0x1)
#define IP_VALID_OutputEnable()      (TRISACLR = (1<<10))
#define IP_VALID_InputEnable()       (TRISASET = (1<<10))
#define IP_VALID_PIN                  GPIO_PIN_RA10
/*** Macros for DISPLAY_BL pin ***/
#define DISPLAY_BL_Set()               (LATBSET = (1<<10))
#define DISPLAY_BL_Clear()             (LATBCLR = (1<<10))
#define DISPLAY_BL_Toggle()            (LATBINV= (1<<10))
#define DISPLAY_BL_Get()               ((PORTB >> 10) & 0x1)
#define DISPLAY_BL_OutputEnable()      (TRISBCLR = (1<<10))
#define DISPLAY_BL_InputEnable()       (TRISBSET = (1<<10))
#define DISPLAY_BL_PIN                  GPIO_PIN_RB10
/*** Macros for CAMERA_RS pin ***/
#define CAMERA_RS_Set()               (LATBSET = (1<<6))
#define CAMERA_RS_Clear()             (LATBCLR = (1<<6))
#define CAMERA_RS_Toggle()            (LATBINV= (1<<6))
#define CAMERA_RS_Get()               ((PORTB >> 6) & 0x1)
#define CAMERA_RS_OutputEnable()      (TRISBCLR = (1<<6))
#define CAMERA_RS_InputEnable()       (TRISBSET = (1<<6))
#define CAMERA_RS_PIN                  GPIO_PIN_RB6
/*** Macros for DISPLAY_SS pin ***/
#define DISPLAY_SS_Set()               (LATBSET = (1<<5))
#define DISPLAY_SS_Clear()             (LATBCLR = (1<<5))
#define DISPLAY_SS_Toggle()            (LATBINV= (1<<5))
#define DISPLAY_SS_Get()               ((PORTB >> 5) & 0x1)
#define DISPLAY_SS_OutputEnable()      (TRISBCLR = (1<<5))
#define DISPLAY_SS_InputEnable()       (TRISBSET = (1<<5))
#define DISPLAY_SS_PIN                  GPIO_PIN_RB5
/*** Macros for BM71_STBYRST pin ***/
#define BM71_STBYRST_Set()               (LATGSET = (1<<6))
#define BM71_STBYRST_Clear()             (LATGCLR = (1<<6))
#define BM71_STBYRST_Toggle()            (LATGINV= (1<<6))
#define BM71_STBYRST_Get()               ((PORTG >> 6) & 0x1)
#define BM71_STBYRST_OutputEnable()      (TRISGCLR = (1<<6))
#define BM71_STBYRST_InputEnable()       (TRISGSET = (1<<6))
#define BM71_STBYRST_PIN                  GPIO_PIN_RG6
/*** Macros for BM71_RX pin ***/
#define BM71_RX_Set()               (LATESET = (1<<8))
#define BM71_RX_Clear()             (LATECLR = (1<<8))
#define BM71_RX_Toggle()            (LATEINV= (1<<8))
#define BM71_RX_Get()               ((PORTE >> 8) & 0x1)
#define BM71_RX_OutputEnable()      (TRISECLR = (1<<8))
#define BM71_RX_InputEnable()       (TRISESET = (1<<8))
#define BM71_RX_PIN                  GPIO_PIN_RE8   
/*** Macros for CAMERA_PWDN pin ***/
#define CAMERA_PWDN_Set()               (LATBSET = (1<<11))
#define CAMERA_PWDN_Clear()             (LATBCLR = (1<<11))
#define CAMERA_PWDN_Toggle()            (LATBINV= (1<<11))
#define CAMERA_PWDN_Get()               ((PORTB >> 11) & 0x1)
#define CAMERA_PWDN_OutputEnable()      (TRISBCLR = (1<<11))
#define CAMERA_PWDN_InputEnable()       (TRISBSET = (1<<11))
#define CAMERA_PWDN_PIN                  GPIO_PIN_RB11
/*** Macros for DISPLAY_RD pin ***/
#define DISPLAY_RD_Set()               (LATDSET = (1<<14))
#define DISPLAY_RD_Clear()             (LATDCLR = (1<<14))
#define DISPLAY_RD_Toggle()            (LATDINV= (1<<14))
#define DISPLAY_RD_Get()               ((PORTD >> 14) & 0x1)
#define DISPLAY_RD_OutputEnable()      (TRISDCLR = (1<<14))
#define DISPLAY_RD_InputEnable()       (TRISDSET = (1<<14))
#define DISPLAY_RD_PIN                  GPIO_PIN_RD14
/*** Macros for DISPLAY_RS pin ***/
#define DISPLAY_RS_Set()               (LATASET = (1<<1))
#define DISPLAY_RS_Clear()             (LATACLR = (1<<1))
#define DISPLAY_RS_Toggle()            (LATAINV= (1<<1))
#define DISPLAY_RS_Get()               ((PORTA >> 1) & 0x1)
#define DISPLAY_RS_OutputEnable()      (TRISACLR = (1<<1))
#define DISPLAY_RS_InputEnable()       (TRISASET = (1<<1))
#define DISPLAY_RS_PIN                  GPIO_PIN_RA1
/*** Macros for CAMERA_SHDN pin ***/
#define CAMERA_SHDN_Set()               (LATBSET = (1<<13))
#define CAMERA_SHDN_Clear()             (LATBCLR = (1<<13))
#define CAMERA_SHDN_Toggle()            (LATBINV= (1<<13))
#define CAMERA_SHDN_Get()               ((PORTB >> 13) & 0x1)
#define CAMERA_SHDN_OutputEnable()      (TRISBCLR = (1<<13))
#define CAMERA_SHDN_InputEnable()       (TRISBSET = (1<<13))
#define CAMERA_SHDN_PIN                  GPIO_PIN_RB13
/*** Macros for DISPLAY_TE pin ***/
#define DISPLAY_TE_Set()               (LATJSET = (1<<2))
#define DISPLAY_TE_Clear()             (LATJCLR = (1<<2))
#define DISPLAY_TE_Toggle()            (LATJINV= (1<<2))
#define DISPLAY_TE_Get()               ((PORTJ >> 2) & 0x1)
#define DISPLAY_TE_OutputEnable()      (TRISJCLR = (1<<2))
#define DISPLAY_TE_InputEnable()       (TRISJSET = (1<<2))
#define DISPLAY_TE_PIN                  GPIO_PIN_RJ2
/*** Macros for DISPLAY_SCK pin ***/
#define DISPLAY_SCK_Set()               (LATDSET = (1<<15))
#define DISPLAY_SCK_Clear()             (LATDCLR = (1<<15))
#define DISPLAY_SCK_Toggle()            (LATDINV= (1<<15))
#define DISPLAY_SCK_Get()               ((PORTD >> 15) & 0x1)
#define DISPLAY_SCK_OutputEnable()      (TRISDCLR = (1<<15))
#define DISPLAY_SCK_InputEnable()       (TRISDSET = (1<<15))
#define DISPLAY_SCK_PIN                  GPIO_PIN_RD15
/*** Macros for DBG_LEDG pin ***/
#define DBG_LEDG_Set()               (LATHSET = (1<<2))
#define DBG_LEDG_Clear()             (LATHCLR = (1<<2))
#define DBG_LEDG_Toggle()            (LATHINV= (1<<2))
#define DBG_LEDG_Get()               ((PORTH >> 2) & 0x1)
#define DBG_LEDG_OutputEnable()      (TRISHCLR = (1<<2))
#define DBG_LEDG_InputEnable()       (TRISHSET = (1<<2))
#define DBG_LEDG_PIN                  GPIO_PIN_RH2
/*** Macros for DBG_LEDR pin ***/
#define DBG_LEDR_Set()               (LATJSET = (1<<15))
#define DBG_LEDR_Clear()             (LATJCLR = (1<<15))
#define DBG_LEDR_Toggle()            (LATJINV= (1<<15))
#define DBG_LEDR_Get()               ((PORTJ >> 15) & 0x1)
#define DBG_LEDR_OutputEnable()      (TRISJCLR = (1<<15))
#define DBG_LEDR_InputEnable()       (TRISJSET = (1<<15))
#define DBG_LEDR_PIN                  GPIO_PIN_RJ15
/*** Macros for DBG_LEDB pin ***/
#define DBG_LEDB_Set()               (LATHSET = (1<<3))
#define DBG_LEDB_Clear()             (LATHCLR = (1<<3))
#define DBG_LEDB_Toggle()            (LATHINV= (1<<3))
#define DBG_LEDB_Get()               ((PORTH >> 3) & 0x1)
#define DBG_LEDB_OutputEnable()      (TRISHCLR = (1<<3))
#define DBG_LEDB_InputEnable()       (TRISHSET = (1<<3))
#define DBG_LEDB_PIN                  GPIO_PIN_RH3
/*** Macros for TP_RESET pin ***/
#define TP_RESET_Set()               (LATJSET = (1<<1))
#define TP_RESET_Clear()             (LATJCLR = (1<<1))
#define TP_RESET_Toggle()            (LATJINV= (1<<1))
#define TP_RESET_Get()               ((PORTJ >> 1) & 0x1)
#define TP_RESET_OutputEnable()      (TRISJCLR = (1<<1))
#define TP_RESET_InputEnable()       (TRISJSET = (1<<1))
#define TP_RESET_PIN                  GPIO_PIN_RJ1
/*** Macros for BUZZER pin ***/
#define BUZZER_Set()               (LATFSET = (1<<3))
#define BUZZER_Clear()             (LATFCLR = (1<<3))
#define BUZZER_Toggle()            (LATFINV= (1<<3))
#define BUZZER_Get()               ((PORTF >> 3) & 0x1)
#define BUZZER_OutputEnable()      (TRISFCLR = (1<<3))
#define BUZZER_InputEnable()       (TRISFSET = (1<<3))
#define BUZZER_PIN                  GPIO_PIN_RF3
/*** Macros for CLOCK_EN pin ***/
#define CLOCK_EN_Set()               (LATHSET = (1<<8))
#define CLOCK_EN_Clear()             (LATHCLR = (1<<8))
#define CLOCK_EN_Toggle()            (LATHINV= (1<<8))
#define CLOCK_EN_Get()               ((PORTH >> 8) & 0x1)
#define CLOCK_EN_OutputEnable()      (TRISHCLR = (1<<8))
#define CLOCK_EN_InputEnable()       (TRISHSET = (1<<8))
#define CLOCK_EN_PIN                  GPIO_PIN_RH8
/*** Macros for ENV_EN pin ***/
#define ENV_EN_Set()               (LATJSET = (1<<11))
#define ENV_EN_Clear()             (LATJCLR = (1<<11))
#define ENV_EN_Toggle()            (LATJINV= (1<<11))
#define ENV_EN_Get()               ((PORTJ >> 11) & 0x1)
#define ENV_EN_OutputEnable()      (TRISJCLR = (1<<11))
#define ENV_EN_InputEnable()       (TRISJSET = (1<<11))
#define ENV_EN_PIN                  GPIO_PIN_RJ11


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
    GPIO_PORT_H = 7,
    GPIO_PORT_J = 8,
    GPIO_PORT_K = 9,
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
    GPIO_PIN_RD6 = 54,
    GPIO_PIN_RD7 = 55,
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
    GPIO_PIN_RH0 = 112,
    GPIO_PIN_RH1 = 113,
    GPIO_PIN_RH2 = 114,
    GPIO_PIN_RH3 = 115,
    GPIO_PIN_RH4 = 116,
    GPIO_PIN_RH5 = 117,
    GPIO_PIN_RH6 = 118,
    GPIO_PIN_RH7 = 119,
    GPIO_PIN_RH8 = 120,
    GPIO_PIN_RH9 = 121,
    GPIO_PIN_RH10 = 122,
    GPIO_PIN_RH11 = 123,
    GPIO_PIN_RH12 = 124,
    GPIO_PIN_RH13 = 125,
    GPIO_PIN_RH14 = 126,
    GPIO_PIN_RH15 = 127,
    GPIO_PIN_RJ0 = 128,
    GPIO_PIN_RJ1 = 129,
    GPIO_PIN_RJ2 = 130,
    GPIO_PIN_RJ3 = 131,
    GPIO_PIN_RJ4 = 132,
    GPIO_PIN_RJ5 = 133,
    GPIO_PIN_RJ6 = 134,
    GPIO_PIN_RJ7 = 135,
    GPIO_PIN_RJ8 = 136,
    GPIO_PIN_RJ9 = 137,
    GPIO_PIN_RJ10 = 138,
    GPIO_PIN_RJ11 = 139,
    GPIO_PIN_RJ12 = 140,
    GPIO_PIN_RJ13 = 141,
    GPIO_PIN_RJ14 = 142,
    GPIO_PIN_RJ15 = 143,
    GPIO_PIN_RK0 = 144,
    GPIO_PIN_RK1 = 145,
    GPIO_PIN_RK2 = 146,
    GPIO_PIN_RK3 = 147,
    GPIO_PIN_RK4 = 148,
    GPIO_PIN_RK5 = 149,
    GPIO_PIN_RK6 = 150,
    GPIO_PIN_RK7 = 151,

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
