cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 2.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mpags-cipher mpags-cipher.cpp)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

target_compile_features(mpags-cipher 
    PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization)