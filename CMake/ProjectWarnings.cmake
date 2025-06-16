
function(createWarningsLibrary name)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
   set(CLANG_WARNINGS
       -Wall
       -Wextra
       -Wshadow
       -Wnon-virtual-dtor
       -Wcast-align
       -Wunused
       -Woverloaded-virtual
       -Wpedantic
       -Wconversion
       -Wsign-conversion
       -Wnull-dereference
       -Wformat=2
       )
   set(CLANG_WARNINGS ${CLANG_WARNINGS}
        -Wno-error=unused
        -Wno-error=unused-command-line-argument
        -Wno-error=unused-parameter
       )

  if(WARNING_AS_ERRORS)
    set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
  else()
     message("No compiler warnings set")
  endif()

  message("Compiler warning set as clang")
  target_compile_options(${name} INTERFACE ${CLANG_WARNINGS})
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(GNU_WARNINGS
      -Wall
      -Wextra
      -Wshadow
      -Wnon-virtual-dtor
      -Wcast-align
      -Wunused
      -Woverloaded-virtual
      -Wpedantic
      -Wconversion
      -Wsign-conversion
      -Wnull-dereference
      -Wformat=2
     )

  set(GNU_WARNINGS ${GNU_WARNINGS}  
      -Wno-error=unused
      -Wno-error=unused-parameter
      -Wno-error=unused-variable
     )

  if(WARNING_AS_ERRORS)
   set(GNU_WARNINGS ${GNU_WARNINGS} -Werror)
  endif()

  message("Compiler warning set as gnu")
  target_compile_options(${name} INTERFACE ${GNU_WARNINGS})
endif()

endfunction()

