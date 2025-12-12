cmake_minimum_required(VERSION 3.28...4.1)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

project(Aoc2025d07 LANGUAGES CXX)

add_library(warnings INTERFACE)
if (MSVC)
    target_compile_options(warnings INTERFACE
            /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296
            /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619
            /w14640 /w14826 /w14905 /w14906 /w14928 /permissive-
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(warnings INTERFACE
            -Wall -Wextra -Wextra-semi -Wshadow -Wnon-virtual-dtor
            -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
            -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference
            -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough
            -fsanitize=address,undefined
    )
    target_compile_definitions(warnings INTERFACE
            _GLIBCXX_ASSERTIONS
            _GLIBCXX_DEBUG
            _GLIBCXX_DEBUG_PEDANTIC
    )
    target_link_options(warnings INTERFACE -fsanitize=address,undefined)
    target_precompile_headers(warnings INTERFACE <bits/stdc++.h>)
endif ()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(warnings INTERFACE
            -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches
            -Wlogical-op -Wuseless-cast
    )
endif ()

add_executable(aoc2025d07a)
target_sources(aoc2025d07a PRIVATE aoc2025d07a.m.cpp)
target_compile_features(aoc2025d07a PRIVATE cxx_std_26)
target_link_libraries(aoc2025d07a PRIVATE warnings)

add_executable(aoc2025d07b)
target_sources(aoc2025d07b PRIVATE aoc2025d07b.m.cpp)
target_compile_features(aoc2025d07b PRIVATE cxx_std_26)
target_link_libraries(aoc2025d07b PRIVATE warnings)
