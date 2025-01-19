#pragma once


#include "Core/Base.hpp"
#include "Core/GraphicsContext.hpp"
#include "Core/Details/MousePosition.hpp"
#include "EllipsePCH.hpp"
#include "Event/Event.hpp"


namespace Ellipse
{

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
   String m_title;

   WindowLibrary m_lib;
   GraphicsLib m_gLib;
};

class Window
{
   public:
    using eventCallBackfn = std::function<void(Event&)>;

    Window() = default;
    virtual ~Window() = default;
    static UniquePtr<Window> createWindow(const WindowSettings& specs);
     
    virtual void updateWindow() = 0;

    virtual void lockCursorToWindow() = 0;
    virtual void unlockCursorToWindow() = 0;

    virtual void disableReportEvents() = 0;

    virtual void setEventCallBack(const eventCallBackfn& event) = 0;
    virtual Pair<float, float> mouseOffsets() const = 0;
    virtual MousePosition mousePositions() const = 0;
    virtual Pair<int, int> getWindowSize() = 0;
    virtual void* getWindow() = 0;

   private:
};

}     // namespace Ellipse




