
#include "Engine.hpp"
#include "Debug/Log.hpp"

namespace Ellipse
{

class EngineImpl final : public Engine
{
   public:
    virtual void addSystem(SharedPtr<ISystem> system) override;
    virtual ISystem& getSystem(const char* name) override;

    virtual void addModule(SharedPtr<IModule> module) override;
    virtual IModule& getModule(const char* name) override;

    virtual Vector<SharedPtr<IModule>>& modules() override
    {
    return m_modules;
    }

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

    ELLIPSE_ENGINE_LOG_WARN("Return invalid system, search name: {}");

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
    ELLIPSE_ENGINE_LOG_WARN("Return invalid module, search name: {}", name);

    return *m_invalidModule;
}

UniquePtr<Engine> Engine::createEngine()
{
    return createUnique<EngineImpl>();
}

}   // namespace Ellipse
