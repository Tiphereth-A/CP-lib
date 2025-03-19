cmake_minimum_required(VERSION 3.10)
project(CP-lib CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.0)
        message(FATAL_ERROR "GCC version must be at least 12.0!")
    endif()
else()
    message(WARNING "Compiling without GCC may not be supported")
endif()

include_directories(include)