
#include "Engine.hpp"

namespace Ellipse
{

class EngineImpl final : public Engine
{
   public:
    virtual void addSystem(SharedPtr<ISystem> system) override;
    virtual ISystem& getSystem(const char* name) override;

    virtual void addModule(SharedPtr<IModule> module) override;
    virtual IModule& getModule(const char* name) override;

    virtual void addLayerModule(SharedPtr<ILayerModule> layerModule) override;
    virtual ILayerModule& getLayerModule(const char* name) override;

    virtual Vector<SharedPtr<ILayerModule>>& layerModules() override
    {
    return m_layerModules;
    }

   private:
    Vector<SharedPtr<ISystem>> m_systems;
    Vector<SharedPtr<IModule>> m_modules;
    Vector<SharedPtr<ILayerModule>> m_layerModules;

    UniquePtr<NoSystem> m_invalidSystem = nullptr;
    UniquePtr<NoModule> m_invalidModule = nullptr;
    UniquePtr<NoLayerModule> m_invalidLayerModule = nullptr;
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

    std::cout << "Return invalid system\n";

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

    // [ Have module manager ]
    std::cout << "Return invalid module\n";

    return *m_invalidModule;
}

void EngineImpl::addLayerModule(SharedPtr<ILayerModule> layerModule)
{
    m_layerModules.push_back(layerModule);
}

ILayerModule& EngineImpl::getLayerModule(const char* name)
{
    for(auto& m : m_layerModules)
    {
    if(strcmp(m->name().c_str(), name) == 0)
    {
    return *m;
    }
    }

    // [ Add logging to notify returning of invalid layer module ]
    std::cout << "Returning invalid\n"; 

    return *m_invalidLayerModule;
}

UniquePtr<Engine> Engine::createEngine()
{
    return createUnique<EngineImpl>();
}

}   // namespace Ellipse
