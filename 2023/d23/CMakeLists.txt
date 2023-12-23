cmake_minimum_required(VERSION 3.25...3.27)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

project(AoC2023d23)

set(CMAKE_CXX_EXTENSIONS YES)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_C_EXTENSIONS YES)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED NO)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif ()


add_library(warnings INTERFACE)
if (MSVC)
    target_compile_options(warnings INTERFACE
            /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311
            /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826
            /w14905 /w14906 /w14928 /permissive-
    )
else ()
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
endif ()

add_executable(aoc2023d23a aoc2023d23a.m.cpp)
#target_compile_definitions(aoc2023d23a PRIVATE _GLIBCXX_DEBUG)
target_link_libraries(aoc2023d23a PRIVATE warnings)

add_executable(aoc2023d23b aoc2023d23b.m.cpp)
#target_compile_definitions(aoc2023d23b PRIVATE _GLIBCXX_DEBUG)
target_link_libraries(aoc2023d23b PRIVATE warnings)
