
message("=======================")

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

option(BUILD_DEMO "Building demo program" ON)
   if(BUILD_DEMO)
    message(STATUS "Building demo example")
      add_compile_definitions(BUILD_DEMO)
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
