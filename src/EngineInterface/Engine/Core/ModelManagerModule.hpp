#pragma once

#include "Engine/Module.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/RenderObj.hpp"
#include "Renderer/UniformVarible.hpp"
#include "Core/Utils/VectorSharedIteratorHeap.hpp"
#include "Math/Random/Random.hpp"
#include "Math/TrigonometricUnits.hpp"
#include "Math/Matrix.hpp"
#include "Core/Base.hpp"


namespace Ellipse
{

struct Viewspace
{
   public:
    Viewspace(float posX,
              float posY,
              float width,
              float height)
     : m_posX{posX},
       m_posY{posY},
       m_width{width},
       m_height{height}
     {

     }
    Viewspace(i32_t posX,
              i32_t posY,
              i32_t width,
              i32_t height)
     : m_posX{static_cast<float>(posX)},
       m_posY{static_cast<float>(posY)},
       m_width{static_cast<float>(width)},
       m_height{static_cast<float>(height)}
    {

    }
    Viewspace()
    : m_posX{0},
      m_posY{0},
      m_width{0},
      m_height{0}
    {

    }
   
    Viewspace(const Viewspace& viewspace)
    : m_posX{viewspace.m_posX},
      m_posY{viewspace.m_posY},
      m_width{viewspace.m_width},
      m_height{viewspace.m_height}
    {

    }

    void operator=(const Viewspace& viewspace)
    {
    m_posX = viewspace.m_posX;
    m_posY = viewspace.m_posY;
    m_width = viewspace.m_width;
    m_height = viewspace.m_height;
    }

    bool operator==(Viewspace viewspace)
    {
    return m_posX == viewspace.m_posX
           && m_posY == viewspace.m_posY
           && m_width == viewspace.m_width 
           && m_height == viewspace.m_height;
    }
    bool operator!=(Viewspace viewspace)
    {
    return m_posX != viewspace.m_posX
           || m_posY != viewspace.m_posY
           || m_width != viewspace.m_width 
           || m_height != viewspace.m_height;
    }

   public:
    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
  
   private: 
};

struct RotateAmount
{
   public:
    float m_radians;
    Vec3 m_rotationAxis;
};

class ModelObject
{
   public:
    ModelObject()
    : m_name{nullptr},
      m_isInList{false},
      m_renderObject{nullptr},
      m_shaderObject{nullptr}
    {

    }
    ModelObject(const char* name,
                SharedPtr<RenderObj> renderObject,
                SharedPtr<RenderShaderObj> shaderObject
               )
    : m_name{name},
      m_isInList{false},
      m_renderObject{std::move(renderObject)},
      m_shaderObject{std::move(shaderObject)}
    {

    }
    ~ModelObject()
    {

    }

    void setName(const char* name)
    {
    m_name = name;
    }

    void setIsInList(bool isInList)
    {
    m_isInList = isInList;
    }

    void setRenderObj(SharedPtr<RenderObj> renderObj)
    {
    m_renderObject = renderObj;
    }

    void setShaderObj(SharedPtr<RenderShaderObj> shaderObj)
    {
    m_shaderObject = shaderObj;
    }

    const char* name() const
    {
    return m_name;
    }

    bool isInList() const
    {
    return m_isInList;
    }

    SharedPtr<RenderObj> renderObject()
    {
    return m_renderObject;
    }
    SharedPtr<RenderObj> renderObject() const
    {
    return m_renderObject;
    }

    SharedPtr<RenderShaderObj> shaderObject()
    {
    return m_shaderObject;
    }

    SharedPtr<RenderShaderObj> shaderObject() const
    {
    return m_shaderObject;
    }

   private:
    const char* m_name;
    bool m_isInList;
    SharedPtr<RenderObj> m_renderObject;
    SharedPtr<RenderShaderObj> m_shaderObject;
};

class Model
{
   public:
    Model()
    : m_model{Mat4{1.0f}},
      m_id{-1},
      m_uniformList{UniformList{}},
      m_renderObject{nullptr},
      m_shaderObject{nullptr}
    {

    }
    Model(Mat4 model,
          ModelID modelID,
          UniformList uniformList,
          SharedPtr<RenderObj> renderObject,
          SharedPtr<RenderShaderObj> shaderObject
         )
    : m_model{model},
      m_id{modelID},
      m_uniformList{uniformList},
      m_renderObject{renderObject},
      m_shaderObject{shaderObject}
    {

    }

    ~Model()
    {

    }

    void setModel(Mat4 model)
    {
    m_model = model;
    }

    void setId(ModelID id)
    {
    m_id = id;
    }

    void setRenderObj(SharedPtr<RenderObj> renderObj)
    {
    m_renderObject = renderObj;
    }

    void setShaderObj(SharedPtr<RenderShaderObj> shaderObj)
    {
    m_shaderObject = shaderObj;
    }

    void setUniformList(const UniformList& uniformList)
    {
    m_uniformList = uniformList;
    }

    Mat4& model()
    {
    return m_model;
    }

    ModelID id() const
    {
    return m_id;
    }

    UniformList& uniformList()
    {
    return m_uniformList;
    }

    UniformList uniformList() const
    {
    return m_uniformList;
    }

    SharedPtr<RenderObj> renderObject()
    {
    return m_renderObject;
    }

    SharedPtr<RenderObj> renderObject() const
    {
    return m_renderObject;
    }

    SharedPtr<RenderShaderObj> shaderObject()
    {
    return m_shaderObject;
    }

    SharedPtr<RenderShaderObj> shaderObject() const
    {
    return m_shaderObject;
    }

   private:
    Mat4 m_model;
    ModelID m_id;
    UniformList m_uniformList;
    SharedPtr<RenderObj> m_renderObject;
    SharedPtr<RenderShaderObj> m_shaderObject;
};

// class CameraManager
// {
//    public:
//     CameraManager()
//     {
//
//     }
//     ~CameraManager()
//     {
//
//     }
//
//
//     void addCamera(const char* name)
//     {
//     m_cameras.push_back(Camera{name});
//     }
//
//     void translateForward(u64_t index)
//     {
//     Camera camera = m_cameras[index];
//
//     m_cameras[index].setPosition(camera.position() + (camera.front() * camera.cameraSpeed()));
//     }
//     
//     void translateBackward(u64_t index)
//     {
//     Camera camera = m_cameras[index];
//
//     m_cameras[index].setPosition(camera.position() - (camera.front() * camera.cameraSpeed()));
//     
//     }
//     void translateLeft(u64_t index)
//     {
//     Camera camera = m_cameras[index];
//
//     m_cameras[index].setPosition(camera.position() - (EllipseMath::cross(camera.front(), camera.upDirection()) * camera.cameraSpeed()));
//     
//     }
//     void translateRight(u64_t index)
//     {
//     Camera camera = m_cameras[index];
//
//     m_cameras[index].setPosition(camera.position() + (EllipseMath::cross(camera.front(), camera.upDirection()) * camera.cameraSpeed()));
//     
//     }
//
//     void registerMouseUpdate(Pair<float, float> mouseOffsets)
//     {
//     for(u32_t i = 0; i < m_cameras.size(); i++)
//     {
//     m_cameras[i].setCameraYawValues(mouseOffsets);
//     m_cameras[i].setCameraFront();
//     }
//
//     }
//
//     void setFronts()
//     {
//     // for(u32_t i = 0; i < m_cameras.size(); i++)
//     // {
//     // m_cameras[i].setFront(m_cameras[i].position() + Vec3{4.0f, 0.0f, 0.0f});
//     // }
//     }
//
//     void setCameraPosition(u64_t index,
//                            Vec3 position)
//     {
//     m_cameras[index].setPosition(position);
//     }
//
//     Vec3 front(u64_t index) const
//     {
//     return m_cameras[index].front();
//     }
//
//     Camera findCamera(const char* cameraName) const
//     {
//     for(u32_t i = 0; i < m_cameras.size(); i++)
//     {
//     if(strcmp(cameraName, m_cameras[i].name()) == 0)
//     {
//     return m_cameras[i];
//     }
//     }
//
//     ELLIPSE_ENGINE_LOG_WARN("Camera not in list, returning invaild camara");
//
//     return Camera{};
//
//     }
//
//     u64_t findCameraIndex(const char* cameraName) const
//     {
//     for(u64_t i = 0; i < m_cameras.size(); i++)
//     {
//     if(strcmp(cameraName, m_cameras[i].name()) == 0)
//     {
//     return i;
//     }
//     }
//
//     ELLIPSE_ENGINE_LOG_WARN("Camera not in list, returning cameras size");
//
//     return m_cameras.size();
//
//     }
//
//     Camera& cameraIndex(u64_t index)
//     {
//     return m_cameras[index];
//     }
//
//    private:
//     Vector<Camera> m_cameras;
// };


class ModelManagerModule : public IModule
{
   public:
    ModelManagerModule()
    {

    }
    ~ModelManagerModule()
    {

    }

    virtual void init() override = 0;
    virtual void onUpdate() override = 0;

    virtual void addModel(ModelID& modelID,
                          const char* objectName,
                          Mat4 model,
                          UniformList uniformList
                          ) = 0;

    virtual void addModelDefinition(const char* objectName,
                                    String vertexShader,
                                    String fragmentShader,
                                    RenderObjData renderObjData
                                    ) = 0;

    virtual void removeModel(ModelID modelID) = 0;

    virtual u64_t findModelIndex(ModelID modelID) const = 0;
    virtual i64_t findObjectIndex(const char* name) const = 0;

    virtual void setDifferentInViewspace(float viewspaceWidth,
                                         float viewspaceHeight,
                                         float originalWindowWidth,
                                         float originalWindowHeight) = 0;
    
    // CREATE_FUNC_CALLBACK_INTERFACE(addModel, void(ModelID& modelID,
    //                                               const char* modelName,
    //                                               const char* objectName,
    //                                               String vertexShader,
    //                                               String fragmentShader,
    //                                               String importPath,
    //                                               UniformList uniformList))
    // CREATE_FUNC_CALLBACK_INTERFACE(removeModel, void(ModelID modelID))
    // CREATE_FUNC_CALLBACK_INTERFACE(translateModel, void(ModelID modelID, Vec3 translationAmount))
    // CREATE_FUNC_CALLBACK_INTERFACE(rotateModel, void(ModelID modelID, float radians, Vec3 rotationAxis))
    // CREATE_FUNC_CALLBACK_INTERFACE(scaleModel, void(ModelID modelID, Vec3 scalarAmount))

    // virtual CameraManager& cameraManager() = 0;

    virtual VectorSharedIteratorHeap<Model>& models() = 0;
    virtual Vector<ModelObject>& objects() = 0;

    static SharedPtr<ModelManagerModule> createModelManagerModule(Engine& engine);

   public:

   protected:
    virtual void importModel(String modelImportPath) = 0;
};

}   // namespace Ellipse
