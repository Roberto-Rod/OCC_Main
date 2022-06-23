#include "mbed.h"

#ifndef DEFS_H
#define DEFS_H


//--------------------------------------------
//application version
//--------------------------------------------
#define VERSION_MAJOR        (0)
#define VERSION_MINOR        (1)

//--------------------------------------------
//useful test overrides
//--------------------------------------------
#ifdef TEST
#define FOREVER              (0)
#define STATIC
#define INLINE
#else
#define FOREVER              (1)
#define STATIC               static
#define INLINE               inline
#endif

//--------------------------------------------
//Add simple types that aren't standard C
//--------------------------------------------
typedef unsigned char BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL 0
#endif

//--------------------------------------------
//Add a helpful status type and codes
//--------------------------------------------
typedef int     STATUS_T;
typedef uint8_t PARAM_ID_T;

#define STATUS_OK                (0)
#define STATUS_UNKNOWN_CMD       (1)
#define STATUS_MISSING_ARG       (2)
#define STATUS_EXTRA_ARG         (3)
#define STATUS_INVALID_ARG       (4)
#define STATUS_TOO_LOW           (5)
#define STATUS_TOO_HIGH          (6)
#define STATUS_BAD_MSG           (7)

#define STATUS_NOT_ARMED         (10)
#define STATUS_NONE_YET          (11)
#define STATUS_CAPTURING         (12)
#define STATUS_OVERFLOW          (13)
#define STATUS_MISSING_DATA      (14)
#define STATUS_ALREADY_TRIGGERED (15)
#define STATUS_ALREADY_ARMED     (16)
#define STATUS_ALREADY_COMPLETE  (17)

#define STATUS_INVALID_PARAM     (20)
#define STATUS_TOO_MANY_PARAMS   (21)

#define STATUS_NOT_INITIALIZED   (30)
#define STATUS_NULL_POINTER      (31)

#define STATUS_UART_BAD_PORT     (40)

#define STATUS_UNKNOWN_ERR       (255)

//--------------------------------------------
//Configuration options
//--------------------------------------------
#ifdef  TEST
#define BUFFER_MAX_BYTES      4096
#else
#define BUFFER_MAX_BYTES      128
#endif

#define DIGITAL_NUM_CHANS     6
#define ANALOG_NUM_CHANS      6

//--------------------------------------------
// Clock Configuration
//--------------------------------------------
#define XTAL                 (12000000UL)
#define OSC_CLK              (      XTAL)
#define PLL0CFG_Val          (0x0000000B)
#define PLL1_SETUP           (         0)
#define PLL1CFG_Val          (0x00000000)
#define CCLKCFG_Val          (0x00000002)
#define USBCLKCFG_Val        (0x00000005)

#define MAIN_TICK_MSEC       (50)

// F_cco0 = (2 * M * F_in) / N
#define __M               (((PLL0CFG_Val      ) & 0x7FFF) + 1)
#define __N               (((PLL0CFG_Val >> 16) & 0x00FF) + 1)
#define __FCCO(__F_IN)    ((2ULL * __M * __F_IN) / __N)
#define __CCLK_DIV        (((CCLKCFG_Val      ) & 0x00FF) + 1)

#define __CORE_CLK (__FCCO(OSC_CLK) / __CCLK_DIV)


#endif //DEFS_H
#ifndef _UTILS_H
#define _UTILS_H

#define DIMENSION_OF(a)    (sizeof(a) / sizeof(a[0]))

#define BIT_TO_MASK(bit)   (1u << bit)
#define BIT_TO_MASK8(bit)  (uint8_t)(1u << bit)
#define BIT_TO_MASK16(bit) (uint16_t)(1u << bit)

#define UINT32_BYTE3(w)    ((w >> 24) & 0x00FF)
#define UINT32_BYTE2(w)    ((w >> 16) & 0x00FF)
#define UINT32_BYTE1(w)    ((w >>  8) & 0x00FF)
#define UINT32_BYTE0(w)    ((w      ) & 0x00FF)

#define BYTE0_TO_UINT32(b) ((uint32_t)(b) << 24)
#define BYTE1_TO_UINT32(b) ((uint32_t)(b) << 16)
#define BYTE2_TO_UINT32(b) ((uint32_t)(b) <<  8)
#define BYTE3_TO_UINT32(b) ((uint32_t)(b)      )

void HexToBin(const char* Src, char* Dst, uint8_t Pairs);
void BinToHex(const char* Src, char* Dst, uint8_t Bytes);

#define DIV_ROUND_UP(n,d) ((n + (d - 1)) / d)

//This is useful for setting the pinsel and pinmode config registers
#define MASK_BIT_PAIR(bit, val)     (val << ((bit % 16) << 1))


static inline uint32_t MASK_RANGE(uint32_t b1, uint32_t b2)
{
    return ((2 << b2) - 1) - ((1 << b1) - 1);
}

static inline uint32_t MASK_RANGE_PAIRS(uint32_t b1, uint32_t b2, uint32_t val)
{
    uint32_t i;
    uint32_t retval = 0;

    for (i = b1; i <= b2; i++)
        retval |= MASK_BIT_PAIR(i, val);

    return retval;
}

static inline uint8_t COUNT_HIGH_BITS8(uint8_t b)
{
    b -= ((b >> 1) & 0x55);
    b  = ((b >> 2) & 0x33) + (b & 0x33);
    b  = ((b >> 4) + b) & 0x0F;
    return b;
}


#endif // _UTILS_H
#ifndef _MAIN_H
#define _MAIN_H

int main(void);

#endif // _MAIN_H

void HexToBin(const char* Src, char* Dst, uint8_t Pairs)
{
    uint8_t i;

    for (i=0; i < Pairs; i++)
    {
        if ((*Src >= '0') && (*Src <= '9'))
            *Dst = (*Src++ - '0') << 4;
        else if ((*Src >= 'A') && (*Src <= 'F'))
            *Dst = (*Src++ +10 - 'A') << 4;

        if ((*Src >= '0') && (*Src <= '9'))
            *Dst++ |= (*Src++ - '0');
        else if ((*Src >= 'A') && (*Src <= 'F'))
            *Dst++ |= (*Src++ +10 - 'A');
    }
    *Dst = 0;
}

void BinToHex(const char* Src, char* Dst, uint8_t Bytes)
{
    uint8_t i;
    char Nibble;

    for (i=0; i < Bytes; i++)
    {
        Nibble = *Src >> 4;
        if (Nibble < 10)
            *Dst++ = (Nibble + '0');
        else
            *Dst++ = (Nibble - 10 + 'A');

        Nibble = *Src & 0x0F;
        if (Nibble < 10)
            *Dst++ = (Nibble + '0');
        else
            *Dst++ = (Nibble - 10 + 'A');

        Src++;
    }
    *Dst = 0;
}

//
// NOTE: Do not attempt to test main() directly.
//       See Lecture 9 for how to handle this special case.
// ========================================================
//

#ifndef TEST
int main(void)
#else
int TestableMain(void)
#endif
{
    return 0;
}
