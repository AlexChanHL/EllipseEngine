#pragma once

#include "Core/Base.hpp"


namespace Ellipse
{

class IModule
{
   public:
    IModule() = default;
    virtual ~IModule() = default;

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

// [ Maybe doesn't need to inherit from IModule ]
class ILayerModule : public IModule
{
   public:
    virtual void initLayerModule() = 0;
    virtual void onUpdateLayer() = 0;
   private:

};

class NoLayerModule : public ILayerModule
{
   public:
    NoLayerModule() = default;
    virtual ~NoLayerModule() = default;

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
