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
#include "definitions.h"
#include "message_exchange.h"
#include "dspic_comms.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
 
#define ENABLE_DEBUG
#define DEBUG_BAUD                                  115200u 
#ifdef ENABLE_DEBUG
//#define BLOCKING_DEBUG                                            // #define to make the debug code block until the message has been sent
#define DEBUG_BUFFER_LENGTH                         (128 * 1024)    // the size of the debug buffer
#define LOG_TIME                                                    // #define this to have time logged on every line  
#else
#define DEBUG_BUFFER_LENGTH                         128             // the size of the debug buffer
#endif

#define MINIMUM_TOKEN_LENGTH                        5               // minimum length of a colour token
#define MAXIMUM_TOKEN_LENGTH                        10              // maximum length of a colour token

#define DEBUG_IN_SYNC1  ('D')                                       //Incoming debug message pack header sync 1 value
#define DEBUG_IN_SYNC2  ('b')                                       //Incoming debug message pack header sync 2 value


#define DEBUG_IN_PACK   (DEBUG_IN_DSIZE + 3)

#ifdef ENABLE_DEBUG
/* buffer used for console output */
static char transmit_buffer[DEBUG_BUFFER_LENGTH];
#else
static char transmit_buffer[0];
#endif
static uint32_t input_index = 0;
static uint32_t output_index = 0;
static DebugTime run_time;
static uint16_t milliseconds;

static uint32_t start_milliseconds;



void debug_millisecond_timer_interrupt(uint32_t status, uintptr_t context);
static const char *get_colour(const char *string, bool *found);
static void detokenise(const char * input, char *output);
static bool buffer_add(char ch);
static bool buffer_empty(void);
static bool buffer_full(void);
static void send_string(const char *string);

#ifdef BLOCKING_DEBUG
static void blocking_dputc(char ch);
#endif

typedef enum{
    
    BB_UNREADY =0,
    BB_READY = 1,
    BB_LOCKED =2
            
    
}bb_state_t;


typedef struct {

    uint16_t        size;
    uint8_t *       buff_ptr;
    volatile uint16_t   fill_count;
    volatile bb_state_t   state;
    
    
} ByteBuffer_t;

static ByteBuffer_t debug_in_buffers[2];



#define DEBUG_IN_BUFF_LENGTH (((DEBUG_BAUD/(10*1000))*2)+1) // more than double required size for 1ms processing tick
static uint8_t in_buff0[DEBUG_IN_BUFF_LENGTH];
static uint8_t in_buff1[DEBUG_IN_BUFF_LENGTH]; 
static uint16_t debug_coms_chk_sum_fail =0; 

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

void byte_buffer_init(ByteBuffer_t *bb, uint8_t *  buff_arr, uint16_t size){
    
    bb->size = size;
    bb->buff_ptr = buff_arr;
    bb->fill_count = 0; 
    bb->state =BB_READY;

}

bool byte_buffer_add(ByteBuffer_t *bb, uint8_t b){
    
    if(bb->fill_count < bb->size ){
        
        *(bb->buff_ptr + bb->fill_count) = b;
        bb->fill_count++; 
        return true;
    }else{
        
        return false; 
    }
}

void byte_buffer_clear(ByteBuffer_t *bb){
    
    bb->fill_count = 0; 
}


void debug_in_init(){
    
    byte_buffer_init(&debug_in_buffers[0],in_buff0, DEBUG_IN_BUFF_LENGTH );
    byte_buffer_init(&debug_in_buffers[1],in_buff1, DEBUG_IN_BUFF_LENGTH );
    
        
    IFS3CLR = _IFS3_U1RXIF_MASK;
    
    IEC3SET = _IEC3_U1RXIE_MASK;
}

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
    const char *colour_codes[] = {"[BLACK]", "\x1B[30m", "[RED]", "\x1B[91m", "[GREEN]", "\x1B[92m", "[YELLOW]", "\x1B[93m",
                                  "[BLUE]", "\x1B[94m", "[MAGENTA]", "\x1B[95m", "[CYAN]", "\x1B[96m", "[WHITE]", "\x1B[97m",
                                  "[ORANGE]", "\x1B[38;5;208m", "[PINK]", "\x1B[38;5;212m", "[BROWN]", "\x1B[38;5;94m",
                                  "[PURPLE]", "\x1B[35m"};
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
/* End of function buffer_add                                                 */

/**************************************************************************** */
/* Function Name: buffer_empty                                                */
/*                determine whether or not the debug logging buffer is empty  */
/* @retval true if the buffer is empty                                        */
/* ************************************************************************** */
static bool buffer_empty(void)
{
    return (input_index == output_index);
}
/* End of function buffer_empty                                               */

/**************************************************************************** */
/* Function Name: buffer_full                                                 */
/*                determine whether or not the debug logging buffer is full   */
/* @retval true if the buffer is full                                         */
/* ************************************************************************** */
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
    while (1 == U2STAbits.UTXBF); // wait until previous transmission is complete
    U2TXREG = ch;
}
#endif
/* End of function blocking_dputc                                             */

/**************************************************************************** */
/* Function Name: UART1_TX_InterruptHandler                                   */
/*                UART transmit interrupt handler for the debug logger        */
/* @retval None                                                               */
/* ************************************************************************** */
//void debug_transmit_interrupt_callback(void)
void UART1_TX_InterruptHandler(void)
{
    char ch;

    /* top up the FIFO transmit buffer */
    while ((input_index != output_index) && (0 == U1STAbits.UTXBF))
    {
        /* get the next character to be sent and increment the output pointer */
        ch = transmit_buffer[output_index];
        output_index++;

        if (output_index >= DEBUG_BUFFER_LENGTH)
        {
            output_index = 0;
        }

        /* send the character */
        U1TXREG = ch;
    }

    /* clear the UART2TX Interrupt flag after writing to buffer */
    IFS3CLR = _IFS3_U1TXIF_MASK;

    /* if the buffer is now empty, then there won't be anything further to send */
    if (input_index == output_index)
    {
        /* disable the transmit interrupt */
        IEC3bits.U1TXIE = 0;
    }
}
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

    for (i = 0; NULL != string[i]; i++)
    {
        blocking_dputc(string[i]);
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
#ifndef ENABLE_DEBUG
    return;
#endif
    
    U1MODE = 0;
    U1MODEbits.STSEL = 1;   /* two stop bits - seems to fix an issue when */
                            /* one stop bit is selected */

    /* Enable UART1 Receiver, Transmitter and TX Interrupt selection */
    //U1STASET = (_U1STA_UTXEN_MASK | _U1STA_URXEN_MASK | _U1STA_UTXISEL0_MASK);

    U1STA = 0;
    U1STAbits.UTXISEL = 0;
    U1STAbits.URXISEL = 0;  //interrupt when receive buffer has at least 1 byte
    U1STAbits.UTXEN = 1;

    /* BAUD Rate register Setup */
    U1BRG = 53;                     /* 115,200 Baud */

    /* Disable Interrupts */
    IEC3CLR = _IEC3_U1EIE_MASK;
    IEC3CLR = _IEC3_U1RXIE_MASK;
    IEC3CLR = _IEC3_U1TXIE_MASK;
    
    IFS3CLR = _IFS3_U1EIF_MASK;
    IFS3CLR = _IFS3_U1RXIF_MASK;
    IFS3CLR = _IFS3_U1TXIF_MASK;

     /* Turn ON UART1 */
    U1MODESET = _U1MODE_ON_MASK;

    milliseconds = 0;
    run_time.hour = 0;
    run_time.minute = 0;
    run_time.second = 0;
}
/* End of function debug_initialise                                           */

/**************************************************************************** */
/* Function Name: debug_millisecond_timer_interrupt                           */
/*                This needs to be called every ms to increment the timer     */
/* @retval None                                                               */
/* ************************************************************************** */
//void (*TMR_CALLBACK)(uint32_t status, uintptr_t context);
void debug_millisecond_timer_interrupt(uint32_t status, uintptr_t context)
{
    (void) status;
    (void) context;

    milliseconds++;
    //dspic_transmit_timer();
    if (milliseconds >= 1000)
    {
        milliseconds = 0;
        debug_increment_time(&run_time);
    }

}
/* End of debug_millisecond_timer_interrupt                                   */

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
    bool interrupt_state;
    char time_buffer[20];               /* HH:MM:SS mmm */

    /* grab a snapshot of the current time */
    interrupt_state = SYS_INT_Disable();
    current_milliseconds = milliseconds;
    current_run_time.hour = run_time.hour;
    current_run_time.minute = run_time.minute;
    current_run_time.second = run_time.second;
    SYS_INT_Restore(interrupt_state);

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
    #ifndef ENABLE_DEBUG
    return;
    #endif    
    
    static char colour_string[256];
    
    #ifdef LOG_TIME
    DebugTime current_run_time;
    uint16_t current_milliseconds;
    bool interrupt_state;
    char time_buffer[20];               /* HH:MM:SS mmm */

    /* grab a snapshot of the current time */
    interrupt_state = SYS_INT_Disable();
    current_milliseconds = milliseconds;
    current_run_time.hour = run_time.hour;
    current_run_time.minute = run_time.minute;
    current_run_time.second = run_time.second;
    SYS_INT_Restore(interrupt_state);

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
    bool interrupt_state;

    /* record the start time */
    interrupt_state = SYS_INT_Disable();
    start_milliseconds = run_time.hour * 60 * 60;
    start_milliseconds += run_time.minute * 60;
    start_milliseconds += run_time.second;
    start_milliseconds *= 1000;
    start_milliseconds += milliseconds;
    SYS_INT_Restore(interrupt_state);
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
    bool interrupt_state;
    uint32_t end_milliseconds;
    uint32_t milliseconds_taken;

    /* record the end time */
    interrupt_state = SYS_INT_Disable();
    end_milliseconds = run_time.hour * 60 * 60;
    end_milliseconds += run_time.minute * 60;
    end_milliseconds += run_time.second;
    end_milliseconds *= 1000;
    end_milliseconds += milliseconds;
    SYS_INT_Restore(interrupt_state);

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
/* End of function log_elapsed_time                                           */

/**************************************************************************** */
/* Function Name: debug_busy                                                  */
/*                Return whether or not the debug logger is transmitting      */
/* @retval true if there is a transmission in progress                        */
/* ************************************************************************** */
bool debug_busy(void)
{
#ifndef ENABLE_DEBUG
    return (false);
#else
    bool busy;
    uint8_t tx_interrupts_enabled;

    tx_interrupts_enabled = IEC4bits.U2TXIE;

    /* disable interrupts */
    IEC4bits.U2TXIE = 0;

    busy = !buffer_empty() || (U1STAbits.TRMT == 0);
    //busy = !buffer_empty();

    /* restore transmit interrupts */
    IEC4bits.U2TXIE = tx_interrupts_enabled;

    return (busy);
#endif
}
/* End of function debug_busy                                                 */

static volatile bool debug_in_buffer_overrun = false; 

void UART1_RX_InterruptHandler(void){
    
    bool enqueued =false; 
    
    while(U1STA & _U1STA_URXDA_MASK){
        
        uint8_t in_byte = U1RXREG; 
        
        
        if(debug_in_buffers[0].state == BB_LOCKED){
            
            enqueued = byte_buffer_add(&debug_in_buffers[1], in_byte); 
            
        }else if(debug_in_buffers[1].state == BB_LOCKED){
            
            enqueued = byte_buffer_add(&debug_in_buffers[0], in_byte);
            
        }else if(debug_in_buffers[0].fill_count > 0 ){
            
            enqueued = byte_buffer_add(&debug_in_buffers[0], in_byte);
            
        }else if(debug_in_buffers[1].fill_count > 0 ){
            
            enqueued = byte_buffer_add(&debug_in_buffers[1], in_byte);
            
        } else{
            
            enqueued = byte_buffer_add(&debug_in_buffers[0], in_byte);
        }
        
        if(enqueued == false){
            
            debug_in_buffer_overrun = true; 
        }

    }
    
    IFS3CLR = _IFS3_U1RXIF_MASK;
}

uint8_t check_sum(uint8_t buffer[], uint16_t offset, uint16_t  len){
    uint8_t sum = 0;
    
    uint16_t i;
    for (i=0; i<len; i++){
        sum += buffer[offset+i];
    }
    return ~sum;
}

void process_byte_buffer(ByteBuffer_t* bb){
    
    
    bb->state =BB_LOCKED;
    static uint16_t proc_state = 0;
    static uint16_t data_count =0; 
    static uint8_t pack_data[DEBUG_IN_DSIZE]; 
    
    uint16_t i = 0;
    uint8_t chk_sum =0; 
    
    for (i = 0; i < bb->fill_count; i++){
        
        
        uint8_t in_byte = bb->buff_ptr[i]; 
        
        switch(proc_state){
            
            case 0:
                
                if(in_byte == DEBUG_IN_SYNC1){
                    
                    proc_state++; 
                }
                
                break; 
            case 1:
                if(in_byte == DEBUG_IN_SYNC2){
                    data_count = 0; 
                    proc_state++; 
                }else{
                    
                    proc_state = 0; 
                }
                break; 
                
            case 2:
                
                pack_data[data_count] = in_byte; 
                
                data_count++; 
                 
                if(data_count ==DEBUG_IN_DSIZE) {
                    
                    proc_state++;
                }
                
                 break;
            case 3:
                
                chk_sum =  check_sum(pack_data, 0,DEBUG_IN_DSIZE); 
                
                if(chk_sum == in_byte){
                    
                    debug_inpack_process(pack_data);
                    
                }else{
                    if(debug_coms_chk_sum_fail < UINT16_MAX){
                        debug_coms_chk_sum_fail++; 
                    }
                
                }
                proc_state = 0; 
                break; 

            
        }
    }
    
    byte_buffer_clear(bb);         
    bb->state = BB_READY; 
}

void debug_receive_process(){

    process_byte_buffer(&debug_in_buffers[0]);
    process_byte_buffer(&debug_in_buffers[1]);
    
}