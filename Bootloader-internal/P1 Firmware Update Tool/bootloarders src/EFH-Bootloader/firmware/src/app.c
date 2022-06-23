/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

/*******************************************************************************
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

#define BTL_TRIGGER_PATTERN (0x5048434DUL)
static uint32_t *ramStart = (uint32_t *) BTL_TRIGGER_RAM_START;

void TriggerBootloader(void) 
{
    ramStart[0] = BTL_TRIGGER_PATTERN;
    ramStart[1] = BTL_TRIGGER_PATTERN;
    ramStart[2] = BTL_TRIGGER_PATTERN;
    ramStart[3] = BTL_TRIGGER_PATTERN;

    DCACHE_CLEAN_BY_ADDR(ramStart, 16);
    
}

bool bootloader_Trigger(void) {
    uint32_t j;

    // Cheap delay. This should give at leat 1 ms delay.
    //PW 19.04.2021
    //to detect USB voltage a lot longer pause (512000 works) is required
    for (j = 0; j < 2000; j++) {
        asm("nop");
    }
    /* Check for Bootloader Trigger Pattern in first 16 Bytes of RAM to enter
     * Bootloader.
     */
    if (BTL_TRIGGER_PATTERN == ramStart[0] && BTL_TRIGGER_PATTERN == ramStart[1] &&
            BTL_TRIGGER_PATTERN == ramStart[2] && BTL_TRIGGER_PATTERN == ramStart[3]) {
        ramStart[0] = 0;

        DCACHE_CLEAN_BY_ADDR(ramStart, 4);

        return true;
    }
    //PW 19.04.2021
    //If voltage from USB is detected enter bootloader
    //TRISBbits.TRISB12 = 0;
    //LATBbits.LATB12 = 0;
    for (j = 0; j < 550000; j++) {
        asm("nop");
    }
#define BTL_EMPTY_RAM 0
    TRISBbits.TRISB13 = 0;
    
    if (USBOTGbits.VBUS == 0b11) {
//        if (BTL_EMPTY_RAM == ramStart[0] && BTL_EMPTY_RAM == ramStart[1] &&
//                BTL_EMPTY_RAM == ramStart[2] && BTL_EMPTY_RAM == ramStart[3]) {
        if(RCONbits.SWR == 0){
            //using one of the UART3 lines to trigger bootloader in DAR
            
            LATBbits.LATB13 = 1;
            
            //using DSP_BUSY line to trigger bootloader in dsPIC
            TRISBbits.TRISB12 = 0;
            LATBbits.LATB12 = 1;
            
            return true;
        }
    }
    LATBbits.LATB13 = 0;
    
    RCONbits.SWR = 0;
    for (j = 0; j < 550000; j++) {
        asm("nop");
    }
    return false;
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void) {

    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            LED13_Clear();
            break;
        }

            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
