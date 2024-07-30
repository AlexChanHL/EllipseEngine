#pragma once

#include "Core/Base.hpp"
#include "RenderPlugin.hpp"
#include "Engine/System.hpp"

class Renderer : public ISystem
{
   public:
    Renderer() = default;
    explicit Renderer(ISystem& system);
    virtual ~Renderer() = default;

    virtual void render(RenderObj& rObj, RenderShaderObj& sObj) = 0;
    virtual void setClearColor(const Vec4& col) = 0;
    virtual void setViewport(int32_t width, int32_t height) = 0;
    virtual UniquePtr<RenderObj> createRenderObj() = 0;
    virtual UniquePtr<RenderShaderObj> createShaderObj() = 0;

    // [ Maybe use template ]
    static SharedPtr<Renderer> createRenderer(UniquePtr<RenderPlugin> plugin);

   private:
};
