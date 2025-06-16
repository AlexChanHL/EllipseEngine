
set(TEST_APP_NAME "${PROJECT_NAME}Demo")
add_executable(${TEST_APP_NAME})

    set(SOURCES
        Core/main.cpp
        Core/DemoApp.cpp
        Core/DemoLayer.cpp
        Core/DemoLayer.hpp
       )

    set(HEADERS

         )

target_sources(${TEST_APP_NAME} PUBLIC
               ${SOURCES} ${HEADERS}
              )

target_link_libraries(${TEST_APP_NAME} PRIVATE EllipseEngineInterface EllipseEngine
                     )

include("${CMAKE_SOURCE_DIR}/CMake/ProjectWarnings.cmake")

add_library(AppWarnings INTERFACE)
createWarningsLibrary(AppWarnings)

target_link_libraries(${TEST_APP_NAME} PRIVATE AppWarnings)

target_include_directories(${TEST_APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

