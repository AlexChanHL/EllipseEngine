#pragma once

#include "Core/Window.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/KeyboardEvent.hpp"
#include "Event/MouseEvent.hpp"

#include <SDL3/SDL.h>

#include <glad/glad.h>

class SDLWindow : public Window
{
  public:
    SDLWindow(const WindowSettings& settings);

    virtual void updateWindow() override;

    void pollEvents();
    virtual void setEventCallBack(const eventCallBackfn& event) override
    {
    m_windowData.m_eventCallBackFn = event;
    }

    virtual Pair<int, int> getWindowSize() override
    {
    return Pair<int, int>{m_windowData.m_width, m_windowData.m_height};
    }
    virtual void* getWindow() override { return m_window; }

    virtual ~SDLWindow() override;

  private:
    struct WindowData
     {
       int m_width;
       int m_height;
       eventCallBackfn m_eventCallBackFn;
     };

    SDL_Window* m_window;
    WindowData m_windowData;

    SDL_GLContext m_glContext = nullptr;

  private:
   static int eventCallBackFn(void* userData, SDL_Event* e)
 {
 WindowData* data = static_cast<WindowData*>(userData);

    switch(e->type)
   {
    case SDL_EVENT_QUIT:
      {
      WindowUserQuitEvent event;
      data->m_eventCallBackFn(event);
      return 0;
      }
    case SDL_EVENT_WINDOW_RESIZED:
      {
      SDL_Window* window = SDL_GetWindowFromID(e->window.windowID);

      int width, height;
      SDL_GetWindowSizeInPixels(window,
                                &width,
                                &height);
      data->m_width = width;
      data->m_height = height;
      WindowResizeEvent event(width, height);
      data->m_eventCallBackFn(event);
      return 0;
      }
    case SDL_EVENT_KEY_DOWN:
      {
      KeyboardPressedEvent event(e->key.keysym.sym);
      data->m_eventCallBackFn(event);
      return 0;
      }
    case SDL_EVENT_MOUSE_MOTION:
      {
      float mousePosX, mousePosY;
      SDL_GetMouseState(&mousePosX, &mousePosY);
      MouseMotionEvent event;
      event.setMousePosX(mousePosX);
      event.setMousePosY(mousePosY);
      data->m_eventCallBackFn(event);
      return 0;
      }
     case SDL_EVENT_MOUSE_BUTTON_DOWN:
      {
      MousePressedEvent event(e->button.button,
                              e->button.x,
                              e->button.y
                              );
      data->m_eventCallBackFn(event);
      }
     case SDL_EVENT_MOUSE_WHEEL:
      {
      MouseWheelEvent event(e->wheel.x,
                            e->wheel.y,
                            e->wheel.mouse_x,
                            e->wheel.mouse_y
                            );
      data->m_eventCallBackFn(event);
        return 0;
      }
     default:
      return 0;
    }
       return 0;
 }

};
