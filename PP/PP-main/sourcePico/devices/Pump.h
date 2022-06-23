/*****************************************************************************
 *   File        : Pump.h
 *
 *   Description : Header for implementation of Pump controls
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

#ifndef PUMP_H
#define	PUMP_H

#include "PaTypes.h"
#include "ErrorCode.h"

ErrorCode_t PumpActivate(bool_t);
bool_t isPumpActivated(void);

#endif	/* PUMP_H */

