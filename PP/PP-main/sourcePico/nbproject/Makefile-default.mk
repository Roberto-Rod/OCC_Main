#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/clc1.c mcc_generated_files/eusart.c mcc_generated_files/memory.c mcc_generated_files/pwm1.c mcc_generated_files/pwm2.c mcc_generated_files/tmr0.c mcc_generated_files/tmr2.c application/Application.c common/Debug.c common/Assert.c devices/DeviceStatus.c devices/LED.c devices/PushButton.c devices/HardwareInterface.c devices/Pump.c devices/Pressure_Part1.c devices/Pressure_Part2.c devices/Pressure_Part3.c devices/Pressure_Part4.c devices/I2CEEPROM.c devices/Transmit.c devices/DutyCycle.c devices/UIInterfaces.c devices/PerformanceLogger.c devices/Battery.c devices/Watchdog.c devices/PowerControl.c devices/Timer.c devices/PumpFrequencyTracker.c managers/StateMachine.c managers/StateMachineIdle.c managers/StateMachinePumpDown.c managers/StateMachineShutdown.c managers/StateMachineTherapyDelivery.c managers/StateMachineFault.c managers/StateMachinePOST_internal.c managers/StateMachinePOST.c managers/AlertManager.c managers/StateMachineCommon.c managers/StateMachineNre.c managers/LoggingManager.c mcc_generated_files/device_config.c mcc_generated_files/adc.c mcc_generated_files/dac.c mcc_generated_files/i2c.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr1.c mcc_generated_files/fvr.c mcc_generated_files/nco1.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/clc1.p1 ${OBJECTDIR}/mcc_generated_files/eusart.p1 ${OBJECTDIR}/mcc_generated_files/memory.p1 ${OBJECTDIR}/mcc_generated_files/pwm1.p1 ${OBJECTDIR}/mcc_generated_files/pwm2.p1 ${OBJECTDIR}/mcc_generated_files/tmr0.p1 ${OBJECTDIR}/mcc_generated_files/tmr2.p1 ${OBJECTDIR}/application/Application.p1 ${OBJECTDIR}/common/Debug.p1 ${OBJECTDIR}/common/Assert.p1 ${OBJECTDIR}/devices/DeviceStatus.p1 ${OBJECTDIR}/devices/LED.p1 ${OBJECTDIR}/devices/PushButton.p1 ${OBJECTDIR}/devices/HardwareInterface.p1 ${OBJECTDIR}/devices/Pump.p1 ${OBJECTDIR}/devices/Pressure_Part1.p1 ${OBJECTDIR}/devices/Pressure_Part2.p1 ${OBJECTDIR}/devices/Pressure_Part3.p1 ${OBJECTDIR}/devices/Pressure_Part4.p1 ${OBJECTDIR}/devices/I2CEEPROM.p1 ${OBJECTDIR}/devices/Transmit.p1 ${OBJECTDIR}/devices/DutyCycle.p1 ${OBJECTDIR}/devices/UIInterfaces.p1 ${OBJECTDIR}/devices/PerformanceLogger.p1 ${OBJECTDIR}/devices/Battery.p1 ${OBJECTDIR}/devices/Watchdog.p1 ${OBJECTDIR}/devices/PowerControl.p1 ${OBJECTDIR}/devices/Timer.p1 ${OBJECTDIR}/devices/PumpFrequencyTracker.p1 ${OBJECTDIR}/managers/StateMachine.p1 ${OBJECTDIR}/managers/StateMachineIdle.p1 ${OBJECTDIR}/managers/StateMachinePumpDown.p1 ${OBJECTDIR}/managers/StateMachineShutdown.p1 ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1 ${OBJECTDIR}/managers/StateMachineFault.p1 ${OBJECTDIR}/managers/StateMachinePOST_internal.p1 ${OBJECTDIR}/managers/StateMachinePOST.p1 ${OBJECTDIR}/managers/AlertManager.p1 ${OBJECTDIR}/managers/StateMachineCommon.p1 ${OBJECTDIR}/managers/StateMachineNre.p1 ${OBJECTDIR}/managers/LoggingManager.p1 ${OBJECTDIR}/mcc_generated_files/device_config.p1 ${OBJECTDIR}/mcc_generated_files/adc.p1 ${OBJECTDIR}/mcc_generated_files/dac.p1 ${OBJECTDIR}/mcc_generated_files/i2c.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/fvr.p1 ${OBJECTDIR}/mcc_generated_files/nco1.p1 ${OBJECTDIR}/main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/clc1.p1.d ${OBJECTDIR}/mcc_generated_files/eusart.p1.d ${OBJECTDIR}/mcc_generated_files/memory.p1.d ${OBJECTDIR}/mcc_generated_files/pwm1.p1.d ${OBJECTDIR}/mcc_generated_files/pwm2.p1.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d ${OBJECTDIR}/application/Application.p1.d ${OBJECTDIR}/common/Debug.p1.d ${OBJECTDIR}/common/Assert.p1.d ${OBJECTDIR}/devices/DeviceStatus.p1.d ${OBJECTDIR}/devices/LED.p1.d ${OBJECTDIR}/devices/PushButton.p1.d ${OBJECTDIR}/devices/HardwareInterface.p1.d ${OBJECTDIR}/devices/Pump.p1.d ${OBJECTDIR}/devices/Pressure_Part1.p1.d ${OBJECTDIR}/devices/Pressure_Part2.p1.d ${OBJECTDIR}/devices/Pressure_Part3.p1.d ${OBJECTDIR}/devices/Pressure_Part4.p1.d ${OBJECTDIR}/devices/I2CEEPROM.p1.d ${OBJECTDIR}/devices/Transmit.p1.d ${OBJECTDIR}/devices/DutyCycle.p1.d ${OBJECTDIR}/devices/UIInterfaces.p1.d ${OBJECTDIR}/devices/PerformanceLogger.p1.d ${OBJECTDIR}/devices/Battery.p1.d ${OBJECTDIR}/devices/Watchdog.p1.d ${OBJECTDIR}/devices/PowerControl.p1.d ${OBJECTDIR}/devices/Timer.p1.d ${OBJECTDIR}/devices/PumpFrequencyTracker.p1.d ${OBJECTDIR}/managers/StateMachine.p1.d ${OBJECTDIR}/managers/StateMachineIdle.p1.d ${OBJECTDIR}/managers/StateMachinePumpDown.p1.d ${OBJECTDIR}/managers/StateMachineShutdown.p1.d ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1.d ${OBJECTDIR}/managers/StateMachineFault.p1.d ${OBJECTDIR}/managers/StateMachinePOST_internal.p1.d ${OBJECTDIR}/managers/StateMachinePOST.p1.d ${OBJECTDIR}/managers/AlertManager.p1.d ${OBJECTDIR}/managers/StateMachineCommon.p1.d ${OBJECTDIR}/managers/StateMachineNre.p1.d ${OBJECTDIR}/managers/LoggingManager.p1.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d ${OBJECTDIR}/mcc_generated_files/adc.p1.d ${OBJECTDIR}/mcc_generated_files/dac.p1.d ${OBJECTDIR}/mcc_generated_files/i2c.p1.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d ${OBJECTDIR}/mcc_generated_files/nco1.p1.d ${OBJECTDIR}/main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/clc1.p1 ${OBJECTDIR}/mcc_generated_files/eusart.p1 ${OBJECTDIR}/mcc_generated_files/memory.p1 ${OBJECTDIR}/mcc_generated_files/pwm1.p1 ${OBJECTDIR}/mcc_generated_files/pwm2.p1 ${OBJECTDIR}/mcc_generated_files/tmr0.p1 ${OBJECTDIR}/mcc_generated_files/tmr2.p1 ${OBJECTDIR}/application/Application.p1 ${OBJECTDIR}/common/Debug.p1 ${OBJECTDIR}/common/Assert.p1 ${OBJECTDIR}/devices/DeviceStatus.p1 ${OBJECTDIR}/devices/LED.p1 ${OBJECTDIR}/devices/PushButton.p1 ${OBJECTDIR}/devices/HardwareInterface.p1 ${OBJECTDIR}/devices/Pump.p1 ${OBJECTDIR}/devices/Pressure_Part1.p1 ${OBJECTDIR}/devices/Pressure_Part2.p1 ${OBJECTDIR}/devices/Pressure_Part3.p1 ${OBJECTDIR}/devices/Pressure_Part4.p1 ${OBJECTDIR}/devices/I2CEEPROM.p1 ${OBJECTDIR}/devices/Transmit.p1 ${OBJECTDIR}/devices/DutyCycle.p1 ${OBJECTDIR}/devices/UIInterfaces.p1 ${OBJECTDIR}/devices/PerformanceLogger.p1 ${OBJECTDIR}/devices/Battery.p1 ${OBJECTDIR}/devices/Watchdog.p1 ${OBJECTDIR}/devices/PowerControl.p1 ${OBJECTDIR}/devices/Timer.p1 ${OBJECTDIR}/devices/PumpFrequencyTracker.p1 ${OBJECTDIR}/managers/StateMachine.p1 ${OBJECTDIR}/managers/StateMachineIdle.p1 ${OBJECTDIR}/managers/StateMachinePumpDown.p1 ${OBJECTDIR}/managers/StateMachineShutdown.p1 ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1 ${OBJECTDIR}/managers/StateMachineFault.p1 ${OBJECTDIR}/managers/StateMachinePOST_internal.p1 ${OBJECTDIR}/managers/StateMachinePOST.p1 ${OBJECTDIR}/managers/AlertManager.p1 ${OBJECTDIR}/managers/StateMachineCommon.p1 ${OBJECTDIR}/managers/StateMachineNre.p1 ${OBJECTDIR}/managers/LoggingManager.p1 ${OBJECTDIR}/mcc_generated_files/device_config.p1 ${OBJECTDIR}/mcc_generated_files/adc.p1 ${OBJECTDIR}/mcc_generated_files/dac.p1 ${OBJECTDIR}/mcc_generated_files/i2c.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/fvr.p1 ${OBJECTDIR}/mcc_generated_files/nco1.p1 ${OBJECTDIR}/main.p1

# Source Files
SOURCEFILES=mcc_generated_files/clc1.c mcc_generated_files/eusart.c mcc_generated_files/memory.c mcc_generated_files/pwm1.c mcc_generated_files/pwm2.c mcc_generated_files/tmr0.c mcc_generated_files/tmr2.c application/Application.c common/Debug.c common/Assert.c devices/DeviceStatus.c devices/LED.c devices/PushButton.c devices/HardwareInterface.c devices/Pump.c devices/Pressure_Part1.c devices/Pressure_Part2.c devices/Pressure_Part3.c devices/Pressure_Part4.c devices/I2CEEPROM.c devices/Transmit.c devices/DutyCycle.c devices/UIInterfaces.c devices/PerformanceLogger.c devices/Battery.c devices/Watchdog.c devices/PowerControl.c devices/Timer.c devices/PumpFrequencyTracker.c managers/StateMachine.c managers/StateMachineIdle.c managers/StateMachinePumpDown.c managers/StateMachineShutdown.c managers/StateMachineTherapyDelivery.c managers/StateMachineFault.c managers/StateMachinePOST_internal.c managers/StateMachinePOST.c managers/AlertManager.c managers/StateMachineCommon.c managers/StateMachineNre.c managers/LoggingManager.c mcc_generated_files/device_config.c mcc_generated_files/adc.c mcc_generated_files/dac.c mcc_generated_files/i2c.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr1.c mcc_generated_files/fvr.c mcc_generated_files/nco1.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16LF1509
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/clc1.p1: mcc_generated_files/clc1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/clc1.p1 mcc_generated_files/clc1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/clc1.d ${OBJECTDIR}/mcc_generated_files/clc1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/clc1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/eusart.p1: mcc_generated_files/eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart.p1 mcc_generated_files/eusart.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart.d ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/memory.p1: mcc_generated_files/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/memory.p1 mcc_generated_files/memory.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/memory.d ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/memory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pwm1.p1: mcc_generated_files/pwm1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pwm1.p1 mcc_generated_files/pwm1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pwm1.d ${OBJECTDIR}/mcc_generated_files/pwm1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pwm1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pwm2.p1: mcc_generated_files/pwm2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pwm2.p1 mcc_generated_files/pwm2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pwm2.d ${OBJECTDIR}/mcc_generated_files/pwm2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pwm2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr0.p1: mcc_generated_files/tmr0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr0.p1 mcc_generated_files/tmr0.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr0.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr2.p1: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr2.p1 mcc_generated_files/tmr2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr2.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/application/Application.p1: application/Application.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/application" 
	@${RM} ${OBJECTDIR}/application/Application.p1.d 
	@${RM} ${OBJECTDIR}/application/Application.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/application/Application.p1 application/Application.c 
	@-${MV} ${OBJECTDIR}/application/Application.d ${OBJECTDIR}/application/Application.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/application/Application.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/common/Debug.p1: common/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/Debug.p1.d 
	@${RM} ${OBJECTDIR}/common/Debug.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/common/Debug.p1 common/Debug.c 
	@-${MV} ${OBJECTDIR}/common/Debug.d ${OBJECTDIR}/common/Debug.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/common/Debug.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/common/Assert.p1: common/Assert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/Assert.p1.d 
	@${RM} ${OBJECTDIR}/common/Assert.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/common/Assert.p1 common/Assert.c 
	@-${MV} ${OBJECTDIR}/common/Assert.d ${OBJECTDIR}/common/Assert.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/common/Assert.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/DeviceStatus.p1: devices/DeviceStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/DeviceStatus.p1.d 
	@${RM} ${OBJECTDIR}/devices/DeviceStatus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/DeviceStatus.p1 devices/DeviceStatus.c 
	@-${MV} ${OBJECTDIR}/devices/DeviceStatus.d ${OBJECTDIR}/devices/DeviceStatus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/DeviceStatus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/LED.p1: devices/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/LED.p1.d 
	@${RM} ${OBJECTDIR}/devices/LED.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/LED.p1 devices/LED.c 
	@-${MV} ${OBJECTDIR}/devices/LED.d ${OBJECTDIR}/devices/LED.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/LED.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PushButton.p1: devices/PushButton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PushButton.p1.d 
	@${RM} ${OBJECTDIR}/devices/PushButton.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PushButton.p1 devices/PushButton.c 
	@-${MV} ${OBJECTDIR}/devices/PushButton.d ${OBJECTDIR}/devices/PushButton.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PushButton.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/HardwareInterface.p1: devices/HardwareInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/HardwareInterface.p1.d 
	@${RM} ${OBJECTDIR}/devices/HardwareInterface.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/HardwareInterface.p1 devices/HardwareInterface.c 
	@-${MV} ${OBJECTDIR}/devices/HardwareInterface.d ${OBJECTDIR}/devices/HardwareInterface.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/HardwareInterface.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pump.p1: devices/Pump.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pump.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pump.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pump.p1 devices/Pump.c 
	@-${MV} ${OBJECTDIR}/devices/Pump.d ${OBJECTDIR}/devices/Pump.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pump.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part1.p1: devices/Pressure_Part1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part1.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part1.p1 devices/Pressure_Part1.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part1.d ${OBJECTDIR}/devices/Pressure_Part1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part2.p1: devices/Pressure_Part2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part2.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part2.p1 devices/Pressure_Part2.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part2.d ${OBJECTDIR}/devices/Pressure_Part2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part3.p1: devices/Pressure_Part3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part3.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part3.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part3.p1 devices/Pressure_Part3.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part3.d ${OBJECTDIR}/devices/Pressure_Part3.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part3.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part4.p1: devices/Pressure_Part4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part4.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part4.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part4.p1 devices/Pressure_Part4.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part4.d ${OBJECTDIR}/devices/Pressure_Part4.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part4.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/I2CEEPROM.p1: devices/I2CEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/I2CEEPROM.p1.d 
	@${RM} ${OBJECTDIR}/devices/I2CEEPROM.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/I2CEEPROM.p1 devices/I2CEEPROM.c 
	@-${MV} ${OBJECTDIR}/devices/I2CEEPROM.d ${OBJECTDIR}/devices/I2CEEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/I2CEEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Transmit.p1: devices/Transmit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Transmit.p1.d 
	@${RM} ${OBJECTDIR}/devices/Transmit.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Transmit.p1 devices/Transmit.c 
	@-${MV} ${OBJECTDIR}/devices/Transmit.d ${OBJECTDIR}/devices/Transmit.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Transmit.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/DutyCycle.p1: devices/DutyCycle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/DutyCycle.p1.d 
	@${RM} ${OBJECTDIR}/devices/DutyCycle.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/DutyCycle.p1 devices/DutyCycle.c 
	@-${MV} ${OBJECTDIR}/devices/DutyCycle.d ${OBJECTDIR}/devices/DutyCycle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/DutyCycle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/UIInterfaces.p1: devices/UIInterfaces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/UIInterfaces.p1.d 
	@${RM} ${OBJECTDIR}/devices/UIInterfaces.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/UIInterfaces.p1 devices/UIInterfaces.c 
	@-${MV} ${OBJECTDIR}/devices/UIInterfaces.d ${OBJECTDIR}/devices/UIInterfaces.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/UIInterfaces.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PerformanceLogger.p1: devices/PerformanceLogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PerformanceLogger.p1.d 
	@${RM} ${OBJECTDIR}/devices/PerformanceLogger.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PerformanceLogger.p1 devices/PerformanceLogger.c 
	@-${MV} ${OBJECTDIR}/devices/PerformanceLogger.d ${OBJECTDIR}/devices/PerformanceLogger.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PerformanceLogger.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Battery.p1: devices/Battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Battery.p1.d 
	@${RM} ${OBJECTDIR}/devices/Battery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Battery.p1 devices/Battery.c 
	@-${MV} ${OBJECTDIR}/devices/Battery.d ${OBJECTDIR}/devices/Battery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Battery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Watchdog.p1: devices/Watchdog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Watchdog.p1.d 
	@${RM} ${OBJECTDIR}/devices/Watchdog.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Watchdog.p1 devices/Watchdog.c 
	@-${MV} ${OBJECTDIR}/devices/Watchdog.d ${OBJECTDIR}/devices/Watchdog.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Watchdog.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PowerControl.p1: devices/PowerControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PowerControl.p1.d 
	@${RM} ${OBJECTDIR}/devices/PowerControl.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PowerControl.p1 devices/PowerControl.c 
	@-${MV} ${OBJECTDIR}/devices/PowerControl.d ${OBJECTDIR}/devices/PowerControl.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PowerControl.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Timer.p1: devices/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Timer.p1.d 
	@${RM} ${OBJECTDIR}/devices/Timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Timer.p1 devices/Timer.c 
	@-${MV} ${OBJECTDIR}/devices/Timer.d ${OBJECTDIR}/devices/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PumpFrequencyTracker.p1: devices/PumpFrequencyTracker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PumpFrequencyTracker.p1.d 
	@${RM} ${OBJECTDIR}/devices/PumpFrequencyTracker.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PumpFrequencyTracker.p1 devices/PumpFrequencyTracker.c 
	@-${MV} ${OBJECTDIR}/devices/PumpFrequencyTracker.d ${OBJECTDIR}/devices/PumpFrequencyTracker.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PumpFrequencyTracker.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachine.p1: managers/StateMachine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachine.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachine.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachine.p1 managers/StateMachine.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachine.d ${OBJECTDIR}/managers/StateMachine.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachine.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineIdle.p1: managers/StateMachineIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineIdle.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineIdle.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineIdle.p1 managers/StateMachineIdle.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineIdle.d ${OBJECTDIR}/managers/StateMachineIdle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineIdle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachinePumpDown.p1: managers/StateMachinePumpDown.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachinePumpDown.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachinePumpDown.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachinePumpDown.p1 managers/StateMachinePumpDown.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachinePumpDown.d ${OBJECTDIR}/managers/StateMachinePumpDown.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachinePumpDown.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineShutdown.p1: managers/StateMachineShutdown.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineShutdown.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineShutdown.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineShutdown.p1 managers/StateMachineShutdown.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineShutdown.d ${OBJECTDIR}/managers/StateMachineShutdown.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineShutdown.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1: managers/StateMachineTherapyDelivery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1 managers/StateMachineTherapyDelivery.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.d ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineFault.p1: managers/StateMachineFault.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineFault.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineFault.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineFault.p1 managers/StateMachineFault.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineFault.d ${OBJECTDIR}/managers/StateMachineFault.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineFault.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachinePOST_internal.p1: managers/StateMachinePOST_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST_internal.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST_internal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachinePOST_internal.p1 managers/StateMachinePOST_internal.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachinePOST_internal.d ${OBJECTDIR}/managers/StateMachinePOST_internal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachinePOST_internal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachinePOST.p1: managers/StateMachinePOST.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachinePOST.p1 managers/StateMachinePOST.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachinePOST.d ${OBJECTDIR}/managers/StateMachinePOST.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachinePOST.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/AlertManager.p1: managers/AlertManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/AlertManager.p1.d 
	@${RM} ${OBJECTDIR}/managers/AlertManager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/AlertManager.p1 managers/AlertManager.c 
	@-${MV} ${OBJECTDIR}/managers/AlertManager.d ${OBJECTDIR}/managers/AlertManager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/AlertManager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineCommon.p1: managers/StateMachineCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineCommon.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineCommon.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineCommon.p1 managers/StateMachineCommon.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineCommon.d ${OBJECTDIR}/managers/StateMachineCommon.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineCommon.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineNre.p1: managers/StateMachineNre.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineNre.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineNre.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineNre.p1 managers/StateMachineNre.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineNre.d ${OBJECTDIR}/managers/StateMachineNre.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineNre.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/LoggingManager.p1: managers/LoggingManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/LoggingManager.p1.d 
	@${RM} ${OBJECTDIR}/managers/LoggingManager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/LoggingManager.p1 managers/LoggingManager.c 
	@-${MV} ${OBJECTDIR}/managers/LoggingManager.d ${OBJECTDIR}/managers/LoggingManager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/LoggingManager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/device_config.p1: mcc_generated_files/device_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/device_config.p1 mcc_generated_files/device_config.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/device_config.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/adc.p1: mcc_generated_files/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adc.p1 mcc_generated_files/adc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adc.d ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/dac.p1: mcc_generated_files/dac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/dac.p1 mcc_generated_files/dac.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/dac.d ${OBJECTDIR}/mcc_generated_files/dac.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/dac.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/i2c.p1: mcc_generated_files/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/i2c.p1 mcc_generated_files/i2c.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/i2c.d ${OBJECTDIR}/mcc_generated_files/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/fvr.p1: mcc_generated_files/fvr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/fvr.p1 mcc_generated_files/fvr.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/fvr.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/nco1.p1: mcc_generated_files/nco1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/nco1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/nco1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/nco1.p1 mcc_generated_files/nco1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/nco1.d ${OBJECTDIR}/mcc_generated_files/nco1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/nco1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/mcc_generated_files/clc1.p1: mcc_generated_files/clc1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/clc1.p1 mcc_generated_files/clc1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/clc1.d ${OBJECTDIR}/mcc_generated_files/clc1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/clc1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/eusart.p1: mcc_generated_files/eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart.p1 mcc_generated_files/eusart.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart.d ${OBJECTDIR}/mcc_generated_files/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/memory.p1: mcc_generated_files/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/memory.p1 mcc_generated_files/memory.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/memory.d ${OBJECTDIR}/mcc_generated_files/memory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/memory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pwm1.p1: mcc_generated_files/pwm1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pwm1.p1 mcc_generated_files/pwm1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pwm1.d ${OBJECTDIR}/mcc_generated_files/pwm1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pwm1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pwm2.p1: mcc_generated_files/pwm2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pwm2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pwm2.p1 mcc_generated_files/pwm2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pwm2.d ${OBJECTDIR}/mcc_generated_files/pwm2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pwm2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr0.p1: mcc_generated_files/tmr0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr0.p1 mcc_generated_files/tmr0.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr0.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr2.p1: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr2.p1 mcc_generated_files/tmr2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr2.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/application/Application.p1: application/Application.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/application" 
	@${RM} ${OBJECTDIR}/application/Application.p1.d 
	@${RM} ${OBJECTDIR}/application/Application.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/application/Application.p1 application/Application.c 
	@-${MV} ${OBJECTDIR}/application/Application.d ${OBJECTDIR}/application/Application.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/application/Application.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/common/Debug.p1: common/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/Debug.p1.d 
	@${RM} ${OBJECTDIR}/common/Debug.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/common/Debug.p1 common/Debug.c 
	@-${MV} ${OBJECTDIR}/common/Debug.d ${OBJECTDIR}/common/Debug.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/common/Debug.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/common/Assert.p1: common/Assert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/common" 
	@${RM} ${OBJECTDIR}/common/Assert.p1.d 
	@${RM} ${OBJECTDIR}/common/Assert.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/common/Assert.p1 common/Assert.c 
	@-${MV} ${OBJECTDIR}/common/Assert.d ${OBJECTDIR}/common/Assert.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/common/Assert.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/DeviceStatus.p1: devices/DeviceStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/DeviceStatus.p1.d 
	@${RM} ${OBJECTDIR}/devices/DeviceStatus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/DeviceStatus.p1 devices/DeviceStatus.c 
	@-${MV} ${OBJECTDIR}/devices/DeviceStatus.d ${OBJECTDIR}/devices/DeviceStatus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/DeviceStatus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/LED.p1: devices/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/LED.p1.d 
	@${RM} ${OBJECTDIR}/devices/LED.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/LED.p1 devices/LED.c 
	@-${MV} ${OBJECTDIR}/devices/LED.d ${OBJECTDIR}/devices/LED.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/LED.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PushButton.p1: devices/PushButton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PushButton.p1.d 
	@${RM} ${OBJECTDIR}/devices/PushButton.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PushButton.p1 devices/PushButton.c 
	@-${MV} ${OBJECTDIR}/devices/PushButton.d ${OBJECTDIR}/devices/PushButton.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PushButton.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/HardwareInterface.p1: devices/HardwareInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/HardwareInterface.p1.d 
	@${RM} ${OBJECTDIR}/devices/HardwareInterface.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/HardwareInterface.p1 devices/HardwareInterface.c 
	@-${MV} ${OBJECTDIR}/devices/HardwareInterface.d ${OBJECTDIR}/devices/HardwareInterface.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/HardwareInterface.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pump.p1: devices/Pump.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pump.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pump.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pump.p1 devices/Pump.c 
	@-${MV} ${OBJECTDIR}/devices/Pump.d ${OBJECTDIR}/devices/Pump.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pump.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part1.p1: devices/Pressure_Part1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part1.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part1.p1 devices/Pressure_Part1.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part1.d ${OBJECTDIR}/devices/Pressure_Part1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part2.p1: devices/Pressure_Part2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part2.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part2.p1 devices/Pressure_Part2.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part2.d ${OBJECTDIR}/devices/Pressure_Part2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part3.p1: devices/Pressure_Part3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part3.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part3.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part3.p1 devices/Pressure_Part3.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part3.d ${OBJECTDIR}/devices/Pressure_Part3.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part3.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Pressure_Part4.p1: devices/Pressure_Part4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part4.p1.d 
	@${RM} ${OBJECTDIR}/devices/Pressure_Part4.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Pressure_Part4.p1 devices/Pressure_Part4.c 
	@-${MV} ${OBJECTDIR}/devices/Pressure_Part4.d ${OBJECTDIR}/devices/Pressure_Part4.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Pressure_Part4.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/I2CEEPROM.p1: devices/I2CEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/I2CEEPROM.p1.d 
	@${RM} ${OBJECTDIR}/devices/I2CEEPROM.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/I2CEEPROM.p1 devices/I2CEEPROM.c 
	@-${MV} ${OBJECTDIR}/devices/I2CEEPROM.d ${OBJECTDIR}/devices/I2CEEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/I2CEEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Transmit.p1: devices/Transmit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Transmit.p1.d 
	@${RM} ${OBJECTDIR}/devices/Transmit.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Transmit.p1 devices/Transmit.c 
	@-${MV} ${OBJECTDIR}/devices/Transmit.d ${OBJECTDIR}/devices/Transmit.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Transmit.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/DutyCycle.p1: devices/DutyCycle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/DutyCycle.p1.d 
	@${RM} ${OBJECTDIR}/devices/DutyCycle.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/DutyCycle.p1 devices/DutyCycle.c 
	@-${MV} ${OBJECTDIR}/devices/DutyCycle.d ${OBJECTDIR}/devices/DutyCycle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/DutyCycle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/UIInterfaces.p1: devices/UIInterfaces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/UIInterfaces.p1.d 
	@${RM} ${OBJECTDIR}/devices/UIInterfaces.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/UIInterfaces.p1 devices/UIInterfaces.c 
	@-${MV} ${OBJECTDIR}/devices/UIInterfaces.d ${OBJECTDIR}/devices/UIInterfaces.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/UIInterfaces.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PerformanceLogger.p1: devices/PerformanceLogger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PerformanceLogger.p1.d 
	@${RM} ${OBJECTDIR}/devices/PerformanceLogger.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PerformanceLogger.p1 devices/PerformanceLogger.c 
	@-${MV} ${OBJECTDIR}/devices/PerformanceLogger.d ${OBJECTDIR}/devices/PerformanceLogger.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PerformanceLogger.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Battery.p1: devices/Battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Battery.p1.d 
	@${RM} ${OBJECTDIR}/devices/Battery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Battery.p1 devices/Battery.c 
	@-${MV} ${OBJECTDIR}/devices/Battery.d ${OBJECTDIR}/devices/Battery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Battery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Watchdog.p1: devices/Watchdog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Watchdog.p1.d 
	@${RM} ${OBJECTDIR}/devices/Watchdog.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Watchdog.p1 devices/Watchdog.c 
	@-${MV} ${OBJECTDIR}/devices/Watchdog.d ${OBJECTDIR}/devices/Watchdog.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Watchdog.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PowerControl.p1: devices/PowerControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PowerControl.p1.d 
	@${RM} ${OBJECTDIR}/devices/PowerControl.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PowerControl.p1 devices/PowerControl.c 
	@-${MV} ${OBJECTDIR}/devices/PowerControl.d ${OBJECTDIR}/devices/PowerControl.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PowerControl.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/Timer.p1: devices/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/Timer.p1.d 
	@${RM} ${OBJECTDIR}/devices/Timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/Timer.p1 devices/Timer.c 
	@-${MV} ${OBJECTDIR}/devices/Timer.d ${OBJECTDIR}/devices/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/devices/PumpFrequencyTracker.p1: devices/PumpFrequencyTracker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/devices" 
	@${RM} ${OBJECTDIR}/devices/PumpFrequencyTracker.p1.d 
	@${RM} ${OBJECTDIR}/devices/PumpFrequencyTracker.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/devices/PumpFrequencyTracker.p1 devices/PumpFrequencyTracker.c 
	@-${MV} ${OBJECTDIR}/devices/PumpFrequencyTracker.d ${OBJECTDIR}/devices/PumpFrequencyTracker.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/devices/PumpFrequencyTracker.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachine.p1: managers/StateMachine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachine.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachine.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachine.p1 managers/StateMachine.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachine.d ${OBJECTDIR}/managers/StateMachine.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachine.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineIdle.p1: managers/StateMachineIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineIdle.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineIdle.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineIdle.p1 managers/StateMachineIdle.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineIdle.d ${OBJECTDIR}/managers/StateMachineIdle.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineIdle.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachinePumpDown.p1: managers/StateMachinePumpDown.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachinePumpDown.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachinePumpDown.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachinePumpDown.p1 managers/StateMachinePumpDown.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachinePumpDown.d ${OBJECTDIR}/managers/StateMachinePumpDown.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachinePumpDown.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineShutdown.p1: managers/StateMachineShutdown.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineShutdown.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineShutdown.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineShutdown.p1 managers/StateMachineShutdown.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineShutdown.d ${OBJECTDIR}/managers/StateMachineShutdown.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineShutdown.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1: managers/StateMachineTherapyDelivery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1 managers/StateMachineTherapyDelivery.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.d ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineTherapyDelivery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineFault.p1: managers/StateMachineFault.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineFault.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineFault.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineFault.p1 managers/StateMachineFault.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineFault.d ${OBJECTDIR}/managers/StateMachineFault.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineFault.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachinePOST_internal.p1: managers/StateMachinePOST_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST_internal.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST_internal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachinePOST_internal.p1 managers/StateMachinePOST_internal.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachinePOST_internal.d ${OBJECTDIR}/managers/StateMachinePOST_internal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachinePOST_internal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachinePOST.p1: managers/StateMachinePOST.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachinePOST.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachinePOST.p1 managers/StateMachinePOST.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachinePOST.d ${OBJECTDIR}/managers/StateMachinePOST.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachinePOST.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/AlertManager.p1: managers/AlertManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/AlertManager.p1.d 
	@${RM} ${OBJECTDIR}/managers/AlertManager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/AlertManager.p1 managers/AlertManager.c 
	@-${MV} ${OBJECTDIR}/managers/AlertManager.d ${OBJECTDIR}/managers/AlertManager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/AlertManager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineCommon.p1: managers/StateMachineCommon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineCommon.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineCommon.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineCommon.p1 managers/StateMachineCommon.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineCommon.d ${OBJECTDIR}/managers/StateMachineCommon.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineCommon.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/StateMachineNre.p1: managers/StateMachineNre.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/StateMachineNre.p1.d 
	@${RM} ${OBJECTDIR}/managers/StateMachineNre.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/StateMachineNre.p1 managers/StateMachineNre.c 
	@-${MV} ${OBJECTDIR}/managers/StateMachineNre.d ${OBJECTDIR}/managers/StateMachineNre.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/StateMachineNre.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/managers/LoggingManager.p1: managers/LoggingManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/managers" 
	@${RM} ${OBJECTDIR}/managers/LoggingManager.p1.d 
	@${RM} ${OBJECTDIR}/managers/LoggingManager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/managers/LoggingManager.p1 managers/LoggingManager.c 
	@-${MV} ${OBJECTDIR}/managers/LoggingManager.d ${OBJECTDIR}/managers/LoggingManager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/managers/LoggingManager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/device_config.p1: mcc_generated_files/device_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/device_config.p1 mcc_generated_files/device_config.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/device_config.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/adc.p1: mcc_generated_files/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adc.p1 mcc_generated_files/adc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adc.d ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/dac.p1: mcc_generated_files/dac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/dac.p1 mcc_generated_files/dac.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/dac.d ${OBJECTDIR}/mcc_generated_files/dac.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/dac.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/i2c.p1: mcc_generated_files/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/i2c.p1 mcc_generated_files/i2c.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/i2c.d ${OBJECTDIR}/mcc_generated_files/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/fvr.p1: mcc_generated_files/fvr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/fvr.p1 mcc_generated_files/fvr.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/fvr.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/nco1.p1: mcc_generated_files/nco1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/nco1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/nco1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/nco1.p1 mcc_generated_files/nco1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/nco1.d ${OBJECTDIR}/mcc_generated_files/nco1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/nco1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto      -mram=default,-320-32f  $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"other" -I"mcc_generated_files" -I"managers" -I"devices" -I"common" -I"application" -v -mwarn=0 -mext=cci -msummary=+psect,+class,+mem,+hex,+file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/sourcePico.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
