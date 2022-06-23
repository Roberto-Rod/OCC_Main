/**
  CLC4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    clc4.c

  @Summary
    This is the generated driver implementation file for the CLC4 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides implementations for driver APIs for CLC4.
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
#include "clc4.h"

/**
  Section: CLC4 APIs
*/

void CLC4_Initialize(void)
{
    // Set the CLC4 to the options selected in the User Interface

	CLC4CONL = 0x8084 & ~(0x8000);

    CLC4CONH = 0x00;

    CLC4SELL = 0x6106;

    CLC4GLSL = 0x2002;

    CLC4GLSH = 0x00;

	
	CLC4_Enable();
}

void __attribute__ ((weak)) CLC4_PositiveEdge_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ((weak)) CLC4_NegativeEdge_CallBack(void)
{
    // Add your custom callback code here
}

void CLC4_PositiveEdge_Tasks ( void )
{
	if(IFS11bits.CLC4PIF)
	{
		// CLC4 PositiveEdge callback function 
		CLC4_PositiveEdge_CallBack();
		
		// clear the CLC4 interrupt flag
		IFS11bits.CLC4PIF = 0;
	}
}

void CLC4_NegativeEdge_Tasks ( void )
{
	if(IFS11bits.CLC4NIF)
	{
		// CLC4 NegativeEdge callback function 
		CLC4_NegativeEdge_CallBack();
		
		// clear the CLC4 interrupt flag
		IFS11bits.CLC4NIF = 0;
	}
}
bool CLC4_OutputStatusGet(void)
{
    return(CLC4CONLbits.LCOUT);

}
/**
 End of File
*/
