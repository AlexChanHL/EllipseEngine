set(NAME "EllipseEngine")

file(GLOB CURRENT_DIR
      *.cpp
      *.hpp
  )

file(GLOB_RECURSE CORE
    Core/*.cpp
    Core/*.hpp
      )

add_library(${NAME} STATIC
           ${CURRENT_DIR} ${CORE} 
             )

# add_custom_target()

target_link_libraries(${NAME} PUBLIC EngineVendor ProjectWarnings)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
