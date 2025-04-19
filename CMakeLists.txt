cmake_minimum_required(VERSION 3.27.7)
project(EllipseEngineDemo VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/lib)

include(CMake/ProjectSettings.cmake)

#Include this library to any library / application to set project warnings
#
add_library(ProjectWarnings INTERFACE)
include(CMake/ProjectWarnings.cmake)
set_project_warnings(ProjectWarnings)

add_subdirectory(src)
add_subdirectory(Vendor)
