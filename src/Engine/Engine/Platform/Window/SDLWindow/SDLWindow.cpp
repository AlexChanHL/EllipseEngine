
#include "SDLWindow.hpp"
#include "Core/Base.hpp"
#include "Debug/Log/Log.hpp"

// [ Add graphics context abstraction ]


SDLWindow::SDLWindow(const WindowSettings& settings)
{
  const unsigned int initFlags{SDL_INIT_EVENTS | SDL_INIT_VIDEO};
  if(SDL_Init(initFlags) != 0)
   {
  ELPSE_ENGINE_LOG_ERROR("Failed to init sdl!");
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

  m_glContext = SDL_GL_CreateContext(m_window);

  SDL_GL_MakeCurrent(m_window, m_glContext);
  SDL_GL_SetSwapInterval(1);

  if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
   {
  ELPSE_ENGINE_LOG_ERROR("Could not load function pointers!");
   }
}

void SDLWindow::updateWindow()
{
   pollEvents();
   SDL_GL_SwapWindow(m_window);
}

void SDLWindow::pollEvents()
{
   SDL_Event e;
    while(SDL_PollEvent(&e))
      {

      }
}

SDLWindow::~SDLWindow()
{
   SDL_Quit();
   // [ Delete the GL context ]
}
