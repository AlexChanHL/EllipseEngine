#pragma once

#include "Ellipse.hpp"

class DemoLayer : public Ellipse::Layer
{
   public:
     DemoLayer(Engine& engine);
     virtual ~DemoLayer() = default;

     void init() override;
     virtual void onEvent(Event& e) override;

     void onUpdateUserLayer(float dt) override;

     void setName(String name) { m_name = name; }

     bool onKeyPressed(KeyboardPressedEvent& e);
     bool onMousePressed(MousePressedEvent& e);
     bool onMouseWheel(MouseWheelEvent& e);

   private:
     float m_offset;
     EntityRef m_entity3;
     EntityRef m_entity4;
};
