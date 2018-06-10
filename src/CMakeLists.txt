if(MSVC)
	cmake_minimum_required(VERSION 3.10)
endif()

if(UNIX OR MINGW)
	cmake_minimum_required(VERSION 3.0)
endif()


if(MSVC)
	set(CMAKE_CXX_FLAGS "/std:c++latest /Ox /W3 /wd4996")
endif()
if(UNIX OR MINGW)
	set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall")
endif()

include_directories(./.. fmgen pmdwin)

file(GLOB SOURCES *.c fmgen/*.cpp pmdwin/*.cpp)

add_library(pmdmini STATIC ${SOURCES})
