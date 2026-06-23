#pragma once

#include "Core/Base.hpp"
#include "Core/Utils/FileHelper.hpp"
#include "Math/Random/Random.hpp"
#include "UniformVarible.hpp"
#include "Camera.hpp"

#include <vips/vips8>
#include <stb_image.h>
#include <fmt/format.h>

#define ELLIPSE_ALL_TEXTURE_EXT "jpeg", "jpg", "png"


namespace Ellipse {
 struct Texture {
    public:
     Texture()
     : m_id{0} {
     }
     ~Texture() {
     }

     u32_t id() const { return m_id; }
     u32_t& id() { return m_id; }
 
    private:
     u32_t m_id;
 };
 
 class RenderMesh {
    public:
     RenderMesh() {
     }
     virtual ~RenderMesh() {
     }
 
     virtual u32_t vao() const = 0;
     virtual Vector<float> positions() const = 0;
     virtual Vector<float> normals() const = 0;
     virtual Vector<float> textureCoords() const = 0;
     virtual Vector<u32_t> indicies() const = 0;
     virtual Vector<Texture> textures() const = 0;
 
     bool isTextured() const { return textures().size() > 0; }
    private:
 };
 
 inline bool isTextureExt(String ext) {
     Vector<String> textureExts = {ELLIPSE_ALL_TEXTURE_EXT};
     for(u64_t i=0;i<textureExts.size();i++) {
      if(ext == textureExts[i]) {
       return true;
      }
     }
 
     return false;
 }
 
 class TextureData {
    public:
     TextureData()
     : m_width{0},
       m_height{0},
       m_clrChannels{0},
       m_fileName{},
       m_ext{},
       m_data{nullptr} {
     }
     TextureData(i32_t width, i32_t height, i32_t clrChannels, String path, unsigned char* data)
     : m_width{width},
       m_height{height},
       m_clrChannels{clrChannels},
       m_fileName{},
       m_ext{},
       m_data{data} {
      String file = Utils::getFile(path);
      m_ext = Utils::getExt(file);
      m_fileName = Utils::getFileName(file);
      if(!isTextureExt(m_ext)) {
       ELLIPSE_ENGINE_LOG_WARN("Unknown texture extenstion");
       m_ext = "unknown";
      }
 
     }
     ~TextureData() {
     }
     TextureData(const TextureData& textureData)
     : m_width{textureData.m_width},
       m_height{textureData.m_height},
       m_clrChannels{textureData.m_clrChannels},
       m_fileName{textureData.m_fileName},
       m_ext{textureData.m_ext},
       m_data{textureData.m_data} {
     }
     void operator=(const TextureData& textureData) {
         m_width = textureData.m_width;
         m_height = textureData.m_height;
         m_clrChannels = textureData.m_clrChannels;
         m_fileName = textureData.m_fileName;
         m_ext = textureData.m_ext;
         m_data = textureData.m_data;
     }
 
    public:
     String m_path;
     i32_t m_width;
     i32_t m_height;
     i32_t m_clrChannels;
     String m_fileName;
     String m_ext;
     unsigned char* m_data;
    private:
 };
 
 inline TextureData loadTexture(String path, bool flipTexture) { 
     stbi_set_flip_vertically_on_load(flipTexture);
     i32_t width = 0; 
     i32_t height = 0; 
     i32_t clrChannels = 0; 
     unsigned char* data = stbi_load(path.c_str(), &width, &height, &clrChannels, 0);
     if(!data) {
      ELLIPSE_ENGINE_LOG_WARN("Error creating texture data");
     }
 
     return TextureData(width, height, clrChannels, path, data);
 }
 
 inline void freeTexture(TextureData& texture) {
     stbi_image_free(texture.m_data);
 }
 
 inline String convertTextureToPower2(TextureData& texture) {
     vips::VImage input = vips::VImage::new_from_memory(texture.m_data,
      static_cast<u64_t>(texture.m_width * texture.m_height * texture.m_clrChannels),
      texture.m_width,
      texture.m_height,
      texture.m_clrChannels,
      VIPS_FORMAT_UCHAR
     );
 
     double nearestPower2 = 0;
     for(double i=0;i<32;i++) {
      if(input.width() <= pow(2, i)) {
       double comp = pow(2, i);
       double compPrev = pow(2, i-1);
 
       double differenceNow = abs(comp - input.width());
       double differencePrev = abs(compPrev - input.width());
 
       if(differenceNow > differencePrev) {
        nearestPower2 = i - 1;
       }
       if(differenceNow < differencePrev) {
        nearestPower2 = i;
       }
       if(differenceNow == differencePrev) {
        i32_t flip = EllipseMath::randIntDist(0, 1);
        flip == 0 ? nearestPower2 = i : nearestPower2 = i - 1;
       }
 
       break;
      }
     }
 
     double scaleFactor = pow(2, nearestPower2) / input.width();
     input = input.resize(scaleFactor);
     // ELLIPSE_ENGINE_LOG_INFO("{}", input.width());
     // ELLIPSE_ENGINE_LOG_INFO(fmt::format("{}", texture.m_ext));
     String resizedFilePath = fmt::format("Assets/Application/{}.{}", texture.m_fileName, texture.m_ext);
     // ELLIPSE_ENGINE_LOG_INFO("{}", resizedFilePath);
     input.write_to_file(resizedFilePath.c_str());
 
     return resizedFilePath;
 }
 
 class RenderObjData
 {
    public:
     RenderObjData() {
     }
     RenderObjData(Vector<u32_t> indicies, Vector<float> positions, Vector<float> normals, Vector<float> textureCoords)
     : m_indicies{indicies},
       m_positions{positions},
       m_normals{normals},
       m_textureCoords{textureCoords} {
 
     }
     ~RenderObjData() {
     }
 
     void setIndicies(Vector<u32_t> indicies) {
      m_indicies = indicies;
     }
     void setPositions(Vector<float> positions) {
      m_positions = positions;
     }
     void setNormals(Vector<float> normals) {
      m_normals = normals;
     }
     void setTexCoords(Vector<float> textureCoords) {
      m_textureCoords = textureCoords;
     }
 
     Vector<u32_t> indicies() {
      return m_indicies;
     }
     Vector<float> positions() {
      return m_positions;
     }
     Vector<float> normals() {
      return m_normals;
     }
     Vector<float> textureCoords() {
      return m_textureCoords;
     }
     TextureData& textureData() {
      return m_textureData;
     }
 
    private:
     Vector<u32_t> m_indicies;
     Vector<float> m_positions;
     Vector<float> m_normals;
     Vector<float> m_textureCoords;
     TextureData m_textureData;
 };
 
 // Use a single model data
 class ModelData {
     public:
      ModelData() {
      }
      virtual ~ModelData() = default;
 
      virtual void translate(EllipseMath::Vec3) = 0;
      virtual void rotate(float) = 0;
      virtual void rotate(float, EllipseMath::Vec3) = 0;
      virtual void scale(EllipseMath::Vec3) = 0;

      virtual EllipseMath::Vec3 translate() = 0;
      virtual EllipseMath::Vec3 rotateAxis() = 0;
      virtual float rotateAngle() = 0;
      virtual EllipseMath::Vec3 scale() = 0;
 
      virtual SharedPtr<EllipseMath::Mat4> model() = 0;
     public:
 };

 class ModelData2D : public ModelData {
     public:
      ModelData2D(Camera& camera)
      : m_translate{EllipseMath::Vec3{0.0f}},
        m_rotateAxis{EllipseMath::Vec3{1.0f}},
        m_rotateAngle{0.0f},
        m_scale{EllipseMath::Vec3{1.0f}},
        m_camera{camera},
        m_model{createShared<EllipseMath::Mat4>(1.0f)} {
      
      }
      ~ModelData2D() = default;

      virtual void translate(EllipseMath::Vec3 vec) override {
       m_translate = vec;
      }
      virtual void rotate(float angle, EllipseMath::Vec3 axis) override {
       m_rotateAngle = angle;
       m_rotateAxis = axis;
      }
      virtual void rotate(float angle) override {
       m_rotateAngle = angle;
      }
      virtual void scale(EllipseMath::Vec3 scale) override {
       m_scale = scale;
      }

      virtual EllipseMath::Vec3 translate() override { return m_translate; }
      virtual EllipseMath::Vec3 rotateAxis() override { return m_rotateAxis; }
      virtual float rotateAngle() override { return m_rotateAngle; }
      virtual EllipseMath::Vec3 scale() override { return m_scale; }
      virtual SharedPtr<EllipseMath::Mat4> model() override { return m_model; }

     public:
      EllipseMath::Vec3 m_translate;
      EllipseMath::Vec3 m_rotateAxis;
      float m_rotateAngle;
      EllipseMath::Vec3 m_scale;
      Camera& m_camera;
      SharedPtr<EllipseMath::Mat4> m_model;
 };

 class ModelData3D : public ModelData {
     public:
      ModelData3D()
      : m_translate{EllipseMath::Vec3{0.0f}},
        m_rotateAxis{EllipseMath::Vec3{1.0f}},
        m_rotateAngle{0.0f},
        m_scale{EllipseMath::Vec3{1.0f}},
        m_model{createShared<EllipseMath::Mat4>(1.0f)} {
      
      }
      ~ModelData3D() = default;

      virtual void translate(EllipseMath::Vec3 vec) override {
       m_translate = vec;
      }
      virtual void rotate(float angle, EllipseMath::Vec3 axis) override {
       m_rotateAngle = angle;
       m_rotateAxis = axis;
      }
      virtual void rotate(float angle) override {
       m_rotateAngle = angle;
      }
      virtual void scale(EllipseMath::Vec3 scale) override {
       m_scale = scale;
      }
      virtual SharedPtr<EllipseMath::Mat4> model() override { return m_model; }

      virtual EllipseMath::Vec3 translate() override { return m_translate; }
      virtual EllipseMath::Vec3 rotateAxis() override { return m_rotateAxis; }
      virtual float rotateAngle() override { return m_rotateAngle; }
      virtual EllipseMath::Vec3 scale() override { return m_scale; }

     public:
      EllipseMath::Vec3 m_translate;
      EllipseMath::Vec3 m_rotateAxis;
      float m_rotateAngle;
      EllipseMath::Vec3 m_scale;
      SharedPtr<EllipseMath::Mat4> m_model;
 };
 
 using PreDefinedObjects = Map<String, RenderObjData>;
 
 struct RenderObj
 {
    public:
     RenderObj() {
 
     }
     virtual ~RenderObj() {
 
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
   
      template<typename T>
      void addUniform(const UniformVariable<T>& t) {
       m_uniformList.addUniform(t);
       m_uniformList.setUniformLocation(t.name(), findUniformLocation(t.name()));
      }
 
      UniformList uniformList() {
       return m_uniformList;
      }
 
     protected:
      UniformList m_uniformList;
 
     private:
 };
 
}    // namespace Ellipse
