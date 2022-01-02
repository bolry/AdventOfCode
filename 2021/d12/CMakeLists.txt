cmake_minimum_required(VERSION 3.21.1...3.22)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

project(AoC2021d12)

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

add_executable(aoc2021d12a aoc2021d12a.m.cpp)
target_include_directories(aoc2021d12a PRIVATE "")
target_link_libraries(aoc2021d12a PRIVATE fmt::fmt Microsoft.GSL::GSL)

add_executable(aoc2021d12b aoc2021d12b.m.cpp)
target_include_directories(aoc2021d12b PRIVATE "")
target_link_libraries(aoc2021d12b PRIVATE fmt::fmt Microsoft.GSL::GSL)
