/* ************************************************************************** */
/** @file power_switch_interrupt.c
 *
 *  @brief Power toggle switch file.
 *
 *  @copyright Occuity Limited (c) 2020
 */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "power_switch_interrupt.h"
#include "debug.h"
#include "mcc_generated_files/uart2.h"
#include "dar_comms.h"
#include "message_exchange.h"
#include "app.h"


/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/** @brief define macro reading state of pin RA1 */
#define IF_ON_OFF_BUTTON_PRESSED          (_RA1)
/** @brief define macro setting state of pin EN high */
#define TURN_PWR_OFF                      EN_SetHigh()
/** @brief define macro setting state of pin EN low */
#define TURN_PWR_ON                       EN_SetLow()
/** @brief define macro multiplexer selector bit of RB14 and RB15 pins. Sets to Uart1 or GPIO */
#define MULTIPLEXER_UART1                 PMD1bits.U1MD 
/** @brief define macro multiplexer selector bit of RB8 and RB9 pins. Sets to Uart2 or GPIO*/
#define MULTIPLEXER_UART2                 PMD1bits.U2MD
/** @brief define macro setting multiplexer selector of pins to Uart1 */
#define UART_MODULE_ENABLED               0
/** @brief define macro setting multiplexer selector of pins to GPIO */
#define UART_MODULE_DISABLED              1
/** @brief define macro setting timeout for forcing the shutdown (ms) */
//#define FORCE_SHTDWN_TIMEOUT              10000
#define FORCE_SHTDWN_TIMEOUT              3000
/** @brief define macro setting timeout for normal the shutdown (ms) */
#define SHTDWN_TIMEOUT                    2000
/** @brief define macro setting interval at which DAR is queried if it is safe to shutdown (ms) */
#define IS_SAFE_TO_SHTDWN_POLL_INTERVAL   1000
/** @brief Minimum time button pressed for device turn on */
#define TURN_ON_TIMEOUT                   10 // currently must be shorter than turn off 
/** @brief Minimum time for button to be released to enable turn on/ off possible states*/
#define DEBOUNCE_TIMEOUT                  200

/** @brief power switch enum defining states of the switching process  */
typedef enum
{   
/** @brief power switch state is idling */
    POWER_SWITCH_STATE_IDLE,
/** @brief power switch state is detected button press */
    POWER_SWITCH_STATE_DETECTED,
/** @brief power switch state is waiting for button release */
    POWER_SWITCH_STATE_WAIT_FOR_RELEASE,
/** @brief power switch state is applying delay to debounce the switch */
    POWER_SWITCH_STATE_WAIT_FOR_DEBOUNCE,
} POWER_SWITCH_STATE;



/** @brief state enum defining turn off state  */
typedef enum
{
/** @brief device was correctly turned off  */
    TURN_OFF_VALID,
/** @brief device was not turned off  correctly */
    TURN_OFF_INVALID,
/** @brief turn off not possible */
    TURN_OFF_NOT_APPLICABLE,
/** @brief turn off can occur */           
    TURN_OFF_POSSIBLE,
/** @brief turn on is possible */            
    TURN_ON_POSSIBLE,
            
            
} TURN_OFF_VALIDATION;

/** @brief power switch object defining current state of the switching process  */
typedef struct
{
/** @brief power switch state  */
    POWER_SWITCH_STATE state; 
/** @brief device state  */
    DEVICE_STATE device_state;
/** @brief turn off state  */
    TURN_OFF_VALIDATION valid_turn_off;
    
/** @brief delay shutdown countdown (ms)  */
    uint16_t shut_dwn_delay;
/** @brief Time (ms) button has been registered as pressed  */    
    uint16_t press_time;
/** @brief Time (ms) button has been registered as released  */   
    uint16_t release_time; 
/** @brief Button state  */    
    bool pressed; 
    
} POWER_SWITCH_OBJ;
/* ************************************************************************** */
/* Section: Global Variables                                                  */
/* ************************************************************************** */

/** @brief power switch object defining current state of the switching process and device state  */
static volatile POWER_SWITCH_OBJ power_switch = 
{
    .state = POWER_SWITCH_STATE_IDLE,
    .device_state = DEVICE_STATE_OFF,
    .pressed =false,
    .press_time =0,
    .release_time = 0,
    .valid_turn_off = TURN_ON_POSSIBLE,
    .shut_dwn_delay = 0, 
};

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
static void enabling_uart_modules(void);


/* ************************************************************************** */
/** 
 * @brief            Enables UART1 and UART2 modules 
 *
 * @note             Called by static void pressed_button(void) when device is 
 *                   turned on. Enables UART1 and UART2 modules
 *
 * @return           None.
 */
/* ************************************************************************** */
static void enabling_uart_modules(void)
{
    MULTIPLEXER_UART1 = UART_MODULE_ENABLED;
    MULTIPLEXER_UART2 = UART_MODULE_ENABLED;
    /** @brief UART1 & UART2 initialisation */
    UART2_Initialize();
    pic_communications_init();
} 

/** 
 * @brief            Turn on the device.
 *
 * @note             Called by  power_switch_millisecond_timer_interrupt(void) or void battery_capacity_task(void). 
 *
 * @return           None.
 */
/* ************************************************************************** */

void turn_on_device(void){
    power_switch.shut_dwn_delay = 0; 
    app_clear_flag(WARNING_FLAG_SHUTDOWN);
    TURN_PWR_ON;
    LED_RED_SetLow(); 
    power_switch.device_state = DEVICE_STATE_ON;      
    power_switch.valid_turn_off = TURN_OFF_NOT_APPLICABLE;   
    enabling_uart_modules();
#ifdef DEBUG_POWER_SW
    dputs("Turning system on\r\n");
#endif
}
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
/** 
 * @brief            Disables UART1 and UART2 modules 
 *
 * @note             Called by static process_releasing(void) when device is 
 *                   turned off. Disables UART1 and UART2 modules
 *
 * @return           None.
 */
/* ************************************************************************** */
void disabling_uart_modules(void)
{
    MULTIPLEXER_UART1 = UART_MODULE_DISABLED;
    
#ifndef DEBUG_COMS_STAY_ON 
    //MULTIPLEXER_UART2 = UART_MODULE_DISABLED;
#endif
}   
/* ************************************************************************** */
/** 
 * @brief            Turn off the device.
 *
 * @note             Called by  power_switch_millisecond_timer_interrupt(void) or void battery_capacity_task(void). 
 *
 * @return           None.
 */
/* ************************************************************************** */
void turn_off_device(void)
{
    
    #ifdef DEBUG_POWER_SW
        dputs("Turning System off\r\n");
    #endif
    if( power_switch.valid_turn_off == TURN_OFF_INVALID)
    {
        power_switch.valid_turn_off = TURN_OFF_VALID;
    }
    
    //turn off LED and wait a bit (let PI beep)
    LED_RED_SetHigh();
    uint32_t i;
    for(i=0;i<500000;i++){
        Nop();
    }

    dprintf_colour("[RED]POWER CUT OFF[WHITE]\r\n");
    TURN_PWR_OFF;
     
    power_switch.device_state = DEVICE_STATE_OFF;
    disabling_uart_modules();
    app_clear_flag(WARNING_FLAG_SHUTDOWN);
    power_switch.shut_dwn_delay = 0; 

}
/* ************************************************************************** */
/** 
 * @brief            start turn off process with delay to allow the system to shutdown gracefully
 *
 * @note             called by battery_capacity_task, to turn off device when battery level reaches critical levels
 *
 * @return           None.
 */
/* ************************************************************************** */
void delayed_turn_off(void){
    if((power_switch.device_state != DEVICE_STATE_DELAYED_OFF) && (power_switch.device_state != DEVICE_STATE_OFF)){
        power_switch.device_state = DEVICE_STATE_DELAYED_OFF;
        send_is_shutdown_safe_message(); // send shutdown warning 
        power_switch.shut_dwn_delay = IS_SAFE_TO_SHTDWN_POLL_INTERVAL*2; // set & enable delay; allowing 1 more warning to be sent
        app_set_flag(WARNING_FLAG_SHUTDOWN);
    #ifdef DEBUG_POWER_SW
        dputs("Turn off delay started\r\n");
    #endif
    }  

}

/* ************************************************************************** */
/** 
 * @brief            Process if button pressed or released.
 *
 * @note             Called by change of ON_OFF line state. resets the pressed/ release counts based on current state of switch
 *
 * @return           None.
 */
/* ************************************************************************** */
void power_switch_interrupt(void)
{

    power_switch.state = POWER_SWITCH_STATE_DETECTED; 
    if(IF_ON_OFF_BUTTON_PRESSED == 0) // Function called on change: so if current state pressed, zero pressed count
    {
        #ifdef DEBUG_POWER_SW
            dputs("Button Pressed\r\n");
        #endif
        
        power_switch.pressed = true;
        power_switch.press_time = 0; 
        
    }
    else 
    {
        #ifdef DEBUG_POWER_SW
            dputs("Button Released\r\n");
        #endif
        power_switch.pressed = false; 
        power_switch.release_time = 0; 
    }
    

}
/* ************************************************************************** */
/** 
 * @brief            Timing for debouncing or deciding if valid turn off.
 *
 * @note             Called every ms check and process button state. Button debouncing done by looking for continuous states
 *
 * @return           None.
 */
/* ************************************************************************** */
void power_switch_millisecond_timer_interrupt(void) 
{

    if (IF_ON_OFF_BUTTON_PRESSED == 0){//(power_switch.pressed){ // Increment button state time counts
        

        if(power_switch.press_time < UINT16_MAX){
            
            power_switch.press_time++; 
        }
        power_switch.release_time = 0; 
        
    }else{
        
        if(power_switch.release_time < UINT16_MAX){
            
            power_switch.release_time++; 
        }
         
    }
    // If the device is off and button has been pressed for required time -> turn on 
    if((power_switch.press_time == TURN_ON_TIMEOUT)&&(power_switch.valid_turn_off == TURN_ON_POSSIBLE)){
        
        //turn_on_device(); // Turn power on to system and setup the power switch states accordingly 
        
        power_switch.device_state = DEVICE_STATE_INIT; 
        app_clear_flag(WARNING_FLAG_SHUTDOWN);
        power_switch.press_time++; // slight fudge to ensure only one entry
        
    }else if(TURN_OFF_POSSIBLE == power_switch.valid_turn_off){ 
        // if power switch state is in turn off possible and switch has been pressed put into power off check state and wake the system
        static unsigned int next_query_time = SHTDWN_TIMEOUT;
        if(TURN_ON_TIMEOUT == power_switch.press_time){
            
            #ifdef DEBUG_POWER_SW
                dputs("Short press send wake\r\n");
            #endif
            
            wakeup_dar();
            power_switch.press_time++; // slight fudge to ensure only one entry
        }
        else if (power_switch.press_time > FORCE_SHTDWN_TIMEOUT) // if button held longer than force shutdown timeout -> just shutdown
        {
            power_switch.valid_turn_off = TURN_OFF_INVALID; 
            turn_off_device();
        }
        else if(power_switch.press_time > SHTDWN_TIMEOUT) // if button held longer than shutdown timeout -> send shutdown query to DAR
        {
            app_set_flag(WARNING_FLAG_SHUTDOWN);
            if(power_switch.press_time > next_query_time)
            {
        #ifdef DEBUG_POWER_SW
            dputs("Button Held send shutdown req\r\n");
        #endif
                send_is_shutdown_safe_message();
                next_query_time += IS_SAFE_TO_SHTDWN_POLL_INTERVAL; // increase by interval amount
            }
        }
        else
        {
            next_query_time = SHTDWN_TIMEOUT; // reset the query time 
        }

        
    }
    
    if(power_switch.release_time > (DEBOUNCE_TIMEOUT)){ // Switch has been released for minimum amount of time
        power_switch.press_time = 0; // zero pressed time
        if((power_switch.device_state == DEVICE_STATE_ON)&&(power_switch.valid_turn_off != TURN_OFF_POSSIBLE)){
            // if the device is on and switch has been released and device is off. Then change power switch state to allow for power off detection
            power_switch.valid_turn_off = TURN_OFF_POSSIBLE; 
            
        }else if((power_switch.device_state == DEVICE_STATE_OFF)&&(power_switch.valid_turn_off != TURN_ON_POSSIBLE)){
            // if the device is on and switch has been released and device is on. Then change power switch state
            power_switch.valid_turn_off = TURN_ON_POSSIBLE;
            
        }
        
        power_switch.state = POWER_SWITCH_STATE_IDLE; 
    }else{
        
        power_switch.state = POWER_SWITCH_STATE_WAIT_FOR_RELEASE; 
    }
    
    if(power_switch.shut_dwn_delay > 0){ // if time is left on shutdown delay, count down
        
        power_switch.shut_dwn_delay --; 
        
        app_set_flag(WARNING_FLAG_SHUTDOWN);
        
        if(power_switch.shut_dwn_delay == IS_SAFE_TO_SHTDWN_POLL_INTERVAL){ // resent warning
            
            send_is_shutdown_safe_message();
        }else if(power_switch.shut_dwn_delay == 0){ // end of delay force shutdown
            
            turn_off_device(); 
        }
        
    }
} 

//Test Purpose. Testing how can be sleep mode utilised  
bool is_device_on(void)
{
    if(power_switch.state == POWER_SWITCH_STATE_IDLE)
    {
        return (power_switch.device_state != DEVICE_STATE_OFF);
    }
    else 
        return true;
}

/* ************************************************************************** */
/** 
 * @brief            Get the current device power state
 *
 * @note             Use to check if off, on, powering on (INIT) or delayed shutdown
 *
 * @return           current device power state 
 */
/* ************************************************************************** */

DEVICE_STATE get_device_state(void){ 
    
    return power_switch.device_state; 
}