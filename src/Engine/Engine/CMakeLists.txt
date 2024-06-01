set(NAME "EllipseEngine")

file(GLOB CURRENT_DIR
      *.cpp
      *.hpp
  )

file(GLOB_RECURSE CORE
    Core/*.cpp
    Core/*.hpp
      )

file(GLOB_RECURSE LOG
    Debug/Log/Log.cpp
    Debug/Log/Log.hpp
      )

add_library(${NAME} STATIC
           ${CURRENT_DIR} ${CORE} ${LOG}
             )

target_link_libraries(${NAME} PUBLIC EngineVendor ProjectWarnings)

 if(BUILD_ENGINE_WITH_PRECOMPILED_HEADERS)
target_precompile_headers(${NAME} PUBLIC EllipsePCH.hpp)
 set(CMAKE_PCH_INSTANIATE_TEMPLATES ON)
  endif()
  
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
