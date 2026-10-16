#pragma once

#include "Core/Details/MousePosition.hpp"


namespace Ellipse
{

class MouseInformation
{
   public:
    MouseInformation()
    {

    }
    ~MouseInformation()
    {

    }


    void update(MousePosition mousePosition,
                float offsetX,
                float offsetY)
    {
    setMousePosition(mousePosition);

    setOffsetX(offsetX);
    setOffsetY(offsetY);
    }

    void setMousePosition(MousePosition mousePosition)
    {
    m_mousePosition = mousePosition;
    }

    Pair<float, float> mouseOffsetsLast(MousePosition position)
    {
    return m_mouseOffsetToLast;
    }

    void findOffsets(MousePosition mousePosition)
    {
    m_mouseOffsetToLast.first = (mousePosition.x() - m_mousePosition.x());
    m_mouseOffsetToLast.second = (mousePosition.y() - m_mousePosition.y());

    m_mousePosition.setX(0);
    m_mousePosition.setY(0);
    }

    void setOffsetX(float offsetX)
    {
    m_mouseOffsetToLast.first = offsetX;
    }

    void setOffsetY(float offsetY)
    {
    m_mouseOffsetToLast.second = offsetY;
    }

    void setOffsets(float offsetX, float offsetY)
    {
    m_mouseOffsetToLast.first = offsetX;
    m_mouseOffsetToLast.second = offsetY;
    }

    Pair<float, float> mouseOffsets() const
    {
    return m_mouseOffsetToLast;
    }

   private:
    MousePosition m_mousePosition;
    Pair<float, float> m_mouseOffsetToLast;
};

}     // namespace Ellipse
