
add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(stb_image)



add_library(EngineVendor INTERFACE)

include(FetchContent)

# if(BUILD_WITH_GITHUB_HOOK)

# FetchContent_Declare(
# uLogger
# GIT_REPOSITORY https://github.com/AUniqueLaver/uLogger
# # GIT_TAG
#
#                    )
#
# FetchContent_MakeAvailable(uLogger)

FetchContent_Declare(
sdlLib
GIT_REPOSITORY https://github.com/libsdl-org/SDL
GIT_TAG release-3.2.12

                   )

FetchContent_MakeAvailable(sdlLib)

FetchContent_Declare(
fmtLib
GIT_REPOSITORY https://github.com/fmtlib/fmt 
GIT_TAG 11.2.0
                   )

FetchContent_MakeAvailable(fmtLib)

add_library(uLogger INTERFACE)

target_link_libraries(EngineVendor INTERFACE uLogger glad glm stb_image SDL3::SDL3 fmt)

