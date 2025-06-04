
#include "SDLGraphicsContext.hpp"
#include "Debug/Log.hpp"

#include <glad/glad.h>


namespace Ellipse
{

void makeSDLCurrentContext(SDL_Window* window, GraphicsContext* context)
{
    switch(context->getGraphicsLibrary())
    {
    case GraphicsLibrary::OpenGL:
    SDL_GL_MakeCurrent(window, (SDL_GLContext)context->getContext());
    break;
    case GraphicsLibrary::Vulkan:
    // [ Make vulkan current context ]
    break;
    default:
    break;
    }
}

void setSDLSwapInterval(GraphicsContext* context, i32_t v)
{
    switch(context->getGraphicsLibrary())
    {
    case GraphicsLibrary::OpenGL:
    SDL_GL_SetSwapInterval(1);
    break;
    case GraphicsLibrary::Vulkan:
    // [ Set vulkan swap interval ]
    break;
    default:
    break;
    }
}

UniquePtr<GraphicsContext> createSDLGraphicsContext(SDL_Window* window, GraphicsLibrary graphics)
{
    switch(graphics)
    {
    case GraphicsLibrary::OpenGL:
    {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
    ELLIPSE_ENGINE_LOG_ERROR("Could not load function pointers!");
    }
    return createUnique<SDLOpenGLGraphicsContext>(glContext);
    }
    case GraphicsLibrary::Vulkan:
    {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    return createUnique<SDLOpenGLGraphicsContext>(glContext);
    }
    default:
    break;
    }

    ELLIPSE_ENGINE_LOG_ERROR("No graphics context");

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    return createUnique<SDLOpenGLGraphicsContext>(glContext);
}

}    // namespace Ellipse
