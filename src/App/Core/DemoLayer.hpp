#pragma once

#include "Ellipse.hpp"

class DemoLayer : public Layer
{
   public:
     virtual void onEvent(Event& e) override;

     void onKeyPressed(KeyboardPressedEvent& e);
     void onMousePressed(MousePressedEvent& e);
     void onMouseWheel(MouseWheelEvent& e);
     virtual ~DemoLayer() = default;
   private:
};
