/*****************************************************************************
 *   File        : LEDType.h
 *
 *   Description : Header for implementation of LED Type interface.
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

#ifndef LED_TYPE_H
#define	LED_TYPE_H

#include "PaTypes.h"

typedef enum
{
    LD_GREEN_E = 0,
    LD_ORANGE_E,
    LD_MAX_E
} LED_Colour_t;

#endif	/* LED_TYPE_H */

