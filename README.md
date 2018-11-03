# pmdmini
Professional Music Driver (PMD) format player using Simple DirectMedia Layer (SDL) version 2.0.x

This is actually a BouKiCHi project (https://github.com/BouKiCHi) and (http://clogging.blog57.fc2.com/), but since I cannot find its repostory anymore,  I would like to share here.

Professional Music Driver (PMD) is a music driver developed by M.Kajihara which utilizes MML (Music Macro Language) to create music files for most japanese computers of the 80's and early 90's.
PMD can be used to make music for the PC-98, PC-88, X68000, and FM Towns.


# How to build

The following steps build `pmdplay.exe` on a MSYS2/MinGW-w64 box, or `pmdplay` on a GNU/Linux box with provided Makefile, using SDL2 and make.

```
$ git clone https://github.com/gzaffin/pmdmini.git
$ cd pmdmini
$ make
```

The following steps build `pmdplay` on Ubuntu/Debian/GNU/LINUX o.s. box with SDL2 and cmake.

```
$ git clone https://github.com/gzaffin/eupmini.git
$ cd eupmini
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make -j 4 pmdplay
```

The following steps build `pmdplay.exe` on a MSYS2/MinGW-w64 Windows o.s. box with SDL2 and cmake.

```
$ git clone https://github.com/gzaffin/eupmini.git
$ cd eupmini
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release ..
$ make -j 4 pmdplay
```

If MSYS_Makefiles generator set with `cmake -G "MSYS Makefiles"` cannot set make properly add `-DCMAKE_MAKE_PROGRAM=` make-utility (see [1])

```
$ git clone https://github.com/gzaffin/eupmini.git
$ cd eupmini
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=mingw32-make ..
$ cmake --build . --target pmdplay
```

The following steps build `pmdplay.exe` on a Windows o.s. box with vcpkg, SDL2 and cmake.

links to reference information pages concerning with how install and use Vcpkg
1.
https://blogs.msdn.microsoft.com/vcblog/2016/09/19/vcpkg-a-tool-to-acquire-and-build-c-open-source-libraries-on-windows/
2.
https://blogs.msdn.microsoft.com/vcblog/2018/04/24/announcing-a-single-c-library-manager-for-linux-macos-and-windows-vcpkg/

```
mkdir build
cd build
cmake-gui ..
```

On CMake GUI

Push `Configure` button

fill Optional toolset to use (argument to -T) with `host=x64`

Push `OK` button

Push `Add entry` button

Add Cache Entry

Name: `CMAKE_TOOLCHAIN_FILE`

Type: `STRING`

Value: PATH vcpkg/scripts/buildsystems/vcpkg.cmake (see [2])

Description: `cmake entry point for vcpkg`

Push `OK` button

Double check that `SDL2_DIR STRING` variable is a path to find SDL2Config.cmake (see [3]), if not the case, fix it

Push `Configure` button

Push `Generate` button

Push `Open Project` button

On Microsoft Visual Studio Community build solution

[1]
it is make name e.g. `mingw32-make`

[2]
it is absolute or relative path to vcpkg's vcpkg.cmake e.g. C:/tempGZ/vcpkg/scripts/buildsystems/vcpkg.cmake

[3]
it is absolute or relative path to vcpkg's SDL2Config.cmake e.g. C:/tempGZ/vcpkg/installed/x64-windows/share/sdl2

