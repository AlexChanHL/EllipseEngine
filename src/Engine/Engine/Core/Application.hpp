#pragma once

#include "Window.hpp"
#include "Renderer/Renderer.hpp"
#include "Event/Event.hpp"
#include "Event/WindowEvent.hpp"
#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Base.hpp"
#include "EllipsePCH.hpp"

namespace Ellipse
{

class ApplicationCMDLineArgs
{
  public:
   ApplicationCMDLineArgs() {}
   ApplicationCMDLineArgs(int argv, char** argc)
 : m_argv{argv}, m_argc{argc}
    {

    }

  private:
    int m_argv;
    char** m_argc;
};

class ApplicationSpecifications
{
   public:
    // using userFn = std::function<std::vector<std::shared_ptr<Layer>()>>;
    using userFn = std::function<std::vector<std::shared_ptr<Layer>>()>;
   
    ApplicationSpecifications()
    {
      setDefaultWindowValues();
    }

    void setValues() { }

    void setWindowValues(int width,
                         int height,
                         std::string title)
    {
      m_windowSettings.m_width = width;
      m_windowSettings.m_height = height;
      m_windowSettings.m_title = title;
    }

    void setDefaultValues()
    {

    }
    void setDefaultWindowValues() 
    {
         setWindowValues(1280, 640, "Title");
    }


    ~ApplicationSpecifications() {

    }
     
   public:
      WindowSettings m_windowSettings;
      GraphicsSpec m_graphicSpec;
      userFn m_userFunc;

   private:
};

ApplicationSpecifications createAppSpecs();

class Application
{
   public:
   Application();
  ~Application();

   void init(const ApplicationSpecifications& specs);
    
   void onEvent(Event& e);

   void run();

   void pushLayer(std::shared_ptr<Layer> layer);

   bool onWindowClose(WindowUserQuitEvent& windowQuit);
   bool onWindowResize(WindowResizeEvent& resizeEvent);

   static Application& get() { return *sInStance; }

   Renderer& getRenderer() const { return *m_renderer; }

   private:
  bool m_running{true};

  Window* m_window;
  std::unique_ptr<Renderer> m_renderer = nullptr;
  LayerStack m_layerStack;
  // Engine* m_engine;
    
  static Application* sInStance;
};

std::function<void()> setUserFunc();
}    //Ellipse namespace
