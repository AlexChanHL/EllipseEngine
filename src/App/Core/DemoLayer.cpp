
#include "Ellipse.hpp"

#include "DemoLayer.hpp"

void DemoLayer::onEvent(Event& e)
{

       EventDispatcher dispatcher(e);
      dispatcher.dispatchEvent<KeyboardPressedEvent>(
        EventType::KeyboardPressedEvent,
        BIND_EVENT_FN(onKeyPressed)
      );
      dispatcher.dispatchEvent<MousePressedEvent>(
        EventType::MousePressedEvent,
        BIND_EVENT_FN(onMousePressed)
      );
      dispatcher.dispatchEvent<MouseWheelEvent>(
        EventType::MouseWheelEvent,
        BIND_EVENT_FN(onMouseWheel)
      );
}

void DemoLayer::onKeyPressed(KeyboardPressedEvent& e)
{
     bool aPressed = Input::isKeyPressed(ELLIPSE_KEY_a);
      if(aPressed)
       {
   std::cout << "'a' key is pressed" << "\n";
       }

    switch(e.keyCode())
     {
        case ELLIPSE_KEY_a:
         break;
        case ELLIPSE_KEY_b:
         break;
       default:
        break;
     }
}

void DemoLayer::onMousePressed(MousePressedEvent& e)
{
  std::cout << e.logMousePosition() << "\n";
}

void DemoLayer::onMouseWheel(MouseWheelEvent& e)
{
  std::cout << e.logMouseOffset() << "\n";
}
