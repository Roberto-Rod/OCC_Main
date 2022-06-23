/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_piezo.h

  @Summary
    Driver for the piezo buzzer.

  @Description
    API to make beeps from the piezo.
 */
/* ************************************************************************** */

#ifndef _DRV_PIEZO_H    /* Guard against multiple inclusion */
#define _DRV_PIEZO_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#define DRV_PIEZO_TONE_1    2730U       // Resonance (Loudest)
#define DRV_PIEZO_TONE_2    2000U       // 
#define DRV_PIEZO_TONE_3    1800U       // 
#define DRV_PIEZO_TONE_4    1500U       //   
#define DRV_PIEZO_DC        2U          // 50% duty cycle (Loudest

typedef struct notification_type
{
    uint16_t duration;
    uint16_t freq;
    bool started;
}notification_type;

typedef enum {
    play_OTHER, play_START, play_SCAN, play_TOUCH, play_POWER_DOWN, play_WAKEUP, play_TESTTONE, play_LASER_ERROR
}BUZZER_NOTIFICATION;
void add_buzzer_action(uint16_t a1,uint16_t a2);
void play_notification(BUZZER_NOTIFICATION notification);
void add_notification(uint16_t time_ms, uint16_t freq_Hz);
void notification_tasks(bool update);

void piezo_two_tone(uint16_t frequency1, uint16_t on_time1_ms, uint16_t off_time1_ms, uint16_t frequency2, uint16_t on2_time_ms);
void piezo_pulse(uint16_t frequency, uint16_t on_time_ms, uint16_t off_time_ms, uint8_t repetitions);

#endif /* _DRV_PIEZO_H */
