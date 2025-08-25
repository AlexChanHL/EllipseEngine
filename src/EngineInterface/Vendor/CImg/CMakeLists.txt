cmake_minimum_required(VERSION 3.27)
project(CImg DESCRIPTION "C Img" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY "CImg")

add_library(${LIBRARY} INTERFACE
            CImg.h
           )

target_include_directories(${LIBRARY}
	INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
                           )

