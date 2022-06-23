#include "PaTypes.h"
void MP_DisablePeripheral(void);

void MP_SleepUntilWokenByRelaxationOscillator(void);

void MP_EnableMainCircuitPower(void);

void MP_DisableMainCircuitPower(void);

void MP_EnableFvr(void);

void MP_EnableTemperatureIndicator(void);

void MP_SetReferenceVoltageBoost(uint8_t);

void MP_EnablePumpPWM(void);

void MP_DisablePumpPWM(void);

void MP_EnableExternalPeripheralsSupply(void);

void MP_DisableExternalPeripheralsSupply(void);

uint8_t MP_GetBoostDemand(void);

void MP_SetBoostDemand(uint8_t);



uint8_t MP_GetInitBoostDemand(void);

void MP_SetInitBoostDemand(uint8_t demand);

bool_t isPumpPwmEnabled(void);

bool_t isMainCircuitPowerEnabled(void);

void MP_EnableRelaxationOscillator(void);



void MP_DeepSleep(void);
