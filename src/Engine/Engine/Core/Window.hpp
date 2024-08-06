#pragma once


#include "Core/Base.hpp"
#include "EllipsePCH.hpp"
#include "Event/Event.hpp"

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
    static UniquePtr<Window> createWindow(const WindowSettings& specs);
     
    virtual void updateWindow() = 0;
    virtual void setEventCallBack(const eventCallBackfn& event) = 0;
    virtual Pair<int, int> getWindowSize() = 0;
    virtual void* getWindow() = 0;

    virtual ~Window() = default;

   private:
};
