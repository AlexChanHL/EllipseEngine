add_executable(${PROJECT_NAME})

    set(SOURCES
       Core/main.cpp
         )

    set(HEADERS

         )

target_sources(${PROJECT_NAME} PUBLIC
                  ${SOURCES} ${HEADERS}
             )

target_link_libraries(${PROJECT_NAME} PUBLIC
                   EllipseEngine ProjectWarnings
               )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
