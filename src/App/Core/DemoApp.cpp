
#include "DemoLayer.hpp"

#include "Ellipse.hpp"

ForwardList<SharedPtr<Ellipse::Layer>> pushUserLayers()
{
   ForwardList<SharedPtr<Ellipse::Layer>> layers;

   SharedPtr<DemoLayer> demoLayer = createShared<DemoLayer>();
   SharedPtr<DemoLayer> UILayer = createShared<DemoLayer>();
   SharedPtr<DemoLayer> DebugLayer = createShared<DemoLayer>();

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
