#pragma once

#include "Core/Base.hpp"

class IModule
{
   public:
    IModule() = default;
    virtual ~IModule() = default;

    virtual String name() = 0;
    virtual void setName(const char* name) = 0;

   protected:
    String m_name;
  
   private:
};
