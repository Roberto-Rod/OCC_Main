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
ifeq "$(wildcard nbproject/Makefile-local-pic32mz2048efh100.mk)" "nbproject/Makefile-local-pic32mz2048efh100.mk"
include nbproject/Makefile-local-pic32mz2048efh100.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mz2048efh100
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/pic32mz2048efh100/driver/usart/src/drv_usart.c ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs.c ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs_device.c ../src/config/pic32mz2048efh100/peripheral/clk/plib_clk.c ../src/config/pic32mz2048efh100/peripheral/evic/plib_evic.c ../src/config/pic32mz2048efh100/peripheral/gpio/plib_gpio.c ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart1.c ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart3.c ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart2.c ../src/config/pic32mz2048efh100/stdio/xc32_monitor.c ../src/config/pic32mz2048efh100/system/dma/sys_dma.c ../src/config/pic32mz2048efh100/system/int/src/sys_int.c ../src/config/pic32mz2048efh100/usb/src/usb_device.c ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc.c ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc_acm.c ../src/config/pic32mz2048efh100/initialization.c ../src/config/pic32mz2048efh100/usb_device_init_data.c ../src/config/pic32mz2048efh100/tasks.c ../src/config/pic32mz2048efh100/interrupts.c ../src/config/pic32mz2048efh100/exceptions.c ../src/main.c ../src/app.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1122388781/drv_usart.o ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o ${OBJECTDIR}/_ext/1079760849/plib_clk.o ${OBJECTDIR}/_ext/887221278/plib_evic.o ${OBJECTDIR}/_ext/887275106/plib_gpio.o ${OBJECTDIR}/_ext/887678049/plib_uart1.o ${OBJECTDIR}/_ext/887678049/plib_uart3.o ${OBJECTDIR}/_ext/887678049/plib_uart2.o ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o ${OBJECTDIR}/_ext/865233096/sys_dma.o ${OBJECTDIR}/_ext/741742084/sys_int.o ${OBJECTDIR}/_ext/795361095/usb_device.o ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o ${OBJECTDIR}/_ext/1317182481/initialization.o ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o ${OBJECTDIR}/_ext/1317182481/tasks.o ${OBJECTDIR}/_ext/1317182481/interrupts.o ${OBJECTDIR}/_ext/1317182481/exceptions.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1122388781/drv_usart.o.d ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o.d ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o.d ${OBJECTDIR}/_ext/1079760849/plib_clk.o.d ${OBJECTDIR}/_ext/887221278/plib_evic.o.d ${OBJECTDIR}/_ext/887275106/plib_gpio.o.d ${OBJECTDIR}/_ext/887678049/plib_uart1.o.d ${OBJECTDIR}/_ext/887678049/plib_uart3.o.d ${OBJECTDIR}/_ext/887678049/plib_uart2.o.d ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o.d ${OBJECTDIR}/_ext/865233096/sys_dma.o.d ${OBJECTDIR}/_ext/741742084/sys_int.o.d ${OBJECTDIR}/_ext/795361095/usb_device.o.d ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o.d ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o.d ${OBJECTDIR}/_ext/1317182481/initialization.o.d ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o.d ${OBJECTDIR}/_ext/1317182481/tasks.o.d ${OBJECTDIR}/_ext/1317182481/interrupts.o.d ${OBJECTDIR}/_ext/1317182481/exceptions.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1122388781/drv_usart.o ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o ${OBJECTDIR}/_ext/1079760849/plib_clk.o ${OBJECTDIR}/_ext/887221278/plib_evic.o ${OBJECTDIR}/_ext/887275106/plib_gpio.o ${OBJECTDIR}/_ext/887678049/plib_uart1.o ${OBJECTDIR}/_ext/887678049/plib_uart3.o ${OBJECTDIR}/_ext/887678049/plib_uart2.o ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o ${OBJECTDIR}/_ext/865233096/sys_dma.o ${OBJECTDIR}/_ext/741742084/sys_int.o ${OBJECTDIR}/_ext/795361095/usb_device.o ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o ${OBJECTDIR}/_ext/1317182481/initialization.o ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o ${OBJECTDIR}/_ext/1317182481/tasks.o ${OBJECTDIR}/_ext/1317182481/interrupts.o ${OBJECTDIR}/_ext/1317182481/exceptions.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o

# Source Files
SOURCEFILES=../src/config/pic32mz2048efh100/driver/usart/src/drv_usart.c ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs.c ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs_device.c ../src/config/pic32mz2048efh100/peripheral/clk/plib_clk.c ../src/config/pic32mz2048efh100/peripheral/evic/plib_evic.c ../src/config/pic32mz2048efh100/peripheral/gpio/plib_gpio.c ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart1.c ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart3.c ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart2.c ../src/config/pic32mz2048efh100/stdio/xc32_monitor.c ../src/config/pic32mz2048efh100/system/dma/sys_dma.c ../src/config/pic32mz2048efh100/system/int/src/sys_int.c ../src/config/pic32mz2048efh100/usb/src/usb_device.c ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc.c ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc_acm.c ../src/config/pic32mz2048efh100/initialization.c ../src/config/pic32mz2048efh100/usb_device_init_data.c ../src/config/pic32mz2048efh100/tasks.c ../src/config/pic32mz2048efh100/interrupts.c ../src/config/pic32mz2048efh100/exceptions.c ../src/main.c ../src/app.c



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
	${MAKE}  -f nbproject/Makefile-pic32mz2048efh100.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048EFH100
MP_LINKER_FILE_OPTION=,--script="..\src\config\pic32mz2048efh100\app_mz.ld"
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
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1122388781/drv_usart.o: ../src/config/pic32mz2048efh100/driver/usart/src/drv_usart.c  .generated_files/97a482549b6e3a9fd8be1b7230f6e7fc76da2a87.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1122388781" 
	@${RM} ${OBJECTDIR}/_ext/1122388781/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1122388781/drv_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1122388781/drv_usart.o.d" -o ${OBJECTDIR}/_ext/1122388781/drv_usart.o ../src/config/pic32mz2048efh100/driver/usart/src/drv_usart.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1155812590/drv_usbhs.o: ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs.c  .generated_files/5a35534c37cc8e9352fefa0037780ceb6c791fc1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1155812590" 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155812590/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o: ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs_device.c  .generated_files/4e6677c90d2045110b4acfa9f58456691ead72a9.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1155812590" 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs_device.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1079760849/plib_clk.o: ../src/config/pic32mz2048efh100/peripheral/clk/plib_clk.c  .generated_files/5ed1737e409312f3d65a826eb0c824bfdcc65fd3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1079760849" 
	@${RM} ${OBJECTDIR}/_ext/1079760849/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1079760849/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1079760849/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1079760849/plib_clk.o ../src/config/pic32mz2048efh100/peripheral/clk/plib_clk.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887221278/plib_evic.o: ../src/config/pic32mz2048efh100/peripheral/evic/plib_evic.c  .generated_files/78fa1aab6bb8f644eab17d8c50ab0dc1671c7ae.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887221278" 
	@${RM} ${OBJECTDIR}/_ext/887221278/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/887221278/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887221278/plib_evic.o.d" -o ${OBJECTDIR}/_ext/887221278/plib_evic.o ../src/config/pic32mz2048efh100/peripheral/evic/plib_evic.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887275106/plib_gpio.o: ../src/config/pic32mz2048efh100/peripheral/gpio/plib_gpio.c  .generated_files/b55610624ad326bfac296643b09405a292922c97.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887275106" 
	@${RM} ${OBJECTDIR}/_ext/887275106/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/887275106/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887275106/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/887275106/plib_gpio.o ../src/config/pic32mz2048efh100/peripheral/gpio/plib_gpio.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887678049/plib_uart1.o: ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart1.c  .generated_files/30f50146603ffc9bab16fd5242d83907b2c996c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887678049" 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887678049/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/887678049/plib_uart1.o ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart1.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887678049/plib_uart3.o: ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart3.c  .generated_files/328b711cbb7b546a4c07dfdfd2174619d95ae34d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887678049" 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887678049/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/887678049/plib_uart3.o ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart3.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887678049/plib_uart2.o: ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart2.c  .generated_files/dd5bf3c72d908781bdef5dca23c9687c9725ece4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887678049" 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887678049/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/887678049/plib_uart2.o ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart2.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1571354519/xc32_monitor.o: ../src/config/pic32mz2048efh100/stdio/xc32_monitor.c  .generated_files/441014f65805d4d3d7b7c57a1ca722de4e1e0e23.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1571354519" 
	@${RM} ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1571354519/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o ../src/config/pic32mz2048efh100/stdio/xc32_monitor.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/865233096/sys_dma.o: ../src/config/pic32mz2048efh100/system/dma/sys_dma.c  .generated_files/836fb21eb47cfc0f8dd72764ae6ec65be92d1a7c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/865233096" 
	@${RM} ${OBJECTDIR}/_ext/865233096/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/865233096/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/865233096/sys_dma.o.d" -o ${OBJECTDIR}/_ext/865233096/sys_dma.o ../src/config/pic32mz2048efh100/system/dma/sys_dma.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/741742084/sys_int.o: ../src/config/pic32mz2048efh100/system/int/src/sys_int.c  .generated_files/dad5bc18a0338849be23d2eae63fb473d6430b7a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/741742084" 
	@${RM} ${OBJECTDIR}/_ext/741742084/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/741742084/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/741742084/sys_int.o.d" -o ${OBJECTDIR}/_ext/741742084/sys_int.o ../src/config/pic32mz2048efh100/system/int/src/sys_int.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/795361095/usb_device.o: ../src/config/pic32mz2048efh100/usb/src/usb_device.c  .generated_files/211d7f8358dedc7a987f087548199c758ee241ee.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/795361095" 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/795361095/usb_device.o.d" -o ${OBJECTDIR}/_ext/795361095/usb_device.o ../src/config/pic32mz2048efh100/usb/src/usb_device.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/795361095/usb_device_cdc.o: ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc.c  .generated_files/a3df046ea08df3ba25f2b8b9be2576c9ff4e9d54.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/795361095" 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/795361095/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o: ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc_acm.c  .generated_files/c346435e7cac191b47e5a77c9a9ba327147872fd.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/795361095" 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc_acm.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/initialization.o: ../src/config/pic32mz2048efh100/initialization.c  .generated_files/e48443ea321cd4ba1f473fe479a85c29a33502b1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/initialization.o.d" -o ${OBJECTDIR}/_ext/1317182481/initialization.o ../src/config/pic32mz2048efh100/initialization.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o: ../src/config/pic32mz2048efh100/usb_device_init_data.c  .generated_files/ba0eabc82ecc225cf7c74b12913db4bc5029341b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o ../src/config/pic32mz2048efh100/usb_device_init_data.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/tasks.o: ../src/config/pic32mz2048efh100/tasks.c  .generated_files/c8bad27038dea176f33365791ce4dc00ba105ac7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/tasks.o.d" -o ${OBJECTDIR}/_ext/1317182481/tasks.o ../src/config/pic32mz2048efh100/tasks.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/interrupts.o: ../src/config/pic32mz2048efh100/interrupts.c  .generated_files/16e4cd76f567517c1c7196aa93428734fb973b20.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/interrupts.o.d" -o ${OBJECTDIR}/_ext/1317182481/interrupts.o ../src/config/pic32mz2048efh100/interrupts.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/exceptions.o: ../src/config/pic32mz2048efh100/exceptions.c  .generated_files/2a4908787cab4928328a99587f4550d868b5f6d8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/exceptions.o.d" -o ${OBJECTDIR}/_ext/1317182481/exceptions.o ../src/config/pic32mz2048efh100/exceptions.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/6e7a759d49b982a1535fbf335c282d4a2ee183aa.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/c9b206125e2e4416b147e086da8e118394471bbc.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1122388781/drv_usart.o: ../src/config/pic32mz2048efh100/driver/usart/src/drv_usart.c  .generated_files/7cea632e451b9d336c33decbeed64461a61b0840.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1122388781" 
	@${RM} ${OBJECTDIR}/_ext/1122388781/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1122388781/drv_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1122388781/drv_usart.o.d" -o ${OBJECTDIR}/_ext/1122388781/drv_usart.o ../src/config/pic32mz2048efh100/driver/usart/src/drv_usart.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1155812590/drv_usbhs.o: ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs.c  .generated_files/2764cd53fef122f6649ea513cd3ab79874c39b3b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1155812590" 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155812590/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/1155812590/drv_usbhs.o ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o: ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs_device.c  .generated_files/132b453d38d819d12ce1d78a7316171852982da6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1155812590" 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/1155812590/drv_usbhs_device.o ../src/config/pic32mz2048efh100/driver/usb/usbhs/src/drv_usbhs_device.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1079760849/plib_clk.o: ../src/config/pic32mz2048efh100/peripheral/clk/plib_clk.c  .generated_files/40964244306a3f28ad539bcbb046f52352c71e40.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1079760849" 
	@${RM} ${OBJECTDIR}/_ext/1079760849/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1079760849/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1079760849/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1079760849/plib_clk.o ../src/config/pic32mz2048efh100/peripheral/clk/plib_clk.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887221278/plib_evic.o: ../src/config/pic32mz2048efh100/peripheral/evic/plib_evic.c  .generated_files/d11eaf2c8c7729882ced449d58114f0dca048927.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887221278" 
	@${RM} ${OBJECTDIR}/_ext/887221278/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/887221278/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887221278/plib_evic.o.d" -o ${OBJECTDIR}/_ext/887221278/plib_evic.o ../src/config/pic32mz2048efh100/peripheral/evic/plib_evic.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887275106/plib_gpio.o: ../src/config/pic32mz2048efh100/peripheral/gpio/plib_gpio.c  .generated_files/c7a294acafa8cc6fbcc2d5c45359821734363a64.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887275106" 
	@${RM} ${OBJECTDIR}/_ext/887275106/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/887275106/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887275106/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/887275106/plib_gpio.o ../src/config/pic32mz2048efh100/peripheral/gpio/plib_gpio.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887678049/plib_uart1.o: ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart1.c  .generated_files/39f52e5b875a20593a53d90f742d5100bef6951.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887678049" 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887678049/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/887678049/plib_uart1.o ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart1.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887678049/plib_uart3.o: ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart3.c  .generated_files/af96e376581d382dacb610efb5c6532e793cf983.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887678049" 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887678049/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/887678049/plib_uart3.o ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart3.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/887678049/plib_uart2.o: ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart2.c  .generated_files/532f273a8640a649798e0f11ec8c9b450f51a454.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/887678049" 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/887678049/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/887678049/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/887678049/plib_uart2.o ../src/config/pic32mz2048efh100/peripheral/uart/plib_uart2.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1571354519/xc32_monitor.o: ../src/config/pic32mz2048efh100/stdio/xc32_monitor.c  .generated_files/c98c59c936f54de77afcd88e9380758082c51003.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1571354519" 
	@${RM} ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1571354519/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/1571354519/xc32_monitor.o ../src/config/pic32mz2048efh100/stdio/xc32_monitor.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/865233096/sys_dma.o: ../src/config/pic32mz2048efh100/system/dma/sys_dma.c  .generated_files/5da31ff4caef26c4da4069dfc479f072785655e1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/865233096" 
	@${RM} ${OBJECTDIR}/_ext/865233096/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/865233096/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/865233096/sys_dma.o.d" -o ${OBJECTDIR}/_ext/865233096/sys_dma.o ../src/config/pic32mz2048efh100/system/dma/sys_dma.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/741742084/sys_int.o: ../src/config/pic32mz2048efh100/system/int/src/sys_int.c  .generated_files/c6cc7566f8e786aa9f49e1eee5b2269a0c813aa6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/741742084" 
	@${RM} ${OBJECTDIR}/_ext/741742084/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/741742084/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/741742084/sys_int.o.d" -o ${OBJECTDIR}/_ext/741742084/sys_int.o ../src/config/pic32mz2048efh100/system/int/src/sys_int.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/795361095/usb_device.o: ../src/config/pic32mz2048efh100/usb/src/usb_device.c  .generated_files/9d7b411ba1dc81dda0268322135b9fa8a8e511a5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/795361095" 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/795361095/usb_device.o.d" -o ${OBJECTDIR}/_ext/795361095/usb_device.o ../src/config/pic32mz2048efh100/usb/src/usb_device.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/795361095/usb_device_cdc.o: ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc.c  .generated_files/638aa0b249b78ae392dab6e4fbf360f438e8a8a3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/795361095" 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/795361095/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/795361095/usb_device_cdc.o ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o: ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc_acm.c  .generated_files/2945fe947bcab67ae9534ea617aeb1c3b94da37c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/795361095" 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/795361095/usb_device_cdc_acm.o ../src/config/pic32mz2048efh100/usb/src/usb_device_cdc_acm.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/initialization.o: ../src/config/pic32mz2048efh100/initialization.c  .generated_files/6446cc0df6af450a9b8c35fc36c487c620b247a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/initialization.o.d" -o ${OBJECTDIR}/_ext/1317182481/initialization.o ../src/config/pic32mz2048efh100/initialization.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o: ../src/config/pic32mz2048efh100/usb_device_init_data.c  .generated_files/e970ac81510fa46b99b4aca8086156b443e7906e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1317182481/usb_device_init_data.o ../src/config/pic32mz2048efh100/usb_device_init_data.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/tasks.o: ../src/config/pic32mz2048efh100/tasks.c  .generated_files/8608321b147fd6bc3621b5a89bad3ead2a59f16f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/tasks.o.d" -o ${OBJECTDIR}/_ext/1317182481/tasks.o ../src/config/pic32mz2048efh100/tasks.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/interrupts.o: ../src/config/pic32mz2048efh100/interrupts.c  .generated_files/93b607e027c1a537cd543ccf1af60dcfac64eff7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/interrupts.o.d" -o ${OBJECTDIR}/_ext/1317182481/interrupts.o ../src/config/pic32mz2048efh100/interrupts.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317182481/exceptions.o: ../src/config/pic32mz2048efh100/exceptions.c  .generated_files/9e13dbef5234488955316954241d4f22f35d106f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317182481" 
	@${RM} ${OBJECTDIR}/_ext/1317182481/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317182481/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317182481/exceptions.o.d" -o ${OBJECTDIR}/_ext/1317182481/exceptions.o ../src/config/pic32mz2048efh100/exceptions.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/32adc3699f99a76c7bf9db595716cf59fd5fe7b9.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/78a6f26edcdd5a55823d8460b2bcfb6c827b65b6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/pic32mz2048efh100" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wno-deprecated-declarations -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/pic32mz2048efh100/app_mz.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/pic32mz2048efh100/app_mz.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32mz2048efh100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIC32mz2048efh100.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mz2048efh100
	${RM} -r dist/pic32mz2048efh100

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
