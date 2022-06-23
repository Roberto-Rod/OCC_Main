/*******************************************************************************
  SYS PORTS Static Functions for PORTS System Service

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.c

  Summary:
    GPIO function implementations for the GPIO PLIB.

  Description:
    The GPIO PLIB provides a simple interface to manage peripheral
    input-output controller.

*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#include "plib_gpio.h"

//version form 11/2021
/******************************************************************************
  Function:
    GPIO_Initialize ( void )

  Summary:
    Initialize the GPIO library.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_Initialize ( void )
{
    
    
    
    /* PORTA Initialization */
    ODCASET = 0x20; /* Open Drain Enable */
    LATA = 0x22; /* Initial Latch Value */
    TRISACLR = 0x4623; /* Direction Control */
    ANSELACLR = 0x623; /* Digital Mode Enable */

    /* PORTB Initialization */
    LATB = 0x0; /* Initial Latch Value */
//    TRISBCLR = 0xae7f; /* Direction Control */
    TRISBCLR = 0xae63; /* Direction Control */
    ANSELBCLR = 0xffff; /* Digital Mode Enable */
    CNPUBSET = 0x3000; /* Pull-Up Enable */
    /* Change Notice Enable */
    CNCONBSET = _CNCONB_ON_MASK;
    PORTB;
    IEC3SET = _IEC3_CNBIE_MASK;

    /* PORTC Initialization */
    LATC = 0x0; /* Initial Latch Value */
//    TRISCCLR = 0x6000; /* Direction Control */
    TRISCCLR = 0x6008; /* Direction Control - Harmony generated config wrong - DO NOT CHANGE*/
    ANSELCCLR = 0xf01e; /* Digital Mode Enable */

    /* PORTD Initialization */
    LATD = 0x800; /* Initial Latch Value */
    TRISDCLR = 0x4000; /* Direction Control */
    ANSELDCLR = 0xffff; /* Digital Mode Enable */

    /* PORTE Initialization */
    ANSELECLR = 0x1f0; /* Digital Mode Enable */

    /* PORTF Initialization */
    LATF = 0x3100; /* Initial Latch Value */
    // TRISFCLR = 0x3138; /* Direction Control */
    TRISFCLR = 0x3130; /* Direction Control - Harmony generated config wrong DO NOT CHANGE */
    ANSELFCLR = 0x3000; /* Digital Mode Enable */

    /* PORTG Initialization */
    ODCGSET = 0x8180; /* Open Drain Enable */
    LATG = 0x8000; /* Initial Latch Value */
    TRISGCLR = 0x8000; /* Direction Control */
    ANSELGCLR = 0x83c0; /* Digital Mode Enable */


    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;

    /* PPS Input Remapping */
    U3CTSR = 12;
    INT1R = 13;
    U4RXR = 11;
    U2RXR = 2;
    U3RXR = 8;
    U1RXR = 8;

    /* PPS Output Remapping */
    RPD5R = 4;
    RPC4R = 1;
    RPC1R = 1;
    RPG9R = 2;
    RPC3R = 1;
    RPB0R = 2;

    /* Lock back the system after PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 1;

}

/******************************************************************************
  Function:
    GPIO_Initialize ( void )

  Summary:
    Initialize the GPIO library.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_Initialize3 ( void )
{
    /* PORTA Initialization */
    ODCASET = 0x20; /* Open Drain Enable */
    LATA = 0x22; /* Initial Latch Value */
    TRISACLR = 0x4623; /* Direction Control */
    ANSELACLR = 0x623; /* Digital Mode Enable */

    /* PORTB Initialization */
    LATB = 0x0; /* Initial Latch Value */
//    TRISBCLR = 0xae7f; /* Direction Control */
    TRISBCLR = 0xae63; /* Direction Control - Harmony generated config wrong - DO NOT CHANGE */
    ANSELBCLR = 0xffff; /* Digital Mode Enable */
    CNPUBSET = 0x3000; /* Pull-Up Enable */
    /* Change Notice Enable */
    CNCONBSET = _CNCONB_ON_MASK;
    PORTB;
    IEC3SET = _IEC3_CNBIE_MASK;

    /* PORTC Initialization */
    LATC = 0x0; /* Initial Latch Value */
//    TRISCCLR = 0x6000; /* Direction Control */
    TRISCCLR = 0x6008; /* Direction Control - Harmony generated config wrong - DO NOT CHANGE*/
    ANSELCCLR = 0xf01e; /* Digital Mode Enable */

    /* PORTD Initialization */
    LATD = 0x800; /* Initial Latch Value */
    //TRISDCLR = 0x8e00; /* Direction Control */
    TRISDCLR = 0x0e00; // REMOVE setting up the RD15 FOR STI BOARDS
    ANSELDCLR = 0xc000; /* Digital Mode Enable */

    /* PORTE Initialization */
    ANSELECLR = 0x1f0; /* Digital Mode Enable */

    /* PORTF Initialization */
    LATF = 0x3100; /* Initial Latch Value */
    // TRISFCLR = 0x3138; /* Direction Control */
    TRISFCLR = 0x3130; /* Direction Control - Harmony generated config wrong DO NOT CHANGE */
    ANSELFCLR = 0x3000; /* Digital Mode Enable */

    /* PORTG Initialization */
    ODCGSET = 0x8180; /* Open Drain Enable */
    LATG = 0x8000; /* Initial Latch Value */
    TRISGCLR = 0x8000; /* Direction Control */
    ANSELGCLR = 0x83c0; /* Digital Mode Enable */


    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;

    /* PPS Input Remapping */
    U3CTSR = 12;
    INT1R = 13;
    U4RXR = 11;
    U2RXR = 2;
    U3RXR = 8;
    U1RXR = 8;

    /* PPS Output Remapping */
    RPD5R = 4;
    RPC4R = 1;
    RPC1R = 1;
    RPG9R = 2;
    RPC3R = 1;
    RPB0R = 2;

    /* Lock back the system after PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 1;


}

/******************************************************************************
  Function:
    GPIO_Initialize ( void )

  Summary:
    Initialize the GPIO library.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_Initialize2 ( void )
{
    /* PORTA Initialization */
    LATA = 0x22; /* Initial Latch Value */
    TRISACLR = 0x22; /* Direction Control */
    ANSELACLR = 0x622; /* Digital Mode Enable */

    /* PORTB Initialization */
    ANSELBCLR = 0x7020; /* Digital Mode Enable */
    CNPUBSET = 0x7000; /* Pull-Up Enable */

    /* PORTC Initialization */
    ANSELCCLR = 0x10; /* Digital Mode Enable */

    /* PORTD Initialization */

    /* PORTE Initialization */
    ANSELECLR = 0x210; /* Digital Mode Enable */

    /* PORTF Initialization */
    LATF = 0x3000; /* Initial Latch Value */
    TRISFCLR = 0x3000; /* Direction Control */
    ANSELFCLR = 0x3000; /* Digital Mode Enable */

    /* PORTG Initialization */
    LATG = 0x8000; /* Initial Latch Value */
    TRISGCLR = 0x8000; /* Direction Control */
    ANSELGCLR = 0x8040; /* Digital Mode Enable */



    /* PPS Input Remapping */

    /* PPS Output Remapping */


}

// *****************************************************************************
// *****************************************************************************
// Section: GPIO APIs which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    uint32_t GPIO_PortRead ( GPIO_PORT port )

  Summary:
    Read all the I/O lines of the selected port.

  Description:
    This function reads the live data values on all the I/O lines of the
    selected port.  Bit values returned in each position indicate corresponding
    pin levels.
    1 = Pin is high.
    0 = Pin is low.

    This function reads the value regardless of pin configuration, whether it is
    set as as an input, driven by the GPIO Controller, or driven by a peripheral.

  Remarks:
    If the port has less than 32-bits, unimplemented pins will read as
    low (0).
    Implemented pins are Right aligned in the 32-bit return value.
*/
uint32_t GPIO_PortRead(GPIO_PORT port)
{
    return (*(volatile uint32_t *)(&PORTA + (port * 0x40)));
}

// *****************************************************************************
/* Function:
    void GPIO_PortWrite (GPIO_PORT port, uint32_t mask, uint32_t value);

  Summary:
    Write the value on the masked I/O lines of the selected port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value)
{
    *(volatile uint32_t *)(&LATA + (port * 0x40)) = (*(volatile uint32_t *)(&LATA + (port * 0x40)) & (~mask)) | (mask & value);
}

// *****************************************************************************
/* Function:
    uint32_t GPIO_PortLatchRead ( GPIO_PORT port )

  Summary:
    Read the latched value on all the I/O lines of the selected port.

  Remarks:
    See plib_gpio.h for more details.
*/
uint32_t GPIO_PortLatchRead(GPIO_PORT port)
{
    return (*(volatile uint32_t *)(&LATA + (port * 0x40)));
}

// *****************************************************************************
/* Function:
    void GPIO_PortSet ( GPIO_PORT port, uint32_t mask )

  Summary:
    Set the selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortSet(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&LATASET + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortClear ( GPIO_PORT port, uint32_t mask )

  Summary:
    Clear the selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortClear(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&LATACLR + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortToggle ( GPIO_PORT port, uint32_t mask )

  Summary:
    Toggles the selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortToggle(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&LATAINV + (port * 0x40))= mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortInputEnable ( GPIO_PORT port, uint32_t mask )

  Summary:
    Enables selected IO pins of a port as input.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&TRISASET + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortOutputEnable ( GPIO_PORT port, uint32_t mask )

  Summary:
    Enables selected IO pins of a port as output(s).

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&TRISACLR + (port * 0x40)) = mask;
}




/*******************************************************************************
 End of File
*/
