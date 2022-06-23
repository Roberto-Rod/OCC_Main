/////******************************************************************************
////
//// Company:   Lein Applied Diagnostics Limited
//// Project:   p15X
//// File Name: Audio_Driver.h   
//// Processor: PIC32MX
//// Hardware:  Targeted for MLT-03CHN driven via PWM
//// Assembler: pic32-gcc
//// Linker:    pic32-ld
//// 
//// Description: 
//// 
//// Functions: 
//// 
////*******************************************************************************/
////
/////*********************** Revision History **************************************
////SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
////1.      1.0     RPT                     Intial Version
////*******************************************************************************/
////
////#ifndef _AUDIO_DRIVER
////#define _AUDIO_DRIVER
////
/////*******************************************************************************
////                            Includes Files
////*******************************************************************************/
////#include <p32xxxx.h>
////#include <plib.h>
////#include "GenericTypeDefs.h"
////#include "delay.h"
/////*******************************************************************************
////                            Macros
////*******************************************************************************/
////
////#define m_InitBuzzer()		{ TRISDbits.TRISD1 = 0; T3CONbits.ON = 0; T3CONbits.TCKPS = 0; T3CONbits.TCS = 0; /* IPC3bits.T3IP = 3; IPC3bits.T3IS = 2; IFS0bits.T3IF = 0; IEC0bits.T3IE = 0; */ TMR3 = 0; PR3 = 26666; m_InitPWM();  m_Timer4();  }
////#define m_InitPWM()			{ OC2CONbits.ON = 0; OC2CONbits.OC32 = 0; OC2CONbits.OCTSEL = 1; OC2CONbits.OCM = 6; OC2R = 13000; OC2RS = 13000; /* IPC2bits.OC2IP = 3; IPC2bits.OC2IS = 1;  IFS0bits.OC2IF = 0; IEC0bits.OC2IE = 0; */ OC2CONbits.ON = 0; }
////#define m_Timer4()			{ T4CONbits.ON = 0; T4CONbits.TCKPS = 7; T4CONbits.TCS = 0; T4CONbits.T32 = 1; IPC5bits.T5IP = 7; IPC5bits.T5IS = 1; IFS0bits.T5IF = 0; IEC0bits.T5IE = 1; TMR4 = 0; PR4 = 312500; T4CONbits.ON = 0; }
////#define m_PWMOn()			{ T3CONbits.ON = 1; OC2CONbits.ON = 1; }
////#define m_PWMOff()			{ T3CONbits.ON = 0; OC2CONbits.ON = 0; }
////
/////*******************************************************************************
////                            Global Variables
////*******************************************************************************/
////
////extern unsigned short beep_frequency;
////extern unsigned short beep_count;
////
/////*******************************************************************************
////                            Function Prototypes
////*******************************************************************************/
////extern void Beep(void);
////extern void Beeps( int count );
////extern void nBeeps( unsigned short frequency, unsigned short n );
////
////#endif
////
//
//#include <xc.h>
//#include <stddef.h>
//#include <stdlib.h>
//
//#include "iScan.h"
//#include "Delay.h"
//
//#use delay(clock=80000000)
//
////define timer scaling value for each note
//#define C 255 
//#define D 227
//#define E 204
//#define F 191
//#define G 170
//#define A 153
//#define B 136
//#define C2 127
////
//
//#define x 14 //total number of notes in song to be played - modify for specific song
//
////the song to be played in this demonstration is "Twinkle Twinkle Little Star" 
//int song[x]={C, C, G, G, A, A, G, F, F, E, E, D, D, C}; //insert notes of song in array
//int length[x]={1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2}; //relative length of each note
//int i;
//
//int hello();