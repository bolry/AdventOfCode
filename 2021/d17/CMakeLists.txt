cmake_minimum_required(VERSION 3.21.1...3.22)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

project(AoC2021d17)

set(CMAKE_CXX_EXTENSIONS YES)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

include(FetchContent)
FetchContent_Declare(MyFmt GIT_REPOSITORY ../../../../../../contrib/fmt GIT_TAG origin/master)
FetchContent_Declare(MyGsl GIT_REPOSITORY ../../../../../../contrib/GSL GIT_TAG origin/main)
FetchContent_MakeAvailable(MyFmt MyGsl)

add_executable(aoc2021d17a aoc2021d17a.m.cpp)
target_include_directories(aoc2021d17a PRIVATE "")
target_link_libraries(aoc2021d17a PRIVATE fmt::fmt Microsoft.GSL::GSL)
target_precompile_headers(aoc2021d17a PRIVATE
        <bits/stdc++.h>
        <fmt/core.h>
        <gsl/gsl>
        )

add_executable(aoc2021d17b aoc2021d17b.m.cpp)
target_include_directories(aoc2021d17b PRIVATE "")
target_link_libraries(aoc2021d17b PRIVATE fmt::fmt Microsoft.GSL::GSL)
target_precompile_headers(aoc2021d17b REUSE_FROM aoc2021d17a)