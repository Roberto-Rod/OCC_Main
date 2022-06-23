#ifndef UNITY_HELPER_H
#define UNITY_HELPER_H

#include <stdint.h>

void unity_helper_dead_loop(void) __attribute__((address(0x00AEF0)));
void unity_helper_send_dbg_char(char);
void unity_helper_uart_init(void);

#endif //UNITY_HELPER_H