#include "ErrorCode.h"
#include "PaTypes.h"




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

void PM_Delay(uint32_t);

bool_t PM_GetT1Flag(void);





void TimerCounters_Init(void);

ErrorCode_t TimerCounter_Start(CounterName_t counterName, uint32_t counterValue);

ErrorCode_t TimerCounter_Disable(CounterName_t counterName);

CounterStatus_t TimerCounter_Status(CounterName_t counterName);

uint32_t TimerCounter_GetTimeout(CounterName_t counterName);
