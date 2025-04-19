#pragma once

#include "Core/Base.hpp"


namespace Ellipse
{

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
   WindowFocusLostEvent           = 0x000au,
   WindowFullscreenEvent          = 0x000bu,
   WindowLeaveFullscreenEvent     = 0x000cu,
   WindowUserQuitEvent            = 0x000du,
   WindowDestroyedEvent           = 0x000eu,
   KeyboardPressedEvent           = 0x000fu,
   KeyboardReleasedEvent          = 0x0010u,
   TextEditingEvent               = 0x0011u,
   TextInputEvent                 = 0x0012u,
   MouseMotionEvent               = 0x0013u,
   MousePressedEvent              = 0x0014u,
   MouseReleasedEvent             = 0x0015u,
   MouseWheelEvent                = 0x0016u,
   JoyStickAxisMotionEvent        = 0x0017u,
   JoyStickBallMotionEvent        = 0x0018u,
   JoyStickHatMotionEvent         = 0x0019u,
   JoyStickButtonPressedEvent     = 0x001au,
   JoyStickButtonReleasedEvent    = 0x001bu,
   GamepadAxisMotionEvent         = 0x001cu,
   GamepadButtonPressedEvent      = 0x001du,
   GamepadButtonReleasedEvent     = 0x001eu,
   GamepadTouchPadPressedEvent    = 0x001fu,
   GamepadTouchPadReleaseedEvent  = 0x0020u,
   GamepadTouchPadMotionEvent     = 0x0021u
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

}    // namespace Ellipse

#define WINDOW_SHOWN_EVENT               Ellipse::EventType(0x0001u)
#define WINDOW_EXPOSED_EVENT             Ellipse::EventType(0x0002u)
#define WINDOW_MOVED_EVENT               Ellipse::EventType(0x0003u)
#define WINDOW_RESIZED_EVENT             Ellipse::EventType(0x0004u)
#define WINDOW_MINIMIZED_EVENT           Ellipse::EventType(0x0005u)
#define WINDOW_MAXIMIZED_EVENT           Ellipse::EventType(0x0006u)
#define WINDOW_MOUSE_ENTER_EVENT         Ellipse::EventType(0x0007u)
#define WINDOW_MOSUE_LEAVE_EVENT         Ellipse::EventType(0x0008u)
#define WINDOW_FOCUS_GAINED_EVENT        Ellipse::EventType(0x0009u)
#define WINDOW_FOCUS_LOST_EVENT          Ellipse::EventType(0x000au)
#define WINDOW_FULLSCREEN_EVENT          Ellipse::EventType(0x000bu)
#define WINDOW_LEAVE_FULLSCREEN_EVENT    Ellipse::EventType(0x000cu)
#define WINDOW_USER_QUIT_EVENT           Ellipse::EventType(0x000du)
#define WINDOW_DESTROYED_EVENT           Ellipse::EventType(0x000eu)
#define KEYBOARD_PRESSED_EVENT           Ellipse::EventType(0x000fu)
#define KEYBOARD_RELEASED_EVENT          Ellipse::EventType(0x0010u)
#define TEXT_EDITING_EVENT               Ellipse::EventType(0x0011u)
#define TEXT_INPUT_EVENT                 Ellipse::EventType(0x0012u)
#define MOUSE_MOTION_EVENT               Ellipse::EventType(0x0013u)
#define MOUSE_PRESSED_EVENT              Ellipse::EventType(0x0014u)
#define MOUSE_RELEASED_EVENT             Ellipse::EventType(0x0015u)
#define MOUSE_WHEEL_EVENT                Ellipse::EventType(0x0016u)
#define JOYSTICK_AXIS_MOTION_EVENT       Ellipse::EventType(0x0017u)
#define JOYSTICK_BALL_MOTION_EVENT       Ellipse::EventType(0x0018u)
#define JOYSTICK_HAT_MOTION_EVENT        Ellipse::EventType(0x0019u)
#define JOYSTICK_BUTTON_PRESSED_EVENT    Ellipse::EventType(0x001au)
#define JOYSTICK_BUTTON_RELEASED_EVENT   Ellipse::EventType(0x001bu)
#define GAMEPAD_AXIS_MOTION_EVENT        Ellipse::EventType(0x001cu)
#define GAMEPAD_BUTTON_PRESSED_EVENT     Ellipse::EventType(0x001du)
#define GAMEPAD_BUTTON_RELEASED_EVENT    Ellipse::EventType(0x001eu)
#define GAMEPAD_TOCUHPAD_PRESSED_EVENT   Ellipse::EventType(0x001fu)
#define GAMEPAD_TOUCHPAD_RELEASED_EVENT  Ellipse::EventType(0x0020u)
#define GAMEPAD_TOUCHPAD_MOTION_EVENT    Ellipse::EventType(0x0021u)
