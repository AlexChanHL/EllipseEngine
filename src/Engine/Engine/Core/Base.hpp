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

using SStream = std::stringstream;
using String = std::string;

using FStreamIn = std::ifstream;

using FStreanOut = std::ofstream;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

// #if USE_GLM
#include <glm/glm.hpp>
//
using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;

using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;
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

