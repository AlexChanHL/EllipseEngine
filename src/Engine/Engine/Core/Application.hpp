#pragma once

#include "Window.hpp"
#include "OSTime.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderModule.hpp"
#include "Engine/Engine.hpp"
#include "Event/Event.hpp"
#include "Event/WindowEvent.hpp"
#include "LayerStack.hpp"
#include "Base.hpp"
#include "EllipsePCH.hpp"

namespace Ellipse
{

class ApplicationStackValue
{
   public:
    static void createStackValues()
    {
    Ellipse::Log::init();
    Ellipse::OSTime::init();
    }
   private:
};

class ApplicationCMDLineArgs
{
   public:
    ApplicationCMDLineArgs()
    {

    }
    ApplicationCMDLineArgs(int argv, char** argc)
    : m_argv{argv},
      m_argc{argc}
    {

    }
    ~ApplicationCMDLineArgs()
    {

    }
    
    i32_t argv()
    {
    return m_argv;
    }
    char** argc()
    {
    return m_argc;
    }

   private:
    i32_t m_argv;
    char** m_argc;
};

class ApplicationSpecifications
{
   public:
    using userFn = std::function<ForwardList<SharedPtr<Layer>>()>;
   
    ApplicationSpecifications()
    {
    setDefaultWindowValues();
    }
    ~ApplicationSpecifications()
    {

    }

    void setValues()
    {

    }

    void setWindowValues(i32_t width,
                         i32_t height,
                         String title)
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

    void quitApplication();

    void pushLayer(SharedPtr<Layer> layer);

    bool onWindowClose(WindowUserQuitEvent& windowQuit);
    bool onWindowResize(WindowResizeEvent& resizeEvent);

    static Application& get()
    {
    return *sInStance;
    }

    Engine& getEngine() const
    {
    return *m_engine;
    }
    Window& getWindow() const 
    {
    return *m_window;
    }
    Renderer& getRenderer() const 
    {
    return *m_renderer;
    }

   private:
    bool m_running;

    UniquePtr<Window> m_window = nullptr;
    // [ Engine should have control of renderer ]
    SharedPtr<Renderer> m_renderer = nullptr;
    LayerStack m_layerStack;
    UniquePtr<Engine> m_engine = nullptr;
      
    static Application* sInStance;
};

std::function<void()> setUserFunc();
}    //Ellipse namespace
