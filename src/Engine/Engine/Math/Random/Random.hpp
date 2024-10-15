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

class RandomRemoveLast
{
   public:
    RandomRemoveLast(int32_t stepIteration)
    : m_lastVal{0},
      m_maxiumRandomVal{0},
      m_stepIteration{stepIteration},
      m_iterationAmount{0}
    {
    addNums();
    }

    ~RandomRemoveLast()
    {

    }

    void addNums()
    {
    m_iterationAmount += m_stepIteration;
    for(int32_t i=m_lastVal;i<m_iterationAmount;i++)
    {
    m_randomUniqueNums.push_back(i);
    }

    m_lastVal = m_iterationAmount;
    m_maxiumRandomVal += m_stepIteration;
    }

    int32_t chooseRandomVal()
    {
    if(m_randomUniqueNums.empty())
    {
    addNums();
    }
    auto chosenRandomValIterator = m_randomUniqueNums.begin() + randIntDist(0, m_maxiumRandomVal - 1);

    int32_t chosenRandomVal = *chosenRandomValIterator;
    m_randomUniqueNums.erase(chosenRandomValIterator);
    m_maxiumRandomVal--;
    return chosenRandomVal;
    }

    std::vector<int> randomUniqueNums()
    {
    return m_randomUniqueNums;
    }

   private:
    std::vector<int> m_randomUniqueNums;
    int32_t m_lastVal;
    int32_t m_maxiumRandomVal;
    int32_t m_stepIteration;
    int32_t m_iterationAmount;
};

}      // namespace EllipseMath
