add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(SDL)
add_subdirectory(stb_image)
add_subdirectory(uLog)

add_library(EngineVendor INTERFACE)

# target_link_libraries(EngineVendor INTERFACE uLogger glad glm stb_image sdl3)
target_link_libraries(EngineVendor INTERFACE uLogger glad glm stb_image SDL3::SDL3)
