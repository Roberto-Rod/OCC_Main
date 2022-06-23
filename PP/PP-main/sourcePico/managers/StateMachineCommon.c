/********************************************************************************
* 
* File : StateMachineCommon.c
*
* Description : Implements common functionalities used across the device state machine.
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */


/**
  * To avoid the Build Warning "managers/StateMachineCommon.c:25:1: warning: ISO C 
  * requires a translation unit to contain at least one declaration [-Wempty-translation-unit]" for 
  * "StateMachineCommon.c", the file has the (#include "StateMachineCommon.h") statement.
  * However, this causes a PC-lint (766) issue to occur.
  * The following comment is added to suppress the (766) message. (Where'.' = This file.)
  */
/*lint -efile(766,.) Include of header file ?StateMachineCommon.h? not used in module ?StateMachineCommon.c?*/
#include "StateMachineCommon.h"

