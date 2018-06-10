for MSYS2/minGW(mingw64) and cmake and pkg-config and Microsoft Windows 7 o.s.

    install required packages with pacman

$ pacman -S mingw-w64-x86_64-pkg-config mingw-w64-x86_64-SDL2 mingw-w64-x86_64-cmake

    clone and compile

$ git clone https://github.com/gzaffin/mdxmini.git
$ cd mdxmini
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" ..
$ make -j 4 mdxplay
