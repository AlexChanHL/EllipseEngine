#pragma once

#include "EllipsePCH.hpp"

namespace Ellipse
{

class ApplicationCMDLineArgs
{
  public:
   ApplicationCMDLineArgs() {}
   ApplicationCMDLineArgs(int argv, char** argc)
 : m_argv{argv}, m_argc{argc}
    {

    }

  private:
    int m_argv;
    char** m_argc;
};

class ApplicationSpecifications
{
  public:
    std::string m_workingDir;
    std::string m_name;
    ApplicationCMDLineArgs m_cmdArgs;

  private:
};

class Application
{
    public:
     Application(const ApplicationSpecifications& specs);
    ~Application();

     void run();

    private:
      ApplicationSpecifications m_appSpecs;
};

  Application* createApplication(ApplicationCMDLineArgs args);
}    //Ellipse namespace
