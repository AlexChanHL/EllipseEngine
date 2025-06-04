
set(NAME ${PROJECT_NAME})


file(GLOB_RECURSE CORE
     Core/*.hpp
     Core/*.cpp
    )

add_library(${NAME} STATIC
						${CORE}
           )

target_link_libraries(EllipseEngine2D PRIVATE EllipseEngineInterface)

add_library(EllipseEngine2D::EllipseEngine2D ALIAS 
            EllipseEngine2D
           )

