/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   
 File Name: RTC_Driver.h   
 Processor: PIC32MZ (Harmony V1.07)
 Hardware:  Targeted for DS1340 Real Time Clock device
 Assembler: XC32-gcc
 Linker:    XC32-ld
 
 Description: This driver header file consists of all attributes and methods
 * required to drive and control the DS1340 RTC device.  
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     BC                     Initial Version
*******************************************************************************/

#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "Error_Functions.h"
#include "I2C_Common.h"
#include "Delay.h"

typedef enum
{
    RTC_NO_ERROR = 0,
    RTC_OSC_ENABLE_ERROR,
    RTC_CONBITS_ERROR,  
    RTC_SET_TIME_ERROR,  
    RTC_SET_DATE_ERROR,  
    RTC_GET_TIME_ERROR,
    RTC_GET_DATE_ERROR
} RTC_ERRORS;

/*******************************************************************************
                            Macros
*******************************************************************************/
//Device instance
#define RTC_PORT 1 

//Slave device address
#define RTC_ADDR     0xD0 

//#define RTC_SET_DAYS

//Device register addresses
#define RTC_SECONDS_ADDR        0x00 
#define RTC_MINUTES_ADDR        0x01
#define RTC_HOURS_ADDR          0x02
#define RTC_DAY_ADDR            0x03
#define RTC_DATE_ADDR           0x04
#define RTC_MONTH_ADDR          0x05
#define RTC_YEAR_ADDR           0x06
#define RTC_CAL_CONTROL_ADDR    0x07
#define RTC_OSC_FLAG_ADDR       0x09

#define OSC_ENABLE              0b00000000 // enable oscillator
#define OSC_DISABLE             0b10000000 // disable oscillator
#define SET_SECONDS             0b00000000 // 0 to 59 seconds
#define SET_MINUTES             0b00000000 // 0 to 59 minutes
#define SET_HOURS               0b00001111 // 0 to 23 hours
// Set the date month and year as 1st November 2016
#define SET_DAYS                0b00000111 // 1 to 7 days
#define SET_DATES               0b00000001 // 1 to 31 dates
#define SET_MONTHS              0b00001011 // 1 to 12 months
#define SET_YEARS               0b00010110 // 0 to 99 years

#define CONTROLBITS             0b10000000 // cal control register bits for power up only
/*******************************************************************************
                              Variables
*******************************************************************************/
typedef struct
{
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
    
}DATE;

typedef struct 
{
    uint8_t Hours;
    uint8_t Minutes;
    uint8_t Seconds; 
    
}TIME;
/*******************************************************************************
                            Function Prototypes
*******************************************************************************/
/*******************************************************************************
 * Function:        uint16_t RTCInit(void)
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         Error code
 *
 * Side Effects:    None
 *
 * Overview:        Initialises and configures the real time clock drivers 
 *
 * Notes:           None
 ******************************************************************************/
uint16_t RTCInit(void);

/*******************************************************************************
 * Function:        uint16_t SetDateTime(uint8_t sec, uint8_t min, uint8_t hrs, uint8_t dt, uint8_t mt, uint8_t yr)
 *
 * Precondition:    Successful initialisation of the RTC device
 *
 * Input:           uint8_t* datetime: Pointer to 6 byte array 
 *                  datetime[0]:    seconds
 *                  datetime[1]:    minutes 
 *                  datetime[2]:    hours 
 *                  datetime[3]:    date 
 *                  datetime[4]:    month 
 *                  datetime[5]:    year
 *
 * Output:          None
 *
 * Returns:         Error code
 *
 * Side Effects:    None
 *
 * Overview:        Initialises and sets the date and time registers  
 *
 * Notes:           None
 ******************************************************************************/
uint16_t SetDateTime( uint8_t* datetime );

/*******************************************************************************
 * Function:        uint16_t GetDateTime(void)
 *
 * Precondition:    Successful initialisation of the RTC device
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         Error code
 *
 * Side Effects:    None
 *
 * Overview:        Retrieves the date and time from respective registers 
 *
 * Notes:           None
 ******************************************************************************/
uint16_t GetDateTime( TIME* time, DATE* date; );

/*******************************************************************************
 * Function:        uint8_t bcd2bin(uint8_t val)
 *
 * Precondition:    None
 *
 * Input:           uint8_t val
 *
 * Output:          uint8_t bin: binary equivalent of BCD value
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        Converts the binary coded decimal value into binary equivalent 
 *
 * Notes:           None
 ******************************************************************************/
uint8_t bcd2bin(uint8_t val);

/*******************************************************************************
 * Function:        uint8_t bin2bcd(uint8_t val)
 *
 * Precondition:    None
 *
 * Input:           uint8_t val
 *
 * Output:          uint8_t bcd: binary coded decimal equivalent of a binary value
 *
 * Returns:         Error code
 *
 * Side Effects:    None
 *
 * Overview:        Retrieves the date and time from respective registers 
 *
 * Notes:           None
 ******************************************************************************/
uint8_t bin2bcd(uint8_t val);
        
#endif /* _RTC_DRIVER_H */
/*******************************************************************************
 End of File
 */

