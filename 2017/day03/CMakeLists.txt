cmake_minimum_required(VERSION 3.12)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif ()

project(AoC2017Day03)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2017d03a)
target_sources(aoc2017d03a PRIVATE day03_main.cpp)

add_executable(aoc2017d03b)
target_sources(aoc2017d03b PRIVATE day03b_main.cpp)
