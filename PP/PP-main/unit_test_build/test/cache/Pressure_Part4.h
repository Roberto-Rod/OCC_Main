#include "ErrorCode.h"
#include "PaTypes.h"
bool_t PM_WritePressureSensors(uint8_t Device, uint8_t DataLength, uint8_t *DataBuffer);

bool_t PM_ReadPressureSensors(uint8_t Device, uint8_t DataLength, uint8_t DataAddress, uint8_t *DataBuffer);
