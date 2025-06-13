#pragma once

// #include "Core/ModelManagerModule.hpp"
// #include "Core/.hpp"
#include "Core/Base.hpp"

#include "UniformVarible.hpp"


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
    
   private:
};

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

   private:
    Vector<u32_t> m_indicies;
    Vector<float> m_positions;
    Vector<float> m_normals;
    Vector<float> m_textureCoords;
};

// Contains model
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

    virtual bool isTextured() const = 0;
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

     virtual i32_t findUniformLocation(const char* name) = 0;
     virtual Map<const char*, i32_t> findUniformLocationList(UniformList uniformList) = 0;

     // virtual void printUniformLocations() = 0;
     //
     // virtual void addUniform(UniformVarible<i32_t> uniform) = 0;
     // virtual void addUniform(UniformVarible<float> uniform) = 0;
     // virtual void addUniform(UniformVarible<u32_t> uniform) = 0;
     // virtual void addUniform(UniformVarible<Vec2> uniform) = 0;
     // virtual void addUniform(UniformVarible<Vec3> uniform) = 0;
     // virtual void addUniform(UniformVarible<Vec4> uniform) = 0;
     // virtual void addUniform(UniformVarible<Mat2> uniform) = 0;
     // virtual void addUniform(UniformVarible<Mat3> uniform) = 0;
     // virtual void addUniform(UniformVarible<Mat4> uniform) = 0;
     //
     //
     // virtual void addUniformsToLocList(UniformList uniforms) = 0;
     //
     // virtual void setUniformPtr(const UniformVarible<i32_t>& uniform) = 0;
     // virtual void setUniformPtr(const UniformVarible<float>& uniform) = 0;
     // virtual void setUniformPtr(const UniformVarible<u32_t>& uniform) = 0;
     // virtual void setUniformPtr(const UniformVarible<Mat4>& uniform) = 0;
     //
     // virtual UniformList getUniforms() const = 0;
     // virtual ForwardList<UniformLoc> getUniformLocs() const = 0;

    private:
};

}    // namespace Ellipse
