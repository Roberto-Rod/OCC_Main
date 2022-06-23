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
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33CK128MP203
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
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
#include "pin_manager.h"
#include "../encoder_drv.h"

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0002;
    LATB = 0x8080;
    LATC = 0x0000;
    
    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x0011;
    TRISB = 0xBF63;
    TRISC = 0x0028;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0008;
    CNPUC = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0xE000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x0011;
    ANSELB = 0x0000;
    ANSELC = 0x0000;


    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_RPCON(0x0000); // unlock PPS

    RPINR46bits.CLCINBR = 0x002D;    //RB13->CLC4:CLCINB
    RPOR7bits.RP46R = 0x0001;    //RB14->UART1:U1TX
    RPINR18bits.U1RXR = 0x002F;    //RB15->UART1:U1RX
    RPOR3bits.RP39R = 0x0003;    //RB7->UART2:U2TX
    RPINR45bits.CLCINAR = 0x002A;    //RB10->CLC3:CLCINA
    RPINR0bits.INT1R = 0x0033;    //RC3->EXT_INT:INT1
    RPINR19bits.U2RXR = 0x0026;    //RB6->UART2:U2RX
    RPOR1bits.RP35R = 0x003B;    //RB3->CLC3:CLC3OUT

    __builtin_write_RPCON(0x0800); // lock PPS

}

/* Interrupt service routine for the CNAI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _CNAInterrupt ( void )
{
    if(IFS0bits.CNAIF == 1)
    {
        // Clear the flag
        IFS0bits.CNAIF = 0;
    }
}
/* Interrupt service routine for the CNBI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _CNBInterrupt ( void )
{
    if(IFS0bits.CNBIF == 1)
    {
        
        if(CNFBbits.CNFB5){
           
            z_INT_callback(); 
            
           CNFBbits.CNFB5 = 0; 
        }
        
        // Clear the flag
        IFS0bits.CNBIF = 0;
    }
}
