
add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(stb_image)

add_library(EngineVendor INTERFACE)

include(FetchContent)

# if(BUILD_WITH_SOURCE)
# createSubdirectory(SDL)
# createSubdirectory(glm)
# endif()
# if(BUILD_WITH_GITHUB_HOOK)

FetchContent_Declare(
uLogger
GIT_REPOSITORY https://github.com/AUniqueLaver/uLogger
# GIT_TAG

                   )

FetchContent_MakeAvailable(uLogger)

target_link_libraries(EngineVendor INTERFACE uLogger glad glm stb_image sdl3)
