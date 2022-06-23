/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_led_pca9530.c

  @Summary
    PCA9530 LED driver chip driver

  @Description
    This PCA9530 LED driver translates non-blocking API function calls to I2C
    commands that are queued and sent to the PCA9530 LED driver chip.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "drv_led_pca9530.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define DRV_LED_I2C_SLAVE_ADDRESS               0x60        /* (this may actually be 0xc0) or 0x61 if A0 is high (possibly 0xc1) */
#define DRV_LED_I2C_INDEX                       0

#define DRV_LED_LED_OFF                         0
#define DRV_LED_LED_ON                          1
#define DRV_LED_LED_PWM0                        2
#define DRV_LED_LED_PWM1                        3

#define DRV_LED_INPUT_REGISTER                  0
#define DRV_LED_PSC0_REGISTER                   1
#define DRV_LED_PWM0_REGISTER                   2
#define DRV_LED_PSC1_REGISTER                   3
#define DRV_LED_PWM1_REGISTER                   4
#define DRV_LED_LED_SELECTOR_REGISTER           5

//#define HARMONY_I2C

typedef enum
{
    DRV_LED_STATE_INIT,
    DRV_LED_STATE_CONFIGURE,
    DRV_LED_STATE_IDLE,
    DRV_LED_STATE_WAIT,            
 
    DRV_LED_STATE_ERROR,
} DRV_LED_STATE;

typedef enum
{
    DRV_LED_ERROR_NONE,    
    DRV_LED_ERROR_I2C,
    DRV_LED_ERROR_I2C_WRITE,
    DRV_LED_ERROR_I2C_INVALID_STATE,
    DRV_LED_ERROR_I2C_INVALID_HANDLE,
} DRV_LED_ERROR;

typedef enum
{
    DRV_LED_COMMAND_INPUT = 1,
    DRV_LED_COMMAND_PSC0 = 2,
    DRV_LED_COMMAND_PWM0 = 4,
    DRV_LED_COMMAND_PSC1 = 8,
    DRV_LED_COMMAND_PWM1 = 0x10,
    DRV_LED_COMMAND_SELECTOR = 0x20,
} DRV_LED_COMMAND;

typedef struct
{
    DRV_LED_STATE state;
    DRV_LED_STATE prev_state;
    DRV_HANDLE i2c_handle;
    DRV_I2C_TRANSFER_HANDLE i2c_tx_handle;
    DRV_LED_ERROR error;
    uint8_t cmd_buffer[2];
    uint32_t timeout;

    uint8_t psc0;                           /* current PSC0 value */
    uint8_t pwm0;                           /* current PWM0 value */
    uint8_t psc1;                           /* current PSC1 value */
    uint8_t pwm1;                           /* current PWM1 value */
    uint8_t led_selector;                   /* current LED selector value */
    uint8_t command_mask;                   /* "queue" of up to 6 commands */
} DRV_LED_OBJ;

static DRV_LED_OBJ drv_led = 
{
    .state = DRV_LED_STATE_INIT,
    .prev_state = DRV_LED_STATE_INIT,
    .led_selector = 0,                      /* both LEDs off */
    .command_mask = 0,                      /* no commands queued */
};

typedef struct
{
    bool active;
    bool fading_in;
    bool fading_out;
    bool start;
    uint16_t f_in_step_duration;
    uint16_t f_out_step_duration;
    uint8_t t_pwm;                           /* target PWM0 value */
    uint8_t c_pwm;
    
    float pwm_increment;
    
    uint16_t progress;
    uint16_t c_value;
    float in_steps_count;
    float out_steps_count;
}LED_FADING_t;

static LED_FADING_t led_fading;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Function: drv_pca9530_led_i2c_callback                                     */
/* This function is called on the completion of every I2C read or write       */
/* operation, and moves the state machine on to the next operation.           */
/* ************************************************************************** */
static void drv_pca9530_led_i2c_callback (DRV_I2C_TRANSFER_EVENT  event, DRV_I2C_TRANSFER_HANDLE transferHandle, uintptr_t context)
{
    if (transferHandle != drv_led.i2c_tx_handle)
    {
        // invalid handle, throw error
        drv_led.state = DRV_LED_STATE_ERROR;
        drv_led.error = DRV_LED_ERROR_I2C_INVALID_HANDLE;
        return;
    }
        
    switch (event)
    {
        case DRV_I2C_TRANSFER_EVENT_COMPLETE:
        {
            switch (drv_led.prev_state)
            {
                case DRV_LED_STATE_CONFIGURE:
                {
                    drv_led.state = drv_led.prev_state;
                    break;
                }

                case DRV_LED_STATE_IDLE:
                {
                    drv_led.state = drv_led.prev_state;
                    break;
                }

                default:
                {
                    // invalid condition, throw error
                    drv_led.state = DRV_LED_STATE_ERROR;
                    drv_led.error = DRV_LED_ERROR_I2C_INVALID_STATE;
                    break;
                }
            }
            break;
        }

        case DRV_I2C_TRANSFER_EVENT_ERROR:
        {
            drv_led.state = DRV_LED_STATE_ERROR;
            drv_led.error = DRV_LED_ERROR_I2C_WRITE;
            break;
        }

        default:
            break;
    }
}
/* End of function drv_pca9530_led_i2c_callback                               */

/* ************************************************************************** */
/* Function: drv_pca9530_led_controller_task                                  */
/* Called in the main task idle loop to send register updates to the LED      */
/* driver chip                                                                */
/* ************************************************************************** */
void drv_pca9530_led_controller_task(void)
{
    switch (drv_led.state)
    {
        case DRV_LED_STATE_INIT:
        {
            dputs_colour("[GREEN]LEDs INIT[WHITE]\r\n");
            led_fading.f_in_step_duration = 2;
            led_fading.f_out_step_duration = 2;
            led_fading.in_steps_count = 30.0f;
            led_fading.out_steps_count = 30.0f;
            set_pca9530_led_pwm0_rate(PCA9530_PWM_152HZ,0);
            
            drv_led.state = DRV_LED_STATE_IDLE;
            break;
        }

        /* waiting for a new command to be issued (via an incoming API function call) */
        case DRV_LED_STATE_IDLE:
        {
            break;
        }

        
        case DRV_LED_STATE_WAIT:
        {
            // do nothing, wait for callback
            drv_led.timeout++;

            if (drv_led.timeout > 100000)
            {
                drv_led.state = DRV_LED_STATE_IDLE;
            }
            
            break;
        }

        case DRV_LED_STATE_ERROR:
        default:
            break;
    }
}
/* End of function drv_pca9530_led_controller_task                            */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


/* set the PWM0 rate */
void set_pca9530_led_pwm0_rate(uint8_t pcs0, uint8_t pwm0)
{
    drv_led.psc0 = pcs0;
    drv_led.pwm0 = pwm0;
}

/* set the PWM1 rate */
void set_pca9530_led_pwm1_rate(uint8_t pcs1, uint8_t pwm1)
{
    drv_led.psc1 = pcs1;
    drv_led.pwm1 = pwm1;
}

void set_pca9530_leds_on(void)
{
    dputs_colour("[GREEN]LEDs ON[WHITE]\r\n");
    led_fading.t_pwm = drv_led.pwm0;
    led_fading.pwm_increment = drv_led.pwm0 / led_fading.in_steps_count;
    led_fading.fading_in = true;
    led_fading.fading_out = false;
    led_fading.start = true;
}
void set_pca9530_leds_off(void)
{
    dputs_colour("[GREEN]LEDs OFF[WHITE]\r\n");
    //fade-out only if previously fade-in was called
    if(led_fading.fading_in == true)
    {
        led_fading.t_pwm = 0;
        led_fading.pwm_increment = drv_led.pwm0 / led_fading.out_steps_count;
        led_fading.fading_out = true;
        led_fading.fading_in = false;
        led_fading.start = true;
    }
}
static void set_pwm0_update_LEDs(uint8_t pwm0)
{
    static uint8_t data[2];
    data[0] = pwm0;
    data[1] = 0b00001010;//update both LEDs to PWM0
    if(pwm0 == 0)
    {
        data[1] = 0b00000000;//turn off both LEDs
        DRV_I2C2_Write_Bytes(DRV_LED_I2C_SLAVE_ADDRESS, DRV_LED_LED_SELECTOR_REGISTER, &data[1], 1);
        drv_pca9530_led_i2c_callback(DRV_I2C_TRANSFER_EVENT_COMPLETE, drv_led.i2c_tx_handle, 0);
        return;
    }
    DRV_I2C2_Write_Bytes(DRV_LED_I2C_SLAVE_ADDRESS, DRV_LED_PWM0_REGISTER, &data[0], 1);
    drv_pca9530_led_i2c_callback(DRV_I2C_TRANSFER_EVENT_COMPLETE, drv_led.i2c_tx_handle, 0);
    DRV_I2C2_Write_Bytes(DRV_LED_I2C_SLAVE_ADDRESS, DRV_LED_LED_SELECTOR_REGISTER, &data[1], 1);
    drv_pca9530_led_i2c_callback(DRV_I2C_TRANSFER_EVENT_COMPLETE, drv_led.i2c_tx_handle, 0);
}
bool drv_led_pca9530_fading_tasks(void)
{
    static uint16_t internal_progress = 0;
    
    if(led_fading.start){
        internal_progress = 0;
        led_fading.start = false;
        led_fading.active = true;
    }
    
    if(led_fading.active)
    {
        if(internal_progress-- <= 0)
        {
            //dprintf_colour("[CYAN]LEDs: %d / %d[WHITE]\r\n", led_fading.c_pwm, led_fading.progress);
            led_fading.progress += 1;
            //led_fading.c_value += 1 + led_fading.c_value / 6;
            
            if(led_fading.fading_in){
                led_fading.c_pwm = led_fading.progress * led_fading.pwm_increment;
                if(led_fading.c_pwm > led_fading.t_pwm){
                    led_fading.c_pwm = led_fading.t_pwm;
                }
            }
            
            if(led_fading.fading_out){
                //led_fading.c_pwm = (uint8_t)(((uint16_t)led_fading.out_steps_count - led_fading.progress) * led_fading.pwm_increment);
                led_fading.c_pwm = (led_fading.out_steps_count - led_fading.progress) * led_fading.pwm_increment;
            }
            
            set_pwm0_update_LEDs(led_fading.c_pwm);
            
            if(led_fading.fading_in){
                internal_progress = led_fading.f_in_step_duration;
                if(led_fading.progress >= led_fading.in_steps_count){
                    led_fading.progress = 0;
                    led_fading.active = false;
                }
            }
            if(led_fading.fading_out){
                internal_progress = led_fading.f_out_step_duration;
                if(led_fading.progress >= led_fading.out_steps_count){
                    led_fading.progress = 0;
                    led_fading.active = false;
                    set_pwm0_update_LEDs(0);
                }
            }
            
            
        }
    }
    return led_fading.active;
}
bool drv_pca9530_fading_active(void)
{
    return led_fading.active;
}