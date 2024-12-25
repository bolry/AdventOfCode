cmake_minimum_required(VERSION 3.28...3.31)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

set(CMAKE_CXX_EXTENSIONS YES)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

project(AoC2024d25 LANGUAGES CXX)

#if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
#    add_compile_options(-stdlib=libc++)
#    add_link_options(-stdlib=libc++)
#endif ()

add_library(warnings INTERFACE)
if (MSVC)
    target_compile_options(warnings INTERFACE
            /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296
            /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619
            /w14640 /w14826 /w14905 /w14906 /w14928 /permissive-
    )
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(warnings INTERFACE
            -Wall -Wextra -Wextra-semi -Wshadow -Wnon-virtual-dtor
            -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
            -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference
            -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough
    )
endif ()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(warnings INTERFACE
            -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches
            -Wlogical-op -Wuseless-cast
    )
endif ()

add_executable(aoc2024d25a)
target_sources(aoc2024d25a PRIVATE aoc2024d25a.m.cpp)
target_compile_features(aoc2024d25a PRIVATE cxx_std_23)
target_link_libraries(aoc2024d25a PRIVATE warnings)
