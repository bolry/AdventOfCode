cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2018Day18)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2018d18a)
target_sources(aoc2018d18a PRIVATE day18a_main.cpp)

add_executable(aoc2018d18b)
target_sources(aoc2018d18b PRIVATE day18b_main.cpp)
