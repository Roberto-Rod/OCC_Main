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
    LATA = 0x841e; /* Initial Latch Value */
    TRISACLR = 0x86ff; /* Direction Control */
    ANSELACLR = 0x622; /* Digital Mode Enable */
    CNPUASET = 0xc; /* Pull-Up Enable */

    /* PORTB Initialization */
    ODCBSET = 0x840; /* Open Drain Enable */
    LATB = 0x2424; /* Initial Latch Value */
    TRISBCLR = 0x796c; /* Direction Control */
    ANSELBCLR = 0xffbf; /* Digital Mode Enable */
    CNPUBSET = 0x7000; /* Pull-Up Enable */
    /* Change Notice Enable */
    CNCONBSET = _CNCONB_ON_MASK;
    PORTB;
    IEC3SET = _IEC3_CNBIE_MASK;

    /* PORTC Initialization */
    ODCCSET = 0x4; /* Open Drain Enable */
    LATC = 0x0; /* Initial Latch Value */
    TRISCCLR = 0x4004; /* Direction Control */
    ANSELCCLR = 0xf01e; /* Digital Mode Enable */

    /* PORTD Initialization */
    LATD = 0x4000; /* Initial Latch Value */
    TRISDCLR = 0xcc52; /* Direction Control */
    ANSELDCLR = 0xc000; /* Digital Mode Enable */
    /* Change Notice Enable */
    CNCONDSET = _CNCOND_ON_MASK;
    PORTD;
    IEC3SET = _IEC3_CNDIE_MASK;

    /* PORTE Initialization */
    LATE = 0x8; /* Initial Latch Value */
    TRISECLR = 0x8; /* Direction Control */
    ANSELECLR = 0x3d2; /* Digital Mode Enable */

    /* PORTF Initialization */
    LATF = 0x0; /* Initial Latch Value */
    TRISFCLR = 0x2114; /* Direction Control */
    ANSELFCLR = 0x3000; /* Digital Mode Enable */

    /* PORTG Initialization */
    LATG = 0x1; /* Initial Latch Value */
    TRISGCLR = 0xf041; /* Direction Control */
    ANSELGCLR = 0x83c0; /* Digital Mode Enable */

    /* PORTH Initialization */
    LATH = 0x112d; /* Initial Latch Value */
    TRISHCLR = 0x3fff; /* Direction Control */
    ANSELHCLR = 0x898; /* Digital Mode Enable */
    /* Change Notice Enable */
    CNCONHSET = _CNCONH_ON_MASK;
    PORTH;
    IEC3SET = _IEC3_CNHIE_MASK;

    /* PORTJ Initialization */
    LATJ = 0x8000; /* Initial Latch Value */
    TRISJCLR = 0x8f22; /* Direction Control */
    ANSELJCLR = 0x4; /* Digital Mode Enable */

    /* PORTK Initialization */
    LATK = 0x10; /* Initial Latch Value */
    TRISKCLR = 0xff; /* Direction Control */

    // bootloader
    LATHbits.LATH14 = 0;
    TRISHbits.TRISH14 = 1;
    // end
    
    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;

    /* PPS Input Remapping */
    INT2R = 2;
    INT1R = 1;
    INT4R = 10;
    INT2R = 12;
    U1RXR = 11;
    U2RXR = 13;
    U2CTSR = 1;
    U4RXR = 6;
    U5RXR = 5;
    U3RXR = 7;
    U3CTSR = 3;

    /* PPS Output Remapping */
    RPB15R = 15;
    RPB10R = 11;
    RPF3R = 12;
    RPB7R = 2;
    RPE8R = 2;
    RPC1R = 1;
    RPG7R = 2;
    RPD7R = 3;
    RPB15R = 1;
    RPF12R = 4;

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

    /* PORTB Initialization */
    ANSELBCLR = 0x8080; /* Digital Mode Enable */

    /* PORTC Initialization */
    ANSELCCLR = 0x2; /* Digital Mode Enable */

    /* PORTD Initialization */

    /* PORTE Initialization */

    /* PORTF Initialization */

    /* PORTG Initialization */

    /* PORTH Initialization */
    LATH = 0x0; /* Initial Latch Value */
    TRISHCLR = 0xc; /* Direction Control */
    ANSELHCLR = 0x8; /* Digital Mode Enable */

    /* PORTJ Initialization */
    LATJ = 0x0; /* Initial Latch Value */
    TRISJCLR = 0x8000; /* Direction Control */

    /* PORTK Initialization */


    /* Unlock system for PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;

    /* PPS Input Remapping */
    U3RXR = 7;
    U3CTSR = 3;
    U4RXR = 6;

    /* PPS Output Remapping */
    RPC1R = 1;
    RPB15R = 1;
    RPB7R = 2;

    /* Lock back the system after PPS configuration */
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x00000000;

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
