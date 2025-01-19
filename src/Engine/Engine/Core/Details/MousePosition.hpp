#pragma once


namespace Ellipse
{

struct MousePosition
{
   public:
    MousePosition()
    : m_x{0},
      m_y{0}
    {

    }
    MousePosition(float x, float y)
    : m_x{x},
      m_y{y}
    {

    }
    ~MousePosition()
    {
    
    }

   
    void setX(float x)
    {
    m_x = x;
    }

    void setY(float y)
    {
    m_y = y;
    }

    float x() const
    {
    return m_x; 
    }
    
    float y() const
    {
    return m_y;
    }

   private:
    float m_x;
    float m_y;
};

}     // namespace Ellipse
