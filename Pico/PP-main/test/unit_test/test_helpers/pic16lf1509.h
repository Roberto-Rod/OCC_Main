/*****************************************************************************
 *   File        : pic16lf1509.h
 *
 *   Description: Header file for PIC16LF1509 register definitions for test application.
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

#ifndef _PIC16LF1509_H_
#define _PIC16LF1509_H_

#include "unity.h"

// bitfield definitions
typedef union {
    struct {
        unsigned LATA0                  :1;
        unsigned LATA1                  :1;
        unsigned LATA2                  :1;
        unsigned                        :1;
        unsigned LATA4                  :1;
        unsigned LATA5                  :1;
    };
} LATAbits_t;

// bitfield definitions
typedef union {
    struct {
        unsigned                        :4;
        unsigned LATB4                  :1;
        unsigned LATB5                  :1;
        unsigned LATB6                  :1;
        unsigned LATB7                  :1;
    };
} LATBbits_t;

// bitfield definitions
typedef union {
    struct {
        unsigned LATC0                  :1;
        unsigned LATC1                  :1;
        unsigned LATC2                  :1;
        unsigned LATC3                  :1;
        unsigned LATC4                  :1;
        unsigned LATC5                  :1;
        unsigned LATC6                  :1;
        unsigned LATC7                  :1;
    };
} LATCbits_t;


#define NCO1CON NCO1CON

typedef union {
    struct {
        unsigned ADON                   :1;
        unsigned GO_nDONE               :1;
        unsigned CHS                    :5;
    };
    struct {
        unsigned                        :1;
        unsigned ADGO                   :1;
        unsigned CHS0                   :1;
        unsigned CHS1                   :1;
        unsigned CHS2                   :1;
        unsigned CHS3                   :1;
        unsigned CHS4                   :1;
    };
    struct {
        unsigned                        :1;
        unsigned GO                     :1;
    };
} ADCON0bits_t;

// bitfield definitions
typedef union {
    struct {
        unsigned RA0                    :1;
        unsigned RA1                    :1;
        unsigned RA2                    :1;
        unsigned RA3                    :1;
        unsigned RA4                    :1;
        unsigned RA5                    :1;
    };
} PORTAbits_t;

// bitfield macros
#define _PORTA_RA0_MASK                 0x01
#define _PORTA_RA1_MASK                 0x02
#define _PORTA_RA2_MASK                 0x04
#define _PORTA_RA3_MASK                 0x08
#define _PORTA_RA4_MASK                 0x10
#define _PORTA_RA5_MASK                 0x20


// bitfield definitions
typedef union {
    struct {
        unsigned                        :4;
        unsigned RB4                    :1;
        unsigned RB5                    :1;
        unsigned RB6                    :1;
        unsigned RB7                    :1;
    };
} PORTBbits_t;

// bitfield macros
#define _PORTB_RB4_MASK                 0x10
#define _PORTB_RB5_MASK                 0x20
#define _PORTB_RB6_MASK                 0x40
#define _PORTB_RB7_MASK                 0x80


// bitfield definitions
typedef union {
    struct {
        unsigned RC0                    :1;
        unsigned RC1                    :1;
        unsigned RC2                    :1;
        unsigned RC3                    :1;
        unsigned RC4                    :1;
        unsigned RC5                    :1;
        unsigned RC6                    :1;
        unsigned RC7                    :1;
    };
} PORTCbits_t;

// bitfield macros
#define _PORTC_RC0_MASK                 0x01
#define _PORTC_RC1_MASK                 0x02
#define _PORTC_RC2_MASK                 0x04
#define _PORTC_RC3_MASK                 0x08
#define _PORTC_RC4_MASK                 0x10
#define _PORTC_RC5_MASK                 0x20
#define _PORTC_RC6_MASK                 0x40
#define _PORTC_RC7_MASK                 0x80

//gpio registers
extern volatile PORTAbits_t PORTAbits;
extern volatile PORTBbits_t PORTBbits;
extern volatile PORTCbits_t PORTCbits;

extern volatile LATAbits_t LATAbits;
extern volatile LATBbits_t LATBbits;
extern volatile LATCbits_t LATCbits;

//ADC registers
extern uint8_t ADCON0;
extern uint8_t ADCON1; 
extern uint8_t ADCON2; 
extern uint8_t ADRESL; 
extern uint8_t ADRESH;

extern unsigned char NCO1CON;

extern volatile unsigned char  NCO1INCL;
extern volatile unsigned char  NCO1INCH;


#endif // _PIC16LF1509_H_
