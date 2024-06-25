
#include "SDLWindow.hpp"
#include "Core/Base.hpp"
#include "Debug/Log/Log.hpp"

SDLWindow::SDLWindow(const WindowSettings& settings)
{
  const unsigned int initFlags{SDL_INIT_EVENTS | SDL_INIT_VIDEO};
  if(SDL_Init(initFlags) != 0)
    {
    ELLIPSE_ENGINE_LOG_ERROR("Failed to init sdl!");
    }

  m_window = SDL_CreateWindow(settings.m_title.c_str(),
                                        settings.m_width,
                                        settings.m_height,
                                        SDL_WINDOW_RESIZABLE
                                        );

  // SDL_PropertiesID properties = SDL_GetWindowProperties(m_window);
  // SDL_SetProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, &m_windowData);

  SDL_AddEventWatch(SDLWindow::eventCallBackFn, &m_windowData);
}

void SDLWindow::updateWindow()
{
   pollEvents();
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
}
