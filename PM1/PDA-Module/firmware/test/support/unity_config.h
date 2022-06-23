#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

#include "unity_helper.h"

#define UNITY_OUTPUT_COMPLETE() unity_helper_dead_loop()

#include "definitions.h"

#define UNITY_OUTPUT_START() SYS_Initialize( NULL )

#define UNITY_OUTPUT_CHAR(a) (void)unity_helper_send_dbg_char(a)
#define UNITY_OUTPUT_CHAR_HEADER_DECLARATION unity_helper_send_dbg_char(char)

#endif //UNITY_CONFIG_H