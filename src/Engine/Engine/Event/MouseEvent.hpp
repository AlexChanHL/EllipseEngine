#pragma once

#include "Event.hpp"
#include "Core/Base.hpp"
#include "Core/Utils.hpp"
#include "Core/MouseCodes.hpp"
#include "Core/Details/MousePosition.hpp"
#include "Debug/Log/Log.hpp"

#include "EllipsePCH.hpp"


namespace Ellipse
{

class MouseEvent : public Event
{
   public:
    virtual EventType getEventType() const override
    {
    return EventType::None;
    }
    virtual const char* getEventName() const override
    {
    return "MouseEvent";
    }

   private:
};

class MouseMotionEvent : public MouseEvent
{
   public:
    virtual EventType getEventType() const override
    {
    return EventType::MouseMotionEvent;
    }

    virtual const char* getEventName() const override
    {
    return "MouseMotionEvent";
    }

    void logMousePosition()
    {
    ELLIPSE_ENGINE_LOG_INFO("{}, {}", m_mousePos.x(), m_mousePos.y());
    }

    Pair<float, float> mousePositions() const
    {
    return createPair<float, float>(mousePosX(), mousePosY());
    }

    void setMousePositionX(float x)
    {
    m_mousePos.setX(x);
    }
    void setMousePositionY(float y)
    {
    m_mousePos.setY(y);
    }

    float mousePosX() const
    {
    return m_mousePos.x();
    }
    float mousePosY() const
    {
    return m_mousePos.y();
    }
   private:
    MousePosition m_mousePos;
};

class MouseWheelEvent : public MouseEvent
{
   public:
    MouseWheelEvent(float offsetX,
                    float offsetY,
                    float posX,
                    float posY
                    )
    : m_mouseOffset_X{offsetX},
      m_mouseOffset_Y{offsetY},
      m_mousePos{posX, posY}
    {

    }
    virtual EventType getEventType() const override
    {
    return EventType::MouseWheelEvent;
    }
    virtual const char* getEventName() const override
    {
    return "MouseWheelEvent";
    }

    String logMousePosition()
    {
    return Utils::toString(m_mousePos.x()) + " , " + Utils::toString(m_mousePos.y());
    }
    String logMouseOffset()
    {
    return "Offset X: " + Utils::toString(m_mouseOffset_X) + " , " + "Offset Y: " + Utils::toString(m_mouseOffset_Y);
    }

    float mouseOffsetX() const
    {
    return m_mouseOffset_X;
    }
    float mouseOffsetY() const
    {
    return m_mouseOffset_Y;
    }

    float mousePosX() const
    {
    return m_mousePos.x();
    }
    float mousePosY() const
    {
    return m_mousePos.y();
    }
   private:
    float m_mouseOffset_X;
    float m_mouseOffset_Y;
    MousePosition m_mousePos;
};

class MousePressedEvent : public MouseEvent
{
   public:
    MousePressedEvent(const MouseIndex& index,
                      const float posX,
                      const float posY
                     )
    : m_mouseIndex{index},
      m_mousePos{posX, posY}
    {

    }
    virtual EventType getEventType() const override
    {
    return EventType::MousePressedEvent;
    }
    virtual const char* getEventName() const override
    {
    return "MousePressedEvent";
    }

    String logMousePositionition()
    {
    return Utils::toString(m_mousePos.x()) + " , " + Utils::toString(m_mousePos.y());
    }

    MouseIndex mouseIndex() const
    {
    return m_mouseIndex;
    }

    Pair<float, float> mousePos()
    {
    return createPair<float, float>(mousePosX(), mousePosY());
    }

    float mousePosX() const
    {
    return m_mousePos.x();
    }
    float mousePosY() const
    {
    return m_mousePos.y();
    }

   private:
    MouseIndex m_mouseIndex;
    MousePosition m_mousePos;
};

class MouseReleasedEvent : public MouseEvent
{
   public:
    virtual EventType getEventType() const override
    {
    return EventType::MouseReleasedEvent;
    }
    virtual const char* getEventName() const override
    {
    return "MouseReleasedEvent";
    }

   private:
};

}    // namespace Ellipse
