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

class ApplicationConfig
{
    public:
     ApplicationConfig();
     ~ApplicationConfig() = default;

     Vector<Pair<String, bool>> systems() const
     {
     return m_systems;
     }

     WindowSettings windowSettings() const
		 {
     return m_windowSettings;
     }

     GraphicsSpec graphicsSpec() const
     {
     return m_graphicsSpec;
     }

    private:
     Vector<Pair<String, bool>> m_systems;

     WindowSettings m_windowSettings;
     GraphicsSpec m_graphicsSpec;
};

class Application
{
   public:
    Application();
    ~Application();

    void init(const ApplicationConfig& specs);
     
    void onEvent(Event& e);

    void run();

    ForwardList<SharedPtr<Layer>> createUserProcesses();

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
