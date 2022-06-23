#include "Mocki2c.h"
#include "I2CEEPROM.h"
#include "unity.h"
#include "xc.h"












I2C_MESSAGE_STATUS insertStatus = I2C_MESSAGE_COMPLETE;

uint8_t doChecks = 0;

uint8_t expectedCount = 2;











static void

Stub_insertTRB(uint8_t count, I2C_TRANSACTION_REQUEST_BLOCK *ptrb_list, I2C_MESSAGE_STATUS *pflag, int NumCall)

{

  *pflag = insertStatus;

  if (doChecks)

  {

    UnityAssertEqualNumber((_U_SINT)((expectedCount)), (_U_SINT)((count)), (

   ((void *)0)

   ), (_U_UINT)(43), UNITY_DISPLAY_STYLE_INT);

  }

}







void setUp(void)

{

}



void tearDown(void)

{}





void test_InitJustCallsTheLowerLevelInit(void)

{

  I2C_Initialize_CMockExpect(59);

  I2E_Init();

}





void test_ReadDoesRangeChecking(void)

{

  ErrorCode_t result = EC_OK_E;

  uint8_t data[4] = {1, 4, 9, 16};



  I2C_MasterWriteTRBBuild_CMockIgnore();

  I2C_MasterReadTRBBuild_CMockIgnore();

  I2C_MasterTRBInsert_StubWithCallback(Stub_insertTRB);

  insertStatus = I2C_MESSAGE_COMPLETE;





  result = I2E_Read(0, 

                      ((void *)0)

                          , 4);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(76), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Read(0, data, 0);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(80), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Read((262144), data, 1);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(84), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Read((262144)-1, data, 1);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(88), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Read(250, data, 7);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(92), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Read(0, data, 4);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Read((262144)-5, data, 4);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);

}





void test_ReadHappyCase(void)

{

  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[4] = {1, 4, 9, 16};

  uint8_t addrData[2] = {0, 3};



  I2C_MasterWriteTRBBuild_CMockExpectWithArray(111, 

 ((void *)0)

 , 0, addrData, 2, 2, 0x50);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(112);



  I2C_MasterReadTRBBuild_CMockExpect(114, 

 ((void *)0)

 , data, 4, 0x50);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_ptrb(115);



  I2C_MasterTRBInsert_CMockExpect(117, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(118);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(119);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(120, &ptrVal, sizeof(*&ptrVal));



  result = I2E_Read(3, data, 4);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(123), UNITY_DISPLAY_STYLE_INT);

 }





void test_ReadHappyRetry(void)

{

  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;

  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_COMPLETE;



  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[5] = {1, 4, 9, 16, 25};

  uint8_t addrData[2] = {0, 17};



  I2C_MasterWriteTRBBuild_CMockExpectWithArray(136, 

 ((void *)0)

 , 0, addrData, 2, 2, 0x50);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(137);



  I2C_MasterReadTRBBuild_CMockExpect(139, 

 ((void *)0)

 , data, 5, 0x50);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_ptrb(140);



  I2C_MasterTRBInsert_CMockExpect(142, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(143);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(144);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(145, &ptrVal1, sizeof(*&ptrVal1));



  I2C_MasterTRBInsert_CMockExpect(147, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(148);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(149);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(150, &ptrVal2, sizeof(*&ptrVal2));



  result = I2E_Read(17, data, 5);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(153), UNITY_DISPLAY_STYLE_INT);

}





void test_ReadRetryFailure(void)

{

  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;

  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_ADDRESS_NO_ACK;



  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[6] = {1, 4, 9, 16, 25, 36};

  uint8_t addrData[2] = {1, 4};



  I2C_MasterWriteTRBBuild_CMockExpectWithArray(166, 

 ((void *)0)

 , 0, addrData, 2, 2, 0x50);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(167);



  I2C_MasterReadTRBBuild_CMockExpect(169, 

 ((void *)0)

 , data, 6, 0x50);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_ptrb(170);



  I2C_MasterTRBInsert_CMockExpect(172, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(173);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(174);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(175, &ptrVal1, sizeof(*&ptrVal1));



  I2C_MasterTRBInsert_CMockExpect(177, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(178);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(179);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(180, &ptrVal2, sizeof(*&ptrVal2));



  result = I2E_Read(260, data, 6);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);

}





void test_WriteDoesRangeChecking(void)

{

  ErrorCode_t result = EC_OK_E;

  uint8_t data[4] = {1, 4, 9, 16};



  I2C_MasterWriteTRBBuild_CMockIgnore();

  I2C_MasterReadTRBBuild_CMockIgnore();

  I2C_MasterTRBInsert_StubWithCallback(Stub_insertTRB);

  insertStatus = I2C_MESSAGE_COMPLETE;





  result = I2E_Write(0, 

                       ((void *)0)

                           , 4);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(199), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Write(0, data, 0);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(203), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Write((262144), data, 1);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(207), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Write((262144)-1, data, 1);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(211), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Write(250, data, 7);

  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(215), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Write(0, data, 4);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(219), UNITY_DISPLAY_STYLE_INT);





  result = I2E_Write((262144)-5, data, 4);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);

}





void test_WriteHappyCase(void)

{

  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[4] = {1, 4, 9, 16};

  uint8_t addrData[2] = {0, 3};

  uint8_t EEPROMBusAddr = 0x50;



  I2C_MasterWriteTRBBuild_CMockExpectWithArray(235, 

 ((void *)0)

 , 0, addrData, 2, 6, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(236);



  I2C_MasterTRBInsert_CMockExpect(238, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(239);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(240);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(241, &ptrVal, sizeof(*&ptrVal));



  result = I2E_Write(3, data, 4);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(244), UNITY_DISPLAY_STYLE_INT);

 }





void test_WriteHappyRetry(void)

{

  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;

  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_COMPLETE;



  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[5] = {1, 4, 9, 16, 25};

  uint8_t addrData[2] = {1, 1};



  I2C_MasterWriteTRBBuild_CMockExpectWithArray(257, 

 ((void *)0)

 , 0, addrData, 2, 7, 0x50);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(258);



  I2C_MasterTRBInsert_CMockExpect(260, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(261);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(262);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(263, &ptrVal1, sizeof(*&ptrVal1));



  I2C_MasterTRBInsert_CMockExpect(265, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(266);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(267);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(268, &ptrVal2, sizeof(*&ptrVal2));



  result = I2E_Write(257, data, 5);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(271), UNITY_DISPLAY_STYLE_INT);

}





void test_WriteRetryFailure(void)

{

  I2C_MESSAGE_STATUS ptrVal1 = I2C_MESSAGE_ADDRESS_NO_ACK;

  I2C_MESSAGE_STATUS ptrVal2 = I2C_MESSAGE_ADDRESS_NO_ACK;



  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[6] = {1, 4, 9, 16, 25, 36};

  uint8_t addrData[2] = {0, 7};



  I2C_MasterWriteTRBBuild_CMockExpectWithArray(284, 

 ((void *)0)

 , 0, addrData, 2, 8, 0x50);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(285);



  I2C_MasterTRBInsert_CMockExpect(287, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(288);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(289);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(290, &ptrVal1, sizeof(*&ptrVal1));



  I2C_MasterTRBInsert_CMockExpect(292, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(293);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(294);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(295, &ptrVal2, sizeof(*&ptrVal2));



  result = I2E_Write(7, data, 6);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(298), UNITY_DISPLAY_STYLE_INT);

}
