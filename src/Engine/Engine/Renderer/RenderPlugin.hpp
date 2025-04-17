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
    virtual void setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height) = 0;
    // virtual UniquePtr<RenderObj> createRenderObj(RenderObjData verts) = 0;
    // virtual UniquePtr<RenderShaderObj> createShaderObj(String vShader, String fShader) = 0;
    virtual RenderObj* createRenderObj(RenderObjData verts) = 0;
    virtual RenderShaderObj* createShaderObj(String vShader, String fShader) = 0;
    virtual void setUniforms(UniformList uniforms) = 0;
    virtual void bindTextures(const RenderObj& renderObj) = 0;

    static UniquePtr<RenderPlugin> createRenderPlugin(GraphicsSpec spec);

   private:

};

}    // namespace Ellipse
