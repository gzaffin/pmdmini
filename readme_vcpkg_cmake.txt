for vcpkg and cmake and microsoft visual studio 2017

links to reference information pages concerinng how install and use Vcpkg
1.
https://blogs.msdn.microsoft.com/vcblog/2016/09/19/vcpkg-a-tool-to-acquire-and-build-c-open-source-libraries-on-windows/
2.
https://blogs.msdn.microsoft.com/vcblog/2018/04/24/announcing-a-single-c-library-manager-for-linux-macos-and-windows-vcpkg/

CMake GUI

cmake-gui ..
Configure
fill Optional toolset to use (argument to -T) with
host=x64
OK
Add entry
Add Cache Entry
Name:
CMAKE_TOOLCHAIN_FILE
Type:
STRING
Value:
<PATH>vcpkg/scripts/buildsystems/vcpkg.cmake (see [1])
Description:
cmake entry point for vcpkg
OK
Configure
Generate
Open Project

[1]
it is absolute or relative path to vcpkg's vcpkg.cmake e.g. C:/tempGZ/vcpkg/scripts/buildsystems/vcpkg.cmake

CMake Command-Line

C:\pmdmini\build>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake" -G "Visual Studio 16 2019" -Ax64 -Thost=x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake -DSDL2_DIR=C:/Users/gzaff/Devs/vcpkg/installed/x64-windows/share/sdl2 ..

[2] https://github.com/Kitware/CMake/blob/master/Help/generator/Visual%20Studio%2016%202019.rst

C:\Users\gzaff\Devs\pmdmini\build>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake" -G "Visual Studio 15 2017 Win64" -Thost=x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake -DSDL2_DIR=C:/Users/gzaff/Devs/vcpkg/installed/x64-windows/share/sdl2 ..

[3] https://github.com/Kitware/CMake/blob/master/Help/generator/Visual%20Studio%2015%202017.rst

C:\pmdmini\build>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake" --build . --target pmdplay

[4] https://cmake.org/cmake/help/latest/manual/cmake.1.html

C:\pmdmini\build>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake -DSDL2_DIR=C:/Users/gzaff/Devs/vcpkg/installed/x64-windows/share/sdl2 ..

C:\pmdmini\build>ninja

