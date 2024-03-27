
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

message("=======================")
