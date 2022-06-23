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

#include "debug.h"
#include "definitions.h"
#include "date_and_time.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define ENABLE_DEBUG                                               

#ifdef ENABLE_DEBUG
#define DEBUG_BUFFER_LENGTH                         (128 * 1024)        // the size of the debug buffer
//#define BLOCKING_DEBUG                                                // #define to make the debug code block until the message has been sent
#define LOG_TIME                                                        // #define this to have time logged on every line
#else
#define DEBUG_BUFFER_LENGTH                         128                 // the size of the debug buffer
#endif

#define MINIMUM_TOKEN_LENGTH                        5                   // minimum length of a colour token
#define MAXIMUM_TOKEN_LENGTH                        10                  // maximum length of a colour token

/* buffer used for console output */
static char transmit_buffer[DEBUG_BUFFER_LENGTH];
static uint32_t input_index = 0;
static uint32_t output_index = 0;
static RTCCFORM run_time;
static uint16_t milliseconds;

static uint32_t start_milliseconds;
static uint32_t core_timer_start;

static const char *get_colour(const char *string, bool *found);
static void detokenise(const char * input, char *output);
static bool buffer_add(char ch);
static bool buffer_empty(void);
static bool buffer_full(void);
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
    while (1 == U6STAbits.UTXBF); // wait until previous transmission is complete
    U6TXREG = ch;
}
#endif
/* End of function blocking_dputc                                             */

/**************************************************************************** */
/* Function Name: UART6_TX_InterruptHandler                                   */
/*                UART transmit interrupt handler for the debug logger        */
/* @retval None                                                               */
/* ************************************************************************** */
//void debug_transmit_interrupt_callback(void)
void UART6_TX_InterruptHandler(void)
{
    char ch;

    /* top up the FIFO transmit buffer */
    while ((input_index != output_index) && (0 == U6STAbits.UTXBF))
    {
        /* get the next character to be sent and increment the output pointer */
        ch = transmit_buffer[output_index];
        output_index++;

        if (output_index >= DEBUG_BUFFER_LENGTH)
        {
            output_index = 0;
        }

        /* send the character */
        U6TXREG = ch;
    }

    /* clear the UART6TX Interrupt flag after writing to buffer */
    IFS5CLR = _IFS5_U6TXIF_MASK;

    /* if the buffer is now empty, then there won't be anything further to send */
    if (input_index == output_index)
    {
        /* disable the transmit interrupt */
        IEC5bits.U6TXIE = 0;
    }
}
/* End of function UART6_TX_InterruptHandler                                  */

/**************************************************************************** */
/* Function Name: send_string                                                 */
/*                output a null terminated string to the debug console        */
/* @param[in] string : the string to output                                   */
/* @retval None                                                               */
/* ************************************************************************** */
#ifdef BLOCKING_DEBUG
void send_string(const char *string)
{
    uint16_t i;

    for (i = 0; NULL != string[i]; i++)
    {
        blocking_dputc(string[i]);
    }
}
#else
void send_string(const char *string)
{
    uint16_t i;
    bool buffering;

    /* disable interrupts */
    IEC5bits.U6TXIE = 0;

    /* check for characters in the software buffer */
    buffering = !buffer_empty();

    /* add the string to the TX FIFO and/or software buffer */    
    for (i = 0; NULL != string[i]; i++)
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
            if (1 == U6STAbits.UTXBF)
            {
                buffering = true;
                buffer_add(string[i]);
            }
            else
            {
                /* add the character to the UART transmit FIFO */
                U6TXREG = string[i];
            }
        }
    }

    /* if there are characters in the software buffer, then we need to enable transmit interrupts */
    if (buffering)
    {
        IEC5bits.U6TXIE = 1;
    }
}
#endif
/* End of function send_string                                                */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/**************************************************************************** */
/* Function Name: debug_initialise                                            */
/*                Initialise the debug logging module                         */
/* @retval None                                                               */
/* ************************************************************************** */
void debug_initialise(void)
{
    U6MODE = 0;
    U6MODEbits.STSEL = 1;   /* two stop bits - seems to fix an issue when */
                            /* one stop bit is selected */

    /* Enable UART6 Receiver, Transmitter and TX Interrupt selection */
    //U6STASET = (_U6STA_UTXEN_MASK | _U6STA_URXEN_MASK | _U6STA_UTXISEL0_MASK);

    U6STA = 0;
    U6STAbits.UTXISEL = 0;
    U6STAbits.UTXEN = 1;

    /* BAUD Rate register Setup */
    //U6BRG = 650;                  /* 19,200 Baud */
    U6BRG = 53;                     /* 115,200 Baud */

    /* Disable Interrupts */
    IEC5CLR = _IEC5_U6EIE_MASK;
    IEC5CLR = _IEC5_U6RXIE_MASK;
    IEC5CLR = _IEC5_U6TXIE_MASK;

     /* Turn ON UART6 */
    U6MODESET = _U6MODE_ON_MASK;

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
void debug_millisecond_timer_interrupt()
{
    milliseconds++;

    if (milliseconds >= 1000)
    {
        milliseconds = 0;
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
    #ifdef DISABLE_DEBUG
    return;
    #endif    

    blocking_dputc(ch);
}
#else
void dputc(char ch)
{
    #ifndef ENABLE_DEBUG
    return;
    #endif    
    
    bool buffering;

    /* disable interrupts */
    IEC5bits.U6TXIE = 0;

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
        if (1 == U6STAbits.UTXBF)
        {
            buffering = true;
            buffer_add(ch);
        }
        else
        {
            /* add the character to the UART transmit FIFO */
            U6TXREG = ch;
        }
    }

    /* if there are characters in the software buffer, then we need to enable transmit interrupts */
    if (buffering)
    {
        IEC5bits.U6TXIE = 1;
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
    RTCCFORM current_run_time;
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
    RTCCFORM current_run_time;
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

    core_timer_start = CORETIMER_CounterGet();
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
void get_elapsed_time(RTCCFORM *elapsed_time, uint32_t *elapsed_milliseconds)
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

    //dprintf_colour("[start_milliseconds = %d\r\n", start_milliseconds);
    //dprintf_colour("end_milliseconds = %d\r\n", end_milliseconds);

    /* calculate the time taken */
    milliseconds_taken = end_milliseconds - start_milliseconds;

    //dprintf_colour("milliseconds_taken = %d]\r\n", milliseconds_taken);    

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
uint32_t log_elapsed_time(const char *string)
{
    RTCCFORM elapsed_time;
    uint32_t elapsed_milliseconds;
    char time_buffer[20];               /* HH:MM:SS mmm */

    get_elapsed_time(&elapsed_time, &elapsed_milliseconds);
    dputs_colour(string);
    sprintf(time_buffer, "%02d:%02d:%02d %03d\x1B[97m\r\n", elapsed_time.hour, elapsed_time.minute, elapsed_time.second, elapsed_milliseconds);
    send_string(time_buffer);

    uint32_t core_timer_end;
    uint32_t core_time;

    core_timer_end = CORETIMER_CounterGet();
    core_time = core_timer_end - core_timer_start;
    
    dputs_colour(string);
    sprintf(time_buffer, "%d.%02dus\x1B[97m\r\n", core_time / 100, core_time % 100);
    send_string(time_buffer);

    return (core_time);
}
/* End of function log_elapsed_time                                           */

/**************************************************************************** */
/* Function Name: debug_busy                                                  */
/*                Return whether or not the debug logger is transmitting      */
/* @retval true if there is a transmission in progress                        */
/* ************************************************************************** */
bool debug_busy(void)
{
    bool busy;
    uint8_t tx_interrupts_enabled;

    tx_interrupts_enabled = IEC5bits.U6TXIE;

    /* disable interrupts */
    IEC5bits.U6TXIE = 0;

    busy = !buffer_empty();

    /* restore transmit interrupts */
    IEC5bits.U6TXIE = tx_interrupts_enabled;

    return (busy);
}
/* End of function debug_busy                                                 */
