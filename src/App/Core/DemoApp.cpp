
#include "Ellipse.hpp"

class DemoApp : public Ellipse::Application
{
   public:
    DemoApp(const Ellipse::ApplicationSpecifications& specs)
     : Ellipse::Application{specs}
     {

     }

  private:
};

Ellipse::Application* Ellipse::createApplication(Ellipse::ApplicationCMDLineArgs args)
{
  Ellipse::ApplicationSpecifications spec;

   spec.m_name = "Demo App";
   spec.m_workingDir = "$(Dir)";
   spec.m_cmdArgs = args;

  return new DemoApp(spec);
}
