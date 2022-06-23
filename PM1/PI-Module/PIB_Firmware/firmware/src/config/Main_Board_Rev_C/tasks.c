/*******************************************************************************
 System Tasks File

  File Name:
    tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled tasks.

  Description:
    This file contains source code necessary to maintain system's polled tasks.
    It implements the "SYS_Tasks" function that calls the individual "Tasks"
    functions for all polled MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
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
#include "app.h"

APP_DATA appData;

static void loop_1ms(void)
{
    static uint8_t loop_state = 0;
    /* Maintain system services */
    
    
    notification_tasks(false);
    DRV_CAMERA_OVM7692_Tasks(sysObj.drvOVM7692);
    
    drv_cst130_touch_controller_task();//average <320ns; max 320us (on touch)
            
    switch(loop_state)
    {
        default:
            drv_pca9530_led_controller_task();//average <250ns; max 31us 

            main_menu_task();//average <350ns; max 98us

            /* Maintain Middleware & Other Libraries */
            SYS_INP_Tasks();//average <300ns; max 4.2us
            
            message_exchange_task();//average <54ns; max 270ns
            
            loop_state = 1;
            break;
        case 1:
            /* Maintain the application's state machine */
            /* Call Application task APP */
            APP_Tasks();//average <20us; max 500us
            loop_state = 2;
            break;
        case 2:
            if(appData.logo_animation == false)
            {
                DRV_CAMERA_test_comms();
            }
            loop_state = 3;
            break;
        case 3:
            loop_state = 4;
            break;
        case 4:
            loop_state = 5;
            break;
        case 5:
            loop_state = 6;
            break;
        case 6:
            loop_state = 7;
            break;
        case 7:
            loop_state = 8;
            break;
        case 8:
            loop_state = 9;
            break;
        case 9:
            loop_state = 10;
            break;
        case 10:
            loop_state = 11;
            break;
        case 11:
            loop_state = 12;
            break;
        case 12:
            loop_state = 13;
            break;
        case 13:
            loop_state = 14;
            break;
        case 14:
            loop_state = 0;
            break;
    }
    
    if(drv_led_pca9530_fading_tasks() == false)
    {
        //block Libaria while animating LEDs
        LibAria_Tasks();
    }
    
    /* call any current test code */
    //Test_Task();
}

void clock_full_speed(void){

    __builtin_disable_interrupts();

    /* unlock system for clock configuration */
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    
    //SPLLCONbits.PLLMULT = 50;
    //SPLLCONbits.PLLODIV = 0b1;

    /* Peripheral Bus 1 is by default enabled, set its divisor */
    PB1DIVbits.PBDIV = 5;
//    PB2DIVbits.PBDIV = 2;
//    PB3DIVbits.PBDIV = 2;
    PB4DIVbits.PBDIV = 2;
    PB5DIVbits.PBDIV = 2;
    PB6DIVbits.PBDIV = 2;
    PB7DIVbits.PBDIV = 0;

    /* Set up Reference Clock 5 */
    /* Enable oscillator (ON bit) */
    REFO5CONSET = 0x00008000;

    /* CFGMPLL */
    /* MPLLVREGDIS = ENABLED */
    /* INTVREFCON = EXTERNAL_DDRV */
    /* MPLLIDIV = DIV_1 */
    /* MPLLMULT = MUL_30 */
    /* MPLLODIV2 = DIV_1 */
    /* MPLLODIV1 = DIV_3 */
    /* MPLLDIS = ENABLED */
    

    /* Peripheral Module Disable Configuration */
    PMD1 = 0x101101;
    PMD2 = 0x3;
    PMD3 = 0x1fa01ff;
    PMD4 = 0xf1;
    PMD5 = 0x301f3f0b;
    PMD6 = 0x10a10000;
    PMD7 = 0x500000;

    /* Lock system since done with clock configuration */
    __builtin_enable_interrupts();

    SYSKEY = 0x33333333;
    
    /* Configure Prefetch, Wait States and ECC */
    PRECONbits.PREFEN = 3;
    PRECONbits.PFMWS = 2;
    CFGCONbits.ECCCON = 3;
}

void clock_power_saving(void){

    __builtin_disable_interrupts();

    /* unlock system for clock configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    //SPLLCONbits.PLLMULT = 48;
    //SPLLCONbits.PLLODIV = 0b10;

    /* Peripheral Bus 1 is by default enabled, set its divisor */
    PB1DIVbits.PBDIV = 0b0001111;
    //PB3DIVbits.ON = 0;
    //PB2DIVbits.PBDIV = 3;//probably damages uart
    //PB3DIVbits.PBDIV = 3;//damages buzzer
    PB4DIVbits.PBDIV = 3;
    PB5DIVbits.PBDIV = 0b1111111;
    PB6DIVbits.PBDIV = 0b1111111;
    PB7DIVbits.PBDIV = 64;

    /* Set up Reference Clock 5 */
    /* Enable oscillator (ON bit) */
    REFO5CONSET = 0x00000000;
  

    /* Peripheral Module Disable Configuration */
    PMD1 = 0xf;
    PMD2 = 0x3;
    PMD3 = 0x1fa01ff;
    PMD4 = 0xf1;
    PMD5 = 0x301f3f0b;
    PMD6 = 0x10a10000;
    PMD7 = 0x500000;

    /* Lock system since done with clock configuration */
    __builtin_enable_interrupts();

    SYSKEY = 0x33333333;
    /* Configure Prefetch, Wait States and ECC */
    PRECONbits.PREFEN = 0;
    PRECONbits.PFMWS = 7;
    CFGCONbits.ECCCON = 0;
}
// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/
void SYS_Tasks ( void )
{
    
    /* monitor system activity and power down when inactive */
    power_management_task();//average <200ns; max 2us
    pic_comms_task();//average <320ns; max 50us
    pic24_comms_task();//average <580ns; max 17us
    GFX_Update();//average <250ns; max 2.6us
    
    if(appData.logo_animation == true)
    {
        //increase LibAria update rate when logo is animated - removes animation jitter
        LibAria_Tasks();
    }
    
    if(appData.timer1ms == true)
    {
        //clock_full_speed();
        loop_1ms();
        appData.timer1ms = false;
//        if(appData.state == APP_STATE_IDLE && !piezo_busy()){
//        clock_power_saving();}
    }
    else
    {
        Nop();
    }
}

/*******************************************************************************
 End of File
 */

