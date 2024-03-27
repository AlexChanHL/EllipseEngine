function(set_project_warnings project_name)

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
         # -Wformat=2
        )
   
    set(CLANG_WARNINGS ${CLANG_WARNINGS}
      -Wno-error=unused
      -Wno-error=unused-parameter
      )

 if(WARNING_AS_ERRORS)
   set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
    else()
     message("No compiler warnings")
   endif()

  target_compile_options(${project_name} INTERFACE ${CLANG_WARNINGS})

endfunction()
