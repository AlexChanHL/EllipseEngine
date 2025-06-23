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
    : m_modules{engine.modules()},
      m_hidden{false},
      m_throughLayer{false}
    {

    }

    virtual ~Layer() = default;

    virtual void init() override = 0;
    virtual void onEvent(Event& event) override = 0;
    virtual void onUpdate(float dt) override = 0;

    static SharedPtr<ILayer> createDefaultLayer();

   protected:
    virtual bool isHidden() override
    {
    return m_hidden;
    }

    virtual void hideLayer() override
    {
    m_hidden = true;
    }
    virtual void showLayer() override 
    {
    m_hidden = false;
    }

  protected:
    Vector<SharedPtr<IModule>> m_modules;

    bool m_hidden;
    bool m_throughLayer;
    String m_name;

  private:
};

}               // Ellipse namespace

