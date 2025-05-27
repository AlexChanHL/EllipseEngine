
set(NAME "EllipseEngine")

file(GLOB CURRENT_DIR
      *.cpp
      *.hpp
  )

file(GLOB_RECURSE CORE
    Core/*.cpp
    Core/*.hpp
      )

file(GLOB_RECURSE ENGINE
    Engine/*.cpp
    Engine/*.hpp
      )

file(GLOB_RECURSE RENDER
    Renderer/*.cpp
    Renderer/*.hpp
      )

file(GLOB_RECURSE MATH
    Math/*.cpp
    Math/*.hpp
    Math/Random/*.cpp
    Math/Random/*.hpp
    )

file(GLOB_RECURSE EVENTS
    Event/*.cpp
    Event/*.hpp
      )

file(GLOB_RECURSE PLATFORM_GRAPHICS_CONTEXT
    Platform/GraphicsContext/*.cpp
    Platform/GraphicsContext/*.hpp
    )

file(GLOB_RECURSE PLATFORM_WINDOW
    Platform/Window/SDLWindow/*.cpp
    Platform/Window/SDLWindow/*.hpp
    Platform/Window/GLFWWindow/*.cpp
    Platform/Window/GLFWWindow/*.hpp
      )

file(GLOB_RECURSE PLATFORM_RENDER
    Platform/RenderPlugin/OpenGL/*.cpp
    Platform/RenderPlugin/OpenGL/*.hpp
      )
 
file(GLOB_RECURSE LOG
    Debug/Log/Log.cpp
    Debug/Log/Log.hpp
      )

add_library(${NAME} STATIC
            ${CURRENT_DIR} ${CORE} ${ENGINE} ${LOG} ${EVENTS} ${RENDER} ${PLATFORM_GRAPHICS_CONTEXT} ${PLATFORM_WINDOW} ${PLATFORM_RENDER} ${MATH}
           )

add_custom_target(CopyAssets ALL
           COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
           ${CMAKE_CURRENT_SOURCE_DIR}/Assets
           ${PROJECT_BINARY_DIR}/$<CONFIG>/bin/Assets
           COMMENT "Copying assets to binary dir"
                 )

add_dependencies(${NAME} CopyAssets)

target_link_libraries(${NAME} PUBLIC glm)
target_link_libraries(${NAME} PRIVATE EngineVendor)

target_link_libraries(${NAME} PRIVATE ProjectWarnings)

if(BUILD_ENGINE_WITH_PRECOMPILED_HEADERS)
target_precompile_headers(${NAME} PUBLIC EllipsePCH.hpp)
set(CMAKE_PCH_INSTANIATE_TEMPLATES ON)
endif()
  
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

