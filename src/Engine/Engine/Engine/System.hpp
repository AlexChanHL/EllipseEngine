#pragma once

#include "Core/Base.hpp"
#include "Module.hpp"

class ISystem
{
  public:
   ISystem() = default;
   virtual ~ISystem() = default;

   virtual String name() = 0;
   virtual void setName(const char* name) = 0;

  protected:
   String m_name;

   private:
};

class NoSystem : public ISystem
{
   public:
    NoSystem()
    {
    m_name = "No system";
    }

    virtual String name() override;
    virtual void setName(const char* name) override;

   private:
};
