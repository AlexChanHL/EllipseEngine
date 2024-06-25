
#include "DemoLayer.hpp"

#include "Ellipse.hpp"

Layer* pushUserLayers()
{
    Layer* demoLayer = new DemoLayer;
   return demoLayer;
}

Ellipse::ApplicationSpecifications Ellipse::createAppSpecs()
{
  Ellipse::ApplicationSpecifications specs;

   specs.m_windowSettings.m_lib = WindowLibrary::SDLWindow;
   specs.m_userFunc = pushUserLayers;

   return specs;
}
