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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/boot/hardware_interrupt_table.S mcc_generated_files/boot/interrupts.S mcc_generated_files/boot/memory_partition.S mcc_generated_files/boot/remapped_reset.S mcc_generated_files/boot/user_interrupt_table.S mcc_generated_files/memory/flash.s mcc_generated_files/reset.c mcc_generated_files/system.c mcc_generated_files/clock.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/clc3.c mcc_generated_files/clc2.c mcc_generated_files/clc1.c mcc_generated_files/traps.c mcc_generated_files/dma.c mcc_generated_files/sccp2_tmr.c mcc_generated_files/delay.c mcc_generated_files/ext_int.c mcc_generated_files/tmr1.c mcc_generated_files/cmp1.c mcc_generated_files/sccp7_tmr.c mcc_generated_files/clc4.c mcc_generated_files/uart1.c mcc_generated_files/uart2.c main.c NVM_Driver.c debug.c encoder_drv.c motor_drv.c LRS_tuning.c pdab_comms.c message_exchange.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/memory/flash.o ${OBJECTDIR}/mcc_generated_files/reset.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/clc3.o ${OBJECTDIR}/mcc_generated_files/clc2.o ${OBJECTDIR}/mcc_generated_files/clc1.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/dma.o ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o ${OBJECTDIR}/mcc_generated_files/delay.o ${OBJECTDIR}/mcc_generated_files/ext_int.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/cmp1.o ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o ${OBJECTDIR}/mcc_generated_files/clc4.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/NVM_Driver.o ${OBJECTDIR}/debug.o ${OBJECTDIR}/encoder_drv.o ${OBJECTDIR}/motor_drv.o ${OBJECTDIR}/LRS_tuning.o ${OBJECTDIR}/pdab_comms.o ${OBJECTDIR}/message_exchange.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o.d ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d ${OBJECTDIR}/mcc_generated_files/reset.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/clc3.o.d ${OBJECTDIR}/mcc_generated_files/clc2.o.d ${OBJECTDIR}/mcc_generated_files/clc1.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/mcc_generated_files/dma.o.d ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o.d ${OBJECTDIR}/mcc_generated_files/delay.o.d ${OBJECTDIR}/mcc_generated_files/ext_int.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/cmp1.o.d ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o.d ${OBJECTDIR}/mcc_generated_files/clc4.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/uart2.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/NVM_Driver.o.d ${OBJECTDIR}/debug.o.d ${OBJECTDIR}/encoder_drv.o.d ${OBJECTDIR}/motor_drv.o.d ${OBJECTDIR}/LRS_tuning.o.d ${OBJECTDIR}/pdab_comms.o.d ${OBJECTDIR}/message_exchange.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/memory/flash.o ${OBJECTDIR}/mcc_generated_files/reset.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/clc3.o ${OBJECTDIR}/mcc_generated_files/clc2.o ${OBJECTDIR}/mcc_generated_files/clc1.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/dma.o ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o ${OBJECTDIR}/mcc_generated_files/delay.o ${OBJECTDIR}/mcc_generated_files/ext_int.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/cmp1.o ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o ${OBJECTDIR}/mcc_generated_files/clc4.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/main.o ${OBJECTDIR}/NVM_Driver.o ${OBJECTDIR}/debug.o ${OBJECTDIR}/encoder_drv.o ${OBJECTDIR}/motor_drv.o ${OBJECTDIR}/LRS_tuning.o ${OBJECTDIR}/pdab_comms.o ${OBJECTDIR}/message_exchange.o

# Source Files
SOURCEFILES=mcc_generated_files/boot/hardware_interrupt_table.S mcc_generated_files/boot/interrupts.S mcc_generated_files/boot/memory_partition.S mcc_generated_files/boot/remapped_reset.S mcc_generated_files/boot/user_interrupt_table.S mcc_generated_files/memory/flash.s mcc_generated_files/reset.c mcc_generated_files/system.c mcc_generated_files/clock.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/clc3.c mcc_generated_files/clc2.c mcc_generated_files/clc1.c mcc_generated_files/traps.c mcc_generated_files/dma.c mcc_generated_files/sccp2_tmr.c mcc_generated_files/delay.c mcc_generated_files/ext_int.c mcc_generated_files/tmr1.c mcc_generated_files/cmp1.c mcc_generated_files/sccp7_tmr.c mcc_generated_files/clc4.c mcc_generated_files/uart1.c mcc_generated_files/uart2.c main.c NVM_Driver.c debug.c encoder_drv.c motor_drv.c LRS_tuning.c pdab_comms.c message_exchange.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33CK128MP203
MP_LINKER_FILE_OPTION=,--script=p33CK128MP203.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/reset.o: mcc_generated_files/reset.c  .generated_files/6fc15f33e6d5bb733802a7fd2f49008c72ee3ac1.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/reset.c  -o ${OBJECTDIR}/mcc_generated_files/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/reset.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/709eae56dfa470076907d42070bd42f4be998ac7.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/c4aa318a7818a93e58acd2b71464485660e2f649.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/6fea3197c120db5324bb9dd639d8dcf9d51cd273.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/cde28c21c372bbf435f57b8007fd4bb0ae55cc89.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/fcee083a02850dd57322554b04840ecb3c0daf00.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc3.o: mcc_generated_files/clc3.c  .generated_files/87ce94517f0b1cee4eed5507e3bd291198bd7fa5.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc3.c  -o ${OBJECTDIR}/mcc_generated_files/clc3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc2.o: mcc_generated_files/clc2.c  .generated_files/4ac7438884b4c80cb0f6825ada734d97e57934e0.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc2.c  -o ${OBJECTDIR}/mcc_generated_files/clc2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc1.o: mcc_generated_files/clc1.c  .generated_files/1ab5319878cbccba42b004190d6fbcb0432beaf6.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc1.c  -o ${OBJECTDIR}/mcc_generated_files/clc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/43dab321382f099415cae0add1a874ff0249221a.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/dma.o: mcc_generated_files/dma.c  .generated_files/539962b64aabea5c0c9df02007d7d6a41cc67078.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/dma.c  -o ${OBJECTDIR}/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o: mcc_generated_files/sccp2_tmr.c  .generated_files/d1da9b7427831fcde7dca35ee02342f94c869cce.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp2_tmr.c  -o ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/delay.o: mcc_generated_files/delay.c  .generated_files/c6e3672b5f75be84bb41a38b5a116b93224bbde7.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/delay.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/delay.c  -o ${OBJECTDIR}/mcc_generated_files/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/ext_int.o: mcc_generated_files/ext_int.c  .generated_files/3d9368be99883cb590d020788749985b28d9511a.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/ext_int.c  -o ${OBJECTDIR}/mcc_generated_files/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/ext_int.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/d4f9528779b5d37d8c1f51b19faa33edd2846997.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/cmp1.o: mcc_generated_files/cmp1.c  .generated_files/cde834e130380fa2661f2b5882fe64850f4ce50e.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/cmp1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/cmp1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/cmp1.c  -o ${OBJECTDIR}/mcc_generated_files/cmp1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/cmp1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o: mcc_generated_files/sccp7_tmr.c  .generated_files/4aee5bb354a8a0206e21bb1cc32923931d949033.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp7_tmr.c  -o ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc4.o: mcc_generated_files/clc4.c  .generated_files/bb7c54dac3dc5374bfb34506747e4ed1978acd28.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc4.c  -o ${OBJECTDIR}/mcc_generated_files/clc4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc4.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/b57b7aef90455f589f86aa19724c0cac7333e592.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/47522e756a6f1a82f4974146f8386aee92579aac.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/87594c8d38d16bbefb1adc6e5dfccb5e4e90e7cb.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/NVM_Driver.o: NVM_Driver.c  .generated_files/f13855b4541a5c81c2539483ed8a80be9e152a3e.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NVM_Driver.o.d 
	@${RM} ${OBJECTDIR}/NVM_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  NVM_Driver.c  -o ${OBJECTDIR}/NVM_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/NVM_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debug.o: debug.c  .generated_files/8f3195502f9d97c955ac7a77776d5e32ad0f318c.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug.c  -o ${OBJECTDIR}/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/encoder_drv.o: encoder_drv.c  .generated_files/ef7d96bc68c590ebd46439ef0efe2a8541be918d.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder_drv.o.d 
	@${RM} ${OBJECTDIR}/encoder_drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  encoder_drv.c  -o ${OBJECTDIR}/encoder_drv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/encoder_drv.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/motor_drv.o: motor_drv.c  .generated_files/9948e62f3eb17615163fb47460ba2179a2557dc8.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor_drv.o.d 
	@${RM} ${OBJECTDIR}/motor_drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_drv.c  -o ${OBJECTDIR}/motor_drv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/motor_drv.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LRS_tuning.o: LRS_tuning.c  .generated_files/773d5cb4d756365902498830d66e6589884452e.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LRS_tuning.o.d 
	@${RM} ${OBJECTDIR}/LRS_tuning.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LRS_tuning.c  -o ${OBJECTDIR}/LRS_tuning.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LRS_tuning.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pdab_comms.o: pdab_comms.c  .generated_files/67d68911b8a78e6591ee9d75e5bf635030c6f5f0.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pdab_comms.o.d 
	@${RM} ${OBJECTDIR}/pdab_comms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pdab_comms.c  -o ${OBJECTDIR}/pdab_comms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pdab_comms.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/message_exchange.o: message_exchange.c  .generated_files/b0be3a7a758e2779d30e4f9ac72e39861a2cbe46.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/message_exchange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  message_exchange.c  -o ${OBJECTDIR}/message_exchange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/message_exchange.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/reset.o: mcc_generated_files/reset.c  .generated_files/c80b132d8f3e53f4521bdb86180978021e69dab7.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/reset.c  -o ${OBJECTDIR}/mcc_generated_files/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/reset.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/1198dc1ccf29cd87d57479c044810d503af5e6ed.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/483a430ccb305d94756a370bb96c38c4ffe912.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/db9d36868bc1a62a23ddf126b9d53c307a77821f.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/be8634de619fd6cc32e9170c772ca9c0a8e68bf0.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/163270f68bccc6bedf88edf834ea2a8b4d107889.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc3.o: mcc_generated_files/clc3.c  .generated_files/aa67d0159faf797c997bcd39705681c1ca423268.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc3.c  -o ${OBJECTDIR}/mcc_generated_files/clc3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc3.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc2.o: mcc_generated_files/clc2.c  .generated_files/9a7b3521ca602793e3a77b3e07887cb8d3989ee7.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc2.c  -o ${OBJECTDIR}/mcc_generated_files/clc2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc2.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc1.o: mcc_generated_files/clc1.c  .generated_files/bf76a2ef5649ec3a0fa56ba0459607807a2706b8.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc1.c  -o ${OBJECTDIR}/mcc_generated_files/clc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc1.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/fc39e3d86c1ef1b98170699ba76fc429e68669ae.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/dma.o: mcc_generated_files/dma.c  .generated_files/e270e9703d3e5ef9f1fbec24ffd836f3185324ef.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/dma.c  -o ${OBJECTDIR}/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/dma.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o: mcc_generated_files/sccp2_tmr.c  .generated_files/f1f74b014f6021b81dd665791431ae58235e76ce.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp2_tmr.c  -o ${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp2_tmr.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/delay.o: mcc_generated_files/delay.c  .generated_files/e28f05ff0954f169044a9fab81179d9dff50426b.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/delay.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/delay.c  -o ${OBJECTDIR}/mcc_generated_files/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/delay.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/ext_int.o: mcc_generated_files/ext_int.c  .generated_files/c356368ec12654f510327802aaa6429cab6c58e1.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/ext_int.c  -o ${OBJECTDIR}/mcc_generated_files/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/ext_int.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/afedc97765aaa4e6b3f526ed8b96ddfbc61e98c4.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/cmp1.o: mcc_generated_files/cmp1.c  .generated_files/793f90961b1aeefa3ca532b84c7429e8e66bf632.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/cmp1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/cmp1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/cmp1.c  -o ${OBJECTDIR}/mcc_generated_files/cmp1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/cmp1.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o: mcc_generated_files/sccp7_tmr.c  .generated_files/f3c291cf1929c97917596402fceabd3e35a539cb.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/sccp7_tmr.c  -o ${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp7_tmr.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clc4.o: mcc_generated_files/clc4.c  .generated_files/ff1fb36cabbbc9b5ff8369ab473ab312e24dd82.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc4.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clc4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clc4.c  -o ${OBJECTDIR}/mcc_generated_files/clc4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clc4.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  .generated_files/a08a92b1e1a214211243b480d849691c91f2e61b.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  .generated_files/17b8689a06a255eb3e3d1ac6861cf3394b599b0.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart2.c  -o ${OBJECTDIR}/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/c5c3eb9ad706547ca28ff1624ce8e79d1c341e2f.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/NVM_Driver.o: NVM_Driver.c  .generated_files/61d1b754dec2a531ff8c27d3f45ce71650ef3705.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/NVM_Driver.o.d 
	@${RM} ${OBJECTDIR}/NVM_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  NVM_Driver.c  -o ${OBJECTDIR}/NVM_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/NVM_Driver.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debug.o: debug.c  .generated_files/9de3e148ac63639681661a929ce9d7d3c6ccaa8f.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debug.c  -o ${OBJECTDIR}/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debug.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/encoder_drv.o: encoder_drv.c  .generated_files/afbfecb9d35c2e460688690292b9fe56a6324737.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder_drv.o.d 
	@${RM} ${OBJECTDIR}/encoder_drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  encoder_drv.c  -o ${OBJECTDIR}/encoder_drv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/encoder_drv.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/motor_drv.o: motor_drv.c  .generated_files/992ed342a2ef85f78867c55eb383a0436251cb61.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor_drv.o.d 
	@${RM} ${OBJECTDIR}/motor_drv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_drv.c  -o ${OBJECTDIR}/motor_drv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/motor_drv.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LRS_tuning.o: LRS_tuning.c  .generated_files/e8a42413fad4fbea582e4369c56062338d8612e8.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LRS_tuning.o.d 
	@${RM} ${OBJECTDIR}/LRS_tuning.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LRS_tuning.c  -o ${OBJECTDIR}/LRS_tuning.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LRS_tuning.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pdab_comms.o: pdab_comms.c  .generated_files/fdcd4bf12f4b0f807202cd5b5b97dc4b2a3e5b3f.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pdab_comms.o.d 
	@${RM} ${OBJECTDIR}/pdab_comms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pdab_comms.c  -o ${OBJECTDIR}/pdab_comms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pdab_comms.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/message_exchange.o: message_exchange.c  .generated_files/f5ba7dde950727cb27837f0f89961ff295bc428c.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/message_exchange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  message_exchange.c  -o ${OBJECTDIR}/message_exchange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/message_exchange.o.d"      -mno-eds-warn  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Os -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/memory/flash.o: mcc_generated_files/memory/flash.s  .generated_files/ad8e23925538d4e8ee85eb7752dd3491efe3be70.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/memory/flash.o: mcc_generated_files/memory/flash.s  .generated_files/5b3c500c9f0efcd016929538034733e738c7521.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o: mcc_generated_files/boot/hardware_interrupt_table.S  .generated_files/7dd5e3d94c3c9410b8b918999d6bc07b2979c64e.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/hardware_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/interrupts.o: mcc_generated_files/boot/interrupts.S  .generated_files/12ca0425800125fbfaf1e4688ba5cd83cc9ee855.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/interrupts.S  -o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o: mcc_generated_files/boot/memory_partition.S  .generated_files/61200d9d422ffab41c8a014299e7acbb6a4c2408.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/memory_partition.S  -o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o: mcc_generated_files/boot/remapped_reset.S  .generated_files/cda32b9105c14816e7c5e854a238b971a884d1fd.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/remapped_reset.S  -o ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o: mcc_generated_files/boot/user_interrupt_table.S  .generated_files/bf31c601f9289aadd5480bb2086a362d6e91ae5b.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/user_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o: mcc_generated_files/boot/hardware_interrupt_table.S  .generated_files/c88a6dca9558cf311835807707d8761ac8463b43.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/hardware_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d"  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/interrupts.o: mcc_generated_files/boot/interrupts.S  .generated_files/9b8c3dde4d240f6a7bc08a8ade3035ef5d0b2661.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/interrupts.S  -o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d"  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.asm.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o: mcc_generated_files/boot/memory_partition.S  .generated_files/8c3251ec8c47c9413bc52e60e7de2d7d57e88fb8.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/memory_partition.S  -o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d"  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.asm.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o: mcc_generated_files/boot/remapped_reset.S  .generated_files/3354a4e1d8958fa3985843d2676925b29ee3caa.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/remapped_reset.S  -o ${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o.d"  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/remapped_reset.o.asm.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o: mcc_generated_files/boot/user_interrupt_table.S  .generated_files/a7cb1e90a683f55420de5df0207c8da4c55f5097.flag .generated_files/e1aa3c1b6aca3e95c5f6375440c59d4c5e41b299.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/user_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d"  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -Wall -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD4=1,$(MP_LINKER_FILE_OPTION),--heap=512,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -fast-math -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wall -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=512,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/LSC_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default
