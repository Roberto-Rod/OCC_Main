/*****************************************************************************
 *   File        : Dbg.h
 *
 *   Description : Header for Debugging Utilities module.
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

#ifndef DBG_H
#define	PRESSURE_PART_1_H

#include "PaTypes.h"
#include "ErrorCode.h"

void Dbg_RecordPwmFrequency(const uint16_t Frequency);
void Dbg_StartPwmFrequencyRecording(void);

#endif //DBG_H