#pragma once

#include "Core/Base.hpp"

// [ Make own random library ]


// [ Maybe should have seperate random library ]

namespace EllipseMath
{

class Random
{
    public:
     static std::mt19937& randomEngine()
     {
     return m_randomEngine;
     }

    private:
     static std::mt19937 m_randomEngine;
};

std::uniform_int_distribution<> createIntDist(int32_t min, int32_t max);

int32_t randIntDist(int32_t min, int32_t max);

int32_t randIntDist(std::uniform_int_distribution<>& intDist);

template<typename T = double>
T randRealDist(T min, T max)
{
    std::uniform_real_distribution<T> dist{min, max};

    return dist(Random::randomEngine());
}

template<typename T = double>
T randRealDist(std::uniform_real_distribution<T>& dist)
{
    return dist(Random::randomEngine());
}

}    // namespace EllipseMath
