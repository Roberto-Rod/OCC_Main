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
////1.      1.0     RMR                     Intial Version
////*******************************************************************************/
////
////unsigned short beep_frequency = 0;
////unsigned short beep_count = 0;
////
/////*******************************************************************************
////                            Includes Files
////*******************************************************************************/
//#include "Audio_Driver.h"
//
//void hello()
//{
//        setup_ccp1(RP1); // PWM output on pin 17, RC2/CCP1 
//      set_pwm1_duty(30);  // the number changes the volume of the piezo speaker
//}
//// /*******************************************************************************
//// * Function:        Beep
//// *
//// * Precondition:    None
//// *
//// * Input:          	None
//// *                  
//// *                  
//// *
//// * Output:          None
//// *                 
//// *                  
//// *
//// * Returns:         None
//// *
//// * Side Effects:    Keeps system running.
//// *
//// * Overview:        This function outputs a single beep.
//// *
//// * Notes:           None
//// ******************************************************************************/
////void Beep(void)
////{
////	m_PWMOn(); 
////	Delay( Delay_100ms );
////	m_PWMOff();
////}
//// /*******************************************************************************
//// * Function:        Beep
//// *
//// * Precondition:    None
//// *
//// * Input:          	None
//// *                  
//// *                  
//// *
//// * Output:          None
//// *                 
//// *                  
//// *
//// * Returns:         None
//// *
//// * Side Effects:    Keeps system running.
//// *
//// * Overview:        This function outputs a single beep.
//// *
//// * Notes:           None
//// ******************************************************************************/
////void Beeps( int count )
////{
////	while(1) 
////	{	
////		m_PWMOn(); 
////		Delay( Delay_200ms );
////		m_PWMOff();
////					
////		if( --count <= 0 )
////			break;	
////		else
////			Delay( Delay_200ms );
////	}	
////}
//// /*******************************************************************************
//// * Function:        nBeeps
//// *
//// * Precondition:    None
//// *
//// * Input:          	None
//// *                  
//// *                  
//// *
//// * Output:          None
//// *                 
//// *                  
//// *
//// * Returns:         None
//// *
//// * Side Effects:    Keeps system running.
//// *
//// * Overview:        This function outputs a single beep.
//// *
//// * Notes:           None
//// ******************************************************************************/
////void nBeeps( unsigned short frequency, unsigned short n)
////{
////	beep_frequency = frequency;
////	beep_count = n << 1;
////	PR4 = ( 312500 / frequency );
////	if( TMR4 >= PR4 )
////		TMR4 = 0;
////	T4CONbits.ON = 1;
////	m_PWMOn(); 
////}
////
