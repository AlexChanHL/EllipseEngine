#pragma once

#include "Core/Base.hpp"


// [ This is wrong, using hexadecimal digits ]
enum class EventType : u8_t
{
   None                           = 0x0000u,
   WindowShownEvent               = 0x0001u,
   WindowExposedEvent             = 0x0002u,
   WindowMovedEvent               = 0x0003u,
   WindowResizeEvent              = 0x0004u,
   WindowMinimizedEvent           = 0x0005u,
   WindowMaximizedEvent           = 0x0006u,
   WindowMouseEnterEvent          = 0x0007u,
   WindowMouseLeaveEvent          = 0x0008u,
   WindowFocusGainedEvent         = 0x0009u,
   WindowFocusLostEvent           = 0x0010u,
   WindowFullscreenEvent          = 0x0011u,
   WindowLeaveFullscreenEvent     = 0x0012u,
   WindowUserQuitEvent            = 0x0013u,
   WindowDestroyedEvent           = 0x0014u,
   KeyboardPressedEvent           = 0x0015u,
   KeyboardReleasedEvent          = 0x0016u,
   TextEditingEvent               = 0x0017u,
   TextInputEvent                 = 0x0018u,
   MouseMotionEvent               = 0x0019u,
   MousePressedEvent              = 0x0020u,
   MouseReleasedEvent             = 0x0021u,
   MouseWheelEvent                = 0x0022u,
   JoyStickAxisMotionEvent        = 0x0023u,
   JoyStickBallMotionEvent        = 0x0024u,
   JoyStickHatMotionEvent         = 0x0025u,
   JoyStickButtonPressedEvent     = 0x0026u,
   JoyStickButtonReleasedEvent    = 0x0027u,
   GamepadAxisMotionEvent         = 0x0028u,
   GamepadButtonPressedEvent      = 0x0029u,
   GamepadButtonReleasedEvent     = 0x0030u,
   GamepadTouchPadPressedEvent    = 0x0031u,
   GamepadTouchPadReleaseedEvent  = 0x0032u,
   GamepadTouchPadMotionEvent     = 0x0033u
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

#define WINDOW_SHOWN_EVENT               EventType(0x0001u)
#define WINDOW_EXPOSED_EVENT             EventType(0x0002u)
#define WINDOW_MOVED_EVENT               EventType(0x0003u)
#define WINDOW_RESIZED_EVENT             EventType(0x0004u)
#define WINDOW_MINIMIZED_EVENT           EventType(0x0005u)
#define WINDOW_MAXIMIZED_EVENT           EventType(0x0006u)
#define WINDOW_MOUSE_ENTER_EVENT         EventType(0x0007u)
#define WINDOW_MOSUE_LEAVE_EVENT         EventType(0x0008u)
#define WINDOW_FOCUS_GAINED_EVENT        EventType(0x0009u)
#define WINDOW_FOCUS_LOST_EVENT          EventType(0x0010u)
#define WINDOW_FULLSCREEN_EVENT          EventType(0x0011u)
#define WINDOW_LEAVE_FULLSCREEN_EVENT    EventType(0x0012u)
#define WINDOW_USER_QUIT_EVENT           EventType(0x0013u)
#define WINDOW_DESTROYED_EVENT           EventType(0x0014u)
#define KEYBOARD_PRESSED_EVENT           EventType(0x0015u)
#define KEYBOARD_RELEASED_EVENT          EventType(0x0016u)
#define TEXT_EDITING_EVENT               EventType(0x0017u)
#define TEXT_INPUT_EVENT                 EventType(0x0018u)
#define MOUSE_MOTION_EVENT               EventType(0x0019u)
#define MOUSE_PRESSED_EVENT              EventType(0x0020u)
#define MOUSE_RELEASED_EVENT             EventType(0x0021u)
#define MOUSE_WHEEL_EVENT                EventType(0x0022u)
#define JOYSTICK_AXIS_MOTION_EVENT       EventType(0x0023u)
#define JOYSTICK_BALL_MOTION_EVENT       EventType(0x0024u)
#define JOYSTICK_HAT_MOTION_EVENT        EventType(0x0025u)
#define JOYSTICK_BUTTON_PRESSED_EVENT    EventType(0x0026u)
#define JOYSTICK_BUTTON_RELEASED_EVENT   EventType(0x0027u)
#define GAMEPAD_AXIS_MOTION_EVENT        EventType(0x0028u)
#define GAMEPAD_BUTTON_PRESSED_EVENT     EventType(0x0029u)
#define GAMEPAD_BUTTON_RELEASED_EVENT    EventType(0x0030u)
#define GAMEPAD_TOCUHPAD_PRESSED_EVENT   EventType(0x0031u)
#define GAMEPAD_TOUCHPAD_RELEASED_EVENT  EventType(0x0032u)
#define GAMEPAD_TOUCHPAD_MOTION_EVENT    EventType(0x0033u)
