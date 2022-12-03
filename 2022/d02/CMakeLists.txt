cmake_minimum_required(VERSION 3.24...3.25)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif ()

project(AoC2022d02)

set(CMAKE_CXX_EXTENSIONS YES)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_C_EXTENSIONS YES)
set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED NO)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

include(FetchContent)
FetchContent_Declare(FcFmt GIT_REPOSITORY ../../../../../../contrib/fmt GIT_TAG b0c8263cb26ea178d3a5df1b984e1a61ef578950)
FetchContent_Declare(FcGsl GIT_REPOSITORY ../../../../../../contrib/GSL GIT_TAG 517ed29228d18cf2c5004d10826090108e06f049)
FetchContent_MakeAvailable(FcFmt FcGsl)

if (MSVC)
    message(FATAL_ERROR "")
elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
else ()
    message(FATAL_ERROR "")
endif ()

add_executable(aoc2022d02a aoc2022d02a.m.cpp)
target_include_directories(aoc2022d02a PRIVATE "")
target_link_libraries(aoc2022d02a PRIVATE fmt::fmt Microsoft.GSL::GSL)
if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_precompile_headers(aoc2022d02a PRIVATE
            <algorithm> <any> <array> <atomic> <bit> <bitset> <cassert>
            <ccomplex> <cctype> <cerrno> <cfenv> <cfloat> <charconv> <chrono>
            <cinttypes> <ciso646> <climits> <clocale> <cmath> <codecvt>
            <compare> <complex> <concepts> <condition_variable> <csetjmp>
            <csignal> <cstdarg> <cstdbool> <cstddef> <cstdint> <cstdio>
            <cstdlib> <cstring> <ctgmath> <ctime> <cuchar> <cwchar> <cwctype>
            <deque> <exception> <filesystem> <forward_list> <fstream>
            <functional> <future> <initializer_list> <iomanip> <ios> <iosfwd>
            <iostream> <istream> <iterator> <limits> <list> <locale> <map>
            <memory> <memory_resource> <mutex> <new> <numbers> <numeric>
            <optional> <ostream> <queue> <random> <ranges> <ratio> <regex>
            <scoped_allocator> <set> <shared_mutex> <span> <sstream> <stack>
            <stdexcept> <streambuf> <string> <string_view> <system_error>
            <thread> <tuple> <type_traits> <typeindex> <typeinfo>
            <unordered_map> <unordered_set> <utility> <variant> <vector>
            <version>
            )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_precompile_headers(aoc2022d02a PRIVATE <bits/stdc++.h>)
endif ()
target_precompile_headers(aoc2022d02a PRIVATE
        <fmt/core.h>
        <gsl/gsl>
        )

add_executable(aoc2022d02b aoc2022d02b.m.cpp)
target_include_directories(aoc2022d02b PRIVATE "")
target_link_libraries(aoc2022d02b PRIVATE fmt::fmt Microsoft.GSL::GSL)
target_precompile_headers(aoc2022d02b REUSE_FROM aoc2022d02a)

add_executable(aoc2022d02balt aoc2022d02bAlt.m.cpp)
target_include_directories(aoc2022d02balt PRIVATE "")
target_link_libraries(aoc2022d02balt PRIVATE fmt::fmt Microsoft.GSL::GSL)
target_precompile_headers(aoc2022d02balt REUSE_FROM aoc2022d02a)
