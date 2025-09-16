
cmake_minimum_required(VERSION 3.31.0)
project(EllipseEngine VERSION 1.0)

add_link_options("-L/opt/homebrew/Cellar/llvm/21.1.0/lib/c++/")
add_link_options("-L/opt/homebrew/Cellar/llvm/21.1.0/lib/")
add_link_options("-L/Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/lib/")

add_link_options("-I/opt/homebrew/Cellar/llvm/21.1.0/include/")
add_link_options("-I/opt/homebrew/Cellar/llvm/21.1.0/include/c++/v1")
add_link_options("-I/Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/include")
add_link_options("-I/Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/include/c++/v1")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/lib)

include(CMake/ProjectSettings.cmake)


add_subdirectory(src)

