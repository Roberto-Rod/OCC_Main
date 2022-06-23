@echo OFF

@REM @Rem Copy the hex files to the firmware update tool location
@REM echo Copying PDAB and PIB hex files to the P1 Firmware Update Tool\FW directory...
@REM copy "C:\Temp\PM1_software_UUT\PDA-Module\firmware\PDAB_Firmware.X\dist\PIC32MZ2048EFH100\production\PDAB_Firmware.X.production.hex" "C:\P1 Firmware Update Tool\FW"
@REM copy "C:\Temp\PM1_software_UUT\PDA-Module\firmware\PDAB_Firmware.X\dist\PIC32MZ2048EFH100\production\PIB_Firmware.X.production.hex" "C:\P1 Firmware Update Tool\FW"
@REM Change directory
cd "C:\P1 Firmware Update Tool\FW"
echo Renaming files...
if exist "EFH_app.hex" del "EFH_app.hex"
if exist "PDAB_Firmware.X.production.hex" ren "PDAB_Firmware.X.production.hex" "EFH_app.hex"
if exist "PDAB_Firmware.X.production.hex" del "PDAB_Firmware.X.production.hex"
if exist "DAR_app.hex" del "DAR_app.hex"
if exist "PIB_Firmware.X.production.hex" ren "PIB_Firmware.X.production.hex" "DAR_app.hex"
if exist "PIB_Firmware.X.production.hex" del "PIB_Firmware.X.production.hex"

cd "C:\P1 Firmware Update Tool\P1 FUT"
echo Lanching programming tool...
"C:\Program Files\Java\jdk-15.0.2\bin\java.exe" --enable-preview -jar ProgrammingTool.jar A 3C "../FW/EFH_app.hex" "../FW/EFH_bs.hex" "../FW/DAR_app.hex" "../FW/DSPIC_app.hex"
pause