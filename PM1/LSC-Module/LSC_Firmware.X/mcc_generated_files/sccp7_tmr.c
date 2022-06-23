/**
  SCCP7 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    sccp7.c

  @Summary
    This is the generated driver implementation file for the SCCP7 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for SCCP7. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33CK128MP203
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB             :  MPLAB X v5.10
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
  Section: Included Files
*/

#include <xc.h> 
#include "sccp7_tmr.h"

/**
  Section: Data Type Definitions
*/

/**
  SCCP7 Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

*/
typedef struct _SCCP7_TMR_OBJ_STRUCT
{

    /* Timer Elapsed */
    bool                                                    primaryTimer16Elapsed;
    bool                                                    secondaryTimer16Elapsed;
    bool                                                    Timer32Elapsed;
} SCCP7_TMR_OBJ;

static SCCP7_TMR_OBJ sccp7_timer_obj;
void SCCP7_TMR_Initialize(void)
{
    // CCPON enabled; MOD 16-Bit/32-Bit Timer; CCSEL disabled; CCPSIDL disabled; TMR32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL OSC/2; TMRSYNC disabled; 
    CCP7CON1L = (0x8000 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; IOPS Each Time Base Period Match; SYNC None; OPSRC Timer Interrupt Event; 
    CCP7CON1H = 0x00;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP7CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC7; AUXOUT Special Event Trigger; OCAEN disabled; OENSYNC disabled; 
    CCP7CON2H = 0x10;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP7CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; TRIG disabled; ICGARM disabled; TRCLR disabled; 
    CCP7STATL = 0x00;
    //TMR 0; 
    CCP7TMRL = 0x00;
    //TMR 0; 
    CCP7TMRH = 0x00;
    //PR 65535; 
    CCP7PRL = 0xFFFF;
    //PR 0; 
    CCP7PRH = 0x00;
    //CMP 0; 
    CCP7RAL = 0x00;
    //CMP 0; 
    CCP7RBL = 0x00;
    //BUF 0; 
    CCP7BUFL = 0x00;
    //BUF 0; 
    CCP7BUFH = 0x00;

    CCP7CON1Lbits.CCPON = 0x1; //Enabling CCP

    IFS9bits.CCP7IF = 0;

    IFS9bits.CCT7IF = 0;
      


}

void SCCP7_TMR_Start( void )
{
    /* Reset the status information */
    sccp7_timer_obj.primaryTimer16Elapsed = false;
    sccp7_timer_obj.secondaryTimer16Elapsed = false;
    sccp7_timer_obj.Timer32Elapsed = false;

    /* Start the Timer */
    CCP7CON1Lbits.CCPON = true;
}

void SCCP7_TMR_Stop( void )
{
    /* Stop the Timer */
    CCP7CON1Lbits.CCPON = false;
}

void __attribute__ ((weak)) SCCP7_TMR_PrimaryTimerCallBack(void)
{
    // Add your custom callback code here
}

void SCCP7_TMR_PrimaryTimerTasks( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS9bits.CCT7IF)
    {
		// SCCP7 Primary Timer callback function 
		SCCP7_TMR_PrimaryTimerCallBack();
		
        sccp7_timer_obj.primaryTimer16Elapsed = true;
        IFS9bits.CCT7IF = 0;
    }
}


void __attribute__ ((weak)) SCCP7_TMR_SecondaryTimerCallBack(void)
{
    // Add your custom callback code here
}

void SCCP7_TMR_SecondaryTimerTasks( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS9bits.CCP7IF)
    {
		// SCCP7 Secondary Timer callback function 
		SCCP7_TMR_SecondaryTimerCallBack();
        sccp7_timer_obj.secondaryTimer16Elapsed = true;
        IFS9bits.CCP7IF = 0;
    }
}

void SCCP7_TMR_Period16BitPrimarySet( uint16_t value )
{
    /* Update the counter values */
    CCP7PRL = value;

    /* Reset the status information */
    sccp7_timer_obj.primaryTimer16Elapsed = false;
}

void SCCP7_TMR_Period16BitSecondarySet( uint16_t value )
{
    /* Update the counter values */
    CCP7PRH = value;

    /* Reset the status information */
    sccp7_timer_obj.secondaryTimer16Elapsed = false;
}

uint16_t SCCP7_TMR_Period16BitPrimaryGet( void )
{
    return( CCP7PRL );
}
uint16_t SCCP7_TMR_Period16BitSecondaryGet( void )
{
    return( CCP7PRH );
}

void SCCP7_TMR_Counter16BitPrimarySet ( uint16_t value )
{
    /* Update the counter values */
    CCP7PRL = value;
    /* Reset the status information */
    sccp7_timer_obj.primaryTimer16Elapsed = false;
}

void SCCP7_TMR_Counter16BitSecondarySet ( uint16_t value )
{
    /* Update the counter values */
    CCP7PRH = value;
    /* Reset the status information */
    sccp7_timer_obj.secondaryTimer16Elapsed = false;
}

uint16_t SCCP7_TMR_Counter16BitPrimaryGet( void )
{
    return( CCP7TMRL );
}

uint16_t SCCP7_TMR_Counter16BitSecondaryGet( void )
{
    return( CCP7TMRH );
}

bool SCCP7_TMR_PrimaryTimer16ElapsedThenClear(void)
{
    bool status;
    
    status = sccp7_timer_obj.primaryTimer16Elapsed ;
    
    if(status == true)
    {
        sccp7_timer_obj.primaryTimer16Elapsed = false;
    }
    return status;
}

bool SCCP7_TMR_SecondaryTimer16ElapsedThenClear(void)
{
    bool status;
    
    status = sccp7_timer_obj.secondaryTimer16Elapsed ;
    
    if(status == true)
    {
        sccp7_timer_obj.secondaryTimer16Elapsed = false;
    }
    return status;
}

/**
 End of File
*/