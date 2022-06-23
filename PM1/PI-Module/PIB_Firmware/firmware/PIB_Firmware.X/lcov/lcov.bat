@echo off

setlocal
cd /d %~dp0

set path=%path%;C:\Perl64\bin;c:\windows\system32;\C:\MinGW\bin;C:\MinGW\msys\1.0\bin

:: Full dirname of current executable
set idir=%~dp0
set perl=C:\MinGW\msys\1.0\bin\perl.exe
set sourceDir=../../src
set outputDir=lcov-report
set gcovExe=C:/MinGW/bin/gcov.exe
set gcovOutputDir=../unit_test_build/gcov/out

md "%CD%\%outputDir%"
echo Creating gcov\lcov.info ...
%perl% %idir%lcov.perl -b %sourceDir% -d %gcovOutputDir% -c  --gcov-tool %gcovExe% -o %outputDir%/lcov.info

if %ERRORLEVEL% NEQ 0; goto Error

echo
echo Extract coverage information for source files ...
%perl% %idir%/lcov.perl --extract %outputDir%/lcov.info "*/src/*" -o %outputDir%/lcov-sanitised.info

echo Generating html ...
%perl% %idir%genhtml.perl -o %outputDir%/html/ %outputDir%/lcov-sanitised.info -p "%CD%"

echo
echo "Completed. Coverage file generated in %outputDir%/html/index.html"
goto End

:Error
  echo "Aborted"
  
:End

