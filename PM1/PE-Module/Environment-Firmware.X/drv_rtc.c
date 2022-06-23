/* ************************************************************************** */
/** @file
 *   Library Handling Power Switch
 *
 *  @Company
 *   Occuity Limited
 *
 *  @File Name
 *   drv_rtc.c
 *
 *  @Description
 *   Driver for the DS1340 Real Time Clock chip file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "drv_rtc.h"
#include "debug.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/****************************************************************************
  Section: Global Variables
  ***************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

static uint8_t convertToBcd(uint8_t byte);
static void process_received_time(RTCCFORM *time, int16_t *write_rtcc_buffer);
static void read_from_buffer(RTCCFORM *time, int16_t *read_rtcc_buffer);
static void write_to_buffer(RTCCFORM *current_time, int16_t *write_rtcc_buffer);

/* ************************************************************************** */
/**
 * @brief            Convert binary data to binary-coded decimal data.
 *
 * @note             None.
 *
 * @param[in]        byte Byte to convert.
 *
 * @return           uint8_t bcd value.
 */
/* ************************************************************************** */
static uint8_t convertToBcd(uint8_t byte)
{
    uint8_t bcd;

    bcd = (byte % 10) | ((byte / 10) << 4);

    return (bcd);
}

/* ************************************************************************** */
/**
 * @brief            Converts RTCCFORM time/date structure to BCD.
 *
 * @note             None.
 *
 * @param[in/out]    time Time/date information to convert.
 *
 * @return           None.
 */
/* ************************************************************************** */
static void convertStructToBCD(RTCCFORM * time)
{
    time->date = convertToBcd(time->date);
    time->day = convertToBcd(time->day);
    time->hour = convertToBcd(time->hour);
    time->minute = convertToBcd(time->minute);
    time->month = convertToBcd(time->month);
    time->second = convertToBcd(time->second);
    time->tenth_second = convertToBcd(time->tenth_second);
    time->year = convertToBcd(time->year);
}

/* ************************************************************************** */
/**
 * @brief            Converts byte from BCD format to binary.
 *
 * @note             None.
 *
 * @param[in]        time Byte to convert.
 *
 * @return           uint8_t converted byte.
 */
/* ************************************************************************** */
static uint8_t convertFromBcd(uint8_t byte)
{
    uint8_t binary;

    binary = byte >> 4;
    binary *= 10;
    binary += byte & 0xf;

    return (binary);
}

/* ************************************************************************** */
/**
 * @brief            Converts RTCCFORM time/date structure from BCD.
 *
 * @note             None.
 *
 * @param[in/out]    time Time/date information to convert.
 *
 * @return           None.
 */
/* ************************************************************************** */
static void convertStructFromBCD(RTCCFORM * time)
{
    time->date = convertFromBcd(time->date);
    time->day = convertFromBcd(time->day);
    time->hour = convertFromBcd(time->hour);
    time->minute = convertFromBcd(time->minute);
    time->month = convertFromBcd(time->month);
    time->second = convertFromBcd(time->second);
    time->tenth_second = convertFromBcd(time->tenth_second);
    time->year = convertFromBcd(time->year);
}

/* ************************************************************************** */
/**
 * @Function:        static void process_received_time(RTCCFORM* current_time, int16_t *read_rtcc_buffer)
 *
 * @Summary:         Processing date received from RTC
 *
 * @Description:     Reading date from RTC registers and processing
 *
 * @Param[in/out]:   RTCCFORM *current_time, int16_t *read_rtcc_buffer, RTCC registers
 *
 * @Returns:         None.
 */
/* ************************************************************************** */
static void process_received_time(RTCCFORM* current_time, int16_t *read_rtcc_buffer)
{
    read_rtcc_buffer[0] = TIMEH;        //read hour, min
    read_rtcc_buffer[1] = TIMEL;        //read sec
    read_rtcc_buffer[2] = DATEH;        //read year, month
    read_rtcc_buffer[3] = DATEL;        //read day, day of week

    read_from_buffer(current_time, read_rtcc_buffer);
}
/* ************************************************************************** */
/**
 * @Function:        static void read_from_buffer(RTCCFORM *current_time, int16_t *read_rtcc_buffer)
 *
 * @Summary:         Write data from buffer to the current time structure
 *
 * @Description:     Write data from buffer consisting of data form RTCC registers to
 *                   current time structure
 *
 * @Param[in/out]:   RTCCFORM *current_time, int16_t *read_rtcc_buffer
 *
 * @Returns:         None.
 */
/* ************************************************************************** */
static void read_from_buffer(RTCCFORM *current_time, int16_t *read_rtcc_buffer)
{
    current_time->tenth_second = 0;
    current_time->second = read_rtcc_buffer[1]>>8 & 0x7f;
    current_time->minute = read_rtcc_buffer[0] & 0x7f;
    current_time->hour = read_rtcc_buffer[0]>>8 & 0x3f;
    current_time->day = read_rtcc_buffer[3] & 0x7;
    current_time->date = read_rtcc_buffer[3]>>8& 0x3f;
    current_time->month = read_rtcc_buffer[2]&0x1f;
    current_time->year = read_rtcc_buffer[2]>>8;

//    dprintf_colour("[CYAN]Reading RTCC:[WHITE]\r\n");
//    dprintf_colour("[CYAN]w[0] TIMEH: 0x%04x[WHITE]\r\n", read_rtcc_buffer[0]);
//    dprintf_colour("[CYAN]w[1] TIMEL: 0x%04x[WHITE]\r\n", read_rtcc_buffer[1]);
//    dprintf_colour("[CYAN]w[2] DATEH: 0x%04x[WHITE]\r\n", read_rtcc_buffer[2]);
//    dprintf_colour("[CYAN]w[3] DATEL: 0x%04x[WHITE]\r\n", read_rtcc_buffer[3]);
}
/* ************************************************************************** */
/**
 * @Function:        static void write_to_buffer(RTCCFORM *time, int16_t *write_rtcc_buffer)
 *
 * @Summary:         Read data from buffer to the current time structure
 *
 * @Description:     Read data from current time structure to buffer which set RTCC registers
 *
 * @Param[in/out]:   RTCCFORM *time, int16_t *write_rtcc_buffer RTCCFORM *current_time,
 *                   int16_t *read_rtcc_buffer
 *
 * @Returns:         None.
 */
/* ************************************************************************** */
static void write_to_buffer(RTCCFORM *time, int16_t *write_rtcc_buffer)
{
  write_rtcc_buffer[0] = time->hour << 8 | time->minute;   //update hour, min
  write_rtcc_buffer[1] = time->second << 8;                //update sec
  write_rtcc_buffer[2] = time->year << 8 |  time->month;   //update year, month
  write_rtcc_buffer[3] = time->date << 8 | time->day;      //update day, day of week
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Global Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/**
 * @Function:        void RTCC_Initialize(void)
 *
 * @Summary:         Initialize RTCC for time counting
 *
 * @Description:     Initialize RTCC for time counting
 *
 * @Param[in/out]:   None.
 *
 * @Returns:         None.
 */
/* ************************************************************************** */
void RTCC_Initialize(void)
{
    _RTCCMD = 0;
    RTCCON1Lbits.WRLOCK = 0;         //Enable RTCC modification
    RTCCON1Lbits.RTCEN = 1;          //RTCC Enabled
    RTCCON1Lbits.RTCOE = 0;          //RTCC output disabled
}

/* ************************************************************************** */
/**
 * @Function:        static inline void nvm_delay(void)
 *
 * @Summary:         Provide delay after NMV unlock sequence
 *
 * @Description:     Provide delay after NMV unlock sequence
 *
 * @Param[in/out]:   None.
 *
 * @Returns:         None.
 */
/* ************************************************************************** */
static inline void __attribute__((optimize("-O0"))) nvm_delay(void)
{
    unsigned int i;
    for(i=0; i<10; i++)
    {
        asm("nop");
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/**
 * @Function:        void set_time(RTCCFORM *time)
 *
 * @Summary:         Update time
 *
 * @Description:     Update RTC time. Called in the main loop update to
 *                   the RTC driver chip
 *
 * @Param[in/out]:   RTCCFORM *time
 *
 * @Returns:         None.
 */
/* ************************************************************************** */
void set_time(RTCCFORM *time)
{
    convertStructToBCD(time);
    int16_t write_rtcc_buffer[4];
    write_to_buffer(time, write_rtcc_buffer);


    /* write the time to the RTC */
    // First, perform NVM unlock sequence
    if(RTCCON1Lbits.WRLOCK != 0)
    {
        asm volatile("mov #0x55, W0 \n"
                     "mov W0, NVMKEY \n"
                     "mov #0xAA, W1 \n"
                     "mov W1, NVMKEY \n");
        RTCCON1Lbits.WRLOCK = 0;        // Second, enable RTCC modification
        nvm_delay();
    }
    TIMEH=write_rtcc_buffer[0];           // Update hour, min
    TIMEL=write_rtcc_buffer[1];           // Update sec
    DATEH=write_rtcc_buffer[2];           // Update year, month
    DATEL=write_rtcc_buffer[3];           // Update day, day of week

    RTCCON1Lbits.WRLOCK = 1;        // Lastly, disable accidental RTCC modification (no NVM unlock sequence required)
}

/* ************************************************************************** */
/**
 * @Function:        void get_time()
 *
 * @Summary:         Show time
 *
 * @Description:     Show RTC time. Called in the main loop get time from
 *                   the RTC driver chip
 *
 * @Param[in/out]:   None.
 *
 * @Returns:         None.
 */
/* ************************************************************************** */
void get_time(RTCCFORM * current_time)
{
    int16_t read_rtcc_buffer[4];
    process_received_time(current_time, read_rtcc_buffer);
    convertStructFromBCD(current_time);

    //Testing Purpose

#ifdef DEBUG_PRINT_TIME

    dprintf_colour("[CYAN]Year: %02d[WHITE]\r\n", current_time->year);
    dprintf_colour("[CYAN]Month: %02d[WHITE]\r\n", current_time->month);
    dprintf_colour("[CYAN]Date: %02d[WHITE]\r\n", current_time->date);
    dprintf_colour("[CYAN]Day of wk: %02d[WHITE]\r\n", current_time->day );
    dprintf_colour("[CYAN]Hour: %02d[WHITE]\r\n", current_time->hour);
    dprintf_colour("[CYAN]Minute: %02d[WHITE]\r\n", current_time->minute);
    dprintf_colour("[CYAN]Second: %02d[WHITE]\r\n", current_time->second);
#endif


}

/****************************************************************************
 *  Testing Purpose
 * Function:
 *  set_time_manually(RTCCFORM *compilation_time)
 * Summary:
 *  Manually set current time
 * Description:
 *  Manually set current time
 * Precondition:
 *  None.
 * Input:
 *  RTCCFORM *manually_set_time
 * Returns:
 *  None
************************************************************************** */
void set_time_manually(RTCCFORM *manually_set_time)
{
    // 12/11/2020 Thursday 15:23:45
    manually_set_time->year = 20;//0x20; //2020
    manually_set_time->month = 11;//0x11; //11
    manually_set_time->date = 12;//0x12; //12
    manually_set_time->day = 4;//0x4; //Thu
    manually_set_time->hour = 15;//0x15; //15
    manually_set_time->minute = 23;//0x23; //23
    manually_set_time->second = 45;//0x45; //45
    manually_set_time->tenth_second = 20;//0x20; //20
}
/**
 End of File
*/
