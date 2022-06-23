/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    dar_comms.c

  @Summary
    Message communications between with the PIC32 DAR.

  @Description
    Message communications with the PIC32 DAR using UART1.
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

// An acknowledgment message will just contain 3 characters "ACK"
// The message index will be for the message that is being acknowledged

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "debug.h"
#include "message_exchange.h"
#include "pe_interface.h"

#define TX_BUFFER_LENGTH            512                 // circular transmit buffer
#define RX_BUFFER_LENGTH            512                 // circular receive buffer
#define MAX_MESSAGE_LENGTH          64                  // maximum length of message body

#define MESSAGE_START_FLAG          0x1857fc0a          // unique pattern to flag the start of a message

#define MAX_TRANSMIT_ATTEMPTS       5                   // maximum tries to send a message
#define MAX_TX_ACK_MESSAGE_LENGTH   100                 // maximum length of message that requires acknowledgment
#define ACK_MESSAGE_LENGTH          3                   // length of ACK message
#define ACK_MESSAGE                 "ACK"               // ACK message body
#define ACK_TIMEOUT_DELAY_MS       200                 // resend message delay after ACK not received
#define PREAMBLE_LENGTH             0                   // this will need to be changed if the Baud rate is changed

#define TX_MESSAGE_QUEUE_SIZE       5                   // transmit message queue



typedef struct
{
    uint8_t * message_data;
    uint32_t message_length;
    bool ack_required;
} tx_message;

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

/* transmit message queue */
static tx_message tx_message_queue[TX_MESSAGE_QUEUE_SIZE];
static uint8_t tx_queue_in;
static uint8_t tx_queue_out;
static bool tx_queue_full;

/* message retrying */
static uint8_t transmit_message_copy[MAX_TX_ACK_MESSAGE_LENGTH];
static uint32_t transmit_message_copy_length;
static uint32_t transmit_message_copy_index;
static TX_STATE tx_state;
static uint8_t transmit_attempt;
static int32_t tx_timer = -1;

static char receive_buffer[RX_BUFFER_LENGTH];
static uint32_t rx_input_index = 0;
static uint32_t rx_output_index = 0;

static uint32_t rx_error_count = 0;
static uint32_t rx_message_crc_failure = 0;

static PE_message_header_t rx_message_header;
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
static bool pic_communications_send_message(const uint8_t *data, uint32_t length, bool acknowledgment_required);

void process_received_message(uint8_t *data, uint32_t length);
static void send_ack_message(uint32_t message_index);
static void start_timeout(void);
static void cancel_timeout(void);
static int32_t get_timer_value(void);
static void resend_message(void);
static void message_acknowledged(uint32_t message_index);

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/**************************************************************************** */
/* Function Name: crc32                                                       */
/*                CRC32 (Ethernet, ZIP, etc) polynomial in reversed bit order */
/* @param[in] uint32_t crc : crc value so far (start from 0)                  */
/* @param[in] const uint8_t *data : data to calculate CRC for                 */
/* @param[in] uint32_t length : length of data                                */
/* @retval CRC                                                                */
/* ************************************************************************** */
uint32_t crc32(uint32_t crc, const uint8_t *data, uint32_t length)
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

/**************************************************************************** */
/* Function Name: pic_communications_init                                     */
/*                Initialise the PIC comms UART and code                      */
/* @retval None                                                               */
/* ************************************************************************** */
void pic_communications_init(void)
{
    /* initialise UART1 for transmit and receive */

    /* initialise transmit buffer */
    tx_input_index = 0;
    tx_output_index = 0;

    /* initialise receive buffer */
    rx_input_index = 0;
    rx_output_index = 0;
    rx_error_count = 0;

    IEC0bits.U1TXIE = 0;
    IEC0bits.U1RXIE = 0;

    transmit_message_index = 0;
    rx_message_crc_failure = 0;
    rx_state = RX_FIND_START;

    tx_state = TX_IDLE;

    /* not timing anything currently */
    tx_timer = -1;

    /* transmit message queue */
    tx_queue_in = 0;
    tx_queue_out = 0;
    tx_queue_full = false;    

    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    // Data Bits = 8; Parity = None; Stop Bits = 2;
    U1MODE = (0x8009 & ~(1<<15));  // disabling UART ON bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x00;

    // BaudRate = 38400; Frequency = 4000000 Hz; U1BRG 25; 
    U1BRG = 0x19;

    // ADMADDR 0; ADMMASK 0; 
    U1ADMD = 0x00;
    
    IEC0bits.U1RXIE = 1;
    
    // Make sure to set LAT bit corresponding to TxPin as high before UART initialisation
    U1MODEbits.UARTEN = 1;   // enabling UART ON bit
    U1STAbits.UTXEN = 1;
}
/* End of function pic_communications_init                                    */

/* transmit code */

/**************************************************************************** */
/* Function Name: UART1_TX_InterruptHandler                                   */
/*                UART transmit interrupt handler for the PIC comms           */
/* @retval None                                                               */
/* ************************************************************************** */
void UART1_TX_InterruptHandler(void)
{
    char ch;

    /* top up the FIFO transmit buffer */
    while ((tx_input_index != tx_output_index) && (0 == U1STAbits.UTXBF))
    {
        /* get the next character to be sent and increment the output pointer */
        ch = transmit_buffer[tx_output_index];
        tx_output_index++;

        if (tx_output_index >= TX_BUFFER_LENGTH)
        {
            tx_output_index = 0;
        }

        /* send the character */
        U1TXREG = ch;
    }

    /* clear the UART5TX interrupt flag after writing to buffer */
    IFS0bits.U1TXIF = 0;

    /* if the buffer is now empty, then there won't be anything further to send */
    if (tx_input_index == tx_output_index)
    {
        /* disable the transmit interrupt */
        IEC0bits.U1TXIE = 0;
    }
}
/* End of function UART1_TX_InterruptHandler                                  */

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
    bool buffer_empty;
    uint8_t interrupts_enabled;

    /* disable transmit interrupts */
    interrupts_enabled = IEC0bits.U1TXIE;
    IEC0bits.U1TXIE = 0;

    buffer_empty = (tx_input_index == tx_output_index);

    /* restore transmit interrupt enabled state */
    IEC0bits.U1TXIE = interrupts_enabled;

    return (buffer_empty);
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
    IEC0bits.U1TXIE = 0;

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
    IEC0bits.U1TXIE = 1;

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
    IEC0bits.U1TXIE = 0;

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
            if (1 == U1STAbits.UTXBF)
            {
                buffering = true;
                tx_buffer_add(string[i]);
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
        IEC0bits.U1TXIE = 1;
    }

    return (i);
}
/* End of function send_bytes                                                 */

/* receive code */

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
    IEC0bits.U1RXIE = 0;

    if (rx_input_index >= rx_output_index)
    {
        bytes = rx_input_index - rx_output_index;
    }
    else
    {
        bytes = RX_BUFFER_LENGTH - (rx_output_index - rx_input_index);
    }

    /* enable receive interrupts */
    IEC0bits.U1RXIE = 1;

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
    IEC0bits.U1RXIE = 0;

    for (i = 0; i < max_length; i++)
    {
        if (rx_buffer_empty())
        {
            /* enable receive interrupts */
            IEC0bits.U1RXIE = 1;
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
    IEC0bits.U1RXIE = 1;

    return (i);
}
/* End of function get_received_data                                          */

/**************************************************************************** */
/* Function Name: UART1_RX_InterruptHandler                                   */
/*                UART1 receive interrupt handler                             */
/* ************************************************************************** */
void UART1_RX_InterruptHandler(void)
{
    uint8_t ch;

    /* retrieve all the received data */
    /* data is discarded once the receive buffer is full */
    while (U1STAbits.URXDA == 1)
    {
        ch = (uint8_t) U1RXREG;

        if (!rx_buffer_full())
        {
            rx_buffer_add(ch);
        }
    }

    /* clear UART1 RX interrupt flag after reading data buffer */
    IFS0bits.U1RXIF = 0;
}
/* End of function UART1_RX_InterruptHandler                                  */

/**************************************************************************** */
/* Function Name: UART1_ErrorClear                                            */
/*                Clear UART1 receive errors                                  */
/* ************************************************************************** */
static void UART1_ErrorClear(void)
{
    if (U1STAbits.OERR == 1)
    {
        U1STAbits.OERR = 0;
    }

    IFS4bits.U1ERIF = 0;    
}
/* End of function UART1_ErrorClear                                           */

/**************************************************************************** */
/* Function Name: UART1_FAULT_InterruptHandler                                */
/*                UART1 fault interrupt handler                               */
/* ************************************************************************** */
void UART1_FAULT_InterruptHandler(void)
{
    rx_error_count++;    

    UART1_ErrorClear();
}
/* End of function UART1_FAULT_InterruptHandler                               */

/**************************************************************************** */
/* Function Name: calculate_header_checksum                                   */
/*                calculate a checksum for the supplied message header        */
/* @param[in] message_header *header : pointer to the header                  */
/* @retval the checksum for the header                                        */
/* ************************************************************************** */
static uint16_t calculate_header_checksum(PE_message_header_t *header)
{
    uint16_t checksum;
    uint8_t *ptr;
    uint8_t i;

    checksum = 0;
    ptr = (uint8_t *) header;

    for (i = 0; i < sizeof(PE_message_header_t) - sizeof(uint16_t); i++)
    {
        checksum += *ptr;
        ptr++;
    }

    return (checksum);
}
/* End of function calculate_header_checksum                                  */

/**************************************************************************** */
/* Function Name: pic_comms_queue_message                                     */
/*                send a message to the other PIC, add to queue if need be    */
/* @param[in] const uint8_t *data : message data                              */
/* @param[in] uint32_t length : message length                                */
/* @param[in] bool acknowledgement_required : true if the message must be      */
/*                 acknowledged                                               */
/* @retval the checksum for the header                                        */
/* ************************************************************************** */
uint8_t pic_comms_queue_message(const uint8_t *data, uint32_t length, bool acknowledgment_required)
{
    /* if the queue is full return false to indicate that we can't add this message to the queue */
    if (tx_queue_full)
    {
        return 0x0F;
    }

    /* if the queue is empty and the transmit task is idle then we can send the message without queueing it first */
    if ((tx_queue_in == tx_queue_out) && (TX_IDLE == tx_state) && tx_buffer_empty())
    {
        pic_communications_send_message(data, length, acknowledgment_required);
        return 0x01;
    }

    /* add the message to the queue */
    tx_message_queue[tx_queue_in].message_data = malloc(length);

    /* if we failed to allocate memory then return false */
    if (NULL == tx_message_queue[tx_queue_in].message_data)
    {
        return 0x0E;
    }

    //dputs_colour("[MAGENTA]Queueing transmit message[WHITE]\r\n");

    /* update the queue */
    tx_message_queue[tx_queue_in].message_length = length;
    tx_message_queue[tx_queue_in].ack_required = acknowledgment_required;
    memcpy(tx_message_queue[tx_queue_in].message_data, data, length);

    tx_queue_in++;

    if (tx_queue_in >= TX_MESSAGE_QUEUE_SIZE)
    {
        tx_queue_in = 0;
    }

    /* check to see if the queue is now full */
    if (tx_queue_in == tx_queue_out)
    {
        tx_queue_full = true;
    }

    return 0x02;
}
/* End of function pic_comms_queue_message                                    */

/**************************************************************************** */
/* Function Name: dequeue_transmit_message                                    */
/*                remove a message from the transmit queue and add it to the  */
/*                transmit buffer                                             */
/* ************************************************************************** */
static void dequeue_transmit_message(void)
{
    uint8_t *data;
    uint32_t length;
    bool acknowledgement_required;

    //dputs_colour("[MAGENTA]Dequeuing transmit message[WHITE]\r\n");

    /* read the message from the queue */
    data = tx_message_queue[tx_queue_out].message_data;
    length = tx_message_queue[tx_queue_out].message_length;
    acknowledgement_required = tx_message_queue[tx_queue_out].ack_required;

    /* send the message */
    if (!pic_communications_send_message(data, length, acknowledgement_required))
    {
        /* we couldn't buffer the message - leave it on the queue */
        return;
    }

    /* free the memory used to buffer the message */
    free(data);

    /* update the queue */
    tx_queue_out++;

    if (tx_queue_out >= TX_MESSAGE_QUEUE_SIZE)
    {
        tx_queue_out = 0;
    }

    tx_queue_full = false;
}
/* End of function dequeue_transmit_message                                   */

#if (PREAMBLE_LENGTH != 0)
/**************************************************************************** */
/* Function Name: send_preamble                                               */
/*                Send preamble before message header to ensure that the PIC  */
/*                at the other end has had time to wake up from sleep         */
/* ************************************************************************** */
static void send_preamble(void)
{
    uint8_t preamble[PREAMBLE_LENGTH];
    uint16_t i;

    /* create the preamble */
    for (i = 0; i < PREAMBLE_LENGTH; i++)
    {
        preamble[i] = 0x5a;
    }

    send_bytes(preamble, PREAMBLE_LENGTH);
}
/* End of function send_preamble                                              */
#endif

/**************************************************************************** */
/* Function Name: pic_communications_send_message                             */
/*                send a message to the other PIC                             */
/* @param[in] const uint8_t *data : message data                              */
/* @param[in] uint32_t length : message length                                */
/* @param[in] bool acknowledgment_required : true if the message must be      */
/*                 acknowledged                                               */
/* @retval true if the message was buffered, false if there wasn't space      */
/* ************************************************************************** */
static bool pic_communications_send_message(const uint8_t *data, uint32_t length, bool acknowledgment_required)
{
    PE_message_header_t header;
    uint32_t free_space;

    /* return false if we're waiting for a message to be acknowledged */
    if (WAIT_FOR_ACK == tx_state)
    {
        return (false);
    }

    /* make sure that we have space for the message */
    free_space = tx_buffer_free_space();
    if (free_space < length + sizeof(PE_message_header_t) + PREAMBLE_LENGTH)
    {
        return (false);
    }

    /* setup the header */
    header.message_start_flag = MESSAGE_START_FLAG;
    header.message_index = transmit_message_index;
    header.message_length = length;
    header.message_crc = crc32(0, data, length);
    header.ack_required = acknowledgment_required;
    header.header_checksum = calculate_header_checksum(&header);

    transmit_message_index++;

    #if (PREAMBLE_LENGTH != 0)
    send_preamble();
    #endif

    /* send the header */
    send_bytes((const uint8_t *) &header, sizeof(PE_message_header_t));

    /* send the message body */
    send_bytes(data, length);

    /* if acknowledgement is required, we need to hold a copy of the message */
    if (acknowledgment_required && (length <= MAX_TX_ACK_MESSAGE_LENGTH))
    {
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
    PE_message_header_t header;
    uint32_t free_space;

    dprintf_colour("[MAGENTA]Resending message %ld, attempt number %d[WHITE]\r\n", transmit_message_copy_index, transmit_attempt + 1);

    /* make sure that we have space for the message */
    free_space = tx_buffer_free_space();
    if (free_space < transmit_message_copy_length + sizeof(PE_message_header_t) + PREAMBLE_LENGTH)
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

    #if (PREAMBLE_LENGTH != 0)
    send_preamble();
    #endif

    /* send the header */
    send_bytes((const uint8_t *) &header, sizeof(PE_message_header_t));

    /* send the message body */
    send_bytes(transmit_message_copy, transmit_message_copy_length);

    start_timeout();
}
/* End of function resend_message                                             */

/**************************************************************************** */
/* Function Name: pic_comms_task                                              */
/*                PIC communications task that's called in the main idle loop */
/* ************************************************************************** */
void pic_comms_task(void)
{
    static uint32_t message_length;
    uint32_t bytes_received;
    uint8_t byte;
    uint32_t crc;
    int32_t missed_messages;

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
            if (rx_buffer_data_length() >= sizeof(PE_message_header_t) - sizeof(uint32_t))
            {
                get_received_data((uint8_t *) &rx_message_header.message_index, sizeof(PE_message_header_t) - sizeof(uint32_t));
                rx_state = RX_GET_MESSAGE;
                message_length = rx_message_header.message_length;

                /* discard the message if the length is invalid */
                if (message_length > MAX_MESSAGE_LENGTH)
                {
                    dprintf_colour("[RED]Invalid message length %ld[WHITE]\r\n", message_length);
                    rx_state = RX_FIND_START;
                    break;
                }

                //dprintf_colour("[RED]P24 message header checksum is 0x%04x[WHITE]\r\n", rx_message_header.header_checksum);

                /* discard the message if the header checksum does not match */
                if (calculate_header_checksum(&rx_message_header) != rx_message_header.header_checksum)
                {
                    dputs_colour("[RED]Header checksum failed[WHITE]\r\n");
                    rx_state = RX_FIND_START;
                    break;
                }

                //dprintf_colour("[GREEN]P24 get message body. Length is %d[WHITE]\r\n", message_length);
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
                    dprintf_colour("[RED]get_received_data() failed[WHITE]\r\n");
                }

                /* check the CRC */
                crc = crc32(0, received_message, message_length);

                if (rx_message_header.message_crc == crc)
                {
                    /* check if this is an acknowledgement message first */
                    if ((ACK_MESSAGE_LENGTH == message_length) && ('A' == received_message[0]) && ('C' == received_message[1]) && ('K' == received_message[2]))
                    {
                        dprintf_colour("got ack for message %lu\r\n",  rx_message_header.message_index);
                        message_acknowledged(rx_message_header.message_index);
                    }
                    else
                    {
                        /* message is good, check the index to ensure that we didn't miss a message */
                        missed_messages = rx_message_header.message_index != last_received_message_index + 1;

                        if (missed_messages > 0)
                        {
                            dprintf_colour("[RED]Missed %ld messages[WHITE]\r\n", missed_messages);
                        }

                        last_received_message_index = rx_message_header.message_index;

                        /* process the message */
                        //dputs_colour("[GREEN]Good message received[[WHITE]\r\n");

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
                    dprintf_colour("[RED]Received message CRC failure[WHITE]\r\n");
                    //received_message[message_length] = '\0';
                    //dprintf_colour("[RED]P24 message data is %s[WHITE]\r\n", received_message);
                    //dprintf_colour("[RED]Message length is %ld, index is %ld[WHITE]\r\n", message_length, rx_message_header.message_index);
                    //dprintf_colour("[RED]P24 message[0] is '%c'[WHITE]\r\n", received_message[0]);
                    //dprintf_colour("[RED]P24 message[1] is '%c'[WHITE]\r\n", received_message[1]);
                    //dprintf_colour("[RED]P24 message[2] is '%c'[WHITE]\r\n", received_message[2]);
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
            /* is there a message waiting to be sent? */
            if (tx_queue_full || (tx_queue_in != tx_queue_out))
            {
                dequeue_transmit_message();
            }
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
}
/* End of function pic_comms_task                                             */

/**************************************************************************** */
/* Function Name: start_timeout                                               */
/*                start system timer for timeout of ACK message reception     */
/* ************************************************************************** */
static void start_timeout(void)
{
    IEC0bits.T1IE = false;
    tx_timer = ACK_TIMEOUT_DELAY_MS;
    IEC0bits.T1IE = true;
}
/* End of function start_timeout                                              */

/**************************************************************************** */
/* Function Name: cancel_timeout                                              */
/*                cancel timer for timeout of ACK message reception           */
/* ************************************************************************** */
static void cancel_timeout(void)
{
    IEC0bits.T1IE = false;
    tx_timer = -1;
    IEC0bits.T1IE = true;
}
/* End of function cancel_timeout                                             */

/**************************************************************************** */
/* Function Name: get_timer_value                                             */
/*                get the current value of the timeout timer                  */
/* ************************************************************************** */
static int32_t get_timer_value(void)
{
    int32_t timer_copy;

    IEC0bits.T1IE = false;
    timer_copy = tx_timer;
    IEC0bits.T1IE = true;

    return (timer_copy);
}
/* End of function get_timer_value                                            */

/**************************************************************************** */
/* Function Name: transmit_timer                                              */
/*                called on 1KHz interrupt timer to decrement the transmit    */
/*                timer                                                       */
/* ************************************************************************** */
void transmit_timer(void)
{
    if (tx_timer > 0)
    {
        tx_timer--;
    }
}
/* End of function transmit_timer                                             */

/**************************************************************************** */
/* Function Name: message_acknowledged                                        */
/*                acknowledgment has been received                            */
/* @param[in] uint32_t message_index : the index of the message               */
/* ************************************************************************** */
static void message_acknowledged(uint32_t message_index)
{
    if (message_index == transmit_message_copy_index)
    {
        //dprintf_colour("[MAGENTA]ACK received for message %ld[WHITE]\r\n", message_index);

        tx_state = TX_IDLE;

        /* cancel timer */
        cancel_timeout();
    }
}
/* End of function message_acknowledged                                       */

/**************************************************************************** */
/* Function Name: send_ack_message                                            */
/*                send a message acknowledgment                               */
/* @param[in] uint32_t message_index : the index of the message               */
/* ************************************************************************** */
static void send_ack_message(uint32_t message_index)
{
    PE_message_header_t header;
    uint32_t free_space;

    //dprintf_colour("[MAGENTA]Sending ACK for message %ld[WHITE]\r\n", message_index);

    /* make sure that we have space for the message */
    free_space = tx_buffer_free_space();
    if (free_space < ACK_MESSAGE_LENGTH + sizeof(PE_message_header_t))
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

    /* send the header */
    send_bytes((const uint8_t *) &header, sizeof(PE_message_header_t));

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
    const uint8_t dar_status_message_length = 24;
    const uint8_t dar_update_date_time_message_length = 31;
    const uint8_t dar_request_shutdown_message_length = 30;
    const uint8_t dar_request_version_message_length = 29;
    const uint8_t dar_reset_temp_message_length = 24;
    const uint8_t dar_reset_error_length = 22;
    const uint8_t dar_reset_length = 11;

    data[length] = '\0'; 
    //dprintf_colour("[CYAN]DAR message received length %ld: %s[WHITE]\r\n", length, data);

    if ((length >= dar_status_message_length) && (0 == memcmp(data, PE_RX_GET_STATUS_MESSAGE_HEADER , dar_status_message_length)))
    {
        // process the get status message here
        process_get_status_message(data + dar_status_message_length, length - dar_status_message_length);
        return;
    }

    if ((length > dar_update_date_time_message_length) && (0 == memcmp(data, PE_RX_SET_TIME_DATE_MESSAGE_HEADER, dar_update_date_time_message_length)))
    {
        // process the set time and date message here
        process_set_time_date_message(data + dar_update_date_time_message_length, length - dar_update_date_time_message_length);
        return;
    }

    if ((length >= dar_request_shutdown_message_length) && (0 == memcmp(data, PE_RX_REQUEST_SHUTDOWN_MESSAGE_HEADER, dar_request_shutdown_message_length)))
    {
        // process the power down message here
        process_power_down_message(data + dar_request_shutdown_message_length, length - dar_request_shutdown_message_length);
        return;
    }

    if ((length >= dar_request_version_message_length) && (0 == memcmp(data, PE_RX_GET_VERSION_MESSAGE_HEADER , dar_request_version_message_length)))
    {
        // process the request version message here
        process_request_version_message(data + dar_request_version_message_length, length - dar_request_version_message_length);
        return;
    }
    
    if((length >= dar_reset_temp_message_length) && (0 == memcmp(data, PE_RX_RESET_TEMPERATURE_MESSAGE_HEADER , dar_reset_temp_message_length))){
        
        process_reset_temp_message(data + dar_reset_temp_message_length, length - dar_reset_temp_message_length); 
        return; 
    }

    if((length >= dar_reset_error_length) && (0 == memcmp(data, PE_RX_RESET_ERROR_MESSAGE_HEADER , dar_reset_error_length))){
        
        process_reset_error_message(data + dar_reset_error_length, length - dar_reset_error_length); 
        return; 
    }

    if((length >= dar_reset_length) && (0 == memcmp(data, PE_RX_RESET_MESSAGE_HEADER , dar_reset_length))){
        
        process_reset_message(data + dar_reset_length, length - dar_reset_length); 
        return; 
    }

}
/* End of function process_received_message                                   */

#ifdef DAR_COMMS_TEST
void dar_communications_test(void)
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
