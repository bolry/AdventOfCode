cmake_minimum_required(VERSION 3.12)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif ()

project(AoC2017Day07)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2017d07a)
target_sources(aoc2017d07a PRIVATE day07a_main.cpp)

add_executable(aoc2017d07b)
target_sources(aoc2017d07b PRIVATE day07b_main.cpp)
