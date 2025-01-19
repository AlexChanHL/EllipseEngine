#pragma once

namespace Ellipse
{

namespace EllipseMath
{

class Radian
{
    public:
     Radian(float degrees)
     {
     const float pi = 3.1415f;
     m_radians = degrees * pi / 180.0f;
     }
     ~Radian()
     {

     }

     float radians() const
     {
     return m_radians;
     }
     
    private:
     float m_radians;
};

}     // namespace EllipseMath

}     // namespace Ellipse
