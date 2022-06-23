/*****************************************************************************
 *   File        : Debug.c
 *
 *   Description : Implementation of verifying conditions during debug.
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

/**
  * To avoid the Build Warning "common/Debug.c:22:1: warning: ISO C requires a translation unit to 
  * contain at least one declaration [-Wempty-translation-unit]" for "Debug.c", the file has the 
  * (#include "Debug.h") statement. However, this causes a PC-lint (766) issue to occur.
  * The following comment is added to suppress the (766) message. (Where'.' = This file.)
  */ 
/*lint -efile(766,.) Include of header file ?Debug.h? not used in module ?Debug.c?*/
#include "Debug.h"

