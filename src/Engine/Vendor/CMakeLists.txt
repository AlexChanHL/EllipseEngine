add_subdirectory(uLog)
add_subdirectory(SDL)
add_subdirectory(glad)
add_subdirectory(glm)

add_library(EngineVendor INTERFACE)

target_link_libraries(EngineVendor INTERFACE uLogger glad glm SDL3::SDL3)
