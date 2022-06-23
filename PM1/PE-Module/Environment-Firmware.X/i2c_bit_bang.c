// i2c-bit-bang.c

// I2C is on:
// Development board issue A
// SDA pin 23 (RB12)
// SCL pin 22 (RB11)

// Development board issue B, main board
// SDA pin 14 (RB5)
// SCL pin 15 (RB6)

#include <stdbool.h>

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"

#include "i2c_bit_bang.h"

#ifdef DEV_BOARD_A
#define SDA        (_RB12)
#define SCLK       (_RB11)

#define SDA_WR     (_LATB12)
#define SCLK_WR    (_LATB11)

#define SDA_TRIS   (_TRISB12)
#define SCLK_TRIS  (_TRISB11)
#else
#define SDA        (_RB5)
#define SCLK       (_RB6)

#define SDA_WR     (_LATB5)
#define SCLK_WR    (_LATB6)

#define SDA_TRIS   (_TRISB5)
#define SCLK_TRIS  (_TRISB6)
#endif

#define I2CSPEED        10
#define TIMEOUT         1000


static char started;
static char arbitrationWasLost;


void i2c_initialise(void)
{
    SDA_TRIS = 1;
    SCLK_TRIS = 1;
    SDA_WR = 1;
    SCLK_WR = 1;
    started = 0;
}

//static void sda(char level)
//{
//    SDA_TRIS = level;
//    SDA_WR = level;
//}

//static void sclk(char level)
//{
//    SCLK_TRIS = level;
//    SCLK_WR = level;
//}

// set SCL as input and return current level of line, 0 or 1
static char read_SCL(void)
{
    SCLK_TRIS = 1;
    SCLK_WR = 1;

    return (SCLK);
}

// set SDA as input and return current level of line, 0 or 1
static char read_SDA(void)
{
    SDA_TRIS = 1;
    SDA_WR = 1;

    return (SDA);
}

// actively drive SCL signal low
static void clear_SCL(void)
{
    SCLK_TRIS = 0;
    SCLK_WR = 0;
}

// actively drive SDA signal low
static void clear_SDA(void)
{
    SDA_TRIS = 0;
    SDA_WR = 0;
}

static void arbitration_lost(void)
{
    arbitrationWasLost = 1;
}

static void I2C_delay()
{
    int i;

    for (i = 0; i < I2CSPEED; i++);
}

static void i2c_start_cond(void)
{
    int timeout;

    if (started)
    {
        // if started, do a restart condition
        // set SDA to 1
        read_SDA();
        I2C_delay();

        timeout = 0;
        while (read_SCL() == 0)
        {
            // clock stretching
            // you should add timeout to this loop
            timeout++;
            if (timeout > TIMEOUT)
            {
                break;
            }
        }

        // repeated start setup time, minimum 4.7us
        I2C_delay();
    }

    if (read_SDA() == 0)
    {
        arbitration_lost();
    }

    // SCL is high, set SDA from 1 to 0
    clear_SDA();
    I2C_delay();
    clear_SCL();
    started = true;
}

static void i2c_stop_cond(void)
{
    int timeout;

    // set SDA to 0
    clear_SDA();
    I2C_delay();

    // clock stretching
    timeout = 0;
    while (read_SCL() == 0)
    {
        // you should add timeout to this loop
        timeout++;
        if (timeout > TIMEOUT)
        {
            break;
        }
    }

    // stop bit setup time, minimum 4us
    I2C_delay();

    // SCL is high, set SDA from 0 to 1
    if (read_SDA() == 0)
    {
        arbitration_lost();
    }

    I2C_delay();
    started = false;
}

// write a bit to I2C bus
static void i2c_write_bit(char thebit)
{
    int timeout;

    if (thebit == 1)
    {
        read_SDA();
    }
    else
    {
        clear_SDA();
    }

    I2C_delay();

    timeout = 0;
    while (read_SCL() == 0)
    {
        // clock stretching
        // you should add timeout to this loop
        timeout++;
        if (timeout > TIMEOUT)
        {
            break;
        }
    }

    // SCL is high, now data is valid
    // if SDA is high, check that nobody else is driving SDA
    if ((thebit == 1) && (read_SDA() == 0))
    {
        arbitration_lost();
    }

    I2C_delay();
    clear_SCL();
}

// read a bit from I2C bus
static char i2c_read_bit(void)
{
    char thebit;
    int timeout;

    // let the slave drive data
    read_SDA();
    I2C_delay();

    timeout = 0;
    while (read_SCL() == 0)
    {
        // clock stretching
        // you should add timeout to this loop
        timeout++;
        if (timeout > TIMEOUT)
        {
            break;
        }
    }

    // SCL is high, now data is valid
    thebit = read_SDA();
    I2C_delay();
    clear_SCL();

    return (thebit);
}

// write a byte to I2C bus
// return 0 if ack by the slave
static char i2c_write_byte(char send_start, char send_stop, unsigned char byte)
{
    unsigned char thebit;
    char nack;

    if (send_start == 1)
    {
        i2c_start_cond();
    }

    for (thebit = 0; thebit < 8; thebit++)
    {
        i2c_write_bit((byte & 0x80) != 0);
        byte <<= 1;
    }

    nack = i2c_read_bit();

    if (send_stop == 1)
    {
       i2c_stop_cond();
    }

    return (nack);
}

// read a byte from I2C bus
static unsigned char i2c_read_byte(char nack, char send_stop)
{
    unsigned char byte = 0;
    unsigned thebit;

    for (thebit = 0; thebit < 8; thebit++)
    {
        byte = (byte << 1) | i2c_read_bit();
    }

    i2c_write_bit(nack);

    if (send_stop == 1)
    {
        i2c_stop_cond();
    }

    return (byte);
}

void i2c_write_bytes(uint8_t address, uint8_t reg, uint8_t *data, uint8_t length)
{
    uint8_t i;

    arbitrationWasLost = 0;

    i2c_write_byte(1, 0, address);          // 7 bit address followed by a 0 for a write
    i2c_write_byte(0, 0, reg);             // select register

    for (i = 0; i < length; i++)
    {
        i2c_write_byte(0, (i == (length - 1)), data[i]);       // write data
    }
}

void i2c_read_register_bytes(uint8_t address, uint8_t reg, uint8_t *data, uint8_t length)
{
    uint8_t i;

    arbitrationWasLost = 0;

    i2c_write_byte(1, 0, address);          // 7 bit address followed by a 0 for a write
    i2c_write_byte(0, 1, reg);              // select register
    i2c_write_byte(1, 0, address | 1);      // 7 bit address followed by a 1 for a read

    for (i = 0; i < length; i++)
    {
        data[i] = i2c_read_byte(0, (i == (length - 1)));       // read data
    }
}
