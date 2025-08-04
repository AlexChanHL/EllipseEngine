#pragma once

// #include "Core/ModelManagerModule.hpp"
// #include "Core/.hpp"
#include "Core/Base.hpp"

#include "UniformVarible.hpp"

#include <stb_image.h>


namespace Ellipse
{

struct Texture
{
   public:
    Texture()
    : m_id{0}
    {

    }
    ~Texture()
    {

    }

    u32_t id() const
    {
    return m_id;
    }

    u32_t& id()
    {
    return m_id;
    }

   private:
    u32_t m_id;
};

class RenderMesh
{
   public:
    RenderMesh()
    {

    }
    virtual ~RenderMesh()
    {
     
    }

    virtual u32_t vao() const = 0;
    virtual Vector<float> positions() const = 0;
    virtual Vector<float> normals() const = 0;
    virtual Vector<float> textureCoords() const = 0;
    virtual Vector<u32_t> indicies() const = 0;
    virtual Vector<Texture> textures() const = 0;

    bool isTextured() const
    {
        return textures().size() > 0;
    }

   private:
};

class TextureData
{
   public:
    TextureData()
    : m_width{0},
      m_height{0},
      m_clrChannels{0},
      m_data{nullptr}
    {

    }
    ~TextureData()
    {

    }
    TextureData(const TextureData& textureData)
    : m_width{textureData.m_width},
      m_height{textureData.m_height},
      m_clrChannels{textureData.m_clrChannels},
      m_data{textureData.m_data}
    {
     
    }
    void operator=(const TextureData& textureData)
    {
        m_width = textureData.m_width;
        m_height = textureData.m_height;
        m_clrChannels = textureData.m_clrChannels;
        m_data = textureData.m_data;
    }

   public:
    String m_path;
    i32_t m_width;
    i32_t m_height;
    i32_t m_clrChannels;
    unsigned char* m_data;

   private:
};

class TextureReminder
{
   public:
    TextureReminder(String path)
    : m_path{path},
      m_isFulfilled{false}
    {

    }
    ~TextureReminder()
    {
        if(!m_isFulfilled)
        {
            ELLIPSE_ENGINE_LOG_WARN("Did not fulfill {}", m_path);
        }
    }

    void fulfill(TextureData& texture)
    {
        m_isFulfilled = true;
        stbi_image_free(texture.m_data);
    }

    void load(String path)
    {
        m_path = path;
        m_isFulfilled = false;
    }

   private:
    String m_path;
    bool m_isFulfilled;
};

inline void loadTexture(TextureReminder& reminder, TextureData& texture, String path)
{
    texture.m_path = path;
    // stbi_set_flip_vertically_on_load(true);
    texture.m_data = stbi_load(path.c_str(), &texture.m_width, &texture.m_height, &texture.m_clrChannels, 0);
    if(!texture.m_data)
    {
        ELLIPSE_ENGINE_LOG_WARN("Error creating texture data");
    }

    reminder.load(path);
}

class RenderObjData
{
   public:
    RenderObjData()
    {

    }
    RenderObjData(Vector<u32_t> indicies, Vector<float> positions, Vector<float> normals, Vector<float> textureCoords)
    : m_indicies{indicies},
      m_positions{positions},
      m_normals{normals},
      m_textureCoords{textureCoords}
    {

    }
    ~RenderObjData()
    {

    }

    void setIndicies(Vector<u32_t> indicies)
    {
    m_indicies = indicies;
    }
    void setPositions(Vector<float> positions)
    {
    m_positions = positions;
    }
    void setNormals(Vector<float> normals)
    {
    m_normals = normals;
    }
    void setTexCoords(Vector<float> textureCoords)
    {
    m_textureCoords = textureCoords;
    }

    Vector<u32_t> indicies()
    {
    return m_indicies;
    }
    Vector<float> positions()
    {
    return m_positions;
    }
    Vector<float> normals()
    {
    return m_normals;
    }
    Vector<float> textureCoords()
    {
    return m_textureCoords;
    }
    TextureData& textureData()
    {
        return m_textureData;
    }

   private:
    Vector<u32_t> m_indicies;
    Vector<float> m_positions;
    Vector<float> m_normals;
    Vector<float> m_textureCoords;
    TextureData m_textureData;
};

using PreDefinedObjects = Map<String, RenderObjData>;

struct RenderObj
{
   public:
    RenderObj()
    {

    }
    virtual ~RenderObj()
    {

    }


    virtual void initializeFromResources(RenderObjData& data) = 0;

    virtual Vector<UniquePtr<RenderMesh>> meshes() = 0;
    virtual Vector<UniquePtr<RenderMesh>> meshes() const = 0;
    // virtual time_t timeCreated() = 0;
   public:
};

class RenderModelObject
{
   public:
    RenderModelObject()
    {

    }
    ~RenderModelObject()
    {

    }

   private:
};

class RenderShaderObj
{
    public:
     RenderShaderObj() = default;
     virtual ~RenderShaderObj() = default;

     virtual void addShader(const char* fname) = 0;
     virtual void linkShaders() = 0;
     virtual void use() const = 0;

     virtual void getShaderSource() = 0;

     virtual i32_t findUniformLocation(const char* name) = 0;
     virtual Map<const char*, i32_t> findUniformLocationList(UniformList uniformList) = 0;

    private:
};

}    // namespace Ellipse
