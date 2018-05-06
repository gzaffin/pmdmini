for vcpkg and cmake and microsoft visual studio 2017

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

