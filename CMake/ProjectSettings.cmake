
message("=======================")

message("==Ellipse Cmake Setting=")

option(DEACTIVATE_LOGGING "Disable logging" OFF)
 if(DEACTIVATE_LOGGING)
  message(STATUS "Deactivating logging")
  add_compile_definitions(DEACTIVATE_LOGGING)
 endif()

option(DEBUG "Enable debug mode" ON)
 if(DEBUG)
  message(STATUS "Enabling debug mode")
  add_compile_definitions(DEBUG)
 endif()

option(BUILD_ENGINE_2D "Building engine 2D" ON)
 if(BUILD_ENGINE_2D)
  message(STATUS "Building engine 2D")
 endif()

option(BUILD_ENGINE_3D "Building engine 3D" ON)
 if(BUILD_ENGINE_3D)
  message(STATUS "Building engine 3D")
 endif()

option(ELLIPSE_TEST_APP "Building app program" ON)
 if(ELLIPSE_TEST_APP)
  message(STATUS "Building test app example")
 endif()

option(WARNING_AS_ERRORS "Treat warnings as errors" ON)
 if(WARNING_AS_ERRORS)
  message(STATUS "Treating warnings as errors")
 endif()

option(BUILD_ENGINE_WITH_PRECOMPILED_HEADERS "Build engine with precompiled headers" ON)
 if(!CMAKE_VERSION VERSION_GREATER_EQUAL 3.16)
  message(STATUS "Version higher needed to use precompiled headers feature with cmake")
 endif()
 if(BUILD_ENGINE_WITH_PRECOMPILED_HEADERS)
  message(STATUS "Building engine with precompiled headers")
 endif()

message("=======================")
