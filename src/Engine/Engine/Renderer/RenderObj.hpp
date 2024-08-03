#pragma once

#include "UniformVarible.hpp"
#include "Core/Base.hpp"

namespace Ellipse
{

struct RenderObj
{
   public:
    RenderObj() = default;
    virtual ~RenderObj() = default;

   public:

};

class RenderShaderObj
{
    public:
     RenderShaderObj() = default;
     virtual ~RenderShaderObj() = default;

     virtual void addShader(const char* fname) = 0;
     virtual void linkShaders() = 0;
     virtual void use() const = 0;
     virtual void printUniformLocations() = 0;

     virtual void addUniform(UniformVarible<i32_t> uniform) = 0;
     virtual void addUniform(UniformVarible<float> uniform) = 0;
     virtual void addUniform(UniformVarible<u32_t> uniform) = 0;
     virtual void addUniform(UniformVarible<Vec2> uniform) = 0;
     virtual void addUniform(UniformVarible<Vec3> uniform) = 0;
     virtual void addUniform(UniformVarible<Vec4> uniform) = 0;
     virtual void addUniform(UniformVarible<Mat2> uniform) = 0;
     virtual void addUniform(UniformVarible<Mat3> uniform) = 0;
     virtual void addUniform(UniformVarible<Mat4> uniform) = 0;


     virtual void addUniformsToLocList(UniformList uniforms) = 0;

     virtual void setUniformPtr(const UniformVarible<i32_t>& uniform) = 0;
     virtual void setUniformPtr(const UniformVarible<float>& uniform) = 0;
     virtual void setUniformPtr(const UniformVarible<u32_t>& uniform) = 0;
     virtual void setUniformPtr(const UniformVarible<Mat4>& uniform) = 0;

     virtual UniformList getUniforms() const = 0;
     virtual ForwardList<UniformLoc> getUniformLocs() const = 0;

    private:
};

}    // namespace Ellipse
