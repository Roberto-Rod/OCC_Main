/*****************************************************************************
 *   File        : pic16lf1509.c
 *
 *   Description: PIC16LF1509 register definitions for test application.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "pic16lf1509.h"

//#GPIO registers
volatile PORTAbits_t PORTAbits;
volatile PORTBbits_t PORTBbits;
volatile PORTCbits_t PORTCbits;


volatile LATAbits_t LATAbits;
volatile LATBbits_t LATBbits;
volatile LATCbits_t LATCbits;

//mock ADC registers
uint8_t ADCON0;
uint8_t ADCON1; 
uint8_t ADCON2; 
uint8_t ADRESL; 
uint8_t ADRESH;

unsigned char NCO1CON;

volatile unsigned char  NCO1INCL;
volatile unsigned char  NCO1INCH;

