/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"
#include "../test/support/unity_helper.h"




// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx2
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config SMCLR =      MCLR_NORM
#pragma config SOSCGAIN =   GAIN_LEVEL_0
#pragma config SOSCBOOST =  OFF
#pragma config POSCGAIN =   GAIN_LEVEL_0
#pragma config POSCBOOST =  OFF
#pragma config EJTAGBEN =   NORMAL
#pragma config CP =         OFF

/*** DEVCFG1 ***/
#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF
#pragma config POSCMOD =    EC
#pragma config OSCIOFNC =   ON
#pragma config FCKSM =      CSDCMD
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     NORMAL
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF

/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_3
#pragma config FPLLRNG =    RANGE_5_10_MHZ
#pragma config FPLLICLK =   PLL_POSC
#pragma config FPLLMULT =   MUL_50
#pragma config FPLLODIV =   DIV_2
#pragma config UPLLFSEL =   FREQ_24MHZ

/*** DEVCFG3 ***/
#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     OFF
#pragma config PGL1WAY =    OFF
#pragma config PMDL1WAY =   OFF
#pragma config IOL1WAY =    OFF
#pragma config FUSBIDIO =   OFF

/*** BF1SEQ0 ***/

#pragma config TSEQ =       0xffff
#pragma config CSEQ =       0x0





// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
/******************************************************
 * USB Driver Initialization
 ******************************************************/

const DRV_USBHS_INIT drvUSBInit =
{
    /* Interrupt Source for USB module */
    .interruptSource = INT_SOURCE_USB,

	/* Interrupt Source for USB module */
    .interruptSourceUSBDma = INT_SOURCE_USB_DMA,
	
    /* System module initialization */
    .moduleInit = {0},

    /* USB Controller to operate as USB Device */
    .operationMode = DRV_USBHS_OPMODE_DEVICE,

	/* Enable High Speed Operation */
    .operationSpeed = USB_SPEED_HIGH,
    
    /* Stop in idle */
    .stopInIdle = true,

    /* Suspend in sleep */
    .suspendInSleep = false,

    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USBHS_ID_0,
	
};




// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)CORETIMER_CallbackSet,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)CORETIMER_CounterGet,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)CORETIMER_FrequencyGet,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)CORETIMER_CompareSet,
    .timerStart = (SYS_TIME_PLIB_START)CORETIMER_Start,
    .timerStop = (SYS_TIME_PLIB_STOP)CORETIMER_Stop 
};

const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = 0,
};

// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************



/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{
    /* Start out with interrupts disabled before configuring any modules */
    __builtin_disable_interrupts();

#ifndef TEST_DISABLE_CLK  
    CLK_Initialize();
#endif //TEST_DISABLE_CLK
    
#ifndef TEST_DISABLE_PRE
    /* Configure Prefetch, Wait States and ECC */
    PRECONbits.PREFEN = 3;
    PRECONbits.PFMWS = 2;
    CFGCONbits.ECCCON = 3;
#endif //TEST_DISABLE_PRE

#ifndef TEST_DISABLE_GPIO
	GPIO_Initialize();
#endif //TEST_DISABLE_GPIO

#ifndef TEST_DISABLE_DMAC
    DMAC_Initialize();
#endif //TEST_DISABLE_DMAC

#ifndef TEST_DISABLE_CVR
	CVR_Initialize();
#endif //TEST_DISABLE_CVR

#ifndef TEST_DISABLE_CMP
	CMP_Initialize();
#endif //TEST_DISABLE_CMP

#ifndef TEST_DISABLE_CORETIMER
    CORETIMER_Initialize();
#endif //TEST_DISABLE_CORETIMER

#ifndef TEST_DISABLE_ADCHS
    ADCHS_Initialize();
#endif //TEST_DISABLE_ADCHS
    
#ifndef TEST_DISABLE_TMR1
    TMR1_Initialize(); 
#endif //TEST_DISABLE_TMR1
    
#ifndef TEST_DISABLE_TMR2
    TMR2_Initialize();
#endif //TEST_DISABLE_TMR2

#ifndef TEST_DISABLE_TMR3
    TMR3_Initialize();
#endif //TEST_DISABLE_TMR3

#ifndef TEST_DISABLE_TMR4
    TMR4_Initialize();
#endif //TEST_DISABLE_TMR4

#ifndef TEST_DISABLE_I2C4
    DRV_I2C4_Initialize();    // discrete driver
#endif //TEST_DISABLE_I2C4

#ifndef TEST_DISABLE_UART2
////////	UART2_Initialize();
#endif //TEST_DISABLE_UART2

#ifndef TEST_DISABLE_SQI
    #ifdef DISABLE_FRAM
    SQI_init();
    disable_FRAM();
    #endif
#endif //TEST_DISABLE_SQI

#ifndef TEST_DISABLE_PMP
    PMP_Initialize();
#endif //TEST_DISABLE_PMP

#ifndef TEST_DISABLE_USB
    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);

	 /* Initialize the USB device layer */
    sysObj.usbDevObject0 = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 , ( SYS_MODULE_INIT* ) & usbDevInitData);

	/* Initialize USB Driver */ 
    sysObj.drvUSBHSObject = DRV_USBHS_Initialize(DRV_USBHS_INDEX_0, (SYS_MODULE_INIT *) &drvUSBInit);
    
    USBCSR0bits.SOFTCONN=0;	
#endif //TEST_DISABLE_USB

#ifndef TEST_DISABLE_PDAB
    PDAB_Initialize();
#endif //TEST_DISABLE_PDAB

#ifndef TEST_DISABLE_EVIC
    EVIC_Initialize();
#endif //TEST_DISABLE_EVIC

#ifndef TEST_DISABLE_DEBUG
    debug_initialise();
#endif //TEST_DISABLE_DEBUG

#ifndef TEST_DISABLE_HELPER_UART_INIT
    unity_helper_uart_init();
#endif //TEST_DISABLE_HELPER_UART_INIT

#ifndef TEST_DISABLE_HELPER_TMR2_INIT
    unity_helper_tmr2_init();
#endif //TEST_DISABLE_HELPER_TMR2_INIT

#ifndef TEST_DISABLE_PIC_COMMS
    pic_communications_init();
#endif //TEST_DISABLE_PIC_COMMS

#ifndef TEST_DISABLE_DSPIC_PIC_COMMS
    dspic_pic_communications_init();
#endif //TEST_DISABLE_DSPIC_PIC_COMMS 
  
	/* Enable global interrupts */
    __builtin_enable_interrupts();
}


/*******************************************************************************
 End of File
*/
