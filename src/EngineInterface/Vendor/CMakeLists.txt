
add_subdirectory(glad)
add_subdirectory(stb_image)


add_library(EngineVendor INTERFACE)

include(FetchContent)

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
SYSTEM
                   )

FetchContent_MakeAvailable(fmtLib)

FetchContent_Declare(
glmLib
GIT_REPOSITORY https://github.com/g-truc/glm.git
GIT_TAG 1.0.1
SYSTEM
                   )

FetchContent_MakeAvailable(glmLib)

FetchContent_Declare(
sglLogger
GIT_REPOSITORY https://github.com/AUniqueLaver/sglLogger.git
GIT_TAG main
                    )

FetchContent_MakeAvailable(sglLogger)


target_link_libraries(EngineVendor INTERFACE glad stb_image SDL3::SDL3 fmt::fmt)

