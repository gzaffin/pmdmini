cmake_minimum_required(VERSION 3.10)

if(MSVC)
  set(CMAKE_C_FLAGS "/std::c++latest /Ox /W3 /wd4996")
else()
  set(CMAKE_C_FLAGS "-O3 -Wall")
endif()

include_directories(./.. fmgen pmdwin)

file(GLOB SOURCES *.c fmgen/*.cpp pmdwin/*.cpp)

add_library(pmdmini STATIC ${SOURCES})
