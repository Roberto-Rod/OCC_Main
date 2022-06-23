Installation instructions
===========================
1) Install ruby (https://rubyinstaller.org/downloads/), with devkit. Tested on version 2.7.2.
2) Open command line as administrator and run: 'gem install ceedling' (no quotes).
3) Open command line as administrator and run: 'gem install rubyserial' (no quotes).
4) Create environmental variable MPLAB_PATH with path to your MPlabX, e.g.: 'C:\Program Files\Microchip\MPLABX\v5.45' (no quotes).
Go to System. Click on the Advanced system settings, go to Advanced tab and then click Environment Variables. Click New.
5) Create environmental variable XC16_PATH with path to your xc16, e.g.: 'C:\Program Files\Microchip\xc16\v1.60' (no quotes).

How to use
===========
Go to ./Environment-Firmware.X/test/hw-test folder. In com.txt specify COM port used by the EFH microcontroller.
Open console window, by running start-cmd.bat
Type: "ceedling options:hw test:all" to run all tests.