#include "pic16lf1509.h"
#include "MockTimer.h"
#include "Mockadc.h"
#include "MockPressure_Part1.h"
#include "MockPowerControl.h"
#include "Mockpin_manager.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "StateMachinePOST_internal.h"
#include "unity.h"




unsigned char NCO1CON;



ErrorCode_t vacReturnVal = EC_OK_E;



static uint16_t TestInternal = 0x4567;

static uint16_t TestExternal = 0x5678;

uint16_t vacVacuum = 0x1234;



uint8_t TXWBytes[16];

ErrorCode_t TXWReturnVal = EC_OK_E;

uint8_t TXWNumBytes;



uint8_t EEPROM_bytes[2048];

ErrorCode_t EEPROM_writeRetVal;

ErrorCode_t EEPROM_readRetVal;

uint8_t EEPROM_numBytesRead;

uint8_t EEPROM_numBytesWrite;

static bool_t reinitialiseEepromWrite = (bool_t) 

                                       0

                                            ;







static ErrorCode_t Stub_GetVacuum(uint16_t* pInternal, uint16_t* pExternal, uint16_t* theVac, int NumCalls)

{

  ErrorCode_t result = vacReturnVal;

  *pInternal = TestInternal;

  *pExternal = TestExternal;

  *theVac = vacVacuum;



  return result;

}





static ErrorCode_t Stub_TXWrite(uint8_t *data, uint8_t numBytes, int NumCall)

{

  ErrorCode_t result = TXWReturnVal;

  if(EC_OK_E == result)

  {

    for(int count = 0; count < numBytes; count++)

    {

      TXWBytes[count] = data[count];

    }

    TXWNumBytes = numBytes;

  }

  return result;

}





static ErrorCode_t Stub_EEPROMWrite(uint32_t address, uint8_t *data, uint8_t numBytes, int NumCall)

{

  ErrorCode_t result = EEPROM_writeRetVal;

  if((EC_OK_E == result) && (2048 > address + numBytes) && !reinitialiseEepromWrite)

  {

    for(int count = 0; count < numBytes; count++)

    {

      EEPROM_bytes[count + address] = data[count];

    }



  }









  reinitialiseEepromWrite = !reinitialiseEepromWrite;



  EEPROM_numBytesWrite = numBytes;

  return result;

}





static ErrorCode_t Stub_EEPROMRead(uint32_t address, uint8_t *data, uint8_t numBytes, int NumCall)

{

  ErrorCode_t result = EEPROM_readRetVal;

  if((EC_OK_E == result) && (2048 > address + numBytes))

  {

    for(int count = 0; count < numBytes; count++)

    {

      data[count] = EEPROM_bytes[count + address];

    }

  }

  EEPROM_numBytesRead = numBytes;

  return result;

}



void setGPIOs(uint8_t RC2Val, uint8_t RC3Val, uint8_t RC4Val, uint8_t RC5Val,

              uint8_t RC6Val, uint8_t RC7Val, uint8_t RB5Val)

{

    PORTCbits.RC2 = RC2Val;

    PORTCbits.RC3 = RC3Val;

    PORTCbits.RC4 = RC4Val;

    PORTCbits.RC5 = RC5Val;

    PORTCbits.RC6 = RC6Val;

    PORTCbits.RC7 = RC7Val;

    PORTBbits.RB5 = RB5Val;

}



void checkGPIOs(uint8_t RC2Val, uint8_t RC3Val, uint8_t RC4Val, uint8_t RC5Val,

                uint8_t RC6Val, uint8_t RC7Val, uint8_t RB5Val)

{

    UnityAssertBits((_U_SINT)((0x04)), (_U_SINT)((RC2Val)), (_U_SINT)((PORTCbits.RC2)), (

   ((void *)0)

   ), (_U_UINT)(129));

    UnityAssertBits((_U_SINT)((0x08)), (_U_SINT)((RC3Val)), (_U_SINT)((PORTCbits.RC3)), (

   ((void *)0)

   ), (_U_UINT)(130));

    UnityAssertBits((_U_SINT)((0x10)), (_U_SINT)((RC4Val)), (_U_SINT)((PORTCbits.RC4)), (

   ((void *)0)

   ), (_U_UINT)(131));

    UnityAssertBits((_U_SINT)((0x20)), (_U_SINT)((RC5Val)), (_U_SINT)((PORTCbits.RC5)), (

   ((void *)0)

   ), (_U_UINT)(132));

    UnityAssertBits((_U_SINT)((0x40)), (_U_SINT)((RC6Val)), (_U_SINT)((PORTCbits.RC6)), (

   ((void *)0)

   ), (_U_UINT)(133));

    UnityAssertBits((_U_SINT)((0x80)), (_U_SINT)((RC7Val)), (_U_SINT)((PORTCbits.RC7)), (

   ((void *)0)

   ), (_U_UINT)(134));

    UnityAssertBits((_U_SINT)((0x20)), (_U_SINT)((RB5Val)), (_U_SINT)((PORTBbits.RB5)), (

   ((void *)0)

   ), (_U_UINT)(135));

}



void setUp(void)

{

  reinitialiseEepromWrite = (bool_t) 

                           0

                                ;



  PM_Delay_CMockIgnore();

}



void tearDown(void)

{}



void test_getAndSetOfStateNumber(void)

{

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);

  iPOST_setSubStateNum(0x30);

  UnityAssertEqualNumber((_U_SINT)((0x30)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);

}



void test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_go(void)

{

  uint8_t retVal;





  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;

  iPOST_setSubStateNum(0xFF);





  setGPIOs(1, 1, 1, 1, 1, 1, 1);

  MP_SetReferenceVoltageBoost_CMockExpect(166, (0));

  retVal = iPOST_doPOST();



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((retVal)), (

 ((void *)0)

 ), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_00)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(170), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 0, 0, 0, 0);





  setGPIOs(1, 1, 1, 1, 1, 1, 1);

  retVal = iPOST_doPOST();

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((retVal)), (

 ((void *)0)

 ), (_U_UINT)(176), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_00)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(177), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 1, 1, 1, 1);

}



void test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_no(void)

{

  uint8_t retVal;





  PORTAbits.RA0 = 1;

  PORTAbits.RA1 = 0;

  iPOST_setSubStateNum(0xFF);





  setGPIOs(1, 1, 1, 1, 1, 1, 1);

  retVal = iPOST_doPOST();

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((retVal)), (

 ((void *)0)

 ), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_MAX)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 1, 1, 1, 1);





  setGPIOs(0, 0, 0, 0, 0, 0, 0);

  retVal = iPOST_doPOST();

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_MAX)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((retVal)), (

 ((void *)0)

 ), (_U_UINT)(201), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 0, 0, 0, 0);

}



void test_weCycleThroughTheStatesProperly(void)

{

  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;

  POSTSubState_t expectedState = POST_STATE_00;

  iPOST_setSubStateNum(POST_STATE_00);



  for(int count = 0; count < POST_STATE_MAX; count++)

  {



    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(215), UNITY_DISPLAY_STYLE_INT);





    iPOST_updateSubStateNum();

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(219), UNITY_DISPLAY_STYLE_INT);

    iPOST_updateSubStateNum();

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

    iPOST_updateSubStateNum();

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 ^= 0x01;

    iPOST_updateSubStateNum();

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(228), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 ^= 0x01;

    PORTAbits.RA1 ^= 0x01;

    iPOST_updateSubStateNum();

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(234), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 ^= 0x01;

    expectedState++;

    iPOST_updateSubStateNum();

  }



  UnityAssertEqualNumber((_U_SINT)((POST_STATE_00)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(242), UNITY_DISPLAY_STYLE_INT);

}



void test_State00SetsRC4(void)

{

  setGPIOs(0, 0, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State00())), (

 ((void *)0)

 ), (_U_UINT)(248), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 1, 0, 0, 0, 0);



  setGPIOs(1, 1, 0, 1, 1, 1, 1);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State00())), (

 ((void *)0)

 ), (_U_UINT)(252), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 1, 1, 1, 1);

}



void test_State01SetsReferenceVBoostReadsBoostVoltageADCAndTransmitsOnTX(void)

{

  TX_Write_StubWithCallback(Stub_TXWrite);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  setGPIOs(0, 0, 1, 0, 0, 0, 0);



  MP_SetReferenceVoltageBoost_CMockExpect(266, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(267, Boost_Voltage, 0xABCD);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State01())), (

 ((void *)0)

 ), (_U_UINT)(269), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 1, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(271), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(272), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xCD)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(273), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAB)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(275), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);

  MP_SetReferenceVoltageBoost_CMockExpect(281, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(282, Boost_Voltage, 0x1357);



  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State01())), (

 ((void *)0)

 ), (_U_UINT)(284), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 1, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(287), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(288), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(289), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(290), UNITY_DISPLAY_STYLE_INT);

}



void test_State02SetsRC7AndClearsVBoost(void)

{

  setGPIOs(0, 0, 0, 0, 0, 0, 0);

  MP_SetReferenceVoltageBoost_CMockExpect(296, (0));

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State02())), (

 ((void *)0)

 ), (_U_UINT)(297), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 0, 0, 1, 0);



  setGPIOs(1, 1, 1, 1, 1, 0, 1);

  MP_SetReferenceVoltageBoost_CMockExpect(301, (0));

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State02())), (

 ((void *)0)

 ), (_U_UINT)(302), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 1, 1, 1, 1);

}



void test_State03SetsRC5ClearsRC7(void)

{

  setGPIOs(0, 0, 0, 0, 0, 1, 0);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State03())), (

 ((void *)0)

 ), (_U_UINT)(309), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 1, 0, 0, 0);



  setGPIOs(1, 1, 1, 0, 1, 1, 1);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State03())), (

 ((void *)0)

 ), (_U_UINT)(313), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 1, 1, 0, 1);

}



void test_State04SetsRC2ClearsRC5ReadsAndTransmitsTheExternalVacuum(void)

{

  GetVacuum_StubWithCallback(Stub_GetVacuum);

  TX_Write_StubWithCallback(Stub_TXWrite);



  setGPIOs(0, 1, 1, 1, 1, 1, 1);

  vacReturnVal = EC_OK_E;

  vacVacuum = 0x5678;

  TestExternal = 0x1234;

  TestInternal = 0x3456;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State04())), (

 ((void *)0)

 ), (_U_UINT)(331), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 0, 1, 1, 1);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(333), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x04)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(334), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x34)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(335), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x12)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(336), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(337), UNITY_DISPLAY_STYLE_INT);





  setGPIOs(0, 0, 0, 1, 0, 0, 0);

  vacReturnVal = EC_FAILED_E;

  vacVacuum = 0x5678;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);



  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State04())), (

 ((void *)0)

 ), (_U_UINT)(347), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 0, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(349), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(350), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(351), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(352), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(353), UNITY_DISPLAY_STYLE_INT);





  vacReturnVal = EC_OK_E;

  vacVacuum = 0x5678;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State04())), (

 ((void *)0)

 ), (_U_UINT)(361), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(362), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(363), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(364), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(365), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(366), UNITY_DISPLAY_STYLE_INT);

}



void test_State05ClearsRC2ReadsAndTransmitsTheInternalVacuum(void)

{

  GetVacuum_StubWithCallback(Stub_GetVacuum);

  TX_Write_StubWithCallback(Stub_TXWrite);





  setGPIOs(1, 1, 1, 1, 1, 1, 1);

  vacReturnVal = EC_OK_E;

  vacVacuum = 0x2345;

  TestExternal = 0x3456;

  TestInternal = 0x1234;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State05())), (

 ((void *)0)

 ), (_U_UINT)(384), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 1, 1, 1, 1, 1, 1);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(386), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x05)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(387), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x34)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(388), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x12)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(389), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(390), UNITY_DISPLAY_STYLE_INT);





  setGPIOs(1, 0, 0, 0, 0, 0, 0);

  vacReturnVal = EC_FAILED_E;

  vacVacuum = 0x5678;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);



  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State05())), (

 ((void *)0)

 ), (_U_UINT)(400), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(402), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(403), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(404), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(405), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(406), UNITY_DISPLAY_STYLE_INT);





  vacReturnVal = EC_OK_E;

  vacVacuum = 0x5678;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State05())), (

 ((void *)0)

 ), (_U_UINT)(414), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(415), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(416), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(417), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(418), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(419), UNITY_DISPLAY_STYLE_INT);

}



void test_State06WritesToTheEEPROMAndReadsItBack(void)

{

  I2E_Write_StubWithCallback(Stub_EEPROMWrite);

  I2E_Read_StubWithCallback(Stub_EEPROMRead);

  TX_Write_StubWithCallback(Stub_TXWrite);





  EEPROM_writeRetVal = EC_OK_E;

  EEPROM_readRetVal = EC_OK_E;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  MP_EnableExternalPeripheralsSupply_CMockExpect(434);

  MP_DisableExternalPeripheralsSupply_CMockExpect(435);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State06())), (

 ((void *)0)

 ), (_U_UINT)(437), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(438), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x06)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(439), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x03)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(440), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x03)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(441), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(442), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((EEPROM_bytes[0])), (

 ((void *)0)

 ), (_U_UINT)(443), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((EEPROM_bytes[1])), (

 ((void *)0)

 ), (_U_UINT)(444), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesRead)), (

 ((void *)0)

 ), (_U_UINT)(445), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesWrite)), (

 ((void *)0)

 ), (_U_UINT)(446), UNITY_DISPLAY_STYLE_INT);





  EEPROM_writeRetVal = EC_FAILED_E;

  EEPROM_readRetVal = EC_OK_E;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  memset(EEPROM_bytes, 0, 16);

  MP_EnableExternalPeripheralsSupply_CMockExpect(455);

  MP_DisableExternalPeripheralsSupply_CMockExpect(456);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State06())), (

 ((void *)0)

 ), (_U_UINT)(458), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(459), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x06)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(460), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x02)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(461), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(462), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(463), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((EEPROM_bytes[0])), (

 ((void *)0)

 ), (_U_UINT)(464), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((EEPROM_bytes[1])), (

 ((void *)0)

 ), (_U_UINT)(465), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesRead)), (

 ((void *)0)

 ), (_U_UINT)(466), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesWrite)), (

 ((void *)0)

 ), (_U_UINT)(467), UNITY_DISPLAY_STYLE_INT);





  EEPROM_writeRetVal = EC_OK_E;

  EEPROM_readRetVal = EC_FAILED_E;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  memset(EEPROM_bytes, 0, 16);

  MP_EnableExternalPeripheralsSupply_CMockExpect(476);

  MP_DisableExternalPeripheralsSupply_CMockExpect(477);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State06())), (

 ((void *)0)

 ), (_U_UINT)(479), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(480), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x06)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(481), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(482), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(483), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(484), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((EEPROM_bytes[0])), (

 ((void *)0)

 ), (_U_UINT)(485), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((EEPROM_bytes[1])), (

 ((void *)0)

 ), (_U_UINT)(486), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesRead)), (

 ((void *)0)

 ), (_U_UINT)(487), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesWrite)), (

 ((void *)0)

 ), (_U_UINT)(488), UNITY_DISPLAY_STYLE_INT);





  EEPROM_writeRetVal = EC_OK_E;

  EEPROM_readRetVal = EC_OK_E;

  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);

  MP_EnableExternalPeripheralsSupply_CMockExpect(496);

  MP_DisableExternalPeripheralsSupply_CMockExpect(497);



  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State06())), (

 ((void *)0)

 ), (_U_UINT)(499), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(500), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(501), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(502), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(503), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(504), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAA)), (_U_SINT)((EEPROM_bytes[0])), (

 ((void *)0)

 ), (_U_UINT)(505), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x55)), (_U_SINT)((EEPROM_bytes[1])), (

 ((void *)0)

 ), (_U_UINT)(506), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesRead)), (

 ((void *)0)

 ), (_U_UINT)(507), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((EEPROM_numBytesWrite)), (

 ((void *)0)

 ), (_U_UINT)(508), UNITY_DISPLAY_STYLE_INT);

}



void test_State07TogglesRC6ClearsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX(void)

{

  TX_Write_StubWithCallback(Stub_TXWrite);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  NCO1CON = 0xFF;

  setGPIOs(0, 1, 0, 0, 0, 0, 0);

  MP_SetReferenceVoltageBoost_CMockExpect(521, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(522, HBridge_Current, 0xABCD);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State07())), (

 ((void *)0)

 ), (_U_UINT)(524), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 0, 0, 0, 1, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((NCO1CON)), (

 ((void *)0)

 ), (_U_UINT)(526), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(527), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x07)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(528), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xCD)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(529), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAB)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(530), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(531), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  NCO1CON = 0xFF;

  MP_SetReferenceVoltageBoost_CMockExpect(538, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(539, HBridge_Current, 0x7654);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State07())), (

 ((void *)0)

 ), (_U_UINT)(541), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 0, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((NCO1CON)), (

 ((void *)0)

 ), (_U_UINT)(543), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(544), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x07)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(545), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x54)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(546), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x76)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(547), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(548), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);

  setGPIOs(0, 1, 1, 1, 0, 1, 1);

  NCO1CON = 0xFF;

  MP_SetReferenceVoltageBoost_CMockExpect(556, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(557, HBridge_Current, 0x1357);



  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State07())), (

 ((void *)0)

 ), (_U_UINT)(559), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 0, 1, 1, 1, 1, 1);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((NCO1CON)), (

 ((void *)0)

 ), (_U_UINT)(561), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(562), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(563), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(564), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(565), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(566), UNITY_DISPLAY_STYLE_INT);

}





void test_State08TogglesRC6SetsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX(void)

{

  TX_Write_StubWithCallback(Stub_TXWrite);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  setGPIOs(0, 0, 0, 0, 0, 0, 0);

  NCO1CON = 0xFF;

  MP_SetReferenceVoltageBoost_CMockExpect(580, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(581, HBridge_Current, 0xABCD);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State08())), (

 ((void *)0)

 ), (_U_UINT)(583), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 0, 0, 1, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((NCO1CON)), (

 ((void *)0)

 ), (_U_UINT)(585), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(586), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x08)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(587), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xCD)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(588), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xAB)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(589), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(590), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  NCO1CON = 0xFF;

  MP_SetReferenceVoltageBoost_CMockExpect(597, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(598, HBridge_Current, 0x7654);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State08())), (

 ((void *)0)

 ), (_U_UINT)(600), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((NCO1CON)), (

 ((void *)0)

 ), (_U_UINT)(602), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(603), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x08)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(604), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x54)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(605), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x76)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(606), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(607), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);

  setGPIOs(0, 0, 1, 1, 1, 1, 1);

  NCO1CON = 0xFF;

  MP_SetReferenceVoltageBoost_CMockExpect(615, ((uint8_t)18));

  ADC_GetConversion_CMockExpectAndReturn(616, HBridge_Current, 0x1357);



  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State08())), (

 ((void *)0)

 ), (_U_UINT)(618), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 1, 0, 1, 1);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((NCO1CON)), (

 ((void *)0)

 ), (_U_UINT)(620), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(621), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(622), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(623), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x000)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(624), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(625), UNITY_DISPLAY_STYLE_INT);

}

void test_State09ClearsRC3SetsDACto0ReadsRA5AndTransmitsRA5OnTX(void)

{

  TX_Write_StubWithCallback(Stub_TXWrite);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  setGPIOs(1, 1, 1, 1, 1, 1, 1);

  MP_SetReferenceVoltageBoost_CMockExpect(636, (0));

  PORTAbits.RA5 = 0;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State09())), (

 ((void *)0)

 ), (_U_UINT)(639), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 0, 1, 1, 1, 1, 1);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(641), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x09)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(642), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x0)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(643), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x0)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(644), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(645), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);

  MP_SetReferenceVoltageBoost_CMockExpect(651, (0));

  setGPIOs(0, 1, 0, 0, 0, 0, 0);

  PORTAbits.RA5 = 1;



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State09())), (

 ((void *)0)

 ), (_U_UINT)(655), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(657), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x09)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(658), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x01)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(659), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(660), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(661), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);

  MP_SetReferenceVoltageBoost_CMockExpect(667, (0));



  setGPIOs(0, 1, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_State09())), (

 ((void *)0)

 ), (_U_UINT)(670), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(672), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(673), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(674), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x000)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(675), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(676), UNITY_DISPLAY_STYLE_INT);

}



void test_State10SetsRB5(void)

{

  setGPIOs(0, 0, 0, 0, 0, 0, 0);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State10())), (

 ((void *)0)

 ), (_U_UINT)(682), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(0, 0, 0, 0, 0, 0, 1);



  setGPIOs(1, 1, 1, 1, 1, 1, 0);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_State10())), (

 ((void *)0)

 ), (_U_UINT)(686), UNITY_DISPLAY_STYLE_INT);

  checkGPIOs(1, 1, 1, 1, 1, 1, 1);

}



void test_StateErrorSendsAMessageOnTheTXLine(void)

{

  TX_Write_StubWithCallback(Stub_TXWrite);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_OK_E;

  memset(TXWBytes, 0, 16);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((iPOST_StateError())), (

 ((void *)0)

 ), (_U_UINT)(699), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(700), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(701), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x0A)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(702), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xA0)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(703), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(704), UNITY_DISPLAY_STYLE_INT);





  TXWNumBytes = 0xFF;

  TXWReturnVal = EC_FAILED_E;

  memset(TXWBytes, 0, 16);



  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((iPOST_StateError())), (

 ((void *)0)

 ), (_U_UINT)(711), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0xFF)), (_U_SINT)((TXWNumBytes)), (

 ((void *)0)

 ), (_U_UINT)(712), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[0])), (

 ((void *)0)

 ), (_U_UINT)(713), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x00)), (_U_SINT)((TXWBytes[1])), (

 ((void *)0)

 ), (_U_UINT)(714), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0x000)), (_U_SINT)((TXWBytes[2])), (

 ((void *)0)

 ), (_U_UINT)(715), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((TXWBytes[0]^TXWBytes[1]^TXWBytes[2])), (_U_SINT)((TXWBytes[3])), (

 ((void *)0)

 ), (_U_UINT)(716), UNITY_DISPLAY_STYLE_INT);

}



void test_InitInitialiseTransmit(void)

{

  TX_Init_CMockExpect(721);

  I2E_Init_CMockExpect(722);

  iPOST_Init();

}
