/*****************************************************************************
 *   File        : Transmit.h
 *
 *   Description : Header for implementation of transmit data over the serial
 * port (EUSART). TX only.
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

#ifndef PICOONBOARD_TRANSMIT_H
#define PICOONBOARD_TRANSMIT_H

#include "PaTypes.h"
#include "ErrorCode.h"

void TX_Init(void);

ErrorCode_t  TX_Write(const uint8_t *data, uint8_t numBytes);


#endif //PICOONBOARD_TRANSMIT_H
