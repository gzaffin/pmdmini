## pmdmini
Professional Music Driver (PMD) format player using Simple DirectMedia Layer (SDL) version 2.0.x .

This is actually a BouKiCHi project (https://github.com/BouKiCHi), but since I cannot find his repostory anymore, I would like to share here.
It'd begun as pmdxmms - PMD input plugin for XMMS - by AGAWA Koji, leveraging PMD for Windows by [C60 site](http://c60.la.coocan.jp/), M88 and FM sound engine by cisc, PPZ8 PCM driver by Ukky.

In [C60 site](http://c60.la.coocan.jp/), a new PMDWin Ver.0.51, updated 2021/12/19, was released, here's a direct link named [DownLoad VS2019](http://c60.la.coocan.jp/download/PMDWinS051_VS2019.zip), this version changed FM sound engine by cisc for [Aaron Giles's ymfm](https://github.com/aaronsgiles/ymfm) engine,
I synchronized/accepted C60 code changes in this repository and refreshed source code.
An important parameter when using Giles's ymfm is re-sampling points number, that is #define NUMOFINTERPOLATION in opnaw.h include file.

Professional Music Driver (PMD) is a music driver developed by M.Kajihara which utilizes MML (Music Macro Language) to create music files for most japanese computers of the 80's and early 90's.
PMD can be used to make music for the PC-98, PC-88, X68000, and FM Towns computers.
[Thoughts of PMD by Kajihara](https://sites.google.com/site/kajapon/pmd)

# How to use pmdplay player

Call `pmdplay` with no arguments for a quick list of examples about how play a .M, .M2, .MZ module.

In folder `${HOME}/.pmdplay/` on Linux o.s. or `%USERPROFILE%\.pmdplay\` on Windows o.s. You shall expand [OPNA Rhythm Sound Source](http://snesmusic.org/hoot/drum_samples.zip) archive or even better [NEC PC-8801/[BIOS] YM2608 (OPNA) rhythm samples (Yamaha)/[BIOS] YM2608 (OPNA) rhythm samples [ROM] [Set 2].7z](https://archive.org/download/Neo_Kobe_NEC_PC-8801_2016-02-25/Neo%20Kobe%20-%20NEC%20PC-8801%20%282016-02-25%29.zip/NEC%20PC-8801%2F%5BBIOS%5D%20YM2608%20%28OPNA%29%20rhythm%20samples%20%28Yamaha%29%2F%5BBIOS%5D%20YM2608%20%28OPNA%29%20rhythm%20samples%20%5BROM%5D%20%5BSet%202%5D.7z) archive and plus put `ym2608_adpcm_rom.bin` taken, for example, [here](https://www.planetemu.net/rom/fb-alpha/ym2608-2) .

# How to build

The following steps build `pmdplay` on Ubuntu/Debian/GNU/LINUX o.s. box with SDL2 and cmake.

```GNU/linux bash
$ git clone https://github.com/gzaffin/pmdmini.git
$ cd pmdmini
$ mkdir build
$ cd build
$ cmake -D CMAKE_BUILD_TYPE=Release ..
$ make pmdplay
```

The following steps build `pmdplay.exe` on a Windows o.s. box with MSVC, vcpkg, SDL2 and Ninja installed with vcpkg.

You can have Your MSVC build environment set, on a Windows 10 box, if Your MSVC is Microsoft Visual Studio 2019 Community edition, using Windows 10 taskbar search box writing `x64 Native Tools Command Prompt for VS 2019` and starting matching App.
Otherwise, if MSVC is installed in default location, if Windows SDK is 10.0.18362.0 (please see what is in 'C:\Program Files (x86)\Microsoft SDKs\Windows Kits\10\ExtensionSDKs\Microsoft.UniversalCRT.Debug' folder) (see [1]) issuing

```windows command-line interface
C:\Users\gzaff>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64 10.0.18362.0
```

Then

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G Ninja -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
C:\pmdmini\build>ninja pmdplay
```

For the case that Visual Studio can be used

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G "Visual Studio 16 2019" -A x64 -T host=x64 -D CMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```

For building from command line

```windows command-line interface
C:\pmdmini\build>cmake --build . --config Release --target pmdplay
```

Otherwise one can start Microsoft Visual Studio and build&debug pmdmini solution.

You must have Your MSVC build environment set, on a Windows 7 box, as a prerequisite.
If MSVC is installed in default location, if Windows SDK is 10.0.17763.0 (please see what is in 'C:\Program Files (x86)\Microsoft SDKs\Windows Kits\10\ExtensionSDKs\Microsoft.UniversalCRT.Debug' folder) (see [1]) issuing

```windows command-line interface
C:\Users\gzaff>"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64 10.0.17763.0
```

Then

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G Ninja -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
C:\pmdmini\build>ninja pmdplay
```

For the case that Visual Studio can be used

```windows command-line interface
C:\>"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd\git" clone https://github.com/gzaffin/pmdmini.git
C:\>cd pmdmini
C:\pmdmini>mkdir build
C:\pmdmini>cd build
C:\pmdmini\build>cmake -G "Visual Studio 15 2017 Win64" -T host=x64 -D CMAKE_TOOLCHAIN_FILE=C:/Users/gzaff/Devs/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```

For building from command line

```windows command-line interface
C:\pmdmini\build>cmake --build . --config Release --target pmdplay
```

Otherwise one can start Microsoft Visual Studio and build&debug pmdmini solution.

Recap of required MACRO definitions:

`CMAKE_TOOLCHAIN_FILE`: full PATH of vcpkg.cmake

[1]
calling vcvarsall.bat will update PATH variable, so "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake" and "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja" can be called as cmake and ninja respectively

# Links
Reference information pages about how to install and how to use Vcpkg

[GitHub Microsoft vcpkg](https://github.com/Microsoft/vcpkg)

[vcpkg: A C++ package manager for Windows, Linux and MacOS](https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019)

[Eric Mittelette's blog](https://devblogs.microsoft.com/cppblog/vcpkg-a-tool-to-acquire-and-build-c-open-source-libraries-on-windows/)

# License

This code is available open source under the terms of the [GNU General Public License version 2](https://opensource.org/licenses/GPL-2.0).
