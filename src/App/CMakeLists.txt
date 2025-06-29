
set(TEST_APP_NAME "${PROJECT_NAME}Demo")
add_executable(${TEST_APP_NAME})

if(NOT (${BUILD_ENGINE_2D} STREQUAL ${BUILD_ENGINE_3D}))
 if(${BUILD_ENGINE_2D})
  file(GLOB 2D_DIR
       2D/Core/*.cpp
       2D/Core/*.hpp
      )
 endif()
  
 if(${BUILD_ENGINE_3D})
  file(GLOB 3D_DIR
       3D/Core/*.cpp
       3D/Core/*.hpp
      )
 endif()

endif()

target_sources(${TEST_APP_NAME} PUBLIC
       	       ${3D_DIR} ${2D_DIR}
              )

target_link_libraries(${TEST_APP_NAME} PRIVATE EllipseEngineInterface EllipseEngine
                     )

include("${CMAKE_SOURCE_DIR}/CMake/ProjectWarnings.cmake")

add_library(AppWarnings INTERFACE)
createWarningsLibrary(AppWarnings)

target_link_libraries(${TEST_APP_NAME} PRIVATE AppWarnings)

target_include_directories(${TEST_APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

