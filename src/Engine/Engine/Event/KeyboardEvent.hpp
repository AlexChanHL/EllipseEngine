#pragma once

#include "Core/ScanCodes.hpp"
#include "Core/KeyCodes.hpp"


namespace Ellipse
{

class KeyboardEvent : public Event
{
    public:
     virtual EventType getEventType() const override
     {
     return EventType::None;
     }
     virtual const char* getEventName() const override
     {
     return "KeyboardEvent";
     }

    private:
};

class KeyboardPressedEvent : public KeyboardEvent
{
    public:
     KeyboardPressedEvent(const KeyCode& key)
      : m_keyCode{key}
     {

     }
     virtual EventType getEventType() const override
     {
     return EventType::KeyboardPressedEvent;
     }
     virtual const char* getEventName() const override
     {
     return "KeyboardPressedEvent";
     }

     KeyCode keyCode() const
     {
     return m_keyCode;
     }
    private:
     KeyCode m_keyCode;
};

}    // namespace Ellipse
