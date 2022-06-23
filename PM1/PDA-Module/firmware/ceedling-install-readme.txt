Installation instructions
===========================
1) Install ruby (https://rubyinstaller.org/downloads/), with devkit. Tested on version 2.7.2.
2) Open command line as administrator and run: 'gem install ceedling' (no quotes).
3) Open command line as administrator and run: 'gem install rubyserial' (no quotes).
4) Create environmental variable MPLAB_PATH with path to your MPlabX, e.g.: 'C:\Program Files\Microchip\MPLABX\v5.45' (no quotes).
Go to System. Click on the Advanced system settings, go to Advanced tab and then click Environment Variables. Click New.
5) Create environmental variable XC32_PATH with path to your xc32, e.g.: 'C:\Program Files\Microchip\xc32\v2.50' (no quotes).

How to use
===========
Go to ./test/hw-test folder. In com.txt specify COM port used by the EFH microcontroller.
Open console window, by running start-cm.bat
Type: "ceedling options:hw test:all" to run all tests.

Java version notes
==================
ipecmd(.sh) uses Java to program the device, however it seems that the version in MPLABX v6.00 doesn't like java versions higher than 1.8.
Symptoms are:
    1) Java error message: "WARNING: An illegal reflective access operation has occurred"
    2) HEX upload to device doesn't work
Fix
    Install java (1.)8 and modify ipecmd(.sh) to use java 8