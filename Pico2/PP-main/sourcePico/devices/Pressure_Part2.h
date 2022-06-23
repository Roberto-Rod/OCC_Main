/*****************************************************************************
 *   File        : Pressure_Part2.h
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

#ifndef PRESSURE_PART_2_H
#define	PRESSURE_PART_2_H

#include "PaTypes.h"
#include "ErrorCode.h"

// Raw temperature value thresholds for overheating detection.
// Derived from https://www.st.com/content/ccc/resource/technical/document/technical_note/23/dd/08/f8/ac/cf/47/83/DM00242307.pdf/files/DM00242307.pdf/jcr:content/translations/en.DM00242307.pdf
// which states that:   Temp in 'C = 42.5 + (rawValue / 480)
#define EXT_TEMPERATURE_THRESHOLD      ((int16_t)0xFB50) // Equivalent to 40'C
#define INT_TEMPERATURE_THRESHOLD      ((int16_t)0xFE20) // Equivalent to 41.5'C

ErrorCode_t TryToGetSingleVacuumMeasurement(uint16_t* pInternal,uint16_t* pExternal, uint16_t* pDiff);

#endif	/* PRESSURE_PART_2_H */

