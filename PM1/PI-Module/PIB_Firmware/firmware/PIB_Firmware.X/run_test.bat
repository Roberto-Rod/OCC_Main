setlocal

echo "Starting unit test"
set path=%PATH%;c:\Ruby27-x64\bin;c:\Ruby27-x64\msys64\mingw64\bin
rake clean clobber test:all

