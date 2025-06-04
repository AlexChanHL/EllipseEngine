#pragma once

#include "Core/Base.hpp"
#include "System.hpp"
#include "Module.hpp"

namespace Ellipse
{

class Engine
{
   public:
    Engine() = default;
    virtual ~Engine() = default;

    virtual void addSystem(SharedPtr<ISystem> system) = 0;
    virtual ISystem& getSystem(const char* name) = 0;

    virtual void addModule(SharedPtr<IModule> module) = 0;
    virtual IModule& getModule(const char* name) = 0;

    virtual Vector<SharedPtr<IModule>>& modules() = 0;

    static UniquePtr<Engine> createEngine();

   private:
};

};   // namespace Ellipse
