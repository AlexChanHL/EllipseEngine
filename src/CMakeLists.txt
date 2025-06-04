
if(ELLIPSE_TEST_APP)
add_subdirectory(App)
endif()


add_subdirectory(EngineInterface)

if(BUILD_ENGINE_2D)
add_subdirectory(EllipseEngine2D)
add_library(EllipseEngine ALIAS EllipseEngine2D)
endif()
if(BUILD_ENGINE_3D)
add_subdirectory(EllipseEngine3D)
add_library(EllipseEngine ALIAS EllipseEngine3D)
endif()


