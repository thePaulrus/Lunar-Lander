set path=%path%;C:\Program Files\CMake\bin
mkdir build
cd build
cmake ..
rem Build a second time to fix PCH folder
cmake ..
pause
cd..
call BuildShaders.bat
exit
