
#include "Core/Base.hpp"
#include "Renderer.hpp"
#include "Draw2D.hpp"
#include "RenderModule.hpp"
#include "Math/Matrix.hpp"
#include "Math/TrigonometricUnits.hpp"

namespace Ellipse
{

class RenderModuleImpl final : public RenderModule
{
    public:
     RenderModuleImpl(Engine& engine);
     ~RenderModuleImpl();

     struct RenderObject
     {
        public:
         RenderObject()
         {

         }
         RenderObject(ObjectID objectID,
                      SharedPtr<RenderObj> renderObj,
                      SharedPtr<RenderShaderObj> shaderObj)
         : m_objectID{objectID},
           m_renderObj{renderObj},
           m_shaderObj{shaderObj}
         {

         }
         ~RenderObject()
         {

         }


         SharedPtr<RenderObj>& renderObj()
         {
         return m_renderObj;
         }

         SharedPtr<RenderShaderObj>& shaderObj()
         {
         return m_shaderObj;
         }

         ObjectID objectID() const
         {
         return m_objectID;
         }

        private:
         ObjectID m_objectID;
         SharedPtr<RenderObj> m_renderObj;
         SharedPtr<RenderShaderObj> m_shaderObj;
     };

     struct RenderModel
     {
        public:
         RenderModel()
         {

         }
         RenderModel(ModelID modelID,
                     ObjectID objectID,
                     UniformList uniforms,
                     Mat4* model)
         : m_modelID{modelID},
           m_objectID{objectID},
           m_uniforms{uniforms},
           m_model{model}
         {

         }
         ~RenderModel()
         {

         }


         ObjectID objectID() const
         {
         return m_objectID;
         }
         UniformList uniformList() const
         {
         return m_uniforms;
         }

        private:
         ModelID m_modelID;
         ObjectID m_objectID;
         UniformList m_uniforms;
         time_t m_timeAdded;
         Mat4* m_model;
     };


     virtual void initLayerModule() override;
     virtual void onUpdateLayer() override;

     RenderModel createRenderModel(ModelID modelID,
                                   ObjectID objectID,
                                   UniformList uniforms,
                                   Mat4* model);
    
     RenderObject createObject(String vShader,
                               String fShader,
                               ModelData modelData);

     void addRenderModuleUniform(UniformList& uniforms)
     {
     uniforms.addUniform(UniformVarible<Mat4>{"view", &m_view});
     uniforms.addUniform(UniformVarible<Mat4>{"proj", &m_proj});
     
     }

     // RenderObject createObject(String vShader,
     //                           String fShader,
     //                           String importPath);

    // RenderObject createObject(ModelID modelID,
                                 // String vShader,
                                 // String fShader,
                                 // String importPath,
                                 // UniformList uniforms,
                                 // Mat4* model) = 0;

     // virtual Model create2DShape(const char* name, uLong_t size) override;


     virtual void setViewCamera(Camera camera) override;

     virtual void setCameraUp(float amount) override; 
     virtual void setCameraDown(float amount) override;
     virtual void setCameraRight(float amount) override;
     virtual void setCameraLeft(float amount) override;
     virtual void updateCamera() override;
     // virtual void translateModel(Model& model, Vec3 pos) override;

     virtual void setViewport(Viewspace viewspace) override;
     virtual void setClearColor(Vec4 col) override;

     String name() override;
     void setName(const char* name) override;

    protected:
     virtual void configureCameras() override
     {

     }

    private:
     class QueryModel
     {
        public:
         QueryModel()
         : m_isInList{false},
           m_index{0}
         {

         }
         QueryModel(u32_t index)
         : m_isInList{true},
           m_index{index}
         {

         }
         QueryModel(bool isInList, u32_t index)
         : m_isInList{isInList},
           m_index{index}
         {

         }
         ~QueryModel()
         {

         }

         bool isInList() const
         {
         return m_isInList;
         }

         u32_t index() const
         {
         return m_index;
         }

        public:
         bool m_isInList;
         u32_t m_index;
     };

     class ObjectPile
     {
        public:
         ObjectPile()
         {

         }
         ~ObjectPile()
         {

         }

         void addObject(const RenderObject& renderObject)
         {
         m_objects.push_back(renderObject);
         }

         RenderObject search(ObjectID objectID)
         {
         for(u32_t i = 0; i < m_objects.size(); i++)
         {
         if(m_objects[i].objectID() == objectID)
         {
         return m_objects[i];
         }
         }


         ELLIPSE_ENGINE_LOG_INFO("Couldn't find model");
          
         return m_objects[0];
         }

         QueryModel findIndex(ObjectID objectID)
         {
         for(u32_t i = 0; i < m_objects.size(); i++)
         {
         if(m_objects[i].objectID() == objectID)
         {
         return QueryModel{true, i};
         }
         }

         
         ELLIPSE_ENGINE_LOG_INFO("Couldn't find model");
          
         return QueryModel{false, 0};
         }


         RenderObject& objectFromindex(u32_t index)
         {
         return m_objects[index];
         }

         Vector<RenderObject>& objects()
         {
         return m_objects;
         }

         RenderObject& lastAddedObject()
         {
         return m_objects[m_objects.size() - 1];
         }

        private:
         Vector<RenderObject> m_objects;
     };


     void renderModel(const RenderModel& model);

     void removeModelsToBeRemovedModels()
     {
     for(u32_t i = 0; i < m_modelManager.modelsToBeRemovedIndicies().size(); i++)
     {
     m_renderModels.erase(m_renderModels.begin() + m_modelManager.modelsToBeRemovedIndicies()[i]);
     }

     }

     QueryModel findObject(ObjectID objectID)
     {
     return QueryModel{false, 0};
     }

     void renderModels();

     void updateViewspaces()
     {
     // auto modelViewspacesIterator = m_modelManager.previousModelLayersIterator()->m_modelViewspaces.begin();
     // for(RenderViewspace& renderViewspace : m_renderLayerIterator->m_renderViewspaces)
     // {
     // renderViewspace.m_viewspace = modelViewspacesIterator->m_viewspace;
     // modelViewspacesIterator++;
     // }
     }

    private:
     ModelManagerModule& m_modelManager;
     Renderer& m_renderer;
     ObjectPile m_objectPile;
     Vector<RenderModel> m_renderModels;
     Vector<RenderModel> m_userWorldRenderModels;

     // [ Model manager will be NoModule if ModelManager is initalized after RenderModule's onInit() ]
     Draw2D m_draw2D;

     EllipseMath::RandomRemoveLast m_objectIDGenerator;
    
     // Vector<Camera> m_cameras;
     // Camera m_camera;
     Mat4 m_view;
     Mat4 m_proj;
};

// [ Resizing window makes smaller shapes ]

RenderModuleImpl::RenderModuleImpl(Engine& engine)
: m_modelManager{static_cast<ModelManagerModule&>(engine.getLayerModule("ModelManagerLayerModule"))},
  m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))},
  m_objectIDGenerator{i32_t(pow(10,3))}
{
   setName("RenderModule");

   // [ Remove this ]
   setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});

   m_view = Mat4(1.0f);

   // m_view = EllipseMath::lookAt(m_camera.m_camPos,
   //                              m_camera.m_camPos + m_camera.m_camFront,
   //                              m_camera.m_camUp
   //                              );

   m_view = Mat4{1.0f};

   m_proj = Mat4{1.0f};

   i32_t winWidth = m_renderer.getWindowFrameSize().first;
   i32_t winHeight = m_renderer.getWindowFrameSize().second;


   float aspectRatio = float(winWidth) / float(winHeight);


   //                              aspectRatio,
   // [ Maybe should set to aspect ratio ]
   // m_proj = EllipseMath::ortho(-1.0f,
   //                              1.0f,
   //                             -1.0f,
   //                              1.0f,
   //                              0.1f,
   //                              100.0f
   //                            );

   m_proj = EllipseMath::perspective(EllipseMath::Radian(45.0f).radians(),
                                     aspectRatio,
                                     0.1f,
                                     100.0f
                                    );
}

RenderModuleImpl::~RenderModuleImpl()
{

}

String RenderModuleImpl::name()
{
   return m_name;
}
void RenderModuleImpl::setName(const char* name)
{
   m_name = name;
}

void RenderModuleImpl::initLayerModule()
{

}

void RenderModuleImpl::onUpdateLayer()
{
    for(u64_t i=0;i<m_modelManager.modelAddCollection().size();i++)
    {
    for(u64_t j=0;j<m_modelManager.modelAddCollection()[i].models().size();j++)
    {
    if(m_modelManager.modelAddCollection()[i].models()[j].isUsingObjectID())
    {
    QueryModel queryModel = m_objectPile.findIndex(m_modelManager.modelAddCollection()[i].models()[j].objectID());
    if(queryModel.isInList())
    {
    // [ To add models with same uniform variables configure by the user they must specify what
    //   value and add it ]
    m_renderModels.push_back(createRenderModel(m_modelManager.modelAddCollection()[i].models()[j].modelID(),
                                              m_modelManager.modelAddCollection()[i].models()[j].objectID(),
                                              m_modelManager.modelAddCollection()[i].models()[j].uniformList(),
                                              &m_modelManager.modelAddCollection()[i].models()[j].model()
                                             )
                           );

    // addRenderModuleUniform(m_modelManager.modelAddCollection()[i].models()[j].uniforms());
    }
    if(!queryModel.isInList())
    {
    ELLIPSE_ENGINE_LOG_WARN("Couldn't find using object id, did not add model");
    }
    }

    if(!m_modelManager.modelAddCollection()[i].models()[j].isUsingObjectID())
    {
    m_objectPile.addObject(
    createObject(
    m_modelManager.modelAddCollection()[i].models()[j].vertexShader(),
    m_modelManager.modelAddCollection()[i].models()[j].fragmentShader(),
    m_modelManager.modelAddCollection()[i].models()[j].modelData()
               )
                       );


    // m_modelManager.notify(ModelTellType::UpdateObjectID, ModelTell{m_objectPile.lastaddedObject().id())};

    m_modelManager.modelAddCollection()[i].models()[j].uniformList().addUniform(UniformVarible<Mat4>{"model",
                                                                                &m_modelManager.modelAddCollection()[i].models()[j].model()});
    addRenderModuleUniform(m_modelManager.modelAddCollection()[i].models()[j].uniformList());
        
    m_modelManager.modelAddCollection()[i].models()[j].uniformList().setUniformLocations(
                m_objectPile.lastAddedObject().shaderObj()->findUniformLocationList(m_modelManager.modelAddCollection()[i].models()[j].uniformList())

                                                                                        );

    // ELLIPSE_ENGINE_LOG_INFO("1: {} 2: {} 3: {}",
    //                         m_modelManager.modelAddCollection()[i].models()[j].uniformList().uniformLocations()["model"],
    //                         m_modelManager.modelAddCollection()[i].models()[j].uniformList().uniformLocations()["view"],
    //                         m_modelManager.modelAddCollection()[i].models()[j].uniformList().uniformLocations()["proj"]
    //                        );

    m_renderModels.push_back(createRenderModel(m_modelManager.modelAddCollection()[i].models()[j].modelID(),
                                               m_objectPile.lastAddedObject().objectID(),
                                               m_modelManager.modelAddCollection()[i].models()[j].uniformList(),
                                               &m_modelManager.modelAddCollection()[i].models()[j].model()
                                              )
                           );
    }
    }

    }

    // addModelsModelManager();


    removeModelsToBeRemovedModels();

    // // [ Uses modelManager to tell which models to hide ]
    // hideAllModelsToBeHidden();

    updateViewspaces();

    m_modelManager.clearModelAddCollection();
    m_modelManager.clearModelsToBeRemoved();

    renderModels();

}

RenderModuleImpl::RenderModel RenderModuleImpl::createRenderModel(ModelID modelID,
                                                                  ObjectID objectID,
                                                                  UniformList uniforms,
                                                                  Mat4* model)
{
    return RenderModel{modelID, objectID, uniforms, model};
}


// Model RenderModuleImpl::create2DShape(const char* name, uLong_t size)
// {
//    Shape shape = m_draw2D.getShape(name);
//
//    auto renderObj = m_renderer.createRenderObj(shape.m_verticies);
//    auto shaderObj = m_renderer.createShaderObj(shape.m_vShader,
//                                                shape.m_fShader,
//                                                UniformList{}
//                                                );
//
//    shaderObj->addUniform(UniformVarible<Mat4>{"view", &m_view});
//    shaderObj->addUniform(UniformVarible<Mat4>{"proj", &m_proj});
//
//    return Model{shape.m_name.c_str(), std::move(renderObj), std::move(shaderObj), size, false, false};
// }

void RenderModuleImpl::renderModel(const RenderModel& modelQuery) 
{
    RenderObject& model = m_objectPile.objectFromindex(m_objectPile.findIndex(modelQuery.objectID()).index());
    m_renderer.render(*model.renderObj(), *model.shaderObj(), modelQuery.uniformList());
    // modelQuery.uniformList().printMat4UniformList();
}

RenderModuleImpl::RenderObject RenderModuleImpl::createObject(String vShader,
                                                              String fShader,
                                                              ModelData modelData)
{
    // [ ChooseRandomVal should return u32_t ]
    ObjectID objectID{static_cast<u32_t>(m_objectIDGenerator.chooseRandomVal())};

    UniformList uniforms;

    auto renderObj = m_renderer.createRenderObj(modelData);
    auto shaderObj = m_renderer.createShaderObj(vShader, fShader, uniforms);
  
    return RenderObject(objectID, renderObj, shaderObj);
}

void RenderModuleImpl::setViewCamera(Camera camera)
{
    m_view = EllipseMath::lookAt(camera.position(),
                                 camera.front() + camera.position(),
                                 camera.upDirection()
                                );


    // ELLIPSE_ENGINE_LOG_INFO("{}, {}, {}", camera.position(),
    //                                       camera.front(),
    //                                       camera.upDirection()
    //                        );

}

void RenderModuleImpl::setCameraUp(float amount)
{
    // m_camera.m_camPos += EllipseMath::normalize(m_camera.m_camUp) * amount;
}
void RenderModuleImpl::setCameraDown(float amount)
{
   // m_camera.m_camPos -= EllipseMath::normalize(m_camera.m_camUp) * amount;
}
void RenderModuleImpl::setCameraRight(float amount)
{
   // m_camera.m_camPos -= EllipseMath::normalize(EllipseMath::cross(m_camera.m_camUp, m_camera.m_camFront)) * amount;
}
void RenderModuleImpl::setCameraLeft(float amount)
{
   // m_camera.m_camPos += EllipseMath::normalize(EllipseMath::cross(m_camera.m_camUp, m_camera.m_camFront)) * amount;
}

void RenderModuleImpl::updateCamera()
{
   // m_view = EllipseMath::lookAt(m_camera.m_camPos,
   //                              m_camera.m_camPos + m_camera.m_camFront,
   //                              m_camera.m_camUp
   //                              );


   // [ Remove this, not using window size now ]
   // i32_t winWidth = m_renderer.getWindowFrameSize().first;
   // i32_t winHeight = m_renderer.getWindowFrameSize().second;
   //
   // float aspectRatio = float(winWidth) / float(winHeight);
   //
   // m_proj = EllipseMath::ortho(-1.0f,
   //                              1.0f,
   //                             -1.0f,
   //                              1.0f,
   //                              0.1f,
   //                              100.0f
   //                            );
}

// void RenderModuleImpl::translateModel(Model& model, Vec3 pos)
// {
//    Mat4 modelTarget = Mat4(1.0f);
//    Mat4 modelTranslated = glm::translate(modelTarget, pos);   
//    Mat4* modelPtr =  model.getPtrUniformPtr("model");
//    *modelPtr = modelTranslated;
// }

void RenderModuleImpl::setClearColor(Vec4 col)
{
   m_renderer.setClearColor(col);
}

void RenderModuleImpl::setViewport(Viewspace viewspace)
{
   // [ Casting causes the lost of precision 
   //    in viewspace saved position ]
   m_renderer.setViewport(static_cast<i32_t>(viewspace.m_posX),
                          static_cast<i32_t>(viewspace.m_posY),
                          static_cast<i32_t>(viewspace.m_width),
                          static_cast<i32_t>(viewspace.m_height)
                         );
}

void RenderModuleImpl::renderModels()
{
    // for(u64_t i=0;i<m_modelManager.retrieveAmount();i++)
    // {
    // renderModel(m_renderModels[m_modelManager.retrieveModel()]);
    // }

    for(u64_t i=0;i<m_modelManager.userWorldsPrevious().size();i++)
    {
    // ELLIPSE_ENGINE_LOG_INFO("{}", m_modelManager.userWorldsPrevious()[i].cameraName());

    if(m_modelManager.userWorldsPrevious()[i].cameraName() != nullptr)
    // if(m_modelManager.userWorldsPrevious()[i].isUsingCamera() != nullptr)
    {
    setViewCamera(m_modelManager.retrieveCamera(
                                  m_modelManager.userWorldsPrevious()[i].cameraName()
                                               )
                      );
    }

    // setViewspace(m_modelManager.userWorlds()[i].viewspace());

    // [ Resets all world positions ]
    m_modelManager.removeWorldLastPositions();


    for(u32_t userIteration = 0;
        userIteration < m_modelManager.userWorldsPrevious()[i].userWorldDraw().size();
        userIteration++)
    {
    bool renderUserWorld = false;

    u32_t worldPositionIndex = m_modelManager.userWorldsPrevious()[i].userWorldDraw()[userIteration];
    const char* mainWorldName = m_modelManager.userWorldsPrevious()[i].mainWorldName();

    ModelWorldQuery modelWorldQuery = m_modelManager.modelWorldFindPrevious(worldPositionIndex, mainWorldName);

    // [ Add a world position ]
    m_modelManager.worldLastPositionAddWorld(worldPositionIndex);

    for(u64_t k = m_modelManager.
          modelWorldIndexPrevious(modelWorldQuery
                    ).modelPosition(m_modelManager.worldLastPosition(worldPositionIndex)).first;
    k < m_modelManager.
          modelWorldIndexPrevious(modelWorldQuery
                    ).modelPosition(m_modelManager.worldLastPosition(worldPositionIndex)).second;
    k++)
    {
    if(!m_modelManager.userWorldsPrevious()[i].editModels().empty())
    {
    if(m_modelManager.userWorldsPrevious()[i].editModel().positionInRenderList() == k)
    {
    renderUserWorld = true;
    if(!m_modelManager.userWorldsPrevious()[i].editModel().isInWireframeMode())
    {

    }

    // [ Need to set user renderModels model pointer to be user model pointer ]
    if(!m_modelManager.userWorldsPrevious()[i].editModel().isHidden())
    {
    renderModel(m_userWorldRenderModels[m_modelManager.userWorldsPrevious()[i].editModel().positionInUserList()]);
    }
    m_modelManager.userWorldsPrevious()[i].updateNextEditModel();
    }
    }

    if(!renderUserWorld)
    {
    if(m_modelManager.isInWireframeModel(k))
    {

    }
    if(!m_modelManager.isHiddenModel(k))
    {
    renderModel(m_renderModels[k]);
    // ELLIPSE_ENGINE_LOG_INFO("{}", k);
    renderUserWorld = false;
    }
    }

    // // [ Update next user model ]
          
    // [ Update for next world ]
    //    
    // m_modelManager.modelWorld(worldPositionIndex.updateNextSubWorl
    // 
    // }
    }
    m_modelManager.worldLastPositionUpdate(worldPositionIndex);

    }

    }
}

SharedPtr<ILayerModule> RenderModule::createRenderModule(Engine& engine)
{
   // if(engine.initData == 2DModule)
   //  {
   // return createShared<RenderMdodule2D>(engine);
   //  }
   return createShared<RenderModuleImpl>(engine); 
}

}    // namespace Ellipse
