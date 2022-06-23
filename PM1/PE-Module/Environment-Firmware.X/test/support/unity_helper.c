#ifndef UNITY_HELPER_C
#define UNITY_HELPER_C

#include "system.h"

void unity_helper_dead_loop(void){
	while(1) { }
}

void unity_helper_send_dbg_char(char a){

    while(U2STAbits.UTXBF == 1)
    {
    }

    U2TXREG = a;    // Write the data byte to the USART.

}

void unity_helper_uart_init(void)
{
    LATB = 0x4200;
    TRISB = 0x63FF;
    IOCPDB = 0x0000;
    IOCPUB = 0x0000;
    ODCB = 0x0000;
    ANSB = 0x0000;

    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPOR4bits.RP9R = 0x0005;    //RB9->UART2:U2TX
    RPINR19bits.U2RXR = 0x0008;    //RB8->UART2:U2RX

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

    U2MODE = (0x8008 & ~(1<<15));  // disabling UARTEN bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U2STA = 0x00;
    // BaudRate = 115200; Frequency = 4000000 Hz; U2BRG 8; 
    U2BRG = 0x08;
    // ADMADDR 0; ADMMASK 0; 
    U2ADMD = 0x00;
    
    U2MODEbits.UARTEN = 1;   // enabling UART ON bit
    U2STAbits.UTXEN = 1;
}

#endif // UNITY_HELPER_C