#pragma once

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
    private:
};
