#pragma once


#include "Core/Base.hpp"
#include "Core/GraphicsContext.hpp"
#include "EllipsePCH.hpp"
#include "Event/Event.hpp"

enum class WindowLibrary
{
    None,
    SDLWindow,
    GLFWWindow
};

struct WindowSettings
{
  public:
   i32_t m_width;
   i32_t m_height;
   std::string m_title;

   WindowLibrary m_lib;
   GraphicsLib m_gLib;
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
