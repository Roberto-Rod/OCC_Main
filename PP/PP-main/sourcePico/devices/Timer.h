/********************************************************************************
* File : Timer.h
*
* Description : Header for Timer implementation
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#ifndef PMTIMER_H_
#define PMTIMER_H_

#include "PaTypes.h"
#include "ErrorCode.h"


typedef enum
{
    STATE_MACHINE_COUNTER_E = 0,
    POWER_OFF_COUNTER_E,
    LED_ALERT_COUNTER_1_E,
    MAX_SOFTWARE_COUNTER_E
} CounterName_t;

typedef enum
{
    RUNNING_COUNTER_E = 0,
    DISABLED_COUNTER_E,
    EXPIRED_COUNTER_E,
    INERROR_COUNTER_E,
    UNKNOWN_STATE_E
} CounterStatus_t;

#define ONE_MILLISECOND_DELAY        (1)
#define TWENTY_MILLISECONDS_DELAY    (20)
#define FORTY_MILLISECONDS_DELAY     (40)
#define FIVE_SECONDS_DELAY           (5000)

// Returns a count based on 100ms update rate
// Clears the count based on 100ms update rate
void PM_Delay(uint32_t);   // Creates a delay in ms
bool_t PM_GetT1Flag(void); // Checks and clears T1 event flag

// Timers
void TimerCounters_Init(void);
ErrorCode_t TimerCounter_Start(CounterName_t counterName, uint32_t counterValue);
ErrorCode_t TimerCounter_Disable(CounterName_t counterName);
CounterStatus_t TimerCounter_Status(CounterName_t counterName);
uint32_t TimerCounter_GetTimeout(CounterName_t counterName);


#endif /* PMTIMER_H_ */

