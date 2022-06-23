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
ifeq "$(wildcard nbproject/Makefile-local-Main_Board_Rev_C.mk)" "nbproject/Makefile-local-Main_Board_Rev_C.mk"
include nbproject/Makefile-local-Main_Board_Rev_C.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Main_Board_Rev_C
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/libnano2D_hal.c ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/drv_gfx_glcd.c ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/plib_glcd.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_context.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_default_impl.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display_def.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_interface.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_def.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_def.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_get.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_interface.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_layer.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_pixel_buffer.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_interface.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_rect.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_util.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_set.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_blend.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_convert.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_lerp.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_value.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_arc.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_blit.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_circle.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_ellipse.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_line.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_pixel.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_rect.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_stretchblit.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_math.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_harmony.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_init.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_array.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context_paint.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_draw.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_editwidget.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_event.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_input.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_layer.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_list.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_rectarray.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_scheme.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_screen.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_string.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_utils.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic_common.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_radiobutton_group.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_events.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_macros.c ../src/config/Main_Board_Rev_C/gfx/third_party/src/lodepng/lodepng.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_utils.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_palette.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_stringbuffer_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_query.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_utils.c ../src/config/Main_Board_Rev_C/gfx/gfx_assets.c ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache.c ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache_pic32mz.S ../src/config/Main_Board_Rev_C/peripheral/clk/plib_clk.c ../src/config/Main_Board_Rev_C/peripheral/coretimer/plib_coretimer.c ../src/config/Main_Board_Rev_C/peripheral/ddr/plib_ddr.c ../src/config/Main_Board_Rev_C/peripheral/dmac/plib_dmac.c ../src/config/Main_Board_Rev_C/peripheral/evic/plib_evic.c ../src/config/Main_Board_Rev_C/peripheral/gpio/plib_gpio.c ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp1.c ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp3.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr4.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr2.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr3.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr9.c ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart5.c ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart6.c ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart3.c ../src/config/Main_Board_Rev_C/stdio/xc32_monitor.c ../src/config/Main_Board_Rev_C/system/cache/sys_cache.c ../src/config/Main_Board_Rev_C/system/dma/sys_dma.c ../src/config/Main_Board_Rev_C/system/input/sys_input.c ../src/config/Main_Board_Rev_C/system/input/sys_input_listener.c ../src/config/Main_Board_Rev_C/system/int/src/sys_int.c ../src/config/Main_Board_Rev_C/system/time/src/sys_time.c ../src/config/Main_Board_Rev_C/initialization.c ../src/config/Main_Board_Rev_C/interrupts.c ../src/config/Main_Board_Rev_C/exceptions.c ../src/config/Main_Board_Rev_C/tasks.c ../src/drv_camera_sccb.c ../src/drv_camera_ovm7692.c ../src/drv_led_pca9530.c ../src/debug.c ../src/drv_i2c2.c ../src/drv_piezo.c ../src/message_exchange.c ../src/Drivers/delay.c ../src/settings.c ../src/device_settings_screen.c ../src/camera_settings_screen.c ../src/maths_library.c ../src/scan.c ../src/app_function.c ../src/app_ui_state.c ../src/main_menu.c ../src/display_settings_screen.c ../src/pic_comms.c ../src/drv_display_ST7701S.c ../src/pic24_comms.c ../src/drv_i2c3.c ../src/drv_touch_cst130.c ../src/power_management.c ../src/main.c ../src/app.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/589521824/libnano2D_hal.o ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o ${OBJECTDIR}/_ext/1122095876/plib_glcd.o ${OBJECTDIR}/_ext/101205154/gfx.o ${OBJECTDIR}/_ext/101205154/gfx_color.o ${OBJECTDIR}/_ext/101205154/gfx_context.o ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o ${OBJECTDIR}/_ext/101205154/gfx_display.o ${OBJECTDIR}/_ext/101205154/gfx_display_def.o ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o ${OBJECTDIR}/_ext/101205154/gfx_get.o ${OBJECTDIR}/_ext/101205154/gfx_interface.o ${OBJECTDIR}/_ext/101205154/gfx_layer.o ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o ${OBJECTDIR}/_ext/101205154/gfx_rect.o ${OBJECTDIR}/_ext/101205154/gfx_util.o ${OBJECTDIR}/_ext/101205154/gfx_set.o ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o ${OBJECTDIR}/_ext/101205154/gfx_color_value.o ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o ${OBJECTDIR}/_ext/101205154/gfx_math.o ${OBJECTDIR}/_ext/624871420/libaria_harmony.o ${OBJECTDIR}/_ext/624871420/libaria_init.o ${OBJECTDIR}/_ext/1481330343/libaria.o ${OBJECTDIR}/_ext/1481330343/libaria_array.o ${OBJECTDIR}/_ext/1481330343/libaria_context.o ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o ${OBJECTDIR}/_ext/1481330343/libaria_draw.o ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o ${OBJECTDIR}/_ext/1481330343/libaria_event.o ${OBJECTDIR}/_ext/1481330343/libaria_input.o ${OBJECTDIR}/_ext/1481330343/libaria_layer.o ${OBJECTDIR}/_ext/1481330343/libaria_list.o ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o ${OBJECTDIR}/_ext/1481330343/libaria_screen.o ${OBJECTDIR}/_ext/1481330343/libaria_string.o ${OBJECTDIR}/_ext/1481330343/libaria_utils.o ${OBJECTDIR}/_ext/1481330343/libaria_widget.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o ${OBJECTDIR}/_ext/624871420/libaria_events.o ${OBJECTDIR}/_ext/624871420/libaria_macros.o ${OBJECTDIR}/_ext/408764847/lodepng.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_image.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o ${OBJECTDIR}/_ext/1634538748/gfxu_string.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o ${OBJECTDIR}/_ext/1447700229/gfx_assets.o ${OBJECTDIR}/_ext/1194195235/plib_cache.o ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o ${OBJECTDIR}/_ext/635879171/plib_clk.o ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o ${OBJECTDIR}/_ext/635879891/plib_ddr.o ${OBJECTDIR}/_ext/1762551638/plib_dmac.o ${OBJECTDIR}/_ext/1762512950/plib_evic.o ${OBJECTDIR}/_ext/1762459122/plib_gpio.o ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o ${OBJECTDIR}/_ext/635895546/plib_tmr4.o ${OBJECTDIR}/_ext/635895546/plib_tmr2.o ${OBJECTDIR}/_ext/635895546/plib_tmr3.o ${OBJECTDIR}/_ext/635895546/plib_tmr9.o ${OBJECTDIR}/_ext/1762056179/plib_uart5.o ${OBJECTDIR}/_ext/1762056179/plib_uart6.o ${OBJECTDIR}/_ext/1762056179/plib_uart3.o ${OBJECTDIR}/_ext/318000363/xc32_monitor.o ${OBJECTDIR}/_ext/1120703082/sys_cache.o ${OBJECTDIR}/_ext/1335146508/sys_dma.o ${OBJECTDIR}/_ext/1114761762/sys_input.o ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o ${OBJECTDIR}/_ext/1837585192/sys_int.o ${OBJECTDIR}/_ext/565369102/sys_time.o ${OBJECTDIR}/_ext/1593671781/initialization.o ${OBJECTDIR}/_ext/1593671781/interrupts.o ${OBJECTDIR}/_ext/1593671781/exceptions.o ${OBJECTDIR}/_ext/1593671781/tasks.o ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o ${OBJECTDIR}/_ext/1360937237/drv_piezo.o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ${OBJECTDIR}/_ext/990863823/delay.o ${OBJECTDIR}/_ext/1360937237/settings.o ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o ${OBJECTDIR}/_ext/1360937237/maths_library.o ${OBJECTDIR}/_ext/1360937237/scan.o ${OBJECTDIR}/_ext/1360937237/app_function.o ${OBJECTDIR}/_ext/1360937237/app_ui_state.o ${OBJECTDIR}/_ext/1360937237/main_menu.o ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o ${OBJECTDIR}/_ext/1360937237/pic24_comms.o ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o ${OBJECTDIR}/_ext/1360937237/power_management.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/589521824/libnano2D_hal.o.d ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o.d ${OBJECTDIR}/_ext/1122095876/plib_glcd.o.d ${OBJECTDIR}/_ext/101205154/gfx.o.d ${OBJECTDIR}/_ext/101205154/gfx_color.o.d ${OBJECTDIR}/_ext/101205154/gfx_context.o.d ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o.d ${OBJECTDIR}/_ext/101205154/gfx_display.o.d ${OBJECTDIR}/_ext/101205154/gfx_display_def.o.d ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o.d ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o.d ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o.d ${OBJECTDIR}/_ext/101205154/gfx_get.o.d ${OBJECTDIR}/_ext/101205154/gfx_interface.o.d ${OBJECTDIR}/_ext/101205154/gfx_layer.o.d ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o.d ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o.d ${OBJECTDIR}/_ext/101205154/gfx_rect.o.d ${OBJECTDIR}/_ext/101205154/gfx_util.o.d ${OBJECTDIR}/_ext/101205154/gfx_set.o.d ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o.d ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o.d ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o.d ${OBJECTDIR}/_ext/101205154/gfx_color_value.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o.d ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o.d ${OBJECTDIR}/_ext/101205154/gfx_math.o.d ${OBJECTDIR}/_ext/624871420/libaria_harmony.o.d ${OBJECTDIR}/_ext/624871420/libaria_init.o.d ${OBJECTDIR}/_ext/1481330343/libaria.o.d ${OBJECTDIR}/_ext/1481330343/libaria_array.o.d ${OBJECTDIR}/_ext/1481330343/libaria_context.o.d ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o.d ${OBJECTDIR}/_ext/1481330343/libaria_draw.o.d ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o.d ${OBJECTDIR}/_ext/1481330343/libaria_event.o.d ${OBJECTDIR}/_ext/1481330343/libaria_input.o.d ${OBJECTDIR}/_ext/1481330343/libaria_layer.o.d ${OBJECTDIR}/_ext/1481330343/libaria_list.o.d ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o.d ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o.d ${OBJECTDIR}/_ext/1481330343/libaria_screen.o.d ${OBJECTDIR}/_ext/1481330343/libaria_string.o.d ${OBJECTDIR}/_ext/1481330343/libaria_utils.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o.d ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o.d ${OBJECTDIR}/_ext/624871420/libaria_events.o.d ${OBJECTDIR}/_ext/624871420/libaria_macros.o.d ${OBJECTDIR}/_ext/408764847/lodepng.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_string.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o.d ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o.d ${OBJECTDIR}/_ext/1447700229/gfx_assets.o.d ${OBJECTDIR}/_ext/1194195235/plib_cache.o.d ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.d ${OBJECTDIR}/_ext/635879171/plib_clk.o.d ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o.d ${OBJECTDIR}/_ext/635879891/plib_ddr.o.d ${OBJECTDIR}/_ext/1762551638/plib_dmac.o.d ${OBJECTDIR}/_ext/1762512950/plib_evic.o.d ${OBJECTDIR}/_ext/1762459122/plib_gpio.o.d ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o.d ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o.d ${OBJECTDIR}/_ext/635895546/plib_tmr4.o.d ${OBJECTDIR}/_ext/635895546/plib_tmr2.o.d ${OBJECTDIR}/_ext/635895546/plib_tmr3.o.d ${OBJECTDIR}/_ext/635895546/plib_tmr9.o.d ${OBJECTDIR}/_ext/1762056179/plib_uart5.o.d ${OBJECTDIR}/_ext/1762056179/plib_uart6.o.d ${OBJECTDIR}/_ext/1762056179/plib_uart3.o.d ${OBJECTDIR}/_ext/318000363/xc32_monitor.o.d ${OBJECTDIR}/_ext/1120703082/sys_cache.o.d ${OBJECTDIR}/_ext/1335146508/sys_dma.o.d ${OBJECTDIR}/_ext/1114761762/sys_input.o.d ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o.d ${OBJECTDIR}/_ext/1837585192/sys_int.o.d ${OBJECTDIR}/_ext/565369102/sys_time.o.d ${OBJECTDIR}/_ext/1593671781/initialization.o.d ${OBJECTDIR}/_ext/1593671781/interrupts.o.d ${OBJECTDIR}/_ext/1593671781/exceptions.o.d ${OBJECTDIR}/_ext/1593671781/tasks.o.d ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o.d ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o.d ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o.d ${OBJECTDIR}/_ext/1360937237/debug.o.d ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o.d ${OBJECTDIR}/_ext/1360937237/drv_piezo.o.d ${OBJECTDIR}/_ext/1360937237/message_exchange.o.d ${OBJECTDIR}/_ext/990863823/delay.o.d ${OBJECTDIR}/_ext/1360937237/settings.o.d ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o.d ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o.d ${OBJECTDIR}/_ext/1360937237/maths_library.o.d ${OBJECTDIR}/_ext/1360937237/scan.o.d ${OBJECTDIR}/_ext/1360937237/app_function.o.d ${OBJECTDIR}/_ext/1360937237/app_ui_state.o.d ${OBJECTDIR}/_ext/1360937237/main_menu.o.d ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o.d ${OBJECTDIR}/_ext/1360937237/pic_comms.o.d ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o.d ${OBJECTDIR}/_ext/1360937237/pic24_comms.o.d ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o.d ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o.d ${OBJECTDIR}/_ext/1360937237/power_management.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/589521824/libnano2D_hal.o ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o ${OBJECTDIR}/_ext/1122095876/plib_glcd.o ${OBJECTDIR}/_ext/101205154/gfx.o ${OBJECTDIR}/_ext/101205154/gfx_color.o ${OBJECTDIR}/_ext/101205154/gfx_context.o ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o ${OBJECTDIR}/_ext/101205154/gfx_display.o ${OBJECTDIR}/_ext/101205154/gfx_display_def.o ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o ${OBJECTDIR}/_ext/101205154/gfx_get.o ${OBJECTDIR}/_ext/101205154/gfx_interface.o ${OBJECTDIR}/_ext/101205154/gfx_layer.o ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o ${OBJECTDIR}/_ext/101205154/gfx_rect.o ${OBJECTDIR}/_ext/101205154/gfx_util.o ${OBJECTDIR}/_ext/101205154/gfx_set.o ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o ${OBJECTDIR}/_ext/101205154/gfx_color_value.o ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o ${OBJECTDIR}/_ext/101205154/gfx_math.o ${OBJECTDIR}/_ext/624871420/libaria_harmony.o ${OBJECTDIR}/_ext/624871420/libaria_init.o ${OBJECTDIR}/_ext/1481330343/libaria.o ${OBJECTDIR}/_ext/1481330343/libaria_array.o ${OBJECTDIR}/_ext/1481330343/libaria_context.o ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o ${OBJECTDIR}/_ext/1481330343/libaria_draw.o ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o ${OBJECTDIR}/_ext/1481330343/libaria_event.o ${OBJECTDIR}/_ext/1481330343/libaria_input.o ${OBJECTDIR}/_ext/1481330343/libaria_layer.o ${OBJECTDIR}/_ext/1481330343/libaria_list.o ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o ${OBJECTDIR}/_ext/1481330343/libaria_screen.o ${OBJECTDIR}/_ext/1481330343/libaria_string.o ${OBJECTDIR}/_ext/1481330343/libaria_utils.o ${OBJECTDIR}/_ext/1481330343/libaria_widget.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o ${OBJECTDIR}/_ext/624871420/libaria_events.o ${OBJECTDIR}/_ext/624871420/libaria_macros.o ${OBJECTDIR}/_ext/408764847/lodepng.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_image.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o ${OBJECTDIR}/_ext/1634538748/gfxu_string.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o ${OBJECTDIR}/_ext/1447700229/gfx_assets.o ${OBJECTDIR}/_ext/1194195235/plib_cache.o ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o ${OBJECTDIR}/_ext/635879171/plib_clk.o ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o ${OBJECTDIR}/_ext/635879891/plib_ddr.o ${OBJECTDIR}/_ext/1762551638/plib_dmac.o ${OBJECTDIR}/_ext/1762512950/plib_evic.o ${OBJECTDIR}/_ext/1762459122/plib_gpio.o ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o ${OBJECTDIR}/_ext/635895546/plib_tmr4.o ${OBJECTDIR}/_ext/635895546/plib_tmr2.o ${OBJECTDIR}/_ext/635895546/plib_tmr3.o ${OBJECTDIR}/_ext/635895546/plib_tmr9.o ${OBJECTDIR}/_ext/1762056179/plib_uart5.o ${OBJECTDIR}/_ext/1762056179/plib_uart6.o ${OBJECTDIR}/_ext/1762056179/plib_uart3.o ${OBJECTDIR}/_ext/318000363/xc32_monitor.o ${OBJECTDIR}/_ext/1120703082/sys_cache.o ${OBJECTDIR}/_ext/1335146508/sys_dma.o ${OBJECTDIR}/_ext/1114761762/sys_input.o ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o ${OBJECTDIR}/_ext/1837585192/sys_int.o ${OBJECTDIR}/_ext/565369102/sys_time.o ${OBJECTDIR}/_ext/1593671781/initialization.o ${OBJECTDIR}/_ext/1593671781/interrupts.o ${OBJECTDIR}/_ext/1593671781/exceptions.o ${OBJECTDIR}/_ext/1593671781/tasks.o ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o ${OBJECTDIR}/_ext/1360937237/drv_piezo.o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ${OBJECTDIR}/_ext/990863823/delay.o ${OBJECTDIR}/_ext/1360937237/settings.o ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o ${OBJECTDIR}/_ext/1360937237/maths_library.o ${OBJECTDIR}/_ext/1360937237/scan.o ${OBJECTDIR}/_ext/1360937237/app_function.o ${OBJECTDIR}/_ext/1360937237/app_ui_state.o ${OBJECTDIR}/_ext/1360937237/main_menu.o ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o ${OBJECTDIR}/_ext/1360937237/pic24_comms.o ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o ${OBJECTDIR}/_ext/1360937237/power_management.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app.o

# Source Files
SOURCEFILES=../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/libnano2D_hal.c ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/drv_gfx_glcd.c ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/plib_glcd.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_context.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_default_impl.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display_def.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_interface.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_def.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_def.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_get.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_interface.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_layer.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_pixel_buffer.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_interface.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_rect.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_util.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_set.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_blend.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_convert.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_lerp.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_value.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_arc.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_blit.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_circle.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_ellipse.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_line.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_pixel.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_rect.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_stretchblit.c ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_math.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_harmony.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_init.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_array.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context_paint.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_draw.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_editwidget.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_event.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_input.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_layer.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_list.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_rectarray.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_scheme.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_screen.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_string.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_utils.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic_common.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_radiobutton_group.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window.c ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window_skin_classic.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_events.c ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_macros.c ../src/config/Main_Board_Rev_C/gfx/third_party/src/lodepng/lodepng.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_utils.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_palette.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_stringbuffer_external.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_internal.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_query.c ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_utils.c ../src/config/Main_Board_Rev_C/gfx/gfx_assets.c ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache.c ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache_pic32mz.S ../src/config/Main_Board_Rev_C/peripheral/clk/plib_clk.c ../src/config/Main_Board_Rev_C/peripheral/coretimer/plib_coretimer.c ../src/config/Main_Board_Rev_C/peripheral/ddr/plib_ddr.c ../src/config/Main_Board_Rev_C/peripheral/dmac/plib_dmac.c ../src/config/Main_Board_Rev_C/peripheral/evic/plib_evic.c ../src/config/Main_Board_Rev_C/peripheral/gpio/plib_gpio.c ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp1.c ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp3.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr4.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr2.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr3.c ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr9.c ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart5.c ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart6.c ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart3.c ../src/config/Main_Board_Rev_C/stdio/xc32_monitor.c ../src/config/Main_Board_Rev_C/system/cache/sys_cache.c ../src/config/Main_Board_Rev_C/system/dma/sys_dma.c ../src/config/Main_Board_Rev_C/system/input/sys_input.c ../src/config/Main_Board_Rev_C/system/input/sys_input_listener.c ../src/config/Main_Board_Rev_C/system/int/src/sys_int.c ../src/config/Main_Board_Rev_C/system/time/src/sys_time.c ../src/config/Main_Board_Rev_C/initialization.c ../src/config/Main_Board_Rev_C/interrupts.c ../src/config/Main_Board_Rev_C/exceptions.c ../src/config/Main_Board_Rev_C/tasks.c ../src/drv_camera_sccb.c ../src/drv_camera_ovm7692.c ../src/drv_led_pca9530.c ../src/debug.c ../src/drv_i2c2.c ../src/drv_piezo.c ../src/message_exchange.c ../src/Drivers/delay.c ../src/settings.c ../src/device_settings_screen.c ../src/camera_settings_screen.c ../src/maths_library.c ../src/scan.c ../src/app_function.c ../src/app_ui_state.c ../src/main_menu.c ../src/display_settings_screen.c ../src/pic_comms.c ../src/drv_display_ST7701S.c ../src/pic24_comms.c ../src/drv_i2c3.c ../src/drv_touch_cst130.c ../src/power_management.c ../src/main.c ../src/app.c



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
	${MAKE}  -f nbproject/Makefile-Main_Board_Rev_C.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2064DAR169
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o: ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache_pic32mz.S  .generated_files/d90f0835ba6bc98e43b84061a2100e033cc8aaf.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1194195235" 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache_pic32mz.S  -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o: ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache_pic32mz.S  .generated_files/b6cdb0ba0fcd90ca2b611b4ef748cb89ab8f6cc0.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1194195235" 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache_pic32mz.S  -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.asm.d",--gdwarf-2 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/1194195235/plib_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/589521824/libnano2D_hal.o: ../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/libnano2D_hal.c  .generated_files/85392435e5d8e615f0e26859acad0ea3951e894c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/589521824" 
	@${RM} ${OBJECTDIR}/_ext/589521824/libnano2D_hal.o.d 
	@${RM} ${OBJECTDIR}/_ext/589521824/libnano2D_hal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/589521824/libnano2D_hal.o.d" -o ${OBJECTDIR}/_ext/589521824/libnano2D_hal.o ../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/libnano2D_hal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o: ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/drv_gfx_glcd.c  .generated_files/269923aed7655f88054e50567284f9255601d40d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1122095876" 
	@${RM} ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o.d" -o ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/drv_gfx_glcd.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1122095876/plib_glcd.o: ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/plib_glcd.c  .generated_files/35a3af06a7850b853839b24f5118b77f1e3581fd.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1122095876" 
	@${RM} ${OBJECTDIR}/_ext/1122095876/plib_glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1122095876/plib_glcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1122095876/plib_glcd.o.d" -o ${OBJECTDIR}/_ext/1122095876/plib_glcd.o ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/plib_glcd.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx.c  .generated_files/c94b91b9f851857c2d814a2d6735a5e3ffcc61ab.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color.c  .generated_files/bccf09458e7f9019b722de6381fc3109d1f451dd.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_context.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_context.c  .generated_files/4ffe6fde2861348ccaf7bcbbea42342e68215531.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_context.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_context.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_context.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_context.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_context.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_default_impl.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_default_impl.c  .generated_files/1e710dcc58f570ce14de155b70e886fe448a18fd.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_default_impl.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_default_impl.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_display.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display.c  .generated_files/a24be4fc2e6fc082a230dc6aa85b3a99bad8eaf0.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_display.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_display.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_display_def.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display_def.c  .generated_files/67813dec33014b1303597c7ae72436458b8c7e32.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display_def.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display_def.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_display_def.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_display_def.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display_def.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_interface.c  .generated_files/f188251e25aca2cefbf372e1100f5dff37f1b25c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_interface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_driver_def.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_def.c  .generated_files/78388bf96a947720dd5f9118ae355c0a34855d74.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_driver_def.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_def.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_processor_def.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_def.c  .generated_files/f2ca29e029c1b37788d4ad001446ff9f091899e1.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_processor_def.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_def.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_get.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_get.c  .generated_files/8749676e4e62cfc7c3407f0b3209b2bb7cc90a47.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_get.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_get.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_get.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_get.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_get.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_interface.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_interface.c  .generated_files/3673c01b8ce6de56abf9a8bc61146b7a024b3c39.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_interface.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_interface.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_interface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_layer.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_layer.c  .generated_files/40e304392836dc1322a4b650de2b859757aeb475.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_layer.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_layer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_layer.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_layer.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_layer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_pixel_buffer.c  .generated_files/2f6617feec25965d9fe2dbcbe231513d2ab1ab3a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_pixel_buffer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_interface.c  .generated_files/df00de4022bfe37b02a8a318279c908b3f3ad1b2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_interface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_rect.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_rect.c  .generated_files/b1157fe7431b8da6061f3098cede6f1efcc95ce5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_rect.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_rect.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_rect.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_rect.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_rect.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_util.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_util.c  .generated_files/67dd455e8c8b225ffb82bd2964c5a83fcd0fa5a6.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_util.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_util.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_util.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_util.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_util.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_set.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_set.c  .generated_files/5f44ab95fd168e38bf21f195db17355f1fa7108e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_set.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_set.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_set.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_set.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_set.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_blend.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_blend.c  .generated_files/4ae3b1414f43971bd83ec79b38f74f4d6bf2608a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_blend.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_blend.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_convert.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_convert.c  .generated_files/ebe1457dd6b2e4272f336a3974e1b132c9dcf35f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_convert.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_convert.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_lerp.c  .generated_files/459556363985d1835974e90c4d34de8dfecbc918.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_lerp.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_value.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_value.c  .generated_files/aa75dd8dfabcc6506054773227ecc416083fde3a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_value.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_value.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_value.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_value.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_value.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_arc.c  .generated_files/8435d01af66215fcc294e0f1db0fcc3cba51ec4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_arc.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_blit.c  .generated_files/d504a08f2756746f4e1c569eb04c3b2b1eab3fd5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_blit.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_circle.c  .generated_files/eb3df5118d90809fbcf1c6550efa21b2380d6433.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_circle.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_ellipse.c  .generated_files/f0781150b28e26ddb6e8a6f1aaa34467477f5948.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_ellipse.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_line.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_line.c  .generated_files/47665cc218d5e7738bb690598a4e17ddb751c44c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_line.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_line.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_pixel.c  .generated_files/3b4b8bfa26c1b085544fcab2dd7947358b2f982b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_pixel.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_rect.c  .generated_files/f9576038b2da6f73eb873b826e5bf2f6e9b3e968.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_rect.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_stretchblit.c  .generated_files/493d4f08c622dd2cde29339125ae6c03b953e54a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_stretchblit.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_math.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_math.c  .generated_files/f2f1d5fa8ed7912fc3b38bbc4ccdce09dba26ef8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_math.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_math.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_math.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_math.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_harmony.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_harmony.c  .generated_files/bf7c091313c4f86e9b1034f31c8b8170dc603ebc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_harmony.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_harmony.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_harmony.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_harmony.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_harmony.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_init.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_init.c  .generated_files/5e021aef5cb59671029ba3acf12d72969f8a7920.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_init.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_init.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_init.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria.c  .generated_files/5d60119deab4add80ab49c978a076dff3614f3c9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_array.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_array.c  .generated_files/41fffa79049cb069a6f2e594a76e78f28976af68.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_array.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_array.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_array.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_array.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_array.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_context.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context.c  .generated_files/f1d0fe3cc56113836764c0e060bb15f9faa50924.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_context.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_context.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context_paint.c  .generated_files/22848e6a1df973b71a82394f2294b44e7e030c0e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context_paint.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_draw.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_draw.c  .generated_files/4e9b7aa3fb5f58326ca4c293af5902b30a5e044b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_draw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_draw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_draw.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_draw.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_draw.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_editwidget.c  .generated_files/9c79b98dc4edd72073e5d6cd5617a8d206a78b1c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_editwidget.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_event.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_event.c  .generated_files/8b4b38c9abd53b194e1822232e43f3d8ac8c6f1d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_event.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_event.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_event.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_event.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_event.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_input.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_input.c  .generated_files/87069335be6f396114230238f9ad4b031590e243.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_input.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_input.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_input.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_input.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_input.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_layer.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_layer.c  .generated_files/e0ce83f76c72997e4294118458fde0f609ad37b1.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_layer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_layer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_layer.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_layer.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_layer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_list.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_list.c  .generated_files/c450ddc91b93ed392f334eac54d23f56ed7fe8cc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_list.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_list.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_list.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_rectarray.c  .generated_files/e52c96b1e73f885a16041c4816a044bdaa4220b3.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_rectarray.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_scheme.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_scheme.c  .generated_files/c1ed8637a3b6af4c3c15115f6a53c261dcc3a7cc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_scheme.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_scheme.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_screen.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_screen.c  .generated_files/dcebe29c9ca55d7423598621d419ea15e11bdda6.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_screen.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_screen.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_string.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_string.c  .generated_files/fbf98c7694912427b472a5e576cdc096af1ccf27.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_string.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_string.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_string.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_string.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_utils.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_utils.c  .generated_files/e9cf6e4f92bbb2eec72ffacabbe196991a57dc42.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_utils.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_utils.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_utils.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget.c  .generated_files/c11dbb3dc46ffead4e6d3b1ae2c4c9c63a7c0cc7.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic.c  .generated_files/1ddc04a6910937e6fd26e0c3f5103c5639f7624d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic_common.c  .generated_files/15ef9838fc277580ccc72b3f0dadec70c5046642.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic_common.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc.c  .generated_files/3cd38b3f19e8613e73dbac424e18a339bcc97047.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc_skin_classic.c  .generated_files/b951531195ab3a21282550e3b33f1052c6f52019.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph.c  .generated_files/3b2873d7e08482bbc6c0d55c9ab4d01022fc8598.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph_skin_classic.c  .generated_files/11ca482fbc7200cb1f4f742197da0fa68ab1d63a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button.c  .generated_files/3b23c86e4eaa0ba84674709903d942d5c70082c8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button_skin_classic.c  .generated_files/e24f6a95eb85fb92cfeea5c71c4d98a16ec404a2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox.c  .generated_files/91a54821d7c0fc6777608df8d06c87f0fb9fa280.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox_skin_classic.c  .generated_files/c29e1e2473344b07371721ad562c88a2e5b4ee24.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle.c  .generated_files/a2cb2e71e986ee05cf55f32426cc747dd83ade4f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle_skin_classic.c  .generated_files/7019d7941f79c66334f1524d358e73746e6fb713.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge.c  .generated_files/1effe486f5ece8e738164f831ef2aa374ee1715.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge_skin_classic.c  .generated_files/88ec99cb0a343f223994f4f597f05746f4071744.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider.c  .generated_files/acce00d5f1925c72fe8663de90f210d03dfba44c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider_skin_classic.c  .generated_files/9e28362a6f14caef935c5aa3dc300058a2f69c2b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface.c  .generated_files/bf7c6b886d62ee3afdc34020f403a95ef145dbf7.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface_skin_classic.c  .generated_files/2d14eb5def25722dbc30b8796fc9d4cd3776f2ad.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient.c  .generated_files/379762622a164b937cf406fd1b9d6c0d8d5f0737.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient_skin_classic.c  .generated_files/6b89848fb5fa27e0210ba56c17e33dc0e5b7758c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox.c  .generated_files/674f487c131c9068a80783ba4a82ebd5b21e23ed.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox_skin_classic.c  .generated_files/befd4254383968319c5b83f55e8503b1146e6862.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image.c  .generated_files/57383feab87b2e81b62b6c223161453697282ee9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image_skin_classic.c  .generated_files/bdd85e03a1e45896151345d50284d62bd48abda8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus.c  .generated_files/4eed6d120ea277889abdf1bd99073cec1e40fabc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus_skin_classic.c  .generated_files/1f26d0ecc7dc20adafc55028d1f0a749dcdad064.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence.c  .generated_files/9742adac266cc90a19f4005a94f23a965d8ff271.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence_skin_classic.c  .generated_files/a20ec544c9d290aa8f3069b974027037170ecb76.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad.c  .generated_files/290f6879d7fd8e4f6a052a5e080481d9c12af0aa.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad_skin_classic.c  .generated_files/36f61b077858bab71e90e715a681c34022acc112.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label.c  .generated_files/50dc1768c783c7fc8dd0b6628de1b00f513f3d76.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label_skin_classic.c  .generated_files/bcfb7818df9b3013d92b81b8bf6881ce00703f27.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line.c  .generated_files/874d4aaadb3e5a997f2c9ab4418cc8c930657b69.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_skin_classic.c  .generated_files/ca645ddb4457fcbf53cee454042474f7175ca454.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph.c  .generated_files/81968cc8e43924a1670fb7b07d4ba1fd6da3a56d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph_skin_classic.c  .generated_files/9da4b95fb97b1cb5ca46c7d6287509644c7d08b5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list.c  .generated_files/29e698df89a4b9782daf884939d56db5b8123b75.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list_skin_classic.c  .generated_files/b82892dd21d1cc8364ef4ef90e51cb29d49b8152.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel.c  .generated_files/92acfb0352deefa57688b5a956988d8fafc6c47d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel_skin_classic.c  .generated_files/322e2bfe7d31f1277617a535fa9bf5f65be7ec2d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart.c  .generated_files/638c4a11c30a447cc9eedc344214718d94dbba03.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart_skin_classic.c  .generated_files/bd5dfbf15e45bbb2aaefcb0c359e1eb1930bfed8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar.c  .generated_files/551a054679b428e192540aec2415f797aa776fe3.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar_skin_classic.c  .generated_files/df79b38a2bdd8508c2c77a3b150327f2d494be8c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu.c  .generated_files/b38ef02550985a16a9b4ec45fb5df56f05085ac1.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu_skin_classic.c  .generated_files/52bad0c96e2d0050f55255dacd9e2100f3a747c4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton.c  .generated_files/e025ffc041df2a2fccdaeededfc325c18688831c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton_skin_classic.c  .generated_files/f3110b1900123431171fedb9731879869d92697f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_radiobutton_group.c  .generated_files/93d1a021f4c149b46eccd0fa59010bd364b221db.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_radiobutton_group.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle.c  .generated_files/e827283ff759055deaeb35da96c5e2b8de53678b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle_skin_classic.c  .generated_files/c96ae697d32b64534a613224255d36fbcc6c2143.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar.c  .generated_files/7ef57b45e14f019bbfe4db4e6599e7d3d0ffd238.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar_skin_classic.c  .generated_files/2452d3edb31895093ab2c191598280434e02a184.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider.c  .generated_files/44463eac00a713e465e82ee19e8c8917fb112564.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider_skin_classic.c  .generated_files/7006df30359dee1ad2fd68b1efacb2bfcbd5e3e4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield.c  .generated_files/f2726cf2eb3f513fbebf4a6add822b0fad4cce5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield_skin_classic.c  .generated_files/a49640615c723a6af315c7c20640c9f1501d8029.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest.c  .generated_files/97fc52c90561649073a852e00f69cd208164fbec.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest_skin_classic.c  .generated_files/9c2632072a3b3b338bd13346dfc725942dc73de3.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window.c  .generated_files/4a06221a14d2c2a0c2f2d8c0ee0751f2442a1a66.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window_skin_classic.c  .generated_files/24670227d11e2b264ccf4567a01e0ed194767c9c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_events.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_events.c  .generated_files/9a0643926bfb710dfc1e555a14948a67ae72fd2e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_events.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_events.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_events.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_events.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_macros.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_macros.c  .generated_files/98f21bdbd30d3b5c2492c0dde1b4bffb67a39a20.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_macros.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_macros.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_macros.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_macros.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_macros.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/408764847/lodepng.o: ../src/config/Main_Board_Rev_C/gfx/third_party/src/lodepng/lodepng.c  .generated_files/57c0cf7971f3f487bf31ede498f230e709be0a70.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/408764847" 
	@${RM} ${OBJECTDIR}/_ext/408764847/lodepng.o.d 
	@${RM} ${OBJECTDIR}/_ext/408764847/lodepng.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/408764847/lodepng.o.d" -o ${OBJECTDIR}/_ext/408764847/lodepng.o ../src/config/Main_Board_Rev_C/gfx/third_party/src/lodepng/lodepng.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_external.c  .generated_files/e72d47d70607b7d87d169765ce57a8c51da4d0b8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_internal.c  .generated_files/c64cb6a2a06885859e87f8fd2c0ce9a8ec643714.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image.c  .generated_files/354d3fdbb700a8235576876b6d265d4c5dda58de.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_external.c  .generated_files/153003765e4ac3da4d3025580db2990d4187461a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_internal.c  .generated_files/145830a270c4370faa9f1228e2c3dcd9485a19c0.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_external.c  .generated_files/32284d735361f1fd13241715ea54277b8079030.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_internal.c  .generated_files/4c5790c8d11644cba007105c6012246ab8fb70de.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_utils.c  .generated_files/1d739902cbf435a2ddd7acff5d60781c0b0f9889.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_utils.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_palette.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_palette.c  .generated_files/cc167b23b2088b93416bd1abf9ca55dd4bb2d71d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_palette.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_palette.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string.c  .generated_files/1c50ded465b15de6b98bd9b94f8d36ba6c64e1a5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_external.c  .generated_files/3d764b4b58412760446005fec615185b485bcd62.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_stringbuffer_external.c  .generated_files/f0d2725999710891df1bda64b878ed66be064733.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_stringbuffer_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_internal.c  .generated_files/f53b0876c2fcf83ad622db9f9cbe4090c9b8930b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_query.c  .generated_files/17cabd7e63cade5f74f8aac69595f2caf5cd7943.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_query.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_utils.c  .generated_files/83899c7ead35603d3511210f8a3644891fa748e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_utils.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1447700229/gfx_assets.o: ../src/config/Main_Board_Rev_C/gfx/gfx_assets.c  .generated_files/4757933675f65afef9b73fd97501be10ba48cf2d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1447700229" 
	@${RM} ${OBJECTDIR}/_ext/1447700229/gfx_assets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1447700229/gfx_assets.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1447700229/gfx_assets.o.d" -o ${OBJECTDIR}/_ext/1447700229/gfx_assets.o ../src/config/Main_Board_Rev_C/gfx/gfx_assets.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1194195235/plib_cache.o: ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache.c  .generated_files/5fa90160e75a1e6e9040cd6b2551d794cf7c7712.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1194195235" 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1194195235/plib_cache.o.d" -o ${OBJECTDIR}/_ext/1194195235/plib_cache.o ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635879171/plib_clk.o: ../src/config/Main_Board_Rev_C/peripheral/clk/plib_clk.c  .generated_files/fe86fe51a5ab5bf6cd1f2cc1bf934d01aa5580dc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635879171" 
	@${RM} ${OBJECTDIR}/_ext/635879171/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/635879171/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635879171/plib_clk.o.d" -o ${OBJECTDIR}/_ext/635879171/plib_clk.o ../src/config/Main_Board_Rev_C/peripheral/clk/plib_clk.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1663751207/plib_coretimer.o: ../src/config/Main_Board_Rev_C/peripheral/coretimer/plib_coretimer.c  .generated_files/6c7cdd88c54a0dbd8754023fd6a456f7cb3f950b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1663751207" 
	@${RM} ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1663751207/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o ../src/config/Main_Board_Rev_C/peripheral/coretimer/plib_coretimer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635879891/plib_ddr.o: ../src/config/Main_Board_Rev_C/peripheral/ddr/plib_ddr.c  .generated_files/b6f064a2a3df976cae2562ac7b55a7a881b4969e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635879891" 
	@${RM} ${OBJECTDIR}/_ext/635879891/plib_ddr.o.d 
	@${RM} ${OBJECTDIR}/_ext/635879891/plib_ddr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635879891/plib_ddr.o.d" -o ${OBJECTDIR}/_ext/635879891/plib_ddr.o ../src/config/Main_Board_Rev_C/peripheral/ddr/plib_ddr.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762551638/plib_dmac.o: ../src/config/Main_Board_Rev_C/peripheral/dmac/plib_dmac.c  .generated_files/553a46c6b068b1312b8bbeb4e3b46106b1394755.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762551638" 
	@${RM} ${OBJECTDIR}/_ext/1762551638/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762551638/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762551638/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1762551638/plib_dmac.o ../src/config/Main_Board_Rev_C/peripheral/dmac/plib_dmac.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762512950/plib_evic.o: ../src/config/Main_Board_Rev_C/peripheral/evic/plib_evic.c  .generated_files/21b8479f83d1f09882a32ba87bba49f14dfdebfc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762512950" 
	@${RM} ${OBJECTDIR}/_ext/1762512950/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762512950/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762512950/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1762512950/plib_evic.o ../src/config/Main_Board_Rev_C/peripheral/evic/plib_evic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762459122/plib_gpio.o: ../src/config/Main_Board_Rev_C/peripheral/gpio/plib_gpio.c  .generated_files/ca9555e7f17f5cc1fdd48059b0488c30077fa243.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762459122" 
	@${RM} ${OBJECTDIR}/_ext/1762459122/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762459122/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762459122/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1762459122/plib_gpio.o ../src/config/Main_Board_Rev_C/peripheral/gpio/plib_gpio.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o: ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp1.c  .generated_files/8293213c09c7beb1a5dd6235fa1c350296428da3.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762233162" 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o.d" -o ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp1.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o: ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp3.c  .generated_files/c2ac561839cce32548d7785a3e3fa5ebc2f57276.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762233162" 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o.d" -o ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr4.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr4.c  .generated_files/f57a3c6a0b459450a12904ebc8bcbd6563e10f31.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr4.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr4.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr4.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr4.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr2.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr2.c  .generated_files/505982ee0b5291817794bbdd842da342b6572d94.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr2.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr2.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr3.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr3.c  .generated_files/e9d01bfa4164064af779228701ec19bba7795eef.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr3.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr9.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr9.c  .generated_files/f09077a33d0b97579606bb64063b7aa95d696ba8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr9.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr9.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr9.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr9.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762056179/plib_uart5.o: ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart5.c  .generated_files/7b2e5ae628ec7cf49c16624116031df09c1c74.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762056179" 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762056179/plib_uart5.o.d" -o ${OBJECTDIR}/_ext/1762056179/plib_uart5.o ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart5.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762056179/plib_uart6.o: ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart6.c  .generated_files/7724a9fde4d6490f7ecb8575e51a69161772c0f0.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762056179" 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart6.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762056179/plib_uart6.o.d" -o ${OBJECTDIR}/_ext/1762056179/plib_uart6.o ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart6.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762056179/plib_uart3.o: ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart3.c  .generated_files/83a322df4de97e506d609875dd18699ba1ff14a9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762056179" 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762056179/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/1762056179/plib_uart3.o ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/318000363/xc32_monitor.o: ../src/config/Main_Board_Rev_C/stdio/xc32_monitor.c  .generated_files/642686dda5072c42967bee57526dd1222f4a418e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/318000363" 
	@${RM} ${OBJECTDIR}/_ext/318000363/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/318000363/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/318000363/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/318000363/xc32_monitor.o ../src/config/Main_Board_Rev_C/stdio/xc32_monitor.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1120703082/sys_cache.o: ../src/config/Main_Board_Rev_C/system/cache/sys_cache.c  .generated_files/57261aac968e0a97cde8fab79aadab2d1371ef3f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1120703082" 
	@${RM} ${OBJECTDIR}/_ext/1120703082/sys_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1120703082/sys_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1120703082/sys_cache.o.d" -o ${OBJECTDIR}/_ext/1120703082/sys_cache.o ../src/config/Main_Board_Rev_C/system/cache/sys_cache.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1335146508/sys_dma.o: ../src/config/Main_Board_Rev_C/system/dma/sys_dma.c  .generated_files/50eb9cc766dedc93ab6df29ce3954d0a36b28053.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1335146508" 
	@${RM} ${OBJECTDIR}/_ext/1335146508/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1335146508/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1335146508/sys_dma.o.d" -o ${OBJECTDIR}/_ext/1335146508/sys_dma.o ../src/config/Main_Board_Rev_C/system/dma/sys_dma.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1114761762/sys_input.o: ../src/config/Main_Board_Rev_C/system/input/sys_input.c  .generated_files/71e6dbe009cebf86c487eb17b783c224f71f054f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1114761762" 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input.o.d 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1114761762/sys_input.o.d" -o ${OBJECTDIR}/_ext/1114761762/sys_input.o ../src/config/Main_Board_Rev_C/system/input/sys_input.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1114761762/sys_input_listener.o: ../src/config/Main_Board_Rev_C/system/input/sys_input_listener.c  .generated_files/95b3b751bc6f031f11dc6f9daa210b93b165a19e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1114761762" 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o.d 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1114761762/sys_input_listener.o.d" -o ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o ../src/config/Main_Board_Rev_C/system/input/sys_input_listener.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1837585192/sys_int.o: ../src/config/Main_Board_Rev_C/system/int/src/sys_int.c  .generated_files/ee8af96c4da54903d34e607d1948bab2135b0929.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1837585192" 
	@${RM} ${OBJECTDIR}/_ext/1837585192/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1837585192/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1837585192/sys_int.o.d" -o ${OBJECTDIR}/_ext/1837585192/sys_int.o ../src/config/Main_Board_Rev_C/system/int/src/sys_int.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/565369102/sys_time.o: ../src/config/Main_Board_Rev_C/system/time/src/sys_time.c  .generated_files/536d6b851b35343fc853e44c1354310a6073331.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/565369102" 
	@${RM} ${OBJECTDIR}/_ext/565369102/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/565369102/sys_time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/565369102/sys_time.o.d" -o ${OBJECTDIR}/_ext/565369102/sys_time.o ../src/config/Main_Board_Rev_C/system/time/src/sys_time.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/initialization.o: ../src/config/Main_Board_Rev_C/initialization.c  .generated_files/b53bb1ad8fd119a4f372a982cb52b27fdd723f91.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/initialization.o.d" -o ${OBJECTDIR}/_ext/1593671781/initialization.o ../src/config/Main_Board_Rev_C/initialization.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/interrupts.o: ../src/config/Main_Board_Rev_C/interrupts.c  .generated_files/ecad135866775cff3524045f7a5e3968beea9a70.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/interrupts.o.d" -o ${OBJECTDIR}/_ext/1593671781/interrupts.o ../src/config/Main_Board_Rev_C/interrupts.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/exceptions.o: ../src/config/Main_Board_Rev_C/exceptions.c  .generated_files/f301ab5e72a22a9d8ad95f5655666da2db8639ca.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/exceptions.o.d" -o ${OBJECTDIR}/_ext/1593671781/exceptions.o ../src/config/Main_Board_Rev_C/exceptions.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/tasks.o: ../src/config/Main_Board_Rev_C/tasks.c  .generated_files/cd5a9118de415244f884cab2a129cd352260194e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/tasks.o.d" -o ${OBJECTDIR}/_ext/1593671781/tasks.o ../src/config/Main_Board_Rev_C/tasks.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o: ../src/drv_camera_sccb.c  .generated_files/9a17e72a3055abc49b0d4553bde97d6ccf4db96b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o ../src/drv_camera_sccb.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o: ../src/drv_camera_ovm7692.c  .generated_files/e94ed61ed8ff571798f13a6b572fbb4235538d38.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o ../src/drv_camera_ovm7692.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o: ../src/drv_led_pca9530.c  .generated_files/fe01d1585c9873ecd4d48e8dcc89f58eaf78936.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o ../src/drv_led_pca9530.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  .generated_files/fcd6d641f418a13c4a3c9144b88b140affb59114.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_i2c2.o: ../src/drv_i2c2.c  .generated_files/d6e39acd856c9acd9a58fe2e008142c8ccb5bf83.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_i2c2.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o ../src/drv_i2c2.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_piezo.o: ../src/drv_piezo.c  .generated_files/4aa26dcffbfb2dd7caa6a4cc229065bcb80f130c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_piezo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_piezo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_piezo.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_piezo.o ../src/drv_piezo.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/message_exchange.o: ../src/message_exchange.c  .generated_files/4cd488b572f7ee138a805f93f2d47107178555ba.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/message_exchange.o.d" -o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ../src/message_exchange.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/990863823/delay.o: ../src/Drivers/delay.c  .generated_files/f1f96b852001cb7155cbdbdca77b10518a199e9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/990863823" 
	@${RM} ${OBJECTDIR}/_ext/990863823/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/990863823/delay.o.d" -o ${OBJECTDIR}/_ext/990863823/delay.o ../src/Drivers/delay.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/settings.o: ../src/settings.c  .generated_files/d07166b79716b4762ec8ba9ae1c5879071707669.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/settings.o.d" -o ${OBJECTDIR}/_ext/1360937237/settings.o ../src/settings.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/device_settings_screen.o: ../src/device_settings_screen.c  .generated_files/35a3348148659230f622be76a9e624d7be75f687.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/device_settings_screen.o.d" -o ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o ../src/device_settings_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o: ../src/camera_settings_screen.c  .generated_files/67f674ecb01422ffe2a58586d64cc8ca1e772485.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o.d" -o ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o ../src/camera_settings_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/maths_library.o: ../src/maths_library.c  .generated_files/2125da70fbdd72be64523c76d64e49f0a5b6699e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/maths_library.o.d" -o ${OBJECTDIR}/_ext/1360937237/maths_library.o ../src/maths_library.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/scan.o: ../src/scan.c  .generated_files/e91f281f8c8aff40b42c6eaab2f9d7ee74cdcc88.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/scan.o.d" -o ${OBJECTDIR}/_ext/1360937237/scan.o ../src/scan.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app_function.o: ../src/app_function.c  .generated_files/ae73e896bb7e9b8561bc88d36478e87f6da23491.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_function.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_function.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_function.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_function.o ../src/app_function.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app_ui_state.o: ../src/app_ui_state.c  .generated_files/4ca81e536edfcc59019ee1d3e36726dcf597061a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_ui_state.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_ui_state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_ui_state.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_ui_state.o ../src/app_ui_state.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main_menu.o: ../src/main_menu.c  .generated_files/1c7ff2a8d4bd0da16977d9e927a353e2190af4c6.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main_menu.o.d" -o ${OBJECTDIR}/_ext/1360937237/main_menu.o ../src/main_menu.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/display_settings_screen.o: ../src/display_settings_screen.c  .generated_files/1c4dffb27e996d87ffcc06ad3d950f0ee7fd23c6.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/display_settings_screen.o.d" -o ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o ../src/display_settings_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pic_comms.o: ../src/pic_comms.c  .generated_files/4cb54a5594c786a7d1cc9f6bdfbb4282db8c1e1e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ../src/pic_comms.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o: ../src/drv_display_ST7701S.c  .generated_files/1c0bef9706aeea74bd5e3efa41e6eb51d46a7ca7.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o ../src/drv_display_ST7701S.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pic24_comms.o: ../src/pic24_comms.c  .generated_files/25c1bf8d1b25a1ff9e1f122ba1ae2219290b359a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic24_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic24_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic24_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/pic24_comms.o ../src/pic24_comms.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_i2c3.o: ../src/drv_i2c3.c  .generated_files/7c2ab0f04973b817ad57b3657a7d1cc2eed80db5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_i2c3.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o ../src/drv_i2c3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o: ../src/drv_touch_cst130.c  .generated_files/60ccd39362b666a4c84223329ab3e29bb5a9f424.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o ../src/drv_touch_cst130.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/power_management.o: ../src/power_management.c  .generated_files/61f559e6c10e81cdc2218019a25eafa601f44b87.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_management.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/power_management.o.d" -o ${OBJECTDIR}/_ext/1360937237/power_management.o ../src/power_management.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/dd468762edd578f46afe538c328dfeae38dc6d58.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/7a4f36731146b46d71cbe3707a9f3e9d015513df.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/589521824/libnano2D_hal.o: ../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/libnano2D_hal.c  .generated_files/7b7ce1ab88bbb0e871a2971ed61976594228e1e5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/589521824" 
	@${RM} ${OBJECTDIR}/_ext/589521824/libnano2D_hal.o.d 
	@${RM} ${OBJECTDIR}/_ext/589521824/libnano2D_hal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/589521824/libnano2D_hal.o.d" -o ${OBJECTDIR}/_ext/589521824/libnano2D_hal.o ../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/libnano2D_hal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o: ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/drv_gfx_glcd.c  .generated_files/abf78be6ef6578d58a852b25e02e564501c8a5e6.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1122095876" 
	@${RM} ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o.d" -o ${OBJECTDIR}/_ext/1122095876/drv_gfx_glcd.o ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/drv_gfx_glcd.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1122095876/plib_glcd.o: ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/plib_glcd.c  .generated_files/dda5c09755163fddfcd79b772e4b83eaa300008e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1122095876" 
	@${RM} ${OBJECTDIR}/_ext/1122095876/plib_glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1122095876/plib_glcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1122095876/plib_glcd.o.d" -o ${OBJECTDIR}/_ext/1122095876/plib_glcd.o ../src/config/Main_Board_Rev_C/gfx/driver/controller/glcd/plib_glcd.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx.c  .generated_files/86ab38a2ff49a791c5d487916c7e7df7ad4adbfe.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color.c  .generated_files/7080b16eb2692331a79c088f7a4fbcb304919296.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_context.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_context.c  .generated_files/c3639713ee8c1b2eb7982f501a72a815a12578f1.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_context.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_context.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_context.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_context.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_context.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_default_impl.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_default_impl.c  .generated_files/5b5c96e4c09d5f1080e6e5890eb88b091f7933d5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_default_impl.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_default_impl.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_default_impl.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_display.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display.c  .generated_files/9f79c1b935d71a9cb4a1d76d6803027d08a68f0b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_display.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_display.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_display_def.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display_def.c  .generated_files/ee349a76c1b0b8314ce92cd51ae37c036c3bd873.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display_def.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_display_def.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_display_def.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_display_def.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_display_def.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_interface.c  .generated_files/6971f0a865d3300ec5f0a333ab4106a267bb1c6f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_driver_interface.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_interface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_driver_def.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_def.c  .generated_files/ac3d56b1b7054bfb471671ae2bc1aff0bdb0ae51.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_driver_def.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_driver_def.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_driver_def.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_processor_def.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_def.c  .generated_files/27168afad85a28b0d89dc61b6e7fea2c555f85a3.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_processor_def.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_processor_def.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_def.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_get.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_get.c  .generated_files/e62b30e00d0e578d4dae6c8bf757e48bdf35c89e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_get.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_get.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_get.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_get.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_get.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_interface.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_interface.c  .generated_files/3ce442214097f5286a74eb5388ec7f45b7df5d1f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_interface.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_interface.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_interface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_layer.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_layer.c  .generated_files/2cb0f97d0640249b35ec55fa555fab8fd3623bb2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_layer.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_layer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_layer.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_layer.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_layer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_pixel_buffer.c  .generated_files/fdaa3351baa00cb556df75cf3541181b9c33a4c2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_pixel_buffer.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_pixel_buffer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_interface.c  .generated_files/1dbcd8d679a3154cc34c0b9985a7eb1ca61ce033.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_processor_interface.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_processor_interface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_rect.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_rect.c  .generated_files/981250a535367b70fa22612ea7c4cece86674b63.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_rect.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_rect.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_rect.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_rect.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_rect.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_util.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_util.c  .generated_files/54572905a0d04b55abb742d472d57c4937870aaf.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_util.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_util.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_util.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_util.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_util.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_set.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_set.c  .generated_files/9aae7747ce7c50dd963d8a58b4fce8f08e999fd2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_set.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_set.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_set.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_set.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_set.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_blend.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_blend.c  .generated_files/37bb7004c8034ff101bd4af192c3f2cddc75418f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_blend.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_blend.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_blend.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_convert.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_convert.c  .generated_files/d1ca0fdee3eafcb4720e997fb766c1d42eacc9c4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_convert.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_convert.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_convert.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_lerp.c  .generated_files/eb853b69d33ea18b00d48f73d9d1ebab13c5676b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_lerp.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_lerp.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_color_value.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_value.c  .generated_files/3baafb512ca778140491e06109f0b9fd47a87680.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_value.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_color_value.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_color_value.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_color_value.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_color_value.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_arc.c  .generated_files/efea237c5c4b4bfe73084855a5cf26345f258bef.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_arc.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_arc.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_blit.c  .generated_files/c60be5e1224c6bfbf2f4af29d65c9d74df9002ba.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_blit.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_blit.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_circle.c  .generated_files/a2ff1c09fc92526438e7dab0c73ad84555bc5aea.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_circle.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_circle.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_ellipse.c  .generated_files/3aafe99ef073b006457279f8973be9c1a8963bd4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_ellipse.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_ellipse.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_line.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_line.c  .generated_files/2c7d16537cc7bc6ef270dd9f18a4d891cd1e0936.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_line.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_line.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_line.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_pixel.c  .generated_files/f2c51a93fc95aac3db28336c1db904365549a73f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_pixel.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_pixel.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_rect.c  .generated_files/5be7eff06c3b7c8d93ae697793a88019ccd17011.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_rect.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_rect.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_stretchblit.c  .generated_files/958ce0e9be3b09183391a9815a00268fad0de881.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_draw_stretchblit.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_draw_stretchblit.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/101205154/gfx_math.o: ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_math.c  .generated_files/75a8e8b9ccbe5c335839e298f7c92ed5e8c334f8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/101205154" 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/101205154/gfx_math.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/101205154/gfx_math.o.d" -o ${OBJECTDIR}/_ext/101205154/gfx_math.o ../src/config/Main_Board_Rev_C/gfx/hal/src/gfx_math.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_harmony.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_harmony.c  .generated_files/6cedf7808e10ed0104b148a635dbcf1d1d395417.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_harmony.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_harmony.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_harmony.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_harmony.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_harmony.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_init.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_init.c  .generated_files/e87e22e3d95c59d856ac72c86e07f6312d462f44.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_init.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_init.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_init.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria.c  .generated_files/1891f97dd96869fdd87c967c1aff121f201f4876.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_array.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_array.c  .generated_files/2e871835d9e6b4ca800375bacc1fa6153c92fe95.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_array.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_array.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_array.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_array.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_array.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_context.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context.c  .generated_files/d23fe8632d8026047dcaec2cf36aef9d58003802.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_context.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_context.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context_paint.c  .generated_files/b66993481cc9cc5bfae1c7ce1e0187b7dc898af7.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_context_paint.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_context_paint.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_draw.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_draw.c  .generated_files/9f4cdeea632fdb1c7818596fb9fbb7e5255753f0.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_draw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_draw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_draw.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_draw.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_draw.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_editwidget.c  .generated_files/ab136cb6df1dd95f3bafbd74b7268ccbec7973d4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_editwidget.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_editwidget.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_event.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_event.c  .generated_files/d451e5d3ea9aa9ffac4cbdac146f48f74f7479ac.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_event.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_event.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_event.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_event.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_event.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_input.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_input.c  .generated_files/cf9db257778aeca20501cd03db5d936323fc09ff.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_input.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_input.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_input.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_input.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_input.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_layer.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_layer.c  .generated_files/2cc3e5902fff561ef1048d9cce44f599c310a155.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_layer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_layer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_layer.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_layer.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_layer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_list.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_list.c  .generated_files/647df5c6aa6da22be15302806145190b8927425e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_list.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_list.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_list.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_rectarray.c  .generated_files/ab3920452d613961faa3b479c642d46ddd00205b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_rectarray.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_rectarray.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_scheme.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_scheme.c  .generated_files/daa56dd545d99a675ac33787a4d09a2f3d7e1425.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_scheme.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_scheme.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_scheme.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_screen.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_screen.c  .generated_files/c7fc60a32b2eee8cdf62dc9d5d8ae42e0f0fbb2f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_screen.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_screen.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_string.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_string.c  .generated_files/8f4ee152adae4b8151d42097ae7df076b5bbebf.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_string.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_string.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_string.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_string.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_utils.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_utils.c  .generated_files/68277e91657ebdd87153980c5bff7c15d5f07b4b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_utils.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_utils.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_utils.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget.c  .generated_files/28cd8517c2e90c8c2f14cac2f099b27d0e80af11.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic.c  .generated_files/ec88fa470593bf49eb515da24b96aafcf17aafb8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic_common.c  .generated_files/c060ea0d327fba72f1031ccc6e12cfa7950e3be4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_skin_classic_common.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_skin_classic_common.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc.c  .generated_files/7b60417a1320b344c9b2b7c9fca07cbfd2df3377.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc_skin_classic.c  .generated_files/8211bf9cbd4797dcae6741e96dc9fe870f1fd2eb.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_arc_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_arc_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph.c  .generated_files/63cbe3688de8b3351df1467b974ad41e16ade51e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph_skin_classic.c  .generated_files/955efb4e315650e4b058f21c711d94c7fbdfa380.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_bar_graph_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_bar_graph_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button.c  .generated_files/2fc50bfcbc46441bf80fa69831c3ca1c0154bd14.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button_skin_classic.c  .generated_files/3714fea7a60b9e26d76847983c22575c87f1a4d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_button_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_button_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox.c  .generated_files/350b9320a0c7ad7928b2ca3e3c108a4ad5e954bc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox_skin_classic.c  .generated_files/614f9bb23735700b3cd9f665c399ce461a6a4a3c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_checkbox_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_checkbox_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle.c  .generated_files/ad4936f96f62ab8265e76142cef8eedb9ae6369e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle_skin_classic.c  .generated_files/73ffed9679f528a7dd6d837f7fcf25c702f07460.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circle_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circle_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge.c  .generated_files/8caaba29e3a8c5d867cda9d2c1900eef837f0bc4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge_skin_classic.c  .generated_files/4029f0a8d7e890d2fc36997b5cba7f21a49b9991.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_gauge_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_gauge_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider.c  .generated_files/130e29adf3635f7ae58bc508244f624f809d658.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider_skin_classic.c  .generated_files/5f733ddbc8879bee5e314a8fc2b53840a74ee07b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_circular_slider_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_circular_slider_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface.c  .generated_files/3559000104935a4edd8b5b869accec852b213330.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface_skin_classic.c  .generated_files/667ac0f5cdb0f1080a291a6bb8ae20b984bafd5f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_drawsurface_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_drawsurface_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient.c  .generated_files/641047612d77cf0d2ce1f7a1c0bf3c7924b7c2ab.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient_skin_classic.c  .generated_files/e86270ece3be9aa08199135c69e5ed9dfeb27453.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_gradient_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_gradient_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox.c  .generated_files/6ed572a4409bff1c3ae8cfe7cd09f6520950fd9f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox_skin_classic.c  .generated_files/30e783b5dede58cc619fa210a856a96b11310e7c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_groupbox_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_groupbox_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image.c  .generated_files/79038ed60ccb0c45c63ebdd05c48cff8ec85d76c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image_skin_classic.c  .generated_files/b48af07b0b0de4047bbeb773b98b5f3b6882a989.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_image_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_image_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus.c  .generated_files/d7b75e26a7041099cd5277f46112b82febee5316.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus_skin_classic.c  .generated_files/5cd399c36024a4f61126e4be2b2af97151bffb64.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imageplus_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imageplus_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence.c  .generated_files/4b4a56b245a7a8c346621fc1470f6f8b9648bdfc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence_skin_classic.c  .generated_files/b65fc8e1e79eeccb40beb2cd286137963fd271b2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_imagesequence_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_imagesequence_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad.c  .generated_files/e5d7a916e3ca2372cf77f216bf7fb9b9739cf335.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad_skin_classic.c  .generated_files/b810e4242eb86c29adb57577e524182143ce5646.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_keypad_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_keypad_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label.c  .generated_files/de55dd6df0d42603260d69b16c23663d50d389ec.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label_skin_classic.c  .generated_files/b159731ad73683e2c8201a3f21dc3ce3622c46c0.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_label_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_label_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line.c  .generated_files/c075053bf26b06bb4012da54b27c6ed880b92362.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_skin_classic.c  .generated_files/8476805d339d7fff250f93a150b319097d965173.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph.c  .generated_files/2edbb797b6173d5eff6cb9091823f3985bb7a578.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph_skin_classic.c  .generated_files/7b6291f135b67cdf442b492cc207b4d8a1ace610.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_line_graph_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_line_graph_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list.c  .generated_files/e953f664317ed41b444d69eff9dcdebae97ef22.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list_skin_classic.c  .generated_files/c715b37fd70836caa0f7767aa00357fc0823349c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_list_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_list_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel.c  .generated_files/ffd99bee8ed17ad80032e052b647c608a2df25cc.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel_skin_classic.c  .generated_files/d8d08fed28f1e3f849d0bff5df09f9c6304d2946.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_listwheel_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_listwheel_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart.c  .generated_files/39bada22f3a2ae42209c93d223c046718606fe31.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart_skin_classic.c  .generated_files/9760e3e6c19803890127ccc40186db022734ce08.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_pie_chart_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_pie_chart_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar.c  .generated_files/5302be36b30f678c796e09ce68027f3cab551a35.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar_skin_classic.c  .generated_files/bae5001c46a637dbb3806ba4d0ef22d4708189a9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_progressbar_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_progressbar_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu.c  .generated_files/a9d9fa5027a9cfa2bb7e951e800eab60c06022a2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu_skin_classic.c  .generated_files/da3cb64e83a220db2af474c7fe99bccaaf1c681b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radial_menu_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radial_menu_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton.c  .generated_files/bb9a5a1835f874fe08ab19c4556ff1ae83d6896.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton_skin_classic.c  .generated_files/925384613ae0cb97792f8e005ba403e4626faf99.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_radiobutton_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_radiobutton_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_radiobutton_group.c  .generated_files/4fdc5a979f0569c53e40a4631c1db5dcf9773be.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_radiobutton_group.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_radiobutton_group.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle.c  .generated_files/986adf62e2387c5cefd9df61d9ae4e0a3e689da2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle_skin_classic.c  .generated_files/5e267f6604540d14327fc3f1634db064b8304b45.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_rectangle_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_rectangle_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar.c  .generated_files/2dd73a867a007459112fb1a0480419d0b152841d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar_skin_classic.c  .generated_files/3f21cfb4d025d2e2e240fd60f9f046aefcb933ae.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_scrollbar_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_scrollbar_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider.c  .generated_files/3f24d567855d54d93f2d500004bd701d36ba38b9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider_skin_classic.c  .generated_files/db4f4034b9418c95e8098324f6d588fd298d7349.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_slider_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_slider_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield.c  .generated_files/80a612b7156df3fb76d75a5b9bd2377a66b974de.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield_skin_classic.c  .generated_files/605407625d55ceda2de5b124cd47869bdcbfa640.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_textfield_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_textfield_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest.c  .generated_files/1ae0c38382064f2f3917bd971b139853488c18f4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest_skin_classic.c  .generated_files/34d3731c4da6576a293718a2ca9d40d69a578653.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_touchtest_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_touchtest_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window.c  .generated_files/3caf8244a90e3a55410898e15b7ccb102df3e695.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o: ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window_skin_classic.c  .generated_files/311a98468bf29fb2cdf5896be1d603388ad0e161.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1481330343" 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o.d" -o ${OBJECTDIR}/_ext/1481330343/libaria_widget_window_skin_classic.o ../src/config/Main_Board_Rev_C/gfx/libaria/src/libaria_widget_window_skin_classic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_events.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_events.c  .generated_files/9303f97e9ceea10968be6cafc229c95d01b5102e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_events.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_events.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_events.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_events.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_events.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/624871420/libaria_macros.o: ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_macros.c  .generated_files/36b1d8a5aacd5245850e2a03afad67fd6fc325a2.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/624871420" 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_macros.o.d 
	@${RM} ${OBJECTDIR}/_ext/624871420/libaria_macros.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/624871420/libaria_macros.o.d" -o ${OBJECTDIR}/_ext/624871420/libaria_macros.o ../src/config/Main_Board_Rev_C/gfx/libaria/libaria_macros.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/408764847/lodepng.o: ../src/config/Main_Board_Rev_C/gfx/third_party/src/lodepng/lodepng.c  .generated_files/9db9eada56bcac82cc19e6391f6ea8595770b979.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/408764847" 
	@${RM} ${OBJECTDIR}/_ext/408764847/lodepng.o.d 
	@${RM} ${OBJECTDIR}/_ext/408764847/lodepng.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/408764847/lodepng.o.d" -o ${OBJECTDIR}/_ext/408764847/lodepng.o ../src/config/Main_Board_Rev_C/gfx/third_party/src/lodepng/lodepng.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_external.c  .generated_files/dda48e973a02739546898cce36459780b85770ad.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_internal.c  .generated_files/ee370e9d22baa1efc7baa0d0dbcb3aca356d9697.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_png_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_png_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image.c  .generated_files/299ee014a77ace0e0b62ddc10dffadc0eb9d4227.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_external.c  .generated_files/a599cbd0f0e59c959be3a9a4c897780b299491e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_internal.c  .generated_files/9663d2a583994cada33c8e25015fd38c232308f5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_raw_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_raw_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_external.c  .generated_files/95231408e90bb52051262d5e378a581f51e6a750.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_internal.c  .generated_files/2388649be535ff7bdd28527298c197b3eb1f5af7.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_rle_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_rle_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_utils.c  .generated_files/9ee7cfe602f82ef973bc8a09b2e49b7bccb3424d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_image_utils.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_image_utils.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_palette.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_palette.c  .generated_files/4c90402850360076bf05a647157195c58db49063.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_palette.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_palette.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_palette.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string.c  .generated_files/9448fe305a79ab9dc1cf8fc43373c1a6743fef20.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_external.c  .generated_files/b475e9fa23346c0dfd6a8a9334370a52c14f8aa1.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_stringbuffer_external.c  .generated_files/ca8daf3dcdec852be8c087edcf79180b8557b5a1.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_stringbuffer_external.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_stringbuffer_external.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_internal.c  .generated_files/4772b68910ddcaadd5cf5b8ae87d70f4ca96e325.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_internal.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_internal.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_query.c  .generated_files/1a6a453bd807a3b442f85019abc5c64933fc6724.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_query.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_query.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o: ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_utils.c  .generated_files/a17cc2e02d9e02052812173ecb0349e76284371.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1634538748" 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o.d" -o ${OBJECTDIR}/_ext/1634538748/gfxu_string_utils.o ../src/config/Main_Board_Rev_C/gfx/utils/src/gfxu_string_utils.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1447700229/gfx_assets.o: ../src/config/Main_Board_Rev_C/gfx/gfx_assets.c  .generated_files/ab494f3a929d0b160062de94128043f4ea7819cf.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1447700229" 
	@${RM} ${OBJECTDIR}/_ext/1447700229/gfx_assets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1447700229/gfx_assets.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1447700229/gfx_assets.o.d" -o ${OBJECTDIR}/_ext/1447700229/gfx_assets.o ../src/config/Main_Board_Rev_C/gfx/gfx_assets.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1194195235/plib_cache.o: ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache.c  .generated_files/73631188a164870ac5f0cdd065083b35fdf109f4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1194195235" 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1194195235/plib_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1194195235/plib_cache.o.d" -o ${OBJECTDIR}/_ext/1194195235/plib_cache.o ../src/config/Main_Board_Rev_C/peripheral/cache/plib_cache.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635879171/plib_clk.o: ../src/config/Main_Board_Rev_C/peripheral/clk/plib_clk.c  .generated_files/3d7fef202f9b61782a3e029fe4711048969f6e4c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635879171" 
	@${RM} ${OBJECTDIR}/_ext/635879171/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/635879171/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635879171/plib_clk.o.d" -o ${OBJECTDIR}/_ext/635879171/plib_clk.o ../src/config/Main_Board_Rev_C/peripheral/clk/plib_clk.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1663751207/plib_coretimer.o: ../src/config/Main_Board_Rev_C/peripheral/coretimer/plib_coretimer.c  .generated_files/bb7e1b076fd8df98a1f5ae48bd8decf60adba78a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1663751207" 
	@${RM} ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1663751207/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1663751207/plib_coretimer.o ../src/config/Main_Board_Rev_C/peripheral/coretimer/plib_coretimer.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635879891/plib_ddr.o: ../src/config/Main_Board_Rev_C/peripheral/ddr/plib_ddr.c  .generated_files/a11bc55d6bd4d87ab7d1ea61f0abf04200c1fd72.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635879891" 
	@${RM} ${OBJECTDIR}/_ext/635879891/plib_ddr.o.d 
	@${RM} ${OBJECTDIR}/_ext/635879891/plib_ddr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635879891/plib_ddr.o.d" -o ${OBJECTDIR}/_ext/635879891/plib_ddr.o ../src/config/Main_Board_Rev_C/peripheral/ddr/plib_ddr.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762551638/plib_dmac.o: ../src/config/Main_Board_Rev_C/peripheral/dmac/plib_dmac.c  .generated_files/b8c6bd620d47c44ab09e182f9deccc7f8da96af8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762551638" 
	@${RM} ${OBJECTDIR}/_ext/1762551638/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762551638/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762551638/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1762551638/plib_dmac.o ../src/config/Main_Board_Rev_C/peripheral/dmac/plib_dmac.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762512950/plib_evic.o: ../src/config/Main_Board_Rev_C/peripheral/evic/plib_evic.c  .generated_files/f5af064386be9194ffbdfcaac9244107979efbb4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762512950" 
	@${RM} ${OBJECTDIR}/_ext/1762512950/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762512950/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762512950/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1762512950/plib_evic.o ../src/config/Main_Board_Rev_C/peripheral/evic/plib_evic.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762459122/plib_gpio.o: ../src/config/Main_Board_Rev_C/peripheral/gpio/plib_gpio.c  .generated_files/82df9c1dad9464dc1e7b44ae1318477c0371635.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762459122" 
	@${RM} ${OBJECTDIR}/_ext/1762459122/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762459122/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762459122/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1762459122/plib_gpio.o ../src/config/Main_Board_Rev_C/peripheral/gpio/plib_gpio.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o: ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp1.c  .generated_files/da284489d7ed8f2caf13258066d5f7dd988e31b5.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762233162" 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o.d" -o ${OBJECTDIR}/_ext/1762233162/plib_ocmp1.o ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp1.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o: ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp3.c  .generated_files/478776a8b5ed2515461d09c00829e37106f0b92.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762233162" 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o.d" -o ${OBJECTDIR}/_ext/1762233162/plib_ocmp3.o ../src/config/Main_Board_Rev_C/peripheral/ocmp/plib_ocmp3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr4.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr4.c  .generated_files/dd4ae41216c1c1b6497bde90e074674cf3b0f963.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr4.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr4.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr4.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr4.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr2.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr2.c  .generated_files/17f1aa63be76f4839e0176817acab5825612188c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr2.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr2.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr3.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr3.c  .generated_files/d2b8d27085ce1594356d14beb8029d5038476863.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr3.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/635895546/plib_tmr9.o: ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr9.c  .generated_files/2a53447d34aa70ec0d61a8e98e2cc8e3f8b5d33f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/635895546" 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr9.o.d 
	@${RM} ${OBJECTDIR}/_ext/635895546/plib_tmr9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/635895546/plib_tmr9.o.d" -o ${OBJECTDIR}/_ext/635895546/plib_tmr9.o ../src/config/Main_Board_Rev_C/peripheral/tmr/plib_tmr9.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762056179/plib_uart5.o: ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart5.c  .generated_files/73af753176228d4ed970edb10cecf84d4c3aad0d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762056179" 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762056179/plib_uart5.o.d" -o ${OBJECTDIR}/_ext/1762056179/plib_uart5.o ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart5.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762056179/plib_uart6.o: ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart6.c  .generated_files/e0405c1fff8dfe05e2a03a1150e03b150ebc432.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762056179" 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart6.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762056179/plib_uart6.o.d" -o ${OBJECTDIR}/_ext/1762056179/plib_uart6.o ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart6.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1762056179/plib_uart3.o: ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart3.c  .generated_files/131c7db5e7549c6d603e27c6d98fe0f60950ed26.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1762056179" 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1762056179/plib_uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1762056179/plib_uart3.o.d" -o ${OBJECTDIR}/_ext/1762056179/plib_uart3.o ../src/config/Main_Board_Rev_C/peripheral/uart/plib_uart3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/318000363/xc32_monitor.o: ../src/config/Main_Board_Rev_C/stdio/xc32_monitor.c  .generated_files/fc6d7f07dfe529fc4a16a8faa0e8a77f1d93daf8.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/318000363" 
	@${RM} ${OBJECTDIR}/_ext/318000363/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/318000363/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/318000363/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/318000363/xc32_monitor.o ../src/config/Main_Board_Rev_C/stdio/xc32_monitor.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1120703082/sys_cache.o: ../src/config/Main_Board_Rev_C/system/cache/sys_cache.c  .generated_files/86d85572795f3e3a34cfc844f162a94079141165.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1120703082" 
	@${RM} ${OBJECTDIR}/_ext/1120703082/sys_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1120703082/sys_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1120703082/sys_cache.o.d" -o ${OBJECTDIR}/_ext/1120703082/sys_cache.o ../src/config/Main_Board_Rev_C/system/cache/sys_cache.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1335146508/sys_dma.o: ../src/config/Main_Board_Rev_C/system/dma/sys_dma.c  .generated_files/1d12fd0c5f3eaefecda35f433284abdff9291028.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1335146508" 
	@${RM} ${OBJECTDIR}/_ext/1335146508/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1335146508/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1335146508/sys_dma.o.d" -o ${OBJECTDIR}/_ext/1335146508/sys_dma.o ../src/config/Main_Board_Rev_C/system/dma/sys_dma.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1114761762/sys_input.o: ../src/config/Main_Board_Rev_C/system/input/sys_input.c  .generated_files/a8d118f988d294b18b504a86ff77c26b34c4aa2c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1114761762" 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input.o.d 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1114761762/sys_input.o.d" -o ${OBJECTDIR}/_ext/1114761762/sys_input.o ../src/config/Main_Board_Rev_C/system/input/sys_input.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1114761762/sys_input_listener.o: ../src/config/Main_Board_Rev_C/system/input/sys_input_listener.c  .generated_files/5bca08f34b26e17f35558af525c98ce3f34d71b.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1114761762" 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o.d 
	@${RM} ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1114761762/sys_input_listener.o.d" -o ${OBJECTDIR}/_ext/1114761762/sys_input_listener.o ../src/config/Main_Board_Rev_C/system/input/sys_input_listener.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1837585192/sys_int.o: ../src/config/Main_Board_Rev_C/system/int/src/sys_int.c  .generated_files/34126b63dad0f3f710650ef0efd9188c5f28237d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1837585192" 
	@${RM} ${OBJECTDIR}/_ext/1837585192/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1837585192/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1837585192/sys_int.o.d" -o ${OBJECTDIR}/_ext/1837585192/sys_int.o ../src/config/Main_Board_Rev_C/system/int/src/sys_int.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/565369102/sys_time.o: ../src/config/Main_Board_Rev_C/system/time/src/sys_time.c  .generated_files/af9d68df3786f98d64883ba2c7ffec2df5dcce33.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/565369102" 
	@${RM} ${OBJECTDIR}/_ext/565369102/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/565369102/sys_time.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/565369102/sys_time.o.d" -o ${OBJECTDIR}/_ext/565369102/sys_time.o ../src/config/Main_Board_Rev_C/system/time/src/sys_time.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/initialization.o: ../src/config/Main_Board_Rev_C/initialization.c  .generated_files/fcc6cfe8ddd71bb6218bd264738e63df4edbe14a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/initialization.o.d" -o ${OBJECTDIR}/_ext/1593671781/initialization.o ../src/config/Main_Board_Rev_C/initialization.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/interrupts.o: ../src/config/Main_Board_Rev_C/interrupts.c  .generated_files/3f14adc4d0bd902baa717d0aec624a9b799eb912.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/interrupts.o.d" -o ${OBJECTDIR}/_ext/1593671781/interrupts.o ../src/config/Main_Board_Rev_C/interrupts.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/exceptions.o: ../src/config/Main_Board_Rev_C/exceptions.c  .generated_files/dff57b86e2c1a0a7779a6e318727bf60870409a9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/exceptions.o.d" -o ${OBJECTDIR}/_ext/1593671781/exceptions.o ../src/config/Main_Board_Rev_C/exceptions.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1593671781/tasks.o: ../src/config/Main_Board_Rev_C/tasks.c  .generated_files/b5489d245ef6da3f755bc2ae44b5fa4724483618.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1593671781" 
	@${RM} ${OBJECTDIR}/_ext/1593671781/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593671781/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593671781/tasks.o.d" -o ${OBJECTDIR}/_ext/1593671781/tasks.o ../src/config/Main_Board_Rev_C/tasks.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o: ../src/drv_camera_sccb.c  .generated_files/7e8e893823d031ad4ea64361590d4bb1a3f41161.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_camera_sccb.o ../src/drv_camera_sccb.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o: ../src/drv_camera_ovm7692.c  .generated_files/f7db420323ceb561b4e0e89e7cce33376e4db01c.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_camera_ovm7692.o ../src/drv_camera_ovm7692.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o: ../src/drv_led_pca9530.c  .generated_files/fec93d9db53ede1fe22c9f004587000b2cafb4a4.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_led_pca9530.o ../src/drv_led_pca9530.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  .generated_files/6e0a5eb974524c4301ea69d1461b8fab2a5cf39e.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_i2c2.o: ../src/drv_i2c2.c  .generated_files/3cce12bb454659d0b1602fd940a127ac3bad5d14.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_i2c2.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_i2c2.o ../src/drv_i2c2.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_piezo.o: ../src/drv_piezo.c  .generated_files/78f6e2d9e33dc5830a05e465309fc85e79122083.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_piezo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_piezo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_piezo.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_piezo.o ../src/drv_piezo.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/message_exchange.o: ../src/message_exchange.c  .generated_files/6ff8598b4096cd17b9823e28b78c79453b8fa633.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_exchange.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/message_exchange.o.d" -o ${OBJECTDIR}/_ext/1360937237/message_exchange.o ../src/message_exchange.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/990863823/delay.o: ../src/Drivers/delay.c  .generated_files/5eb6ef30c834508a06d208eaf33e87f17ef9df86.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/990863823" 
	@${RM} ${OBJECTDIR}/_ext/990863823/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/990863823/delay.o.d" -o ${OBJECTDIR}/_ext/990863823/delay.o ../src/Drivers/delay.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/settings.o: ../src/settings.c  .generated_files/5bd4bff99a815ac29aebcf0e8c5685956db3b688.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/settings.o.d" -o ${OBJECTDIR}/_ext/1360937237/settings.o ../src/settings.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/device_settings_screen.o: ../src/device_settings_screen.c  .generated_files/e50f3652e65ed6bdcf7a253638b5fa2237f09100.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/device_settings_screen.o.d" -o ${OBJECTDIR}/_ext/1360937237/device_settings_screen.o ../src/device_settings_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o: ../src/camera_settings_screen.c  .generated_files/29e02b919932474f2e3e73a5bcee1613bd0f6dd7.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o.d" -o ${OBJECTDIR}/_ext/1360937237/camera_settings_screen.o ../src/camera_settings_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/maths_library.o: ../src/maths_library.c  .generated_files/8cf47a930e2447611d01700e18b0caa87e0175d6.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/maths_library.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/maths_library.o.d" -o ${OBJECTDIR}/_ext/1360937237/maths_library.o ../src/maths_library.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/scan.o: ../src/scan.c  .generated_files/9fd766e217d2fed007460ad6bae2484143fc4a73.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/scan.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/scan.o.d" -o ${OBJECTDIR}/_ext/1360937237/scan.o ../src/scan.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app_function.o: ../src/app_function.c  .generated_files/e5ba4102444700d9bb25a0ad333a3a444c07875a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_function.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_function.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_function.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_function.o ../src/app_function.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app_ui_state.o: ../src/app_ui_state.c  .generated_files/93884d4841e9408aad482e88194192e933542384.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_ui_state.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_ui_state.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_ui_state.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_ui_state.o ../src/app_ui_state.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main_menu.o: ../src/main_menu.c  .generated_files/13e9c9be623db90a75852c1991685a90ae1ef92a.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main_menu.o.d" -o ${OBJECTDIR}/_ext/1360937237/main_menu.o ../src/main_menu.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/display_settings_screen.o: ../src/display_settings_screen.c  .generated_files/52d4555f51005f9c10e957467916d2b3e272fb9.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/display_settings_screen.o.d" -o ${OBJECTDIR}/_ext/1360937237/display_settings_screen.o ../src/display_settings_screen.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pic_comms.o: ../src/pic_comms.c  .generated_files/89868d15077afae9a6ca89a4611b316628316acf.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/pic_comms.o ../src/pic_comms.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o: ../src/drv_display_ST7701S.c  .generated_files/2100102fe3a31f91ead2298b872c2a90d8c92f57.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_display_ST7701S.o ../src/drv_display_ST7701S.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/pic24_comms.o: ../src/pic24_comms.c  .generated_files/a537a3b79fcfb64ad5d9ef97984f3e303e86f071.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic24_comms.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic24_comms.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic24_comms.o.d" -o ${OBJECTDIR}/_ext/1360937237/pic24_comms.o ../src/pic24_comms.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_i2c3.o: ../src/drv_i2c3.c  .generated_files/318f9d2209170fc3948fc9dbff6bcceaebae7c4f.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_i2c3.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_i2c3.o ../src/drv_i2c3.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o: ../src/drv_touch_cst130.c  .generated_files/2c460099769f6b4f8b1d1c52d4c72d979a5b492d.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o.d" -o ${OBJECTDIR}/_ext/1360937237/drv_touch_cst130.o ../src/drv_touch_cst130.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/power_management.o: ../src/power_management.c  .generated_files/927432c6fbfd8a605649e25eb2a3cb2f2b0072a7.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_management.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/power_management.o.d" -o ${OBJECTDIR}/_ext/1360937237/power_management.o ../src/power_management.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/1500578dd563be4a65fd984bb40baa8ab342d870.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/4586fb934fc76eece5c04faa3632861d804b2833.flag .generated_files/5b305add086e31c782c0329118986cb81dcfa37.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O3 -I"../src" -I"../src/config/Main_Board_rev_C" -I"../src/packs/PIC32MZ2064DAR169_DFP" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/lib/libnano2d.a ../src/config/Main_Board_rev_C/gfx/driver/processor/2dgpu/lib/libnano2d.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\src\config\Main_Board_Rev_C\gfx\driver\processor\2dgpu\lib\libnano2d.a ..\src\config\Main_Board_rev_C\gfx\driver\processor\2dgpu\lib\libnano2d.a      -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x27F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=48748,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../src/config/Main_Board_Rev_C/gfx/driver/processor/2dgpu/lib/libnano2d.a ../src/config/Main_Board_rev_C/gfx/driver/processor/2dgpu/lib/libnano2d.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\src\config\Main_Board_Rev_C\gfx\driver\processor\2dgpu\lib\libnano2d.a ..\src\config\Main_Board_rev_C\gfx\driver\processor\2dgpu\lib\libnano2d.a      -DXPRJ_Main_Board_Rev_C=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=48748,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIB_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Main_Board_Rev_C
	${RM} -r dist/Main_Board_Rev_C

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
