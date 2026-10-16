#pragma once

#include "Core/Base.hpp"


namespace Ellipse
{

class IModule
{
   public:
    IModule()
    {
    m_name = "No module";
    }
    virtual ~IModule()
    {

    }

    virtual void init() = 0;
    virtual void onUpdate() = 0;

    // [ Set name: use a name that engine can identify ]
    virtual String name() 
    {
    return m_name;
    }
    virtual void setName(const char* name)
    {
    m_name = name;
    }

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
    ~NoModule()
    {

    }

    virtual void init() override
		{

    }
    virtual void onUpdate() override
		{

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

}     // namespace Ellipse
