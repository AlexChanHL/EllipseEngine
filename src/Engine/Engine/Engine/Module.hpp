#pragma once

#include "Core/Base.hpp"

class IModule
{
   public:
    IModule() = default;
    virtual ~IModule() = default;

    // [ Set name: use a name that engine can identify ]
    virtual String name() = 0;
    virtual void setName(const char* name) = 0;

   protected:
    String m_name;
  
   private:
};

class NoModule : public IModule
{
   public:
    NoModule()
    {
    m_name = "No Module";
    }
    virtual String name() override
    {
    return m_name;
    }
    virtual void setName(const char* name) override
    {
    m_name = name;
    }

   private:
};
