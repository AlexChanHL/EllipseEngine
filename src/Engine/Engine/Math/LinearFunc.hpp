#pragma once

#include "Base.hpp"


namespace Ellipse
{

namespace EllipseMath
{

inline Vec3 rotateXAxis(Vec3 position, float theta)
{
    Mat3 xAxisMatrix{1.0f};

    xAxisMatrix[1][1] = static_cast<float>(cos(theta));
    xAxisMatrix[1][2] = static_cast<float>(sin(theta));
    xAxisMatrix[2][1] = static_cast<float>(-sin(theta));
    xAxisMatrix[2][2] = static_cast<float>(cos(theta));

    return position * xAxisMatrix;
}

inline Vec3 rotateYAxis(Vec3 position, float theta)
{
    Mat3 yAxisMatrix{1.0f};

    yAxisMatrix[0][0] = static_cast<float>(cos(theta));
    yAxisMatrix[0][2] = static_cast<float>(sin(theta));
    yAxisMatrix[2][0] = static_cast<float>(-sin(theta));
    yAxisMatrix[2][2] = static_cast<float>(cos(theta));

    return position * yAxisMatrix;
}

inline Vec3 rotateZAxis(Vec3 position, float theta)
{
    Mat3 zAxisMatrix{1.0f};

    zAxisMatrix[0][0] = static_cast<float>(cos(theta));
    zAxisMatrix[0][1] = static_cast<float>(sin(theta));
    zAxisMatrix[1][0] = static_cast<float>(-sin(theta));
    zAxisMatrix[1][1] = static_cast<float>(cos(theta));

    return position * zAxisMatrix;
}

// inline Vec3 rotate(Vec3 vec, Vec3 axis, float theta)
// {
//     if(axis.x > 0)
//     {
//         vec = rotateXAxis(vec);
//     }
//     if(axis.y > 0)
//     {
//         vec = rotateYAxis(vec);
//     }
//     if(axis.z > 0)
//     {
//         vec = rotateZAxis(vec);
//     }
//
//     return vec;
// }

}             // namespace EllipseMath

}             // namespace Ellipse

