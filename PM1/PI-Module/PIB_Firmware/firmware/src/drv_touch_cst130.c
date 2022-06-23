/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_touch_cst130.h

  @Summary
    Driver for the CST130 capacitive touch driver.

  @Description
    Driver for the CST130 capacitive touch driver.
 */
/* ************************************************************************** */

/* The TP_INT pin will continually generate interrupts at 100Hz while the panel is being touched */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "drv_touch_cst130.h"
#include "definitions.h"
#include "debug.h"
#include "drv_i2c3.h"
#include "Drivers/delay.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

#define DRV_TOUCH_I2C_INDEX                     0
#define DRV_TOUCH_I2C_SLAVE_ADDRESS             0x1a
#define DRV_TOUCH_INT_VALUE                     1
#define FINGER1_REGISTER_ADDRESS                0xd000

#define TOUCH_GONE_TIME_MS                      200          /* number of milliseconds without a touch before the touch is deemed to have gone */
#define SHORT_WAIT_MS                           20



typedef enum
{
    DRV_TOUCH_STATE_INIT,
    DRV_TOUCH_STATE_IDLE,
    DRV_TOUCH_STATE_WAIT_NO_INT,
} DRV_TOUCH_STATE;

typedef struct
{
    DRV_TOUCH_STATE state;
    uint8_t read_buffer[7];
    uint32_t timeout_start_time;
    uint16_t x;
    uint16_t y;
    bool touch_in_progress;
    uint32_t touch_up_start_time;
    
    void (*app_touch_callback)(uint16_t * context);
} DRV_TOUCH_OBJ;

static DRV_TOUCH_OBJ drv_touch = 
{
    .state = DRV_TOUCH_STATE_INIT,
    .touch_in_progress = false,
};

static void drv_cst130_touch_down(void);
static void drv_cst130_touch_up(void);
static void drv_cst130_touch_move(void);

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

static void drv_touch_process_data(void)
{
    bool previous_touch_in_progress;
    uint16_t x;
    uint16_t y;

    //dprintf_colour("[GREEN]read_buffer[0] = 0x%02x[WHITE]\r\n", drv_touch.read_buffer[0]);
    //dprintf_colour("[GREEN]read_buffer[1] = 0x%02x[WHITE]\r\n", drv_touch.read_buffer[1]);
    //dprintf_colour("[GREEN]read_buffer[2] = 0x%02x[WHITE]\r\n", drv_touch.read_buffer[2]);
    //dprintf_colour("[GREEN]read_buffer[3] = 0x%02x[WHITE]\r\n", drv_touch.read_buffer[3]);
    //dprintf_colour("[GREEN]read_buffer[4] = 0x%02x[WHITE]\r\n", drv_touch.read_buffer[4]);
    //dprintf_colour("[GREEN]read_buffer[5] = 0x%02x[WHITE]\r\n", drv_touch.read_buffer[5]);
    //dprintf_colour("[GREEN]read_buffer[6] = 0x%02x[WHITE]\r\n", drv_touch.read_buffer[6]);

    previous_touch_in_progress = drv_touch.touch_in_progress;

    if (0x6 == (drv_touch.read_buffer[0] & 0xf))
    {
        //dputs_colour("[CYAN]Finger 1 touch[WHITE]\r\n");
        drv_touch.touch_in_progress = true;
    }
    else
    {
        //dputs_colour("[CYAN]Finger 1 release[WHITE]\r\n");
        drv_touch.touch_in_progress = false;
    }

    x = drv_touch.read_buffer[1];
    x <<= 4;
    x |= (drv_touch.read_buffer[3] >> 4);

    y = drv_touch.read_buffer[2];
    y <<= 4;
    y |= (drv_touch.read_buffer[3] & 0xf);

    #ifdef DEBUG_TOUCH
    //dprintf_colour("[CYAN]x = %d, y = %d[WHITE]\r\n", drv_touch.x, drv_touch.y);
    #endif

    /* update the system */
    if (drv_touch.touch_in_progress)
    {
        if (previous_touch_in_progress)
        {
            if ((drv_touch.x != x) || (drv_touch.y != y))
            {
                drv_touch.x = x;
                drv_touch.y = y;

                drv_cst130_touch_move();
            }
        }
        else
        {
            drv_touch.x = x;
            drv_touch.y = y;            

            drv_cst130_touch_down();
                
            if (NULL != drv_touch.app_touch_callback)
            {
                (*drv_touch.app_touch_callback)((uint16_t *) &drv_touch);
            }            
        }

        drv_touch.touch_up_start_time = get_millisecond_timer_value();
    }
    else
    {
        drv_cst130_touch_up();
    }
}

static void show_touch_circle(laBool visible)
{
    #ifdef DEBUG_TOUCH
    if (visible)
    {
        laCircleWidget_SetOrigin(TouchTestCircleWidget, drv_touch.x, drv_touch.y);
    }

    laWidget_SetVisible((laWidget*)TouchTestCircleWidget, visible);
    #endif
}

static void drv_cst130_touch_down(void)
{
    #ifdef DEBUG_TOUCH
    dputs_colour("[MAGENTA]Touch down[WHITE]\r\n");
    #endif

    SYS_INP_InjectTouchDown(0, drv_touch.x, drv_touch.y);

    show_touch_circle(LA_TRUE);
}

static void drv_cst130_touch_up(void)
{
    #ifdef DEBUG_TOUCH
    dputs_colour("[MAGENTA]Touch up[WHITE]\r\n");
    #endif

    SYS_INP_InjectTouchUp(0, drv_touch.x, drv_touch.y);
    show_touch_circle(LA_FALSE);
}

static void drv_cst130_touch_move(void)
{
    #ifdef DEBUG_TOUCH    
    dputs_colour("[MAGENTA]Touch move[WHITE]\r\n");
    #endif

    SYS_INP_InjectTouchMove(0, drv_touch.x, drv_touch.y);
    show_touch_circle(LA_TRUE);
}

void drv_cst130_touch_callback_set(void (*app_touch_callback)(uint16_t* context))
{
    drv_touch.app_touch_callback = app_touch_callback;
}

void drv_cst130_touch_controller_task(void)
{
    if (drv_touch.touch_in_progress)
    {
        if ((get_millisecond_timer_value() - drv_touch.touch_up_start_time) > TOUCH_GONE_TIME_MS)
        {
            drv_touch.touch_in_progress = false;
            drv_cst130_touch_up();
        }
    }

    switch (drv_touch.state)
    {
        /* reset the CST130 touch driver */
        case DRV_TOUCH_STATE_INIT:
        {
//            dputs_colour("[GREEN]CST130 touch driver DRV_TOUCH_STATE_INIT[WHITE]\r\n");

            TP_INT_InputEnable();
            TP_INT_InterruptDisable();
            
            // hardware reset the touch panel
            TP_RESET_Clear();
            DelayMs(2);
            TP_RESET_Set();

            drv_touch.state = DRV_TOUCH_STATE_IDLE;
            break;
        }

        /* wait for a touch notification on the TP_INT input */
        case DRV_TOUCH_STATE_IDLE:
        {
            // poll notification pin
            if (TP_INT_Get() == DRV_TOUCH_INT_VALUE)
            {
//                dputs_colour("[CYAN]Touch detected[WHITE]\r\n");

                /* read the 7 bytes of data for the first finger from the touch driver chip */                
                DRV_I2C3_Read_Bytes_Word_Register(DRV_TOUCH_I2C_SLAVE_ADDRESS, FINGER1_REGISTER_ADDRESS, drv_touch.read_buffer, 7);
                drv_touch_process_data();
                drv_touch.state = DRV_TOUCH_STATE_WAIT_NO_INT;
            }
            break;
        }

        /* wait for the touch notification on the TP_INT input to go away */
        case DRV_TOUCH_STATE_WAIT_NO_INT:
        {
            if (TP_INT_Get() != DRV_TOUCH_INT_VALUE)
            {
                drv_touch.state = DRV_TOUCH_STATE_IDLE;
            }
            break;
        }
    }
}

bool get_touch_in_progress(void){
    return (TP_INT_Get() == DRV_TOUCH_INT_VALUE);
}