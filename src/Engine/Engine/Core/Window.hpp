#pragma once

#include "Event/Event.hpp"

#include "EllipsePCH.hpp"

enum class WindowLibrary
{
    None, SDLWindow, GLFWWindow
};

struct WindowSettings
{
   int m_width;
   int m_height;
   std::string m_title;

   WindowLibrary m_lib;
};

class Window
{
   public:
    using eventCallBackfn = std::function<void(Event&)>;

    Window() = default;
    static Window* createWindow(const WindowSettings& specs);
     
    virtual void updateWindow() = 0;
    virtual void setEventCallBack(const eventCallBackfn& event) = 0;
    virtual void* getWindow() = 0;

  virtual ~Window() = default;

   private:
};
