#include "unity.h"
#include "UnityHelper.h"

#include <stdint.h>
#include <stdbool.h>
#include "cmd.h"
#include "Mockdebug.h"
#include "Mockfsl_debug_console.h"
#include "Mockqdc.h"

#define MAX_DATA_LENGTH         (10u)

#define RX_HEAD_1               (0xAFu)
#define RX_HEAD_2               (0x45u)
#define RX_TAIL_1               (0xE1u)
#define RX_TAIL_2               (0xE2u)

#define CMD_PING                (0x01u) 
#define CMD_PWR_ON              (0x02u)
#define CMD_PWR_OFF             (0x03u)
#define CMD_SIM_BTN             (0x04u)

typedef union
{
    struct part{
        uint8_t cmd;
        uint8_t len; 
        char data[MAX_DATA_LENGTH]; 
    }part;
    uint8_t full[MAX_DATA_LENGTH+2u];
} rx_pack_t;

extern uint8_t g_state;
extern uint8_t g_data_index;  
extern rx_pack_t g_pack; 
extern const char gp_ping_message[];
extern const char gp_pwr_on_message[];
extern const char gp_forced_off_message[];
extern const char gp_delayed_off_message[];
extern const char gp_button_press_message[];
extern const char gp_on[];
extern const char gp_forced_off[];
extern const char gp_delayed_off[]; 
extern const char gp_button[]; 

void setUp(void)
{
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void tearDown(void)
{
  g_state = 0;
  g_data_index = 0;
}

void test_cmd_handler_ascii_character(void)
{
  bool result = CMD_data_handler('0');
  
  TEST_ASSERT_FALSE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_rx_head1(void)
{
  bool result = CMD_data_handler(RX_HEAD_1);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(1, g_state);
}

void test_cmd_handler_rx_head2_error(void)
{
  g_state = 1;

  DbgConsole_Printf_ExpectAnyArgsAndReturn(0);

  bool result = CMD_data_handler('0');
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_rx_head2(void)
{
  g_state = 1;
  
  bool result = CMD_data_handler(RX_HEAD_2);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(2, g_state);
}

void test_cmd_handler_invalid_command(void)
{
  g_state = 2;
  
  DbgConsole_Printf_ExpectAnyArgsAndReturn(0);

  bool result = CMD_data_handler(0);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_command(void)
{
  g_state = 2;
  
  bool result = CMD_data_handler(CMD_PING);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(3, g_state);
}

void test_cmd_handler_data_length_error(void)
{
  g_state = 3;
  
  DbgConsole_Printf_ExpectAnyArgsAndReturn(0);
  
  bool result = CMD_data_handler(MAX_DATA_LENGTH + 1);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_data_length_zero(void)
{
  g_state = 3;
  
  bool result = CMD_data_handler(0);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(4, g_state);
}

void test_cmd_handler_rx_tail1_error(void)
{
  g_state = 4;
  g_data_index = 0;
  g_pack.part.len = 0;
  
  DbgConsole_Printf_ExpectAnyArgsAndReturn(0);

  bool result = CMD_data_handler('0');
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_rx_tail1(void)
{
  g_state = 4;
  g_data_index = 0;
  g_pack.part.len = 0;
 
  bool result = CMD_data_handler(RX_TAIL_1);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(5, g_state);
}

void test_cmd_handler_rx_tail2_error(void)
{
  g_state = 5;
  
  DbgConsole_Printf_ExpectAnyArgsAndReturn(0);

  bool result = CMD_data_handler('0');
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_rx_tail2(void)
{
  g_state = 5;
  
  bool result = CMD_data_handler(RX_TAIL_2);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(6, g_state);
}

void test_cmd_handler_checksum_error(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_PING;
  g_pack.part.len = 0;

  for (uint8_t i = 0; i < MAX_DATA_LENGTH; i++)
  {
    g_pack.part.data[0] = 0;
  }
  
  DbgConsole_Printf_ExpectAnyArgsAndReturn(0);
  DbgConsole_Printf_ExpectAnyArgsAndReturn(0);

  bool result = CMD_data_handler(RX_TAIL_2);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_ping(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_PING;
  g_pack.part.len = 0;

  for (uint8_t i = 0; i < MAX_DATA_LENGTH; i++)
  {
    g_pack.part.data[0] = 0;
  }
  
  DbgConsole_Printf_ExpectAndReturn(gp_ping_message, 0);

  bool result = CMD_data_handler(0xFE);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_power_on_error(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_PWR_ON;
  g_pack.part.len = 2;
  sprintf(g_pack.part.data, gp_on);
  
  // swap data characters to introduce an error without affecting checksum
  char temp = g_pack.part.data[0];
  g_pack.part.data[0] = g_pack.part.data[1];
  g_pack.part.data[1] = temp;
    
  bool result = CMD_data_handler(0x5E);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_power_on(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_PWR_ON;
  g_pack.part.len = strlen(gp_on);
  sprintf(g_pack.part.data, gp_on);
    
  DbgConsole_Printf_ExpectAndReturn(gp_pwr_on_message, 0);

  bool result = CMD_data_handler(0x5E);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_power_off_error(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_PWR_OFF;
  g_pack.part.len = strlen(gp_forced_off);
  sprintf(g_pack.part.data, gp_forced_off);
    
  // swap data characters to introduce an error without affecting checksum
  char temp = g_pack.part.data[0];
  g_pack.part.data[0] = g_pack.part.data[1];
  g_pack.part.data[1] = temp;
    
  bool result = CMD_data_handler(0x77);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_forced_power_off(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_PWR_OFF;
  g_pack.part.len = strlen(gp_forced_off);
  sprintf(g_pack.part.data, gp_forced_off);
    
  DbgConsole_Printf_ExpectAndReturn(gp_forced_off_message, 0);

  bool result = CMD_data_handler(0x77);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_delayed_power_off(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_PWR_OFF;
  g_pack.part.len = strlen(gp_delayed_off);
  sprintf(g_pack.part.data, gp_delayed_off);
    
  DbgConsole_Printf_ExpectAndReturn(gp_delayed_off_message, 0);

  bool result = CMD_data_handler(0x79);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_button_error(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_SIM_BTN;
  g_pack.part.len = strlen(gp_button) + sizeof(uint16_t);
  sprintf(g_pack.part.data, gp_button);
  g_pack.part.data[3] = 0x00;
  g_pack.part.data[4] = 0x0A;
    
  // swap data characters to introduce an error without affecting checksum
  char temp = g_pack.part.data[0];
  g_pack.part.data[0] = g_pack.part.data[1];
  g_pack.part.data[1] = temp;

  bool result = CMD_data_handler(0x08);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}

void test_cmd_handler_button(void)
{
  g_state = 6;
  g_pack.part.cmd = CMD_SIM_BTN;
  g_pack.part.len = strlen(gp_button) + sizeof(uint16_t);
  sprintf(g_pack.part.data, gp_button);
  g_pack.part.data[3] = 0x00;
  g_pack.part.data[4] = 0x0A;
    
  DbgConsole_Printf_ExpectAndReturn(gp_button_press_message, 0);

  bool result = CMD_data_handler(0x08);
  
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_EQUAL_UINT8(0, g_state);
}
