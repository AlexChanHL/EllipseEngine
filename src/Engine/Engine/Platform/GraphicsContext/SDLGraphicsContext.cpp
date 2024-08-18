
#include "SDLGraphicsContext.hpp"
#include "Debug/Log/Log.hpp"


#include <glad/glad.h>

void makeSDLCurrentContext(SDL_Window* window, GraphicsContext* context)
{
    switch(context->getGraphicsLib())
    {
    case GraphicsLib::OpenGL:
    SDL_GL_MakeCurrent(window, context->getContext());
    break;
    case GraphicsLib::Vulkan:
    // [ Make vulkan current context ]
    break;
    default:
    break;
    }
}

void setSDLSwapInterval(GraphicsContext* context, i32_t v)
{
    switch(context->getGraphicsLib())
    {
    case GraphicsLib::OpenGL:
    SDL_GL_SetSwapInterval(1);
    break;
    case GraphicsLib::Vulkan:
    // [ Set vulkan swap interval ]
    break;
    default:
    break;
    }
}

UniquePtr<GraphicsContext> createSDLGraphicsContext(SDL_Window* window, GraphicsLib specs)
{
    switch(specs)
    {
    case GraphicsLib::OpenGL:
     {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
     {
    ELPSE_ENGINE_LOG_ERROR("Could not load function pointers!");
     }
    return createUnique<SDLOpenGLGraphicsContext>(glContext);
     }
    case GraphicsLib::Vulkan:
     {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    return createUnique<SDLOpenGLGraphicsContext>(glContext);
     }
    default:
     break;
    }

    ELPSE_ENGINE_LOG_ERROR("No graphics context");

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    return createUnique<SDLOpenGLGraphicsContext>(glContext);
}
