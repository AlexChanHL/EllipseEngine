#pragma once

#include "Core/Base.hpp"
#include "Renderer/RenderObj.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


struct OpenGLRenderObj : public RenderObj
{
   public:
    void initRenderObj(Vector<float> verts) override;
    void initBuffers(Vector<float> verts);

   public:
    uint32_t m_nVerts;
    GLuint m_vao;
};

struct UniformLoc
{
   public:
    const char* m_name;
    int m_loc;
};

class OpenGLShaderObj : public RenderShaderObj
{
   public:

    OpenGLShaderObj();
    ~OpenGLShaderObj();

    virtual void addShader(const char* name) override;
    virtual void linkShaders() override;
    virtual void use() const override;

    void compileShader(const char* fname);
    void linkGLShaders();

    void deleteAttachedShaders(GLuint vert, GLuint frag);

    void addUniform(const char* name);

    virtual void setUniform(const char* name, float x) override;
    virtual void setUniform(const char* name, float x, float y) override;
    virtual void setUniform(const char* name, float x, float y, float z) override;
    virtual void setUniform(const char* name, float x, float y, float z, float w) override;

    virtual void setUniform(const char* name, int x) override;
    virtual void setUniform(const char* name, int x, int y) override;
    virtual void setUniform(const char* name, int x, int y, int z) override;
    virtual void setUniform(const char* name, int x, int y, int z, int w) override;

    virtual void setUniform(const char* name, unsigned int x) override;
    virtual void setUniform(const char* name, unsigned int x, unsigned int y) override;
    virtual void setUniform(const char* name, unsigned int x, unsigned int y, unsigned int z) override;
    virtual void setUniform(const char* name, unsigned int x, unsigned int y, unsigned int z, unsigned int w) override;

    virtual void setUniform(const char* name, glm::mat4& mat) override;
    virtual void setUniform(const char* name, glm::vec3& vec) override;
   
    void printUniformLocations();

   public:
    GLuint m_prog;

   private:
    GLenum queryType(const char* fname);

    void checkCompileStatus(GLuint shader);
    void checkLinkStatus();

    void deleteAttachedShaders();

    int findUniformLocation(const char* name);
    void addUniform(const char* name, int& loc);

    const char* typeToCString(GLenum type);

   private:
    Map<const char*, GLenum> m_typeMap;
    ForwardList<UniformLoc> m_uniformLoc;
};
