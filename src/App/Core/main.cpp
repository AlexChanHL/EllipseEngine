#include "Ellipse.hpp"

int main(int argc, char** argv)
{
   Ellipse::Log::init();

  Ellipse::Application* app = Ellipse::createApplication( {argc, argv} );

  app->run();

  delete app;
}
