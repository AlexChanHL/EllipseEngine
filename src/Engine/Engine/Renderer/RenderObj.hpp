#pragma once

#include "Core/Base.hpp"

struct RenderObj
{
   public:
    RenderObj() = default;
    virtual ~RenderObj() = default;
    virtual void initRenderObj(std::vector<float> verts) = 0;

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

     virtual void setUniform(const char* name, float x) = 0;
     virtual void setUniform(const char* name, float x, float y) = 0;
     virtual void setUniform(const char* name, float x, float y, float z) = 0;
     virtual void setUniform(const char* name, float x, float y, float z, float w) = 0;

     virtual void setUniform(const char* name, int x) = 0;
     virtual void setUniform(const char* name, int x, int y) = 0;
     virtual void setUniform(const char* name, int x, int y, int z) = 0;
     virtual void setUniform(const char* name, int x, int y, int z, int w) = 0;

     virtual void setUniform(const char* name, unsigned int x) = 0;
     virtual void setUniform(const char* name, unsigned int x, unsigned int y) = 0;
     virtual void setUniform(const char* name, unsigned int x, unsigned int y, unsigned int z) = 0;
     virtual void setUniform(const char* name, unsigned int x, unsigned int y, unsigned int z, unsigned int w) = 0;

     virtual void setUniform(const char* name, Mat4& mat) = 0;
     virtual void setUniform(const char* name, Vec3& vec) = 0;
     
    private:
};
