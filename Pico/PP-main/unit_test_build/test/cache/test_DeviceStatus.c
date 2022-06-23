#include "DeviceStatus.h"
#include "unity.h"


void setUp(void)

{

}



void tearDown(void)

{}



void test_DeviceStatusSetAndGet(void)

{

  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , IDLE_E);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(31), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_GetOnEntry())), (

 ((void *)0)

 ), (_U_UINT)(32), UNITY_DISPLAY_STYLE_INT);



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 1

                                     , PUMP_DOWN_E);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(35), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 1

 )), (_U_SINT)((DeviceStatus_GetOnEntry())), (

 ((void *)0)

 ), (_U_UINT)(36), UNITY_DISPLAY_STYLE_INT);



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , THERAPY_DELIVERY_E);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(39), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_GetOnEntry())), (

 ((void *)0)

 ), (_U_UINT)(40), UNITY_DISPLAY_STYLE_INT);



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , FAULT_E);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(43), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_GetOnEntry())), (

 ((void *)0)

 ), (_U_UINT)(44), UNITY_DISPLAY_STYLE_INT);





  bool_t tmp_led_status = DeviceStatus_GetLedsOnStatus();



  DeviceStatus_SetLedsOnStatus(!tmp_led_status);

  UnityAssertEqualNumber((_U_SINT)((!tmp_led_status)), (_U_SINT)((DeviceStatus_GetLedsOnStatus())), (

 ((void *)0)

 ), (_U_UINT)(50), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetLedsOnStatus((bool_t) 

                              1

                                  );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 1

 )), (_U_SINT)((DeviceStatus_GetLedsOnStatus())), (

 ((void *)0)

 ), (_U_UINT)(54), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetLedsOnStatus((bool_t) 

                              0

                                   );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_GetLedsOnStatus())), (

 ((void *)0)

 ), (_U_UINT)(58), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetCheckStatusAlert((bool_t) 

                                  0

                                       );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_GetCheckStatusAlert())), (

 ((void *)0)

 ), (_U_UINT)(62), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetCheckStatusAlert((bool_t) 

                                  1

                                      );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 1

 )), (_U_SINT)((DeviceStatus_GetCheckStatusAlert())), (

 ((void *)0)

 ), (_U_UINT)(66), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetDeepSleepModeStatus((bool_t) 

                                     0

                                          );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_isGoingInDeepSleep())), (

 ((void *)0)

 ), (_U_UINT)(70), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetDeepSleepModeStatus((bool_t) 

                                     1

                                         );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 1

 )), (_U_SINT)((DeviceStatus_isGoingInDeepSleep())), (

 ((void *)0)

 ), (_U_UINT)(74), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetButtonPressFromLeak((bool_t) 

                                     0

                                          );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_GetButtonPressFromLeak())), (

 ((void *)0)

 ), (_U_UINT)(78), UNITY_DISPLAY_STYLE_INT);





  DeviceStatus_SetButtonPressFromLeak((bool_t) 

                                     1

                                         );

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 1

 )), (_U_SINT)((DeviceStatus_GetButtonPressFromLeak())), (

 ((void *)0)

 ), (_U_UINT)(82), UNITY_DISPLAY_STYLE_INT);













  DeviceStatus_SetLedsOnStatus((bool_t) 

                              1

                                  );

  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 1

                                     , IDLE_E);



  DeviceStatus_Init();

  UnityAssertEqualNumber((_U_SINT)((NONE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(93), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 1

 )), (_U_SINT)((DeviceStatus_GetOnEntry())), (

 ((void *)0)

 ), (_U_UINT)(94), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)(((bool_t) 

 0

 )), (_U_SINT)((DeviceStatus_GetLedsOnStatus())), (

 ((void *)0)

 ), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);

}



void test_IsPumpRunning()

{

  DeviceStatus_SetPumpIsRunning((bool_t) 

                               0

                                    );

  if (!(DeviceStatus_IsRunningPump())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(101)));};



  DeviceStatus_SetPumpIsRunning((bool_t) 

                               1

                                   );

  if ((DeviceStatus_IsRunningPump())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(104)));};



  DeviceStatus_SetPumpIsRunning((bool_t) 

                               0

                                    );

  if (!(DeviceStatus_IsRunningPump())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(107)));};

}



void test_IsPressureSensorReading()

{

  DeviceStatus_SetPressureSensorIsReading((bool_t) 

                                         0

                                              );

  if (!(DeviceStatus_IsReadingPressureSensor())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(113)));};



  DeviceStatus_SetPressureSensorIsReading((bool_t) 

                                         1

                                             );

  if ((DeviceStatus_IsReadingPressureSensor())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(116)));};



  DeviceStatus_SetPressureSensorIsReading((bool_t) 

                                         0

                                              );

  if (!(DeviceStatus_IsReadingPressureSensor())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(119)));};

}
