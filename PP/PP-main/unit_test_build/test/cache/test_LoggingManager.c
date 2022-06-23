#include "MockBattery.h"
#include "MockPerformanceLogger.h"
#include "MockStateMachine.h"
#include "StateMachineCommon.h"
#include "DeviceStatus.h"
#include "LoggingManager.h"
#include "unity.h"






void setUp()

{}



void tearDown()

{}



void test_Initialise(void)

{

  PerformanceLogger_Init_CMockExpect(36);

  LoggingManager_Init();



  UnityAssertEqualNumber((_U_SINT)(((10 * 60))), (_U_SINT)((LoggingManager_GetTicks())), (

 ((void *)0)

 ), (_U_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}



void test_LogEveryMinuteWhenNotIdle(void)

{

  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , THERAPY_DELIVERY_E);

  DeviceStatus_SetPressureSensorIsReading((bool_t) 

                                         0

                                              );

  DeviceStatus_SetPumpIsRunning((bool_t) 

                               0

                                    );

  PerformanceLogger_GetCurrentAddress_CMockIgnoreAndReturn(47, 0);





  for (int i = 0; i < (10 * 60) - 1; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OPS_NOT_EXECUTED_E)), (_U_SINT)((LoggingManager_Run())), (

   ((void *)0)

   ), (_U_UINT)(52), UNITY_DISPLAY_STYLE_INT);

  }



  PerformanceLogger_SetStatus_CMockExpect(55, DeviceStatus_GetState());

  PerformanceLogger_Persist_CMockExpectAndReturn(56, EC_OK_E);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((LoggingManager_Run())), (

 ((void *)0)

 ), (_U_UINT)(57), UNITY_DISPLAY_STYLE_INT);





  for (int i = 0; i < (10 * 60) - 1; i++)

  {

    LoggingManager_Run();

  }



  PerformanceLogger_SetStatus_CMockExpect(65, DeviceStatus_GetState());

  PerformanceLogger_Persist_CMockExpectAndReturn(66, EC_OK_E);

  LoggingManager_Run();

}



void test_NoLoggingIfPumpIsRunning(void)

{

  PerformanceLogger_Init_CMockIgnore();

  LoggingManager_Init();



  DeviceStatus_SetPressureSensorIsReading((bool_t) 

                                         0

                                              );

  DeviceStatus_SetPumpIsRunning((bool_t) 

                               1

                                   );

  PerformanceLogger_GetCurrentAddress_CMockIgnoreAndReturn(77, 0);



  for (int i = 0; i < (10 * 60) -1; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OPS_NOT_EXECUTED_E)), (_U_SINT)((LoggingManager_Run())), (

   ((void *)0)

   ), (_U_UINT)(81), UNITY_DISPLAY_STYLE_INT);

  }

  UnityAssertEqualNumber((_U_SINT)((EC_LOGGING_POSTPONE_E)), (_U_SINT)((LoggingManager_Run())), (

 ((void *)0)

 ), (_U_UINT)(83), UNITY_DISPLAY_STYLE_INT);

}



void test_NoLoggingIfPressureSensorReadingIsPerformed(void)

{

  PerformanceLogger_Init_CMockIgnore();

  LoggingManager_Init();



  DeviceStatus_SetPressureSensorIsReading((bool_t) 

                                         1

                                             );

  DeviceStatus_SetPumpIsRunning((bool_t) 

                               0

                                    );

  PerformanceLogger_GetCurrentAddress_CMockIgnoreAndReturn(93, 0);



  for (int i = 0; i < (10 * 60) -1; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OPS_NOT_EXECUTED_E)), (_U_SINT)((LoggingManager_Run())), (

   ((void *)0)

   ), (_U_UINT)(97), UNITY_DISPLAY_STYLE_INT);

  }

  UnityAssertEqualNumber((_U_SINT)((EC_LOGGING_POSTPONE_E)), (_U_SINT)((LoggingManager_Run())), (

 ((void *)0)

 ), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

}



void test_SkipLoggingWhenStateIsIdle(void)

{

  PerformanceLogger_Init_CMockIgnore();

  LoggingManager_Init();



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , IDLE_E);

  PerformanceLogger_GetCurrentAddress_CMockIgnoreAndReturn(108, 0);



  for (int i = 0; i < (10 * 60) -1; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OPS_NOT_EXECUTED_E)), (_U_SINT)((LoggingManager_Run())), (

   ((void *)0)

   ), (_U_UINT)(112), UNITY_DISPLAY_STYLE_INT);

  }



  PerformanceLogger_SkipToNextTimeline_CMockExpect(115);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((LoggingManager_Run())), (

 ((void *)0)

 ), (_U_UINT)(116), UNITY_DISPLAY_STYLE_INT);



}









void test_LogEveryMinuteButEnterNREWhenEEPROMFull(void)

{

  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , THERAPY_DELIVERY_E);

  DeviceStatus_SetPressureSensorIsReading((bool_t) 

                                         0

                                              );

  DeviceStatus_SetPumpIsRunning((bool_t) 

                               0

                                    );

  PerformanceLogger_GetCurrentAddress_CMockIgnoreAndReturn(128, 60ul * 8 * 24 * 16);





  for (int i = 0; i < (10 * 60) - 1; i++)

  {

    UnityAssertEqualNumber((_U_SINT)((EC_OPS_NOT_EXECUTED_E)), (_U_SINT)((LoggingManager_Run())), (

   ((void *)0)

   ), (_U_UINT)(133), UNITY_DISPLAY_STYLE_INT);

  }



  StateMachine_Enter_NRE_CMockExpect(136, (bool_t) 

 1

 );

  UnityAssertEqualNumber((_U_SINT)((EC_EEPROM_BUFFER_FULL_EOL)), (_U_SINT)((LoggingManager_Run())), (

 ((void *)0)

 ), (_U_UINT)(137), UNITY_DISPLAY_STYLE_INT);



}
