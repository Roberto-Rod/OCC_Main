@echo OFF

@Rem Copy the hex files to the firmware update tool location
echo Copying PDAB and PIB hex files to the P1 Firmware Update Tool\FW directory...
copy "C:\Temp\MSV001\MSV001_Test_Scripts\SysTst_Manual_00013\PDAB_SysTst_Manual_00013.hex" "C:\P1 Firmware Update Tool\FW"
copy "C:\Temp\MSV001\MSV001_Test_Scripts\SysTst_Manual_00013\PIB_SysTst_Manual_00013.hex" "C:\P1 Firmware Update Tool\FW"
@REM Change directory
cd "C:\P1 Firmware Update Tool\FW"
echo Renaming files...
if exist "EFH_app.hex" del "EFH_app.hex"
if exist "PDAB_SysTst_Manual_00013.hex" ren "PDAB_SysTst_Manual_00013.hex" "EFH_app.hex"
if exist "PDAB_SysTst_Manual_00013.hex" del "PDAB_SysTst_Manual_00013.hex"
if exist "DAR_app.hex" del "DAR_app.hex"
if exist "PIB_SysTst_Manual_00013.hex" ren "PIB_SysTst_Manual_00013.hex" "DAR_app.hex"
if exist "PIB_SysTst_Manual_00013.hex" del "PIB_SysTst_Manual_00013.hex"

cd "C:\P1 Firmware Update Tool\P1 FUT"
echo Lanching programming tool...
"C:\Program Files\Java\jdk-15.0.2\bin\java.exe" --enable-preview -jar ProgrammingTool.jar A 3C "../FW/EFH_app.hex" "../FW/EFH_bs.hex" "../FW/DAR_app.hex" "../FW/DSPIC_app.hex"
pause