#pragma once

#include "Renderer/RenderPlugin.hpp"
#include "Platform/RenderPlugin/OpenGL/OpenGLObj.hpp"

#include <glad/glad.h>

class OpenGLRenderPlugin : public RenderPlugin
{
   public:
    virtual void render(RenderObj& rObj, RenderShaderObj& sObj) override;
    virtual void setClearColor(const glm::vec4& col) override;
    virtual void setViewport(int width, int height) override;
    virtual std::unique_ptr<RenderObj> createRenderObj() override;
    virtual std::unique_ptr<RenderShaderObj> createShaderObj() override;

    void renderGL(OpenGLRenderObj& rObj, OpenGLShaderObj& sObj);

   private:
    GLuint m_boundVao;
};
