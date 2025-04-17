#pragma once

#include "Core/Base.hpp"
#include "Renderer/RenderObj.hpp"
#include "Renderer/UniformVarible.hpp"


#include <stb_image.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ellipse
{


template<typename T, typename D>
Vector<UniquePtr<T>> createVectorFromDerived(Vector<D> derived)
{
    Vector<UniquePtr<T>> dataCollect;
    for(u32_t i = 0; i < derived.size(); i++)
    {
    dataCollect.push_back(createUnique<D>(derived[i]));
    }

    return dataCollect;
   
}

// A signle entity
class OpenGLMesh : public RenderMesh
{
   public:
    OpenGLMesh()
    {

    }
    virtual ~OpenGLMesh()
    {

    }

    void initializeMesh()
    // void initializeMesh(Vector<float> positions,
    //                     Vector<float> normals,
    //                     Vector<float> textureCoords)
    {
    m_textures.push_back(Texture{});
    glGenTextures(1, &m_textures[0].id());

    i32_t textureWidth;
    i32_t textureHeight;
    i32_t textureClrChannels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load("Assets/Images/GreenColor.png", &textureWidth, &textureHeight, &textureClrChannels, 0);
    // unsigned char* textureData = stbi_load("../build/debug/Debug/bin/Assets/Images/GreenColor.png", &textureWidth, &textureHeight, &textureClrChannels, 0);
    if(!textureData)
    {
    ELLIPSE_ENGINE_LOG_WARN("Error creating texture data");
    }


    stbi_image_free(textureData);

    glGenTextures(1, &m_textures[0].id());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textures[0].id());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    m_indicies = Vector<u32_t>
    {
    0, 2, 3,
    0, 1, 3,

    4, 5, 7,
    4, 6, 7,

    8, 9, 11,
    8, 10, 11,

    12, 13, 15,
    12, 14, 15,

    16, 17, 19,
    16, 18, 19,

    20, 21, 23,
    20, 22, 23
    };

    m_positions = Vector<float>
    {
    -0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
    -0.5f, -0.5f,  0.5f,  
     0.5f, -0.5f,  0.5f,  

     0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f, -0.5f,  
     0.5f, -0.5f,  0.5f,  
     0.5f, -0.5f, -0.5f,  

    -0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
    -0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  

    -0.5f,  0.5f,  0.5f,  
    -0.5f,  0.5f, -0.5f,  
    -0.5f, -0.5f,  0.5f,  
    -0.5f, -0.5f, -0.5f,  

    -0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
    -0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  

    -0.5f, -0.5f,  0.5f,  
     0.5f, -0.5f,  0.5f,  
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f
    };

    Vector<Vec3> cubeNormals;  

    Vector<Vec3> point;
    Vector<float> storeFloats;

    for(uint32_t i = 0; i < m_positions.size(); i++)
    {
    storeFloats.push_back(m_positions[i]);
    if(((i + 1) % 3) == 0)
    {
    point.push_back(Vec3(storeFloats[0], storeFloats[1], storeFloats[2]));
    storeFloats.clear();
    }

    if(((i + 1) % 12) == 0)
    {
    cubeNormals.push_back(EllipseMath::cross((point[0] - point[1]), (point[0] - point[2])));
    point.clear();
    }

    }

    for(uint32_t i = 0; i < cubeNormals.size(); i++)
    {
    for(uint32_t j = 0; j < 4; j++)
    {
    m_normals.push_back(cubeNormals[i].x);
    m_normals.push_back(cubeNormals[i].y);
    m_normals.push_back(cubeNormals[i].z);
    }

    }

    m_textureCoords = Vector<float>
    {
     0.0f, 0.0f,
     1.0f, 0.0f,
     0.0f, 1.0f,
     1.0f, 1.0f,

     0.0f, 0.0f,
     1.0f, 0.0f,
     0.0f, 1.0f,
     1.0f, 1.0f,

     0.0f, 0.0f,
     1.0f, 0.0f,
     0.0f, 1.0f,
     1.0f, 1.0f,

     0.0f, 0.0f,
     1.0f, 0.0f,
     0.0f, 1.0f,
     1.0f, 1.0f,

     0.0f, 0.0f,
     1.0f, 0.0f,
     0.0f, 1.0f,
     1.0f, 1.0f,

     0.0f, 0.0f,
     1.0f, 0.0f,
     0.0f, 1.0f,
     1.0f, 1.0f,
    };


    u32_t positionsBuffer = 0;
    u32_t normalsBuffer = 0;
    u32_t textureCoordsBuffer = 0;
    u32_t indiciesBuffer = 0;


    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);  

    glGenBuffers(1, &indiciesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<long>(m_indicies.size() * sizeof(u32_t)),
                 m_indicies.data(),
                 GL_STATIC_DRAW
                 );
  
    glGenBuffers(1, &positionsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(m_positions.size() * sizeof(float)),
                 m_positions.data(),
                 GL_STATIC_DRAW
                );

    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(m_normals.size() * sizeof(float)),
                 m_normals.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, &textureCoordsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureCoordsBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(m_textureCoords.size() * sizeof(float)),
                 m_textureCoords.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

    glBindBuffer(GL_ARRAY_BUFFER, textureCoordsBuffer);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);


    glBindVertexArray(0);

    }


    virtual u32_t vao() const override
    {
    return m_vao;
    }

    virtual Vector<float> positions() const override
    {
    return m_positions;
    }

    virtual Vector<float> normals() const override
    {
    return m_normals;
    }

    virtual Vector<float> textureCoords() const override
    {
    return m_textureCoords;
    }

    virtual Vector<u32_t> indicies() const override
    {
    return m_indicies;
    }

    virtual Vector<Texture> textures() const override
    {
    return m_textures;
    }


   private:
    u32_t m_vao;

    Vector<float> m_normals;
    Vector<float> m_positions;
    Vector<float> m_textureCoords;

    Vector<u32_t> m_indicies;
    Vector<Texture> m_textures;
};

struct OpenGLRenderObj : public RenderObj
{
   public:
    OpenGLRenderObj()
    {

    }
    ~OpenGLRenderObj()
    {

    }

    virtual void initializeFromResources(RenderObjData& data) override
    {
    OpenGLMesh openGLMesh;
    openGLMesh.initializeMesh();

    m_meshes.push_back(openGLMesh);
    }


    virtual bool isTextured() const override
    {
    return true;
    }

    virtual Vector<UniquePtr<RenderMesh>> meshes() override
    {
    return createVectorFromDerived<RenderMesh, OpenGLMesh>(m_meshes);

    }

    virtual Vector<UniquePtr<RenderMesh>> meshes() const override
    {
    return createVectorFromDerived<RenderMesh, OpenGLMesh>(m_meshes);
    }

   public:

   private:
    Vector<OpenGLMesh> m_meshes;
};

class OpenGLShaderObj : public RenderShaderObj
{
   public:
    OpenGLShaderObj();
    ~OpenGLShaderObj();

    virtual void addShader(const char* name) override;
    virtual void linkShaders() override;
    virtual void use() const override;

    virtual i32_t findUniformLocation(const char* name) override;
    virtual Map<const char*, i32_t> findUniformLocationList(UniformList uniformList) override;

    // virtual void addUniform(UniformVarible<i32_t> uniform) override;
    // virtual void addUniform(UniformVarible<float> uniform) override;
    // virtual void addUniform(UniformVarible<u32_t> uniform) override;
    // virtual void addUniform(UniformVarible<Vec2> uniform) override;
    // virtual void addUniform(UniformVarible<Vec3> uniform) override;
    // virtual void addUniform(UniformVarible<Vec4> uniform) override;
    // virtual void addUniform(UniformVarible<Mat2> uniform) override;
    // virtual void addUniform(UniformVarible<Mat3> uniform) override;
    // virtual void addUniform(UniformVarible<Mat4> uniform) override;
    //
    // virtual void setUniformPtr(const UniformVarible<i32_t>& uniform) override;
    // virtual void setUniformPtr(const UniformVarible<float>& uniform) override;
    // virtual void setUniformPtr(const UniformVarible<u32_t>& uniform) override;
    // virtual void setUniformPtr(const UniformVarible<Mat4>& uniform) override;
    // 
    // void setUniformList(UniformList& uniforms);
    
    void compileShader(const char* fname);
    void linkGLShaders();

    void deleteAttachedShaders(GLuint vert, GLuint frag);

    // virtual void addUniformsToLocList(UniformList uniforms) override;
    // virtual UniformList getUniforms() const override
    // {
    // return m_uniforms;
    // }
    // virtual ForwardList<UniformLoc> getUniformLocs() const override
    // {
    // return m_uniformLoc;
    // }
    // 
    // void printUniformLocations() override;

   public:
    GLuint m_shaderProgram;

   private:
    // void addUniformToList(const char* name);
    GLenum queryType(const char* fname);

    void checkCompileStatus(GLuint shader);
    void checkLinkStatus();

    void deleteAttachedShaders();

    // void addUniform(const char* name, int& loc);

    const char* typeToCString(GLenum type);

   private:
    Map<const char*, GLenum> m_typeMap;
    // ForwardList<UniformLoc> m_uniformLoc;
    // UniformList m_uniforms;
};

}    // namespace Ellipse
