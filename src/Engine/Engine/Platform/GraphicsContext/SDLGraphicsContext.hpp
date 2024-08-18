#pragma once

#include "Core/Base.hpp"
#include "Core/GraphicsContext.hpp"

#include <SDL3/SDL.h>

class SDLOpenGLGraphicsContext final : public GraphicsContext
{
    public:
     SDLOpenGLGraphicsContext(SDL_GLContext context)
     : m_glContext{context}
     {

     }

     virtual GraphicsLib getGraphicsLib() override
     {
     return GraphicsLib::OpenGL;
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

UniquePtr<GraphicsContext> createSDLGraphicsContext(SDL_Window* window, GraphicsLib specs);
