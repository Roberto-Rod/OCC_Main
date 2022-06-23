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
1.      1.0     BC                      Initial Version
*******************************************************************************/

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "RTC_Driver.h"
/*******************************************************************************
                             Variables
*******************************************************************************/

/******************************************************************************
 *Function: double RTCInit(void)
 Remarks: See header file for definitions
 ******************************************************************************/
uint16_t RTCInit(void)
{  
    uint16_t rtc_error = NO_ERROR;
    _I2C_BUFFER rtc_i2cBuffer;
    
    // Oscillator enable
    rtc_i2cBuffer.Byte[0] = RTC_SECONDS_ADDR;
    rtc_i2cBuffer.Byte[1] = OSC_ENABLE;
    if( !I2C_MasterWriteBytes( RTC_PORT , RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
    {
        rtc_error = RTC_OSC_ENABLE_ERROR;
    }
    else
    { 
        // Calibration 
        rtc_i2cBuffer.Byte[0] = RTC_CAL_CONTROL_ADDR;
        rtc_i2cBuffer.Byte[1] = CONTROLBITS;
        if( !I2C_MasterWriteBytes( RTC_PORT , RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ) )
        {   
            rtc_error = RTC_CONBITS_ERROR;
        }
    }
     
    return rtc_error;
}
/******************************************************************************
 * Function: double SetDateTime( uint8_t* datetime )
 * Remarks: See header file for details
 ******************************************************************************/
uint16_t SetDateTime( uint8_t* datetime )
{
    uint16_t rtc_error = RTC_NO_ERROR;
    _I2C_BUFFER rtc_i2cBuffer;
    
    //Set the seconds register
    rtc_i2cBuffer.Byte[0] = RTC_SECONDS_ADDR;
    rtc_i2cBuffer.Byte[1] = bin2bcd(datetime[0]);
    
    if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
    {
        rtc_error = RTC_SET_TIME_ERROR;
    }
    else
    {
        //Set the minutes register
        rtc_i2cBuffer.Byte[0] = RTC_MINUTES_ADDR;
        rtc_i2cBuffer.Byte[1] = bin2bcd(datetime[1]);
        
        if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
        {
            rtc_error = RTC_SET_TIME_ERROR;
        }
        else
        {
            //Set the hours register
            rtc_i2cBuffer.Byte[0] = RTC_HOURS_ADDR;
            rtc_i2cBuffer.Byte[1] = bin2bcd(datetime[2]);
            
            if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
            {
                rtc_error = RTC_SET_TIME_ERROR;
            }
            else
            {

#ifdef RTC_SET_DAYS    
                //Set the days register 
                rtc_i2cBuffer.Byte[0] = RTC_DAY_ADDR;
                rtc_i2cBuffer.Byte[1] = bin2bcd(datetime[3]);
                if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
                {
                    return RTC_SET_DATE_ERROR;
                }
                else
                {
#endif
                    //Set the dates register
                    rtc_i2cBuffer.Byte[0] = RTC_DATE_ADDR;
                    rtc_i2cBuffer.Byte[1] = bin2bcd(datetime[3]);

                    if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
                    {
                        rtc_error = RTC_SET_DATE_ERROR;
                    }
                    else
                    {
                        //Set the months register
                        rtc_i2cBuffer.Byte[0] = RTC_MONTH_ADDR;
                        rtc_i2cBuffer.Byte[1] = bin2bcd(datetime[4]);

                        if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
                        {
                            rtc_error = RTC_SET_DATE_ERROR;
                        }
                        else
                        {
                            //Set the years register
                            rtc_i2cBuffer.Byte[0] = RTC_YEAR_ADDR;
                            rtc_i2cBuffer.Byte[1] = bin2bcd(datetime[5]);

                            if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 2 ))
                            {
                                rtc_error = RTC_SET_DATE_ERROR;
                            }
                        }
                    }
#ifdef RTC_SET_DAYS
                }
#endif               
            }
        }
    }
    
    return rtc_error;
}
/******************************************************************************
 * Function: double GetDateTime(void)
 * Remarks: See header file for details
 ******************************************************************************/
uint16_t GetDateTime( TIME* time, DATE* date )
{  
    uint16_t rtc_error = NO_ERROR;
    _I2C_BUFFER rtc_i2cBuffer;
    
    //Set the initial read address to seconds register
    rtc_i2cBuffer.Byte[0] = RTC_SECONDS_ADDR;
    if( !I2C_MasterWriteBytes( RTC_PORT, RTC_ADDR, (uint8_t*) &rtc_i2cBuffer, 1))
    {
        // If unsuccessful
        rtc_error = RTC_GET_TIME_ERROR;
    }
    else
    {
        // Read all 7 registers one after another
        uint8_t datetime[7];
        
        if(!I2C_MasterReadBytes( RTC_PORT, RTC_ADDR, &datetime[0], 7 ))
        {
            // If unsuccessful
            rtc_error = RTC_GET_TIME_ERROR;
        }
        else
        {
            // Mask of the enable bit and read the seconds value
            time->Seconds = bcd2bin(datetime[0] & 0x7F); 

            time->Minutes = bcd2bin(datetime[1]); 
            time->Hours = bcd2bin(datetime[2]);
            date->Day = bcd2bin(datetime[4]);
            date->Month = bcd2bin(datetime[5]);
            date->Year = bcd2bin(datetime[6]);
        }
    }
     
    return rtc_error;
}
/******************************************************************************
 * Function: uint8_t bin2bcd(uint8_t val)
 * Remarks: See header file for details
 ******************************************************************************/
uint8_t bin2bcd(uint8_t val)
{
    // convert binary value to binary coded decimal and return
    return val + 6 * (val/10);
}
/******************************************************************************
 * Function: uint8_t bcd2bin(uint8_t val)
 * Remarks: See header file for details
 ******************************************************************************/
uint8_t bcd2bin(uint8_t val)
{
    // convert binary coded decimal to binary and return
    return val - 6 * (val >> 4);
}
/******************************************************************************/
/******************************* EOF ******************************************/
/******************************************************************************/