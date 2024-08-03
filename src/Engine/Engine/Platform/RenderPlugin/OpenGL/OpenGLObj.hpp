#pragma once

#include "Core/Base.hpp"
#include "Renderer/RenderObj.hpp"
#include "Renderer/UniformVarible.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ellipse
{

struct OpenGLRenderObj : public RenderObj
{
   public:
    void initBuffers(Vector<float> verts);
    void setVerts(u32_t verts)
    {
    m_nVerts = verts;
    }

   public:
    uint32_t m_nVerts;
    GLuint m_vao;
};

class OpenGLShaderObj : public RenderShaderObj
{
   public:

    OpenGLShaderObj();
    ~OpenGLShaderObj();

    virtual void addShader(const char* name) override;
    virtual void linkShaders() override;
    virtual void use() const override;

    virtual void addUniform(UniformVarible<i32_t> uniform) override;
    virtual void addUniform(UniformVarible<float> uniform) override;
    virtual void addUniform(UniformVarible<u32_t> uniform) override;
    virtual void addUniform(UniformVarible<Vec2> uniform) override;
    virtual void addUniform(UniformVarible<Vec3> uniform) override;
    virtual void addUniform(UniformVarible<Vec4> uniform) override;
    virtual void addUniform(UniformVarible<Mat2> uniform) override;
    virtual void addUniform(UniformVarible<Mat3> uniform) override;
    virtual void addUniform(UniformVarible<Mat4> uniform) override;

    virtual void setUniformPtr(const UniformVarible<i32_t>& uniform) override;
    virtual void setUniformPtr(const UniformVarible<float>& uniform) override;
    virtual void setUniformPtr(const UniformVarible<u32_t>& uniform) override;
    virtual void setUniformPtr(const UniformVarible<Mat4>& uniform) override;
    
    void setUniformList(UniformList& uniforms);
    void compileShader(const char* fname);
    void linkGLShaders();

    void deleteAttachedShaders(GLuint vert, GLuint frag);

    virtual void addUniformsToLocList(UniformList uniforms) override;
    virtual UniformList getUniforms() const override
    {
    return m_uniforms;
    }
    virtual ForwardList<UniformLoc> getUniformLocs() const override
    {
    return m_uniformLoc;
    }
   
    void printUniformLocations() override;

   public:
    GLuint m_prog;

   private:
    void addUniformToList(const char* name);
    GLenum queryType(const char* fname);

    void checkCompileStatus(GLuint shader);
    void checkLinkStatus();

    void deleteAttachedShaders();

    void addUniform(const char* name, int& loc);

    const char* typeToCString(GLenum type);

   private:
    Map<const char*, GLenum> m_typeMap;
    ForwardList<UniformLoc> m_uniformLoc;
    UniformList m_uniforms;
};

}    // namespace Ellipse
