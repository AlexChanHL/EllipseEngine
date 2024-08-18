#include "Ellipse.hpp"

int main()
{
    // [ Maybe a better way of initalizing values ]
    Ellipse::ApplicationStackValue::createStackValues();

    auto specs = Ellipse::createAppSpecs();
  
    Ellipse::Application* app = new Ellipse::Application;

    app->init(specs);

    app->run();
  
    // app->shutDown();

    delete app;
}
