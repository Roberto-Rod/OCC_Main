#include "MockStateMachine.h"
#include "MockPerformanceLogger.h"
#include "MockPressure_Part3.h"
#include "Pressure_Part2.h"
#include "unity.h"




typedef enum {

    PS_NONE_E = 0,

    PS_EXTERNAL_E,

    PS_INTERNAL_E,

    PS_BOTH_E

} PressureSensorFail_t;











static uint8_t IsExtSensorReadyCount = 0;

static uint8_t IsIntSensorReadyCount = 0;

static uint8_t ExtPressureGetCount = 0;

static uint8_t IntPressureGetCount = 0;

static PressureSensorFail_t SensorReadyForceFail = PS_NONE_E;

static PressureSensorFail_t PressureGetForceFail = PS_NONE_E;

static uint16_t ExtPressureTest = 0;

static uint16_t IntPressureTest = 0;

static uint16_t VacuumTest = 0;

static uint16_t ExtTemperatureTest = 0;

static uint16_t IntTemperatureTest = 0;

static uint16_t IntTemperatureLogged = 0;

static uint16_t ExtTemperatureLogged = 0;







static bool_t Stub_isPressureSensorReady(PressureSensor_t Sensor, int NumCall)

{

  bool_t result = (bool_t) 

                 1

                     ;



  if (PS_EXTERNAL_PRESSURE_E == Sensor)

  {

    IsExtSensorReadyCount++;

    result = ((PS_EXTERNAL_E == SensorReadyForceFail) || (PS_BOTH_E == SensorReadyForceFail)) ? (bool_t) 

                                                                                               0

                                                                                                    :(bool_t) 

                                                                                                     1

                                                                                                         ;

  }

  else if (PS_INTERNAL_PRESSURE_E == Sensor)

  {

    IsIntSensorReadyCount++;

    result = ((PS_INTERNAL_E == SensorReadyForceFail) || (PS_BOTH_E == SensorReadyForceFail)) ? (bool_t) 

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



  return result;

}





static void Stub_PerformanceLogger_SetIntTemperature(uint16_t IntTemperatureValue, int NumCall )

{

   IntTemperatureLogged = IntTemperatureValue;

}





static void Stub_PerformanceLogger_SetExtTemperature(uint16_t ExtTemperatureValue, int NumCall )

{

   ExtTemperatureLogged = ExtTemperatureValue;

}





static ErrorCode_t Stub_PM_GetPressure(PressureSensor_t Sensor, uint16_t* pPressure, uint16_t* pTemperature, int NumCall)

{

  ErrorCode_t result = EC_OK_E;



  if (PS_EXTERNAL_PRESSURE_E == Sensor)

  {

    *pPressure = ExtPressureTest;

    *pTemperature = ExtTemperatureTest;

    ExtPressureGetCount++;

    result = ((PS_EXTERNAL_E == PressureGetForceFail) || (PS_BOTH_E == PressureGetForceFail)) ? EC_EXT_PRESSURE_SENSOR_READ_FAILED_E:EC_OK_E;

  }

  else if (PS_INTERNAL_PRESSURE_E == Sensor)

  {

    *pPressure = IntPressureTest;

    *pTemperature = IntTemperatureTest;

    IntPressureGetCount++;

    result = ((PS_INTERNAL_E == PressureGetForceFail) || (PS_BOTH_E == PressureGetForceFail)) ? EC_INT_PRESSURE_SENSOR_READ_FAILED_E:EC_OK_E;

  }

  else

  {

    result = EC_EXT_PRESSURE_SENSOR_READ_FAILED_E;

  }



  return result;

}











ErrorCode_t Stub_PM_CalcDiffPressure(uint16_t PresExt, uint16_t PresInt, uint16_t* pDiff, int NumCall)

{

  ErrorCode_t result = EC_OK_E;



  if (

     ((void *)0) 

          != pDiff)

  {

    *pDiff = VacuumTest;

  }

  else

  {

    result = EC_INVALID_INPUT_PARAMETER_E;

  }



  return result;

}



void setUp(void)

{

  IsExtSensorReadyCount = 0;

  IsIntSensorReadyCount = 0;

  ExtPressureGetCount = 0;

  IntPressureGetCount = 0;

  SensorReadyForceFail = PS_NONE_E;

  PressureGetForceFail = PS_NONE_E;

  ExtPressureTest = 0;

  IntPressureTest = 0;

  ExtTemperatureTest = 0;

  IntTemperatureTest = 0;

  VacuumTest = 0;



  isPressureSensorReady_StubWithCallback(Stub_isPressureSensorReady);

  PM_GetPressure_StubWithCallback(Stub_PM_GetPressure);

  PerformanceLogger_SetExternalPressure_CMockIgnore();

  PerformanceLogger_SetDifferentialPressure_CMockIgnore();

  PerformanceLogger_SetInternalTemperature_StubWithCallback(Stub_PerformanceLogger_SetIntTemperature);

  PerformanceLogger_SetExternalTemperature_StubWithCallback(Stub_PerformanceLogger_SetExtTemperature);

}



void tearDown(void)

{}





void test_TryToGetSingleDifferentialVacuumMeasurementOkAndCheck(void)

{

  ErrorCode_t result = EC_FAILED_E;

  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  ExtPressureTest = 700;

  IntPressureTest = 650;

  ExtTemperatureTest = ((int16_t)0xFB50) - 0x0010;

  IntTemperatureTest = ((int16_t)0xFE20) - 0x0010;

  VacuumTest = ExtPressureTest - IntPressureTest;



  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);





  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);





  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(178), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((VacuumTest)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(180), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(181), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(182), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);





  UnityAssertEqualNumber((_U_SINT)((ExtTemperatureLogged)), (_U_SINT)((ExtTemperatureTest)), (

 ((void *)0)

 ), (_U_UINT)(186), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IntTemperatureLogged)), (_U_SINT)((IntTemperatureTest)), (

 ((void *)0)

 ), (_U_UINT)(187), UNITY_DISPLAY_STYLE_INT);

}





void test_TryToGetSingleVacuumInternalMeasurementOkAndCheck(void)

{

  ErrorCode_t result = EC_FAILED_E;

  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  ExtPressureTest = 700;

  IntPressureTest = 650;

  ExtTemperatureTest = ((int16_t)0xFB50) - 0x0010;

  IntTemperatureTest = ((int16_t)0xFE20) - 0x0010;

  VacuumTest = ExtPressureTest - IntPressureTest;



  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(207), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((VacuumTest)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(208), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IntPressureTest)), (_U_SINT)((internal_pressure)), (

 ((void *)0)

 ), (_U_UINT)(209), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((ExtPressureTest)), (_U_SINT)((external_pressure)), (

 ((void *)0)

 ), (_U_UINT)(210), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(211), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(212), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(213), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(214), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((ExtTemperatureLogged)), (_U_SINT)((ExtTemperatureTest)), (

 ((void *)0)

 ), (_U_UINT)(216), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IntTemperatureLogged)), (_U_SINT)((IntTemperatureTest)), (

 ((void *)0)

 ), (_U_UINT)(217), UNITY_DISPLAY_STYLE_INT);

}







void test_TryToGetSingleVacuumExternalMeasurementOkAndCheck(void)

{

  ErrorCode_t result = EC_FAILED_E;

  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  ExtPressureTest = 70;

  IntPressureTest = 69;

  ExtTemperatureTest = ((int16_t)0xFB50) - 0x0010;

  IntTemperatureTest = ((int16_t)0xFE20) - 0x0010;

  VacuumTest = ExtPressureTest - IntPressureTest;



  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(238), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IntPressureTest)), (_U_SINT)((internal_pressure)), (

 ((void *)0)

 ), (_U_UINT)(239), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((ExtPressureTest)), (_U_SINT)((external_pressure)), (

 ((void *)0)

 ), (_U_UINT)(240), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((VacuumTest)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(241), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(242), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(243), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(244), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(245), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((ExtTemperatureLogged)), (_U_SINT)((ExtTemperatureTest)), (

 ((void *)0)

 ), (_U_UINT)(247), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IntTemperatureLogged)), (_U_SINT)((IntTemperatureTest)), (

 ((void *)0)

 ), (_U_UINT)(248), UNITY_DISPLAY_STYLE_INT);

}





void test_TryToGetSingleVacuumMeasurementInvalidInputParameterAndCheck(void)

{

  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  ErrorCode_t result = EC_OK_E;





  result = TryToGetSingleVacuumMeasurement(

                                          ((void *)0)

                                              , &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(262), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(264), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(265), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(266), UNITY_DISPLAY_STYLE_INT);





  result = TryToGetSingleVacuumMeasurement(&internal_pressure, 

                                                              ((void *)0)

                                                                  , &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(271), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(272), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(273), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(275), UNITY_DISPLAY_STYLE_INT);



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, 

                                                                                  ((void *)0)

                                                                                      );



  UnityAssertEqualNumber((_U_SINT)((EC_INVALID_INPUT_PARAMETER_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(279), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(280), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(281), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(282), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(283), UNITY_DISPLAY_STYLE_INT);



}







void test_TryToGetSingleVacuumMeasurementExternalSensorNotReadyAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  SensorReadyForceFail = PS_EXTERNAL_E;

  uint16_t vacuum = 10;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_NOT_READY_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(299), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(300), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(301), UNITY_DISPLAY_STYLE_INT);



}





void test_TryToGetSingleVacuumMeasurementInternalSensorNotReadyAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  SensorReadyForceFail = PS_INTERNAL_E;

  uint16_t vacuum = 10;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_NOT_READY_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(316), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(317), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(318), UNITY_DISPLAY_STYLE_INT);



}







void test_TryToGetSingleVacuumMeasurementBothSensorsNotReadyAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  SensorReadyForceFail = PS_BOTH_E;

  uint16_t vacuum = 10;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_NOT_READY_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(334), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(335), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(336), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(337), UNITY_DISPLAY_STYLE_INT);

}







void test_TryToGetSingleVacuumMeasurementFailGettingExtPressureAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  PressureGetForceFail = PS_EXTERNAL_E;

  uint16_t vacuum = 10;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_EXT_PRESSURE_SENSOR_READ_FAILED_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(352), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(353), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(355), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(356), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(357), UNITY_DISPLAY_STYLE_INT);

}





void test_TryToGetSingleVacuumMeasurementFailGettingIntPressureAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  PressureGetForceFail = PS_INTERNAL_E;

  uint16_t vacuum = 10;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_INT_PRESSURE_SENSOR_READ_FAILED_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(371), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(372), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(373), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(374), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(375), UNITY_DISPLAY_STYLE_INT);

}





void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureDiffAndCheck(void)

{

  ErrorCode_t result = EC_OK_E;

  uint16_t vacuum = 10;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  ExtTemperatureTest = ((int16_t)0xFB50) - 0x0010;

  IntTemperatureTest = ((int16_t)0xFE20) - 0x0010;



  PM_CalcDiffPressure_CMockIgnoreAndReturn(388, EC_PRESSURE_DIFF_FAULT_CODE_E);



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_PRESSURE_DIFF_FAULT_CODE_E)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(392), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsExtSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(393), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IsIntSensorReadyCount)), (

 ((void *)0)

 ), (_U_UINT)(394), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((ExtPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(395), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((IntPressureGetCount)), (

 ((void *)0)

 ), (_U_UINT)(396), UNITY_DISPLAY_STYLE_INT);

}





void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureExternalTemperatureThreshholdReached (void)

{

  ErrorCode_t result = EC_OK_E;

  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  ExtPressureTest = 700;

  IntPressureTest = 650;

  ExtTemperatureTest = ((int16_t)0xFB50) + 0x0010;

  IntTemperatureTest = ((int16_t)0xFE20) - 0x0010;

  VacuumTest = ExtPressureTest - IntPressureTest;



  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_EXT_TEMPERATURE_HIGH)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(416), UNITY_DISPLAY_STYLE_INT);



}



 void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureInternalTemperatureThreshholdReached (void)

{

  ErrorCode_t result = EC_OK_E;

  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  ExtPressureTest = 700;

  IntPressureTest = 650;

  ExtTemperatureTest = ((int16_t)0xFB50) - 0x0010;

  IntTemperatureTest = ((int16_t)0xFE20) + 0x0010;

  VacuumTest = ExtPressureTest - IntPressureTest;



  PM_CalcDiffPressure_StubWithCallback(Stub_PM_CalcDiffPressure);



  result = TryToGetSingleVacuumMeasurement(&internal_pressure, &external_pressure, &vacuum);



  UnityAssertEqualNumber((_U_SINT)((EC_INT_TEMPERATURE_HIGH)), (_U_SINT)((result)), (

 ((void *)0)

 ), (_U_UINT)(436), UNITY_DISPLAY_STYLE_INT);

}
