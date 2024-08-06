#pragma once

#include "Core/Base.hpp"
#include "Renderer/RenderPlugin.hpp"
#include "Platform/RenderPlugin/OpenGL/OpenGLObj.hpp"

#include <glad/glad.h>

namespace Ellipse
{

class OpenGLRenderPlugin final : public RenderPlugin
{
   public:
    virtual void render(const RenderObj& rObj) override;
    virtual void clearColorBuffer() override;
    virtual void setClearColor(const glm::vec4& col) override;
    virtual void setViewport(int width, int height) override;
    virtual SharedPtr<RenderObj> createRenderObj(VerticiesData verts) override;
    virtual SharedPtr<RenderShaderObj> createShaderObj(String vShader,
                                                       String fShader,
                                                       UniformList uniforms) override;

    virtual void setUniforms(UniformList uniforms, const ForwardList<UniformLoc>& loc) override;

   void renderGL(const OpenGLRenderObj& rObj);

  private:
   int findUniformLocation(const char* name, const ForwardList<UniformLoc>& locs);

  private:
};

}    //   namespace Ellipse
