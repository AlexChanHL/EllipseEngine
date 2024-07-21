#pragma once

enum class EventType
{
   None, 
   WindowShownEvent,
   WindowExposedEvent,
   WindowMovedEvent,
   WindowResizeEvent,
   WindowMinimizedEvent,
   WindowMaximizedEvent,
   WindowMouseEnterEvent,
   WindowMouseLeaveEvent,
   WindowFocusGainedEvent,
   WindowFocusLostEvent,
   WindowFullscreenEvent,
   WindowLeaveFullscreenEvent,
   WindowUserQuitEvent,
   WindowDestroyedEvent,
   KeyboardPressedEvent,
   KeyboardReleasedEvent,
   TextEditingEvent,
   TextInputEvent,
   MouseMotionEvent,
   MousePressedEvent,
   MouseReleasedEvent,
   MouseWheelEvent,
   JoyStickAxisMotionEvent,
   JoyStickBallMotionEvent,
   JoyStickHatMotionEvent,
   JoyStickButtonPressedEvent,
   JoyStickButtonReleasedEvent,
   GamepadAxisMotionEvent,
   GamepadButtonPressedEvent,
   GamepadButtonReleasedEvent,
   GamepadTouchPadPressedEvent,
   GamepadTouchPadReleaseedEvent,
   GamepadTouchPadMotionEvent
};

class Event
{
   public:
     Event() = default;

     virtual EventType getEventType() const = 0;
   
     virtual const char* getEventName() const = 0;

     virtual std::string toString() const { return getEventName(); }

     virtual ~Event() = default;

     bool m_handled = false;
};

struct EventDispatcher
{
   public:
    EventDispatcher(Event& event)
     : m_event{event}
    {

    }

     template<typename T, typename F>
void dispatchEvent(EventType type,
                   F func)
{
   if(m_event.getEventType() == type)
     {
  m_event.m_handled = func(static_cast<T&>(m_event));
     }

      return;
}

   private:
    Event& m_event;
};
