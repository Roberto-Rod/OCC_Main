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
ifeq "$(wildcard nbproject/Makefile-local-PIC32MZ2048EFH100.mk)" "nbproject/Makefile-local-PIC32MZ2048EFH100.mk"
include nbproject/Makefile-local-PIC32MZ2048EFH100.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32MZ2048EFH100
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs.c ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs_device.c ../src/config/PIC32MZ2048EFH100/peripheral/adchs/plib_adchs.c ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache.c ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache_pic32mz.S ../src/config/PIC32MZ2048EFH100/peripheral/clk/plib_clk.c ../src/config/PIC32MZ2048EFH100/peripheral/cmp/plib_cmp.c ../src/config/PIC32MZ2048EFH100/peripheral/coretimer/plib_coretimer.c ../src/config/PIC32MZ2048EFH100/peripheral/cvr/plib_cvr.c ../src/config/PIC32MZ2048EFH100/peripheral/dmac/plib_dmac.c ../src/config/PIC32MZ2048EFH100/peripheral/evic/plib_evic.c ../src/config/PIC32MZ2048EFH100/peripheral/gpio/plib_gpio.c ../src/config/PIC32MZ2048EFH100/peripheral/pmp/plib_pmp.c ../src/config/PIC32MZ2048EFH100/peripheral/sqi/plib_sqi1.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr4.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr2.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr3.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr1/plib_tmr1.c ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart3.c ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart4.c ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart1.c ../src/config/PIC32MZ2048EFH100/stdio/xc32_monitor.c ../src/config/PIC32MZ2048EFH100/system/cache/sys_cache.c ../src/config/PIC32MZ2048EFH100/system/dma/sys_dma.c ../src/config/PIC32MZ2048EFH100/system/int/src/sys_int.c ../src/config/PIC32MZ2048EFH100/system/time/src/sys_time.c ../src/config/PIC32MZ2048EFH100/usb/src/usb_device.c ../src/config/PIC32MZ2048EFH100/usb/src/usb_device_endpoint_functions.c ../src/config/PIC32MZ2048EFH100/initialization.c ../src/config/PIC32MZ2048EFH100/interrupts.c ../src/config/PIC32MZ2048EFH100/exceptions.c ../src/config/PIC32MZ2048EFH100/usb_device_init_data.c ../src/config/PIC32MZ2048EFH100/tasks.c ../src/drv_dac_ad5667r.c ../src/drv_dpot_ad5247.c ../src/drv_ext_adc.c ../src/pdab_scan_functions.c ../src/pdab_usb_functions.c ../src/debug.c ../src/drv_lsc.c ../src/pic_comms.c ../src/scan_processing.c ../src/maths_library.c ../src/npda.c ../src/npda_tools.c ../src/drv_i2c4.c ../src/drv_laser.c ../src/message_exchange.c ../src/dspic_comms.c ../src/drv_N95256.c ../src/main.c ../src/pdab.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/409924846/drv_usbhs.o ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o ${OBJECTDIR}/_ext/335302008/plib_adchs.o ${OBJECTDIR}/_ext/337059663/plib_cache.o ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o ${OBJECTDIR}/_ext/1694203951/plib_clk.o ${OBJECTDIR}/_ext/1694203987/plib_cmp.o ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o ${OBJECTDIR}/_ext/1694204268/plib_cvr.o ${OBJECTDIR}/_ext/980745470/plib_dmac.o ${OBJECTDIR}/_ext/980784158/plib_evic.o ${OBJECTDIR}/_ext/980837986/plib_gpio.o ${OBJECTDIR}/_ext/1694216480/plib_pmp.o ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o ${OBJECTDIR}/_ext/981222603/plib_tmr1.o ${OBJECTDIR}/_ext/981240929/plib_uart3.o ${OBJECTDIR}/_ext/981240929/plib_uart4.o ${OBJECTDIR}/_ext/981240929/plib_uart1.o ${OBJECTDIR}/_ext/886878313/xc32_monitor.o ${OBJECTDIR}/_ext/1432450622/sys_cache.o ${OBJECTDIR}/_ext/1288638664/sys_dma.o ${OBJECTDIR}/_ext/779260412/sys_int.o ${OBJECTDIR}/_ext/986301086/sys_time.o ${OBJECTDIR}/_ext/665622343/usb_device.o ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o ${OBJECTDIR}/_ext/1667304431/initialization.o ${OBJECTDIR}/_ext/1667304431/interrupts.o ${OBJECTDIR}/_ext/1667304431/exceptions.o ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o ${OBJECTDIR}/_ext/1667304431/tasks.o ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/drv_lsc.o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ${OBJECTDIR}/_ext/1360937237/scan_processing.o ${OBJECTDIR}/_ext/1360937237/maths_library.o ${OBJECTDIR}/_ext/1360937237/npda.o ${OBJECTDIR}/_ext/1360937237/npda_tools.o ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o ${OBJECTDIR}/_ext/1360937237/drv_laser.o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ${OBJECTDIR}/_ext/1360937237/dspic_comms.o ${OBJECTDIR}/_ext/1360937237/drv_N95256.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/pdab.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/409924846/drv_usbhs.o.d ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o.d ${OBJECTDIR}/_ext/335302008/plib_adchs.o.d ${OBJECTDIR}/_ext/337059663/plib_cache.o.d ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.d ${OBJECTDIR}/_ext/1694203951/plib_clk.o.d ${OBJECTDIR}/_ext/1694203987/plib_cmp.o.d ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o.d ${OBJECTDIR}/_ext/1694204268/plib_cvr.o.d ${OBJECTDIR}/_ext/980745470/plib_dmac.o.d ${OBJECTDIR}/_ext/980784158/plib_evic.o.d ${OBJECTDIR}/_ext/980837986/plib_gpio.o.d ${OBJECTDIR}/_ext/1694216480/plib_pmp.o.d ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o.d ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o.d ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o.d ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o.d ${OBJECTDIR}/_ext/981222603/plib_tmr1.o.d ${OBJECTDIR}/_ext/981240929/plib_uart3.o.d ${OBJECTDIR}/_ext/981240929/plib_uart4.o.d ${OBJECTDIR}/_ext/981240929/plib_uart1.o.d ${OBJECTDIR}/_ext/886878313/xc32_monitor.o.d ${OBJECTDIR}/_ext/1432450622/sys_cache.o.d ${OBJECTDIR}/_ext/1288638664/sys_dma.o.d ${OBJECTDIR}/_ext/779260412/sys_int.o.d ${OBJECTDIR}/_ext/986301086/sys_time.o.d ${OBJECTDIR}/_ext/665622343/usb_device.o.d ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o.d ${OBJECTDIR}/_ext/1667304431/initialization.o.d ${OBJECTDIR}/_ext/1667304431/interrupts.o.d ${OBJECTDIR}/_ext/1667304431/exceptions.o.d ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o.d ${OBJECTDIR}/_ext/1667304431/tasks.o.d ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o.d ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o.d ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o.d ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o.d ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o.d ${OBJECTDIR}/_ext/1360937237/debug.o.d ${OBJECTDIR}/_ext/1360937237/drv_lsc.o.d ${OBJECTDIR}/_ext/1360937237/pic_comms.o.d ${OBJECTDIR}/_ext/1360937237/scan_processing.o.d ${OBJECTDIR}/_ext/1360937237/maths_library.o.d ${OBJECTDIR}/_ext/1360937237/npda.o.d ${OBJECTDIR}/_ext/1360937237/npda_tools.o.d ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o.d ${OBJECTDIR}/_ext/1360937237/drv_laser.o.d ${OBJECTDIR}/_ext/1360937237/message_exchange.o.d ${OBJECTDIR}/_ext/1360937237/dspic_comms.o.d ${OBJECTDIR}/_ext/1360937237/drv_N95256.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/pdab.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/409924846/drv_usbhs.o ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o ${OBJECTDIR}/_ext/335302008/plib_adchs.o ${OBJECTDIR}/_ext/337059663/plib_cache.o ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o ${OBJECTDIR}/_ext/1694203951/plib_clk.o ${OBJECTDIR}/_ext/1694203987/plib_cmp.o ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o ${OBJECTDIR}/_ext/1694204268/plib_cvr.o ${OBJECTDIR}/_ext/980745470/plib_dmac.o ${OBJECTDIR}/_ext/980784158/plib_evic.o ${OBJECTDIR}/_ext/980837986/plib_gpio.o ${OBJECTDIR}/_ext/1694216480/plib_pmp.o ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o ${OBJECTDIR}/_ext/981222603/plib_tmr1.o ${OBJECTDIR}/_ext/981240929/plib_uart3.o ${OBJECTDIR}/_ext/981240929/plib_uart4.o ${OBJECTDIR}/_ext/981240929/plib_uart1.o ${OBJECTDIR}/_ext/886878313/xc32_monitor.o ${OBJECTDIR}/_ext/1432450622/sys_cache.o ${OBJECTDIR}/_ext/1288638664/sys_dma.o ${OBJECTDIR}/_ext/779260412/sys_int.o ${OBJECTDIR}/_ext/986301086/sys_time.o ${OBJECTDIR}/_ext/665622343/usb_device.o ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o ${OBJECTDIR}/_ext/1667304431/initialization.o ${OBJECTDIR}/_ext/1667304431/interrupts.o ${OBJECTDIR}/_ext/1667304431/exceptions.o ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o ${OBJECTDIR}/_ext/1667304431/tasks.o ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/drv_lsc.o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ${OBJECTDIR}/_ext/1360937237/scan_processing.o ${OBJECTDIR}/_ext/1360937237/maths_library.o ${OBJECTDIR}/_ext/1360937237/npda.o ${OBJECTDIR}/_ext/1360937237/npda_tools.o ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o ${OBJECTDIR}/_ext/1360937237/drv_laser.o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ${OBJECTDIR}/_ext/1360937237/dspic_comms.o ${OBJECTDIR}/_ext/1360937237/drv_N95256.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/pdab.o

# Source Files
SOURCEFILES=../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs.c ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs_device.c ../src/config/PIC32MZ2048EFH100/peripheral/adchs/plib_adchs.c ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache.c ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache_pic32mz.S ../src/config/PIC32MZ2048EFH100/peripheral/clk/plib_clk.c ../src/config/PIC32MZ2048EFH100/peripheral/cmp/plib_cmp.c ../src/config/PIC32MZ2048EFH100/peripheral/coretimer/plib_coretimer.c ../src/config/PIC32MZ2048EFH100/peripheral/cvr/plib_cvr.c ../src/config/PIC32MZ2048EFH100/peripheral/dmac/plib_dmac.c ../src/config/PIC32MZ2048EFH100/peripheral/evic/plib_evic.c ../src/config/PIC32MZ2048EFH100/peripheral/gpio/plib_gpio.c ../src/config/PIC32MZ2048EFH100/peripheral/pmp/plib_pmp.c ../src/config/PIC32MZ2048EFH100/peripheral/sqi/plib_sqi1.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr4.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr2.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr3.c ../src/config/PIC32MZ2048EFH100/peripheral/tmr1/plib_tmr1.c ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart3.c ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart4.c ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart1.c ../src/config/PIC32MZ2048EFH100/stdio/xc32_monitor.c ../src/config/PIC32MZ2048EFH100/system/cache/sys_cache.c ../src/config/PIC32MZ2048EFH100/system/dma/sys_dma.c ../src/config/PIC32MZ2048EFH100/system/int/src/sys_int.c ../src/config/PIC32MZ2048EFH100/system/time/src/sys_time.c ../src/config/PIC32MZ2048EFH100/usb/src/usb_device.c ../src/config/PIC32MZ2048EFH100/usb/src/usb_device_endpoint_functions.c ../src/config/PIC32MZ2048EFH100/initialization.c ../src/config/PIC32MZ2048EFH100/interrupts.c ../src/config/PIC32MZ2048EFH100/exceptions.c ../src/config/PIC32MZ2048EFH100/usb_device_init_data.c ../src/config/PIC32MZ2048EFH100/tasks.c ../src/drv_dac_ad5667r.c ../src/drv_dpot_ad5247.c ../src/drv_ext_adc.c ../src/pdab_scan_functions.c ../src/pdab_usb_functions.c ../src/debug.c ../src/drv_lsc.c ../src/pic_comms.c ../src/scan_processing.c ../src/maths_library.c ../src/npda.c ../src/npda_tools.c ../src/drv_i2c4.c ../src/drv_laser.c ../src/message_exchange.c ../src/dspic_comms.c ../src/drv_N95256.c ../src/main.c ../src/pdab.c



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
	${MAKE}  -f nbproject/Makefile-PIC32MZ2048EFH100.mk dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ1024EFH100
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o: ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache_pic32mz.S  .generated_files/329f2b23b45bad1668acd8104762fc1ff53e8032.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/337059663" 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache_pic32mz.S  -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o: ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache_pic32mz.S  .generated_files/73fe7dbb13e8c6449e956f11604c21dac310d9fa.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/337059663" 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache_pic32mz.S  -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.asm.d",--gdwarf-2 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/337059663/plib_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/409924846/drv_usbhs.o: ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs.c  .generated_files/b0267b0ed702f17ee8c38159a2bca4042a7a0a99.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/409924846" 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/409924846/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/409924846/drv_usbhs.o ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o: ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs_device.c  .generated_files/722cd1346befe97716968aad4e38ad741a2ead02.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/409924846" 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs_device.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/335302008/plib_adchs.o: ../src/config/PIC32MZ2048EFH100/peripheral/adchs/plib_adchs.c  .generated_files/4c92c01ecbc0cf2fe2133ed4a1262dd8dc28a1c9.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/335302008" 
	@${RM} ${OBJECTDIR}/_ext/335302008/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/335302008/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/335302008/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/335302008/plib_adchs.o ../src/config/PIC32MZ2048EFH100/peripheral/adchs/plib_adchs.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/337059663/plib_cache.o: ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache.c  .generated_files/4fa97f9e283f8e5e43c2a0219d8e8a0a9015d5e8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/337059663" 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/337059663/plib_cache.o.d" -o ${OBJECTDIR}/_ext/337059663/plib_cache.o ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694203951/plib_clk.o: ../src/config/PIC32MZ2048EFH100/peripheral/clk/plib_clk.c  .generated_files/66e3fa50b62b45f4cd7660a21366ed67219c43f5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694203951" 
	@${RM} ${OBJECTDIR}/_ext/1694203951/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694203951/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694203951/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1694203951/plib_clk.o ../src/config/PIC32MZ2048EFH100/peripheral/clk/plib_clk.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694203987/plib_cmp.o: ../src/config/PIC32MZ2048EFH100/peripheral/cmp/plib_cmp.c  .generated_files/c81af972f6684f742cccd6258d486b1544cfa4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694203987" 
	@${RM} ${OBJECTDIR}/_ext/1694203987/plib_cmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694203987/plib_cmp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694203987/plib_cmp.o.d" -o ${OBJECTDIR}/_ext/1694203987/plib_cmp.o ../src/config/PIC32MZ2048EFH100/peripheral/cmp/plib_cmp.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384315821/plib_coretimer.o: ../src/config/PIC32MZ2048EFH100/peripheral/coretimer/plib_coretimer.c  .generated_files/7e926bcfcb4b37d3e1ef7d561bf3bb5d3268d8b7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1384315821" 
	@${RM} ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1384315821/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o ../src/config/PIC32MZ2048EFH100/peripheral/coretimer/plib_coretimer.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694204268/plib_cvr.o: ../src/config/PIC32MZ2048EFH100/peripheral/cvr/plib_cvr.c  .generated_files/30b04fb57472f6d351a1ab7adf14cb0fc083bad1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694204268" 
	@${RM} ${OBJECTDIR}/_ext/1694204268/plib_cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694204268/plib_cvr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694204268/plib_cvr.o.d" -o ${OBJECTDIR}/_ext/1694204268/plib_cvr.o ../src/config/PIC32MZ2048EFH100/peripheral/cvr/plib_cvr.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/980745470/plib_dmac.o: ../src/config/PIC32MZ2048EFH100/peripheral/dmac/plib_dmac.c  .generated_files/6435121492ff7ab8784251bb7489e47d4c3fd8ba.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/980745470" 
	@${RM} ${OBJECTDIR}/_ext/980745470/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/980745470/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/980745470/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/980745470/plib_dmac.o ../src/config/PIC32MZ2048EFH100/peripheral/dmac/plib_dmac.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/980784158/plib_evic.o: ../src/config/PIC32MZ2048EFH100/peripheral/evic/plib_evic.c  .generated_files/400cb3b6a9034c50b6c0b61b39b186eba4fb2411.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/980784158" 
	@${RM} ${OBJECTDIR}/_ext/980784158/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/980784158/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/980784158/plib_evic.o.d" -o ${OBJECTDIR}/_ext/980784158/plib_evic.o ../src/config/PIC32MZ2048EFH100/peripheral/evic/plib_evic.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/980837986/plib_gpio.o: ../src/config/PIC32MZ2048EFH100/peripheral/gpio/plib_gpio.c  .generated_files/413b0f9be224f3aab2255fdbe795d36a133ff84d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/980837986" 
	@${RM} ${OBJECTDIR}/_ext/980837986/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/980837986/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/980837986/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/980837986/plib_gpio.o ../src/config/PIC32MZ2048EFH100/peripheral/gpio/plib_gpio.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694216480/plib_pmp.o: ../src/config/PIC32MZ2048EFH100/peripheral/pmp/plib_pmp.c  .generated_files/6422936d0cf8ec3644403b1427d9a08e294173b0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694216480" 
	@${RM} ${OBJECTDIR}/_ext/1694216480/plib_pmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694216480/plib_pmp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694216480/plib_pmp.o.d" -o ${OBJECTDIR}/_ext/1694216480/plib_pmp.o ../src/config/PIC32MZ2048EFH100/peripheral/pmp/plib_pmp.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694219480/plib_sqi1.o: ../src/config/PIC32MZ2048EFH100/peripheral/sqi/plib_sqi1.c  .generated_files/63882d47dbbd2cf4a626f7ac167666011e26017a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694219480" 
	@${RM} ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694219480/plib_sqi1.o.d" -o ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o ../src/config/PIC32MZ2048EFH100/peripheral/sqi/plib_sqi1.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694220326/plib_tmr4.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr4.c  .generated_files/2256bc4d44f44b14ab59600512a0f8aa4ad772f7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694220326" 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694220326/plib_tmr4.o.d" -o ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr4.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694220326/plib_tmr2.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr2.c  .generated_files/81ae9c45112ac7f5cd76ccb873b509e0dfcb4b70.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694220326" 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694220326/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr2.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694220326/plib_tmr3.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr3.c  .generated_files/e9acf978db2313b64c3cf70f53a446f28e997837.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694220326" 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694220326/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr3.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981222603/plib_tmr1.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr1/plib_tmr1.c  .generated_files/67c9a9b707adb7eb63024a71da08a9d2f38af802.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981222603" 
	@${RM} ${OBJECTDIR}/_ext/981222603/plib_tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/981222603/plib_tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981222603/plib_tmr1.o.d" -o ${OBJECTDIR}/_ext/981222603/plib_tmr1.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr1/plib_tmr1.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981240929/plib_uart3.o: ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart3.c  .generated_files/6588cc7a25b79975dff325ae346a55c0a925efc2.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981240929" 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981240929/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/981240929/plib_uart3.o ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart3.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981240929/plib_uart4.o: ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart4.c  .generated_files/26e22694c6b2a436da0e0d84203d3f4b8f21cb8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981240929" 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart4.o.d 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981240929/plib_uart4.o.d" -o ${OBJECTDIR}/_ext/981240929/plib_uart4.o ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart4.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981240929/plib_uart1.o: ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart1.c  .generated_files/79186876b2d7bb184ea603da7bbb97457fb99a09.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981240929" 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981240929/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/981240929/plib_uart1.o ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart1.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/886878313/xc32_monitor.o: ../src/config/PIC32MZ2048EFH100/stdio/xc32_monitor.c  .generated_files/5c230537e004d5b4e0df60bc429379475231a5a7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/886878313" 
	@${RM} ${OBJECTDIR}/_ext/886878313/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/886878313/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/886878313/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/886878313/xc32_monitor.o ../src/config/PIC32MZ2048EFH100/stdio/xc32_monitor.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1432450622/sys_cache.o: ../src/config/PIC32MZ2048EFH100/system/cache/sys_cache.c  .generated_files/61a374fc7e78d0c05a5bcc38ffd7ebf0ad3dfe4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1432450622" 
	@${RM} ${OBJECTDIR}/_ext/1432450622/sys_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1432450622/sys_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1432450622/sys_cache.o.d" -o ${OBJECTDIR}/_ext/1432450622/sys_cache.o ../src/config/PIC32MZ2048EFH100/system/cache/sys_cache.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1288638664/sys_dma.o: ../src/config/PIC32MZ2048EFH100/system/dma/sys_dma.c  .generated_files/46005fe0578f6f5c52dfa27ba4d7f702edf01a2c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1288638664" 
	@${RM} ${OBJECTDIR}/_ext/1288638664/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1288638664/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1288638664/sys_dma.o.d" -o ${OBJECTDIR}/_ext/1288638664/sys_dma.o ../src/config/PIC32MZ2048EFH100/system/dma/sys_dma.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/779260412/sys_int.o: ../src/config/PIC32MZ2048EFH100/system/int/src/sys_int.c  .generated_files/b9649db3c077f4971856a1f1a96f2526ddd844a0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/779260412" 
	@${RM} ${OBJECTDIR}/_ext/779260412/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/779260412/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/779260412/sys_int.o.d" -o ${OBJECTDIR}/_ext/779260412/sys_int.o ../src/config/PIC32MZ2048EFH100/system/int/src/sys_int.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/986301086/sys_time.o: ../src/config/PIC32MZ2048EFH100/system/time/src/sys_time.c  .generated_files/251aad2e7841e4d742998d1891d25795bc33855f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/986301086" 
	@${RM} ${OBJECTDIR}/_ext/986301086/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/986301086/sys_time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/986301086/sys_time.o.d" -o ${OBJECTDIR}/_ext/986301086/sys_time.o ../src/config/PIC32MZ2048EFH100/system/time/src/sys_time.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/665622343/usb_device.o: ../src/config/PIC32MZ2048EFH100/usb/src/usb_device.c  .generated_files/36631f4a6c5023f33e2474a5fea5dc54e3fbdb10.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/665622343" 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/665622343/usb_device.o.d" -o ${OBJECTDIR}/_ext/665622343/usb_device.o ../src/config/PIC32MZ2048EFH100/usb/src/usb_device.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o: ../src/config/PIC32MZ2048EFH100/usb/src/usb_device_endpoint_functions.c  .generated_files/5773c6ff35b81cc10637487a6444c83d523dd8f0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/665622343" 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o.d" -o ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o ../src/config/PIC32MZ2048EFH100/usb/src/usb_device_endpoint_functions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/initialization.o: ../src/config/PIC32MZ2048EFH100/initialization.c  .generated_files/978f207655642ff2c2a65da15a6c7f24db2621ee.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/initialization.o.d" -o ${OBJECTDIR}/_ext/1667304431/initialization.o ../src/config/PIC32MZ2048EFH100/initialization.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/interrupts.o: ../src/config/PIC32MZ2048EFH100/interrupts.c  .generated_files/a6b09c223d035ae59a70dd97b885beb74b1fae35.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/interrupts.o.d" -o ${OBJECTDIR}/_ext/1667304431/interrupts.o ../src/config/PIC32MZ2048EFH100/interrupts.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/exceptions.o: ../src/config/PIC32MZ2048EFH100/exceptions.c  .generated_files/d65e08298503168c33b1b11bd85e6cd859ee1c03.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/exceptions.o.d" -o ${OBJECTDIR}/_ext/1667304431/exceptions.o ../src/config/PIC32MZ2048EFH100/exceptions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o: ../src/config/PIC32MZ2048EFH100/usb_device_init_data.c  .generated_files/f7a8dd789cdaabfd8482719df19aebb89fa466b1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o ../src/config/PIC32MZ2048EFH100/usb_device_init_data.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/tasks.o: ../src/config/PIC32MZ2048EFH100/tasks.c  .generated_files/54e79490c5a028b39da445dd13cb662dd31036d1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/tasks.o.d" -o ${OBJECTDIR}/_ext/1667304431/tasks.o ../src/config/PIC32MZ2048EFH100/tasks.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o: ../src/drv_dac_ad5667r.c  .generated_files/ee6d43b49826621190c1e79aafb8ef3a65f52b3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o ../src/drv_dac_ad5667r.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o: ../src/drv_dpot_ad5247.c  .generated_files/32a8bd80ce915c908aa60f12fe0848122ffc335.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o ../src/drv_dpot_ad5247.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o: ../src/drv_ext_adc.c  .generated_files/5e8d83b89ce69f617ae9a4679691f845da3460ac.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o ../src/drv_ext_adc.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o: ../src/pdab_scan_functions.c  .generated_files/439de4e60183317354b8a96455ca3b63e15e809b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o.d" -o ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o ../src/pdab_scan_functions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o: ../src/pdab_usb_functions.c  .generated_files/4798cca8c9ce04902203f8feccb45a3f30ab6647.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o.d" -o ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o ../src/pdab_usb_functions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  .generated_files/eac002dd85b4ca1c093bc12d53d3119eaa52cad9.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_lsc.o: ../src/drv_lsc.c  .generated_files/8c8d971dcbf623bb55f4b4d34355533c1248f676.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_lsc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_lsc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_lsc.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_lsc.o ../src/drv_lsc.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pic_comms.o: ../src/pic_comms.c  .generated_files/d7dd3b7a107db5eebef989dadfc159119fbe7f46.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ../src/pic_comms.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/scan_processing.o: ../src/scan_processing.c  .generated_files/e41667cc8b67585a51838adf517b505f38681372.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan_processing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan_processing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/scan_processing.o.d" -o ${OBJECTDIR}/_ext/1360937237/scan_processing.o ../src/scan_processing.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/maths_library.o: ../src/maths_library.c  .generated_files/bf36943a4fe16f6c82fd809521fe3d3503062b27.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/maths_library.o.d" -o ${OBJECTDIR}/_ext/1360937237/maths_library.o ../src/maths_library.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/npda.o: ../src/npda.c  .generated_files/bf9ba71d7c2f18ecd0e37fbf3bd9920b422c7fff.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/npda.o.d" -o ${OBJECTDIR}/_ext/1360937237/npda.o ../src/npda.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/npda_tools.o: ../src/npda_tools.c  .generated_files/b5b3521fc5493fa4102f600f6eefd35bb6410e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda_tools.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/npda_tools.o.d" -o ${OBJECTDIR}/_ext/1360937237/npda_tools.o ../src/npda_tools.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_i2c4.o: ../src/drv_i2c4.c  .generated_files/86e0b8b97ecc12775a80958430aa821b05e3ceef.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_i2c4.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o ../src/drv_i2c4.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_laser.o: ../src/drv_laser.c  .generated_files/fbe5a69b091d35f073d9ba33fe280fd3b0698e31.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_laser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_laser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_laser.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_laser.o ../src/drv_laser.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/message_exchange.o: ../src/message_exchange.c  .generated_files/885138f2fd4b8d0002f6984579e060a4d860c440.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/message_exchange.o.d" -o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ../src/message_exchange.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/dspic_comms.o: ../src/dspic_comms.c  .generated_files/12774bdf5ee94580622b1eac477b18a6fb7d5d64.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dspic_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dspic_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dspic_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/dspic_comms.o ../src/dspic_comms.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_N95256.o: ../src/drv_N95256.c  .generated_files/4a945c28a7200abd2a05c82cb4e1986d9af589ce.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_N95256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_N95256.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_N95256.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_N95256.o ../src/drv_N95256.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/f799e7400d8ed523752f00fa9f7372b416256157.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pdab.o: ../src/pdab.c  .generated_files/64c35d65af7d5cc9ecb513aebd1a85cd27d5217a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pdab.o.d" -o ${OBJECTDIR}/_ext/1360937237/pdab.o ../src/pdab.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/409924846/drv_usbhs.o: ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs.c  .generated_files/937f68d6548adebdd4f25b9017a74832e40f825d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/409924846" 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/409924846/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/409924846/drv_usbhs.o ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o: ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs_device.c  .generated_files/bb458305d1bcf03afcb375cfaa2f0c07061c800d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/409924846" 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/409924846/drv_usbhs_device.o ../src/config/PIC32MZ2048EFH100/driver/usb/usbhs/src/drv_usbhs_device.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/335302008/plib_adchs.o: ../src/config/PIC32MZ2048EFH100/peripheral/adchs/plib_adchs.c  .generated_files/e1b680ebb9329ff134944c1eb901dfec9e03735d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/335302008" 
	@${RM} ${OBJECTDIR}/_ext/335302008/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/335302008/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/335302008/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/335302008/plib_adchs.o ../src/config/PIC32MZ2048EFH100/peripheral/adchs/plib_adchs.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/337059663/plib_cache.o: ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache.c  .generated_files/cbe8de6238d24b1ddf8ab1c7dd1bd8a7ed0f7fcf.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/337059663" 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/337059663/plib_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/337059663/plib_cache.o.d" -o ${OBJECTDIR}/_ext/337059663/plib_cache.o ../src/config/PIC32MZ2048EFH100/peripheral/cache/plib_cache.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694203951/plib_clk.o: ../src/config/PIC32MZ2048EFH100/peripheral/clk/plib_clk.c  .generated_files/7544c018cb3891bf69eb3480b48d7846f259b591.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694203951" 
	@${RM} ${OBJECTDIR}/_ext/1694203951/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694203951/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694203951/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1694203951/plib_clk.o ../src/config/PIC32MZ2048EFH100/peripheral/clk/plib_clk.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694203987/plib_cmp.o: ../src/config/PIC32MZ2048EFH100/peripheral/cmp/plib_cmp.c  .generated_files/66013bc38beb05f1ac9dd90617bcf798edcce2c1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694203987" 
	@${RM} ${OBJECTDIR}/_ext/1694203987/plib_cmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694203987/plib_cmp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694203987/plib_cmp.o.d" -o ${OBJECTDIR}/_ext/1694203987/plib_cmp.o ../src/config/PIC32MZ2048EFH100/peripheral/cmp/plib_cmp.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384315821/plib_coretimer.o: ../src/config/PIC32MZ2048EFH100/peripheral/coretimer/plib_coretimer.c  .generated_files/ae35eb0fbb9cceb26477ff28d60f68976580e278.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1384315821" 
	@${RM} ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1384315821/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1384315821/plib_coretimer.o ../src/config/PIC32MZ2048EFH100/peripheral/coretimer/plib_coretimer.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694204268/plib_cvr.o: ../src/config/PIC32MZ2048EFH100/peripheral/cvr/plib_cvr.c  .generated_files/bf2d0177e2081921bb03dd7e717709de878e17d0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694204268" 
	@${RM} ${OBJECTDIR}/_ext/1694204268/plib_cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694204268/plib_cvr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694204268/plib_cvr.o.d" -o ${OBJECTDIR}/_ext/1694204268/plib_cvr.o ../src/config/PIC32MZ2048EFH100/peripheral/cvr/plib_cvr.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/980745470/plib_dmac.o: ../src/config/PIC32MZ2048EFH100/peripheral/dmac/plib_dmac.c  .generated_files/73e73ebea9dcd6a4affa76c45057cee99daf055d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/980745470" 
	@${RM} ${OBJECTDIR}/_ext/980745470/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/980745470/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/980745470/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/980745470/plib_dmac.o ../src/config/PIC32MZ2048EFH100/peripheral/dmac/plib_dmac.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/980784158/plib_evic.o: ../src/config/PIC32MZ2048EFH100/peripheral/evic/plib_evic.c  .generated_files/f56ff912e27c2735492e88c33c0314876e6af050.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/980784158" 
	@${RM} ${OBJECTDIR}/_ext/980784158/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/980784158/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/980784158/plib_evic.o.d" -o ${OBJECTDIR}/_ext/980784158/plib_evic.o ../src/config/PIC32MZ2048EFH100/peripheral/evic/plib_evic.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/980837986/plib_gpio.o: ../src/config/PIC32MZ2048EFH100/peripheral/gpio/plib_gpio.c  .generated_files/75eafbecd148e1ac0ef4e2fba194d98c850fd90a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/980837986" 
	@${RM} ${OBJECTDIR}/_ext/980837986/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/980837986/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/980837986/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/980837986/plib_gpio.o ../src/config/PIC32MZ2048EFH100/peripheral/gpio/plib_gpio.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694216480/plib_pmp.o: ../src/config/PIC32MZ2048EFH100/peripheral/pmp/plib_pmp.c  .generated_files/8b5f2914c34d9bdcee166654e052dee61607caf7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694216480" 
	@${RM} ${OBJECTDIR}/_ext/1694216480/plib_pmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694216480/plib_pmp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694216480/plib_pmp.o.d" -o ${OBJECTDIR}/_ext/1694216480/plib_pmp.o ../src/config/PIC32MZ2048EFH100/peripheral/pmp/plib_pmp.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694219480/plib_sqi1.o: ../src/config/PIC32MZ2048EFH100/peripheral/sqi/plib_sqi1.c  .generated_files/5464bff14d615fe8c22c37b109b35d142bb1a095.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694219480" 
	@${RM} ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694219480/plib_sqi1.o.d" -o ${OBJECTDIR}/_ext/1694219480/plib_sqi1.o ../src/config/PIC32MZ2048EFH100/peripheral/sqi/plib_sqi1.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694220326/plib_tmr4.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr4.c  .generated_files/cf057bb3673448bb49c3031d973e9c13e7bb74cf.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694220326" 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694220326/plib_tmr4.o.d" -o ${OBJECTDIR}/_ext/1694220326/plib_tmr4.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr4.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694220326/plib_tmr2.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr2.c  .generated_files/a9033fb809e355462a4d8c7247159ffe4940e10e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694220326" 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694220326/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/1694220326/plib_tmr2.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr2.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1694220326/plib_tmr3.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr3.c  .generated_files/6f0d7a41a9d48a9ee4efe8bab4cb79c891a76bfe.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1694220326" 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1694220326/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/1694220326/plib_tmr3.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr/plib_tmr3.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981222603/plib_tmr1.o: ../src/config/PIC32MZ2048EFH100/peripheral/tmr1/plib_tmr1.c  .generated_files/3972a97d9b329ad72af655e745482dbfe6a3d418.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981222603" 
	@${RM} ${OBJECTDIR}/_ext/981222603/plib_tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/981222603/plib_tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981222603/plib_tmr1.o.d" -o ${OBJECTDIR}/_ext/981222603/plib_tmr1.o ../src/config/PIC32MZ2048EFH100/peripheral/tmr1/plib_tmr1.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981240929/plib_uart3.o: ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart3.c  .generated_files/ea94a56dd324ca21ae7cfc9f689cb0861a8531a4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981240929" 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981240929/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/981240929/plib_uart3.o ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart3.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981240929/plib_uart4.o: ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart4.c  .generated_files/c74290e8a3d468d0773f0ef073b278c0961a79ed.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981240929" 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart4.o.d 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981240929/plib_uart4.o.d" -o ${OBJECTDIR}/_ext/981240929/plib_uart4.o ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart4.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/981240929/plib_uart1.o: ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart1.c  .generated_files/dccbcd5bc6aa81f9165f9e4bd368fc1732d76de2.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/981240929" 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/981240929/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/981240929/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/981240929/plib_uart1.o ../src/config/PIC32MZ2048EFH100/peripheral/uart/plib_uart1.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/886878313/xc32_monitor.o: ../src/config/PIC32MZ2048EFH100/stdio/xc32_monitor.c  .generated_files/7a1b366a1ee4fa075a13e94a45e320bae1036529.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/886878313" 
	@${RM} ${OBJECTDIR}/_ext/886878313/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/886878313/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/886878313/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/886878313/xc32_monitor.o ../src/config/PIC32MZ2048EFH100/stdio/xc32_monitor.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1432450622/sys_cache.o: ../src/config/PIC32MZ2048EFH100/system/cache/sys_cache.c  .generated_files/2494dcfcea7cbcc180aad60c2651ad006179d5c3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1432450622" 
	@${RM} ${OBJECTDIR}/_ext/1432450622/sys_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1432450622/sys_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1432450622/sys_cache.o.d" -o ${OBJECTDIR}/_ext/1432450622/sys_cache.o ../src/config/PIC32MZ2048EFH100/system/cache/sys_cache.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1288638664/sys_dma.o: ../src/config/PIC32MZ2048EFH100/system/dma/sys_dma.c  .generated_files/e687c9ed0273bb0366c0f1a785c6378140d009fc.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1288638664" 
	@${RM} ${OBJECTDIR}/_ext/1288638664/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1288638664/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1288638664/sys_dma.o.d" -o ${OBJECTDIR}/_ext/1288638664/sys_dma.o ../src/config/PIC32MZ2048EFH100/system/dma/sys_dma.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/779260412/sys_int.o: ../src/config/PIC32MZ2048EFH100/system/int/src/sys_int.c  .generated_files/63deab4ab773ea3675589cb91a8fbf01cadc0e9e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/779260412" 
	@${RM} ${OBJECTDIR}/_ext/779260412/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/779260412/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/779260412/sys_int.o.d" -o ${OBJECTDIR}/_ext/779260412/sys_int.o ../src/config/PIC32MZ2048EFH100/system/int/src/sys_int.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/986301086/sys_time.o: ../src/config/PIC32MZ2048EFH100/system/time/src/sys_time.c  .generated_files/5d0dbc2c092dd783577c090895015bc610b671cc.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/986301086" 
	@${RM} ${OBJECTDIR}/_ext/986301086/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/986301086/sys_time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/986301086/sys_time.o.d" -o ${OBJECTDIR}/_ext/986301086/sys_time.o ../src/config/PIC32MZ2048EFH100/system/time/src/sys_time.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/665622343/usb_device.o: ../src/config/PIC32MZ2048EFH100/usb/src/usb_device.c  .generated_files/34af5893a64c3a956f7f380af23e24b213657086.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/665622343" 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/665622343/usb_device.o.d" -o ${OBJECTDIR}/_ext/665622343/usb_device.o ../src/config/PIC32MZ2048EFH100/usb/src/usb_device.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o: ../src/config/PIC32MZ2048EFH100/usb/src/usb_device_endpoint_functions.c  .generated_files/9a62a4cdfbc24bc54bad6beb9e70da8ad4899ea7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/665622343" 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o.d" -o ${OBJECTDIR}/_ext/665622343/usb_device_endpoint_functions.o ../src/config/PIC32MZ2048EFH100/usb/src/usb_device_endpoint_functions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/initialization.o: ../src/config/PIC32MZ2048EFH100/initialization.c  .generated_files/ba7709a25ad001fa0eac2a75819b8b840bc29c78.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/initialization.o.d" -o ${OBJECTDIR}/_ext/1667304431/initialization.o ../src/config/PIC32MZ2048EFH100/initialization.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/interrupts.o: ../src/config/PIC32MZ2048EFH100/interrupts.c  .generated_files/544ea0de97071deca39d5a17c075d77331fbc031.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/interrupts.o.d" -o ${OBJECTDIR}/_ext/1667304431/interrupts.o ../src/config/PIC32MZ2048EFH100/interrupts.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/exceptions.o: ../src/config/PIC32MZ2048EFH100/exceptions.c  .generated_files/45db7d15068beceb59875bee0312cfb8dee829eb.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/exceptions.o.d" -o ${OBJECTDIR}/_ext/1667304431/exceptions.o ../src/config/PIC32MZ2048EFH100/exceptions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o: ../src/config/PIC32MZ2048EFH100/usb_device_init_data.c  .generated_files/10e44ce56ba84406b945b65f028a4d0f2ccce54b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o.d" -o ${OBJECTDIR}/_ext/1667304431/usb_device_init_data.o ../src/config/PIC32MZ2048EFH100/usb_device_init_data.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1667304431/tasks.o: ../src/config/PIC32MZ2048EFH100/tasks.c  .generated_files/c18811f9aab1fa56747249ee36faed7ca188a090.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1667304431" 
	@${RM} ${OBJECTDIR}/_ext/1667304431/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1667304431/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1667304431/tasks.o.d" -o ${OBJECTDIR}/_ext/1667304431/tasks.o ../src/config/PIC32MZ2048EFH100/tasks.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o: ../src/drv_dac_ad5667r.c  .generated_files/73c3d24e6b74e124379a16a9b8456283ca8d3d6e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_dac_ad5667r.o ../src/drv_dac_ad5667r.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o: ../src/drv_dpot_ad5247.c  .generated_files/ac2131f7237aca16efe1cac8e24701884306905f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_dpot_ad5247.o ../src/drv_dpot_ad5247.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o: ../src/drv_ext_adc.c  .generated_files/a3158f2d66b713d9cf62c0361e7b848f814409b6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_ext_adc.o ../src/drv_ext_adc.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o: ../src/pdab_scan_functions.c  .generated_files/cb3bfe19833d437958e2853371725da5bf97c4d7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o.d" -o ${OBJECTDIR}/_ext/1360937237/pdab_scan_functions.o ../src/pdab_scan_functions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o: ../src/pdab_usb_functions.c  .generated_files/a7ffa7ca1f2cc2de7913ddb18beb28f7021c6c1c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o.d" -o ${OBJECTDIR}/_ext/1360937237/pdab_usb_functions.o ../src/pdab_usb_functions.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  .generated_files/5414d68057d64716218b92fe7f5813d2549a6b91.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_lsc.o: ../src/drv_lsc.c  .generated_files/d2b2045b16afd7cfb7882c5ecb16d6b40f23f67c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_lsc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_lsc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_lsc.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_lsc.o ../src/drv_lsc.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pic_comms.o: ../src/pic_comms.c  .generated_files/c1b0689920d9c83570b4425e86456b0854aa218e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ../src/pic_comms.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/scan_processing.o: ../src/scan_processing.c  .generated_files/5f5c7877a39e728c461517abe6110f0b7bc404f3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan_processing.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan_processing.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/scan_processing.o.d" -o ${OBJECTDIR}/_ext/1360937237/scan_processing.o ../src/scan_processing.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/maths_library.o: ../src/maths_library.c  .generated_files/3ee0814f107106dd2477aa8116c960a7a0d25863.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/maths_library.o.d" -o ${OBJECTDIR}/_ext/1360937237/maths_library.o ../src/maths_library.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/npda.o: ../src/npda.c  .generated_files/906f220d2d00065c760eb6cfe246df8a05061270.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/npda.o.d" -o ${OBJECTDIR}/_ext/1360937237/npda.o ../src/npda.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/npda_tools.o: ../src/npda_tools.c  .generated_files/9bea452e72303d5f745390d7eaf08efda6c693e0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda_tools.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/npda_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/npda_tools.o.d" -o ${OBJECTDIR}/_ext/1360937237/npda_tools.o ../src/npda_tools.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_i2c4.o: ../src/drv_i2c4.c  .generated_files/7e2066179dba4a67d17ade3f9b2a892dfbc7eeed.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_i2c4.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_i2c4.o ../src/drv_i2c4.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_laser.o: ../src/drv_laser.c  .generated_files/5ccabdfd7127261e4f500083ed63449855ef9e74.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_laser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_laser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_laser.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_laser.o ../src/drv_laser.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/message_exchange.o: ../src/message_exchange.c  .generated_files/c66a12324fbeb86a47f9860c8daad0d2df4eee6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/message_exchange.o.d" -o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ../src/message_exchange.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/dspic_comms.o: ../src/dspic_comms.c  .generated_files/61600594f0339b55bec4a2aa666e09e0c7619002.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dspic_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dspic_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dspic_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/dspic_comms.o ../src/dspic_comms.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_N95256.o: ../src/drv_N95256.c  .generated_files/46e67d2c6ad357a59d0a98c02ab68905bc7d902c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_N95256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_N95256.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_N95256.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_N95256.o ../src/drv_N95256.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/9bfe521309e7c7b63c6f5df86223b628437a802f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pdab.o: ../src/pdab.c  .generated_files/8839db34771723eeed564960793452bf86812a6e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pdab.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -I"../src" -I"../src/config/PIC32MZ2048EFH100" -I"../src/packs/PIC32MZ1024EFH100_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pdab.o.d" -o ${OBJECTDIR}/_ext/1360937237/pdab.o ../src/pdab.c    -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32MZ2048EFH100=$(CND_CONF)  -no-legacy-libc  -D TEST_DISABLE_HELPER_UART_INIT -D TEST_DISABLE_HELPER_TMR2_INIT $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PDAB_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32MZ2048EFH100
	${RM} -r dist/PIC32MZ2048EFH100

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
