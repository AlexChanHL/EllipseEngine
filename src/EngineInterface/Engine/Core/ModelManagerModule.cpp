
#include "Renderer/UniformVarible.hpp"
#include "Renderer/RenderModule.hpp"
#include "Renderer/VerticiesData.hpp"
#include "ModelManagerModule.hpp"

namespace Ellipse
{

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
                RenderObj* renderObject,
                RenderShaderObj* shaderObject
               )
    : m_name{name},
      m_isInList{false},
      m_renderObject{std::move(renderObject)},
      m_shaderObject{std::move(shaderObject)}
    {

    }
    // ModelObject(const ModelObject& rhs)
    // : m_name{rhs.name()},
    //   m_isInList{false},
    //   m_renderObject{rhs.renderObject()},
    //   m_shaderObject{rhs.shaderObject()}
    // {
    //
    // }
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

    void setRenderObj(RenderObj* renderObj)
    {
    m_renderObject = renderObj;
    }

    void setShaderObj(RenderShaderObj* shaderObj)
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

    RenderObj* renderObject()
    {
    return m_renderObject;
    }
    RenderObj* renderObject() const
    {
    return m_renderObject;
    }

    RenderShaderObj* shaderObject()
    {
    return m_shaderObject;
    }

    RenderShaderObj* shaderObject() const
    {
    return m_shaderObject;
    }

   private:
    const char* m_name;
    bool m_isInList;
    RenderObj* m_renderObject;
    RenderShaderObj* m_shaderObject;
};

class ModelManagerModuleImpl : public ModelManagerModule
{
   public:
    ModelManagerModuleImpl(Engine& engine)
    : m_engine{engine},
      m_modelLastAddedCount{0},
      m_randomRemoveLast{int32_t(pow(10,2))}
    {
    setName("ModelModule");
    }
  
    ~ModelManagerModuleImpl()
    {

    }
 
    struct ModelNotSet
    {
       public:
        ModelNotSet(RenderObjData renderObjectData,
                    String vertex,
                    String fragment,
                    Mat4 model,
                    ModelID modelID,
                    UniformList uniformList,
                    const char* objectName
                   )
        : m_renderObjectData{renderObjectData},
          m_vertex{vertex},
          m_fragment{fragment},
          m_model{model},
          m_modelID{modelID},
          m_uniformList{uniformList},
          m_objectName{objectName}
        {

        }
        ~ModelNotSet()
        {

        }

        RenderObjData renderObjData() const
        {
        return m_renderObjectData;
        }

        String vertex() const
        {
        return m_vertex;
        }
        
        String fragment() const
        {
        return m_fragment;
        }

        Mat4 model() const
        {
        return m_model;
        }
      
        ModelID id() const
        {
        return m_modelID;
        }

        UniformList uniformList() const
        {
        return m_uniformList;
        }

        const char* objectName() const
        {
        return m_objectName;
        }

       private:
        RenderObjData m_renderObjectData;
        String m_vertex;
        String m_fragment;
        Mat4 m_model;
        ModelID m_modelID;
        UniformList m_uniformList;
        const char* m_objectName;
    };

    virtual void init() override
    {
    // m_modelWorldDrawOrder.initModelWorldDrawOrder();
    // m_layerTracker.initLayer();
    // m_modelWorlds.initLayer();
    // m_userWorlds.initLayer();
    }


    virtual void onUpdate() override
    {
    for(u64_t i=0;i<m_removeModels.size();i++)
    {
    removeModelId(m_removeModels[i]);
    }

    m_removeModels.clear();

    }

    virtual void importModel(String modelImportPath) override
    {
    // return m_modelImporter.importModel(modelImportPath);
      
    }

    virtual void addModel(ModelID& modelID,
                          const char* objectName,
                          Mat4 modelMat,
                          UniformList uniformList
                          ) override
    {
    ModelID idLocation{m_randomRemoveLast.chooseRandomVal()};

    modelID = idLocation;

    for(const ModelObject& object : m_objects)
    {
    if(strcmp(objectName, object.name()) == 0)
    {
    Model model = prepareModel(objectName);
    model.setId(modelID);
    model.setModel(modelMat);
    model.setUniformList(uniformList);


    m_models.push_back(model);
   
    m_models[m_models.size() - 1].uniformList().addUniform(UniformVarible<Mat4>{"model", &m_models[m_models.size() - 1].model()});

    RenderModule& renderModule = static_cast<RenderModule&>(m_engine.getModule("RenderModule"));
    m_models[m_models.size() - 1].uniformList().addUniform(UniformVarible<Mat4>{"proj", &renderModule.proj()});
    m_models[m_models.size() - 1].uniformList().addUniform(UniformVarible<Mat4>{"view", &renderModule.view()});

    m_models[m_models.size() - 1].uniformList().setUniformLocations(m_models[m_models.size() - 1].shaderObject()->findUniformLocationList(m_models[m_models.size() - 1].uniformList()));

    return;
    }
    }

    ELLIPSE_ENGINE_LOG_ERROR("Object not list");
    }

    virtual void addModelDefinition(const char* objectName,
                                    String vertexShader,
                                    String fragmentShader,
                                    RenderObjData renderObjData
                                   ) override
    {
    ModelObject object = prepareObject(objectName, 
                                       renderObjData,
                                       vertexShader,
                                       fragmentShader
                                      );
    m_objects.push_back(object);
    }

    virtual void removeModel(ModelID modelID) override
    {
    m_removeModels.push_back(modelID);
    }

    void removeModelId(ModelID id)
    {
    for(u64_t i=0;i<m_models.size();i++)
    {
    if(id == m_models[i].id())
    {
    m_models.erase(m_models.begin() + i);
    m_modelLastAddedCount--;
    }

    }

    }

    virtual u64_t findModelIndex(ModelID modelID) const override 
    {
    for(u64_t i=0;i<m_models.size();i++)
    {
    if(m_models[i].id() == modelID)
    {
    return i;
    }
    }

    ELLIPSE_ENGINE_LOG_ERROR("Could not find model, returning zero index");
   
    return 0;
    }

    virtual void setDifferentInViewspace(float viewspaceWidth,
                                         float viewspaceHeight,
                                         float originalWindowWidth,
                                         float originalWindowHeight) override;

    virtual VectorSharedIteratorHeap<Model>& models() override
    {
    return m_models;
    }

    SharedPtr<ModelManagerModule> createModelManagerModule();

   private:
    ModelObject prepareObject(const char* name, RenderObjData data, String vertexShader, String fragShader)
    {
    Renderer& renderer = static_cast<Renderer&>(m_engine.getSystem("Renderer"));

    ModelObject object;

    auto renderObj = renderer.createRenderObj(data);
    auto shaderObj = renderer.createShaderObj(vertexShader, fragShader);
    // shaderObj->getShaderSource();

    object.setName(name);
    object.setIsInList(true);
    object.setRenderObj(renderObj);
    object.setShaderObj(shaderObj);

    return object;
    }

    Model prepareModel(const char* objectName)
    {
    // ELLIPSE_ENGINE_LOG_INFO("shader object name: {}", objectName);
    Model model;

    for(u64_t j=0;j<m_objects.size();j++)
    {
    ModelObject& object = m_objects[j];
    if(strcmp(objectName, object.name()) == 0)
    {
    model.setRenderObj(m_objects[j].renderObject());
    model.setShaderObj(m_objects[j].shaderObject());
    }
    }
   
    return model;
    }

   private: 
    Engine& m_engine;

    Vector<ModelNotSet> m_modelsNotSet;

    VectorSharedIteratorHeap<Model> m_models;
    Vector<ModelObject> m_objects;

    u64_t m_modelLastAddedCount;

    Viewspace m_currentViewspace;

    Vector<ModelID> m_removeModels;

    EllipseMath::RandomRemoveLast m_randomRemoveLast;
    // CameraManager m_cameraManager;
};

void ModelManagerModuleImpl::setDifferentInViewspace(float viewspaceWidth,
                                                     float viewspaceHeight,
                                                     float originalWindowWidth,
                                                     float originalWindowHeight)
{
    // m_currentViewspace.m_width += (static_cast<float>(m_currentViewspace.m_width) / static_cast<float>(originalWindowWidth) ) * static_cast<float>(viewspaceWidth);
    //
    // m_currentViewspace.m_height += (static_cast<float>(m_currentViewspace.m_height) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceHeight);
    //
    // m_currentViewspace.m_posX += (static_cast<float>(m_currentViewspace.m_posX) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceWidth);
    //
    // m_currentViewspace.m_posY += (static_cast<float>(m_currentViewspace.m_posY) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceHeight);
    //
    //
    // // for(ModelLayer& modelLayer : m_modelLayers)
    // // {
    // // for(ModelViewspace& modelViewspace : modelLayer.m_modelViewspaces)
    // // {
    // // float viewspaceWindowWidthRatio = 
    // // static_cast<float>(modelViewspace.m_viewspace.m_width)
    // // / 
    // // static_cast<float>(originalWindowWidth);
    // //
    // // float viewspaceWindowHeightRatio = 
    // // static_cast<float>(modelViewspace.m_viewspace.m_height)
    // // / 
    // // static_cast<float>(originalWindowHeight);
    // //
    // // float viewspaceWindowPosXRatio = 
    // // static_cast<float>(modelViewspace.m_viewspace.m_posX)
    // // / 
    // // static_cast<float>(originalWindowWidth);
    // //
    // // float viewspaceWindowPosYRatio = 
    // // static_cast<float>(modelViewspace.m_viewspace.m_posY)
    // // / 
    // // static_cast<float>(originalWindowHeight);
    // //
    // // // [ This ratio solution is heavily hackish, need to find
    // // //   a better solution for resolving multiple viewspaces 
    // // //   adjust to the new window size ]
    // //
    // // float viewspaceRatioWidth = static_cast<float>(viewspaceWidth) * viewspaceWindowWidthRatio;
    // // float viewspaceRatioHeight = static_cast<float>(viewspaceHeight) * viewspaceWindowHeightRatio;
    // // float viewspaceRatioPosX = static_cast<float>(viewspaceWidth) * viewspaceWindowPosXRatio;
    // // float viewspaceRatioPosY = static_cast<float>(viewspaceHeight) * viewspaceWindowPosYRatio;
    // //
    // // // std::cout << "Window difference " <<  viewspaceWidth << '\n';
    // // // std::cout << "Window ratio " << viewspaceWindowWidthRatio << '\n';
    // //
    // // if(modelViewspace.m_viewspace.m_posX != 0 
    // //    || modelViewspace.m_viewspace.m_posY != 0)
    // // {
    // // modelViewspace.m_viewspace.m_posX += viewspaceRatioPosX;
    // // modelViewspace.m_viewspace.m_posY += viewspaceRatioPosY;
    // // }
    // //
    // // modelViewspace.m_viewspace.m_width += viewspaceRatioWidth;
    // // modelViewspace.m_viewspace.m_height += viewspaceRatioHeight;
    // // }
    // // }
}


SharedPtr<ModelManagerModule> ModelManagerModule::createModelManagerModule(Engine& engine)
{
    return createShared<ModelManagerModuleImpl>(engine);
}

}   // namespace Ellipse

