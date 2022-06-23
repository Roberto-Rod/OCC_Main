/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC24FJ64GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/


/**
    Section: Includes
*/

#include <xc.h>
#include <stdio.h>
#include "pin_manager.h"
#include "..\power_switch_interrupt.h"

/**
 Section: File specific functions
*/
void (*ON_OFF_InterruptHandler)(void) = NULL;
void (*ACCEL_INT1_InterruptHandler)(void) = NULL;
void (*ACCEL_INT2_InterruptHandler)(void) = NULL;
void (*CHARGE_STAT_InterruptHandler)(void) = NULL;

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x4200;
    LATBbits.LATB10 = 1;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x0003;
    TRISB = 0xA19F;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    IOCPDA = 0x0000;
    IOCPDB = 0x0000;
    IOCPUA = 0x0002;
    IOCPUB = 0x0080;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0060;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSA = 0x0001;
    ANSB = 0x0000;
    
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPOR7bits.RP14R = 0x0003;    //RB14->UART1:U1TX
    RPOR4bits.RP9R = 0x0005;    //RB9->UART2:U2TX
    RPINR19bits.U2RXR = 0x0008;    //RB8->UART2:U2RX
    RPINR18bits.U1RXR = 0x000F;    //RB15->UART1:U1RX

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    
    /****************************************************************************
     * Interrupt On Change: any
     ***************************************************************************/
    IOCNAbits.IOCNA1 = 1;    //Pin : RA1
    IOCNBbits.IOCNB2 = 1;    //Pin : RB2
    IOCNBbits.IOCNB3 = 1;    //Pin : RB3
    IOCNBbits.IOCNB7 = 1;    //Pin : RB7
    IOCPAbits.IOCPA1 = 1;    //Pin : RA1
    IOCPBbits.IOCPB2 = 1;    //Pin : RB2
    IOCPBbits.IOCPB3 = 1;    //Pin : RB3
    IOCPBbits.IOCPB7 = 1;    //Pin : RB7
    /****************************************************************************
     * Interrupt On Change: flag
     ***************************************************************************/
    IOCFAbits.IOCFA1 = 0;    //Pin : RA1
    IOCFBbits.IOCFB2 = 0;    //Pin : RB2
    IOCFBbits.IOCFB3 = 0;    //Pin : RB3
    IOCFBbits.IOCFB7 = 0;    //Pin : RB7
    /****************************************************************************
     * Interrupt On Change: config
     ***************************************************************************/
    PADCONbits.IOCON = 1;    //Config for PORTA
    
    /* Initialize IOC Interrupt Handler*/
    ON_OFF_SetInterruptHandler(&ON_OFF_CallBack);
    ACCEL_INT1_SetInterruptHandler(&ACCEL_INT1_CallBack);
    ACCEL_INT2_SetInterruptHandler(&ACCEL_INT2_CallBack);
    CHARGE_STAT_SetInterruptHandler(&CHARGE_STAT_CallBack);
    
    /****************************************************************************
     * Interrupt On Change: Interrupt Enable
     ***************************************************************************/
    IFS1bits.IOCIF = 0; //Clear IOCI interrupt flag
    IEC1bits.IOCIE = 1; //Enable IOCI interrupt
}

void __attribute__ ((weak)) ON_OFF_CallBack(void)
{
    power_switch_interrupt();
}

void __attribute__ ((weak)) ACCEL_INT1_CallBack(void)
{

}

void __attribute__ ((weak)) ACCEL_INT2_CallBack(void)
{

}

void __attribute__ ((weak)) CHARGE_STAT_CallBack(void)
{

}

void ON_OFF_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC1bits.IOCIE = 0; //Disable IOCI interrupt
    ON_OFF_InterruptHandler = InterruptHandler; 
    IEC1bits.IOCIE = 1; //Enable IOCI interrupt
}

void ON_OFF_SetIOCInterruptHandler(void *handler)
{ 
    ON_OFF_SetInterruptHandler(handler);
}

void ACCEL_INT1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC1bits.IOCIE = 0; //Disable IOCI interrupt
    ACCEL_INT1_InterruptHandler = InterruptHandler; 
    IEC1bits.IOCIE = 1; //Enable IOCI interrupt
}

void ACCEL_INT1_SetIOCInterruptHandler(void *handler)
{ 
    ACCEL_INT1_SetInterruptHandler(handler);
}

void ACCEL_INT2_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC1bits.IOCIE = 0; //Disable IOCI interrupt
    ACCEL_INT2_InterruptHandler = InterruptHandler; 
    IEC1bits.IOCIE = 1; //Enable IOCI interrupt
}

void ACCEL_INT2_SetIOCInterruptHandler(void *handler)
{ 
    ACCEL_INT2_SetInterruptHandler(handler);
}

void CHARGE_STAT_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC1bits.IOCIE = 0; //Disable IOCI interrupt
    CHARGE_STAT_InterruptHandler = InterruptHandler; 
    IEC1bits.IOCIE = 1; //Enable IOCI interrupt
}

void CHARGE_STAT_SetIOCInterruptHandler(void *handler)
{ 
    CHARGE_STAT_SetInterruptHandler(handler);
}

/* Interrupt service routine for the IOCI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _IOCInterrupt ( void )
{
    if(IFS1bits.IOCIF == 1)
    {
        if(IOCFAbits.IOCFA1 == 1)
        {
            if(ON_OFF_InterruptHandler) 
            { 
                ON_OFF_InterruptHandler(); 
            }
            
            IOCFAbits.IOCFA1 = 0;  //Clear flag for Pin - RA1

        }
        
        if(IOCFBbits.IOCFB2 == 1)
        {
            if(ACCEL_INT1_InterruptHandler) 
            { 
                ACCEL_INT1_InterruptHandler(); 
            }
            
            IOCFBbits.IOCFB2 = 0;  //Clear flag for Pin - RB2

        }
        
        if(IOCFBbits.IOCFB3 == 1)
        {
            if(ACCEL_INT2_InterruptHandler) 
            { 
                ACCEL_INT2_InterruptHandler(); 
            }
            
            IOCFBbits.IOCFB3 = 0;  //Clear flag for Pin - RB3

        }
        
        if(IOCFBbits.IOCFB7 == 1)
        {
            if(CHARGE_STAT_InterruptHandler) 
            { 
                CHARGE_STAT_InterruptHandler(); 
            }
        
            IOCFBbits.IOCFB7 = 0;  //Clear flag for Pin - RB7

        }
        
        
        // Clear the flag
        IFS1bits.IOCIF = 0;
    }
}

