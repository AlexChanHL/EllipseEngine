
#include "Window.hpp"

#include "Platform/Window/SDLWindow/SDLWindow.hpp"

#include "Base.hpp"

UniquePtr<Window> Window::createWindow(const WindowSettings& specs)
{
     switch(specs.m_lib)
     {
     case WindowLibrary::SDLWindow:
     {
     return createUnique<SDLWindow>(specs);
     }
     case WindowLibrary::GLFWWindow:
     {
     std::cout << "No GLFW class\n";
     return nullptr;
     }
       default:
     // LOG_MESSAGE("Failed to create window");
         return nullptr;
       }
    
   // LOG_MESSAGE("Failed to create window");
   
    return nullptr;
}
