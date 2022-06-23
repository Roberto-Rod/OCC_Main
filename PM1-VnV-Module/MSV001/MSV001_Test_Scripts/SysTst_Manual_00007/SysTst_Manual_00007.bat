@echo off
cd C:\Program Files (x86)\teraterm
:: Create a directory for Teraterm and test reports logging files root
echo Checking if the directory exists
if not exist "C:\Temp\MSV001\MSV001_Logs\SysTst_Manual_00007" mkdir "C:\Temp\MSV001\MSV001_Logs\SysTst_Manual_00007"
set LOG_FILE_ROOT="C:\Temp\MSV001\MSV001_Logs\SysTst_Manual_00007\SysTst_Manual_00007
:: Get date parts
set CUR_YYYY=%date:~6,4%
set CUR_MM=%date:~3,2%
set CUR_DD=%date:~0,2%
:: Concate everything together
set LOG_FILE_TIME=%LOG_FILE_ROOT%_%CUR_DD%_%CUR_MM%_%CUR_YYYY%
set LOG_FILE_LSC=%LOG_FILE_TIME%_LSC-log.txt"
set LOG_FILE_PIB=%LOG_FILE_TIME%_PIB-log.txt"
set LOG_FILE_PDA=%LOG_FILE_TIME%_PDAB-log.txt"
set LOG_FILE_PE=%LOG_FILE_TIME%_PE-log.txt"
:: Start Tera term
start TTERMPRO /C=3 /BAUD=115200 /L=%LOG_FILE_LSC%
start TTERMPRO /C=4 /BAUD=115200 /L=%LOG_FILE_PIB%
start TTERMPRO /C=5 /BAUD=115200 /L=%LOG_FILE_PDA%
start TTERMPRO /C=6 /BAUD=115200 /L=%LOG_FILE_PE%

echo Running test script SysTst_Manual_00007 from MSV001 test protocol
python "C:\Temp\MSV001\MSV001_Test_Scripts\SysTst_Manual_00007\SysTst_Manual_00007.py"
pause
