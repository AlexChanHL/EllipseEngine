#pragma once

#include "Core/Base.hpp"

namespace Ellipse
{

class VerticiesData
{
   public:
    VerticiesData() = default;
    VerticiesData(u32_t offsetToNextVal,
                  uLong_t verticiesAmount,
                  Vector<float> verticies)
    : m_offsetToNextVal{offsetToNextVal},
      m_verticiesAmount{verticiesAmount},
      m_verticies{verticies}
    {
    m_numVerts = static_cast<u32_t>(m_verticiesAmount) / m_offsetToNextVal;
    }

    u32_t numVerts()
    {
    return m_numVerts;
    }

    u32_t offsetToNextVal()
    {
    return m_offsetToNextVal;
    }
    uLong_t verticiesAmount()
    {
    return m_verticiesAmount;
    }
    Vector<float> verticies()
    {
    return m_verticies;
    }

   private:
    u32_t m_offsetToNextVal;
    uLong_t m_verticiesAmount;
    Vector<float> m_verticies;
    u32_t m_numVerts;
};

}      // namespace Ellipse
