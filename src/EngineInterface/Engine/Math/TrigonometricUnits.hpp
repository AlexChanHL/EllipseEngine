#pragma once


namespace Ellipse
{

namespace EllipseMath
{

// class Radian
// {
//     public:
//      Radian(float degrees)
//      {
//      const float pi = 3.1415f;
//      m_radians = degrees * pi / 180.0f;
//      }
//      ~Radian()
//      {
//
//      }
//
//      float radians() const
//      {
//      return m_radians;
//      }
//      
//     private:
//      float m_radians;
// };

inline float radians(float degrees)
{
     const float pi = 3.1415f;
     return degrees * pi / 180.0f;
}

inline float degrees(float radians)
{
     const float pi = 3.1415f;
     return radians * 180.0f / pi;
}

}     // namespace EllipseMath

}     // namespace Ellipse

