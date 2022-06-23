/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    power_management_task.c

  @Summary
    Power management.

  @Description
    Manages power.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "power_management.h"

//#define POWER_DOWN_IDLE_DELAY_MS                  5000    /* 5 seconds */
//#define POWER_DOWN_IDLE_DELAY_MS                  10000   /* 10 seconds */
#define POWER_DOWN_IDLE_DELAY_MS                  20000   /* 20 seconds */
//#define POWER_DOWN_IDLE_DELAY_MS                  60000   /* 60 seconds */
//#define POWER_DOWN_IDLE_DELAY_MS                  3600000 /* one hour */

#define POWER_DOWN_COMS_QUIET_PER                  90u // Percentage of power idle delay at which communication quiet window starts
 
#define POWER_OFF_DELAY_MS                        180000   /* 300 seconds */

//it will power-off device automatically if below is commented out
//#define AUTO_POWER_OFF_DISABLED

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
APP_DATA appData;

typedef struct
{
    POWER_MANAGEMENT_STATE state;
    uint32_t idle_time;
    uint32_t millisecond_timer;
    uint16_t second_timer;
    bool woken_up;
    void (*app_power_up_callback)(uint16_t * context);
    void (*app_power_down_callback)(uint16_t * context);
    void (*app_power_off_callback)(uint16_t * context); 
} POWER_MANAGEMENT_OBJ;

static POWER_MANAGEMENT_OBJ power = 
{
    .state = POWER_MANAGEMENT_STATE_INIT,
    .idle_time = 0,
    .millisecond_timer = 0,
    .second_timer = 0,
    .woken_up = false,
    .app_power_up_callback = NULL,
    .app_power_down_callback = NULL, 
    .app_power_off_callback = NULL,     
};

volatile SLEEP_WAKE_CAUSE sleep_wake_cause;
extern uint8_t interrupt_source;                // debug

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
static void power_off(void)
{
    if (NULL != power.app_power_off_callback)
    {
        (*power.app_power_off_callback)((uint16_t *) &power);
    }
}

static void power_down(void)
{
    //dputs_colour("[PINK]Power down[WHITE]\r\n");

    power.state = POWER_MANAGEMENT_STATE_POWERED_DOWN;

    if (NULL != power.app_power_down_callback)
    {
        (*power.app_power_down_callback)((uint16_t *) &power);
    }
}

static void power_up(void)
{
    //dputs_colour("[PINK]Power up[WHITE]\r\n");

    power.state = POWER_MANAGEMENT_STATE_RUNNING;

    if (NULL != power.app_power_up_callback)
    {
        (*power.app_power_up_callback)((uint16_t *) &power);
    }
}

POWER_MANAGEMENT_STATE get_power_state(void)
{
    return (power.state);
}

/* called at 1KHz */
void timer_callback(uint32_t status, uintptr_t context)
{
    (void) status;
    (void) context;

    power.idle_time++;
    power.millisecond_timer++;

    debug_millisecond_timer_interrupt();

    power.second_timer++;

    if (power.second_timer >= 1000)
    {
        power.second_timer = 0;
        app_update_system_clock();
    }
    appData.timer1ms = true;
}

/* put the device to sleep, and bring it back up afterwards */
static void sleep(void)
{    
    
    clock_full_speed();
    dprintf_colour("[PINK]Going to sleep...[WHITE]\r\n");

    int lcdbo = settings_get_lcd_brightness();
    float stepo = lcdbo / 30.0f;
    lcdbo -= stepo;
    
    for(; lcdbo>0; lcdbo-=stepo){
        
        app_set_lcd_brightness(lcdbo); 
        
        DelayMs(20);
    }
    app_set_lcd_brightness(0);
    
    laWidget_SetVisible((laWidget*)mainscreen_cover,LA_TRUE);
    
    
    /* wait for any ongoing DMA transfers to complete */
    CORETIMER_DelayMs(50);

    /* disable core timer interrupt */
    IEC0CLR = 0x1;

    DMAC_ChannelDisable(DMAC_CHANNEL_0);
    DMAC_ChannelDisable(DMAC_CHANNEL_1);

    sleep_wake_cause = SLEEP_WAKE_CAUSE_SLEEPING;
    interrupt_source = 0;

    IEC0bits.INT4IE = 0;
    uint32_t i4ip = IPC5bits.INT4IP;
    IPC5bits.INT4IP = 0;
    
    WDTCONSET = 0x8000; //enable the watchdog
    WDTCONbits.WDTCLRKEY = 0x5743; //clear the watchdog timer
    
    // unlock system registers for write
    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    // set the OSCCON register for sleep
    OSCCONbits.SLPEN = 1;

    // lock system registers
    SYSKEY = 0x0;
    
    TMR9_Stop();
    TMR2_Stop();
    DISPLAY_BL_Clear();
    __builtin_disable_interrupts();
    
    U5MODEbits.ON = 0;
    
    //buzzer pull down !
    LATFCLR = (1 << 3);
    TRISFCLR = (1 << 3);
    
    CFGMPLLbits.INTVREFCON = 0b11; 
    CFGMPLLbits.MPLLDIS = 1;
    CFGMPLLbits.MPLLVREGDIS = 1;
    CFGCONbits.IOANCPEN = 0;
    
    
    DelayMs(1);
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    
    OSCCONbits.NOSC=0x000;
    OSCCONSET = 0x00000001; //switching oscillator to FRC - to power down oscillator
    while (OSCCONbits.OSWEN);
    
    SYSKEY = 0;
    TP_INT_InterruptEnable();
    CNENBSET = (1 << 9);//Set interrupt for input change UART5 RX from PE
    LATHCLR = (1 << 8);//oscillator power off
    LATHSET = (1 << 6);//green LED off (dev board)
    __builtin_enable_interrupts();
    
    
    /* enter sleep state */
    _wait();
    
    
    IPC5bits.INT4IP = i4ip;
    IEC0bits.INT4IE = 1;
    
    U5MODEbits.WAKE = 0;        
    WDTCONCLR = 0x8000; //disable the watchdog
    power.idle_time = 0;
    
    TP_INT_InterruptDisable();
    CNENBCLR = (1 << 9);//Disable interrupt for input change UART5 RX from PE
    
    U5MODEbits.ON = 1;
    
    LATHCLR = (1 << 6);//green LED on (dev board)
    LATHSET = (1 << 8);
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    
    OSCCONbits.SLPEN = 0;
    
    OSCCONbits.NOSC=0x001;
    OSCCONSET = 0x00000001; //switching oscillator to SPLL
    while (OSCCONbits.OSWEN);
    
    SYSKEY = 0;
    DelayMs(10);
    
    
    CFGMPLLbits.INTVREFCON = 0b10;
    CFGMPLLbits.MPLLDIS = 0;
    CFGMPLLbits.MPLLVREGDIS = 0;
    CFGCONbits.IOANCPEN = 1;    
    
    //display_en
    LATJCLR = (1 << 7);
    TMR9_Start();
    drv_display_set_enable();
    CAMERA_PWDN_Clear();/* turn the camera back on */ 
    
    /* re-enable core timer interrupt */
    IEC0SET = 0x1;
    
    //DelayMs(100);
    
    int i;
    
    DRV_CAMERA_OVM7692_Resume(sysObj.drvOVM7692);
//    laWidget_SetAlphaEnable((laWidget*)mainscreen_cover,LA_TRUE);
//    laWidget_SetAlphaAmount((laWidget*)mainscreen_cover,0);
    laWidget_SetVisible((laWidget*)mainscreen_cover,LA_FALSE);
    for(i=0;i<20;i++){
        DRV_CAMERA_OVM7692_Tasks(sysObj.drvOVM7692);
        GFX_Update();
        LibAria_Tasks();
        DelayMs(1);
    }
    
    /* reinitialise the display */
    
    int target = settings_get_lcd_brightness();
    int lcdb = 20;
    float step = (target-lcdb) / 20.0f;
    i=0;
    for(lcdb=0;lcdb<target;lcdb+=step){
        i++;
        app_set_lcd_brightness(lcdb); 
        //laWidget_SetAlphaAmount((laWidget*)mainscreen_cover,255 * (i/20.0f));
        DRV_CAMERA_OVM7692_Tasks(sysObj.drvOVM7692);
        GFX_Update();
        LibAria_Tasks();
        DelayMs(20);
    }
    app_set_lcd_brightness(settings_get_lcd_brightness());
    
    
    power_up();
    
    
    sleep_wake_cause = SLEEP_WAKE_CAUSE_NONE;
    
    if(RNMICONbits.WDTS == 1) //if interrupt from WDT
    {
        RNMICONbits.WDTS = 0;
        dprintf_colour("[PINK]WDT interrupt - POWEROFF[WHITE]\r\n");
        #ifndef AUTO_POWER_OFF_DISABLED
        power_off();
        #endif
    }
    dprintf_colour("[PINK]interrupt_source %d[WHITE]\r\n", interrupt_source);
}
static void sleep2(void)
{
    clock_full_speed();
    WDTCONSET = 0x8000; //enable the watchdog
    WDTCONbits.WDTCLRKEY = 0x5743; //clear the watchdog timer
    
    // unlock system registers for write
    SYSKEY = 0x0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    // set the OSCCON register for sleep
    OSCCONbits.SLPEN = 1;

    // lock system registers
    SYSKEY = 0x0;

    TMR9_Stop();

    TP_INT_InterruptEnable();

    dprintf_colour("[PINK]Going to sleep...[WHITE]\r\n");
    /* wait for any ongoing DMA transfers to complete */
    CORETIMER_DelayMs(100);

    /* disable core timer interrupt */
    IEC0CLR = 0x1;

    DMAC_ChannelDisable(DMAC_CHANNEL_0);
    DMAC_ChannelDisable(DMAC_CHANNEL_1);

    sleep_wake_cause = SLEEP_WAKE_CAUSE_SLEEPING;
    interrupt_source = 0;

    IEC0bits.INT4IE = 0;
    uint32_t i4ip = IPC5bits.INT4IP;
    IPC5bits.INT4IP = 0;
    
    /* allow the P24 command to wake us up */
    U5MODEbits.SLPEN = 1;
    U5MODEbits.WAKE = 1;
    
    /* enter sleep state */
    _wait();
    
    play_notification(play_WAKEUP);
    IPC5bits.INT4IP = i4ip;
    IEC0bits.INT4IE = 1;
    
    U5MODEbits.WAKE = 0;        
    WDTCONCLR = 0x8000; //disable the watchdog
    power.idle_time = 0;
    
    TP_INT_InterruptDisable();
    
    power_up();
    TMR9_Start();

    /* re-enable core timer interrupt */
    IEC0SET = 0x1;
    
    sleep_wake_cause = SLEEP_WAKE_CAUSE_NONE;
    
    if(RNMICONbits.WDTS == 1) //if interrupt from WDT
    {
        RNMICONbits.WDTS = 0;
        dprintf_colour("[PINK]WDT interrupt - POWEROFF[WHITE]\r\n");
        #ifndef AUTO_POWER_OFF_DISABLED
        power_off();
        #endif
    }
    dprintf_colour("[PINK]interrupt_source %d[WHITE]\r\n", interrupt_source);
}

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
bool check_if_pwr_coms_quiet_window(void){

    const uint32_t quiet_window_threh = ((POWER_DOWN_IDLE_DELAY_MS* POWER_DOWN_COMS_QUIET_PER) / 100);

    if(power.idle_time > quiet_window_threh) {

        return true;
    }

    return false;

}

void power_up_callback_set(void (*app_power_up_callback)(uint16_t * context))
{
    power.app_power_up_callback = app_power_up_callback;
}

void power_down_callback_set(void (*app_power_down_callback)(uint16_t * context))
{
    power.app_power_down_callback = app_power_down_callback;
}

void power_off_callback_set(void (*app_power_off_callback)(uint16_t * context))
{
    power.app_power_off_callback = app_power_off_callback;
}

void power_management_task(void)
{
    switch (power.state)
    {
        case POWER_MANAGEMENT_STATE_INIT:
        {

            TP_INT_InputEnable();
            TP_INT_InterruptDisable();
            
            /* register callback for 1ms interrupts */
            TMR9_CallbackRegister(timer_callback, 0);
            TMR9_InterruptEnable();
            TMR9_Start();
            power.state = POWER_MANAGEMENT_STATE_RUNNING;
            sleep_wake_cause = SLEEP_WAKE_CAUSE_NONE;
            break;
        }

        case POWER_MANAGEMENT_STATE_RUNNING:
        {
            if (power.idle_time > POWER_OFF_DELAY_MS)
            {
                power_off();
            }            
            else if (power.idle_time > POWER_DOWN_IDLE_DELAY_MS)
            {
                power_down();
            }
            break;
        }

        case POWER_MANAGEMENT_STATE_POWERED_DOWN:
        {
            /* the system is powered down waiting for a touch or trigger pull */
            sleep();
            break;
        }

        case POWER_MANAGEMENT_STATE_SUSPENDED:
        {
            /* power management is suspended - do nothing */
            power.idle_time = 0;
            break;
        }        
    }
}

void power_management_activity_trigger(void)
{
    /* hopefully this is atomic */
    power.idle_time = 0;
}

/* suspend or enable power management */
void power_management_suspend(bool suspend)
{
    if (suspend)
    {
        power.state = POWER_MANAGEMENT_STATE_SUSPENDED;
    }
    else
    {
        power.state = POWER_MANAGEMENT_STATE_RUNNING;
    }

    power.idle_time = 0;
}

uint32_t get_millisecond_timer_value(void)
{
    /* hopefully this is atomic */
    return (power.millisecond_timer);
}

/* returns true if it was a trigger press that woke up the device */
bool trigger_woke_us_from_sleep(void)
{
    return (SLEEP_WAKE_CAUSE_TRIGGER == sleep_wake_cause);
}

/* restart the counter that puts the device to sleep */
void reset_sleep_counter(void)
{
    power.idle_time = 0;
}
