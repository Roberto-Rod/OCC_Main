/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    pic_comms.c

  @Summary
    Message communications between PICs.

  @Description
    Message communications between PICs.
 */
/* ************************************************************************** */

// This needs:
// DMA to minimise CPU use
// Message ACK or NAK for reliability
// Message index so that we can spot missed messages
// CRC for checking message data

// Message:
// Header 
//   Message start sequence
//   Message index
//   Message length
// Message body
// CRC

// An acknowledgement message will just contain 3 characters "ACK"
// The message index will be for the message that is being acknowledged

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include <string.h>

#include "definitions.h"
#include "message_exchange.h"

//#define DEBUG_COMMS

//#define DMA_TRANSMIT

#define TX_BUFFER_LENGTH            (64 * 1024)         // circular transmit buffer
#define RX_BUFFER_LENGTH            1024                // circular receive buffer
#define MAX_MESSAGE_LENGTH          128                 // maximum length of message body

#define MESSAGE_START_FLAG          0x1857fc0a          // unique pattern to flag the start of a message

#define MAX_TRANSMIT_ATTEMPTS       5                   // maximum tries to send a message
#define MAX_TX_ACK_MESSAGE_LENGTH   200                 // maximum length of message that requires acknowledgement
#define ACK_MESSAGE_LENGTH          3                   // length of ACK message
#define ACK_MESSAGE                 "ACK"               // ACK message body
#define ACK_TIMEOUT_DELAY_MS        100                 // resend message delay after ACK not received


typedef struct
{
    uint32_t message_start_flag;                        // message start flag
    uint32_t message_index;                             // incrementing message index
    uint32_t message_length;                            // length of the message body
    uint32_t message_crc;                               // message body CRC
    bool ack_required;                                  // true if this message needs to be acknowledged
    uint16_t header_checksum;                           // simple checksum for this header
} message_header;

typedef enum
{
    RX_FIND_START,
    RX_GET_HEADER,
    RX_GET_MESSAGE,
} RX_STATE;

typedef enum
{
    TX_IDLE,
    WAIT_FOR_ACK
} TX_STATE;

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

static char transmit_buffer[TX_BUFFER_LENGTH];
static uint32_t tx_input_index = 0;
static uint32_t tx_output_index = 0;
static uint32_t transmit_message_index = 0;

/* message retrying */
static uint8_t transmit_message_copy[MAX_TX_ACK_MESSAGE_LENGTH];
static uint32_t transmit_message_copy_length;
static uint32_t transmit_message_copy_index;
static TX_STATE tx_state;
static uint8_t transmit_attempt;

static char receive_buffer[RX_BUFFER_LENGTH];
static uint32_t rx_input_index = 0;
static uint32_t rx_output_index = 0;

static uint32_t rx_error_count = 0;
static uint32_t rx_message_crc_failure = 0;

static message_header rx_message_header;
static RX_STATE rx_state;
static uint8_t received_message[MAX_MESSAGE_LENGTH];
static uint32_t last_received_message_index = 0;

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

static bool tx_buffer_add(char ch);
static bool tx_buffer_empty(void);
static bool tx_buffer_full(void);

static bool rx_buffer_add(char ch);
static bool rx_buffer_empty(void);
static bool rx_buffer_full(void);
static uint32_t rx_buffer_data_length(void);

static uint32_t send_bytes(const uint8_t *string, uint32_t length);

void process_received_message(uint8_t *data, uint32_t length);
static void send_ack_message(uint32_t message_index);
static void resend_message(void);
static void message_acknowledged(uint32_t message_index);

static int32_t tx_timer = -1;
static void start_timeout(void);
static void cancel_timeout(void);
static int32_t get_timer_value(void);

/**************************************************************************** */
/* Function Name: crc32                                                       */
/*                CRC32 (Ethernet, ZIP, etc) polynomial in reversed bit order */
/* @param[in] uint32_t crc : crc value so far (start from 0)                  */
/* @param[in] const uint8_t *data : data to calculate CRC for                 */
/* @param[in] uint32_t length : length of data                                */
/* @retval CRC                                                                */
/* ************************************************************************** */
static uint32_t crc32(uint32_t crc, const uint8_t *data, uint32_t length)
{
    uint8_t i;
    const uint32_t POLY = 0xedb88320;

    crc = ~crc;
    while (length > 0)
    {
        crc ^= *data;
        data++;

        for (i = 0; i < 8; i++)
        {
            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        }

        length--;
    }

    return (~crc);
}
/* End of function crc32                                                      */

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/**************************************************************************** */
/* Function Name: pic_communications_init                                     */
/*                Initialise the PIC comms UARTS and code                     */
/* @retval None                                                               */
/* ************************************************************************** */
void pic_communications_init(void)
{
    /* initialise UART3 for transmit and receive */

    /* set up UxMODE bits */
    /* STSEL  = 1*/
    /* PDSEL = 0 */
    /* BRGH = 0 */
    /* RXINV = 0 */
    /* ABAUD = 0 */
    /* LPBACK = 0 */
    /* WAKE = 1 */
    /* SIDL = 0 */
    /* RUNOVF = 0 */
    /* CLKSEL = 0 */
    /* SLPEN = 0 */
    U3MODE = 0x0289;    // U3MODE = 0x1;

    /* enable receiver, transmitter and TX interrupt selection */
    U3STASET = (_U3STA_UTXEN_MASK | _U3STA_UTXISEL0_MASK | _U3STA_URXEN_MASK );

    /* Baud rate register setup */
    U3BRG = 2;         // 53 is 115,200

    /* disable interrupts */
    IEC4CLR = _IEC4_U3EIE_MASK;
    IEC4CLR = _IEC4_U3RXIE_MASK;
    IEC4CLR = _IEC4_U3TXIE_MASK;

    /* initialise transmit buffer */
    tx_input_index = 0;
    tx_output_index = 0;

    /* initialise receive buffer */
    rx_input_index = 0;
    rx_output_index = 0;
    rx_error_count = 0;

    /* enable receive interrupts */
    IEC4SET = _IEC4_U3RXIE_MASK;

    /* enable UART3_FAULT Interrupt */
    IEC4SET = _IEC4_U3EIE_MASK;

    transmit_message_index = 0;
    rx_message_crc_failure = 0;
    rx_state = RX_FIND_START;

    tx_state = TX_IDLE;

    /* turn on UART3 */
    U3MODESET = _U3MODE_ON_MASK;
}
/* End of function pic_communications_init                                    */

/**************************************************************************** */
/* Function Name: UART3_TX_InterruptHandler                                   */
/*                UART transmit interrupt handler for the PIC communications  */
/* @retval None                                                               */
/* ************************************************************************** */
void UART3_TX_InterruptHandler(void)
{
    char ch;

    /* top up the FIFO transmit buffer */
    while ((tx_input_index != tx_output_index) && (0 == U3STAbits.UTXBF))
    {
        /* get the next character to be sent and increment the output pointer */
        ch = transmit_buffer[tx_output_index];
        tx_output_index++;

        if (tx_output_index >= TX_BUFFER_LENGTH)
        {
            tx_output_index = 0;
        }

        /* send the character */
        U3TXREG = ch;
    }

    /* clear the UART3TX interrupt flag after writing to buffer */
    IFS4CLR = _IFS4_U3TXIF_MASK;

    /* if the buffer is now empty, then there won't be anything further to send */
    if (tx_input_index == tx_output_index)
    {
        /* disable the transmit interrupt */
        IEC4bits.U3TXIE = 0;
    }
}
/* End of function UART3_TX_InterruptHandler                                  */

/**************************************************************************** */
/* Function Name: tx_buffer_add                                               */
/*                add a character to the transmit buffer                      */
/* @param[in] char ch : the character to add to the buffer                    */
/* @retval true if the character was added, false if the buffer is full       */
/* ************************************************************************** */
static bool tx_buffer_add(char ch)
{
    if (tx_buffer_full())
    {
        return (false);
    }

    transmit_buffer[tx_input_index] = ch;
    tx_input_index++;

    if (tx_input_index >= TX_BUFFER_LENGTH)
    {
        tx_input_index = 0;
    }

    return (true);
}
/* End of function tx_buffer_add                                              */

/**************************************************************************** */
/* Function Name: tx_buffer_empty                                             */
/*                determine whether or not the transmit buffer is empty       */
/* @retval true if the buffer is empty                                        */
/* ************************************************************************** */
static bool tx_buffer_empty(void)
{
    return (tx_input_index == tx_output_index);
}
/* End of function tx_buffer_empty                                            */

/**************************************************************************** */
/* Function Name: tx_buffer_full                                              */
/*                determine whether or not the transmit buffer is full        */
/* @retval true if the buffer is full                                         */
/* ************************************************************************** */
static bool tx_buffer_full(void)
{
    uint32_t next_input_index;

    next_input_index = tx_input_index + 1;

    if (next_input_index >= TX_BUFFER_LENGTH)
    {
        next_input_index = 0;
    }

    return (next_input_index == tx_output_index);
}
/* End of function tx_buffer_full                                             */

/**************************************************************************** */
/* Function Name: tx_buffer_free_space                                        */
/*                returns the number of bytes free in the transmit buffer     */
/* @retval byte in the buffer                                                 */
/* ************************************************************************** */
static uint32_t tx_buffer_free_space(void)
{
    uint32_t bytes;

    /* disable transmit interrupts */
    IEC4bits.U3TXIE = 0;

    /* get the space in the buffer */
    if (tx_input_index >= tx_output_index)
    {
        bytes = TX_BUFFER_LENGTH - (tx_input_index - tx_output_index) - 1;
    }
    else
    {
        bytes = tx_output_index - tx_input_index - 1;
    }

    /* enable transmit interrupts */
    IEC4bits.U3TXIE = 1;

    return (bytes);
}
/* End of function tx_buffer_free_space                                       */

/**************************************************************************** */
/* Function Name: send_bytes                                                  */
/*                send bytes to the other PIC via the UART                    */
/* @param[in] const uint8_t *string : the data to send                        */
/* @param[in] uint32_t length : the length of the data                        */
/* @retval the number of bytes that were sent (or were buffered for tx)       */
/* ************************************************************************** */
static uint32_t send_bytes(const uint8_t *string, uint32_t length)
{
    uint32_t i;
    bool buffering;

    if (0 == length)
    {
        length = strlen((const char *) string);
    }

    /* disable interrupts */
    IEC4bits.U3TXIE = 0;

    /* check for characters in the software buffer */
    buffering = !tx_buffer_empty();

    /* add the string to the TX FIFO and/or software buffer */    
    for (i = 0; i < length; i++)
    {
        if (buffering)
        {
            if (!tx_buffer_add(string[i]))
            {
                /* the software buffer is full */
                break;
            }
        }
        else
        {
            /* if the UART transmit buffer is full */
            if (1 == U3STAbits.UTXBF)
            {
                buffering = true;
                tx_buffer_add(string[i]);
            }
            else
            {
                /* add the character to the UART transmit FIFO */
                U3TXREG = string[i];
            }
        }
    }

    /* if there are characters in the software buffer, then we need to enable transmit interrupts */
    if (buffering)
    {
        IEC4bits.U3TXIE = 1;
    }

    return (i);
}
/* End of function send_bytes                                                 */

/**************************************************************************** */
/* Function Name: sending_data                                                */
/*                determines whether or not the comms channel is sending data */
/* @retval true if still in the process of sending data                       */
/* ************************************************************************** */
bool sending_data()
{
    bool sending;
    uint8_t tx_interrupts_enabled;

    tx_interrupts_enabled = IEC4bits.U3TXIE;

    /* disable interrupts */
    IEC4bits.U3TXIE = 0;

    /* check for characters in the software buffer */
    sending = !tx_buffer_empty();

    /* check to see if there is a transmission in progress */
    if (0 == U3STAbits.TRMT)
    {
        sending = true;
    }

    /* turn interrupts back on if they were previously enabled */
    IEC4bits.U3TXIE = tx_interrupts_enabled;

    return (sending);
}
/* End of function sending_data                                               */

/**************************************************************************** */
/* Function Name: rx_buffer_add                                               */
/*                add a character to the receive buffer                       */
/* @param[in] char ch : the character to add to the buffer                    */
/* @retval true if the character was added, false if the buffer is full       */
/* ************************************************************************** */
static bool rx_buffer_add(char ch)
{
    if (rx_buffer_full())
    {
        return (false);
    }

    receive_buffer[rx_input_index] = ch;
    rx_input_index++;

    if (rx_input_index >= RX_BUFFER_LENGTH)
    {
        rx_input_index = 0;
    }

    return (true);
}
/* End of function rx_buffer_add                                              */

/**************************************************************************** */
/* Function Name: rx_buffer_empty                                             */
/*                determine whether or not the receive buffer is empty        */
/* @retval true if the buffer is empty                                        */
/* ************************************************************************** */
static bool rx_buffer_empty(void)
{
    return (rx_input_index == rx_output_index);
}
/* End of function rx_buffer_empty                                            */

/**************************************************************************** */
/* Function Name: rx_buffer_full                                              */
/*                determine whether or not the receive buffer is full         */
/* @retval true if the buffer is full                                         */
/* ************************************************************************** */
static bool rx_buffer_full(void)
{
    uint32_t next_input_index;

    next_input_index = rx_input_index + 1;

    if (next_input_index >= RX_BUFFER_LENGTH)
    {
        next_input_index = 0;
    }

    return (next_input_index == rx_output_index);
}
/* End of function rx_buffer_full                                             */

/**************************************************************************** */
/* Function Name: rx_buffer_data_length                                       */
/*                returns the number of bytes in the receive buffer           */
/* @retval bytes in the buffer                                                */
/* ************************************************************************** */
static uint32_t rx_buffer_data_length(void)
{
    uint32_t bytes;

    /* disable receive interrupts */
    IEC4CLR = _IEC4_U3RXIE_MASK;

    if (rx_input_index >= rx_output_index)
    {
        bytes = rx_input_index - rx_output_index;
    }
    else
    {
        bytes = RX_BUFFER_LENGTH - (rx_output_index - rx_input_index);
    }

    /* enable receive interrupts */
    IEC4SET = _IEC4_U3RXIE_MASK;

    return (bytes);
}
/* End of function rx_buffer_data_length                                      */

/**************************************************************************** */
/* Function Name: get_received_data                                           */
/*                get received data into the supplied buffer up to max_length */
/* @param[in] uint8_t *buffer : the buffer to receive data                    */
/* @param[in] uint32_t max_length : the maximum number of bytes to copy       */
/* @retval the number of bytes copied to                                      */
/* ************************************************************************** */
static uint32_t get_received_data(uint8_t *buffer, uint32_t max_length)
{
    uint32_t i;

    /* disable receive interrupts */
    IEC4CLR = _IEC4_U3RXIE_MASK;

    for (i = 0; i < max_length; i++)
    {
        if (rx_buffer_empty())
        {
            /* enable receive interrupts */
            IEC4SET = _IEC4_U3RXIE_MASK;
            return (i);
        }

        buffer[i] = receive_buffer[rx_output_index];
        rx_output_index++;

        if (rx_output_index >= RX_BUFFER_LENGTH)
        {
            rx_output_index = 0;
        }
    }

    /* enable receive interrupts */
    IEC4SET = _IEC4_U3RXIE_MASK;

    return (i);
}
/* End of function get_received_data                                          */

/**************************************************************************** */
/* Function Name: UART3_RX_InterruptHandler                                   */
/*                UART3 receive interrupt handler                             */
/* ************************************************************************** */
void UART3_RX_InterruptHandler(void)
{
    uint8_t ch;

    /* retrieve all the received data */
    /* data is discarded once the receive buffer is full */
    while (_U3STA_URXDA_MASK == (U3STA & _U3STA_URXDA_MASK))
    {
        ch = (uint8_t) U3RXREG;

        if (!rx_buffer_full())
        {
            rx_buffer_add(ch);
        }
    }

    /* clear UART3 RX interrupt flag after reading data buffer */
    IFS4CLR = _IFS4_U3RXIF_MASK;
}
/* End of function UART3_RX_InterruptHandler                                  */

/**************************************************************************** */
/* Function Name: UART3_ErrorClear                                            */
/*                Clear UART3 receive errors                                  */
/* ************************************************************************** */
static void UART3_ErrorClear(void)
{
    /* rxBufferLen = (FIFO level + RX register) */
    uint8_t rxBufferLen = UART_RXFIFO_DEPTH;
    uint8_t dummyData = 0u;
   
    /* if it's an overrun error then clear it to flush FIFO */
    if (U3STA & _U3STA_OERR_MASK)
    {
        U3MODECLR = _U3MODE_ON_MASK;            /* Errata workaround - reset the module on overflow */        
        U3STACLR = _U3STA_OERR_MASK;
        dprintf_colour("[RED]UART3 OERR Error [WHITE]\r\n" );
         /* turn off UART3 */
    }
    
    if (U3STA & _U3STA_PERR_MASK)
    {
        dprintf_colour("[RED]UART3 PERR Error [WHITE]\r\n" );
    }    
    
    /* if it's an overrun error then clear it to flush FIFO */
    if (U3STA & _U3STA_FERR_MASK)
    {
        dprintf_colour("[RED]UART3 PERR Error [WHITE]\r\n" );
    }        
    
    /* read existing error bytes from FIFO to clear parity and framing error flags */
    while (U3STA & (_U3STA_FERR_MASK | _U3STA_PERR_MASK))
    {
        dummyData = (uint8_t) U3RXREG;
        rxBufferLen--;

        /* try to flush error bytes for one full FIFO and exit instead of
         * blocking here if more error bytes are received */
        if (rxBufferLen == 0u)
        {
            break;
        }
    }
    
    dprintf_colour("[RED]UART3 Error Cleared.[WHITE]\r\n" );    

    // ignore the warning
    (void) dummyData;
    
    /* turn on UART3 to release the stall */
    U3MODESET = _U3MODE_ON_MASK;    

    /* clear error interrupt flag */
    IFS4CLR = _IFS4_U3EIF_MASK;

    /* clear up the receive interrupt flag so that RX interrupt is not triggered for error bytes */
    IFS4CLR = _IFS4_U3RXIF_MASK;
}
/* End of function UART3_ErrorClear                                           */

/**************************************************************************** */
/* Function Name: UART3_FAULT_InterruptHandler                                */
/*                UART3 fault interrupt handler                               */
/* ************************************************************************** */
void UART3_FAULT_InterruptHandler(void)
{
    rx_error_count++;    
    
    dprintf_colour("[RED]UART3 RX Error count: %d[WHITE]\r\n", rx_error_count  );    

    UART3_ErrorClear();
}
/* End of function UART3_FAULT_InterruptHandler                               */

/**************************************************************************** */
/* Function Name: calculate_header_checksum                                   */
/*                calculate a checksum for the supplied message header        */
/* @param[in] message_header *header : pointer to the header                  */
/* @retval the checksum for the header                                        */
/* ************************************************************************** */
static uint16_t calculate_header_checksum(message_header *header)
{
    uint16_t checksum;
    uint8_t *ptr;
    uint8_t i;

    checksum = 0;
    ptr = (uint8_t *) header;

    for (i = 0; i < sizeof(message_header) - sizeof(uint16_t); i++)
    {
        checksum += *ptr;
        ptr++;
    }

    return (checksum);
}
/* End of function calculate_header_checksum                                  */

/**************************************************************************** */
/* Function Name: pic_communications_send_message                             */
/*                send a message to the other PIC                             */
/* @param[in] const uint8_t *data : message data                              */
/* @param[in] uint32_t length : message length                                */
/* @param[in] bool acknowledgement_required : true if the message must be     */
/*                 acknowledged                                               */
/* @retval the checksum for the header                                        */
/* ************************************************************************** */
bool pic_communications_send_message(const uint8_t *data, uint32_t length, bool acknowledgement_required)
{
    message_header header;
    uint32_t free_space;

    //dprintf_colour("[BLUE]pic_communications_send_message length %u[WHITE]\r\n", length);

    /* return false if we're waiting for a message to be acknowledged */
    if (WAIT_FOR_ACK == tx_state)
    {
        return (false);
    }

    /* make sure that we have space for the message */
    free_space = tx_buffer_free_space();
    if (free_space < length + sizeof(message_header))
    {
        return (false);
    }

    /* setup the header */
    header.message_start_flag = MESSAGE_START_FLAG;
    header.message_index = transmit_message_index;
    header.message_length = length;
    header.message_crc = crc32(0, data, length);
    header.ack_required = acknowledgement_required;
    header.header_checksum = calculate_header_checksum(&header);

    transmit_message_index++;
    //dprintf_colour("[BLUE]Message index is %u, header checksum is 0x%04x[WHITE]\r\n", transmit_message_index, header.header_checksum);

    /* send the header */
    send_bytes((const uint8_t *) &header, sizeof(message_header));

    /* send the message body */
    send_bytes(data, length);

    //dprintf_colour("[BLUE]pic_communications_send_message sending bytes (%u)[WHITE]\r\n", length);

    /* if acknowledgement is required, we need to hold a copy of the message */
    if (acknowledgement_required && (length <= MAX_TX_ACK_MESSAGE_LENGTH))
    {
        //dputs_colour("[BLUE]pic_communications_send_message acknowledgement_required[WHITE]\r\n");    
        memcpy(transmit_message_copy, data, length);
        transmit_message_copy_length = length;
        transmit_message_copy_index = header.message_index;
        tx_state = WAIT_FOR_ACK;
        transmit_attempt = 1;
        start_timeout();
    }

    return (true);
}
/* End of function pic_communications_send_message                            */

/**************************************************************************** */
/* Function Name: resend_message                                              */
/*                resend the current message                                  */
/* ************************************************************************** */
static void resend_message(void)
{
    message_header header;
    uint32_t free_space;

    #ifdef DEBUG_COMMS 
    dprintf_colour("[MAGENTA]Resending message %u[WHITE]\r\n", transmit_message_copy_index);
    #endif

    /* make sure that we have space for the message */
    free_space = tx_buffer_free_space();
    if (free_space < transmit_message_copy_length + sizeof(message_header))
    {
        return;
    }

    /* setup the header */
    header.message_start_flag = MESSAGE_START_FLAG;
    header.message_index = transmit_message_copy_index;
    header.message_length = transmit_message_copy_length;
    header.message_crc = crc32(0, transmit_message_copy, transmit_message_copy_length);
    header.ack_required = true;
    header.header_checksum = calculate_header_checksum(&header);

    /* send the header */
    send_bytes((const uint8_t *) &header, sizeof(message_header));

    /* send the message body */
    send_bytes(transmit_message_copy, transmit_message_copy_length);

    start_timeout();
}
/* End of function pic_communications_resend_message                          */

/**************************************************************************** */
/* Function Name: pic_comms_task                                              */
/*                PIC communications task that's called in the main idle loop */
/* ************************************************************************** */
bool pic_comms_task(void)
{
    static uint32_t message_length;
    uint32_t bytes_received;
    uint8_t byte;
    uint32_t crc;

    switch (rx_state)
    {
        /* discard data until we find a message start flag */
        case RX_FIND_START:
        {
            bytes_received = get_received_data((uint8_t *) &byte, 1);

            if (1 == bytes_received)
            {
                rx_message_header.message_start_flag >>= 8;
                rx_message_header.message_start_flag |= ((uint32_t) byte << 24);

                if (MESSAGE_START_FLAG == rx_message_header.message_start_flag)
                {
                    /* wait until we've received the rest of the message header */
                    rx_state = RX_GET_HEADER;
                }
            }
            break;
        }

        /* read the rest of the message header */
        case RX_GET_HEADER:
        {
            if (rx_buffer_data_length() >= sizeof(message_header) - sizeof(uint32_t))
            {
                get_received_data((uint8_t *) &rx_message_header.message_index, sizeof(message_header) - sizeof(uint32_t));
                rx_state = RX_GET_MESSAGE;
                message_length = rx_message_header.message_length;

                /* discard the message if the length is invalid */
                if (message_length > MAX_MESSAGE_LENGTH)
                {
                    #ifdef DEBUG_COMMS 
                    dprintf_colour("[RED]Invalid message length %u[WHITE]\r\n", message_length);
                    #endif                                 
                    rx_state = RX_FIND_START;
                    break;
                }

                /* discard the message if the header checksum does not match */
                if (calculate_header_checksum(&rx_message_header) != rx_message_header.header_checksum)
                {
                    #ifdef DEBUG_COMMS 
                    dputs_colour("[RED]Header checksum failed[WHITE]\r\n");
                    #endif                                  
                    rx_state = RX_FIND_START;
                    break;
                }
                
                #ifdef DEBUG_COMMS
                dprintf_colour("[GREEN]Get message body. Length is %d[WHITE]\r\n", message_length);
                #endif
            }
            break;
        }

        case RX_GET_MESSAGE:
        {
            if (rx_buffer_data_length() >= message_length)
            {
                /* get the received message */
 
                if (get_received_data(received_message, message_length) != message_length)
                {
                    #ifdef DEBUG_COMMS                   
                    dprintf_colour("[RED]get_received_data() failed[WHITE]\r\n");
                    #endif                      
                }
                 

                /* check the CRC */
                crc = crc32(0, received_message, message_length);

                if (rx_message_header.message_crc == crc)
                {
                    /* check if this is an acknowledgement message first */
                    if ((ACK_MESSAGE_LENGTH == message_length) && ('A' == received_message[0]) && ('C' == received_message[1]) && ('K' == received_message[2]))
                    {
                        message_acknowledged(rx_message_header.message_index);
                    }
                    else
                    {
                        /* message is good, check the index to ensure that we didn't miss a message */

                        #ifdef DEBUG_COMMS 
                        if (rx_message_header.message_index != last_received_message_index + 1)
                        {
                            dprintf_colour("[RED]Missed %d messages[WHITE]\r\n", rx_message_header.message_index - last_received_message_index - 1);
                        }
                        #endif                         

                        last_received_message_index = rx_message_header.message_index;

                        /* process the message */
                        #ifdef DEBUG_COMMS
                        dputs_colour("[GREEN]Good message received[[WHITE]\r\n");
                        #endif

                        /* send acknowledgement message if required */
                        if (rx_message_header.ack_required)
                        {
                            send_ack_message(rx_message_header.message_index);
                        }

                        process_received_message(received_message, message_length);
                    }
                }
                else
                {
                    #ifdef DEBUG_COMMS
                    dprintf_colour("[RED]Received message CRC failure[WHITE]\r\n");
                    #endif
                    rx_message_crc_failure++;
                }

                /* wait for the next message */
                rx_state = RX_FIND_START;
                rx_message_header.message_start_flag = 0;
            }
            break;
        }
    }

    switch (tx_state)
    {
        case TX_IDLE:
        {
            /* nothing to do here */
            break;
        }

        case WAIT_FOR_ACK:
        {
            if (get_timer_value() == 0)
            {
                /* if we're here then no ACK has been received, so resend the message */
                resend_message();
                transmit_attempt++;

                /* after a while we give up */
                if (transmit_attempt >= MAX_TRANSMIT_ATTEMPTS)
                {
                    tx_state = TX_IDLE;
                }
            }
            break;
        }
    }

    return ((TX_IDLE != tx_state) || (RX_FIND_START != rx_state) || sending_data());
}
/* End of function pic_comms_task                                             */





static void start_timeout(void)
{
    tx_timer = ACK_TIMEOUT_DELAY_MS;
}
/* End of function start_timeout                                              */

/**************************************************************************** */
/* Function Name: cancel_timeout                                              */
/*                cancel timer for timeout of ACK message reception           */
/* ************************************************************************** */
static void cancel_timeout(void)
{
    tx_timer = -1;
}
/* End of function cancel_timeout                                             */

/**************************************************************************** */
/* Function Name: get_timer_value                                             */
/*                get the current value of the timeout timer                  */
/* ************************************************************************** */
static int32_t get_timer_value(void)
{
    int32_t timer_copy;
    timer_copy = tx_timer;
    return (timer_copy);
}
/* End of function get_timer_value                                            */

/**************************************************************************** */
/* Function Name: dspic_transmit_timer                                              */
/*                called on 1KHz interrupt timer to decrement the transmit    */
/*                timer                                                       */
/* ************************************************************************** */
void pic_transmit_timer(void)
{
    if (tx_timer > 0)
    {
        tx_timer--;
    }
}
/* End of function transmit_timer    */


/**************************************************************************** */
/* Function Name: message_acknowledged                                        */
/*                acknowledgement has been received                           */
/* @param[in] uint32_t message_index : the index of the message               */
/* ************************************************************************** */
static void message_acknowledged(uint32_t message_index)
{
    if (message_index == transmit_message_copy_index)
    {
        #ifdef DEBUG_COMMS
        dprintf_colour("[MAGENTA]ACK received for message %u[WHITE]\r\n", message_index);
        #endif

        tx_state = TX_IDLE;

        /* cancel timer */
        cancel_timeout();
    }
}
/* End of function message_acknowledged                                       */

/**************************************************************************** */
/* Function Name: send_ack_message                                            */
/*                send a message acknowledgement                              */
/* @param[in] uint32_t message_index : the index of the message               */
/* ************************************************************************** */
static void send_ack_message(uint32_t message_index)
{
    message_header header;
    uint32_t free_space;

    #ifdef DEBUG_COMMS
    dprintf_colour("[MAGENTA]Sending ACK for message %u[WHITE]\r\n", message_index);
    #endif

    /* make sure that we have space for the message */
    free_space = tx_buffer_free_space();
    if (free_space < ACK_MESSAGE_LENGTH + sizeof(message_header))
    {
        return;
    }

    /* setup the header */
    header.message_start_flag = MESSAGE_START_FLAG;
    header.message_index = message_index;
    header.message_length = ACK_MESSAGE_LENGTH;
    header.message_crc = crc32(0, (const uint8_t *) ACK_MESSAGE, ACK_MESSAGE_LENGTH);
    header.ack_required = false;
    header.header_checksum = calculate_header_checksum(&header);

    #ifdef DEBUG_COMMS
    dprintf_colour("[MAGENTA]Header checksum is 0x%04x[WHITE]\r\n", header.header_checksum);
    #endif
    
    /* send the header */
    send_bytes((const uint8_t *) &header, sizeof(message_header));

    /* send the message body */
    send_bytes((const uint8_t *) ACK_MESSAGE, ACK_MESSAGE_LENGTH);
}
/* End of function send_ack_message                                           */

/**************************************************************************** */
/* Function Name: process_received_message                                    */
/*                process the received message                                */
/* @param[in] uint8_t *data : message data                                    */
/* @param[in] uint32_t length : message length                                */
/* ************************************************************************** */
void process_received_message(uint8_t *data, uint32_t length)
{
    data[length] = '\0';

 

    #ifdef DEBUG_COMMS
    dprintf_colour("[CYAN]Message received length %d: %s[WHITE]\r\n", length, data);
    #endif

 

    if (1 == data[0])
    {
        dputs_colour("[PINK]cmd: Perform zero offset[WHITE]\r\n");
        // perform zero offset - obsolete
        return;
    }

 

    if (2 == data[0])
    {
        dputs_colour("[PINK]cmd: Perform reset[WHITE]\r\n");
        // perform reset
        PDAB_Command_Received(PDAB_CMD_RESET, 0, NULL, COMM_UART);
        return;
    }

 

    if (4 == data[0])
    {
        //dputs_colour("[PINK]cmd: Get status[WHITE]\r\n");
        // get status
        PDAB_Command_Received(PDAB_CMD_GET_STATUS, 0, NULL, COMM_UART);
        return;
    }
    
    if (3 == data[0])
    {
        dputs_colour("[PINK]cmd: Perform scan[WHITE]\r\n");
        // perform scan
        PDAB_Command_Received(PDAB_CMD_START_SCANNING, 0, NULL, COMM_UART);
        return;
    }
    
    if (5 == data[0])
    {
        dputs_colour("[PINK]cmd: Stop scanning command received[WHITE]\r\n");
        // stop scanning
        PDAB_Command_Received(PDAB_CMD_STOP_SCANNING, 0, NULL, COMM_UART);
        return;
    }
    
    if (7 == data[0])
    {
        dputs_colour("[PINK]cmd: Laser check command received[WHITE]\r\n");
        // laser check
        PDAB_Command_Received(PDAB_CMD_LASER_CHECK, 0, NULL, COMM_UART);
        return;
    }
    
    if (8 == data[0])
    {
        dputs_colour("[PINK]cmd: Request of settings[WHITE]\r\n");
        // request settings
        PDAB_Command_Received(PDAB_CMD_SETTINGS_REQUEST, 0, NULL, COMM_UART);
        return;
    }
    
    if (9 == data[0])
    {
        dputs_colour("[PINK]cmd: update settings[WHITE]\r\n");
        // update settings
        PDAB_Command_Received(PDAB_CMD_SETTINGS_UPDATE, length - 2, data + 2, COMM_UART);
        return;
    }
    
    if (6 == data[0])
    {
        dputs_colour("[PINK]cmd: is shutdown safe[WHITE]\r\n");
        // is shutdown safe
#ifndef DISABLE_PIC24
        process_pdab_is_safe_to_shutdown_message(data + 1, length - 1);
#endif
        return;
    }
}

#ifdef PIC_COMMS_TEST
void pic_communications_test(void)
{
    static uint8_t use_test_string = 0;
    const char *test_string0 = "[0] The government has previously said \"social distancing\" measures to slow the spread of the virus could include a ban on sporting events and other large gatherings";
    const char *test_string1 = "[1] The real fear is that, in the hours between the quarantine being announced and it coming into effect, people have gone from more infected areas in the north down south";
    const char *test_string2 = "[2] Last-minute changes meant the Cambridges and the Sussexes were led straight to their seats - rather than waiting for the Queen and taking part in the procession as they did in 2019";
    const char *test_string3 = "[3] \"We understand that there may be circumstances where a personal customer may fall into financial difficulty as a result of the impacts of coronavirus, for instance, loss of income,\" a spokesman for RBS said";
    const char *test_string;
    uint32_t test_string_length;

    /* test transmit */

    switch (use_test_string)
    {
        default:
        case 0:
            test_string = test_string0;
            break;

        case 1:
            test_string = test_string1;
            break;

        case 2:
            test_string = test_string2;
            break;

        case 3:
            test_string = test_string3;
            break;
    }

    test_string_length = strlen(test_string);

    dprintf_colour("[MAGENTA]rx_error_count = %d, rx_message_crc_failure %d[WHITE]\r\n", rx_error_count, rx_message_crc_failure);

    if (pic_communications_send_message((uint8_t *) test_string, test_string_length))
    {
        dprintf_colour("[YELLOW]Message [%d] added. Message length %d[WHITE]\r\n", use_test_string, test_string_length);

        use_test_string++;

        if (use_test_string > 3)
        {
            use_test_string = 0;
        }
    }
    else
    {
        dprintf_colour("[BLUE]Failed to send message[WHITE]\r\n");
    }
}
#endif
