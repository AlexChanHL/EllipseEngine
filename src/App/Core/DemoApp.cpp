
#include "DemoLayer.hpp"

#include "Ellipse.hpp"

std::vector<std::shared_ptr<Ellipse::Layer>> pushUserLayers()
{
   // use shared pointer
    // Layer* demoLayer = new DemoLayer;

  std::vector<std::shared_ptr<Ellipse::Layer>> layers;

  std::shared_ptr<Ellipse::Layer> demoLayer = std::make_shared<DemoLayer>();
  std::shared_ptr<Ellipse::Layer> UILayer = std::make_shared<DemoLayer>();
  std::shared_ptr<Ellipse::Layer> Debuglayer = std::make_shared<DemoLayer>();


   layers.push_back(std::move(demoLayer));
   layers.push_back(std::move(UILayer));
   layers.push_back(std::move(Debuglayer));

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
