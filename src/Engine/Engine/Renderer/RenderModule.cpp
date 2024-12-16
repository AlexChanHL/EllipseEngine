
#include "Core/Base.hpp"
#include "Renderer.hpp"
#include "Draw2D.hpp"
#include "RenderModule.hpp"
#include "Math/Matrix.hpp"

namespace Ellipse
{


// void scaleModel(Model& model)
// {
//    Mat4 modelScaled = glm::scale(model.modelMat(), model.scalarAmount());
//
//    Mat4* modelPtr =  model.getPtrUniformPtr("model");
//    *modelPtr = modelScaled;
// }
// void rotateModel(Model& model)
// {
//    Mat4 modelRotated = glm::rotate(model.modelMat(), model.rotationAmount().m_radians, model.rotationAmount().m_vec3);
//
//    Mat4* modelPtr =  model.getPtrUniformPtr("model");
//    *modelPtr = modelRotated;
// }
//
// void translateModel(Model& model)
// {
//    Mat4 modelTranslated = glm::translate(model.modelMat(), model.translationAmount());
//
//    Mat4* modelPtr =  model.getPtrUniformPtr("model");
//    *modelPtr = modelTranslated;
//    // Math::printMat(*modelPtr);
// }

class RenderModuleImpl final : public RenderModule
{
    public:
     RenderModuleImpl(Engine& engine);
     ~RenderModuleImpl();

     virtual void initLayerModule() override;
     virtual void onUpdateLayer() override;

     virtual RenderModel createRenderModel(ModelID modelID,
                                           String vShader,
                                           String fShader,
                                           VerticiesData verts,
                                           UniformList uniforms,
                                           Mat4* model) override
     {
     auto renderObj = m_renderer.createRenderObj(verts);
     auto shaderObj = m_renderer.createShaderObj(vShader, fShader, uniforms);

     shaderObj->addUniform(UniformVarible<Mat4>{"model", model});
     shaderObj->addUniform(UniformVarible<Mat4>{"view", &m_view});
     shaderObj->addUniform(UniformVarible<Mat4>{"proj", &m_proj});

     // Math::printMat(*model);

     return RenderModel{modelID.m_ID, shaderObj, renderObj, model};
     }
     // virtual Model createModel(const char* modelName,
     //                           String vShader,
     //                           String fShader,
     //                           VerticiesData verts,
     //                           UniformList uniforms,
     //                           uLong_t size
     //                          ) override;
     // virtual Model create2DShape(const char* name, uLong_t size) override;
     virtual void renderModel(const RenderModel& model) override;

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

    private:
     void removeModelsToBeRemovedModels()
     {
     for(u32_t i = 0; i < m_modelManager.modelsToBeRemovedIndicies().size(); i++)
     {
     m_renderModels.erase(m_renderModels.begin() + m_modelManager.modelsToBeRemovedIndicies()[i]);
     }

     }

     void renderModels()
     {

     for(u64_t i=0;i<m_modelManager.userWorldsPrevious().size();i++)
     {

     // setCamera(m_modelManager.userWorlds()[i].camera());
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

     // [ Reset all positions ]
     // for(u32_t userIteration = 0;
     //      userIteration < m_modelManager.userWorldsPrevious()[i].userWorldDraw().size();
     //      userIteration++)
     // {
     // m_modelManager.modelWorldPrevious(worldPositionIndex,
     //                                   m_modelManager.userWorldsPrevious()[i].mainWorldName()).resetCurrentPosition();
     // }

     }

   //   // [ Need to set individual viewports that reside 
   //   //   inside RenderViewspaces ]
   //   //
   //   // [ Worlds contain render viewspaces and all models
   //   //   that belong to the world. Any other worlds cannot
   //   //   models that do not belong to it. Worlds contain 
   //   //   all total models and renderModel() will draw models
   //   //   according to their viewspace. ]
   //   //  
   //   // [ To specify new viewspaces with a new list of models 
   //   //   the user craetes a new world ]
      
     }

     void reOrderModels()
     {
 
     }

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
     Vector<RenderModel> m_renderModels;
     Vector<RenderModel> m_userWorldRenderModels;
     Vector<RenderLayer> m_renderLayers;
     Vector<RenderLayer>::iterator m_renderLayerIterator;

     // [ Model manager will be NoModule if ModelManager is initalized after RenderModule's onInit() ]
     Draw2D m_draw2D;
    
     // Vector<Camera> m_cameras;
     Camera m_camera;
     Mat4 m_view;
     Mat4 m_proj;
};

// [ Resizing window makes smaller shapes ]

RenderModuleImpl::RenderModuleImpl(Engine& engine)
: m_modelManager{static_cast<ModelManagerModule&>(engine.getLayerModule("ModelManagerLayerModule"))},
  m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))}
{
   setName("RenderModule");

   // [ Remove this ]
   setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});

   m_view = Mat4(1.0f);

   m_view = EllipseMath::lookAt(m_camera.m_camPos,
                                m_camera.m_camPos + m_camera.m_camFront,
                                m_camera.m_camUp
                                );

   m_proj = Mat4(1.0f);

   i32_t winWidth = m_renderer.getWindowFrameSize().first;
   i32_t winHeight = m_renderer.getWindowFrameSize().second;


   float aspectRatio = float(winWidth) / float(winHeight);


   // m_proj = EllipseMath::ortho(-aspectRatio,
   //                              aspectRatio,
   // [ Maybe should set to aspect ratio ]
   m_proj = EllipseMath::ortho(-1.0f,
                                1.0f,
                               -1.0f,
                                1.0f,
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
   m_renderLayers.push_back(RenderLayer{});
   m_renderLayerIterator = m_renderLayers.begin();
}

void RenderModuleImpl::onUpdateLayer()
{
   if(m_renderLayerIterator == m_renderLayers.end())
   {
   m_renderLayerIterator = m_renderLayers.begin();
   }

     
   // [ Adds model from subModelManagers list ]
   for(unsigned long i=0;i<m_modelManager.subModelManagers().size();i++)
   {
   // [ Adds the model to the world its querying ]
   // RenderViewspace renderViewspace{m_modelManager.subModelManagers()[i].viewspace()};


   // [ Models need to be queried after initalization call, 
   //   if we create a new world that world be accessed
   //   for its models ]

   for(u64_t j=0;j<m_modelManager.subModelManagers()[i].models().size();j++)
   {
    m_renderModels.push_back(
      createRenderModel(
   m_modelManager.subModelManagers()[i].models()[j].m_modelID,
   m_modelManager.subModelManagers()[i].models()[j].m_vertexShader,
   m_modelManager.subModelManagers()[i].models()[j].m_fragmentShader,
   m_modelManager.subModelManagers()[i].models()[j].m_verticies,
   m_modelManager.subModelManagers()[i].models()[j].m_uniformList,
   &m_modelManager.subModelManagers()[i].models()[j].m_model
                       )
                                           );
   }

   // if(m_modelManager.subModelManagers()[i].isAddWorld())
   // {
   // m_renderLayerIterator->m_modelWorlds.push_back(ModelWorld{});
   // }

   }


   removeModelsToBeRemovedModels();

   // // [ Uses modelManager to tell which models to hide ]
   // hideAllModelsToBeHidden();

   updateViewspaces();

   m_modelManager.clearSubModelManagers();
   m_modelManager.clearModelsToBeRemoved();

   renderModels();

   m_renderLayerIterator++;
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

void RenderModuleImpl::renderModel(const RenderModel& model) 
{
   m_renderer.render(*model.m_renderObj, *model.m_shaderObj);
}

void RenderModuleImpl::setCameraUp(float amount)
{
   m_camera.m_camPos += EllipseMath::normalize(m_camera.m_camUp) * amount;
}
void RenderModuleImpl::setCameraDown(float amount)
{
   m_camera.m_camPos -= EllipseMath::normalize(m_camera.m_camUp) * amount;
}
void RenderModuleImpl::setCameraRight(float amount)
{
   m_camera.m_camPos -= EllipseMath::normalize(EllipseMath::cross(m_camera.m_camUp, m_camera.m_camFront)) * amount;
}
void RenderModuleImpl::setCameraLeft(float amount)
{
   m_camera.m_camPos += EllipseMath::normalize(EllipseMath::cross(m_camera.m_camUp, m_camera.m_camFront)) * amount;
}

void RenderModuleImpl::updateCamera()
{
   m_view = EllipseMath::lookAt(m_camera.m_camPos,
                                m_camera.m_camPos + m_camera.m_camFront,
                                m_camera.m_camUp
                                );

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

SharedPtr<ILayerModule> RenderModule::createRenderModule(Engine& engine)
{
   // if(engine.initData == 2DModule)
   //  {
   // return createShared<RenderMdodule2D>(engine);
   //  }
   return createShared<RenderModuleImpl>(engine); 
}

}    // namespace Ellipse
