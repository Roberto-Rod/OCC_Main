setlocal
echo Building MPLab X project for release
set MPLABXDIR=C:\Program Files\Microchip\MPLABX\v5.45
set path=%MPLABXDIR%\gnuBins\GnuWin32\bin;C:\Program Files\Microchip\xc32\v2.50\bin;%MPLABXDIR%\mplab_platform\bin
cd PDAB_Firmware.X
make clean
make -f nbproject/Makefile-Main_Board_Rev_C.mk SUBPROJECTS= .build-conf