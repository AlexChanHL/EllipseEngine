#pragma once

#include "Core/Base.hpp"
#include "VerticiesData.hpp"

namespace Ellipse
{

struct Shape
{
    public:
     String m_name;
     VerticiesData m_verticies;
     const char* m_vShader;
     const char* m_fShader;
};

} //    namespace Ellipse
