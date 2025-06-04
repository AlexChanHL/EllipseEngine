#pragma once

#include "Types.hpp"

#include "EllipsePCH.hpp"

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define CREATE_FUNC_CALLBACK_INTERFACE(fn, type) virtual function<type> fn ## CallReturn() = 0;

#define CREATE_FUNC_CALLBACK(fn, type) virtual function<type> fn ## CallReturn() override\
                                       {\
                                       return [this](auto&&... args) -> decltype(auto)  { return this->fn(std::forward<decltype(args)>(args)...); };\
                                       }


// [ Define Ellipse::String used by engine, and for app string ]

template<typename T>
using Vector = std::vector<T>;

template<typename T, u64_t N>
using Array = std::array<T, N>;

template<typename T>
using ForwardList = std::forward_list<T>;

template<typename T, typename D>
using Map = std::map<T, D>;

template<typename T, typename D>
using Pair = std::pair<T, D>;

using SStream = std::stringstream;
using String = std::string;

using FStreamIn = std::ifstream;

using FStreanOut = std::ofstream;

template<typename T>
using function = std::function<T>;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

// [ Temporarily use this ]
using EntityRef = uLong_t;

// template<typename T>
// std::function<T> std::function<

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

inline Mat4 ortho(float left,
                  float right,
                  float top,
                  float bottom,
                  float near,
                  float far
                 )
{
    return glm::ortho(left, right, top, bottom, near, far);
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

template<typename T, typename D, typename Func>
void erase_if(Map<T, D>& map, Func func)
{
    std::erase_if(map, func);
}

template<typename T, typename D>
Pair<T, D> createPair(T t, D d)
{
    return std::make_pair<T, D>(std::forward<T>(t), std::forward<D>(d));
}

template<typename T>
UniquePtr<T> createUnique(auto&&... args)
{
    return std::make_unique<T>(std::forward<decltype(args)>(args)...);
}

template<typename T>
SharedPtr<T> createShared(auto&&... args)
{
    return std::make_shared<T>(std::forward<decltype(args)>(args)...);
}

