
#include "Core/Base.hpp"
#include "Renderer.hpp"
#include "Draw2D.hpp"
#include "RenderModule.hpp"
#include "Math/Matrix.hpp"
#include "Math/TrigonometricUnits.hpp"

namespace Ellipse
{

// class RenderModuleImpl final : public RenderModule
// {
//     public:
//      RenderModuleImpl(Engine& engine);
//      ~RenderModuleImpl();
//
//      virtual void init() override;
//      virtual void onUpdate() override;
//
//      virtual void setViewCamera(Camera camera) override;
//
//      virtual void setCameraFront(float amount) override; 
//      virtual void setCameraBackward(float amount) override;
//      virtual void setCameraRight(float amount) override;
//      virtual void setCameraLeft(float amount) override;
//      // virtual void translateModel(Model& model, Vec3 pos) override;
//
//      virtual void setViewport(Viewspace viewspace) override;
//      virtual void setClearColor(Vec4 col) override;
//
//      String name() override;
//      void setName(const char* name) override;
//
//      virtual Mat4& proj() override
//      {
//      return m_proj;
//      }
//
//      virtual Mat4& view() override
//      {
//      return m_view;
//      }
//
//      virtual Camera& camera() override
//      {
//      return m_camera;
//      }
//
//     protected:
//      virtual void configureCameras() override
//      {
//
//      }
//
//     private:
//      void renderModels();
//      void renderModel(RenderObj* renderObj, RenderShaderObj* shaderObj, const UniformList& uniformList);
//
//     private:
//      ModelManagerModule& m_modelManager;
//      Renderer& m_renderer;
//
//      // [ Model manager will be NoModule if ModelManager is initalized after RenderModule's onInit() ]
//      EllipseMath::RandomRemoveLast m_objectIDGenerator;
//     
//      // Vector<Camera> m_cameras;
//      Camera m_camera;
//      Mat4 m_view;
//      Mat4 m_proj;
// };
//
// // [ Resizing window makes smaller shapes ]
//
// RenderModuleImpl::RenderModuleImpl(Engine& engine)
// : m_modelManager{static_cast<ModelManagerModule&>(engine.getModule("ModelManagerLayerModule"))},
//   m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))},
//   m_objectIDGenerator{i32_t(pow(10,3))}
// {
//    setName("RenderModule");
//
//    // [ Remove this ]
//    setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});
//
//    m_view = Mat4(1.0f);
//
//    m_view = EllipseMath::lookAt(m_camera.position(),
//                                 m_camera.position() + m_camera.front(),
//                                 m_camera.upDirection()
//                                 );
//
//    m_proj = Mat4{1.0f};
//
//    i32_t winWidth = m_renderer.getWindowFrameSize().first;
//    i32_t winHeight = m_renderer.getWindowFrameSize().second;
//
//    float aspectRatio = float(winWidth) / float(winHeight);
//
//
//    //                              aspectRatio,
//    // [ Maybe should set to aspect ratio ]
//    // m_proj = EllipseMath::ortho(-1.0f,
//    //                              1.0f,
//    //                             -1.0f,
//    //                              1.0f,
//    //                              0.1f,
//    //                              100.0f
//    //                            );
//
//    m_proj = EllipseMath::perspective(EllipseMath::Radian(45.0f).radians(),
//                                      aspectRatio,
//                                      0.1f,
//                                      100.0f
//                                     );
// }
//
// RenderModuleImpl::~RenderModuleImpl()
// {
//
// }
//
// String RenderModuleImpl::name()
// {
//    return m_name;
// }
// void RenderModuleImpl::setName(const char* name)
// {
//    m_name = name;
// }
//
// void RenderModuleImpl::init()
// {
//    m_renderer.plugin()->enable(0);
// }
//
// void RenderModuleImpl::onUpdate()
// {
//     m_view = EllipseMath::lookAt(m_camera.position(),
//                                  m_camera.front() + m_camera.position(),
//                                  m_camera.upDirection()
//                                 );
//
//     renderModels();
// }
//
// // void RenderModuleImpl::renderModel() 
// // {
//     // m_renderer.render(*model.renderObj(), *model.shaderObj(), modelQuery.uniformList());
//     // modelQuery.uniformList().printMat4UniformList();
// // }
//
// void RenderModuleImpl::setViewCamera(Camera camera)
// {
//     m_view = EllipseMath::lookAt(camera.position(),
//                                  camera.front() + camera.position(),
//                                  camera.upDirection()
//                                 );
//
//
//     // ELLIPSE_ENGINE_LOG_INFO("{}, {}, {}", camera.position(),
//     //                                       camera.front(),
//     //                                       camera.upDirection()
//     //                        );
//
// }
//
// void RenderModuleImpl::setCameraFront(float amount)
// {
//     m_camera.setPosition(m_camera.position() + EllipseMath::normalize(m_camera.front()) * amount);
// }
// void RenderModuleImpl::setCameraBackward(float amount)
// {
//     m_camera.setPosition(m_camera.position() - EllipseMath::normalize(m_camera.front()) * amount);
// }
// void RenderModuleImpl::setCameraRight(float amount)
// {
//     m_camera.setPosition(m_camera.position() - EllipseMath::normalize(EllipseMath::cross(m_camera.upDirection(), m_camera.front())) * amount);
// }
// void RenderModuleImpl::setCameraLeft(float amount)
// {
//     m_camera.setPosition(m_camera.position() + EllipseMath::normalize(EllipseMath::cross(m_camera.upDirection(), m_camera.front())) * amount);
// }
//
// // void RenderModuleImpl::translateModel(Model& model, Vec3 pos)
// // {
// //    Mat4 modelTarget = Mat4(1.0f);
// //    Mat4 modelTranslated = glm::translate(modelTarget, pos);   
// //    Mat4* modelPtr =  model.getPtrUniformPtr("model");
// //    *modelPtr = modelTranslated;
// // }
//
// void RenderModuleImpl::setClearColor(Vec4 col)
// {
//    m_renderer.setClearColor(col);
// }
//
// void RenderModuleImpl::setViewport(Viewspace viewspace)
// {
//    // [ Casting causes the lost of precision 
//    //    in viewspace saved position ]
//    m_renderer.setViewport(static_cast<i32_t>(viewspace.m_posX),
//                           static_cast<i32_t>(viewspace.m_posY),
//                           static_cast<i32_t>(viewspace.m_width),
//                           static_cast<i32_t>(viewspace.m_height)
//                          );
// }
//
// void RenderModuleImpl::renderModels()
// {
//     for(u64_t i=0;i<m_modelManager.models().size();i++)
//     {
//     const Model& renderModelModel = m_modelManager.models()[i];
//     if(renderModelModel.renderObject() != nullptr)
//     {
//     renderModel(renderModelModel.renderObject(), renderModelModel.shaderObject(), renderModelModel.uniformList());
//     }
//
//     }
//
// }

// void RenderModuleImpl::renderModel(RenderObj* renderObj,
//                                    RenderShaderObj* shaderObj,
//                                    const UniformList& uniformList)
// {
//     m_renderer.render(*renderObj, *shaderObj, uniformList);
// }

// SharedPtr<IModule> RenderModule::createRenderModule(Engine& engine)
// {
//    return createShared<RenderModuleImpl>(engine); 
// }

}    // namespace Ellipse
