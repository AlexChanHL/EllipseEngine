
#include "GLRenderPlugin.hpp"
#include "OpenGLObj.hpp"
#include "Debug/Log/Log.hpp"
#include "EllipsePCH.hpp"

namespace Ellipse
{

void OpenGLRenderPlugin::render(const RenderObj& rObj)
{
     renderGL(static_cast<const OpenGLRenderObj&>(rObj));
}

void OpenGLRenderPlugin::renderGL(const OpenGLRenderObj& rObj)
{
     glBindVertexArray(rObj.m_vao);
     glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(rObj.m_nVerts));
     glBindVertexArray(0);
}

void OpenGLRenderPlugin::clearColorBuffer()
{
     glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderPlugin::setClearColor(const glm::vec4& col)
{
     glClearColor(col.x, col.y, col.z, col.w);
}

void OpenGLRenderPlugin::setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height)
{
     glViewport(posX, posY, width, height);
}

SharedPtr<RenderObj> OpenGLRenderPlugin::createRenderObj(VerticiesData verts)
{
     auto rObj = createUnique<OpenGLRenderObj>();
     rObj->setVerts(verts.numVerts());
     rObj->initBuffers(verts.verticies());
     return rObj;
}

SharedPtr<RenderShaderObj> OpenGLRenderPlugin::createShaderObj(String vShader, String fShader, UniformList uniforms)
{
     auto sObj = createShared<OpenGLShaderObj>();

     sObj->compileShader(vShader.c_str());
     sObj->compileShader(fShader.c_str());

     sObj->linkGLShaders();

     sObj->setUniformList(uniforms);
     sObj->addUniformsToLocList(uniforms);
  
     return sObj;
}

i32_t OpenGLRenderPlugin::findUniformLocation(const char* name, const ForwardList<UniformLoc>& locs)
{
     for(auto& a : locs)
     {
     if(strcmp(name, a.m_name) == 0)
     {
     return a.m_loc;
     }
     } 

     ELLIPSE_ENGINE_LOG_ERROR("Uniform not found");

     return 0;
}

void OpenGLRenderPlugin::setUniforms(UniformList uniforms, const ForwardList<UniformLoc>& locs) 
{
    for(UniformVarible<i32_t>& uniform : uniforms.getIntUniforms())
     {
    int loc = findUniformLocation(uniform.name(), locs);
    switch(uniform.size())
    {
    case 1:
    glUniform1i(loc, uniform.uniformAt(0));
    break;
    case 2:
    glUniform2i(loc, uniform.uniformAt(0), uniform.uniformAt(1));
    break;
    case 3:
    glUniform3i(loc, uniform.uniformAt(0), uniform.uniformAt(1), uniform.uniformAt(2));
    break;
    case 4:
    glUniform4i(loc, uniform.uniformAt(0), uniform.uniformAt(1), uniform.uniformAt(2), uniform.uniformAt(3));
    break;
    }
    }

    for(UniformVarible<float>& uniform : uniforms.getFloatUniforms())
    {
    int loc = findUniformLocation(uniform.name(), locs);
    switch(uniform.size())
    {
    case 1:
    glUniform1f(loc, uniform.uniformAt(0));
    break;
    case 2:
    glUniform2f(loc, uniform.uniformAt(0), uniform.uniformAt(1));
    break;
    case 3:
    glUniform3f(loc, uniform.uniformAt(0), uniform.uniformAt(1), uniform.uniformAt(2));
    break;
    case 4:
    glUniform4f(loc, uniform.uniformAt(0), uniform.uniformAt(1), uniform.uniformAt(2), uniform.uniformAt(3));
    break;
    }
    }


    for(UniformVarible<u32_t>& uniform : uniforms.getUnsignedIntUniforms())
    {
    int loc = findUniformLocation(uniform.name(), locs);
    switch(uniform.size())
    {
    case 1:
    glUniform1ui(loc, uniform.uniformAt(0));
    break;
    case 2:
    glUniform2ui(loc, uniform.uniformAt(0), uniform.uniformAt(1));
    break;
    case 3:
    glUniform3ui(loc, uniform.uniformAt(0), uniform.uniformAt(1), uniform.uniformAt(2));
    break;
    case 4:
    glUniform4ui(loc, uniform.uniformAt(0), uniform.uniformAt(1), uniform.uniformAt(2), uniform.uniformAt(3));
    break;
    }
    }

    // // [ Setting vectors and matricies one at a time, maybe have
    //      a single list of all ]
    for(UniformVarible<Vec2>& uniform : uniforms.getVec2Uniforms())
    {
    int loc = findUniformLocation(uniform.name(), locs);
    glUniform2f(loc, uniform.uniformAt(0).x, uniform.uniformAt(0).y);
    }

    for(UniformVarible<Vec3>& uniform : uniforms.getVec3Uniforms())
    {
    int loc = findUniformLocation(uniform.name(), locs);
    glUniform3f(loc, uniform.uniformAt(0).x, uniform.uniformAt(0).y, uniform.uniformAt(0).z);
    }

    for(UniformVarible<Vec4>& uniform : uniforms.getVec4Uniforms())
    {
    int loc = findUniformLocation(uniform.name(), locs);
    glUniform4f(loc, uniform.uniformAt(0).x, uniform.uniformAt(0).y, uniform.uniformAt(0).z, uniform.uniformAt(0).w);
    }

    for(UniformVarible<Mat2>& uniform : uniforms.getMat2Uniforms())
    {
    int loc = findUniformLocation(uniform.name(), locs);
    glUniformMatrix2fv(loc, 1, GL_FALSE, &(uniform.uniformAt(0)[0][0]));
    }

    for(UniformVarible<Mat3>& uniform : uniforms.getMat3Uniforms())
    {
    int loc = findUniformLocation(uniform.name(), locs);
    glUniformMatrix3fv(loc, 1, GL_FALSE, &(uniform.uniformAt(0)[0][0]));
    }

    for(UniformVarible<Mat4>& uniform : uniforms.getMat4Uniforms())
    {
    // uniform.printUniforms();
    int loc = findUniformLocation(uniform.name(), locs);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &(uniform.uniformAt(0)[0][0]));
    }

}

}  // namespace Ellipse
