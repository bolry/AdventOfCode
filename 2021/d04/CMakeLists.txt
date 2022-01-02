cmake_minimum_required(VERSION 3.21.1)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

project(AoC2021d04)

set(CMAKE_CXX_EXTENSIONS YES)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

include(FetchContent)
FetchContent_Declare(MyFmt GIT_REPOSITORY git://github.com/fmtlib/fmt.git GIT_TAG origin/master)
FetchContent_Declare(MyGsl GIT_REPOSITORY https://github.com/microsoft/GSL.git GIT_TAG origin/main)
FetchContent_MakeAvailable(MyFmt MyGsl)

add_executable(aoc2021d04a aoc2021d04a.m.cpp)
target_include_directories(aoc2021d04a PRIVATE "")
target_link_libraries(aoc2021d04a PRIVATE fmt::fmt Microsoft.GSL::GSL)

add_executable(aoc2021d04b aoc2021d04b.m.cpp)
target_include_directories(aoc2021d04b PRIVATE "")
target_link_libraries(aoc2021d04b PRIVATE fmt::fmt Microsoft.GSL::GSL)
