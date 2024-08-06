#pragma once

#include "Core/Base.hpp"
#include "RenderPlugin.hpp"
#include "VerticiesData.hpp"
#include "UniformVarible.hpp"
#include "Engine/Engine.hpp"
#include "Engine/System.hpp"

namespace Ellipse
{

class Renderer : public ISystem
{
   public:
    Renderer() = default;
    explicit Renderer(ISystem& system);
    virtual ~Renderer() = default;

    virtual void render(const RenderObj& rObj, const RenderShaderObj& sObj) = 0;
    virtual void clearColorBuffer() = 0;
    virtual void setClearColor(const Vec4& col) = 0;
    virtual void setWindowFrameSize(Pair<int, int> winSize) = 0;
    virtual void setViewport(int32_t width, int32_t height) = 0;
    virtual Pair<int, int> getWindowFrameSize() = 0;
    virtual SharedPtr<RenderObj> createRenderObj(VerticiesData verts) = 0;
    virtual SharedPtr<RenderShaderObj> createShaderObj(String vShader,
                                                 String fShader,
                                                 UniformList uniforms) = 0;

    // [ Maybe use template ]
    static SharedPtr<Renderer> createRenderer(UniquePtr<RenderPlugin> plugin);

   private:
};

}    // namespace Ellipse
