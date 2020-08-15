# pmdmini
Professional Music Driver (PMD) format player using Simple DirectMedia Layer (SDL) version 2.0.x

This is actually a BouKiCHi project (https://github.com/BouKiCHi), but since I cannot find its repostory anymore, I would like to share here.

Professional Music Driver (PMD) is a music driver developed by M.Kajihara which utilizes MML (Music Macro Language) to create music files for most japanese computers of the 80's and early 90's.
PMD can be used to make music for the PC-98, PC-88, X68000, and FM Towns.
[Thoughts of PMD by Kajihara](https://sites.google.com/site/kajapon/pmd)

# How to build

The following steps build `pmdplay.exe` on a MSYS2/MinGW-w64 box, or `pmdplay` on a GNU/Linux box with provided Makefile, using SDL2 and make.

```shell/bash shell
$ git clone https://github.com/gzaffin/pmdmini.git
$ cd pmdmini
$ make
```

The following steps build `pmdplay` on Ubuntu/Debian/GNU/LINUX o.s. box with SDL2 and cmake.

```GNU/linux bash
$ git clone https://github.com/gzaffin/pmdmini.git
$ cd pmdmini
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make pmdplay
```

The following steps build `pmdplay.exe` on a MSYS2/MinGW-w64 Windows o.s. box with SDL2 and cmake.

```msys2/mingw bash
$ git clone https://github.com/gzaffin/pmdmini.git
$ cd pmdmini
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release ..
$ make pmdplay
```

If MSYS Makefiles generator set with `-G "MSYS Makefiles"` cannot properly set make-utility,
then add `-DCMAKE_MAKE_PROGRAM=<[PATH]/make-utility>` PATH of make-utility (see [1])

```windows command-line interface
$ git clone https://github.com/gzaffin/pmdmini.git
$ cd pmdmini
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" -DCMAKE_MAKE_PROGRAM=mingw32-make ..
$ cmake --build . --config Release --target pmdplay
```

The following steps build `pmdplay.exe` on a Windows o.s. box with MSVC, vcpkg, SDL2 installed with vcpkg.

You can have Your build environment set, on a Windows 10 box, if Your MSVC is Microsoft Visual Studio 2019 Community edition, using Windows 10 taskbar search box writing `x64 Native Tools Command Prompt for VS 2019` and starting matching App.
Otherwise, if MSVC is installed in default localtion, if Windows SDK is 10.0.18362.0 (please see what is in 'C:\Program Files (x86)\Microsoft SDKs\Windows Kits\10\ExtensionSDKs\Microsoft.UniversalCRT.Debug' folder) (see [2]) issuing

```windows command-line interface
C:\Users\gzaff>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64 10.0.18362.0
```

Then

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
C:\pmdmini\build>ninja
```

For the case that Visual Studio can be used

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G "Visual Studio 16 2019" -A x64 -T host=x64 -DCMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```

For building from command line

```windows command-line interface
C:\pmdmini\build>cmake --build . --config Release --target pmdplay
```

Otherwise start Microsoft Visual Studio and debug pmdmini solution.

You can have Your build environment set, on a Windows 7 box, if Your MSVC is Microsoft Visual Studio 2017 Community edition, using Windows 7 taskbar search box writing `x64 Native Tools Command Prompt for VS 2017` and starting matching App.
Otherwise, if MSVC is installed in default localtion, if Windows SDK is 10.0.17763.0 (please see what is in 'C:\Program Files (x86)\Microsoft SDKs\Windows Kits\10\ExtensionSDKs\Microsoft.UniversalCRT.Debug' folder) (see [2]) issuing

```windows command-line interface
C:\Users\gzaff>"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64 10.0.17763.0
```

Then

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
C:\pmdmini\build>ninja
```

For the case that Visual Studio can be used

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G "Visual Studio 15 2017 Win64" -T host=x64 -DCMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```

For building from command line

```windows command-line interface
C:\pmdmini\build>cmake --build . --config Release --target pmdplay
```

Otherwise start Microsoft Visual Studio and debug pmdmini solution.

Recap of required MACRO definitions:

`CMAKE_TOOLCHAIN_FILE`: full PATH of vcpkg.cmake
`SDL2_DIR`: PATH to find SDL2Config.cmake

[1]
it is make-utility name e.g. `mingw32-make` with specified PATH if make is not within search PATH as it should be

[2]
calling vcvarsall.bat update PATH variable, so "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake" and "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja" can be called as cmake and ninja respectively

# Links
Reference information pages about how to install and how to use Vcpkg

[GitHub Microsoft vcpkg](https://github.com/Microsoft/vcpkg)

[vcpkg: A C++ package manager for Windows, Linux and MacOS](https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019)

[Eric Mittelette's blog](https://devblogs.microsoft.com/cppblog/vcpkg-a-tool-to-acquire-and-build-c-open-source-libraries-on-windows/)
