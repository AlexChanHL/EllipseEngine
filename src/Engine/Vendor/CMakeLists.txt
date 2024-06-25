add_subdirectory(uLog)
add_subdirectory(SDL)

add_library(EngineVendor INTERFACE)

target_link_libraries(EngineVendor INTERFACE uLogger SDL3::SDL3)
