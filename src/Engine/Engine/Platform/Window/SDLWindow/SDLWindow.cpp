
#include "SDLWindow.hpp"
#include "Core/Base.hpp"
#include "Platform/GraphicsContext/SDLGraphicsContext.hpp"
#include "Debug/Log/Log.hpp"

// [ Add graphics context abstraction ]


namespace Ellipse
{

SDLWindow::SDLWindow(const WindowSettings& settings)
{
    const unsigned int initFlags{SDL_INIT_EVENTS | SDL_INIT_VIDEO};
    if(SDL_Init(initFlags) == 0)
    {
    ELLIPSE_ENGINE_LOG_ERROR("Failed to init sdl!");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG); 


    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    m_window = SDL_CreateWindow(settings.m_title.c_str(),
                                        settings.m_width,
                                        settings.m_height,
                                        SDL_WINDOW_RESIZABLE
                                    |   SDL_WINDOW_OPENGL 
                                        );

    m_windowData.m_width = settings.m_width;
    m_windowData.m_height = settings.m_height;

    // SDL_PropertiesID properties = SDL_GetWindowProperties(m_window);
    // SDL_SetProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, &m_windowData);

    SDL_AddEventWatch(SDLWindow::eventCallBackFn, &m_windowData);

    // [ Add graphics context abstraction ]

    m_graphicsContext = createSDLGraphicsContext(m_window, settings.m_gLib);


    makeSDLCurrentContext(m_window, m_graphicsContext.get());
    setSDLSwapInterval(m_graphicsContext.get(), 1);
}

SDLWindow::~SDLWindow()
{
   SDL_Quit();
   m_graphicsContext->deleteContext();
   // [ Delete the GL context ]
}

void SDLWindow::updateWindow()
{
   pollEvents();
   updateWindowInformation();
   SDL_GL_SwapWindow(m_window);
}

void SDLWindow::lockCursorToWindow()
{
    SDL_SetWindowRelativeMouseMode(m_window, true);


    // [ SDL_GetRelativeMouseState() will return the offset
    //   of border window to the center of screen when
    //   SDL_WarpMouseInWindow() is called, and calling
    //   mode will the mouse at the center ]

    SDL_WarpMouseInWindow(m_window, static_cast<float>(m_windowData.m_width) / 2.0f, static_cast<float>(m_windowData.m_height) / 2.0f);
}

void SDLWindow::unlockCursorToWindow()
{
    SDL_SetWindowRelativeMouseMode(m_window, false);
}

void SDLWindow::disableReportEvents()
{
    SDL_RemoveEventWatch(SDLWindow::eventCallBackFn, &m_windowData);
}

void SDLWindow::pollEvents()
{
   SDL_Event e;
   while(SDL_PollEvent(&e))
   {

   }
}

void SDLWindow::updateWindowInformation()
{
   // if(m_isCursorConstrained)
   // {
   // recenterMousePosition();
   // }
  
   m_mouseInformation.update(m_windowData.m_mousePosition,
                             m_windowData.m_offsetX,
                             m_windowData.m_offsetY);

   // m_mouseInformation.findOffsets(m_windowData.m_mousePosition);

}

}    // namespace Ellipse
