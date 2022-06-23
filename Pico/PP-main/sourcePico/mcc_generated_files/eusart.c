/**
  EUSART Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart.c

  @Summary
    This is the generated driver implementation file for the EUSART driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for EUSART.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16LF1509
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 

    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

/**
  Section: Included Files
 */
#include "eusart.h"


/**
  Section: EUSART APIs
 */
void EUSART_Initialize(void)
{
  // Set the EUSART module to the options selected in the user interface.

  // ABDOVF no_overflow; SCKP async_noninverted_sync_fallingedge; RCIDL idle; BRG16 16bit_generator; WUE disabled; ABDEN disabled;
  BAUDCON = 0x48;

  // SPEN enabled; OERR no_error; RX9 8-bit; RX9D 0x0; CREN disabled; ADDEN disabled; SREN disabled; FERR no_error;
  RCSTA = 0x80;

  // TRMT TSR_empty; TX9 8-bit; TX9D 0x0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode;
  TXSTA = 0x26;

  // Baud Rate = 19200; SPBRGL 51;
  SPBRGL = 0x33;

  // Baud Rate = 19200; SPBRGH 0;
  SPBRGH = 0x00;

}

bool EUSART_is_tx_ready(void)
{
    return (bool)(PIR1bits.TXIF && TXSTAbits.TXEN);
}

bool EUSART_is_rx_ready(void)
  {
    return PIR1bits.RCIF;
  }

bool EUSART_is_tx_done(void)
  {
    return TXSTAbits.TRMT;
}

uint8_t EUSART_Read(void)
{
    while(!PIR1bits.RCIF)
    {
        /** 
         * This loop may cause a Watchdog Reset if the Watchdog timeout period
         * is reached.
         * However, the MCC generated default includes a CLRWDT instruction
         * which would prevent a Watchdog Reset from occurring.
         * Uncomment the line below to include the CLRWDT instruction and prevent
         * Watchdog Resets within the While loop.
         */
        //CLRWDT();
    }

    
    if(1 == RCSTAbits.OERR)
    {
        // EUSART error - restart

        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

  return RCREG;
}

void EUSART_Write(uint8_t txData)
{
  while(0 == PIR1bits.TXIF)
  {
        /** 
         * This loop may cause a Watchdog Reset if the Watchdog timeout period
         * is reached.
         * However, the MCC generated default includes a CLRWDT instruction
         * which would prevent a Watchdog Reset from occurring.
         * Uncomment the line below to include the CLRWDT instruction and prevent
         * Watchdog Resets within the While loop.
         */
        //CLRWDT();
  }

  TXREG = txData;    // Write the data byte to the USART.
}

char getch(void)
{
  return EUSART_Read();
}

void putch(char txData)
{
  EUSART_Write(txData);
}




/**
  End of File
 */
