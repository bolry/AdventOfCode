cmake_minimum_required(VERSION 3.24...3.25)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

project(AoC2022d03)

set(CMAKE_CXX_EXTENSIONS YES)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_C_EXTENSIONS YES)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED NO)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif ()

add_executable(aoc2022d03a aoc2022d03a.m.cpp)
add_executable(aoc2022d03b aoc2022d03b.m.cpp)
