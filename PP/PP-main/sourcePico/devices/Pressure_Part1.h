/*****************************************************************************
 *   File        : Pressure_Part1.h
 *
 *   Description : Header for implementation of pressure measurements
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018 - 2021 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#ifndef PRESSURE_PART_1_H
#define	PRESSURE_PART_1_H

#include "PaTypes.h"
#include "ErrorCode.h"
#define PUMP_DOWN_TARGET_VACUUM        (96)
#define PUMP_DOWN_DEBOUNCE_VACUUM_MAX   (1)
#define GET_VACUUM_MAX_RETRIES         (40)

// Using 0.1 kPa resolution
//  9.3 kPa vacuum == -70 mmHg
// 10.7 kPa vacuum == -80 mmHg
// 12.0 kPa vacuum == -90 mmHg
#define PRESSURE_DIFFERENTIAL (0)
#define PRESSURE_INTERNAL     (1)
#define PRESSURE_EXTERNAL     (2)


#define THERAPY_DELIVERY_TARGET_VACUUM            (96)
#define THERAPY_DELIVERY_MAX_PRESSURE_OFFSET      (11)
#define THERAPY_DELIVERY_TARGET_VACCUM_UPDATE_PERIOD_SECONDS  (9)

void InitPumpDownVacuum (void);
void InitTherapyDeliveryVacuum(void);
ErrorCode_t GetVacuum(uint16_t* pInternal,uint16_t* pExternal, uint16_t* pDiff);
void SetInitialExternalPressure(uint32_t);
uint32_t GetInitialExternalPressure(void);
uint32_t GetTargetPumpDownVaccumDebounceCount(void);
bool_t  isTargetPumpDownVacuumAchieved(uint16_t Vacuum);
bool_t  isTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum);
bool_t  isTherapyDeliveryLeakDetected(void);
void TherapyDeliveryTargetVacuumUpdate(void);


#endif	/* PRESSURE_PART_1_H */

