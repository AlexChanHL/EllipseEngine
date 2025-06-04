#pragma once

#include "TimeModule.hpp"
#include "Event/Event.hpp"
#include "Renderer/RenderModule.hpp"
#include "Math/Matrix.hpp"
#include "Engine/Engine.hpp"
#include "Debug/Log.hpp"

namespace Ellipse
{

//     SubModelManager m_subModelManger;

class ILayer
{
  public:
    ILayer() = default;
    virtual ~ILayer() = default;

    virtual void init() = 0;
    virtual void onEvent(Event& event) = 0;
    virtual void onUpdate(float dt) = 0;
  
    virtual bool isHidden() = 0;
    virtual void hideLayer() = 0;
    virtual void showLayer() = 0;

  private:

};

class Layer : public ILayer
{
  public:
    Layer(Engine& engine)
    : m_modules{engine.modules()}
    {

    }

    virtual ~Layer() = default;

    virtual void initUserLayer() = 0;
    virtual void init() override
    {    
    for(SharedPtr<IModule> module : m_modules)
    {
    module->init();
    }

    initUserLayer();
    }
    virtual void onEvent(Event& event) override = 0;
    virtual void onUpdateUserLayer(float dt) = 0;
    virtual void onUpdate(float dt) override
    {
    onUpdateUserLayer(dt);

    for(SharedPtr<IModule> module : m_modules)
    {
    module->onUpdate();
    }

    }

    static SharedPtr<ILayer> createDefaultLayer();

  protected:
    virtual bool isHidden() override { return m_hidden; }

    virtual void hideLayer() override { m_hidden = true; }
    virtual void showLayer() override { m_hidden = false; }

  protected:
    // TimeModule& m_timeModule;
    // RenderModule& m_renderModule;
    Vector<SharedPtr<IModule>> m_modules;

    bool m_hidden = false;
    bool m_throughLayer;
    String m_name;

  private:
};

} //Ellipse namespace
