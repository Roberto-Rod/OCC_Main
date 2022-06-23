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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/clock.c mcc_generated_files/traps.c mcc_generated_files/pin_manager.c mcc_generated_files/system.c mcc_generated_files/mcc.c mcc_generated_files/adc1.c mcc_generated_files/interrupt_manager.c mcc_generated_files/uart2.c mcc_generated_files/uart1.c mcc_generated_files/tmr1.c main.c debug.c drv_rtc.c dar_comms.c i2c_bit_bang.c power_switch_interrupt.c drv_STTS75.c drv_LIS2DS12.c battery_capacity.c message_exchange.c app.c debug_leds.c temperature_monitor.c drv_i2c1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/debug.o ${OBJECTDIR}/drv_rtc.o ${OBJECTDIR}/dar_comms.o ${OBJECTDIR}/i2c_bit_bang.o ${OBJECTDIR}/power_switch_interrupt.o ${OBJECTDIR}/drv_STTS75.o ${OBJECTDIR}/drv_LIS2DS12.o ${OBJECTDIR}/battery_capacity.o ${OBJECTDIR}/message_exchange.o ${OBJECTDIR}/app.o ${OBJECTDIR}/debug_leds.o ${OBJECTDIR}/temperature_monitor.o ${OBJECTDIR}/drv_i2c1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/adc1.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/uart2.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/debug.o.d ${OBJECTDIR}/drv_rtc.o.d ${OBJECTDIR}/dar_comms.o.d ${OBJECTDIR}/i2c_bit_bang.o.d ${OBJECTDIR}/power_switch_interrupt.o.d ${OBJECTDIR}/drv_STTS75.o.d ${OBJECTDIR}/drv_LIS2DS12.o.d ${OBJECTDIR}/battery_capacity.o.d ${OBJECTDIR}/message_exchange.o.d ${OBJECTDIR}/app.o.d ${OBJECTDIR}/debug_leds.o.d ${OBJECTDIR}/temperature_monitor.o.d ${OBJECTDIR}/drv_i2c1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/debug.o ${OBJECTDIR}/drv_rtc.o ${OBJECTDIR}/dar_comms.o ${OBJECTDIR}/i2c_bit_bang.o ${OBJECTDIR}/power_switch_interrupt.o ${OBJECTDIR}/drv_STTS75.o ${OBJECTDIR}/drv_LIS2DS12.o ${OBJECTDIR}/battery_capacity.o ${OBJECTDIR}/message_exchange.o ${OBJECTDIR}/app.o ${OBJECTDIR}/debug_leds.o ${OBJECTDIR}/temperature_monitor.o ${OBJECTDIR}/drv_i2c1.o

# Source Files
SOURCEFILES=mcc_generated_files/clock.c mcc_generated_files/traps.c mcc_generated_files/pin_manager.c mcc_generated_files/system.c mcc_generated_files/mcc.c mcc_generated_files/adc1.c mcc_generated_files/interrupt_manager.c mcc_generated_files/uart2.c mcc_generated_files/uart1.c mcc_generated_files/tmr1.c main.c debug.c drv_rtc.c dar_comms.c i2c_bit_bang.c power_switch_interrupt.c drv_STTS75.c drv_LIS2DS12.c battery_capacity.c message_exchange.c app.c debug_leds.c temperature_monitor.c drv_i2c1.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA702
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA702.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/ab4f699e44beced815769ec662df0bf3092bd385.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/368efc1422cd7f7dca0666a4c5b17fcc4d4be08.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/ae3590d00077d07005deecd901b242f32d6c8fca.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/125fadda58eef54a6acda3fee2283488fdce9d76.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/9fc314391d340fb69faa9418dec02423ad1451fb.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/28f5603fee1a11393407815ef61b4c02cdf9e403.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/2a189bf37a40f10e1f668a9bef72a5b95c760ba1.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/faa2602dbc0e5456f70bb57ca0631b9bfd9e6881.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/d831c9a43f17a89f1512c39d9eed1c9199f67a34.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/c7d694dce136fbce04d90b5e6be1d53e885b5c7.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/168cebeae33a255f071514ccb1c6f694910eed3a.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debug.o: debug.c  .generated_files/4d6c060cb886a04bb788c30412d3f57ac190cd49.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug.c  -o ${OBJECTDIR}/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_rtc.o: drv_rtc.c  .generated_files/4bc7cc99cea26c9701d03d0554c958ad05c3f880.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_rtc.o.d 
	@${RM} ${OBJECTDIR}/drv_rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_rtc.c  -o ${OBJECTDIR}/drv_rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dar_comms.o: dar_comms.c  .generated_files/7d4f2347549f6f574953ec2f0e1bf5938dd340b9.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dar_comms.o.d 
	@${RM} ${OBJECTDIR}/dar_comms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dar_comms.c  -o ${OBJECTDIR}/dar_comms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dar_comms.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c_bit_bang.o: i2c_bit_bang.c  .generated_files/76539b0fb5826b11e7745aa8b6f05d02e4dfaad0.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c_bit_bang.o.d 
	@${RM} ${OBJECTDIR}/i2c_bit_bang.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c_bit_bang.c  -o ${OBJECTDIR}/i2c_bit_bang.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c_bit_bang.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/power_switch_interrupt.o: power_switch_interrupt.c  .generated_files/599cb5d17ec232fcbfc3bfdba93cdda9fe3cb159.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/power_switch_interrupt.o.d 
	@${RM} ${OBJECTDIR}/power_switch_interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  power_switch_interrupt.c  -o ${OBJECTDIR}/power_switch_interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/power_switch_interrupt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_STTS75.o: drv_STTS75.c  .generated_files/83c4d939796fa4e05253ca289f6c0baa80ce6dc7.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_STTS75.o.d 
	@${RM} ${OBJECTDIR}/drv_STTS75.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_STTS75.c  -o ${OBJECTDIR}/drv_STTS75.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_STTS75.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_LIS2DS12.o: drv_LIS2DS12.c  .generated_files/e1b3450d1f21a4ae76695669140ab7ff2226bc37.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_LIS2DS12.o.d 
	@${RM} ${OBJECTDIR}/drv_LIS2DS12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_LIS2DS12.c  -o ${OBJECTDIR}/drv_LIS2DS12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_LIS2DS12.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/battery_capacity.o: battery_capacity.c  .generated_files/7bf0a770c0c221038d92cf67d907fd5bed513465.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/battery_capacity.o.d 
	@${RM} ${OBJECTDIR}/battery_capacity.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  battery_capacity.c  -o ${OBJECTDIR}/battery_capacity.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/battery_capacity.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/message_exchange.o: message_exchange.c  .generated_files/b2ec8c84a52e87903ff8111352b762cb0dfe3787.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/message_exchange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  message_exchange.c  -o ${OBJECTDIR}/message_exchange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/message_exchange.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app.o: app.c  .generated_files/751a49ad2daa5b34addc46856dcf0915944023c1.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app.o.d 
	@${RM} ${OBJECTDIR}/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app.c  -o ${OBJECTDIR}/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debug_leds.o: debug_leds.c  .generated_files/135a0c5884dd294bb0e62c0e1d9e03c0f22cfbf3.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug_leds.o.d 
	@${RM} ${OBJECTDIR}/debug_leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug_leds.c  -o ${OBJECTDIR}/debug_leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug_leds.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/temperature_monitor.o: temperature_monitor.c  .generated_files/351abac4a4d875562a427cbb5ccb89f3734e4c28.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/temperature_monitor.o.d 
	@${RM} ${OBJECTDIR}/temperature_monitor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  temperature_monitor.c  -o ${OBJECTDIR}/temperature_monitor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/temperature_monitor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_i2c1.o: drv_i2c1.c  .generated_files/7970791e04944a09546b80c19b59124f7bf49777.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_i2c1.o.d 
	@${RM} ${OBJECTDIR}/drv_i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_i2c1.c  -o ${OBJECTDIR}/drv_i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_i2c1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/16ef7aed195a5e800603467ba37132646c5639f1.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/451a49f698bb892afea4a186bcae029c5b0aa824.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/aa95be790b2a3d5af8b9be6e1fa1f5a592e6ae39.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/4765a9817a9862397a8469900abf5806a9b0d6fa.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/d21f8076e76d6ba934e59d7bf1bf8ac186f37cc5.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/f1a9933077a3ba50cb6c29e01f83378ed8572612.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/8c486add5dd8fae391b58dd20e44e2a1eb99ab04.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/52352e4890d1a99238455e18669152758d5dc6fe.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/58a16fbe9ae6ed863447054345ffb0762db3817.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/52b7554e004bcce4cc3e001891c8e1c402c9ffc4.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/76423985c83d2b0f441972e84bd2cfdd19d8bff4.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debug.o: debug.c  .generated_files/bf340301d6accb02de00068aaecfeeef7af07da.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug.c  -o ${OBJECTDIR}/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_rtc.o: drv_rtc.c  .generated_files/70c3c90df4d9da402bcd585ddf84397d80ce32e5.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_rtc.o.d 
	@${RM} ${OBJECTDIR}/drv_rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_rtc.c  -o ${OBJECTDIR}/drv_rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_rtc.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dar_comms.o: dar_comms.c  .generated_files/29550c564dc5f5295e0707e5a7b616fb1661a88c.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dar_comms.o.d 
	@${RM} ${OBJECTDIR}/dar_comms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dar_comms.c  -o ${OBJECTDIR}/dar_comms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dar_comms.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c_bit_bang.o: i2c_bit_bang.c  .generated_files/974363de9f6431e19acf5f392c62b9f7e8ccc269.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c_bit_bang.o.d 
	@${RM} ${OBJECTDIR}/i2c_bit_bang.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c_bit_bang.c  -o ${OBJECTDIR}/i2c_bit_bang.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c_bit_bang.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/power_switch_interrupt.o: power_switch_interrupt.c  .generated_files/ff4765d2e75a592b467926282d0f4287384c632e.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/power_switch_interrupt.o.d 
	@${RM} ${OBJECTDIR}/power_switch_interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  power_switch_interrupt.c  -o ${OBJECTDIR}/power_switch_interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/power_switch_interrupt.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_STTS75.o: drv_STTS75.c  .generated_files/3545052d46870fa071f0d7010b75f40dc45ace34.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_STTS75.o.d 
	@${RM} ${OBJECTDIR}/drv_STTS75.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_STTS75.c  -o ${OBJECTDIR}/drv_STTS75.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_STTS75.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_LIS2DS12.o: drv_LIS2DS12.c  .generated_files/26e5bdf1ab567080479493c3115671adb5610ed9.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_LIS2DS12.o.d 
	@${RM} ${OBJECTDIR}/drv_LIS2DS12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_LIS2DS12.c  -o ${OBJECTDIR}/drv_LIS2DS12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_LIS2DS12.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/battery_capacity.o: battery_capacity.c  .generated_files/de5cc9ef8494a05447888984bf3d2bfea14dc360.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/battery_capacity.o.d 
	@${RM} ${OBJECTDIR}/battery_capacity.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  battery_capacity.c  -o ${OBJECTDIR}/battery_capacity.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/battery_capacity.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/message_exchange.o: message_exchange.c  .generated_files/46ddd308c7c6989a88a76d9b3de51bab73034a3f.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/message_exchange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  message_exchange.c  -o ${OBJECTDIR}/message_exchange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/message_exchange.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app.o: app.c  .generated_files/5b19fbb7f17ee69d019bee219f2aeb7c4494112b.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app.o.d 
	@${RM} ${OBJECTDIR}/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app.c  -o ${OBJECTDIR}/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debug_leds.o: debug_leds.c  .generated_files/7378ed62f361c14b86dad68701ff04297edae512.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug_leds.o.d 
	@${RM} ${OBJECTDIR}/debug_leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug_leds.c  -o ${OBJECTDIR}/debug_leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug_leds.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/temperature_monitor.o: temperature_monitor.c  .generated_files/55414c9087b96cc0aedb28d8d97098cb068fb254.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/temperature_monitor.o.d 
	@${RM} ${OBJECTDIR}/temperature_monitor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  temperature_monitor.c  -o ${OBJECTDIR}/temperature_monitor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/temperature_monitor.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/drv_i2c1.o: drv_i2c1.c  .generated_files/6adaae7ec1dd27d5c6bbd4ecd249b87f96f4fb6d.flag .generated_files/74709fa1d19e35bc709bb7e9e4fe6fe1caa6a4d6.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/drv_i2c1.o.d 
	@${RM} ${OBJECTDIR}/drv_i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  drv_i2c1.c  -o ${OBJECTDIR}/drv_i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/drv_i2c1.o.d"      -mno-eds-warn  -g -omf=elf -mcodecov=near -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -O3 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD4=1,$(MP_LINKER_FILE_OPTION),--heap=512,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=512,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Environment-Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default
