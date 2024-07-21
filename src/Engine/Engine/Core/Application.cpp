
#include "Application.hpp"
#include "Debug/Log/Log.hpp"

namespace Ellipse
{

Application* Application::sInStance = nullptr;

Application::Application()
{
    sInStance = this;
}

void Application::init(const ApplicationSpecifications& specs)
{
  m_window = Window::createWindow(specs.m_windowSettings);
  m_window->setEventCallBack(BIND_EVENT_FN(Application::onEvent));

   // Change the name of this
   // Use forward-list
   // std::shared_ptr<Layer> layer = specs.m_userFunc();
  
   auto renderPlugin = RenderPlugin::createRenderPlugin(specs.m_graphicSpec);
  
  m_renderer = Renderer::createRenderer(std::move(renderPlugin));

  std::vector<std::shared_ptr<Layer>> layers = specs.m_userFunc();

   for(uint i=0;i<layers.size();i++)
     {
    pushLayer(layers[i]);
     }

   for(uint i=0;i<layers.size();i++)
     {
    layers[i]->init();
     }
}

Application::~Application()
{

}
void Application::pushLayer(std::shared_ptr<Layer> layer)
{
     pushLayerToStack(m_layerStack, layer);
}

void Application::onEvent(Event& e)
{
   EventDispatcher dispatcher(e);
    dispatcher.dispatchEvent<WindowUserQuitEvent>(EventType::WindowUserQuitEvent,
                                  BIND_EVENT_FN(onWindowClose)
                                     );
    dispatcher.dispatchEvent<WindowResizeEvent>(EventType::WindowResizeEvent,
                                  BIND_EVENT_FN(onWindowResize)
                                     );
  
     updateLayerEvents(m_layerStack, e);
}

void Application::run()
{
    while(m_running)
       {
     updateLayerStack(m_layerStack);

     m_window->updateWindow();
       }
}

bool Application::onWindowClose(WindowUserQuitEvent& windowQuit)
{
    m_running = false;

    return true;
}

bool Application::onWindowResize(WindowResizeEvent& resizeEvent)
{
    m_renderer->setViewport(resizeEvent.width(), resizeEvent.height());

    return true;
}

}    //Ellipse namespace
