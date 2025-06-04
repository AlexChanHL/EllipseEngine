
set(NAME ${PROJECT_NAME})


file(GLOB_RECURSE CORE
     Core/*.hpp
     Core/*.cpp
    )

add_library(${NAME} STATIC
						${CORE}
           )

target_link_libraries(${NAME} PRIVATE EllipseEngineInterface)

add_library(${NAME}::${NAME} ALIAS 
						${NAME}
           )

