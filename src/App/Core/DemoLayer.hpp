#pragma once

#include "Ellipse.hpp"

class DemoLayer : public Ellipse::Layer
{
   public:
     DemoLayer();
     virtual ~DemoLayer() = default;

     void init() override;
     virtual void onEvent(Event& e) override;
     virtual void onUpdate() override;

     void setName(String name) { m_name = name; }

     bool onKeyPressed(KeyboardPressedEvent& e);
     bool onMousePressed(MousePressedEvent& e);
     bool onMouseWheel(MouseWheelEvent& e);

   private:
     Renderer& m_renderer;
     std::unique_ptr<RenderShaderObj> m_shaderObj = nullptr;
     std::unique_ptr<RenderObj> m_renderObj = nullptr;
     std::string m_name;

     float m_offset;

     bool m_throughLayer;
};
