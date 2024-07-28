
#include "GLRenderPlugin.hpp"
#include "OpenGLObj.hpp"
#include "EllipsePCH.hpp"


void OpenGLRenderPlugin::render(RenderObj& rObj, RenderShaderObj& sObj)
{
     renderGL(static_cast<OpenGLRenderObj&>(rObj), 
              static_cast<OpenGLShaderObj&>(sObj));
}

void OpenGLRenderPlugin::setClearColor(const glm::vec4& col)
{
     glClearColor(col.x, col.y, col.z, col.w);
}

void OpenGLRenderPlugin::setViewport(int width, int height)
{
     glViewport(0, 0, width, height);
}

UniquePtr<RenderObj> OpenGLRenderPlugin::createRenderObj()
{
    return createUnique<OpenGLRenderObj>();
}

UniquePtr<RenderShaderObj> OpenGLRenderPlugin::createShaderObj()
{
    return createUnique<OpenGLShaderObj>();
}

void OpenGLRenderPlugin::renderGL(OpenGLRenderObj& rObj, OpenGLShaderObj& sObj)
{
      glClear(GL_COLOR_BUFFER_BIT);

      sObj.use();

      glBindVertexArray(rObj.m_vao);
      glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(rObj.m_nVerts));
      glBindVertexArray(0);
}
