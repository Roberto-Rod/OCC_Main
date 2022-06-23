
This SDK has been patched by Embedded Artists for the iMXRT1176 Developer's Kit.
The SDK was released on 2022-03-02 and is based on NXP's 2.11.0 SDK (SDK_2_11_0_MIMXRT1176xxxxx.zip).

This is what has been patched:
* LWIP projects - added reading of the MAC address from I2C EEPROM either on the 100Mbit adapter
  or on the uCOM board
* Added an I2C driver for the gpio expander (PCA6416) and code to use it
* Added an I2C driver for the PWM gpio expander (PCA9530) and code to use it
* SDRAM size has been corrected to 32Mb (including linker files, MPU and DCD)
* 1G Ethernet PHY has been changed from RTL8211F to AR8031DS
* SEMC projects - changed to correct settings for the SDRAM
* SEMC projects - changed algorithm for memory test and now test entire 32MB instead of only 4KB
* Examples using eLCDIF/LCDIFv2 have been updated to use PCA6416/PCA9530 for
  RST/PWR/BL signals
* BOARD_USER_BUTTON has been redirected to SW5/WAKEUP button on the uCOM Carrier Board
* USER_LED has been changed to the blue RGB LED using PCA6416
* Touch: I2C bus and GPIOs have been changed for RST/INT
* Camera pins
* Adjusted the USB interface number (it is different for host and device examples)
* Changed the Wi-Fi examples to use the Embedded Artists 1XK M.2 Module (EAR00385) as default
* Corrected the ethernet PHY addresses
* Changed CORE clock depending on speed grading of MCU (798MHz for Industrial, 996MHz for Commercial)
* Changed SEMC clock to be within maximum speed for SDRAM (now 148.5MHz, was 198MHz)
* Many of the projects have been updated to use a more complete pin_mux.c file where all
  necessary pins have been initialized. The SDK examples used to only configure the pins
  that they use (and often not every pin) and most of the time the configuration was only
  for MUX:ing and not the PAD settings (pull up/down/none, drive strength and slew).
* Converted the AzureRTOS examples to use the BOARD_NETWORK_USE_100M_ENET_PORT (same as all
  other networking examples) instead of using the old EXAMPLE_USE_1G_ENET_PORT

This has been added:
* HDMI support to most GUI examples. HDMI at 1024x768@60 is the default resolution but
  that can be changed per project in display_support.h/elcdif_support.h/lcdifv2_support.h.
* Added ADT example for TensorFlow Lite
* I2C probe example
* EDID reader example
* Wi-Fi (serial) examples for the CMWC1ZZABR-107-EVB (a.k.a ABR Module)

This has been removed:
* All projects for the expansion board AGM01

Important things to note:
* Read section "8 - Known Issues" in docs/MCUXpresso SDK Release Notes for MIMXRT1170-EVK.pdf
  to see known issues with the current version of the SDK.
* For Iperf examples, set compiler optimization to -O3 or similar to improve performance.
* If the hardware seems unresponsive and the debugger cannot connect/flash/erase the current program
  then the most likely cause is the running program preventing the access. To stop the currently
  running program and regain control:
  1) Press and hold down the ISP_ENABLE button (SW1)
  2) Press and hold down the RESET button (SW3)
  3) Let go of the RESET button
  4) Wait an extra second or two
  5) Release the ISP_ENABLE button
  6) The hardware is now in a mode where programming/erasing it should work


Connectors:
* J29 (micro USB) is the default UART for the CM7 core and unless specified otherwise it is setup for 115200 8/N/1
* J30 (micro USB) is the default UART for the CM4 core and unless specified otherwise it is setup for 115200 8/N/1
* For 1Gbit Ethernet examples, use connector J25 on uCOM Carrier Board
* For 100Mbit Ethernet examples, use ethernet adapter connected between J12 on uCOM Carrier Board
  and J37 on the adapter. These four connections are also needed:
    1) uCOM Carrier Board, JP38:1 -> adapter JP37:1
    2) uCOM Carrier Board, JP38:2 -> adapter JP37:2
    3) uCOM Carrier Board, JP27:1 -> adapter JP39:2
    4) uCOM Carrier Board, JP27:2 -> adapter JP39:1
* The two CSI examples can use either an OV5640 camera in connector J23 or a camera in connector J24
* The EIQ examples that use a camera expects the camera in connector J24 (J23 might work for some
  of the examples but runs much slower)
* Some GUI examples are configured for the RK055AHD091 display which should be in connector "C" on
  the uCOM Carrier Board. Ignore the readme text about connecting extra 5V power.
* The default for GUI examples is to use an HDMI adapter in connector "C" on
  the uCOM Carrier Board. Ignore the readme text about connecting extra 5V power.


Everything below this line is the original content of the readme file.
=======================================================================



Overview
========
The Multicore Hello World demo application demonstrates how to set up projects for individual
cores on a multicore system. In this demo, the primary core prints the "Hello World from the Primary Core!"
string to the terminal and then releases the secondary core from the reset. The secondary
core toggles an on-board LED indicating that the secondary core is running.

Toolchain supported
===================
- IAR embedded Workbench  9.10.2
- Keil MDK  5.34
- GCC ARM Embedded  10.2.1
- MCUXpresso  11.5.0

Hardware requirements
=====================
- Mini/micro USB cable
- MIMXRT1170-EVK board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the hello world multicore demo in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Hello World from the Primary Core!

Copy Secondary core image to address: 0x20200000, size: 3280
Starting Secondary core.
The secondary core application has been started.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note:
The "Copy Secondary core image to address..." log message is not displayed on the terminal window when MCUXpresso IDE is used.
In case of MCUXpresso IDE the secondary core image is copied to the target memory during startup automatically.

Note:
To download binary of cm7 core into qspiflash and boot from qspiflash directly, following steps are needed:
1. Compile flash target of the project, and get the binaray file "hello_world.bin".
3. Set the SW1: 1 off 2 off 3 on 4 off, then power on the board and connect USB cable to J11.
4. Drop the binaray into disk "RT1170-EVK" on PC.
5. Wait for the disk disappear and appear again which will take couple of seconds.
7. Reset the board by pressing SW3 or power off and on the board. 
(If default boot core is cm4, binary of cm4 could be downloaded and boot according to steps above.)

Note:
To download and debug IAR EW project using J-Link (replacing the default CMSIS-DAP debug probe), following steps are needed:
1. Remove J6 and J7 jumpers.
2. Attach the J-Link probe (J-Link Plus / J-Trace) to the board using the J1 connector.
3. Set "J-Link / J-Trace" in CM7 project options -> Debugger -> Setup panel (replacing CMSIS-DAP option).
4. Unselect the "Use macro file(s)" in CM7 project options -> Debugger -> Setup panel.
5. Enable "Use command line options" in CM7 project options -> Debugger -> Extra Options panel 
   (--jlink_script_file=$PROJ_DIR$/../evkmimxrt1170_connect_cm4_cm7side.jlinkscript command line option is applied).
5. Click on "Download and Debug" button. During the loading process you can be asked by J-Link sw
   to select the proper device name (MIMXRT1176XXXA_M7 is unknown). Click O.K. and choose the MIMXRT1176xxxxA device.
6. It is not possible to attach to the CM4 core when using the J-Link. Also, the multicore debugging does not work with that probe.

Note:
To download and debug Keil MDK project using J-Link (replacing the default CMSIS-DAP debug probe), following steps are needed:
1. Remove J6 and J7 jumpers.
2. Attach the J-Link probe (J-Link Plus / J-Trace) to the board using the J1 connector.
3. Set "J-LINK / J-TRACE Cortex" in CM7 project options -> Debug panel (replacing CMSIS-DAP Debugger option).
4. After the CM7 application build click on Download/F8 button (menu Flash -> Download).
5. Power off and power on the board.
6. Multicore example starts running, one can start debugging the CM7 side by clicking on Start/Stop Debug Session (Ctrl + F5). 
7. It is not possible to attach to the CM4 core when using the J-Link.
