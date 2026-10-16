
#include "Core/Base.hpp"
#include "Matrix.hpp"

namespace Ellipse
{

namespace EllipseMath
{

void printMat(const Mat4& mat)
{
    for(int i=0;i<4;i++)
    {
    std::cout << "Row: ";
    for(int j=0;j<4;j++)
    {
    std::cout << mat[j][i] << " ";
    }
    std::cout << "\n";
    }
}

void printVec(const Vec3& vec)
{
    std::cout << vec.x << " , " << vec.y << " , " << vec.z << '\n';
}


}    // namespace EllipseMath

}    // namespace Ellipse
