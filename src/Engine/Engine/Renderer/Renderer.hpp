#pragma once

#include "Core/Base.hpp"
#include "RenderPlugin.hpp"

class Renderer
{
   public:
    Renderer() = default;
    virtual ~Renderer() = default;

    virtual void render(RenderObj& rObj, RenderShaderObj& sObj) = 0;
    virtual void setClearColor(const Vec4& col) = 0;
    virtual void setViewport(int32_t width, int32_t height) = 0;
    virtual UniquePtr<RenderObj> createRenderObj() = 0;
    virtual UniquePtr<RenderShaderObj> createShaderObj() = 0;

    // [ Maybe use template ]
    static UniquePtr<Renderer> createRenderer(UniquePtr<RenderPlugin> plugin);

   private:
};
