/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    clock.c

  @Summary:
    This is the clock.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CK128MP203
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
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

#include <stdint.h>
#include "xc.h"
#include "clock.h"

void CLOCK_Initialize(void)
{
    // FRCDIV FRC/1; PLLPRE 1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3001;
    // PLLFBDIV 100; 
    PLLFBD = 0x65;
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // POST1DIV 1:4; VCODIV FVCO/2; POST2DIV 1:1; 
    PLLDIV = 0x241;
    // APLLEN disabled; FRCSEL FRC; APLLPRE 1:1; 
    ACLKCON1 = 0x101;
    // APLLFBDIV 150; 
    APLLFBD1 = 0x96;
    // APOST1DIV 1:4; APOST2DIV 1:1; AVCODIV FVCO/2; 
    APLLDIV1 = 0x241;
    // ROEN enabled; ROSLP disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; 
    REFOCONL = 0x8000;
    // RODIV 0; 
    REFOCONH = 0x00;
    // IOLOCK disabled; 
    RPCON = 0x00;
    // PMDLOCK disabled; 
    PMDCON = 0x00;
    // ADC1MD disabled; T1MD enabled; U2MD enabled; U1MD enabled; SPI2MD disabled; SPI1MD enabled; QEIMD enabled; PWMMD disabled; I2C1MD disabled; 
    PMD1 = 0x291;
    // CCP2MD enabled; CCP1MD disabled; CCP4MD disabled; CCP3MD disabled; CCP7MD enabled; CCP8MD disabled; CCP5MD disabled; CCP6MD disabled; CCP9MD disabled; 
    PMD2 = 0x1BD;
    // I2C3MD disabled; U3MD disabled; QEI2MD disabled; CRCMD disabled; I2C2MD disabled; 
    PMD3 = 0x1AE;
    // REFOMD disabled; 
    PMD4 = 0x08;
    // DMA1MD disabled; SPI3MD disabled; DMA2MD disabled; DMA3MD disabled; DMA0MD enabled; 
    PMD6 = 0xE01;
    // CMP3MD disabled; PTGMD disabled; CMP1MD enabled; CMP2MD disabled; 
    PMD7 = 0x608;
    // DMTMD disabled; CLC3MD enabled; OPAMPMD disabled; BIASMD disabled; CLC4MD enabled; SENT2MD disabled; SENT1MD disabled; CLC1MD enabled; CLC2MD enabled; 
    PMD8 = 0x3902;
    // CF no clock failure; NOSC FRCPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (( 0x01 << _OSCCON_NOSC_POSITION ) >> 0x08 ));
    __builtin_write_OSCCONL((uint8_t) ((0x100 | _OSCCON_OSWEN_MASK) & 0xFF));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1);
}

bool CLOCK_AuxPllLockStatusGet()
{
    return ACLKCON1bits.APLLCK;
}
