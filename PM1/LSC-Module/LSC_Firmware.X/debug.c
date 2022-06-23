/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    debug.c

  @Summary
    Functions for logging to a console via a UART.

  @Description
    Console logging functions.

    Logging criteria:
    1) Logging ideally needs to return fast and must be non-blocking
    2) No logging should be lost
 
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdarg.h>
#include <string.h>

#include "debug.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/interrupt_manager.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define DEBUG_BUFFER_LENGTH                         ( 2 * 1024 )    // the size of the debug buffer
#define BLOCKING_DEBUG                                              // #define to make the debug code block until the message has been sent
#define LOG_TIME                                                    // #define this to have time logged on every line
#define ENABLE_DEBUG

#define MINIMUM_TOKEN_LENGTH                        5               // minimum length of a colour token
#define MAXIMUM_TOKEN_LENGTH                        10              // maximum length of a colour token

/* buffer used for console output */
#ifndef BLOCKING_DEBUG
static char transmit_buffer[DEBUG_BUFFER_LENGTH];
static uint32_t input_index = 0;
static uint32_t output_index = 0;
#endif
static DebugTime run_time;
static uint16_t milliseconds;

static uint32_t start_milliseconds;
static const char *get_colour(const char *string, bool *found);
static void detokenise(const char * input, char *output);

#ifndef BLOCKING_DEBUG
static bool buffer_add(char ch);
static bool buffer_empty(void);
static bool buffer_full(void);
#endif

static void send_string(const char *string);

#ifdef BLOCKING_DEBUG
static void blocking_dputc(char ch);
#endif

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Function Name: get_colour                                                  */
/*                Get the escape code string for the supplied colour tag      */
/* @param[in] char *string : the escape code                                  */
/* @param[out] bool_t *found : true if the tag was found, false if not        */
/* @retval the escape code for the colour tag, or the original string if      */
/* there was no match                                                         */
/* ************************************************************************** */
static const char *get_colour(const char *string, bool *found)
{
    const char *colour_codes[] = {"[BLACK]", BLACK, "[RED]", RED, "[GREEN]", GREEN, "[YELLOW]", YELLOW,
                                  "[BLUE]", BLUE, "[MAGENTA]", MAGENTA, "[CYAN]", CYAN, "[WHITE]", WHITE,
                                  "[ORANGE]", ORANGE, "[PINK]", PINK, "[BROWN]", BROWN,
                                  "[PURPLE]", PURPLE};
	uint8_t i;

	for (i = 0; i < 12; i++)
	{
		if (0 == strcmp(string, colour_codes[i << 1]))
		{
			*found = true;
			return colour_codes[(i << 1) + 1];
		}
	}

	*found = false;
	return (string);
}
/* End of function get_colour                                                 */

/* ************************************************************************** */
/* Function Name: detokenise                                                  */
/*                Replace colour tokens with terminal colour escape codes     */
/* @param[in] input : input string possibly containing colour tokens          */
/* @param[out] output : string with colour tokens replaced with escape codes  */
/* @retval none                                                               */
/* ************************************************************************** */
static void detokenise(const char * input, char *output)
{
    int16_t start_bracket_index;
    int16_t end_bracket_index;
    int16_t start_bracket_output_index;
    uint16_t i;
    uint16_t o;
    char token[MAXIMUM_TOKEN_LENGTH + 1];
    uint8_t token_length;
    bool token_found;
    const char *colour_code;
    bool token_replaced;

    start_bracket_index = -1;
    end_bracket_index = -1;
    start_bracket_output_index = 0;
    o = 0;

    /* scan the input string */
    for (i = 0; '\0' != input[i]; i++)
    {
        token_replaced = false;

        /* token start? */
        if ('[' == input[i])
        {
            start_bracket_index = i;
            start_bracket_output_index = o;
        }

        /* token end? */
        if (']' == input[i])
        {
            end_bracket_index = i;

            /* check to see if we have a token */
            if (start_bracket_index >= 0)
            {
                token_length = end_bracket_index - start_bracket_index + 1;

                if ((token_length >= MINIMUM_TOKEN_LENGTH) && (token_length <= MAXIMUM_TOKEN_LENGTH))
                {
                    /* copy the token to a buffer */
                    strncpy(token, &input[start_bracket_index], token_length);
                    token[token_length] = '\0';

                    /* check for a valid token */
                    colour_code = get_colour(token, &token_found);
                    
                    /* if we have a colour token, then replace it in the output with the associated escape code */
                    if (token_found)
                    {
                        strcpy(&output[start_bracket_output_index], colour_code);
                        o = start_bracket_output_index + strlen(colour_code);
                        token_replaced = true;
                    }
                }
            }

            /* reset and start looking for another token */            
            start_bracket_index = -1;
            end_bracket_index = -1;
        }

        /* if we didn't replace a token, then carry on copying input to output */
        if (!token_replaced)
        {
            output[o] = input[i];
            o++;
        }
    }

    /* terminate the output string */
    output[o] = '\0';
}
/* End of function detokenise                                                 */

/**************************************************************************** */
/* Function Name: buffer_add                                                  */
/*                add a character to the debug logging buffer                 */
/* @param[in] char ch : the character to add to the buffer                    */
/* @retval true if the character was added, false if the buffer is full       */
/* ************************************************************************** */
#ifndef BLOCKING_DEBUG
static bool buffer_add(char ch)
{
    if (buffer_full())
    {
        return (false);
    }

    transmit_buffer[input_index] = ch;
    input_index++;

    if (input_index >= DEBUG_BUFFER_LENGTH)
    {
        input_index = 0;
    }

    return (true);
}
#endif
/* End of function buffer_add                                                 */

/**************************************************************************** */
/* Function Name: buffer_empty                                                */
/*                determine whether or not the debug logging buffer is empty  */
/* @retval true if the buffer is empty                                        */
/* ************************************************************************** */
#ifndef BLOCKING_DEBUG
static bool buffer_empty(void)
{
    return (input_index == output_index);
}
#endif
/* End of function buffer_empty                                               */

/**************************************************************************** */
/* Function Name: buffer_full                                                 */
/*                determine whether or not the debug logging buffer is full   */
/* @retval true if the buffer is full                                         */
/* ************************************************************************** */
#ifndef BLOCKING_DEBUG
static bool buffer_full(void)
{
    uint32_t next_input_index;

    next_input_index = input_index + 1;

    if (next_input_index >= DEBUG_BUFFER_LENGTH)
    {
        next_input_index = 0;
    }

    return (next_input_index == output_index);
}
#endif
/* End of function buffer_full                                                */

/**************************************************************************** */
/* Function Name: blocking_dputc                                              */
/*                output a character to the debug console after waiting for   */
/*                the UART to finish transmitting the previous character      */
/* @param[in] char ch : character to output                                   */
/* @retval None                                                               */
/* ************************************************************************** */
#ifdef BLOCKING_DEBUG
static void blocking_dputc(char ch)
{
    UART1_Write((const uint8_t) ch);
}
#endif
/* End of function blocking_dputc                                             */

/**************************************************************************** */
/* Function Name: UART1_TX_InterruptHandler                                   */
/*                UART transmit interrupt handler for the debug logger        */
/* @retval None                                                               */
/* ************************************************************************** */
//void debug_transmit_interrupt_callback(void)
//void UART1_TX_InterruptHandler(void)
//{
//    char ch;
//
//    /* top up the FIFO transmit buffer */
//    while ((input_index != output_index) && (0 == U1STAbits.UTXBF))
//    {
//        /* get the next character to be sent and increment the output pointer */
//        ch = transmit_buffer[output_index];
//        output_index++;
//
//        if (output_index >= DEBUG_BUFFER_LENGTH)
//        {
//            output_index = 0;
//        }
//
//        /* send the character */
//        U1TXREG = ch;
//    }
//
//    /* clear the UART2TX Interrupt flag after writing to buffer */
//    IFS3CLR = _IFS3_U1TXIF_MASK;
//
//    /* if the buffer is now empty, then there won't be anything further to send */
//    if (input_index == output_index)
//    {
//        /* disable the transmit interrupt */
//        IEC3bits.U1TXIE = 0;
//    }
//}
/* End of function UART1_TX_InterruptHandler                                  */

/**************************************************************************** */
/* Function Name: send_string                                                 */
/*                output a null terminated string to the debug console        */
/* @param[in] string : the string to output                                   */
/* @retval None                                                               */
/* ************************************************************************** */
#ifdef BLOCKING_DEBUG
static void send_string(const char *string)
{
    uint16_t i;

    for (i = 0; '\0' != string[i]; i++)
    {
          UART1_Write(string[i]);
    }
}
#else
static void send_string(const char *string)
{
    uint16_t i;
    bool buffering;

    /* disable interrupts */
    IEC3bits.U1TXIE = 0;

    /* check for characters in the software buffer */
    buffering = !buffer_empty();

    /* add the string to the TX FIFO and/or software buffer */    
    for (i = 0; '\0' != string[i]; i++)
    {
        if (buffering)
        {
            if (!buffer_add(string[i]))
            {
                /* the software buffer is full */
                break;
            }
        }
        else
        {
            /* if the UART transmit buffer is full */
            if (1 == U1STAbits.UTXBF)
            {
                buffering = true;
                buffer_add(string[i]);
            }
            else
            {
                /* add the character to the UART transmit FIFO */
                U1TXREG = string[i];
            }
        }
    }

    /* if there are characters in the software buffer, then we need to enable transmit interrupts */
    if (buffering)
    {
        IEC3bits.U1TXIE = 1;
    }
}
#endif
/* End of function send_string                                                */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
// called once per second to update the time
void debug_increment_time(DebugTime *time)
{
    time -> second++;

    if (time -> second < 60)
    {
        return;
    }

    time -> second = 0;
    time -> minute++;

    if (time -> minute < 60)
    {
        return;
    }

    time -> minute = 0;
    time -> hour++;

    if (time -> hour >= 24)
    {
        time -> hour = 0;
    }
}
/**************************************************************************** */
/* Function Name: debug_initialise                                            */
/*                Initialise the debug logging module                         */
/* @retval None                                                               */
/* ************************************************************************** */
void debug_initialise(void)
{
    timeouts_init(); 
//    U1MODE = 0;
//    U1MODEbits.STSEL = 1;   /* two stop bits - seems to fix an issue when */
//                            /* one stop bit is selected */
//
//    /* Enable UART1 Receiver, Transmitter and TX Interrupt selection */
//    //U1STASET = (_U1STA_UTXEN_MASK | _U1STA_URXEN_MASK | _U1STA_UTXISEL0_MASK);
//
//    U1STA = 0;
//    U1STAbits.UTXISEL = 0;
//    U1STAbits.UTXEN = 1;
//
//    /* BAUD Rate register Setup */
//    //U1BRG = 650;                  /* 19,200 Baud */
//    U1BRG = 53;                     /* 115,200 Baud */
//
//    /* Disable Interrupts */
//    IEC3CLR = _IEC3_U1EIE_MASK;
//    IEC3CLR = _IEC3_U1RXIE_MASK;
//    IEC3CLR = _IEC3_U1TXIE_MASK;
//
//     /* Turn ON UART1 */
//    U1MODESET = _U1MODE_ON_MASK;

    milliseconds = 0;
    run_time.hour = 0;
    run_time.minute = 0;
    run_time.second = 0;

//    TMR2_CallbackRegister(debug_millisecond_timer_interrupt, 0);
//    TMR2_Start();
//    TMR2_InterruptEnable();
}
/* End of function debug_initialise                                           */

#define NUM_COUNTDOWN_TMRS 5



typedef enum{
    
    UNUSED  = 0, 
    IDLE = 1, 
    RUNNING  = 2, 
    ELAPSED = 3,
    LOCKED = 4,
    
}timeout_state_t;


typedef struct{
    
    volatile int32_t durn; 
    volatile timeout_state_t state; 
}timeout_t; 

static struct{
    
    timeout_t timeouts[NUM_COUNTDOWN_TMRS]; 
    uint8_t num_used; 
    bool locked; 
    bool init; 
}timeout_mgr = {.init = false, .locked =true};


void timeouts_init(){
    
    if(timeout_mgr.init == false){
            uint8_t i= 0; 
        for(i = 0; i <NUM_COUNTDOWN_TMRS; i++){

            timeout_mgr.timeouts[i].durn = -1; 
            timeout_mgr.timeouts[i].state = UNUSED; 
        }

        timeout_mgr.num_used = 0; 

        timeout_mgr.locked = false; 
        timeout_mgr.init = true; 
    }

}

#define TIMEOUT_INV_HANDLE (-1)
#define TIMEOUT_HANDLE_PRE  (0xCE00u)

inline int8_t handle_to_idx(timeout_handle_t handle){
    
    int8_t idx = (handle & 0x00FFu); 
    
    if(((handle & 0xFF00u) == TIMEOUT_HANDLE_PRE) && (idx < NUM_COUNTDOWN_TMRS)){
        
        return idx; 
    }else{
        
        return TIMEOUT_INV_HANDLE; 
    }
}

inline timeout_handle_t idx_to_handle (int8_t idx){
    
    if(idx < NUM_COUNTDOWN_TMRS){
        
        return (timeout_handle_t)(TIMEOUT_HANDLE_PRE | (timeout_handle_t)(idx)); 
    }
    return 0; 
}

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* start system timer */
 bool timeout_start(timeout_handle_t handle,uint32_t delay)
{
    if(delay> INT32_MAX){
        
        delay= INT32_MAX; 
    }
    
    int8_t idx = handle_to_idx(handle); 
    
    if(idx == TIMEOUT_INV_HANDLE){
        
        return false; 
    }
    

    timeout_mgr.timeouts[idx].state = LOCKED; 
    timeout_mgr.timeouts[idx].durn = delay; 
    timeout_mgr.timeouts[idx].state = RUNNING; 
    
    return true; 
    
}



int8_t timeout_check(timeout_handle_t handle){
    
    int8_t idx = handle_to_idx(handle); 
    if(idx == TIMEOUT_INV_HANDLE){
        
        return TIMEOUT_HANDLE_INV; 
    }
    
    switch(timeout_mgr.timeouts[idx].state){
        
        case ELAPSED:
            
            timeout_mgr.timeouts[idx].state = IDLE; 
            
            return TIMEOUT_EXPIRED; 
            break; 
            
        case RUNNING:
            
            return TIMEOUT_RUNNING; 
            break; 
            
        default:
            
            return TIMEOUT_INVALID; 
            break; 
        
    }

}

#define RETURN_TIMEOUT_MGR_UNLOCK( val) timeout_mgr.locked = false; return val 

bool timeout_alloc(uint16_t* handle){
    
    if(timeout_mgr.locked == true){
        
        return false; 
    }
    
    timeout_mgr.locked = true; 
    int8_t idx = handle_to_idx(*handle); 
    if((idx != TIMEOUT_INV_HANDLE)&&(timeout_mgr.num_used > 0)){
        
        if(timeout_mgr.timeouts[idx].state == IDLE){
            
            
           
            RETURN_TIMEOUT_MGR_UNLOCK( true); 
        }
        
    }
    
    if(timeout_mgr.num_used < NUM_COUNTDOWN_TMRS){
        
       
        for(idx = 0; idx <NUM_COUNTDOWN_TMRS; idx++){
            
            
            if(timeout_mgr.timeouts[idx].state == UNUSED){
                
                
                * handle = idx_to_handle(idx);
                timeout_mgr.timeouts[idx].state = IDLE; 
                timeout_mgr.num_used++; 
                
                RETURN_TIMEOUT_MGR_UNLOCK(true); 
            }
            
        }
        
        
        
    }else{
        
        dputs("Hit maximum number of timeout allocations"); 
        
    }
    
   
    RETURN_TIMEOUT_MGR_UNLOCK(false); 
}

bool timeout_free(uint16_t* handle){
    
    bool success = false; 
    
    if(timeout_mgr.locked == true){
        
        return false; 
    }
    
    timeout_mgr.locked = true; 
    int8_t idx = handle_to_idx(*handle); 
    if((idx != TIMEOUT_INV_HANDLE)&&(timeout_mgr.num_used > 0)){
        
        timeout_mgr.timeouts[idx].durn = -1;
        timeout_mgr.timeouts[idx].state = UNUSED; 
        timeout_mgr.num_used--;
        * handle = 0; 
        success = true; 
        
        
    }
    timeout_mgr.locked = false; 
    return success; 

}

void timeouts_update_tick(void){
    
    uint8_t i =0; 
    for (i = 0; i < NUM_COUNTDOWN_TMRS; i++){
        if(timeout_mgr.timeouts[i].state == RUNNING){
            if(timeout_mgr.timeouts[i].durn > 0){

                timeout_mgr.timeouts[i].durn--; 
            }else if(timeout_mgr.timeouts[i].durn == 0){

                timeout_mgr.timeouts[i].state = ELAPSED; 
                timeout_mgr.timeouts[i].durn = -1; 
            }
        }
        
    }
    
}
static timeout_handle_t timers[NUM_COUNTDOWN_TMRS+1]   = {0}; 
static bool timer0_elapsed = false; 

void timeouts_test_tick(){
    
    static uint16_t timeout_9ms = 0; 
    
    if(timeout_check(timers[0]) == TIMEOUT_RUNNING){
        
        DBG_LEDB_SetLow();
    }else{
        
        DBG_LEDB_SetHigh();
    }
    timeout_9ms++; 
    if(timeout_9ms == 8){
        DBG_LEDG_Toggle(); 
        timeout_9ms = 0; 
        
        if(timeout_check(timers[0]) == TIMEOUT_EXPIRED){
            
            timer0_elapsed = true; 
        }
        timeout_start(timers[0], 10); 
        
    }
}

void timeouts_test(void){
    
    
    static uint8_t i = 0; 
    
    static int8_t test_state = 0; 
    int8_t check_res = 0; 
    switch(test_state){
        
        
        case 0:
        case 1: 
                
            
            if (i <(NUM_COUNTDOWN_TMRS+1)){
                timeout_alloc(timers+i); 
                dprintf("timeout_handle: 0x%04X\r\n",timers[i]); 
                i++; 
            }else{
                
                i = 0; 
                test_state++; 
            }
                
            
            
            break; 
            
        case 2: 
            
            if (i <NUM_COUNTDOWN_TMRS){
                
                if(timeout_start(timers[i], 250*(i+1))){
                    
                    dprintf("timer %d started\r\n", i); 
                    
                }else{
                    
                    dprintf("timer %d start failed\r\n", i); 
                    
                }
                i++; 
            }else{
                
                i = 0; 
                test_state++; 
            }
            break; 
            
        case 3:
            
            check_res = timeout_check(timers[i]); 
            
            if(timer0_elapsed){
                dputs("time 0 has elapsed\r\n"); 
                
                timer0_elapsed = false; 
            }
            
            if(check_res == TIMEOUT_EXPIRED){

                dprintf("timer %d expired\r\n", i); 

            }else if(check_res == TIMEOUT_INVALID) {

                dprintf("timer %d Invalid state\r\n", i);

                if(timeout_start(timers[i], 250*(i+1))){

                    dprintf("timer %d restarted\r\n", i); 

                }else{

                    dprintf("timer %d restart failed\r\n", i); 

                }

            }else if(check_res == TIMEOUT_HANDLE_INV){

                dprintf("timer %d Handle Invalid\r\n", i); 
            }else if (check_res ==TIMEOUT_RUNNING){
                
                dprintf("timer %d running\r\n", i); 
            }
            
            i++;
            
            timeout_start(timers[0], 5); 
            
            if(i > NUM_COUNTDOWN_TMRS) i = 0; 
                    
                    

            
            
            break; 
    }

}




static volatile uint16_t next_pulse = 0; 
static volatile uint16_t active_time = 0;
static volatile bool dbg_out_active = false; 

#define DEBUG_OUT_ACTIVE    //DBG_LEDG_SetLow()
#define DEBUG_OUT_IDLE      //DBG_LEDG_SetHigh()

#define DEBUG_OUT_BLANK_MS 1

void debug_output_pulse_proc(){
    
    
    static uint16_t blank_time = DEBUG_OUT_BLANK_MS; 
    
    if(active_time > 0){
         DEBUG_OUT_ACTIVE;
         
         active_time --; 
         blank_time = 0; 
         dbg_out_active = true; 
    }else if(blank_time < DEBUG_OUT_BLANK_MS){
        DEBUG_OUT_IDLE; 
        blank_time++;
        dbg_out_active = false; 
    }else{
        
        if(next_pulse > 0){
            active_time = next_pulse; 
            next_pulse = 0; 
        }
    }

}

void debug_output_pulse(uint16_t width_ms){
    
    if(dbg_out_active){
        next_pulse = width_ms; 
    }else{
        active_time = width_ms; 
        DEBUG_OUT_ACTIVE;
    }
    
}


/**************************************************************************** */
/* Function Name: debug_millisecond_timer_interrupt                           */
/*                This needs to be called every ms to increment the timer     */
/* @retval None                                                               */
/* ************************************************************************** */
void debug_millisecond_timer_interrupt(void)
{
    milliseconds++;
    
    debug_output_pulse_proc();
    if (milliseconds >= 1000)
    {
        milliseconds = 0;
        debug_increment_time(&run_time);
    }
}
/* End of debug_millisecond_timer_interrupt                                */


/**************************************************************************** */
/* Function Name: dprintf_colour                                              */
/*                As dprintf, but replaces colour tags with escape codes      */
/* @param[in] char *format : the format string                                */
/* @param[in] ... : argument list, 0 or more parameters                       */
/* @retval None                                                               */
/* ************************************************************************** */
void dprintf_colour(const char *format, ...)
{
    #ifndef ENABLE_DEBUG
    return;
    #endif     
    
	va_list arglist;
    static char colour_format[256];
    static char final_buffer[256];
 
    va_start(arglist, format);

    /* replace colour tokens with terminal colour escape codes */
    detokenise(format, colour_format);

    vsprintf(final_buffer, colour_format, arglist);
    va_end(arglist);

    dputs(final_buffer);
}
/* End of function dprintf_colour                                             */

/**************************************************************************** */
/* Function Name: dprintf                                                     */
/*                printf to the debug console                                 */
/* @param[in] char *format : the format string                                */
/* @param[in] ... : argument list, 0 or more parameters                       */
/* @retval None                                                               */
/* ************************************************************************** */
void dprintf(const char *format, ...)
{
    #ifndef ENABLE_DEBUG
    return;
    #endif     
    
	va_list arglist;
    static char buffer[256];

   
    
    va_start(arglist, format);
    vsprintf(buffer, format, arglist);
    va_end(arglist);

    /* output the complete string */
    dputs(buffer);
}
/* End of function dprintf                                                    */

/**************************************************************************** */
/* Function Name: dputc                                                       */
/*                output a single character to the debug console              */
/* @param[in] char ch : character to output                                   */
/* @retval None                                                               */
/* ************************************************************************** */
#ifdef BLOCKING_DEBUG
void dputc(char ch)
{
    #ifndef ENABLE_DEBUG
    return;
    #endif    

    blocking_dputc(ch);
}
#else
void dputc(char ch)
{
    bool buffering;

    #ifndef ENABLE_DEBUG
    return;
    #endif    

    /* disable interrupts */
    IEC3bits.U1TXIE = 0;

    /* check for characters in the software buffer */
    buffering = !buffer_empty();

    /* add the character to the TX FIFO or the software buffer */
    if (buffering)
    {
        buffer_add(ch);
    }
    else
    {
        /* if the UART transmit buffer is full */
        if (1 == U1STAbits.UTXBF)
        {
            buffering = true;
            buffer_add(ch);
        }
        else
        {
            /* add the character to the UART transmit FIFO */
            U1TXREG = ch;
        }
    }

    /* if there are characters in the software buffer, then we need to enable transmit interrupts */
    if (buffering)
    {
        IEC3bits.U1TXIE = 1;
    }
}
#endif
/* End of function dputc                                                      */

/**************************************************************************** */
/* Function Name: dputs                                                       */
/*                output a null terminated string to the debug console        */
/* @param[in] string : the string to output                                   */
/* @retval None                                                               */
/* ************************************************************************** */
void dputs(const char *string)
{
    #ifndef ENABLE_DEBUG
    return;
    #endif    

    #ifdef LOG_TIME
    DebugTime current_run_time;
    uint16_t current_milliseconds;
    char time_buffer[20];               /* HH:MM:SS mmm */

    /* grab a snapshot of the current time */
    INTERRUPT_GlobalDisable();
    current_milliseconds = milliseconds;
    current_run_time.hour = run_time.hour;
    current_run_time.minute = run_time.minute;
    current_run_time.second = run_time.second;
    INTERRUPT_GlobalEnable();

    /* output the time to the console */
    sprintf(time_buffer, "%02d:%02d:%02d %03d ", current_run_time.hour, current_run_time.minute, current_run_time.second, current_milliseconds);
    send_string(time_buffer);
    #endif

    send_string(string);
}
/* End of function dputs                                                      */

/**************************************************************************** */
/* Function Name: dputs_colour                                                */
/*                output a null terminated string to the debug console        */
/*                having replaced colour tokens with terminal escape codes    */
/* @param[in] string : the string to output                                   */
/* @retval None                                                               */
/* ************************************************************************** */
void dputs_colour(const char *string)
{
    static char colour_string[256];

    #ifndef ENABLE_DEBUG
    return;
    #endif
    
    #ifdef LOG_TIME
    DebugTime current_run_time;
    uint16_t current_milliseconds;
    char time_buffer[20];               /* HH:MM:SS mmm */

    /* grab a snapshot of the current time */
    INTERRUPT_GlobalDisable();
    current_milliseconds = milliseconds;
    current_run_time.hour = run_time.hour;
    current_run_time.minute = run_time.minute;
    current_run_time.second = run_time.second;
    INTERRUPT_GlobalEnable();

    /* output the time to the console */
    sprintf(time_buffer, "%02d:%02d:%02d %03d ", current_run_time.hour, current_run_time.minute, current_run_time.second, current_milliseconds);
    send_string(time_buffer);
    #endif

    /* replace colour tokens with terminal colour escape codes */
    detokenise(string, colour_string);

    send_string(colour_string);
}
/* End of function dputs_colour                                               */

/**************************************************************************** */
/* Function Name: logging_start_timer                                         */
/*                Start a timer to be used for logging time taken             */
/* @retval None                                                               */
/* ************************************************************************** */
void logging_start_timer(void)
{
    /* record the start time */
    INTERRUPT_GlobalDisable();
    start_milliseconds = run_time.hour * 60 * 60;
    start_milliseconds += run_time.minute * 60;
    start_milliseconds += run_time.second;
    start_milliseconds *= 1000;
    start_milliseconds += milliseconds;
    INTERRUPT_GlobalEnable();
}
/* End of function logging_start_timer                                        */

/**************************************************************************** */
/* Function Name: get_elapsed_time                                            */
/*                Gets the time elapsed since logging_start_timer() was       */
/*                called                                                      */
/* @param[out] elapsed_time : pointer to structure to return time             */
/* @param[out] elapsed_milliseconds : pointer to variable to return ms        */
/* @retval None                                                               */
/* ************************************************************************** */
void get_elapsed_time(DebugTime *elapsed_time, uint16_t *elapsed_milliseconds)
{
    uint32_t end_milliseconds;
    uint32_t milliseconds_taken;

    /* record the end time */
    INTERRUPT_GlobalDisable();
    end_milliseconds = run_time.hour * 60 * 60;
    end_milliseconds += run_time.minute * 60;
    end_milliseconds += run_time.second;
    end_milliseconds *= 1000;
    end_milliseconds += milliseconds;
    INTERRUPT_GlobalEnable();

    /* calculate the time taken */
    milliseconds_taken = end_milliseconds - start_milliseconds;

    /* split it into human readable time fields */
    *elapsed_milliseconds = milliseconds_taken % 1000;
    milliseconds_taken -= *elapsed_milliseconds;

    milliseconds_taken /= 1000;
    elapsed_time->second = milliseconds_taken % 60;
    milliseconds_taken -= elapsed_time->second;

    milliseconds_taken /= 60;
    elapsed_time->minute = milliseconds_taken % 60;
    milliseconds_taken -= elapsed_time->minute;

    milliseconds_taken /= 60;
    elapsed_time->hour = milliseconds_taken;    
}
/* End of function get_elapsed_time                                           */

/**************************************************************************** */
/* Function Name: log_elapsed_time                                            */
/*                Logs the time elapsed since logging_start_timer() was       */
/*                called                                                      */
/* @param[in] string : string to print before the elapsed time                */
/* @retval None                                                               */
/* ************************************************************************** */
void log_elapsed_time(const char *string)
{
    DebugTime elapsed_time;
    uint16_t elapsed_milliseconds;
    char time_buffer[20];               /* HH:MM:SS mmm */

    get_elapsed_time(&elapsed_time, &elapsed_milliseconds);
    dputs_colour(string);
    sprintf(time_buffer, "%02d:%02d:%02d %03d\x1B[97m\r\n", elapsed_time.hour, elapsed_time.minute, elapsed_time.second, elapsed_milliseconds);
    send_string(time_buffer);
}
/* ************************************************************************** */
/** 
 * @brief            display debug actions / logging to be performed during startup
 *
 * @note             Called by int main(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
/* End of function log_elapsed_time                                           */
/* debug actions / logging to be performed during startup */
void initialisation_debug(void)
{
    dputs_colour("[GREEN]main() starting[WHITE]\r\n");
}
/* ************************************************************************** */
/** 
 * @brief            perform any processing of debugging code
 *
 * @note             Called by int main(void)
 * 
 * @param[in/out]    bool *wake_up
 * 
 * @return           None.
 */
/* ************************************************************************** */
void debug_task(bool *wake_up)
{
    static uint32_t counter = 0;
    static uint8_t led = 0;    

    if (*wake_up)
    {
        *wake_up = false;
        dputs_colour("[MAGENTA]Wake up call![WHITE]\r\n");
    }

    counter++;

    if (counter > 100000)
    {
        counter = 0;

        led++;

        if ((led & 1) > 0)
        {
//            DBG_LEDB_SetLow();
        }
        else
        {
 //           DBG_LEDB_SetHigh();
        }
        
        if ((led & 2) > 0)
        {
            DBG_LEDG_SetLow();
        }
        else
        {
            DBG_LEDG_SetHigh();
        }
        
        if ((led & 4) > 0)
        {
            //DBG_LEDR_SetLow();
        }
        else
        {
            //DBG_LEDR_SetHigh();
        }

        dputs_colour("[GREEN]Hello[WHITE]\r\n");
    }
}



