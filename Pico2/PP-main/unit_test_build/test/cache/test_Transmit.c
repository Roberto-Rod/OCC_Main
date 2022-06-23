#include "Assert.h"
#include "Mockeusart.h"
#include "Transmit.h"
#include "unity.h"




void setUp(void)

{

}



void tearDown(void)

{}







void test_InitDoesNothing(void)

{

  EUSART_Initialize_CMockExpect(35);

  TX_Init();

}





void test_TransmitDoesRangeCheckingOnDataPointer(void)

{

  uint8_t data[4] = {1, 4, 9, 16};

  ErrorCode_t result = TX_Write(

                               ((void *)0)

                                   , 4);

  UnityFail( (("Assert should be called prior to this function")), (_U_UINT)(44));

}



void test_TransmitDoesRangeCheckingonDataSize(void)

{

  uint8_t data[4] = {1, 4, 9, 16};

  ErrorCode_t result = TX_Write(data, 0);

  UnityFail( (("Assert should be called prior to this function")), (_U_UINT)(51));

}







void test_TransmitCallsEUSARTWriteForEachCharacter(void)

{

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[4] = {1, 4, 9, 16};



  EUSART_Write_CMockExpect(61, 1);

  EUSART_Write_CMockExpect(62, 4);

  EUSART_Write_CMockExpect(63, 9);

  EUSART_Write_CMockExpect(64, 16);

  result = TX_Write(data, 4);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(66), UNITY_DISPLAY_STYLE_INT);

}
