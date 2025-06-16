
#include "GLRenderPlugin.hpp"
#include "OpenGLObj.hpp"
#include "Debug/Log.hpp"
#include "Math/Matrix.hpp"
#include "EllipsePCH.hpp"

namespace Ellipse
{

void OpenGLRenderPlugin::render(const RenderObj& rObj)
{
    renderGL(static_cast<const OpenGLRenderObj&>(rObj));
}

void OpenGLRenderPlugin::renderGL(const OpenGLRenderObj& rObj)
{
    for(u32_t i = 0; i < rObj.meshes().size(); i++)
    {
    renderGLMesh(static_cast<OpenGLMesh&>(*rObj.meshes()[i]));
    }

}

void OpenGLRenderPlugin::renderGLMesh(const OpenGLMesh& mesh)
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(mesh.vao()); 
    glDrawElements(GL_TRIANGLES, static_cast<i32_t>(mesh.indicies().size()), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void OpenGLRenderPlugin::enable(u64_t glUint)
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderPlugin::clearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void OpenGLRenderPlugin::clearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderPlugin::setClearColor(const glm::vec4& col)
{
    glClearColor(col.x, col.y, col.z, col.w);
}

void OpenGLRenderPlugin::setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height)
{
    glViewport(posX, posY, width, height);
}

RenderObj* OpenGLRenderPlugin::createRenderObj(RenderObjData modelData)
{
    auto rObj = new OpenGLRenderObj();
    
    rObj->initializeFromResources(modelData);

    return rObj;
}

RenderShaderObj* OpenGLRenderPlugin::createShaderObj(String vShader, String fShader)
{
    auto sObj = new OpenGLShaderObj();

    sObj->compileShader(vShader.c_str());
    sObj->compileShader(fShader.c_str());

    sObj->linkGLShaders();

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

void OpenGLRenderPlugin::setUniforms(UniformList uniforms) 
{
   // if(!compareUniformsIsSame(uniforms, locs))
   // {
   // ELLIPSE_ENGINE_LOG_ERROR("Uniform couldn't be found in list");
   // }
  
   for(UniformVarible<i32_t>& uniform : uniforms.getIntUniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
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
   default:
   break;
   }
   }

   for(UniformVarible<float>& uniform : uniforms.getFloatUniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
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
   default:
   break;
   }
   }


   for(UniformVarible<u32_t>& uniform : uniforms.getUnsignedIntUniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
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
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
   glUniform2f(loc, uniform.uniformAt(0).x, uniform.uniformAt(0).y);
   }

   for(UniformVarible<Vec3>& uniform : uniforms.getVec3Uniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
   glUniform3f(loc, uniform.uniformAt(0).x, uniform.uniformAt(0).y, uniform.uniformAt(0).z);
   // ELLIPSE_ENGINE_LOG_INFO("{}, {}, {}", uniform.uniformAt(0).x, uniform.uniformAt(0).y, uniform.uniformAt(0).z);
   }

   for(UniformVarible<Vec4>& uniform : uniforms.getVec4Uniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
   glUniform4f(loc, uniform.uniformAt(0).x, uniform.uniformAt(0).y, uniform.uniformAt(0).z, uniform.uniformAt(0).w);
   }

   for(UniformVarible<Mat2>& uniform : uniforms.getMat2Uniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
   glUniformMatrix2fv(loc, 1, GL_FALSE, &(uniform.uniformAt(0)[0][0]));
   }

   for(UniformVarible<Mat3>& uniform : uniforms.getMat3Uniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
   glUniformMatrix3fv(loc, 1, GL_FALSE, &(uniform.uniformAt(0)[0][0]));
   }

   for(UniformVarible<Mat4>& uniform : uniforms.getMat4Uniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
   glUniformMatrix4fv(loc, 1, GL_FALSE, &(uniform.uniformAt(0)[0][0]));
   // std::cout << loc << '\n';
   }

   for(UniformVarible<bool>& uniform : uniforms.getBoolUniforms())
   {
   i32_t loc = uniforms.uniformLocations()[uniform.name()];
   glUniform1i(loc, uniform.uniformAt(0));
   }

}

void OpenGLRenderPlugin::bindTextures(const RenderObj& renderObj)
{
   glActiveTexture(GL_TEXTURE0);
  
   for(u32_t i=0;i<renderObj.meshes().size();i++)
   {
   for(u32_t j=0;j<renderObj.meshes()[i]->textures().size();j++)
   {
   glBindTexture(GL_TEXTURE_2D, renderObj.meshes()[i]->textures()[j].id());
   }
   }
}

}  // namespace Ellipse
