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
#include "debug.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     VREGS
#pragma config DBGPER =     PG_ALL
#pragma config SMCLR =      MCLR_NORM
#pragma config SOSCGAIN =   GAIN_1X
#pragma config SOSCBOOST =  OFF
#pragma config POSCGAIN =   GAIN_1X
#pragma config POSCBOOST =  OFF
#pragma config POSCFGAIN =  GAIN_G2
#pragma config POSCAGCDLY = POSCAGCDLY1
#pragma config POSCAGC =      OFF
#pragma config EJTAGBEN =   REDUCED

/*** DEVCFG1 ***/
#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF
#pragma config POSCMOD =    EC
#pragma config OSCIOFNC =   ON//camera clock
#pragma config FCKSM =      CSECMD
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config WINDIS =     NORMAL
#pragma config FWDTEN =     OFF
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF

/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_3
#pragma config FPLLRNG =    RANGE_5_10_MHZ
#pragma config FPLLICLK =   PLL_POSC
#pragma config FPLLMULT =   MUL_50
#pragma config FPLLODIV =   DIV_2
#pragma config VBATBOREN =  OFF
#pragma config DSBOREN =    ON
#pragma config DSWDTPS =    DSPS32
#pragma config DSWDTOSC =   LPRC
#pragma config DSWDTEN =    OFF
//ERRATA DEEP SLEEP IS NOT FUNCTIONAL
#pragma config FDSEN =      OFF
#pragma config UPLLFSEL =   FREQ_24MHZ

/*** DEVCFG3 ***/
#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     OFF
#pragma config PGL1WAY =    OFF
#pragma config PMDL1WAY =   OFF
#pragma config IOL1WAY =    OFF

/*** DEVCFG4 ***/
#pragma config SWDTPS = SPS1048576

/*** BF1SEQ0 ***/
#pragma config TSEQ =       0x0
#pragma config CSEQ =       0xffff





// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_OVM7692 Configuration">
/*** OVM7692 Driver Initialization Data ***/

const DRV_CAMERA_OVM7692_INIT drvCameraInit =
{
    .cameraID                = CAMERA_MODULE_OVM7692,
    .sourcePort              = (void *)&PORTE,
    .pwdnPin                 = SYS_PORT_PIN_RB11,
    .shdnPin                 = SYS_PORT_PIN_RB13,   
    .hsyncInterruptSource    = INT_SOURCE_EXTERNAL_1,
    .vsyncInterruptSource    = INT_SOURCE_EXTERNAL_4,
    .pclkInterruptSource     = INT_SOURCE_EXTERNAL_2,
    .dmaChannel1             = DRV_CAMERA_OVM7692_DMA_CHANNEL1_INDEX,
    .dmaChannel2             = DRV_CAMERA_OVM7692_DMA_CHANNEL2_INDEX,
    .dmaChannel3             = DRV_CAMERA_OVM7692_DMA_CHANNEL3_INDEX,
    .dmaChannel4             = DRV_CAMERA_OVM7692_DMA_CHANNEL4_INDEX,   
    .frameVerticalSize       = DRV_CAMERA_FRAME_HEIGHT,
    .frameHorizontalSize     = DRV_CAMERA_FRAME_WIDTH,
    .bytesPerPixel           = DRV_CAMERA_COLOUR_DEPTH,
};

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

    DBINIT();
    
    CLK_Initialize();
	GPIO_Initialize();
    
    /* Configure Prefetch, Wait States and ECC */
    PRECONbits.PREFEN = 3;
    PRECONbits.PFMWS = 2;
    CFGCONbits.ECCCON = 3;

    DMAC_Initialize();
    
    OCMP1_Initialize();
    OCMP3_Initialize();
    
    CORETIMER_Initialize();

    SCCB_Initialize();
    

    DRV_I2C2_Initialize();
    DRV_I2C3_Initialize();
    
    TMR2_Initialize();

    TMR3_Initialize();
    
    TMR4_Initialize();
    TMR4_InterruptEnable();
    BUZZER_OutputEnable();
    BUZZER_Clear();

	DDR_Initialize();
   
    debug_initialise();

    TMR9_Initialize();

    GFX_Initialize();
    
    /* Initialise system timer  */
    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);

    /* Initialise Camera Driver Interface */
    sysObj.drvOVM7692 = DRV_CAMERA_OVM7692_Initialize(DRV_CAMERA_OVM7692_INDEX_0, (SYS_MODULE_INIT *) &drvCameraInit);
    DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, 1, 1);//init position values to non zero values

    SYS_INP_Init();    
    
    // initialize UI library
    LibAria_Initialize();    

    APP_Initialize();

    EVIC_Initialize();

     /* Initialise Display Driver */
    ST7701S_Init();

    pic_communications_init();
    
    pic24_communications_init();
    
    PWRCONbits.VREGS = 1;
        
	/* Enable global interrupts */
    __builtin_enable_interrupts();
}


/*******************************************************************************
 End of File
*/
