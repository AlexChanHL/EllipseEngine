#pragma once

#include "Core/Window.hpp"
#include "Core/GraphicsContext.hpp"
#include "Core/MouseInformation.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/KeyboardEvent.hpp"
#include "Event/MouseEvent.hpp"

#include <SDL3/SDL.h>

#include <glad/glad.h>


namespace Ellipse
{

class SDLWindow : public Window
{
  public:
    SDLWindow(const WindowSettings& settings);
    virtual ~SDLWindow() override;

    virtual void updateWindow() override;

    virtual void lockCursorToWindow() override;    
    virtual void unlockCursorToWindow() override;    

    virtual void disableReportEvents() override;

    void pollEvents();

    void updateWindowInformation();

    virtual void setEventCallBack(const eventCallBackfn& event) override
    {
    m_windowData.m_eventCallBackFn = event;
    }

    virtual Pair<float, float> mouseOffsets() const override
    {
    return createPair<float, float>(m_windowData.m_offsetX, m_windowData.m_offsetY);
    }

    virtual MousePosition mousePositions() const override
    {
    return m_windowData.m_mousePosition;
    }

    virtual Pair<i32_t, i32_t> getWindowSize() override
    {
    return Pair<i32_t, i32_t>{m_windowData.m_width, m_windowData.m_height};
    }

    virtual void* getWindow() override
    {
    return m_window;
    }

  private:
   struct WindowData
   {
      public:
       WindowData()
       : m_width{0},
         m_height{0},
         m_mousePosition{MousePosition{}},
         m_offsetX{0},
         m_offsetY{0}
       {

       }
       ~WindowData()
       {

       }

      public:
       int m_width;
       int m_height;

       MousePosition m_mousePosition;

       float m_offsetX;
       float m_offsetY;

       eventCallBackfn m_eventCallBackFn;
   };

    SDL_Window* m_window;
    WindowData m_windowData;

    MouseInformation m_mouseInformation;
    // KeyboardInformation m_keyboardInformation;

    UniquePtr<GraphicsContext> m_graphicsContext = nullptr;


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
   KeyboardPressedEvent event(static_cast<u32_t>(e->key.keysym.sym));
   data->m_eventCallBackFn(event);
   return 0;
   }
   case SDL_EVENT_MOUSE_MOTION:
   {
   float mousePosX = 0;
   float mousePosY = 0;

   SDL_GetMouseState(&mousePosX, &mousePosY);
   data->m_mousePosition.setX(mousePosX);
   data->m_mousePosition.setY(mousePosY);

   float offsetX = 0;
   float offsetY = 0;

   SDL_GetRelativeMouseState(&offsetX, &offsetY);

   data->m_offsetX = offsetX;
   data->m_offsetY = offsetY;

   MouseMotionEvent event;
   event.setMousePositionX(mousePosX);
   event.setMousePositionY(mousePosY);
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
                         e->wheel.mouseX,
                         e->wheel.mouseY
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

}
