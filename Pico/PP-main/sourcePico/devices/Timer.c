/********************************************************************************
* File : Timer.c
*
* Description : Source Code for Timer implementation
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

#include "Timer.h"
#include "HardwareInterface.h"
#include "Assert.h"

typedef struct Counter_tag
{
    bool_t   isEnabled;
    uint32_t countRemaining;
} Counter_t;

#define MS_DELAY                  (30)         //0x01F7
// The following line is Commented out to avoid PC-lint (750) issue. local macro 'SYSTEM_CLOCK_COUNT_MAX' (Location) not referenced.
//#define SYSTEM_CLOCK_COUNT_MAX    (4294967295) // assuming that TMR 1 is called every 0.1s, this can proceed up to 4971 days
                                               // which is far beyond the life of the device (currently 7 days). This means
                                               // we do not have to worry about any wrap around event
#define TIMER_COUNT_MAX           (86400000ul) // Arbitrary maximum value that can be assigned to a timer counter that
                                               // corresponds to 1 day (24h) assuming that TMR 1 is called every 0.1s


static Counter_t counterFactory[MAX_SOFTWARE_COUNTER_E];
static uint8_t   t1Flag = 0;


void TimerCounters_Update(void);

/*************************************************
*  @brief   Code called by Timer 1 ISR
*  @param   None
*  @return  None
*
*  NOTE: Comment out the auto generated code for this routine
*
*************************************************/
void TMR1_CallBack(void)
{
    t1Flag = 1;

    TimerCounters_Update();
}


/*************************************************
*  @brief
*  @param
*  @return
*
*  NOTE: This is called when the Global Interrupt
*        is not enabled therefore it does not need
*        protection (i.e. disabling the Global
*        Interrupt)
*
*************************************************/
void TimerCounters_Init(void)
{
    HardwareInterface_DisableGlobalInterrupt();

    for (int i = 0; i < MAX_SOFTWARE_COUNTER_E; i++)
    {
        counterFactory[i].isEnabled      = FALSE;
        counterFactory[i].countRemaining = 0;
    }

    HardwareInterface_EnableGlobalInterrupt();
}

/*************************************************
*  @brief
*  @param
*  @return
*
*  NOTE:
*
*************************************************/
ErrorCode_t TimerCounter_Start(CounterName_t counterName, uint32_t counterValue)
{
    ErrorCode_t result = EC_OK_E;

    ASSERT(MAX_SOFTWARE_COUNTER_E > counterName);
    ASSERT(TIMER_COUNT_MAX > counterValue);

    if (!counterFactory[counterName].isEnabled)
    {
        counterFactory[counterName].isEnabled      = TRUE;
        counterFactory[counterName].countRemaining = counterValue;
    }
    else
    {
        result = EC_TIMER_COUNT_UNAVAILABLE_E;
    }

    return result;
}


/*************************************************
*  @brief
*  @param
*  @return
*
*  NOTE:
*
*************************************************/
ErrorCode_t TimerCounter_Disable(CounterName_t counterName)
{
    ASSERT(MAX_SOFTWARE_COUNTER_E > counterName);
    counterFactory[counterName].isEnabled = FALSE;
    return EC_OK_E;
}

/*************************************************
*  @brief
*  @param
*  @return
*
*  NOTE:
*
*************************************************/
CounterStatus_t TimerCounter_Status(CounterName_t counterName)
{
    ASSERT(MAX_SOFTWARE_COUNTER_E > counterName);

    CounterStatus_t status = INERROR_COUNTER_E;

    if (counterFactory[counterName].isEnabled)
    {
        HardwareInterface_DisableGlobalInterrupt();
        uint32_t countRemaining = counterFactory[counterName].countRemaining;
        HardwareInterface_EnableGlobalInterrupt();

        if (countRemaining > 0)
        {
            status = RUNNING_COUNTER_E;
        }
        else
        {
            status = EXPIRED_COUNTER_E;
        }
    }
    else
    {
        status = DISABLED_COUNTER_E;
    }

    return status;
}


/*************************************************
*  @brief
*  @param
*  @return
*
*  NOTE:
*
*************************************************/
uint32_t TimerCounter_GetTimeout(CounterName_t counterName)
{
    uint32_t countRemaining = 0;

    ASSERT(MAX_SOFTWARE_COUNTER_E > counterName);

    if (counterFactory[counterName].isEnabled)
    {
        HardwareInterface_DisableGlobalInterrupt();
        countRemaining = counterFactory[counterName].countRemaining;
        HardwareInterface_EnableGlobalInterrupt();
    }

    return countRemaining;
}

/*************************************************
*  @brief
*  @param   None
*  @return  None
*
*  NOTE:
*
*************************************************/
void TimerCounters_Update(void)
{
    for (int i = 0; i < MAX_SOFTWARE_COUNTER_E; i++)
    {
        if (!counterFactory[i].isEnabled)
        {
            continue;
        }         //skip evaluation if this Timer Counter is not enabled

        if (counterFactory[i].countRemaining > 0)
        {
            counterFactory[i].countRemaining--;
        }
    }
}


/*********************************************//**
*  @brief   Creates a delay.
*           This works only if with a System Clock
*           of 4kHz. If you change that the whole
*           Application may not work
*  @param   Value to delay in ms
*  @return  None
*
*************************************************/
void PM_Delay(uint32_t delay)
{
    uint32_t count;
    while (delay--)
    {
        // this should add a delay of 1 ms
        count = 0;
        while (MS_DELAY > count++)
        {
            ; //do nothing
        }
    }
}


/*********************************************//**
*  @brief   Checks and clears the T1 event flag
*  @param   None
*  @return  T1 event flag
*
*************************************************/
bool_t PM_GetT1Flag()
{
    bool_t isTimeUp = FALSE;

    if (t1Flag)
    {
        isTimeUp = TRUE;
        t1Flag   = 0;
    }

    return(isTimeUp);
}
