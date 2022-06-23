/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC24FJ64GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
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

/**
  Section: Included Files
*/


//TODO: Create generic moving average  & exponential avg filter and apply for Temperature monitoring

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr1.h"
#include "debug.h"
#include "debug_leds.h"
#include "drv_rtc.h"
#include "dar_comms.h"
#include "message_exchange.h"
#include "power_switch_interrupt.h"
//#include "drv_STTS75.h"
#include "temperature_monitor.h"
#include "battery_capacity.h"
#include "app.h"
//#include "drv_LIS2DS12.h" TODO: The work has been abandoned for now

#define INIT_ON_OFF_PIN_INTERRUPT_HANDLER   IEC1bits.IOCIE 
//#define INTERRUPT_HANDLER                IFS1bits.IOCIF
#define INTERRUPT_HANDLING_RUTINE_BEGAN     0
#define INTERRUPT_HANDLING_RUTINE_NOT_BEGAN 1




uint16_t readSTTS75Temperature(void);

/* turn off outputs that would otherwise back-power the DAR and logging */
static void power_down(void)
{
    _TRISB14 = 1;
    _TRISB13 = 1;       // not sure why this needs to set to input - it should be already
    _TRISB9 = 1;    
}

/* re-enable outputs that were turned off to prevent back-powering other parts of the circuit */
static void power_up(void)
{
    _TRISB14 = 0;
    _TRISB9 = 0;    
}

/* put the PIC24 to sleep to save power */
/* it will be woken up by a message from the DAR or a switch press */
/* or by the watchdog timer to take a temperature reading (TODO) */
static void sleep(void)
{
    /* turn off the LEDs */
    red_led(0); 
    green_led(0);
    dputs("Going to sleep \r\n");
    /* turn off outputs and then go to sleep */
    power_down();
    Sleep();

    /* turn outputs back on */
    power_up();    
}

/*
                         Main application
 */

#define MONITOR_PERIOD_MS    1000u


int main(void)
{
    uint16_t rcon_copy = RCON; 
    static uint32_t i;
    static uint32_t message = 0;
    RTCCFORM manually_set_time;
    float temperature;
    //static uint32_t loop_counter = 0;
    //static uint32_t loop_period = MONITOR_PERIOD_INIT;
    // initialize the device
    ClrWdt(); 
    SYSTEM_Initialize();
    RCONbits.VREGS = 0; // Enable Retention sleep for extra power saving, increases wake time to about 100us 
    RCONbits.RETEN =1 ; 
    //Power_Switch_Initialize();

    // initialise UART1 and the comms with the DAR
    ClrWdt(); 
    pic_communications_init();
    DRV_I2C1_Initialize(); 
    // allow the debugging LEDs to be used
    initialise_leds();
    #ifndef  DISABLE_LEDS
    red_led(0); 
    green_led(1);    
    #else
    red_led(0); 
    green_led(0);    
    #endif    

    // disable the EN line while it is being controlled by the LTC2951
    //  EN_SetDigitalInput();
    
    //  sleep & idle mode initialisation 
    // _IDLE = 0;
    // _SLEEP  = 0;
     
    // Brown out on and controlled by SBOREN bit
    // BOREN_SBOREN;
    // Enabling Software control over BOR 
    // RCONBITS.SBOREN = 1;
   
    // Brown Out Enable Bit - SBOREN bit is disabled (no software control)
    // BOREN_ON;
     ClrWdt(); 
    // start the 1KHz timer used for logging timestamps
    TMR1_Start();
    
    dprintf("\033\143");                                                // Clear terminal
    dprintf("\033[3JResetting terminal and clearing scroll-back\r\n");  // Clear scroll back
    app_initialize(rcon_copy);
    
    _SW_VERSION ver = SYS_full_version(); 

    dprintf_colour("[GREEN]Environment Controller running: V%3u.%02u Build: %03u\r\n[WHITE]\r\n", ver.major, ver.minor , ver.build);
    
    set_time_manually(&manually_set_time);
    set_time(&manually_set_time);
    
    
    ClrWdt(); 
    //Disables UART1 and UART2 modules
    disabling_uart_modules();
    for (i = 0; i < 5000; i++);

    temperature_mon_init(); 
    // configure_LIS2DS12();
    uint8_t cur_bat_soc = 255; 
    /* this in the main idle loop */
    /* nothing within this loop should take any significant length of time */
    bool one_ms_elapsed = false;
    bool turn_on_first = true; 
    uint16_t ms_elasped_cnt = 0; 
    
    uint16_t monitor_cnt = 0; 
    
    STTS75_int_t temp; 
    temp.part.whole = 15; 
    while (1)
    {
        
        if(TMR1_GetElapsedThenClear()){
            one_ms_elapsed = true; 
            
            ms_elasped_cnt++;
            
            if(ms_elasped_cnt > MONITOR_PERIOD_MS){
                ms_elasped_cnt = 0; 
            }
        }
        
        if (ms_elasped_cnt == MONITOR_PERIOD_MS)
        {

            if(monitor_cnt < 0xFFFFu) monitor_cnt++; 

            //Test Purpose. Testing drv_rtc
            // log_time_with_RTCC("[BLUE] Hi\r\n");
            //RTCCFORM current_time;
            //get_time(&current_time);

            cur_bat_soc = battery_capacity_task();
            float bat_volts = get_battery_average_value(); 
            
            #ifndef NO_DEBUG_COMMS
            dprintf("Battery cap(%%): %03d ,Avg(V): %.2f \r\n", cur_bat_soc, bat_volts);
            #endif
            
            temperature_monitor_min_200ms();
            
#ifdef DEBUG_TEMPERATURE
            
            
            int16_t temp_vals[3] = {0}; 
            
            app_get_temperature(temp_vals, 3); 
            
            float temp_cur = (float)temp_vals[0] / 256.0f;
            float temp_min = (float)temp_vals[1] / 256.0f;
            float temp_max = (float)temp_vals[2] / 256.0f;
            #ifndef NO_DEBUG_COMMS
            dprintf("Temperature(cur, min, max): %.2f, %.2f, %.2f\r\n",temp_cur, temp_min, temp_max);
            #endif
#endif
            #ifndef NO_DEBUG_COMMS
            dprintf("App flags:0x%04X\r\n", app_get_status().flags);
            #endif
        }
        

        switch(get_device_state()){

            case DEVICE_STATE_ON:
                
                wakeup_task();
                pic_comms_task();

                break;
                
            case DEVICE_STATE_INIT:
                //CLKDIVbits.DOZEN = 0; 
                
                
                if(turn_on_first == true){
                    
                    battery_capacity_reset_avg(); 
                    turn_on_first = false; 
                }
                
                if (one_ms_elapsed)
                {
                    turn_on_battery_capacity_task();
                    float bat_volts = get_battery_average_value(); 
                    dprintf("Init Bat Avg (V): %.2f \r\n", bat_volts);
                }
                
                break; 
                
            case DEVICE_STATE_OFF:
                //CLKDIVbits.DOZEN =1;
            /* at the moment the PIC24 only sleeps while the device is off */
            /* TODO: it should sleep for most of the time while the device is on too */
            /* this will save battery power */

            // Test Purpose. Testing how can be sleep mode used
                
                if ((!is_device_on()) && (monitor_cnt > 2))
                {
                    // turn off LEDs
                    
                    sleep();
                    
                    RCONbits.SLEEP =0; 
                    //battery_capacity_reset_avg(); 
                    monitor_cnt = 0; 
                    ms_elasped_cnt = MONITOR_PERIOD_MS -1; 
                    #ifndef DISABLE_LEDS
                    green_led(1);
                    #endif
                    turn_on_first = true; 

                }
                break; 
            
            
            
            default:
                
                break; 
        }

        ClrWdt(); 
       one_ms_elapsed = false;  
    }
    
    return (1);
}

/**
 End of File
*/
