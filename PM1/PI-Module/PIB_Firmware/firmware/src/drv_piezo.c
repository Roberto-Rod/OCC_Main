/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_piezo.c

  @Summary
    Driver for the piezo buzzer.

  @Description
    API to make beeps from the piezo.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"
#include "drv_piezo.h"
#include "configuration.h"

#define buzzer_max_q 32U
static struct notification_type BuzzerQueue[buzzer_max_q];
static uint16_t buzzer_queue_size = 0;


inline uint32_t get_pr4_val(uint32_t freq) {
    uint32_t pr4_val = (uint32_t) ((float) ((float) 12500000 / 2.0f) / (float) freq) - 1;
    return pr4_val;
}

void add_notification(uint16_t time_ms, uint16_t freq_Hz) {
    if (buzzer_queue_size < buzzer_max_q) {
        BuzzerQueue[buzzer_queue_size].started = false;
        BuzzerQueue[buzzer_queue_size].duration = time_ms;
        if (freq_Hz == 0) {
            BuzzerQueue[buzzer_queue_size].freq = 0;
        } else {
            BuzzerQueue[buzzer_queue_size].freq = get_pr4_val(freq_Hz);
        }
        buzzer_queue_size++;
    }
}

/* It is called directly by TIMER_9_InterruptHandler in plib_tmr9.c */
void notification_tasks(bool update) {
    static uint16_t current_buzzer_act = 0U;
    if (buzzer_queue_size > 0) {
        if (BuzzerQueue[current_buzzer_act].started) {
            if (BuzzerQueue[current_buzzer_act].duration == 0) {
                if (++current_buzzer_act == buzzer_queue_size) {
                    current_buzzer_act = 0U;
                    buzzer_queue_size = 0U;
                    TMR4_Stop();
                    LATFCLR = (1 << 3);
                }
            } else {
                if(true == update) {BuzzerQueue[current_buzzer_act].duration--;}
            }
        } else {
            if (BuzzerQueue[current_buzzer_act].freq > 0) {
                LATFCLR = (1 << 3);
                TMR4 = 0;
                TMR4_PeriodSet(BuzzerQueue[current_buzzer_act].freq);
                TMR4_Start();
                BuzzerQueue[current_buzzer_act].started = true;
            } else {
                TMR4_Stop();
                LATFCLR = (1 << 3);
                BuzzerQueue[current_buzzer_act].started = true;
            }
        }
    }
}

void play_notification(BUZZER_NOTIFICATION notification) {
    switch (notification) {
        default:
            //no notification
            add_notification(200, 500U);
            break;
        case play_START:
            add_notification(100, 2730U/2);
            add_notification(100, 0);
            add_notification(100, 2000U/2);
            break;
        case play_SCAN:
            add_notification(50, 2730U/2);
            //add_notification(25, 0);
            break;
        case play_TOUCH:
            add_notification(50, 2730U/4);
            break;
        case play_WAKEUP:
            add_notification(25, 2730U);
            add_notification(25, 3730U);
            add_notification(25, 4730U);
            break;
        case play_LASER_ERROR:
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            add_notification(1000, 2730U/2);
            add_notification(1000, 2730U/4);
            break;
        case play_TESTTONE:
        {
            int factor = 3;
            int gap_len = 5;
            int sound_len = 50;
            add_notification(sound_len, 110*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 117*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 123*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 131*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 139*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 147*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 156*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 165*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 175*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 185*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 196*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 208*factor);
            add_notification(gap_len, 0);
            
            factor = 4;
            add_notification(sound_len, 110*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 117*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 123*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 131*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 139*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 147*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 156*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 165*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 175*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 185*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 196*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 208*factor);
            add_notification(gap_len, 0);
            
            factor = 5;
            add_notification(sound_len, 110*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 117*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 123*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 131*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 139*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 147*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 156*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 165*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 175*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 185*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 196*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 208*factor);
            add_notification(gap_len, 0);
            
            factor = 6;
            add_notification(sound_len, 110*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 117*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 123*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 131*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 139*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 147*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 156*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 165*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 175*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 185*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 196*factor);
            add_notification(gap_len, 0);
            add_notification(sound_len, 208*factor);
            add_notification(gap_len, 0);
        }   
            break;
        case play_POWER_DOWN:
            add_notification(200, 500U);
            
            break;
    }
}

//legacy functions to not throw errors and do beeps
void piezo_two_tone(uint16_t frequency1, uint16_t on_time1_ms, uint16_t off_time1_ms, uint16_t frequency2, uint16_t on2_time_ms)
{
    play_notification(play_START);
}
void piezo_pulse(uint16_t frequency, uint16_t on_time_ms, uint16_t off_time_ms, uint8_t repetitions){play_notification(play_OTHER);}

bool piezo_busy(void){
    return (bool)buzzer_queue_size;
}