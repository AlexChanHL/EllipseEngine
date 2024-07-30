#pragma once

#include "Ellipse.hpp"

class DemoLayer : public Ellipse::Layer
{
   public:
     DemoLayer(Engine& engine);
     virtual ~DemoLayer() = default;

     void init() override;
     virtual void onEvent(Event& e) override;
     virtual void onUpdate() override;

     void setName(String name) { m_name = name; }

     bool onKeyPressed(KeyboardPressedEvent& e);
     bool onMousePressed(MousePressedEvent& e);
     bool onMouseWheel(MouseWheelEvent& e);

   private:
     UniquePtr<RenderShaderObj> m_shaderObj = nullptr;
     UniquePtr<RenderObj> m_renderObj = nullptr;
     String m_name;

     float m_offset;

     bool m_throughLayer;
};
