cmake_minimum_required (VERSION 2.8.7)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set (CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
    endif ()
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

project (graph-analyzer)

add_executable (graph-analyzer analyzer.cpp)
