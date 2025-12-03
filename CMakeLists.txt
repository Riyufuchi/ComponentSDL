cmake_minimum_required(VERSION 3.20)
project(ComponentSDL LANGUAGES C CXX)

#
# C++ version
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Default build type
#
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

#
# Warnings
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_definitions(NOMINMAX)
	add_compile_options(/W4)
endif()

#
# Optimization
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif()

#
# SDL2
#
set(SDL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL)

add_library(SDL2 STATIC IMPORTED)

if (WIN32)
	set_target_properties(SDL2 PROPERTIES
	IMPORTED_LOCATION ${SDL_LIB_DIR}/windows/x64/SDL2.lib
	INTERFACE_INCLUDE_DIRECTORIES ${SDL_LIB_DIR})
else()
	set_target_properties(SDL2 PROPERTIES
	IMPORTED_LOCATION ${SDL_LIB_DIR}/linux/libSDL2.a
	INTERFACE_INCLUDE_DIRECTORIES ${SDL_LIB_DIR})
endif()

#
# Library itself
#
file(MAKE_DIRECTORY build)

file(GLOB_RECURSE APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(ComponentSDL STATIC ${APP_SOURCES})

# Link everything
target_link_libraries(ComponentSDL PRIVATE
	SDL2
)
