
#include "DemoLayer.hpp"

#include "Ellipse.hpp"

ForwardList<SharedPtr<Ellipse::Layer>> pushUserLayers()
{
   ForwardList<SharedPtr<Ellipse::Layer>> layers;

   // SharedPtr<DemoLayer> demoLayer = createShared<DemoLayer>(renderer);
   // SharedPtr<DemoLayer> UILayer = createShared<DemoLayer>(renderer);
   // SharedPtr<DemoLayer> DebugLayer = createShared<DemoLayer>(renderer);

   SharedPtr<DemoLayer> demoLayer = createShared<DemoLayer>(Ellipse::Application::get().getEngine());
   SharedPtr<DemoLayer> UILayer = createShared<DemoLayer>(Ellipse::Application::get().getEngine());
   SharedPtr<DemoLayer> DebugLayer = createShared<DemoLayer>(Ellipse::Application::get().getEngine());

   demoLayer->setName("demoLayer");
   UILayer->setName("UILayer");
   DebugLayer->setName("DebugLayer");

   layers.push_front(std::move(demoLayer));
   layers.push_front(std::move(UILayer));
   layers.push_front(std::move(DebugLayer));

   // [ Use own layer list type ]
   layers.reverse();

  return layers;
}

Ellipse::ApplicationSpecifications Ellipse::createAppSpecs()
{
  Ellipse::ApplicationSpecifications specs;

   specs.m_windowSettings.m_lib = WindowLibrary::SDLWindow;
   specs.m_graphicSpec = GraphicsSpec::OpenGL;
   specs.m_userFunc = pushUserLayers;

   return specs;
}
