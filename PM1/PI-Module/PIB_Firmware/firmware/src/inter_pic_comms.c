/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    inter_pic_comms.c

  @Summary
    Uses the shared FRAM to communicate with the other board.

  @Description
    PIC to PIC communications.
 */
/* ************************************************************************** */

/* Need to have one area of RAM for sending messages */
/* Another for receiving messages */
/* A signalling system for notifying the other chip that there is a message */
/* A CRC on the message packet */
/* A header on the message packet giving its length */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"

/* We have 512K bytes of RAM */
/* If we have a maximum message length of 16K, then that gives us space for 32 messages */
/* So for the time being, allow each MPU to queue up to 16 messages before the other reads them */
/* Message header will have an index number and a length */
/* And a flag to indicate that there was a CRC failure */
/* And the CRC */

// #define PDA_BOARD if this module is on the data acquisition board
//#define PDA_BOARD

#define MAXIMUM_MESSAGE_LENGTH                  (16 * 1024)     // maximum message length including the header
#define MAXIMUM_MESSAGES                        16              // maximum number of messages that can be in the "queue"
#define MESSAGE_MARKER                          0x42073791u     // an arbitrary number that signifies the start of a message
#define MESSAGE_OFFSET                          32              // the start of the actual message data

#ifdef PDA_BOARD
    #define RAM_TRANSMIT_BASE_ADDRESS           0
    #define RAM_RECEIVE_BASE_ADDRESS            (MAXIMUM_MESSAGE_LENGTH * 16)
#else
    #define RAM_TRANSMIT_BASE_ADDRESS           (MAXIMUM_MESSAGE_LENGTH * 16)
    #define RAM_RECEIVE_BASE_ADDRESS            0
#endif

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

typedef struct
{
    uint32_t message_marker;        // a number to signify that this is a message
    uint32_t message_index;         // the message index number
    uint32_t message_length;        // the length of the message not including the header
    uint32_t crc;                   // the CRC of the message data
    bool message_nack;              // true if the CRC failed
} message_header;

static uint32_t message_index = 0;
static uint32_t last_received_index = 0;
static void (*message_received_callback)(void) = NULL;

static uint32_t calculate_crc(uint8_t *message, uint32_t length);
static void send_message_sent_signal(void);
static int8_t pic_comms_get_next_free_slot(void);
static bool flush_messages(bool receive);
static void message_ready_pin_change_callback(GPIO_PIN pin, uintptr_t context);

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* calculate CRC on the supplied block of memory */
static uint32_t calculate_crc(uint8_t *message, uint32_t length)
{
    uint32_t crc;
    uint32_t i;

    crc = 0;

    /* just a checksum for now */
    for (i = 0; i < length; i++)
    {
        crc += message[i];
    }

    return (crc);
}

/* find the next free slot for sending a message */
static int8_t pic_comms_get_next_free_slot(void)
{
    uint8_t i;
    message_header msg_header;

    /* read through the message headers until we find a free slot */
    for (i = 0; i < MAXIMUM_MESSAGES; i++)
    {
        if (!FRAM_read(RAM_TRANSMIT_BASE_ADDRESS + (i * MAXIMUM_MESSAGE_LENGTH), (uint8_t *) &msg_header, sizeof(message_header)))
        {
            /* timed out */
            dputs_colour("[RED]pic_comms_get_next_free_slot() FRAM_read() timed out[WHITE]\r\n");
            return (-1);
        }

        /* a slot is free if there is no message marker */
        if (0 == msg_header.message_marker)
        {
            dprintf_colour("[MAGENTA]Message index is %d[WHITE]\r\n", i);
            dprintf_colour("[MAGENTA]Message marker is 0x%x[WHITE]\r\n", msg_header.message_marker);
            dprintf_colour("[MAGENTA]Message index was %d[WHITE]\r\n", msg_header.message_index);
            return (i);
        }
    }

    return (-1);
}

/* flush the messages from the transmit or receive queue */
/* returns true if it was able to access the FRAM, false if not */
static bool flush_messages(bool receive)
{
    uint8_t i;
    message_header msg_header;
    uint32_t base_address;

    /* return false if the FRAM is busy */
    if (!FRAM_is_fram_free())
    {
        return (false);
    }

    /* generate the message header */
    msg_header.message_marker = 0;
    msg_header.message_index = 0;
    msg_header.message_length = 0;
    msg_header.crc = 0;
    msg_header.message_nack = false;

    if (receive)
    {
        base_address = RAM_RECEIVE_BASE_ADDRESS;
    }
    else
    {
        base_address = RAM_TRANSMIT_BASE_ADDRESS;
    }

    /* clear down all of the message headers */
    for (i = 0; i < MAXIMUM_MESSAGES; i++)
    {
        /* write the message header */
        FRAM_write(base_address + (i * MAXIMUM_MESSAGE_LENGTH), (uint8_t *) &msg_header, sizeof(message_header));
    }

    return (true);
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void inter_pic_comms_init(void)
{
    #ifdef PDA_BOARD
    GPIO_PinInterruptCallbackRegister(GPIO_PIN_RB13, message_ready_pin_change_callback, 0);
    PIB_IO2_InputEnable();
    PIB_IO2_InterruptEnable();
    #else
    GPIO_PinInterruptCallbackRegister(GPIO_PIN_RB9, message_ready_pin_change_callback, 0);
    EIB_IRQ_InputEnable();
    EIB_IRQ_InterruptEnable();
    #endif
}

/* send a message to the other board */
/* returns true if it was able to access the FRAM, false if not */
/* message_sent is set true if the message was added to the queue */
bool pic_comms_send_message(uint8_t *message, uint32_t length, bool *message_sent)
{
    int8_t next_free_slot;
    message_header msg_header;
    //message_header verify_msg_header;

    *message_sent = false;

    /* return false if the FRAM is busy */
    if (!FRAM_is_fram_free())
    {
        return (false);        
    }

    /* validate that the message length is within range */
    if (length > (MAXIMUM_MESSAGE_LENGTH - MESSAGE_OFFSET))
    {
        return (true);
    }

    /* get the next free message slot */
    next_free_slot = pic_comms_get_next_free_slot();

    /* return if there are no free message slots */
    if (next_free_slot < 0)
    {
        return (true);
    }

    /* we have an empty slot - copy the message body to the slot */
    FRAM_write(RAM_TRANSMIT_BASE_ADDRESS + (MAXIMUM_MESSAGE_LENGTH * next_free_slot) + MESSAGE_OFFSET, message, length);

    /* generate the message header */
    msg_header.message_marker = MESSAGE_MARKER;
    msg_header.message_index = message_index;
    msg_header.message_length = length;
    msg_header.crc = calculate_crc(message, length);
    msg_header.message_nack = false;

    message_index++;

    /* write the message header */
    FRAM_write(RAM_TRANSMIT_BASE_ADDRESS + (MAXIMUM_MESSAGE_LENGTH * next_free_slot), (uint8_t *) &msg_header, sizeof(message_header));

    /* verify the message header */
    //FRAM_read(RAM_TRANSMIT_BASE_ADDRESS + (MAXIMUM_MESSAGE_LENGTH * next_free_slot), (uint8_t *) &verify_msg_header, sizeof(message_header));

    //if (memcmp((void *) &msg_header, (void *) &verify_msg_header, sizeof(message_header)) != 0)
    //{
    //    dputs_colour("[RED]pic_comms_send_message() message header write verification failure[WHITE]\r\n");
    //}    

    *message_sent = true;
    send_message_sent_signal();

    /* message successfully copied to FRAM */
    return (true);
}

/* retrieve the next message from the other board */
/* returns true if it was able to access the FRAM, false if not */
/* message_received is set true if the message was retrieved from the queue */
bool pic_comms_get_message(uint8_t *message, uint32_t *length, bool *message_received)
{
    uint8_t i;
    uint32_t lowest_index;
    uint8_t message_slot;
    message_header msg_header;
    message_header next_msg_header;
    //message_header verify_msg_header;
    uint32_t calculated_crc;

    /* set the initial state of the message received flag */
    *message_received = false;

    /* return false if the FRAM is in the process of being accessed */
    if (!FRAM_is_fram_free())
    {
        return (false);        
    }

    lowest_index = 0xffffffffu;

    /* read all of the message headers */
    /* we need to find the next message (lowest index) */
    for (i = 0; i < MAXIMUM_MESSAGES; i++)
    {
        /* read message header */
        if (!FRAM_read(RAM_RECEIVE_BASE_ADDRESS + (i * MAXIMUM_MESSAGE_LENGTH), (uint8_t *) &msg_header, sizeof(message_header)))
        {
            dputs_colour("[RED]pic_comms_get_message() FRAM_read() for message header timed out[WHITE]\r\n");
            return (true);
        }

        /* if this is a message and the index is the lowest found so far, and it has not been NAKed */
        if ((MESSAGE_MARKER == msg_header.message_marker) && (msg_header.message_index < lowest_index) && !msg_header.message_nack)
        {
            lowest_index = msg_header.message_index;
            message_slot = i;
            memcpy((void *) &next_msg_header, (void *) &msg_header, sizeof(message_header));
        }
    }

    /* return if there is no new message */
    if (0xffffffffu == lowest_index)
    {
        return (true);
    }

    dprintf_colour("[YELLOW]Message received with index [%d][WHITE]\r\n", lowest_index);
    
    if ((last_received_index > 0) && (lowest_index != last_received_index + 1))
    {
        dputs_colour("[RED]Message(s) missed![WHITE]\r\n");
    }

    last_received_index = lowest_index;

    /* read the message content */
    if (!FRAM_read(RAM_RECEIVE_BASE_ADDRESS + (message_slot * MAXIMUM_MESSAGE_LENGTH) + MESSAGE_OFFSET, message, next_msg_header.message_length))
    {
        dputs_colour("[RED]pic_comms_get_message() FRAM_read() for message content timed out[WHITE]\r\n");
        return (true);
    }

    /* check the CRC */
    calculated_crc = calculate_crc(message, next_msg_header.message_length);

    if (calculated_crc == next_msg_header.crc)
    {
        /* free up the message slot */
        next_msg_header.message_marker = 0;
        *length = next_msg_header.message_length;
    }
    else
    {
        dputs_colour("[RED]Message CRC failure[WHITE]\r\n");
        /* the CRC does not match - NAK the message */
        /* give the other board the opportunity to regenerate the message */
        next_msg_header.message_nack = true;

        // temp override (in future we may want to leave failed messages to allow the transmitter to rewrite the message)
        next_msg_header.message_marker = 0;
        next_msg_header.message_nack = false;
        *length = next_msg_header.message_length;
        calculated_crc = next_msg_header.crc;
    }

    /* re-write the message header */
    FRAM_write(RAM_RECEIVE_BASE_ADDRESS + (message_slot * MAXIMUM_MESSAGE_LENGTH), (uint8_t *) &next_msg_header, sizeof(message_header));

    /* verify the message header */
    /* note that this is here for testing - we can take this out once we're happy that everything is working properly */
    //FRAM_read(RAM_RECEIVE_BASE_ADDRESS + (message_slot * MAXIMUM_MESSAGE_LENGTH), (uint8_t *) &verify_msg_header, sizeof(message_header));

    //if (memcmp((void *) &next_msg_header, (void *) &verify_msg_header, sizeof(message_header)) != 0)
    //{
    //    dputs_colour("[RED]pic_comms_get_message() message header write verification failure[WHITE]\r\n");
    //}

    /* set message received true if the message was good */
    if (calculated_crc == next_msg_header.crc)
    {
        *message_received = true;
    }

    /* we were able to access the FRAM */
    return (true);
}

/* flush the message transmit queue */
bool flush_received_messages(void)
{
    return (flush_messages(true));
}

/* flush the message receive queue */
bool flush_transmitted_messages(void)
{
    return (flush_messages(false));
}

/* log all of the receive buffer header slots for debugging */
bool log_receive_buffer_slots(void)
{
    uint8_t i;
    uint32_t address;
    message_header msg_header;

    /* wait for the FRAM to be free */
    if (!FRAM_is_fram_free())
    {
        return (false);
    }

    /* read all of the message headers */
    for (i = 0; i < MAXIMUM_MESSAGES; i++)
    {
        /* read message header */
        address = RAM_RECEIVE_BASE_ADDRESS + (i * MAXIMUM_MESSAGE_LENGTH);
        FRAM_read(address, (uint8_t *) &msg_header, sizeof(message_header));

        /* log the details for each slot */
        dprintf_colour("Message slot %d at address 0x%08x:\r\n", i, address);
        dprintf_colour("  message_marker [0x%08x]\r\n", msg_header.message_marker);
        dprintf_colour("  message_length [%d]\r\n", msg_header.message_index);
        dprintf_colour("  message_index  [%d]\r\n", msg_header.message_length);
        dprintf_colour("  crc            [%d]\r\n", msg_header.crc);
        dprintf_colour("  message_nack   [%d]\r\n", msg_header.message_nack);
    }

    return (true);
}

// I/O lines connected between the PIB board and the PDA board

// 1) PIB DIB EIB_IRQ pin 173 RB9                  PDA DIB_IO1 pin 6  RC1
// 2) PIB DIB MPB_IRQ pin 42  RH14 / INT0          PDA DIB_IO2 pin 42 RB13
// 3) PIB DIB MPB_IO3 pin 2   RA10                 PDA DIB_IO3 pin 10 RG6

// Let's assign (1) to signal PDA -> PIB and (2) to signal PIB -> PDA

// PIB board: set change notification on pin 173 (RB9), RH14 (pin 42) to output
// PDA board: set change notification on pin 42 (RB13), RC1 (pin 6) to output

/* this function will be called when a message is available from the other board */
static void message_ready_pin_change_callback(GPIO_PIN pin, uintptr_t context)
{
    (void) pin;
    (void) context;

    /* if a callback is registered, then call it */
    if (NULL != message_received_callback)
    {
        (*message_received_callback)();
    }
}

/* signal the other board that a message has been sent */
static void send_message_sent_signal(void)
{
    dputs_colour("[YELLOW]Sending message available signal[WHITE]\r\n");

    #ifdef PDA_BOARD
        LATCbits.LATC1 ^= 1;
    #else
        LATHbits.LATH14 ^= 1;
    #endif    
}

void register_new_message_callback(void (*message_received_callback_function)(void))
{
    message_received_callback = message_received_callback_function;
}
