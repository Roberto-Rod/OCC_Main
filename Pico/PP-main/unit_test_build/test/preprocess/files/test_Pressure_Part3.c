#include "Mocki2c.h"
#include "MockTimer.h"
#include "MockPressure_Part4.h"
#include "Pressure_Part3.h"
#include "unity.h"




typedef enum {

    PS_NONE_E = 0,

    PS_EXTERNAL_E,

    PS_INTERNAL_E,

    PS_BOTH_E

} PressureSensorFail_t;











static uint8_t ExtPressureDeviceWriteCount = 0;

static uint8_t IntPressureDeviceWriteCount = 0;

static uint8_t ExtPressureDeviceReadCount = 0;

static uint8_t IntPressureDeviceReadCount = 0;

static PressureSensorFail_t SensorWriteForceFail = PS_NONE_E;

static PressureSensorFail_t SensorReadForceFail = PS_NONE_E;

static uint8_t WriteDataBufferTest[20];

static uint8_t ReadDataBufferTest[20];





static bool_t Stub_PM_WritePressureSensors(uint8_t Device, uint8_t DataLength, uint8_t *DataBuffer, int NumCall)

{

  bool_t result = (bool_t) 

                 1

                     ;



  if (0x5D == Device)

  {

    ExtPressureDeviceWriteCount++;

    result = ((PS_EXTERNAL_E == SensorWriteForceFail) || (PS_BOTH_E == SensorWriteForceFail)) ? (bool_t) 

                                                                                               0

                                                                                                    :(bool_t) 

                                                                                                     1

                                                                                                         ;

  }

  else if (0x5C == Device)

  {

    IntPressureDeviceWriteCount++;

    result = ((PS_INTERNAL_E == SensorWriteForceFail) || (PS_BOTH_E == SensorWriteForceFail))? (bool_t) 

                                                                                               0

                                                                                                    :(bool_t) 

                                                                                                     1

                                                                                                         ;

  }

  else

  {

    result = (bool_t) 

            0

                 ;

  }



  memcpy(WriteDataBufferTest, DataBuffer, DataLength);



  return result;

}





static bool_t Stub_PM_ReadPressureSensors(uint8_t Device, uint8_t DataLength, uint8_t DataAddress, uint8_t *DataBuffer, int NumCall)

{

  bool_t result = (bool_t) 

                 1

                     ;



  if (0x5D == Device)

  {

    ExtPressureDeviceReadCount++;

    result = ((PS_EXTERNAL_E == SensorReadForceFail) || (PS_BOTH_E == SensorReadForceFail)) ? (bool_t) 

                                                                                             0

                                                                                                  :(bool_t) 

                                                                                                   1

                                                                                                       ;

  }

  else if (0x5C == Device)

  {

    IntPressureDeviceReadCount++;

    result = ((PS_INTERNAL_E == SensorReadForceFail) || (PS_BOTH_E == SensorReadForceFail)) ? (bool_t) 

                                                                                             0

                                                                                                  :(bool_t) 

                                                                                                   1

                                                                                                       ;

  }

  else

  {

    result = (bool_t) 

            0

                 ;

  }



  memcpy(DataBuffer, ReadDataBufferTest,DataLength);



  return result;

}





void setUp(void)

{

  ExtPressureDeviceWriteCount = 0;

  IntPressureDeviceWriteCount = 0;

  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;



  SensorWriteForceFail = PS_NONE_E;

  SensorReadForceFail = PS_NONE_E;



  memset(ReadDataBufferTest, '\0', sizeof(ReadDataBufferTest));

  memset(WriteDataBufferTest, '\0', sizeof(WriteDataBufferTest));



  PM_WritePressureSensors_StubWithCallback(Stub_PM_WritePressureSensors);

  PM_ReadPressureSensors_StubWithCallback(Stub_PM_ReadPressureSensors);



}



void tearDown(void)

{}







void test_InitialisePressureSensorsAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = ((uint8_t)~0x80);



  if ((EC_OK_E == PM_InitSensors())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(127)));};

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureDeviceWriteCount)), (

 ((void *)0)

 ), (_U_UINT)(128), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IntPressureDeviceWriteCount)), (

 ((void *)0)

 ), (_U_UINT)(129), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureDeviceReadCount)), (

 ((void *)0)

 ), (_U_UINT)(130), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IntPressureDeviceReadCount)), (

 ((void *)0)

 ), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);

}







void test_InitialisePressureSensorsWithWriteToExtSensorFailAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  SensorWriteForceFail = PS_EXTERNAL_E;

  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = ((uint8_t)~0x80);



  result = PM_InitSensors();



  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(146)));};

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureDeviceWriteCount)), (

 ((void *)0)

 ), (_U_UINT)(147), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((ExtPressureDeviceReadCount)), (

 ((void *)0)

 ), (_U_UINT)(148), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IntPressureDeviceReadCount)), (

 ((void *)0)

 ), (_U_UINT)(149), UNITY_DISPLAY_STYLE_INT);

}





void test_InitialisePressureSensorsWithWriteToIntSensorFailAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  SensorWriteForceFail = PS_INTERNAL_E;

  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = ((uint8_t)~0x80);



  result = PM_InitSensors();



  if ((EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(163)));};

  if ((1 == IntPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(164)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(165)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(166)));};

}







void test_InitialisePressureSensorsWithWriteToIntAndExtSensorsFailAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  SensorWriteForceFail = PS_BOTH_E;

  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = ((uint8_t)~0x80);



  result = PM_InitSensors();





  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(182)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(183)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(184)));};

}







void test_InitialisePressureSensorsWithReadFromExtSensorFailAndRetryTimeoutAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = ((uint8_t)~0x80);

  SensorReadForceFail = PS_EXTERNAL_E;



  result = PM_InitSensors();



  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(199)));};

  if ((20 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(200)));};

  if ((20 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(201)));};

}





void test_InitialisePressureSensorsWithReadFromIntSensorFailAndRetryTimeoutAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = ((uint8_t)~0x80);

  SensorReadForceFail = PS_INTERNAL_E;



  result = PM_InitSensors();



  if ((EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(215)));};

  if ((20 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(216)));};

  if ((20 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(217)));};

}





void test_InitialisePressureSensorsWithReadFromBothSensorsFailAndRetryTimeoutAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = ((uint8_t)~0x80);

  SensorReadForceFail = PS_BOTH_E;



  result = PM_InitSensors();



  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(231)));};

  if ((20 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(232)));};

  if ((20 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(233)));};

}





void test_InitialisePressureSensorsWithReadNoBootStatusFromExternalSensorsAndRetryTimeoutAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  PM_Delay_CMockIgnore();

  ReadDataBufferTest[0] = 0x80;



  result = PM_InitSensors();



  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(246)));};

  if ((20 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(247)));};

  if ((20 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(248)));};

}





void test_StartSensorsAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;



  result = PM_StartSensors();



  if ((EC_OK_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(258)));};

  if ((1 == IntPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(259)));};

  if ((1 == ExtPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(260)));};

  if (((0x80 | 0x20) == WriteDataBufferTest[0])) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(261)));};

  if ((0x84 == WriteDataBufferTest[1])) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(262)));};

  if ((0x01 == WriteDataBufferTest[2])) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(263)));};

}





void test_StartSensorsWithWriteToExtSensorFailAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  SensorWriteForceFail = PS_EXTERNAL_E;



  result = PM_StartSensors();



  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(274)));};

  if ((1 == ExtPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(275)));};

  if ((0 == IntPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(276)));};

}





void test_StartSensorsWithWriteToIntSensorFailAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  SensorWriteForceFail = PS_INTERNAL_E;



  result = PM_StartSensors();



  if ((EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(287)));};

  if ((1 == ExtPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(288)));};

  if ((1 == IntPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(289)));};

}





void test_StartSensorsWithWriteToBotSensorFailAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  SensorWriteForceFail = PS_BOTH_E;



  result = PM_StartSensors();



  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(300)));};

  if ((1 == ExtPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(301)));};

  if ((0 == IntPressureDeviceWriteCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(302)));};

}









void test_GetPressureFromSensorsAndCheck(void)

{

  ErrorCode_t result = EC_FAILED_E;





  ReadDataBufferTest[1] = (uint8_t) (((((uint16_t) 0x044C) << 4) & 0x00F0) | 0x000A);

  ReadDataBufferTest[2] = (uint8_t) ((((uint16_t) 0x044C) >> 4) & 0x00FF);

  ReadDataBufferTest[3] = (uint8_t) 0x55;

  ReadDataBufferTest[4] = (uint8_t) 0xAA;

  uint16_t pressure = 0;

  uint16_t temperature = 0;



  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, &pressure, &temperature);



  if ((EC_OK_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(322)));};

  if ((((uint16_t) 0x044C) == pressure)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(323)));};

  if ((0xAA55 == temperature)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(324)));};

  if ((1 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(325)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(326)));};





  result = EC_FAILED_E;

  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;

  ReadDataBufferTest[1] = (uint8_t) (((((uint16_t) 0x0226) << 4) & 0x00F0) | 0x000A);

  ReadDataBufferTest[2] = (uint8_t) ((((uint16_t) 0x0226) >> 4) & 0x00FF);

  ReadDataBufferTest[3] = (uint8_t) 0x00;

  ReadDataBufferTest[4] = (uint8_t) 0x80;

  pressure = 0;

  temperature = 0;



  result = PM_GetPressure(PS_INTERNAL_PRESSURE_E, &pressure, &temperature);



  if ((EC_OK_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(341)));};

  if ((((uint16_t) 0x0226) == pressure)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(342)));};

  if ((0x8000 == temperature)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(343)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(344)));};

  if ((1 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(345)));};

}







void test_GetPressureFromSensorsFailsAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;





  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, 

                                                 ((void *)0)

                                                     , 

                                                       ((void *)0)

                                                           );



  if ((EC_INVALID_INPUT_PARAMETER_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(357)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(358)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(359)));};





  uint16_t pres = 0;

  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, &pres, 

                                                        ((void *)0)

                                                            );



  if ((EC_INVALID_INPUT_PARAMETER_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(365)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(366)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(367)));}







  result = EC_OK_E;

  uint16_t pressure = 0;

  uint16_t temperature = 0;



  result = PM_GetPressure(PS_MAX_NUM_PRESSURE_SENSORS_E, &pressure, &temperature);



  if ((EC_INVALID_INPUT_PARAMETER_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(377)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(378)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(379)));};





  result = EC_OK_E;

  pressure = 0;

  SensorReadForceFail = PS_EXTERNAL_E;



  result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, &pressure, &temperature);



  if ((EC_EXT_PRESSURE_SENSOR_READ_FAILED_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(388)));};

  if ((1 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(389)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(390)));};

}







void test_CalculatePressureDifferenceAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  uint16_t pressureExt = 0;

  uint16_t pressureInt = 0;

  uint16_t pressureDiff = 0;





  result = EC_PRESSURE_DIFF_FAULT_CODE_E;

  pressureExt = 300;

  pressureInt = 200;

  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);



  if ((EC_OK_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(420)));};

  UnityAssertEqualNumber((_U_SINT)(((pressureExt - pressureInt))), (_U_SINT)((pressureDiff)), (

 ((void *)0)

 ), (_U_UINT)(421), UNITY_DISPLAY_STYLE_INT);





  result = EC_OK_E;

  pressureExt = 200;

  pressureInt = 200;

  pressureDiff = 0;

  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);



  if ((EC_OK_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(430)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((pressureDiff)), (

 ((void *)0)

 ), (_U_UINT)(431), UNITY_DISPLAY_STYLE_INT);







  result = EC_OK_E;

  pressureExt = 200;

  pressureInt = 250;

  pressureDiff = 10;

  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);



  if ((EC_OK_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(441)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((pressureDiff)), (

 ((void *)0)

 ), (_U_UINT)(442), UNITY_DISPLAY_STYLE_INT);





  result = EC_OK_E;

  pressureExt = 0;

  pressureInt = 200;

  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);



  if ((EC_PRESSURE_DIFF_FAULT_CODE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(450)));};

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((pressureDiff)), (

 ((void *)0)

 ), (_U_UINT)(451), UNITY_DISPLAY_STYLE_INT);





  result = EC_OK_E;

  pressureExt = 150;

  pressureInt = 0;

  pressureDiff = 0;

  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);



  if ((EC_PRESSURE_DIFF_FAULT_CODE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(460)));};

  if ((0 == pressureDiff)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(461)));};





  result = EC_OK_E;

  pressureExt = 0;

  pressureInt = 0;

  pressureDiff = 0;

  result = PM_CalcDiffPressure(pressureExt, pressureInt, &pressureDiff);



  if ((EC_PRESSURE_DIFF_FAULT_CODE_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(470)));};

  if ((0 == pressureDiff)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(471)));};





  result = EC_OK_E;

  pressureExt = 500;

  pressureInt = 300;

  result = PM_CalcDiffPressure(pressureExt, pressureInt, 

                                                        ((void *)0)

                                                            );



  if ((EC_INVALID_INPUT_PARAMETER_E == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(479)));};

}





void test_IfPressureSensorIsReadyAndCheck(void)

{

  bool_t result = (bool_t) 

                 1

                     ;





  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;



  result = isPressureSensorReady(PS_MAX_NUM_PRESSURE_SENSORS_E);



  if (((bool_t) 

 0 

 == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(493)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(494)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(495)));};





  result = (bool_t) 

          1

              ;

  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;

  SensorReadForceFail = PS_INTERNAL_E;



  result = isPressureSensorReady(PS_INTERNAL_PRESSURE_E);



  if (((bool_t) 

 0 

 == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(505)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(506)));};

  if ((1 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(507)));};





  result = (bool_t) 

          1

              ;

  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;

  SensorReadForceFail = PS_EXTERNAL_E;



  result = isPressureSensorReady(PS_EXTERNAL_PRESSURE_E);



  if (((bool_t) 

 0 

 == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(517)));};

  if ((1 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(518)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(519)));};





  result = (bool_t) 

          1

              ;

  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;

  SensorReadForceFail = PS_NONE_E;

  ReadDataBufferTest[7] = 0x00;



  result = isPressureSensorReady(PS_EXTERNAL_PRESSURE_E);



  if (((bool_t) 

 0 

 == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(530)));};

  if ((1 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(531)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(532)));};





  result = (bool_t) 

          1

              ;

  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;

  SensorReadForceFail = PS_NONE_E;

  ReadDataBufferTest[7] = 0x02;



  result = isPressureSensorReady(PS_EXTERNAL_PRESSURE_E);



  if (((bool_t) 

 1 

 == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(543)));};

  if ((1 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(544)));};

  if ((0 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(545)));};





  result = (bool_t) 

          1

              ;

  ExtPressureDeviceReadCount = 0;

  IntPressureDeviceReadCount = 0;

  SensorReadForceFail = PS_NONE_E;

  ReadDataBufferTest[7] = 0x02;



  result = isPressureSensorReady(PS_INTERNAL_PRESSURE_E);



  if (((bool_t) 

 1 

 == result)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(556)));};

  if ((0 == ExtPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(557)));};

  if ((1 == IntPressureDeviceReadCount)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(558)));};

}
