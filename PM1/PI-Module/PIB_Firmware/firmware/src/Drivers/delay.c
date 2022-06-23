/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   
 File Name: delay.h   
 Processor: PIC32MZ
 Hardware:  
 Assembler: XC32-gcc
 Linker:    XC32-ld
 
 Description: 
 
 Functions:
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Initial Version
*******************************************************************************/

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "delay.h"
/*******************************************************************************
                       Global Data Definitions
*******************************************************************************/
static uint32_t ReadCoreTimer(void);

static uint32_t ReadCoreTimer(void)
{
    volatile uint32_t timer;
    asm volatile("mfc0   %0, $9" : "=r"(timer));
    return(timer);
}

#define GetSystemClock() (200000000UL)/* Fcy = 200MHz */
#define ns_SCALE   (GetSystemClock()/2000000000UL)
#define us_SCALE   (GetSystemClock()/2000000UL)
#define ms_SCALE   (GetSystemClock()/2000UL)
/*******************************************************************************
 * Function:        void DelayMs(unsigned long int msDelay )
 *
 * Precondition:    None
 *
 * Input:           Delay in milli seconds
 *                  
 *
 * Output:          None
 *                  
 *                  
 *
 * Returns:         Return status
 *
 * Side Effects:    Keeps system running.
 *
 * Overview:        This function writes a voltage value to the addressed AD_DAC
 *
 * Notes:           
 *                  Millisecond Delay function using the Count register
 *                  in coprocessor 0 in the MIPS core.
 *                  When running 200 MHz, CoreTimer frequency is 100 MHz
 *                  CoreTimer increments every 2 SYS_CLK, CoreTimer period = 10ns
 *                  1 ms = N x CoreTimer_period;
 *                  To count 1ms, N = 100000 counts of CoreTimer
 *                  1 ms = 10 ns * 100000 = 10e6 ns = 1 ms
 *                  When running 80 MHz, CoreTimer frequency is 40 MHz 
 *                  CoreTimer increments every 2 SYS_CLK, CoreTimer period = 25ns
 *                  To count 1ms, N = 40000 counts of CoreTimer
 *                  1ms = 25 ns * 40000 = 10e6 ns = 1 ms
 *                  ms_SCALE = (GetSystemClock()/2000) @ 200 MHz = 200e6/2e3 = 100e3 = 100000
 *                  ms_SCLAE = (GetSystemClock()/2000) @ = 80e6/2e3 = 40e3 = 40000 
******************************************************************************/
void DelayMs(unsigned long int msDelay )
{
      // Read core timer       
      register unsigned int startCntms = ReadCoreTimer();
      // Set the wait time
      register unsigned int waitCntms = msDelay * ms_SCALE;
 
      // Wait until set delay is achieved
      while( ReadCoreTimer() - startCntms < waitCntms );
}
/*******************************************************************************
 * Function:        void DelayUs(unsigned long int usDelay )
 *
 * Precondition:    None
 *
 * Input:           Delay in micro seconds
 *                  
 *
 * Output:          None
 *                  
 *                  
 *
 * Returns:         Return status
 *
 * Side Effects:    Keeps system running.
 *
 * Overview:        This function writes a voltage value to the addressed AD_DAC
 *
 * Notes:           Microsecond Delay function using the Count register
 *                  in coprocessor 0 in the MIPS core.
 *                  When running 200 MHz, CoreTimer frequency is 100 MHz
 *                  CoreTimer increments every 2 SYS_CLK, CoreTimer period = 10ns
 *                  1 us = N x CoreTimer_period;
 *                  To count 1us, N = 100 counts of CoreTimer
 *                  1 us = 10 ns * 100 = 1000 ns  = 1us
 *                  When running 80 MHz, CoreTimer frequency is 40 MHz 
 *                  CoreTimer increments every 2 SYS_CLK, CoreTimer period = 25ns
 *                  To count 1us, N = 40 counts of CoreTimer
 *                  1us = 25 ns * 40 = 1000 ns = 1 us 
******************************************************************************/
 void DelayUs(unsigned long int usDelay )
{
     // Read core timer
      register unsigned int startCnt = ReadCoreTimer();
      // Set the wait time
      register unsigned int waitCnt = usDelay * us_SCALE;
 
      // Wait until set delay is achieved
      while( ReadCoreTimer() - startCnt < waitCnt );      
}
/*******************************************************************************
 * Function:        void DelayNs(unsigned long int nsDelay )
 *
 * Precondition:    None
 *
 * Input:           Delay in nano seconds
 *                  
 *
 * Output:          None
 *                  
 *                  
 *
 * Returns:         Return status
 *
 * Side Effects:    Keeps system running.
 *
 * Overview:        This function writes a voltage value to the addressed AD_DAC
 *
 * Notes:           Microsecond Delay function using the Count register
 *                  in coprocessor 0 in the MIPS core.
 *                  When running 200 MHz, CoreTimer frequency is 100 MHz
 *                  CoreTimer increments every 2 SYS_CLK, CoreTimer period = 10ns
 *                  1 us = N x CoreTimer_period;
 *                  To count 1us, N = 100 counts of CoreTimer
 *                  1 us = 10 ns * 100 = 1000 ns  = 1us
 *                  When running 80 MHz, CoreTimer frequency is 40 MHz 
 *                  CoreTimer increments every 2 SYS_CLK, CoreTimer period = 25ns
 *                  To count 1us, N = 40 counts of CoreTimer
 *                  1us = 25 ns * 40 = 1000 ns = 1 us 
******************************************************************************/
 void DelayNs(unsigned long int nsDelay )
{
     // Read core timer
      register unsigned int startCnt = ReadCoreTimer();
      // Set the wait time
      register unsigned int waitCnt = nsDelay * ns_SCALE;
 
      // Wait until set delay is achieved
      while( ReadCoreTimer() - startCnt < waitCnt );      
}
/*******************************************************************************
 End of File
 */
