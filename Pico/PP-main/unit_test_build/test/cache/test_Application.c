#include "Mocki2c.h"
#include "MockI2CEEPROM.h"
#include "MockPerformanceLogger.h"
#include "MockWatchdog.h"
#include "MockDutyCycle.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockPushButton.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "Assert.h"
#include "UIInterfaces.h"
#include "MockTimer.h"
#include "MockStateMachinePOST.h"
#include "MockStateMachineCommon.h"
#include "MockStateMachineNre.h"
#include "MockStateMachineTherapyDelivery.h"
#include "MockStateMachineFault.h"
#include "MockStateMachineShutdown.h"
#include "MockStateMachinePumpDown.h"
#include "MockStateMachineIdle.h"
#include "MockStateMachine.h"
#include "DeviceStatus.h"
#include "MockLoggingManager.h"
#include "MockAlertManager.h"
#include "Application.h"
#include "unity.h"


















void setUp(void)

{

  HardwareInterface_EnableGlobalInterrupt_CMockIgnore();

  HardwareInterface_DisableGlobalInterrupt_CMockIgnore();

  Idle_Init_CMockIgnoreAndReturn(59, EC_OK_E);

  PumpDown_Init_CMockIgnoreAndReturn(60, EC_OK_E);

  TherapyDelivery_Init_CMockIgnoreAndReturn(61, EC_OK_E);

  POST_Init_CMockIgnoreAndReturn(62, EC_OK_E);

}



void tearDown(void)

{}



void test_ApplicationInitInitialiseManagers(void)

{

  TimerCounters_Init_CMockExpect(70);

  AlertManager_Init_CMockExpectAndReturn(71, EC_OK_E);

  StateMachine_Init_CMockExpectAndReturn(72, EC_OK_E);



  HardwareInterface_SystemInitialise_CMockIgnore();

  HardwareInterface_EnableGlobalInterrupt_CMockIgnore();

  HardwareInterface_EnablePeripheralInterrupt_CMockIgnore();



  LoggingManager_Init_CMockExpect(78);

  Watchdog_Init_CMockExpect(79);

  PerformanceLogger_GetNRE_CMockExpectAndReturn(80, (bool_t) 

 0

 );



  Application_Init();

}



void test_ApplicationSleepGoesToSleepWhenNotAtPOSTStateAndRelaxationOscillatorIsUsed(void)

{

  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , IDLE_E);

  MP_SleepUntilWokenByRelaxationOscillator_CMockExpect(88);

  Application_Stop();



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , PUMP_DOWN_E);

  MP_SleepUntilWokenByRelaxationOscillator_CMockExpect(92);

  Application_Stop();



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , THERAPY_DELIVERY_E);

  MP_SleepUntilWokenByRelaxationOscillator_CMockExpect(96);

  Application_Stop();



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , FAULT_E);

  MP_SleepUntilWokenByRelaxationOscillator_CMockExpect(100);

  Application_Stop();



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , SHUT_DOWN_E);

  MP_SleepUntilWokenByRelaxationOscillator_CMockExpect(104);

  Application_Stop();



  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , NRE_E);

  MP_SleepUntilWokenByRelaxationOscillator_CMockExpect(108);

  Application_Stop();

}



void test_ApplicationDoesNotGoToSleepWhenAtPOSTStateAndRelaxationOscillatorIsUsed(void)

{

  DeviceStatus_StateAndOnEntrySet((bool_t) 

                                 0

                                      , POST_E);

  MP_EnableRelaxationOscillator_CMockExpect(115);

  Application_Stop();

}



void test_RunDoesNotTickControllerWhenTimerFlagIsNotSet()

{

  PM_GetT1Flag_CMockExpectAndReturn(121, (bool_t) 

 0

 );

  PM_GetT1Flag_CMockExpectAndReturn(122, (bool_t) 

 1

 );



  AlertManager_Run_CMockExpectAndReturn(124, EC_OK_E);

  StateMachine_Run_CMockExpectAndReturn(125, EC_OK_E);

  LoggingManager_Run_CMockExpectAndReturn(126, EC_OK_E);

  Watchdog_Clear_CMockExpect(127);





  Application_Run();

}



void test_RunTicksControllersAndState(void)

{

  PM_GetT1Flag_CMockExpectAndReturn(135, (bool_t) 

 1

 );



  AlertManager_Run_CMockExpectAndReturn(137, EC_OK_E);

  StateMachine_Run_CMockExpectAndReturn(138, EC_OK_E);

  LoggingManager_Run_CMockExpectAndReturn(139, EC_OK_E);

  Watchdog_Clear_CMockExpect(140);



  Application_Run();

}
