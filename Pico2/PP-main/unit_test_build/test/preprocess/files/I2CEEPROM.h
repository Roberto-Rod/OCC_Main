#include "ErrorCode.h"
#include "PaTypes.h"










void I2E_Init(void);



ErrorCode_t I2E_Read(uint32_t address, uint8_t *data, uint8_t numBytes);



ErrorCode_t I2E_Write(uint32_t address, const uint8_t *data, uint8_t numBytes);
