
add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(stb_image)



add_library(EngineVendor INTERFACE)

include(FetchContent)

# if(BUILD_WITH_GITHUB_HOOK)

FetchContent_Declare(
sdlLib
GIT_REPOSITORY https://github.com/libsdl-org/SDL
GIT_TAG release-3.2.14

                   )

FetchContent_MakeAvailable(sdlLib)

FetchContent_Declare(
fmtLib
GIT_REPOSITORY https://github.com/fmtlib/fmt.git
GIT_TAG 11.2.0

                   )

FetchContent_MakeAvailable(fmtLib)

FetchContent_Declare(
sglLogger
GIT_REPOSITORY https://github.com/AUniqueLaver/sglLogger.git
GIT_TAG v1.0.0
                    )

FetchContent_MakeAvailable(sglLogger)


target_link_libraries(EngineVendor INTERFACE sglLogger glad stb_image SDL3::SDL3 fmt::fmt)

