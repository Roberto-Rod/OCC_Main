#ifndef UNITY_HELPER_C
#define UNITY_HELPER_C

#include "definitions.h"

#ifndef TEST_DISABLE_HELPER_TMR2_INIT
static uint32_t milliseconds;
#endif //TEST_DISABLE_HELPER_TMR2_INIT

void unity_helper_dead_loop(void){
    while(1) {};
}

void unity_helper_send_dbg_char(char a){

    while (1 == U1STAbits.UTXBF);
    /* add the character to the UART transmit FIFO */
    U1TXREG = a;

}

void unity_helper_uart_init(void)
{

    U1MODE = 0;
    U1MODEbits.STSEL = 1;   /* two stop bits - seems to fix an issue when */
                            /* one stop bit is selected */

    /* Enable UART1 Transmitter and TX Interrupt selection */
    U1STA = 0;
    U1STAbits.UTXISEL = 0;
    U1STAbits.UTXEN = 1;

    /* BAUD Rate register Setup */
    U1BRG = 53;                     /* 115,200 Baud */

    /* Disable Interrupts */
    IEC3CLR = _IEC3_U1EIE_MASK;
    IEC3CLR = _IEC3_U1RXIE_MASK;
    IEC3CLR = _IEC3_U1TXIE_MASK;

     /* Turn ON UART1 */
    U1MODESET = _U1MODE_ON_MASK;

}

#ifndef TEST_DISABLE_HELPER_TMR2_INIT
void     TIMER_2_InterruptHandler(void);

void __ISR(_TIMER_2_VECTOR, ipl1AUTO) TIMER_2_Handler (void)
{
    TIMER_2_InterruptHandler();
}

void unity_helper_tmr2_interrupt(uint32_t status, uintptr_t context)
{
    (void) status;
    (void) context;

    milliseconds++;

}

void unity_helper_tmr2_init(void)
{
    INTCONSET = _INTCON_MVEC_MASK;

    IPC2SET = 0x400 | 0x0;  /* TIMER_2:  Priority 1 / Subpriority 0 */

    TMR2_CallbackRegister(unity_helper_tmr2_interrupt, 0);
    TMR2_InterruptEnable();
}

void unity_helper_tic(void)
{
    TMR2 = 0x0;
	milliseconds = 0;
    TMR2_Start();
}

uint32_t unity_helper_toc(void)
{
	uint32_t timer_val = TMR2;
	float microseconds = (float)milliseconds * 1000.0 + (float)timer_val * 2.56;
    TMR2_Stop();

	return (uint32_t)microseconds;
}
#endif //TEST_DISABLE_HELPER_TMR2_INIT


#endif // UNITY_HELPER_C