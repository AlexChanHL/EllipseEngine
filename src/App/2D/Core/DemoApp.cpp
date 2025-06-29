
#include "DemoLayer.hpp"

#include "Ellipse.hpp"


ForwardList<SharedPtr<Ellipse::Layer>> Ellipse::Application::createUserProcesses()
{
   ForwardList<SharedPtr<Ellipse::Layer>> layers;

   // SharedPtr<GUILayer> guiLayer = createShared<GUILayer>(Ellipse::Application::get().getEngine());
   // layers.push_front(std::move(guiLayer));

   SharedPtr<DemoLayer> demoLayer = createShared<DemoLayer>(Ellipse::Application::get().getEngine());
   layers.push_front(std::move(demoLayer));

   layers.reverse();

   return layers;
}

Ellipse::ApplicationConfig::ApplicationConfig()
{
   m_windowSettings.m_media = WindowLibrary::SDLWindow;
   m_windowSettings.m_graphics = GraphicsLibrary::OpenGL;

   m_windowSettings.m_width = 1280;
   m_windowSettings.m_height = 640;

   m_graphicsSpec = GraphicsSpec::OpenGL;

   m_systems.push_back(Pair<String, bool>{"Logger", true});
   m_systems.push_back(Pair<String, bool>{"Time", true});
   m_systems.push_back(Pair<String, bool>{"Window", true});
   m_systems.push_back(Pair<String, bool>{"Render", true});
   m_systems.push_back(Pair<String, bool>{"Model", true});
   m_systems.push_back(Pair<String, bool>{"RenderModule", true});
}

