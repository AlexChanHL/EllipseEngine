cmake_minimum_required(VERSION 3.27)
project(Stb DESCRIPTION "Stb image" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY "stb_image")

set(SOURCES
    stb_image.cpp
    stb_image.h)

add_library(${LIBRARY} ${SOURCES})

target_include_directories(${LIBRARY}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
