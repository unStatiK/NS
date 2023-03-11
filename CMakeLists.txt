cmake_minimum_required (VERSION 3.13.5)

project (nslib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(DetectPlatform)
find_package(liblua REQUIRED)

add_subdirectory (nslib)
