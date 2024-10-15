#pragma once

#include "Ellipse.hpp"

class DemoLayer : public Ellipse::Layer
{
   public:
     DemoLayer(Ellipse::Engine& engine);
     virtual ~DemoLayer() = default;

     void initUserLayer() override;
     virtual void onEvent(Event& e) override;

     void onUpdateUserLayer(float dt) override;

     void setName(String name) { m_name = name; }

     bool onKeyPressed(KeyboardPressedEvent& e);
     bool onMousePressed(MousePressedEvent& e);
     bool onMouseWheel(MouseWheelEvent& e);

   private:
     Ellipse::Engine&  m_engine;
     Ellipse::TimeModule& m_timeModule;
     Ellipse::ModelManagerModule& m_modelManagerLayerModule;
     float m_offset;
     Ellipse::Timer m_timer1;
     Vector<Ellipse::ModelID> m_entities;
};
