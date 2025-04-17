
#include "Application.hpp"
#include "TimeModule.hpp"
#include "ModelManagerModule.hpp"
#include "Debug/Log/Log.hpp"

namespace Ellipse
{

Application* Application::sInStance = nullptr;

Application::Application()
: m_running{true},
  m_window{nullptr},
  m_renderer{nullptr},
  m_engine{nullptr}
{
  sInStance = this;
}

void Application::init(const ApplicationSpecifications& specs)
{
  m_engine = Engine::createEngine();

  m_window = Window::createWindow(specs.m_windowSettings);
  m_window->setEventCallBack(BIND_EVENT_FN(Application::onEvent));


  // [ Create a render plugin with init data in the renderer hpp file ]
  auto renderPlugin = RenderPlugin::createRenderPlugin(specs.m_graphicSpec);
   
  m_renderer = Renderer::createRenderer(std::move(renderPlugin));
  Pair<int, int> winSize = m_window->getWindowSize();
  m_renderer->setWindowFrameSize(winSize);
  // m_engineSystemManager.init(*m_engine);

  // [ Add initialization of modules independent of 
  //   what modeules they are ]
  
  m_engine->addSystem(m_renderer);

  // m_engine->initSystems();

  // m_engineSystemManager.initModules(initData.initModules);
  


  // [ Maybe shouldn't make it a time module ]
  // [ User might not need some modules, add 
  //   configurbility ]
  m_engine->addModule(TimeModule::createTimeModule());

  // [ ModelManagerModule and RenderModule are linked together and
  //   need eachother to function, should have render module add
  //   a default modelmanager ]
  m_engine->addLayerModule(ModelManagerModule::createModelManagerModule(*m_engine));
  m_engine->addLayerModule(RenderModule::createRenderModule(*m_engine));

  // m_engine->initModules(initData);

  ForwardList<SharedPtr<Layer>> layers = specs.m_userFunc();

  for(auto i = layers.begin(); i != layers.end(); i++)
  {
  pushLayer(*i);
  }

  // [ Initalize layers next ]
  for(auto i = layers.begin(); i != layers.end(); i++)
  {
  (*i)->init();
  }
}

Application::~Application()
{

}

void Application::pushLayer(SharedPtr<Layer> layer)
{
  pushLayerToStack(m_layerStack, layer);
}

void Application::onEvent(Event& e)
{
  EventDispatcher dispatcher(e);
  dispatcher.dispatchEvent<WindowUserQuitEvent>(
  WINDOW_USER_QUIT_EVENT,
  BIND_EVENT_FN(onWindowClose)
                                               );
  dispatcher.dispatchEvent<WindowResizeEvent>(
  WINDOW_RESIZED_EVENT,
  BIND_EVENT_FN(onWindowResize)
                                               );

  updateLayerEvents(m_layerStack, e);
}

void Application::run()
{
  while(m_running)
  {
  // [ Clear buffer in module update  ]
  m_renderer->clearColorBuffer();

  float dt = 0.0f;
  updateLayerStack(m_layerStack, dt);

  m_window->updateWindow();
  }
}

void Application::quitApplication()
{
    m_running = false;
    m_window->disableReportEvents();
}

bool Application::onWindowClose(WindowUserQuitEvent& windowQuit)
{
  m_running = false;

  return true;
}

bool Application::onWindowResize(WindowResizeEvent& resizeEvent)
{

  // [ Add default viewport position values ]
  
  Pair<i32_t, i32_t> windowSize = m_renderer->getWindowFrameSize();

  i32_t newSizeWidth = resizeEvent.width();
  i32_t newSizeHeight = resizeEvent.height();

  i32_t viewspaceDiffernceWidth = newSizeWidth - windowSize.first;
  i32_t viewspaceDiffernceHeight = newSizeHeight - windowSize.second;

  ModelManagerModule& modelManagerModule = static_cast<ModelManagerModule&>(m_engine->getLayerModule("ModelManagerLayerModule"));

  // Updates all viewspaces within all layers
  // of the ModelManagerModule
  // modelManagerModule.setDifferentInViewspace(
  //   static_cast<float>(viewspaceDiffernceWidth),
  //   static_cast<float>(viewspaceDiffernceHeight),
  //   static_cast<float>(windowSize.first),
  //   static_cast<float>(windowSize.second)
  //                                           );

  m_renderer->setViewport(0, 0, resizeEvent.width(), resizeEvent.height());
  m_renderer->setWindowFrameSize(Pair<i32_t, i32_t>{resizeEvent.width(), resizeEvent.height()});

  // std::cout << m_renderer->getWindowFrameSize().first << '\n';

  return true;
}

}    //Ellipse namespace
