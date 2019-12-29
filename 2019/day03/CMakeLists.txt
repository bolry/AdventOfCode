cmake_minimum_required(VERSION 3.15)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(AdventOfCode2019Day03)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(aoc2019d03a)
target_sources(aoc2019d03a PRIVATE day03a_main.cpp)
target_compile_options(aoc2019d03a PRIVATE -Wall -Wextra -pedantic -Wno-c99-extensions)

add_executable(aoc2019d03b)
target_sources(aoc2019d03b PRIVATE day03b_main.cpp)
target_compile_options(aoc2019d03b PRIVATE -Wall -Wextra -pedantic -Wno-c99-extensions)
