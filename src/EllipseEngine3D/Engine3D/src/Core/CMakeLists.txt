
set(NAME ${PROJECT_NAME})


file(GLOB_RECURSE CORE
     Core/*.hpp
     Core/*.cpp
    )

file(GLOB_RECURSE ELLIPSE
     *.hpp
)

add_library(${NAME} STATIC
            ${ELLIPSE} ${CORE}
           )

target_link_libraries(${NAME} PRIVATE EllipseEngineInterface)

add_library(${NAME}::${NAME} ALIAS 
						${NAME}
           )

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

