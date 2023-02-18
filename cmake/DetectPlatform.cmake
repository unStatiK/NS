cmake_minimum_required (VERSION 3.13.5)

string(TOUPPER "${CMAKE_C_COMPILER_ID}" COMPILER_ID)
string(TOUPPER "${CMAKE_GENERATOR_PLATFORM}" PLATFORM_ID)

if ("${COMPILER_ID}" STREQUAL "MSVC")
    if ("${PLATFORM_ID}" STREQUAL "X64")
        set(FOUNDED_PLATFORM x64)
        set(PLATFORM_FOUND true)
    endif()
    if ("${PLATFORM_ID}" STREQUAL "WIN32")
        set(FOUNDED_PLATFORM x86)
        set(PLATFORM_FOUND true)
    endif()
endif()

if (PLATFORM_FOUND)   
    message(STATUS "PLATFORM: ${CMAKE_GENERATOR_PLATFORM}")
    message(STATUS "COMPILER: ${CMAKE_C_COMPILER_ID}")
else()
    message(FATAL_ERROR "Building for platform or target compiler not support.")
endif ()


