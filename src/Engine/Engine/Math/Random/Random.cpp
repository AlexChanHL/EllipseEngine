
#include "Random.hpp"


namespace Ellipse
{

namespace EllipseMath
{

std::mt19937 Random::m_randomEngine{std::random_device{}()};

std::uniform_int_distribution<> createIntDist(int32_t min, int32_t max)
{
    return std::uniform_int_distribution{min, max};
}

int32_t randIntDist(int32_t min, int32_t max)
{
    std::uniform_int_distribution dist{min, max};

    return dist(Random::randomEngine());
}

int32_t randIntDist(std::uniform_int_distribution<>& intDist)
{
    return intDist(Random::randomEngine());
}

}    // namespace EllipseMath

}    // namespace Ellipse
