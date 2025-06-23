
#include "Application.hpp"
#include "TimeModule.hpp"
#include "ModelManagerModule.hpp"
#include "Debug/Log.hpp"


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

void Application::init(const ApplicationConfig& config)
{
  m_engine = Engine::createEngine();

  for(Pair<String, bool> pair : config.systems())
  {
  String key = pair.first;
  bool value = pair.second;
  if((key == "Logger") && (value))
  {
  Log::init();
  }
  if((key == "Time") && (value))
  {
  OSTime::init();
  m_engine->addModule(TimeModule::createTimeModule());
  }
  if((key == "Window") && (value))
  {
  m_window = Window::createWindow(config.windowSettings());
  m_window->setEventCallBack(BIND_EVENT_FN(Application::onEvent));
  }
  if((key == "Render") && (value))
  {
  auto renderPlugin = RenderPlugin::createRenderPlugin(config.graphicsSpec());
   
  m_renderer = Renderer::createRenderer(std::move(renderPlugin));
  Pair<int, int> winSize = m_window->getWindowSize();
  m_renderer->setWindowFrameSize(winSize);

  m_engine->addSystem(m_renderer);
  }
  if((key == "Model") && (value))
  {
  m_engine->addModule(ModelManagerModule::createModelManagerModule(*m_engine));
  }
  if((key == "RenderModule") && (value))
  {
  m_engine->addModule(RenderModule::createRenderModule(*m_engine));
  }

  }


  // m_engine->initModules(initData);

  ForwardList<SharedPtr<Layer>> layers = createUserProcesses();

  for(auto i = layers.begin(); i != layers.end(); i++)
  {
  pushLayer(*i);
  }

  for(SharedPtr<IModule> module : m_engine->modules())
  {
  module->init();
  }

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
  m_renderer->clearColorBuffer();
  m_renderer->clearDepthBuffer();

  float dt = 0.0f;
  updateLayerStack(m_layerStack, dt);
  for(SharedPtr<IModule> module : m_engine->modules())
  {
  module->onUpdate();
  }

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

  Pair<i32_t, i32_t> windowSize = m_renderer->getWindowFrameSize();

  i32_t newSizeWidth = resizeEvent.width();
  i32_t newSizeHeight = resizeEvent.height();

  i32_t viewspaceDiffernceWidth = newSizeWidth - windowSize.first;
  i32_t viewspaceDiffernceHeight = newSizeHeight - windowSize.second;

  ModelManagerModule& modelManagerModule = static_cast<ModelManagerModule&>(m_engine->getModule("ModelManagerLayerModule"));

  // modelManagerModule.setDifferentInViewspace(
  //   static_cast<float>(viewspaceDiffernceWidth),
  //   static_cast<float>(viewspaceDiffernceHeight),
  //   static_cast<float>(windowSize.first),
  //   static_cast<float>(windowSize.second)
  //                                           );

  m_renderer->setViewport(0, 0, resizeEvent.width(), resizeEvent.height());
  m_renderer->setWindowFrameSize(Pair<i32_t, i32_t>{resizeEvent.width(), resizeEvent.height()});

  return true;
}

}    // Ellipse namespace

