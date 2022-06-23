#include "ErrorCode.h"
#include "PaTypes.h"
void InitPumpDownVacuum (void);

void InitTherapyDeliveryVacuum(void);

ErrorCode_t GetVacuum(uint16_t* pInternal,uint16_t* pExternal, uint16_t* pDiff);

void SetInitialExternalPressure(uint32_t);

uint32_t GetInitialExternalPressure(void);

uint32_t GetTargetPumpDownVaccumDebounceCount(void);

bool_t isTargetPumpDownVacuumAchieved(uint16_t Vacuum);

bool_t isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum);

bool_t isTherapyDeliveryLeakDetected(void);

void TherapyDeliveryTargetVacuumUpdate(void);
