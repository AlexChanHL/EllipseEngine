#pragma once

#include "Core/Base.hpp"
#include "Renderer/RenderObj.hpp"
#include "Renderer/UniformVarible.hpp"


#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
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

    void initializeMesh(Vector<u32_t> indicies,
                        Vector<float> positions,
                        Vector<float> normals,
                        Vector<float> textureCoords,
                        bool isTextured
                       )
    {

    if(isTextured)
    {
        m_textures.push_back(Texture{});
        glGenTextures(1, &m_textures[0].id());

        i32_t textureWidth = 0;
        i32_t textureHeight = 0;
        i32_t textureClrChannels = 0;

        // stbi_set_flip_vertically_on_load(true);
        unsigned char* textureData = stbi_load("Assets/Images/Message.png", &textureWidth, &textureHeight, &textureClrChannels, 0);
        if(!textureData)
        {
            ELLIPSE_ENGINE_LOG_WARN("Error creating texture data");
        }

        glGenTextures(1, &m_textures[0].id());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textures[0].id());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        Assimp::Importer importer;

        auto scene = importer.ReadFile("./Assets/Models/Cube.glb", 0);
        // if(scene->mNumTextures)
        // {
        //
        // }
        // if(scene->mTextures[0]->CheckFormat("png"))
        // {
        //     // std::cout << scene->mTextures[0]->mFilename.c_str() << ".png\n";
        // }

        auto texture = scene->mTextures[0];
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<i32_t>(texture->mWidth), static_cast<i32_t>(texture->mHeight), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pcData);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(textureData);
    }

    m_indicies = indicies;
    m_positions = positions;
    m_normals = normals;
    m_textureCoords = textureCoords;


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
    openGLMesh.initializeMesh(data.indicies(),
                              data.positions(),
                              data.normals(),
                              data.textureCoords(),
                              data.isTextured()
                             );

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

    virtual void getShaderSource() override;

    virtual i32_t findUniformLocation(const char* name) override;
    virtual Map<const char*, i32_t> findUniformLocationList(UniformList uniformList) override;

    void compileShader(const char* fname);
    void linkGLShaders();

    void deleteAttachedShaders(GLuint vert, GLuint frag);

   public:
    GLuint m_shaderProgram;

   private:
    GLenum queryType(const char* fname);

    void checkCompileStatus(GLuint shader);
    void checkLinkStatus();

    void deleteAttachedShaders();
    const char* typeToCString(GLenum type);

   private:
    Map<String, GLenum> m_typeMap;
};

}    // namespace Ellipse

