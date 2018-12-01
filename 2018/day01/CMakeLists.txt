cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2018Day01)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2018d01a)
target_sources(aoc2018d01a PRIVATE day01a_main.cpp)

add_executable(aoc2018d01b)
target_sources(aoc2018d01b PRIVATE day01b_main.cpp)
