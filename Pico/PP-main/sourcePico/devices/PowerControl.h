/*****************************************************************************
 *   File        : PowerControl.h
 *
 *   Description : Header for implementation of maximum power tracking of PWM
 * for pump
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#ifndef MPPOWERCONTROL_H
#define	MPPOWERCONTROL_H

#include "PaTypes.h"

#define VBOOST_REF_MAX ((uint8_t)27)   // DAC reference out for 27V at Vdd 2V0
#define VBOOST_REF_30V ((uint8_t)20)   // DAC reference out for 30V at Vdd 3V0
#define VBOOST_REF_29V ((uint8_t)19)   // DAC reference out for 29V at Vdd 3V0
#define VBOOST_REF_27V ((uint8_t)18)   // DAC reference out for 27V at Vdd 3V0
#define VBOOST_REF_26V ((uint8_t)17)   // DAC reference out for 27V at Vdd 3V0
#define VBOOST_REF_25V ((uint8_t)16)   // DAC reference out for 25V at Vdd 3V0
#define VBOOST_REF_23V ((uint8_t)15)   // DAC reference out for 23V at Vdd 3V0
#define VBOOST_REF_22V ((uint8_t)14)   // DAC reference out for 22V at Vdd 3V0
#define VBOOST_REF_20V ((uint8_t)13)   // DAC reference out for 20V at Vdd 3V0
#define VBOOST_REF_18V ((uint8_t)12)   // DAC reference out for 18V at Vdd 3V0

#define VBOOST_REF  (VBOOST_REF_27V)
#define VBOOST_REF_0V   (0)

void MP_DisablePeripheral(void);    // puts the PIC into a low power sleep mode
void MP_SleepUntilWokenByRelaxationOscillator(void);
void MP_EnableMainCircuitPower(void);  // Apply power to main circuit
void MP_DisableMainCircuitPower(void);  // Remove power from main circuit
void MP_EnableFvr(void); // Enable the FVR
void MP_EnableTemperatureIndicator(void); // Enable the Temperature Indicator
void MP_SetReferenceVoltageBoost(uint8_t);   // Set Boost reference voltage in mV
void MP_EnablePumpPWM(void);    // Activate PWM on pump
void MP_DisablePumpPWM(void);    // Deactivate PWM on pump
void MP_EnableExternalPeripheralsSupply(void);
void MP_DisableExternalPeripheralsSupply(void);
uint8_t MP_GetBoostDemand(void);   // Get latest boost demand value
void MP_SetBoostDemand(uint8_t);   // Set latest boost demand value

uint8_t MP_GetInitBoostDemand(void);
void MP_SetInitBoostDemand(uint8_t demand);
bool_t isPumpPwmEnabled(void);
bool_t isMainCircuitPowerEnabled(void);
void MP_EnableRelaxationOscillator(void);

void MP_DeepSleep(void);

#endif	/* MPPOWERCONTROL_H */
