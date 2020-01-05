cmake_minimum_required(VERSION 3.15...3.17)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif ()

project(AdventOfCode2019Day06)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2019d06a)
target_sources(aoc2019d06a PRIVATE day06a_main.cpp)
target_compile_options(aoc2019d06a PRIVATE -Wall -Wextra -pedantic)

add_executable(aoc2019d06b)
target_sources(aoc2019d06b PRIVATE day06b_main.cpp)
target_compile_options(aoc2019d06b PRIVATE -Wall -Wextra -pedantic)
