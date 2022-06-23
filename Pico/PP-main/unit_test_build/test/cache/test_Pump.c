#include "MockDeviceStatus.h"
#include "MockPumpFrequencyTracker.h"
#include "MockBattery.h"
#include "MockTimer.h"
#include "MockPowerControl.h"
#include "Pump.h"
#include "unity.h"




static bool_t ExternalPeripheralsSupplyEnabled = (bool_t) 

                                                0

                                                     ;

static uint32_t ExternalPeripheralsSupplyEnableCount = 0;

static uint32_t ExternalPeripheralsSupplyDisableCount = 0;

static bool_t MainCircuitPowerEnabled = (bool_t) 

                                       0

                                            ;

static bool_t PumpPwmEnabled = (bool_t) 

                              0

                                   ;

static uint8_t BoostDemand = 0;

static bool_t PoweTrackerCalled = (bool_t) 

                                 0

                                      ;

static bool_t VoltageBoundsCalled = (bool_t) 

                                   0

                                        ;

static ErrorCode_t VoltageBoundsOK = EC_OK_E;





static void Stub_MP_EnableExternalPeripheralsSupply(int NumCall)

{

  ExternalPeripheralsSupplyEnabled = (bool_t) 

                                    1

                                        ;

  ExternalPeripheralsSupplyEnableCount++;

}

static void Stub_MP_DisableExternalPeripheralsSupply(int NumCall)

{

  ExternalPeripheralsSupplyEnabled = (bool_t) 

                                    0

                                         ;

  ExternalPeripheralsSupplyDisableCount++;

}

static void Stub_MP_EnableMainCircuitPower(int NumCall)

{

  MainCircuitPowerEnabled = (bool_t) 

                           1

                               ;

}

static void Stub_MP_DisableMainCircuitPower(int NumCall)

{

  MainCircuitPowerEnabled = (bool_t) 

                           0

                                ;

}

static bool_t Stub_isMainCircuitPowerEnabled(int NumCall)

{

  return MainCircuitPowerEnabled;

}

static void Stub_MP_EnablePumpPWM(int NumCall)

{

 PumpPwmEnabled = (bool_t) 

                 1

                     ;

}

static void Stub_MP_DisablePumpPWM(int NumCall)

{

 PumpPwmEnabled = (bool_t) 

                 0

                      ;

}

static bool_t Stub_isPumpPwmEnabled(int NumCall)

{

  return PumpPwmEnabled;

}

static void Stub_MP_SetReferenceVoltageBoost(uint8_t Demand, int NumCall)

{

  BoostDemand = Demand;

}

static ErrorCode_t Stub_PumpFrequencyTracker_Optimise(int NumCall)

{

  PoweTrackerCalled = (bool_t) 

                     1

                         ;



  return EC_OK_E;

}



static ErrorCode_t Stub_Battery_CheckVoltageBounds(int NumCall)

{

  VoltageBoundsCalled = (bool_t) 

                       1

                           ;



  return VoltageBoundsOK;

}



void setUp(void)

{

  ExternalPeripheralsSupplyEnabled = (bool_t) 

                                    0

                                         ;

  ExternalPeripheralsSupplyEnableCount = 0;

  ExternalPeripheralsSupplyDisableCount = 0;

  MainCircuitPowerEnabled = (bool_t) 

                           0

                                ;

  PumpPwmEnabled = (bool_t) 

                  0

                       ;

  BoostDemand = 0;

  PoweTrackerCalled = (bool_t) 

                     0

                          ;



  MP_EnableExternalPeripheralsSupply_StubWithCallback(Stub_MP_EnableExternalPeripheralsSupply);

  MP_DisableExternalPeripheralsSupply_StubWithCallback(Stub_MP_DisableExternalPeripheralsSupply);

  MP_EnableMainCircuitPower_StubWithCallback(Stub_MP_EnableMainCircuitPower);

  MP_DisableMainCircuitPower_StubWithCallback(Stub_MP_DisableMainCircuitPower);

  isMainCircuitPowerEnabled_StubWithCallback(Stub_isMainCircuitPowerEnabled);

  MP_EnablePumpPWM_StubWithCallback(Stub_MP_EnablePumpPWM);

  MP_DisablePumpPWM_StubWithCallback(Stub_MP_DisablePumpPWM);

  isPumpPwmEnabled_StubWithCallback(Stub_isPumpPwmEnabled);

  MP_SetReferenceVoltageBoost_StubWithCallback(Stub_MP_SetReferenceVoltageBoost);

  PumpFrequencyTracker_Optimise_StubWithCallback(Stub_PumpFrequencyTracker_Optimise);

  Battery_CheckVoltageBounds_StubWithCallback(Stub_Battery_CheckVoltageBounds);

}



void tearDown(void)

{}









void test_ActivateAndDeactivatePumpReturnOk(void)

{

  DeviceStatus_SetPumpIsRunning_CMockIgnore();





  MP_GetBoostDemand_CMockIgnoreAndReturn(124, (((uint8_t)18)));

  PM_Delay_CMockIgnore();

  ErrorCode_t errorCode = PumpActivate((bool_t) 

                                      1

                                          );

  if (((EC_OK_E == errorCode) && ((bool_t) 

 0 

 == ExternalPeripheralsSupplyEnabled) && (1 == ExternalPeripheralsSupplyEnableCount) && (1 == ExternalPeripheralsSupplyDisableCount) && ((bool_t) 

 1 

 == MainCircuitPowerEnabled) && ((bool_t) 

 1 

 == PumpPwmEnabled) && ((((uint8_t)18))==BoostDemand) && ((bool_t) 

 1 

 == PoweTrackerCalled))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(134)));}













                                               ;





  PoweTrackerCalled = (bool_t) 

                     0

                          ;

  errorCode = PumpActivate((bool_t) 

                          0

                               );

  if (((EC_OK_E == errorCode) && ((bool_t) 

 0 

 == PumpPwmEnabled) && ((0) == BoostDemand) && ((bool_t) 

 0 

 == PoweTrackerCalled))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(142)));}





                                                ;

}





void test_ActivatePumpAndCheckResultOfIsPumpActivatedFunction(void)

{

  DeviceStatus_SetPumpIsRunning_CMockIgnore();

  MP_GetBoostDemand_CMockIgnoreAndReturn(149, (((uint8_t)18)));



  PM_Delay_CMockIgnore();





  PumpActivate((bool_t) 

              1

                  );

  if (((bool_t) 

 1 

 == isPumpActivated())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(155)));};





  PumpActivate((bool_t) 

              0

                   );

  if (!((bool_t) 

 1 

 == isPumpActivated())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(159)));};

}



void test_IsPumpRunningFlagSetOnPumpActivate(void)

{

  MP_GetBoostDemand_CMockIgnoreAndReturn(164, (((uint8_t)18)));

  PM_Delay_CMockIgnore();



  DeviceStatus_SetPumpIsRunning_CMockExpect(167, (bool_t) 

 0

 );

  PumpActivate((bool_t) 

              0

                   );



  DeviceStatus_SetPumpIsRunning_CMockExpect(170, (bool_t) 

 1

 );

  PumpActivate((bool_t) 

              1

                  );

}
