#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;

using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

using Radians = float;

namespace Ellipse
{

namespace EllipseMath
{

inline Mat4 scale(Mat4 model, Vec3 scalerAmount)
{
   return glm::scale(model, scalerAmount);
}

inline Mat4 rotate(Mat4 model, float radians, Vec3 rotationAxis)
{
   return glm::rotate(model, radians, rotationAxis);
}

inline Mat4 translate(Mat4 model, Vec3 translateAmount)
{
   return glm::translate(model, translateAmount);
}

inline Mat3 inverse(Mat3 model)
{
   return glm::inverse(model);
}

inline Mat3 transpose(Mat3 model)
{
   return glm::transpose(model);
}

inline Mat4 lookAt(Vec3 camPos, Vec3 camDir, Vec3 camUp)
{
   return glm::lookAt(camPos, camDir, camUp);
}

inline Mat4 ortho(float aspectRatio1,
                  float aspectRatio2,
                  float top,
                  float bottom,
                  float near,
                  float far
                 )
{
    return glm::ortho(aspectRatio1, aspectRatio2, top, bottom, near, far);
}

inline Mat4 perspective(float fov,
                        float aspectRatio,
                        float near,
                        float far)
{
    return glm::perspective(fov, aspectRatio, near, far);
}

inline float length(Vec3 vec)
{
    return glm::length(vec);
}


inline Vec3 normalize(Vec3 vec)
{
   return glm::normalize(vec);
}

inline Vec3 cross(Vec3 vec1, Vec3 vec2)
{
   return glm::cross(vec1, vec2);
}

}    // namespace ElipseMath


// #endif

}     // namespace Ellipse

