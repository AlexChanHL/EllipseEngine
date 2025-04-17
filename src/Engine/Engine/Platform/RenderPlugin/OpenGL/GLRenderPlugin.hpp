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
    virtual void setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height) override;
    // virtual UniquePtr<RenderObj> createRenderObj(RenderObjData modelData) override;
    // virtual UniquePtr<RenderShaderObj> createShaderObj(String vShader,
    //                                                    String fShader) override;
    virtual RenderObj* createRenderObj(RenderObjData modelData) override;
    virtual RenderShaderObj* createShaderObj(String vShader,
                                                 String fShader) override;


    virtual void setUniforms(UniformList uniforms) override;
    virtual void bindTextures(const RenderObj& renderObj) override;

    void renderGL(const OpenGLRenderObj& rObj);
    void renderGLMesh(const OpenGLMesh& mesh);
    

   private:
    int findUniformLocation(const char* name, const ForwardList<UniformLoc>& locs);

  private:
};

}    //   namespace Ellipse
