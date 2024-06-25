#pragma once

#include "Event.hpp"

class WindowEvent : public Event
{
   public:
     virtual EventType getEventType() const override
      { 
       return EventType::None;
      }
      virtual const char* getEventName() const  override
     {
       return "WindowEvent";
     }

   private:
};

class WindowUserQuitEvent : public WindowEvent
{
   public:
    WindowUserQuitEvent() = default;
     virtual EventType getEventType() const override
      {
        return EventType::WindowUserQuitEvent;
      }
     virtual const char* getEventName() const override
     {
        return "WindowUserQuitEvent";
     }
   private:
};

class WindowResizeEvent : public WindowEvent
{
    public:
      WindowResizeEvent(int width, int height)
       : m_width{width}, m_height{height}
      {
         
      }
     virtual EventType getEventType() const override
      {
        return EventType::WindowResizeEvent;
      }
     virtual const char* getEventName() const override
     {
        return "WindowResizeEvent";
     }

     int width() const { return m_width; }
     int height() const { return m_height; }
   private:
     int m_width;
     int m_height;
};
