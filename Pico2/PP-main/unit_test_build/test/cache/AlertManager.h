#include "ErrorCode.h"
#include "PaTypes.h"










ErrorCode_t AlertManager_Init(void);











ErrorCode_t AlertManager_Run(void);





typedef enum

{

    LED_CTRL_OFF_E = 0,

    LED_CTRL_PUMP_DOWN_E,

    LED_CTRL_POWER_DOWN_E,

    LED_CTRL_LEAK_E,

    LED_CTRL_GOOD_STATUS_E,



    LED_CTRL_COMPLETED_E,

} LEDControl_t;





void StartLEDSequence(LEDControl_t seq);





bool_t checkLEDSequenceCompleted (void);
