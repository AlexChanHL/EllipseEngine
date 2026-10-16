
#include "Window.hpp"

#include "Platform/Window/SDLWindow/SDLWindow.hpp"

#include "Base.hpp"


namespace Ellipse
{

UniquePtr<Window> Window::createWindow(const WindowSettings& settings)
{
     switch(settings.m_media)
     {
     case WindowLibrary::SDLWindow:
     {
     return createUnique<SDLWindow>(settings);
     }
     case WindowLibrary::GLFWWindow:
     {
     ELLIPSE_ENGINE_LOG_WARN("No GLFW class\n");
     return nullptr;
     }
     default:
     // LOG_MESSAGE("Failed to create window");
     return nullptr;
     }
    
     // LOG_MESSAGE("Failed to create window");
   
     return nullptr;
}

}     // namespace Ellipse

