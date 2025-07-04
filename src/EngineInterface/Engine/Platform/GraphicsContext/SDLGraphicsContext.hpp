#pragma once

#include "Core/Base.hpp"
#include "Core/GraphicsContext.hpp"

#include <SDL3/SDL.h>


namespace Ellipse
{

class SDLOpenGLGraphicsContext final : public GraphicsContext
{
    public:
     SDLOpenGLGraphicsContext()
     {

     }
     SDLOpenGLGraphicsContext(SDL_GLContext context)
     : m_glContext{context}
     {

     }
     ~SDLOpenGLGraphicsContext()
     {

     }


     virtual void deleteContext() override
     {
     SDL_GL_DestroyContext(m_glContext);
     }

     virtual GraphicsLibrary getGraphicsLibrary() override
     {
     return GraphicsLibrary::OpenGL;
     }

     virtual void* getContext() override
     {
     return m_glContext;
     }

    private:
     SDL_GLContext m_glContext = nullptr;
};

void makeSDLCurrentContext(SDL_Window* window, GraphicsContext* context);
void setSDLSwapInterval(GraphicsContext* context, i32_t v);

UniquePtr<GraphicsContext> createSDLGraphicsContext(SDL_Window* window, GraphicsLibrary graphics);

}    // namespace Ellipse
