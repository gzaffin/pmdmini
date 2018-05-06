cmake_minimum_required(VERSION 3.10)

if(MSVC)
	set(CMAKE_C_FLAGS "/Ox /W3 /wd4996")
else()
	set(CMAKE_C_FLAGS "-std=c11 -O3 -Wall")
endif()

add_subdirectory(src)

file(GLOB SOURCES sdlplay.c)

include_directories(src src/fmgen src/pmdwin)

add_executable(pmdplay EXCLUDE_FROM_ALL ${SOURCES})

target_link_libraries(pmdplay pmdmini)

