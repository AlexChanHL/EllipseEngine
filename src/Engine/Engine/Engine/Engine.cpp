
#include "Engine.hpp"

class EngineImpl final : public Engine
{
   public:
    virtual void addSystem(SharedPtr<ISystem> system) override;
    virtual ISystem& getSystem(const char* name) override;

    virtual void addModule(SharedPtr<IModule> module) override;
    virtual IModule& getModule(const char* name) override;

   private:
    Vector<SharedPtr<ISystem>> m_systems;
    Vector<SharedPtr<IModule>> m_modules;

    UniquePtr<NoSystem> m_invalidSystem = nullptr;
    UniquePtr<NoModule> m_invalidModule = nullptr;
};

void EngineImpl::addSystem(SharedPtr<ISystem> system)
{
    m_systems.push_back(std::move(system));
}
ISystem& EngineImpl::getSystem(const char* name)
{
    for(const auto& a : m_systems)
    {
     if(strcmp(a->name().c_str(), name) == 0)
      {
    return *a;
      }
    }

    return *m_invalidSystem;
}

void EngineImpl::addModule(SharedPtr<IModule> module)
{
    m_modules.push_back(module);
}
IModule& EngineImpl::getModule(const char* name)
{
    for(const auto& a : m_modules)
    {
    if(strcmp(a->name().c_str(), name) == 0)
      {
    return *a;
      }
    }

   // [ Have moduele manager ]

    return *m_invalidModule;
}

UniquePtr<Engine> Engine::createEngine()
{
    return createUnique<EngineImpl>();
}

