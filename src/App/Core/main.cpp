#include "Ellipse.hpp"

int main()
{
    Ellipse::Log::init();

    auto specs = Ellipse::createAppSpecs();
  
    Ellipse::Application* app = new Ellipse::Application;

    app->init(specs);

    app->run();
  
    // app->shutDown();

    delete app;
}
