add_subdirectory(uLog)

add_library(EngineVendor INTERFACE)

target_link_libraries(EngineVendor INTERFACE uLogger)
