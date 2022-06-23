#include "DeviceStatus.h"
#include "MockDutyCycle.h"
#include "MockTimer.h"
#include "MockPowerControl.h"
#include "MockPressure_Part4.h"
#include "MockPressure_Part3.h"
#include "MockPressure_Part2.h"
#include "Pressure_Part1.h"
#include "unity.h"




static uint32_t GetVacuumFailRetries = 0;



static uint32_t SingleVacuumRetries = 0;

static uint16_t InternalMeasuredVacuum = 0;

static uint16_t ExternalMeasuredVacuum = 0;

static uint16_t MeasuredVacuum = 0;

static uint8_t ExpectedPressureType = 0;







static ErrorCode_t Stub_TryToGetSingleVacuumMeasurementEXT(uint16_t* pInternal, uint16_t* pExternal, uint16_t* pDiff, int NumCall)

{

  ErrorCode_t result = EC_EXT_PRESSURE_SENSOR_NOT_READY_E;



  SingleVacuumRetries++;



  if (SingleVacuumRetries > GetVacuumFailRetries)

  {

    *pDiff = MeasuredVacuum;

    result = EC_OK_E;

  }



  return result;

}



static ErrorCode_t Stub_TryToGetSingleVacuumMeasurementINT(uint16_t* pInternal, uint16_t* pExternal, uint16_t* pDiff, int NumCall)

{

  ErrorCode_t result = EC_INT_PRESSURE_SENSOR_NOT_READY_E;



  SingleVacuumRetries++;



  if (SingleVacuumRetries > GetVacuumFailRetries)

  {

    *pDiff = MeasuredVacuum;

    result = EC_OK_E;

  }



  return result;

}





void setUp(void)

{

  GetVacuumFailRetries = 0;

  MeasuredVacuum = 0;

  SingleVacuumRetries = 0;

}



void tearDown(void)

{}







void test_SetInitiaExternalPressureAndCheck(void)

{

  uint32_t pressure = 0;

  SetInitialExternalPressure(pressure);

  UnityAssertEqualNumber((_U_SINT)((GetInitialExternalPressure())), (_U_SINT)((pressure)), (

 ((void *)0)

 ), (_U_UINT)(87), UNITY_DISPLAY_STYLE_INT);

  if (((GetInitialExternalPressure()) != ((pressure+1)))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(88)));};



  pressure = 200;

  SetInitialExternalPressure(pressure);

  GetInitialExternalPressure();

  UnityAssertEqualNumber((_U_SINT)((GetInitialExternalPressure())), (_U_SINT)((pressure)), (

 ((void *)0)

 ), (_U_UINT)(93), UNITY_DISPLAY_STYLE_INT);

  if (((GetInitialExternalPressure()) != ((pressure+1)))) {} else {UnityFail( ((" Expected Not-Equal")), (_U_UINT)((_U_UINT)(94)));};

}







void test_InitialisePressureForPumpdownAndCheck(void)

{

  InitPumpDownVacuum();



  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((GetInitialExternalPressure())), (

 ((void *)0)

 ), (_U_UINT)(103), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((GetTargetPumpDownVaccumDebounceCount())), (

 ((void *)0)

 ), (_U_UINT)(104), UNITY_DISPLAY_STYLE_INT);

}







void test_TargetPumpDownVacuumAchievedOrNotAndCheck(void)

{

  bool_t result = (bool_t) 

                 0

                      ;

  uint16_t vacuum = (96) + 1;

  uint32_t fail_count = 0;

  uint32_t pass_count = 0;

  uint32_t loop = 0;





  InitPumpDownVacuum();

  for (loop = 0; loop < ((1)); loop++)

  {

    if(

      0 

            == isTargetPumpDownVacuumAchieved(vacuum))

    {

      fail_count++;

    }

    else

    {

      pass_count++;

    }

  }



  UnityAssertEqualNumber((_U_SINT)(((1))), (_U_SINT)((GetTargetPumpDownVaccumDebounceCount())), (

 ((void *)0)

 ), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((pass_count)), (

 ((void *)0)

 ), (_U_UINT)(132), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((1)-1))), (_U_SINT)((fail_count)), (

 ((void *)0)

 ), (_U_UINT)(133), UNITY_DISPLAY_STYLE_INT);







  vacuum = (96) + 1;

  fail_count = 0;

  pass_count = 0;

  InitPumpDownVacuum();

  for (loop = 0; loop < ((1)-1); loop++)

  {

    if(

      0 

            == isTargetPumpDownVacuumAchieved(vacuum))

    {

      fail_count++;

    }

    else

    {

      pass_count++;

    }

  }



  if (((bool_t) 

 0 

 == isTargetPumpDownVacuumAchieved(vacuum-1))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(153)));}

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((GetTargetPumpDownVaccumDebounceCount())), (

 ((void *)0)

 ), (_U_UINT)(154), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((pass_count)), (

 ((void *)0)

 ), (_U_UINT)(155), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((1)-1))), (_U_SINT)((fail_count)), (

 ((void *)0)

 ), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);





  vacuum = (96) - 1;

  fail_count = 0;

  pass_count = 0;

  InitPumpDownVacuum();

  for (loop = 0; loop < ((1)+1); loop++)

  {

    if(

      0 

            == isTargetPumpDownVacuumAchieved(vacuum))

    {

      fail_count++;

    }

    else

    {

      pass_count++;

    }

  }

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((GetTargetPumpDownVaccumDebounceCount())), (

 ((void *)0)

 ), (_U_UINT)(174), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((pass_count)), (

 ((void *)0)

 ), (_U_UINT)(175), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((1)+1))), (_U_SINT)((fail_count)), (

 ((void *)0)

 ), (_U_UINT)(176), UNITY_DISPLAY_STYLE_INT);





  fail_count = 0;

  pass_count = 0;

  InitPumpDownVacuum();

  vacuum = (96) + 1;

  for (loop = 0; loop < (

                        (0x7f * 2 + 1) 

                                  + (1)); loop++)

  {

    if(

      0 

            == isTargetPumpDownVacuumAchieved(vacuum))

    {

      fail_count++;

    }

    else

    {

      pass_count++;

    }

  }

  UnityAssertEqualNumber((_U_SINT)((

 (0x7f * 2 + 1)

 )), (_U_SINT)((GetTargetPumpDownVaccumDebounceCount())), (

 ((void *)0)

 ), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((

 (0x7f * 2 + 1)

 +1)), (_U_SINT)((pass_count)), (

 ((void *)0)

 ), (_U_UINT)(195), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((((1)-1))), (_U_SINT)((fail_count)), (

 ((void *)0)

 ), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);

}









void test_GetVacuumFailForInvalidInputParameterOrSensorsNotInitialisedAndCheck(void)

{

    uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  uint16_t vacuum = 0;

  ErrorCode_t result = EC_OK_E;





  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  if ((EC_INVALID_INPUT_PARAMETER_E == GetVacuum(

 ((void *)0)

 , 0, 0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(211)));};





  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_Delay_CMockIgnore();

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  PM_InitSensors_CMockIgnoreAndReturn(217, EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);

  if ((EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(218)));};





  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_Delay_CMockIgnore();

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  PM_InitSensors_CMockIgnoreAndReturn(224, EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E);

  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(225)));};





  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_InitSensors_CMockIgnoreAndReturn(229, EC_OK_E);

  PM_StartSensors_CMockIgnoreAndReturn(230, EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E);

  MP_DisableExternalPeripheralsSupply_CMockIgnore();



  if ((EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(233)));};





  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_InitSensors_CMockIgnoreAndReturn(237, EC_OK_E);

  PM_StartSensors_CMockIgnoreAndReturn(238, EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E);

  MP_DisableExternalPeripheralsSupply_CMockIgnore();



  if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(241)));};

}







void test_GetVacuumPassFirstTryAndCheck(void)

{

  TryToGetSingleVacuumMeasurement_StubWithCallback(Stub_TryToGetSingleVacuumMeasurementEXT);

  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_InitSensors_CMockIgnoreAndReturn(250, EC_OK_E);

  PM_StartSensors_CMockIgnoreAndReturn(251, EC_OK_E);

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  PM_Delay_CMockIgnore();





  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  GetVacuumFailRetries = 0;

  MeasuredVacuum = 100;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(263)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(264), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(265), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40)/2;

  MeasuredVacuum = 50;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(273)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(275), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40)-1;

  MeasuredVacuum = 150;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(283)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(284), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(285), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40);

  MeasuredVacuum = 75;

  SingleVacuumRetries = 0;



  if ((EC_OK_E != GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(293)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(294), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(295), UNITY_DISPLAY_STYLE_INT);

}





void test_GetVacuumProvidesInternalPressureWhenAsked(void)

{

  TryToGetSingleVacuumMeasurement_StubWithCallback(Stub_TryToGetSingleVacuumMeasurementINT);

  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_InitSensors_CMockIgnoreAndReturn(303, EC_OK_E);

  PM_StartSensors_CMockIgnoreAndReturn(304, EC_OK_E);

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  PM_Delay_CMockIgnore();

  ExpectedPressureType = 1;





  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  GetVacuumFailRetries = 0;

  MeasuredVacuum = 100;

  SingleVacuumRetries = 0;











  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(321)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(322), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(323), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40)/2;

  MeasuredVacuum = 50;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(331)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(332), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(333), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40)-1;

  MeasuredVacuum = 150;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(341)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(342), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(343), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40);

  MeasuredVacuum = 75;

  SingleVacuumRetries = 0;



  if ((EC_OK_E != GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(351)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(352), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(353), UNITY_DISPLAY_STYLE_INT);

}





void test_GetVacuumProvidesExternalPressureWhenAsked(void)

{

  TryToGetSingleVacuumMeasurement_StubWithCallback(Stub_TryToGetSingleVacuumMeasurementEXT);

  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  PM_InitSensors_CMockIgnoreAndReturn(361, EC_OK_E);

  PM_StartSensors_CMockIgnoreAndReturn(362, EC_OK_E);

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  PM_Delay_CMockIgnore();

  ExpectedPressureType = 2;





  uint16_t vacuum = 0;

  uint16_t internal_pressure = 0;

  uint16_t external_pressure = 0;

  GetVacuumFailRetries = 0;

  MeasuredVacuum = 100;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(375)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(376), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(377), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40)/2;

  MeasuredVacuum = 50;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(385)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(386), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(387), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40)-1;

  MeasuredVacuum = 150;

  SingleVacuumRetries = 0;



  if ((EC_OK_E == GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(395)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries + 1)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(396), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((MeasuredVacuum)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(397), UNITY_DISPLAY_STYLE_INT);





  vacuum = 0;

  GetVacuumFailRetries = (40);

  MeasuredVacuum = 75;

  SingleVacuumRetries = 0;



  if ((EC_OK_E !=GetVacuum(&internal_pressure, &external_pressure, &vacuum))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(405)));};

  UnityAssertEqualNumber((_U_SINT)((GetVacuumFailRetries)), (_U_SINT)((SingleVacuumRetries)), (

 ((void *)0)

 ), (_U_UINT)(406), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((vacuum)), (

 ((void *)0)

 ), (_U_UINT)(407), UNITY_DISPLAY_STYLE_INT);

}



void test_CheckTheLeakDetectionIsActiveWhenTheReferenceBoostVoltageIs27V(void)

{



  MP_GetInitBoostDemand_CMockExpectAndReturn(413, (((uint8_t)18)));

  DCLeakGet_CMockExpectAndReturn(414, (15)-1);



  if (!(isTherapyDeliveryLeakDetected())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(416)));};





  MP_GetInitBoostDemand_CMockExpectAndReturn(419, (((uint8_t)18)));

  DCLeakGet_CMockExpectAndReturn(420, (15));



  if (!(isTherapyDeliveryLeakDetected())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(422)));};





  MP_GetInitBoostDemand_CMockExpectAndReturn(425, (((uint8_t)18)));

  DCLeakGet_CMockExpectAndReturn(426, (15)+1);



  if ((isTherapyDeliveryLeakDetected())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(428)));};





  MP_GetInitBoostDemand_CMockExpectAndReturn(431, (((uint8_t)18))-1);



  if (!(isTherapyDeliveryLeakDetected())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(433)));};







  MP_GetInitBoostDemand_CMockExpectAndReturn(437, (((uint8_t)18))-1);

  DCLeakGet_CMockIgnoreAndReturn(438, (15)-1);



  if (!(isTherapyDeliveryLeakDetected())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(440)));};







  MP_GetInitBoostDemand_CMockExpectAndReturn(444, (((uint8_t)18))-1);

  DCLeakGet_CMockIgnoreAndReturn(445, (15)+1);



  if (!(isTherapyDeliveryLeakDetected())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(447)));};

}
