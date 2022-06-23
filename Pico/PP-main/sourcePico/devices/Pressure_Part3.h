/*****************************************************************************
 *   File        : Pressure_Part3.h
 *
 *   Description : Header for implementation of pressure measurements including
 * I2C comms
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

#ifndef PRESSURE_PART_3_H
#define	PRESSURE_PART_3_H

#include "PaTypes.h"
#include "ErrorCode.h"

typedef enum {
    PS_EXTERNAL_PRESSURE_E = 0,      
    PS_INTERNAL_PRESSURE_E,
    PS_MAX_NUM_PRESSURE_SENSORS_E   //number of the sensors
} PressureSensor_t;

ErrorCode_t PM_InitSensors(void);
ErrorCode_t PM_StartSensors(void);
ErrorCode_t PM_GetPressure(PressureSensor_t Sensor, uint16_t* pPressure, uint16_t* pTemperature);
ErrorCode_t PM_CalcDiffPressure(uint16_t PresExt, uint16_t PresInt, uint16_t* pDiff);
bool_t isPressureSensorReady(PressureSensor_t Sensor);
bool_t PM_GetPressureSensorBootOk(uint8_t Sensor);
//void PM_Reset_Psensors(void);

#endif	/* PRESSURE_PART_3_H */

