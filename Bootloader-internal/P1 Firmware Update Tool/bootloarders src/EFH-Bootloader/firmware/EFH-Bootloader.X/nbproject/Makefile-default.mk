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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/bootloader/datastream/datastream_usb_device_hid.c ../src/config/default/bootloader/bootloader.c ../src/config/default/bootloader/bootloader_nvm_interface.c ../src/config/default/driver/usb/usbhs/src/drv_usbhs.c ../src/config/default/driver/usb/usbhs/src/drv_usbhs_device.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/system/time/src/sys_time.c ../src/config/default/usb/src/usb_device_hid.c ../src/config/default/usb/src/usb_device.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/usb_device_init_data.c ../src/config/default/initialization.c ../src/config/default/tasks.c ../src/main.c ../src/app.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o ${OBJECTDIR}/_ext/1748409734/bootloader.o ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/101884895/sys_time.o ${OBJECTDIR}/_ext/308758920/usb_device_hid.o ${OBJECTDIR}/_ext/308758920/usb_device.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o.d ${OBJECTDIR}/_ext/1748409734/bootloader.o.d ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o.d ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o.d ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o.d ${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1881668453/sys_int.o.d ${OBJECTDIR}/_ext/101884895/sys_time.o.d ${OBJECTDIR}/_ext/308758920/usb_device_hid.o.d ${OBJECTDIR}/_ext/308758920/usb_device.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/tasks.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o ${OBJECTDIR}/_ext/1748409734/bootloader.o ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/101884895/sys_time.o ${OBJECTDIR}/_ext/308758920/usb_device_hid.o ${OBJECTDIR}/_ext/308758920/usb_device.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o

# Source Files
SOURCEFILES=../src/config/default/bootloader/datastream/datastream_usb_device_hid.c ../src/config/default/bootloader/bootloader.c ../src/config/default/bootloader/bootloader_nvm_interface.c ../src/config/default/driver/usb/usbhs/src/drv_usbhs.c ../src/config/default/driver/usb/usbhs/src/drv_usbhs_device.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/system/time/src/sys_time.c ../src/config/default/usb/src/usb_device_hid.c ../src/config/default/usb/src/usb_device.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/usb_device_init_data.c ../src/config/default/initialization.c ../src/config/default/tasks.c ../src/main.c ../src/app.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ1024EFH100
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\btl.ld"
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
${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o: ../src/config/default/bootloader/datastream/datastream_usb_device_hid.c  .generated_files/c974f75a7be2d1182a4734f127fd8548994659df.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1277623251" 
	@${RM} ${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o ../src/config/default/bootloader/datastream/datastream_usb_device_hid.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1748409734/bootloader.o: ../src/config/default/bootloader/bootloader.c  .generated_files/b4e6df465f78417e7cbb6fe6fa92611e4b1779b4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1748409734" 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1748409734/bootloader.o.d" -o ${OBJECTDIR}/_ext/1748409734/bootloader.o ../src/config/default/bootloader/bootloader.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o: ../src/config/default/bootloader/bootloader_nvm_interface.c  .generated_files/916a04e4f1a48f23ae4272973781a046e0976857.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1748409734" 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o.d" -o ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o ../src/config/default/bootloader/bootloader_nvm_interface.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2071311437/drv_usbhs.o: ../src/config/default/driver/usb/usbhs/src/drv_usbhs.c  .generated_files/6986e9be4253f087389adc5055416715324dc43c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2071311437" 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2071311437/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o ../src/config/default/driver/usb/usbhs/src/drv_usbhs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o: ../src/config/default/driver/usb/usbhs/src/drv_usbhs_device.c  .generated_files/1056e93d38b2b6781cdaabca445d043ebeb1de8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2071311437" 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o ../src/config/default/driver/usb/usbhs/src/drv_usbhs_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/cccf80bc2f5149dadf39067b9358cc8bf162e0ee.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/e3b5b932a7bdac5aa924b7a1ac9c7fd5bfdee98b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/99b6cfc48b9728472fd402018d8a558bcac567a1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/cb785b775420b45d29726e4ea28b51f57831c39e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/47f6aee290861fb9d98010a46d33f40f1146a4b3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/967b835b9e1c0a562cb18e0ea76c287118b16998.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/19c899a9e147f23c6d0edb834d253b274dacfd60.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101884895/sys_time.o: ../src/config/default/system/time/src/sys_time.c  .generated_files/de642264b38c783a5e7db3c03a2bcefb5e09cff1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101884895" 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101884895/sys_time.o.d" -o ${OBJECTDIR}/_ext/101884895/sys_time.o ../src/config/default/system/time/src/sys_time.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/308758920/usb_device_hid.o: ../src/config/default/usb/src/usb_device_hid.c  .generated_files/677fc74cbc2a3313713b07f7021ca28558f1f52c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/308758920" 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/308758920/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/308758920/usb_device_hid.o ../src/config/default/usb/src/usb_device_hid.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/308758920/usb_device.o: ../src/config/default/usb/src/usb_device.c  .generated_files/233fde57074911fd0a152116398c731e5fc8a09c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/308758920" 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/308758920/usb_device.o.d" -o ${OBJECTDIR}/_ext/308758920/usb_device.o ../src/config/default/usb/src/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/c61dbc8cb50b1e54cdd5566b23ed28c82ec2afe6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/9d54cea028890ec2f7ed2277abda9d7eb3e87607.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o: ../src/config/default/usb_device_init_data.c  .generated_files/72e8935fd4950877641a2a87ad1496eae206a1a0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o ../src/config/default/usb_device_init_data.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/47dc8e3a237730c110baf040867a0200bc05041b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/2320568bcb0f7f61136a8bab8bf95d6c3d37835.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/e46e06c44cd0af6e32f0ce85b25404c4b7348f7c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/8f3646da964b3c9161ec5451a218bbd95dd841db.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o: ../src/config/default/bootloader/datastream/datastream_usb_device_hid.c  .generated_files/3afb0b9e6450828dfbb09d4c0f565b9b6fbf3a59.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1277623251" 
	@${RM} ${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/1277623251/datastream_usb_device_hid.o ../src/config/default/bootloader/datastream/datastream_usb_device_hid.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1748409734/bootloader.o: ../src/config/default/bootloader/bootloader.c  .generated_files/ea067dbded911516ae618b5983d3b9ddf53dde31.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1748409734" 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1748409734/bootloader.o.d" -o ${OBJECTDIR}/_ext/1748409734/bootloader.o ../src/config/default/bootloader/bootloader.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o: ../src/config/default/bootloader/bootloader_nvm_interface.c  .generated_files/902eecdbb762ad7640ee7d9cc0adf2aa27f4e201.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1748409734" 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o.d" -o ${OBJECTDIR}/_ext/1748409734/bootloader_nvm_interface.o ../src/config/default/bootloader/bootloader_nvm_interface.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2071311437/drv_usbhs.o: ../src/config/default/driver/usb/usbhs/src/drv_usbhs.c  .generated_files/190a59e06eb7f1e7c10551e6e0194978ad439814.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2071311437" 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2071311437/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/2071311437/drv_usbhs.o ../src/config/default/driver/usb/usbhs/src/drv_usbhs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o: ../src/config/default/driver/usb/usbhs/src/drv_usbhs_device.c  .generated_files/d9bc29cf4a27faf6b3d47fc18427d6d026546a22.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2071311437" 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/2071311437/drv_usbhs_device.o ../src/config/default/driver/usb/usbhs/src/drv_usbhs_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/1eb884cbe47babbe63c4fff627c0a7f313a6700e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/594ef18824cfcd6afd26f837c693ff8ff192efaa.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/3988362baf798615baeebe56dfb53eea0559e1e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/8aee48a2f85700613fc0343f2687825b83f19940.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/21fdad3766bfa861582d98ac398d1c0d6bb81990.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/9470ccacc65d8182a881ed393dd58d66c606517a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/86576ba71d84b2248465baa6411432be126dea77.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101884895/sys_time.o: ../src/config/default/system/time/src/sys_time.c  .generated_files/9cfc99e400634fd89b8475dfc0cf0a1e4423b0af.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101884895" 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/101884895/sys_time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101884895/sys_time.o.d" -o ${OBJECTDIR}/_ext/101884895/sys_time.o ../src/config/default/system/time/src/sys_time.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/308758920/usb_device_hid.o: ../src/config/default/usb/src/usb_device_hid.c  .generated_files/f4c292db3e3106c6b78bc9086e0b4fa79901db95.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/308758920" 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/308758920/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/308758920/usb_device_hid.o ../src/config/default/usb/src/usb_device_hid.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/308758920/usb_device.o: ../src/config/default/usb/src/usb_device.c  .generated_files/4f361c2daf965b230c207f892fa7d8f4e5bcc076.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/308758920" 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/308758920/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/308758920/usb_device.o.d" -o ${OBJECTDIR}/_ext/308758920/usb_device.o ../src/config/default/usb/src/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/df0ecb9a6f78e6c41349e1cade4da97c90b6184e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/5e128d78fe18280ab9a1d070967b2e8bf4725056.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o: ../src/config/default/usb_device_init_data.c  .generated_files/2d97573377c4b61f1759055fcdeba23ba9d94cb8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1171490990/usb_device_init_data.o ../src/config/default/usb_device_init_data.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/8335238f01b69de6e62e07f4c5c95b99d899baa7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/69b5d934b82b9ed476afe5059f403db16b428438.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/4d9cd5910c9fb3d140924ac08e10618e42ab0d79.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/46f1d181b768b5d5f5558ed9e95eb929e1d61036.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFH100_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/btl.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/btl.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/EFH-Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
