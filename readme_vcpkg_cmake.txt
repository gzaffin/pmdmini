for vcpkg and cmake and microsoft visual studio 2017

links to reference information pages concerinng how install and use Vcpkg
1.
https://blogs.msdn.microsoft.com/vcblog/2016/09/19/vcpkg-a-tool-to-acquire-and-build-c-open-source-libraries-on-windows/
2.
https://blogs.msdn.microsoft.com/vcblog/2018/04/24/announcing-a-single-c-library-manager-for-linux-macos-and-windows-vcpkg/

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

