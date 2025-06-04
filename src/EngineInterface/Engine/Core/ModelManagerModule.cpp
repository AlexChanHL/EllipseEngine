
#include "Renderer/UniformVarible.hpp"
#include "Renderer/RenderModule.hpp"
#include "Renderer/VerticiesData.hpp"
#include "ModelManagerModule.hpp"

namespace Ellipse
{

    // Render
    // +=======+==================+=============+
    // | 1     | 2                | 1           |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // | 0 | 1 | 2 | 3 | 4 | 5 |  | 6 | 7 | 8 | |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // 
    // Render remove World 2, first model
    // +=======+==================+=============+
    // | 1     | 2                | 1           |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // | 0 | 1 | 2 | 3 | 4 | 5 |  | 6 | 7 | 8 | |
    // +===+===+===+===+===+===+==+===+===+===+=+
    //
    //                    |
    //                   \|/
    //
    // +=======+==================+=============+
    // | 1     | 2                | 1           |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // | 0 | 1 | 2 | 3 | 4 |   |  | 5 | 6 | 7 | |
    // +===+===+===+===+===+===+==+===+===+===+=+
      


    // User world 1
    // +===+===+===+
    // | 1 | 3 |   |
    // +===+===+===+
      
    // User world 2
    // +===+===+===+
    // | 1 | 2 | 3 |
    // +===+===+===+
      
    // 1
    // +===+===+===+
    // | 1 | 3 |   |
    // +===+===+===+
    // | 0 | 1 |   |
    // +===+===+===+
      
    // 2
    // +===+===+===+
    // | 1 | 3 | 2 |
    // +===+===+===+
    // | 0 | 1 | 2 |
    // +===+===+===+

class ModelObject
{
   public:
    // ModelObject()
    // : m_objectName{nullptr},
    //   m_renderObject{nullptr},
    //   m_shaderObject{nullptr}
    // {
    //
    // }
    //
    ModelObject(const char* objectName,
                UniquePtr<RenderObj> renderObject,
                UniquePtr<RenderShaderObj> shaderObject
               )
    : m_objectName{objectName},
      m_isInList{false},
      // m_renderObject{std::move(renderObject)},
      // m_shaderObject{std::move(shaderObject)}
      m_renderObject{nullptr},
      m_shaderObject{nullptr}
    {

    }

    ~ModelObject()
    {

    }

    ModelObject(const ModelObject& rhs)
    : m_objectName{rhs.name()},
      m_isInList{false},
      m_renderObject{nullptr},
      m_shaderObject{nullptr}
    {

    }

    void setIsInList(bool isInList)
    {
    m_isInList = isInList;
    }

    // void setRenderObj(UniquePtr<RenderObj> renderObj)
    // {
    // m_renderObject = std::move(renderObj);
    // }
    //
    // void setShaderObj(UniquePtr<RenderShaderObj> shaderObj)
    // {
    // m_shaderObject = std::move(shaderObj);
    // }

    void setRenderObj(UniquePtr<RenderObj> renderObj)
    {
    m_renderObject = std::move(renderObj);
    }

    void setShaderObj(UniquePtr<RenderShaderObj> shaderObj)
    {
    m_shaderObject = std::move(shaderObj);
    }

    const char* name() const
    {
    return m_objectName;
    }

    bool isInList() const
    {
    return m_isInList;
    }

    UniquePtr<RenderObj>& renderObject()
    {
    return m_renderObject;
    }

    // UniquePtr<RenderObj> renderObject() const
    // {
    // return m_renderObject;
    // }

    UniquePtr<RenderShaderObj>& shaderObject()
    {
    return m_shaderObject;
    }

    // UniquePtr<RenderShaderObj> shaderObject() const
    // {
    // return m_shaderObject;
    // }

   private:
    const char* m_objectName;
    bool m_isInList;
    UniquePtr<RenderObj> m_renderObject;
    UniquePtr<RenderShaderObj> m_shaderObject;
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


    // [ Updating the next layer is using after
    //   update call ]

    virtual void onUpdate() override
    {
    // m_cameraManager.setFronts();
    //
    Renderer& renderer = static_cast<Renderer&>(m_engine.getSystem("Renderer"));


    for(u64_t i=0;i<m_modelsNotSet.size();i++)
    {
    u64_t index = m_modelLastAddedCount + i;
    ModelNotSet model = m_modelsNotSet[i];

    // ELLIPSE_ENGINE_LOG_INFO("index: {}", index);

    for(u64_t j=0;j<m_objects.size();j++)
    {
    ModelObject& object = m_objects[j];
    if(strcmp(model.objectName(), object.name()) == 0)
    {
    if(object.isInList())
    {
    m_models[index].setRenderObj(m_objects[j].renderObject().get());
    m_models[index].setShaderObj(m_objects[j].shaderObject().get());
    }
    if(!object.isInList())
    {
    auto renderObj = renderer.createRenderObj(model.renderObjData());
    auto shaderObj = renderer.createShaderObj(model.vertex(), model.fragment());

    m_objects[j].setIsInList(true);
    m_objects[j].setRenderObj(std::move(renderObj));
    m_objects[j].setShaderObj(std::move(shaderObj));

    m_models[index].setRenderObj(m_objects[j].renderObject().get());
    m_models[index].setShaderObj(m_objects[j].shaderObject().get());
    }

    }

    }


    if(m_models[index].renderObject() != nullptr)
    {
    // ELLIPSE_ENGINE_LOG_INFO("{}", index);
    }
        
    m_models[index].uniformList().addUniform(UniformVarible<Mat4>{"model", &m_models[index].model()});

    RenderModule& renderModule = static_cast<RenderModule&>(m_engine.getModule("RenderModule"));
    m_models[index].uniformList().addUniform(UniformVarible<Mat4>{"proj", &renderModule.proj()});
    m_models[index].uniformList().addUniform(UniformVarible<Mat4>{"view", &renderModule.view()});

    // m_models[index].uniformList().setUniformLocations(shaderObj->findUniformLocationList(m_models[index].uniformList()));
    m_models[index].uniformList().setUniformLocations(m_models[index].shaderObject()->findUniformLocationList(m_models[index].uniformList()));
    }

    m_modelLastAddedCount = m_modelLastAddedCount + m_modelsNotSet.size();
    m_modelsNotSet.clear();


    for(u64_t i=0;i<m_removeModels.size();i++)
    {
    removeModelId(m_removeModels[i]);
    }

    m_removeModels.clear();

    }

    virtual void importModel(String modelImportPath) override
    // virtual ModelData importModel(String modelImportPath) override
    {
    // return m_modelImporter.importModel(modelImportPath);
      
    }

    virtual void addModel(ModelID& modelID,
                          const char* objectName,
                          Mat4 model,
                          UniformList uniformList
                          ) override
    {
    ModelID idLocation{m_randomRemoveLast.chooseRandomVal()};

    modelID = idLocation;

    for(const ModelObject& object : m_objects)
    {
    if(strcmp(objectName, object.name()) == 0)
    {
    m_modelsNotSet.push_back(ModelNotSet{RenderObjData{},
                                         "",
                                         "",
                                         model,
                                         idLocation,
                                         uniformList,
                                         objectName
                                        }
                             );

    m_models.pushBack(Model{model,
                            idLocation,
                            uniformList,
                            nullptr,
                            nullptr
                           }
                      );

    return;
    }
    }

    ELLIPSE_ENGINE_LOG_ERROR("Object not list");
    }

    virtual void addModel(ModelID& modelID,
                          const char* objectName,
                          Mat4 model,
                          String vertexShader,
                          String fragmentShader,
                          String importPath,
                          UniformList uniformList
                          ) override
    {
    ModelID idLocation{m_randomRemoveLast.chooseRandomVal()};
    
    modelID = idLocation;

    // for(const ModelObject& object : m_objects)
    // {
    // if(strcmp(objectName, object.name()) == 0)
    // {
    // m_modelsNotSet.push_back(ModelNotSet{RenderObjData{},
    //                                      "",
    //                                      "",
    //                                      model,
    //                                      idLocation,
    //                                      uniformList,
    //                                      objectName
    //                                     }
    //                          );
    //
    // m_models.pushBack(Model{model,
    //                         idLocation,
    //                         uniformList,
    //                         nullptr,
    //                         nullptr
    //                        }
    //                   );
    //
    // return;
    // }
    // }

    // importModel(importPath);
    RenderObjData renderObjectData;
      
    m_modelsNotSet.push_back(ModelNotSet{renderObjectData,
                                         vertexShader,
                                         fragmentShader,
                                         model,
                                         idLocation,
                                         uniformList,
                                         objectName
                                        }
                            );
     
    m_models.pushBack(Model{model,
                            idLocation,
                            uniformList,
                            nullptr,
                            nullptr
                           }
       
                     );

    m_objects.push_back(ModelObject{objectName,
                                    nullptr,
                                    nullptr
                                   }
                       );
    
    }

    // [ Remove model is broken and sometimes removed models
    //   function but the user worlds does not update the 
    //   new world and won't show on queryUserWorld ]
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

    ELLIPSE_ENGINE_LOG_ERROR("Could not find model, returning index");
   
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
    // virtual void onUpdateModelMatrices() override
    // {
    // // for(u64_t i = 0; i < m_modelModuleModels.size(); i++)
    // // {
    // // if(m_modelModuleModels[i].isModified())
    // // {
    // // m_modelModuleModels[i].resetModelMatrix();
    // //       
    // // translateModelInModelList(m_modelModuleModels[i].model(), m_modelModuleModels[i].translationAmount());
    // // rotateModelInModelList(m_modelModuleModels[i].model(), m_modelModuleModels[i].rotationAmount().m_radians, m_modelModuleModels[i].rotationAmount().m_rotationAxis);
    // // scaleModelInModelList(m_modelModuleModels[i].model(), m_modelModuleModels[i].scalarAmount());
    // //
    // // // Math::printMat(m_modelModuleModels[i].model());
    // //
    // //
    // // m_modelModuleModels[i].setIsModified(false);
    // // }
    // // }
    // // 
    // }

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

