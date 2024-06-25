
#include "Window.hpp"

#include "Platform/Window/SDLWindow/SDLWindow.hpp"

#include "EllipsePCH.hpp"

Window* Window::createWindow(const WindowSettings& specs)
{
     switch(specs.m_lib)
      {
    case WindowLibrary::SDLWindow:
         {
        return new SDLWindow(specs);
         }
    case WindowLibrary::GLFWWindow:
         {
            return nullptr;
         }
       default:
     // LOG_MESSAGE("Failed to create window");
         return nullptr;
       }
    
   // LOG_MESSAGE("Failed to create window");
   
    return nullptr;
}
