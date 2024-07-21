#pragma once

#include "Event/Event.hpp"
#include "Renderer/Renderer.hpp"

namespace Ellipse
{

class Layer
{
  public:
    Layer() = default;
    virtual ~Layer() = default;

    virtual void init() = 0;
    virtual void onEvent(Event& event) = 0;
    virtual void onUpdate() = 0;

    bool isHidden() { return m_hidden; }

    void hideLayer() { m_hidden = true; }
    void showLayer() { m_hidden = false; }

  protected:
    bool m_hidden = false;

  private:
};

class PlaceHolderLayer : public Layer
{
  public:
    PlaceHolderLayer() = default;
    virtual ~PlaceHolderLayer() = default;
    virtual void init() override
     {
     
     }
    virtual void onEvent(Event& event) override
     {

     }
    virtual void onUpdate() override
     {

     }
  private:
};

} //Ellipse namespace
