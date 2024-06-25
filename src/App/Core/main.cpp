#include "Ellipse.hpp"

int main()
{
  auto specs = Ellipse::createAppSpecs();
  
  Ellipse::Application* app = new Ellipse::Application;

    app->init(specs);

    app->run();
  
    // app->shutDown();

    delete app;
}
