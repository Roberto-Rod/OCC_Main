echo "Starting coverage report"
set path=%PATH%;c:\Ruby27-x64\bin;c:\Ruby27-x64\msys64\mingw64\bin
rake gcov:all
pause
