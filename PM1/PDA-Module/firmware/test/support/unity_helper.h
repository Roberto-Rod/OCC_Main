#ifndef UNITY_HELPER_H
#define UNITY_HELPER_H

#include <stdint.h>

//void unity_helper_dead_loop(void) __attribute__((address(0x9D07CFF0))); //If program memory was 512
void unity_helper_dead_loop(void) __attribute__((address(0x9D0F9FF0))); //If program memory was 1024
//void unity_helper_dead_loop(void) __attribute__((address(0x9D1F3FF0))); //If program memory was 2048
void unity_helper_send_dbg_char(char a);
void unity_helper_uart_init(void);

#ifndef TEST_DISABLE_HELPER_TMR2_INIT
void unity_helper_tmr2_init(void);
void unity_helper_tic(void);
uint32_t unity_helper_toc(void);
#endif //TEST_DISABLE_HELPER_TMR2_INIT

#endif //UNITY_HELPER_H