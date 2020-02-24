if(MSVC OR MINGW)
	cmake_minimum_required(VERSION 3.10)
endif()

if(UNIX)
	cmake_minimum_required(VERSION 3.0)
endif()

if(MSVC)
	find_package(SDL2 REQUIRED)
	set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED YES)
endif()
if(UNIX OR MINGW)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(SDL2 REQUIRED sdl2)
	set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED YES)
endif()

add_subdirectory(src)

file(GLOB SOURCES sdlplay.c)

include_directories(src src/fmgen src/pmdwin)

add_executable(pmdplay EXCLUDE_FROM_ALL ${SOURCES})

if(MSVC)
	target_link_libraries(pmdplay PRIVATE pmdmini SDL2::SDL2)
endif()

if(UNIX OR MINGW)
	target_link_libraries(pmdplay PRIVATE pmdmini ${SDL2_LIBRARIES} m)
	target_include_directories(pmdplay PUBLIC ${SDL2_INCLUDE_DIRS})
	target_compile_options(pmdplay PUBLIC ${SDL2_FLAGS} ${SDL2_FLAGS_OTHERS})
endif()
