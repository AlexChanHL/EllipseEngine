#pragma once

#include "Core/Base.hpp"
#include "VerticiesData.hpp"
#include "Renderer/UniformVarible.hpp"
#include "RenderObj.hpp"

// Use own math library instead
#include <glm/glm.hpp>

namespace Ellipse
{

enum class GraphicsSpec : uint32_t
{
    OpenGL
};

class RenderPlugin
{
   public:
    RenderPlugin() = default;
    virtual ~RenderPlugin() = default;
    virtual void render(const RenderObj& rObj) = 0;
    virtual void clearColorBuffer() = 0;
    virtual void setClearColor(const glm::vec4& col) = 0;
    virtual void setViewport(int width, int height) = 0;
    virtual SharedPtr<RenderObj> createRenderObj(VerticiesData verts) = 0;
    virtual SharedPtr<RenderShaderObj> createShaderObj(String vShader, String fShader, UniformList uniforms) = 0;
    virtual void setUniforms(UniformList uniforms, const ForwardList<UniformLoc>& loc) = 0;

    static UniquePtr<RenderPlugin> createRenderPlugin(GraphicsSpec spec);

   private:

};

}    // namespace Ellipse
