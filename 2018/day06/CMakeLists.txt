cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2018Day06)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2018d06a)
target_sources(aoc2018d06a PRIVATE day06a_main.cpp)

add_executable(aoc2018d06b)
target_sources(aoc2018d06b PRIVATE day06b_main.cpp)
