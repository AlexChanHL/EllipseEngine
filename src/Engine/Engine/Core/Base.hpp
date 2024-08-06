#pragma once

#include "Types.hpp"

#include "EllipsePCH.hpp"

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

template<typename T>
using Vector = std::vector<T>;

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
using UniquePtr = std::unique_ptr<T>;

// [ Temporarily use this ]
using EntityRef = uLong_t;

// #if USE_GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//
using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;

using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

using Radians = float;

namespace EllipseMath
{

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

inline Vec3 normalize(Vec3 vec)
{
   return glm::normalize(vec);
}

inline Vec3 cross(Vec3 vec1, Vec3 vec2)
{
   return glm::cross(vec1, vec2);
}

}    // namespace ElipseMath

//
// #endif

template<typename T>
UniquePtr<T> createUnique(auto&&... args)
{
    return std::make_unique<T>(std::forward<decltype(args)>(args)...);
}

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
SharedPtr<T> createShared(auto&&... args)
{
    return std::make_shared<T>(std::forward<decltype(args)>(args)...);
}

struct MousePos
{
   float x;
   float y;
};

