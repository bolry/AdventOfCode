cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2018Day16)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2018d16a)
target_sources(aoc2018d16a PRIVATE day16a_main.cpp)

add_executable(aoc2018d16b)
target_sources(aoc2018d16b PRIVATE day16b_main.cpp)
