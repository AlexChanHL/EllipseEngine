#pragma once

#include "Event/Event.hpp"
#include "Renderer/Renderer.hpp"
#include "Engine/Engine.hpp"

namespace Ellipse
{

class ILayer
{
  public:
    ILayer() = default;
    virtual ~ILayer() = default;

    virtual void init() = 0;
    virtual void onEvent(Event& event) = 0;
    virtual void onUpdate() = 0;

    virtual bool isHidden() = 0;
    virtual void hideLayer() = 0;
    virtual void showLayer() = 0;

  private:

};

class Layer : public ILayer
{
  public:
    Layer(Engine& engine)
    : m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))}
    //  : m_renderModule{engine.getModule("Renderer")}
    {

    }

    virtual ~Layer() = default;

    virtual void init() override {}
    virtual void onEvent(Event& event) override {}
    virtual void onUpdate() override {}

    virtual bool isHidden() override { return m_hidden; }

    virtual void hideLayer() override { m_hidden = true; }
    virtual void showLayer() override { m_hidden = false; }

    static SharedPtr<ILayer> createDefaultLayer();

  protected:
    Renderer& m_renderer;
    // RenderModule& m_renderModule;
    bool m_hidden = false;

  private:
};

} //Ellipse namespace
