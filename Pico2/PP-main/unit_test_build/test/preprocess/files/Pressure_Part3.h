#include "ErrorCode.h"
#include "PaTypes.h"


typedef enum {

    PS_EXTERNAL_PRESSURE_E = 0,

    PS_INTERNAL_PRESSURE_E,

    PS_MAX_NUM_PRESSURE_SENSORS_E

} PressureSensor_t;



ErrorCode_t PM_InitSensors(void);

ErrorCode_t PM_StartSensors(void);

ErrorCode_t PM_GetPressure(PressureSensor_t Sensor, uint16_t* pPressure, uint16_t* pTemperature);

ErrorCode_t PM_CalcDiffPressure(uint16_t PresExt, uint16_t PresInt, uint16_t* pDiff);

bool_t isPressureSensorReady(PressureSensor_t Sensor);

bool_t PM_GetPressureSensorBootOk(uint8_t Sensor);
