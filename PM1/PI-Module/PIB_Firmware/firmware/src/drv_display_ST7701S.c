/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_display_ST7701S.c

  @Summary
    Driver for the ST7701 LCD drive.

  @Description
    Initialises the ST7701 LCD drive chip.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "definitions.h"
#include "Drivers/delay.h"

#define DISPLAY_CS      LATBbits.LATB5      // display chip select
#define DISPLAY_DC      LATBbits.LATB12     // display data / command
#define DISPLAY_SDI     LATBbits.LATB2      // display SPI data input
#define DISPLAY_SCK     LATDbits.LATD15     // display SPI clock
#define DISPLAY_RS      LATAbits.LATA1      // display reset

#define SPI_DELAY       50

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

static void write_byte(uint8_t byte);
static void write_display(uint8_t byte, uint8_t dc);
static void write_command(uint8_t command);
static void write_data(uint8_t data);

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/**************************************************************************** */
/* Function Name: write_byte                                                  */
/*                Write a byte to the ST7701S LCD display by bit-banging      */
/*                the SPI interface                                           */
/* @param[in] byte : byte to write to the display                             */
/* @retval None                                                               */
/* ************************************************************************** */
static void write_byte(uint8_t byte)
{  
    uint8_t bit; 
   
    for (bit = 0; bit < 8; bit++)			
    {  
	    if ((byte & 0x80) != 0)
        {
            DISPLAY_SDI = 1;
        }
        else
        {
            DISPLAY_SDI = 0;
        }
      
        byte <<= 1; 
      
	    DISPLAY_SCK = 0;
        DelayNs(SPI_DELAY);  
        DISPLAY_SCK = 1; 
        DelayNs(SPI_DELAY);       
    }
}
/* End of function write_byte                                                 */

/**************************************************************************** */
/* Function Name: write_display                                               */
/*                Write a command or data to the ST7701S LCD display by       */
/*                by bit-banging the SPI interface                            */
/* @param[in] byte : byte to write to the display                             */
/* @param[in] dc : 0 for command, 1 for data                                  */
/* @retval None                                                               */
/* ************************************************************************** */
static void write_display(uint8_t byte, uint8_t dc)
{
    DISPLAY_CS = 0; 
    DISPLAY_DC = dc;
    DelayNs(10);

	write_byte(byte);

    DISPLAY_CS = 1; 
}
/* End of function write_display                                              */

/**************************************************************************** */
/* Function Name: write_command                                               */
/*                Write a command to the ST7701S LCD display by bit-banging   */
/*                the SPI interface                                           */
/* @param[in] command : command to write to the display                       */
/* @retval None                                                               */
/* ************************************************************************** */
static void write_command(uint8_t command)
{
    //dprintf_colour("[YELLOW]write_command(0x%02x)[WHITE]\r\n", command);

    write_display(command, 0);
}
/* End of function write_command                                              */

/**************************************************************************** */
/* Function Name: write_data                                                  */
/*                Write a data byte to the ST7701S LCD display by bit-banging */
/*                the SPI interface                                           */
/* @param[in] data : data to write to the display                             */
/* @retval None                                                               */
/* ************************************************************************** */
static void write_data(uint8_t data)
{
    //dprintf_colour("[GREEN]write_data(0x%02x)[WHITE]\r\n", data);

    write_display(data, 1);
}
/* End of function write_data                                                 */

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */


/**************************************************************************** */
/* Function Name: ST7701S_Init                                                */
/*                Initialise the ST7701S LCD display                          */
/* @retval None                                                               */
/* ************************************************************************** */
void ST7701S_Init(void)
{
    uint16_t i;
    
    // reset LCD driver 
    DISPLAY_RS = 1; 
    DelayMs(1);                 // delay 1ms 
    DISPLAY_RS = 0; 
    DelayMs(10);                // delay 10ms - this delay time is necessary 
    DISPLAY_RS = 1; 
    DelayMs(120);               // delay 120ms 

    // initialisation sequence 
    write_command(0x11);        // exit sleep 
    DelayMs(120); 

    const uint16_t init[] = {
            // Bank select
            0x1FF, 0x77, 0x01, 0x00, 0x00, 0x13,
            0x1EF, 0x08,
            // Bank select
            0x1FF, 0x77, 0x01, 0x00, 0x00, 0x10,
            0x1C0, 0x63, 0x00,                                                                                          // display line setting
            0x1C1, 13, 2,                                                                                               // porch control
            0x1C2, 0x37, 0x08,                                                                                          // inversion selection and frame rate control
            0x1C3, 0x80, 1, 13,                                                 
//            0x1C5, 0x00, 0x00, 0x54, 0x01,                                                                            // Partial mode on
//            0x112,       
//            0x1C7, 0x00,
//            0x1CC, 0x10,                                                                                                // ?
            0x1B0, 0x02, 0x13, 0x1B, 0x0D, 0x10, 0x05, 0x08, 0x07, 0x07, 0x24, 0x04, 0x11, 0x0E, 0x2C, 0x33, 0x1D,      // positive voltage gamma control
            0x1B1, 0x05, 0x13, 0x1B, 0x0D, 0x11, 0x05, 0x08, 0x07, 0x07, 0x24, 0x04, 0x11, 0x0E, 0x2C, 0x33, 0x1D,      // negative voltage gamma control
            // Bank select
            0x1FF, 0x77, 0x01, 0x00, 0x00, 0x11, 
            0x1B0, 0xB5,                                                                                                // 
            0x1B1, 0x6F, 
            0x1B2, 0x85,
            0x1B3, 0x80, 
            0x1B5, 0x4C, 
            0x1B7, 0x85, 
            0x1B8, 0x30,
            0x1BB, 0x00,
            0x1C1, 0x08, 
            0x1C2, 0x08, 
            0x1D0, 0x88, 
            0x1E0, 0x00, 0x00, 0x02,
            0x1E1, 0x01, 0xA0, 0x03, 0xA0, 0x02, 0xA0, 0x04, 0xA0, 0x00, 0x44, 0x44,     
            0x1E2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x1E3, 0x00, 0x00, 0x33, 0x33, 
            0x1E4, 0x44, 0x44,
            0x1E5, 0x01, 0x2b, 0xA0, 0x80, 0x03, 0x2d, 0xA0, 0x80, 0x05, 0x2f, 0xA0, 0x80, 0x07, 0x31, 0xA0, 0x80, 
            0x1E6, 0x00, 0x00, 0x33, 0x33,
            0x1E7, 0x44, 0x44, 
            0x1E8, 0x02, 0x2c, 0xA0, 0x80, 0x04, 0x2e, 0xA0, 0x80, 0x06, 0x30, 0xA0, 0x80, 0x08, 0x32, 0xA0, 0x80, 
            0x1EB, 0x00, 0x00, 0xE4, 0xE4, 0x44, 0x00, 0x40, 
            0x1ED, 0xFF, 0xF0, 0x17, 0x65, 0x4A, 0xBF, 0xAF, 0xFF, 0xFF, 0xFA, 0xFB, 0xA4, 0x56, 0x71, 0x0F, 0xFF, 
            // Bank select
            0x1FF, 0x77, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x13A, 0x50,
            0x136, 0x0C,
            0x1E3, 0x01,
            0x138, 0x00,
//            0x134, 0x00,
//            0x112, 0x00,
            0xFFFF};

    /* write commands and data to the ST7701S */
    /* commands have the 9th bit set, data does not */
    i = 0;
    while (init[i] != 0xFFFFu)
    {
        if ((init[i] & 0x100) != 0)
        {
            write_command(init[i]);
        }
        else
        {
            write_data(init[i]);
        }

        i++;
    }
    write_command(0x28);	// display off - required for smooth power-up
    write_command(0x10);
}

void drv_display_set_enable(void)
{
    write_command(0x11);	// display wakeup
    write_command(0x29);    // display on
}

void drv_display_set_disable(void)
{
    write_command(0x28);    // display off
    write_command(0x10);	// display sleep
}
/* End of function ST7701S_Init                                               */

/**************************************************************************** */
/* Function Name: ST7701S_Init                                                */
/*                Initialise the ST7701S LCD display                          */
/* @retval None                                                               */
/* ************************************************************************** */
//void ST7701S_Init_2(void)
//{
//    // reset LCD driver 
//    DISPLAY_RS = 1; 
//    DelayMs(1);                 // delay 1ms 
//    DISPLAY_RS = 0; 
//    DelayMs(10);                // delay 10ms - this delay time is necessary 
//    DISPLAY_RS = 1; 
//    DelayMs(120);               // delay 120ms 
//
//    // initialisation sequence 
//    write_command(0x11);        // exit sleep 
//    DelayMs(120); 
//
//    write_command(0xFF);
//    write_data(0x77);
//    write_data(0x01);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x13);
//
//    write_command(0xEF);
//    write_data(0x08);
//
//    write_command(0xFF);
//    write_data(0x77);
//    write_data(0x01);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x10);
//
//    write_command(0xC0);
//    write_data(0x63);
//    write_data(0x00);
//
//    write_command(0xC1);
//    write_data(0x0D);
//    write_data(0x02);
//
//    write_command(0xC2);
//    write_data(0x37);
//    write_data(0x08);
//
//    write_command(0xCC);
//    write_data(0x10);
//
//    write_command(0xB0);
//    write_data(0x02);
//    write_data(0x13);
//    write_data(0x1B);
//    write_data(0x0D);
//    write_data(0x10);
//    write_data(0x05);
//    write_data(0x08);
//    write_data(0x07);
//    write_data(0x07);
//    write_data(0x24);
//    write_data(0x04);
//    write_data(0x11);
//    write_data(0x0E);
//    write_data(0x2C);
//    write_data(0x33);
//    write_data(0x1D);
//
//    write_command(0xB1);
//    write_data(0x05);
//    write_data(0x13);
//    write_data(0x1B);
//    write_data(0x0D);
//    write_data(0x11);
//    write_data(0x05);
//    write_data(0x08);
//    write_data(0x07);
//    write_data(0x07);
//    write_data(0x24);
//    write_data(0x04);
//    write_data(0x11);
//    write_data(0x0E);
//    write_data(0x2C);
//    write_data(0x33);
//    write_data(0x1D);
//
//    write_command(0xFF);
//    write_data(0x77);
//    write_data(0x01);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x11);
//
//    write_command(0xB0);
//    write_data(0xB5);
//
//    write_command(0xB1);
//    write_data(0x6F);
//
//    write_command(0xB2);
//    write_data(0x85);
//
//    write_command(0xB3);
//    write_data(0x80);
//
//    write_command(0xB5);
//    write_data(0x4C);
//
//    write_command(0xB7);
//    write_data(0x85);
//
//    write_command(0xB8);
//    write_data(0x30);
//
//    write_command(0xBB);
//    write_data(0x00);
//
//    write_command(0xC1);
//    write_data(0x08);
//
//    write_command(0xC2);
//    write_data(0x08);
//
//    write_command(0xD0);
//    write_data(0x88);
//
//    write_command(0xE0);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x02);
//
//    write_command(0xE1);
//    write_data(0x01);
//    write_data(0xA0);
//    write_data(0x03);
//    write_data(0xA0);
//    write_data(0x02);
//    write_data(0xA0);
//    write_data(0x04);
//    write_data(0xA0);
//    write_data(0x00);
//    write_data(0x44);
//    write_data(0x44);
//
//    write_command(0xE2);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//
//    write_command(0xE3);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x33);
//    write_data(0x33);
//
//    write_command(0xE4);
//    write_data(0x44);
//    write_data(0x44);
//
//    write_command(0xE5);
//    write_data(0x01);
//    write_data(0x2b);
//    write_data(0xA0);
//    write_data(0x80);
//    write_data(0x03);
//    write_data(0x2d);
//    write_data(0xA0);
//    write_data(0x80);
//    write_data(0x05);
//    write_data(0x2f);
//    write_data(0xA0);
//    write_data(0x80);
//    write_data(0x07);
//    write_data(0x31);
//    write_data(0xA0);
//    write_data(0x80);
//
//    write_command(0xE6);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x33);
//    write_data(0x33);
//
//    write_command(0xE7);
//    write_data(0x44);
//    write_data(0x44);
//
//    write_command(0xE8);
//    write_data(0x02);
//    write_data(0x2c);
//    write_data(0xA0);
//    write_data(0x80);
//    write_data(0x04);
//    write_data(0x2e);
//    write_data(0xA0);
//    write_data(0x80);
//    write_data(0x06);
//    write_data(0x30);
//    write_data(0xA0);
//    write_data(0x80);
//    write_data(0x08);
//    write_data(0x32);
//    write_data(0xA0);
//    write_data(0x80);
//
//    write_command(0xEB);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0xE4);
//    write_data(0xE4);
//    write_data(0x44);
//    write_data(0x00);
//    write_data(0x40);
//
//    write_command(0xED);
//    write_data(0xFF);
//    write_data(0xF0);
//    write_data(0x17);
//    write_data(0x65);
//    write_data(0x4A);
//    write_data(0xBF);
//    write_data(0xAF);
//    write_data(0xFF);
//    write_data(0xFF);
//    write_data(0xFA);
//    write_data(0xFB);
//    write_data(0xA4);
//    write_data(0x56);
//    write_data(0x71);
//    write_data(0x0F);
//    write_data(0xFF);
//
//    write_command(0xFF);
//    write_data(0x77);
//    write_data(0x01);
//    write_data(0x00);
//    write_data(0x00);
//    write_data(0x00);
//
//    write_command(0x3A);
//    write_data(0x50);	
//
//    write_command(0x29);	// display on 
//}
/* End of function ST7701S_Init_2                                             */

/* *****************************************************************************
 End of File
 */
