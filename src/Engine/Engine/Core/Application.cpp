
#include "Application.hpp"
#include "Debug/Log/Log.hpp"

namespace Ellipse
{

Application::Application()
{

}

void Application::init(const ApplicationSpecifications& specs)
{
  m_window = Window::createWindow(specs.m_windowSettings);
  m_window->setEventCallBack(BIND_EVENT_FN(Application::onEvent));

  Layer* layer = specs.m_userFunc();

  // for(int i=0;i<layers.size();i++)
  //   {
  pushLayer(layer);
    // }
}

Application::~Application()
{

}

void Application::pushLayer(Layer* layer)
{
     m_layer = layer;
}

void Application::onEvent(Event& e)
{
   EventDispatcher dispatcher(e);
    dispatcher.dispatchEvent<WindowUserQuitEvent>(EventType::WindowUserQuitEvent,
                                  BIND_EVENT_FN(onWindowClose)
                                     );

   if(m_layer)
    {
     m_layer->onEvent(e);
    }
}

void Application::run()
{
    while(m_running)
       {
      m_window->updateWindow();
       }
}

void Application::onWindowClose(WindowUserQuitEvent& windowQuit)
{
   m_running = false;
}

}    //Ellipse namespace
