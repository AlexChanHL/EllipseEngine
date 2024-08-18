
#include "Core/Base.hpp"
#include "Renderer.hpp"
#include "Draw2D.hpp"
#include "RenderModule.hpp"
#include "Math/Matrix.hpp"

namespace Ellipse
{


// [ Create a model file so and not have it in RenderModule ]
//
void scaleModel(Model& model)
{
   Mat4 modelScaled = glm::scale(model.modelMat(), model.scalarAmount());

   Mat4* modelPtr =  model.getPtrUniformPtr("model");
   *modelPtr = modelScaled;
}
void rotateModel(Model& model)
{
   Mat4 modelRotated = glm::rotate(model.modelMat(), model.rotationAmount().m_radians, model.rotationAmount().m_vec3);

   Mat4* modelPtr =  model.getPtrUniformPtr("model");
   *modelPtr = modelRotated;
}

void translateModel(Model& model)
{
   Mat4 modelTranslated = glm::translate(model.modelMat(), model.translationAmount());

   Mat4* modelPtr =  model.getPtrUniformPtr("model");
   *modelPtr = modelTranslated;
   // Math::printMat(*modelPtr);
}

class RenderModuleImpl final : public RenderModule
{
    public:
     RenderModuleImpl(Engine& engine);
     virtual Model createModel(const char* modelName,
                               String vShader,
                               String fShader,
                               VerticiesData verts,
                               UniformList uniforms,
                               uLong_t size
                              ) override;
     virtual Model create2DShape(const char* name, uLong_t size) override;
     virtual void renderModel(const Model& model) override;
     virtual void setClearColor(Vec4 col) override;
     virtual void setCameraRight(float amount) override;
     virtual void setCameraLeft(float amount) override;
     virtual void updateCamera() override;
     virtual void translateModel(Model& model, Vec3 pos) override;

     String name() override;
     void setName(const char* name) override;

    private:
     Renderer& m_renderer;
     Draw2D m_draw2D;
    
     // Vector<ViewSpace> m_viewSpaces;
    
     Camera m_camera;
     Mat4 m_view;
     Mat4 m_proj;
};

// [ Resizing window makes smaller shapes ]

RenderModuleImpl::RenderModuleImpl(Engine& engine)
: m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))}
{
   setName("RenderModule");

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

String RenderModuleImpl::name()
{
   return m_name;
}
void RenderModuleImpl::setName(const char* name)
{
   m_name = name;
}

Model RenderModuleImpl::createModel(const char* modelName,
                                    String vShader,
                                    String fShader,
                                    VerticiesData verts,
                                    UniformList uniforms,
                                    uLong_t size
                                    )
{
   auto renderObj = m_renderer.createRenderObj(verts);
   auto shaderObj = m_renderer.createShaderObj(vShader, fShader, uniforms);

   shaderObj->addUniform(UniformVarible<Mat4>{"view", &m_view});
   shaderObj->addUniform(UniformVarible<Mat4>{"proj", &m_proj});

   return Model{modelName, std::move(renderObj), std::move(shaderObj), size, false, false};
}

Model RenderModuleImpl::create2DShape(const char* name, uLong_t size)
{
   Shape shape = m_draw2D.getShape(name);

   auto renderObj = m_renderer.createRenderObj(shape.m_verticies);
   auto shaderObj = m_renderer.createShaderObj(shape.m_vShader,
                                               shape.m_fShader,
                                               UniformList{}
                                               );

   shaderObj->addUniform(UniformVarible<Mat4>{"view", &m_view});
   shaderObj->addUniform(UniformVarible<Mat4>{"proj", &m_proj});

   return Model{shape.m_name.c_str(), std::move(renderObj), std::move(shaderObj), size, false, false};
}

void RenderModuleImpl::renderModel(const Model& model) 
{
   m_renderer.render(model.renderObj(), model.shaderObj());
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

   i32_t winWidth = m_renderer.getWindowFrameSize().first;
   i32_t winHeight = m_renderer.getWindowFrameSize().second;

   float aspectRatio = float(winWidth) / float(winHeight);

   m_proj = EllipseMath::ortho(-1.0f,
                                1.0f,
                               -1.0f,
                                1.0f,
                                0.1f,
                                100.0f
                              );
}

void RenderModuleImpl::translateModel(Model& model, Vec3 pos)
{
   Mat4 modelTarget = Mat4(1.0f);
   Mat4 modelTranslated = glm::translate(modelTarget, pos);   
   // model.modelMat() = glm::translate(modelTarget, pos);   
   // Mat4 modelTranslated = glm::translate(model.modelMat(), pos);   
   // model.shaderObj().setUniformPtr(UniformVarible<Mat4>{"model", pointerToModel});
  //
   // Mat4* modelPtr =  model.shaderObj().getUniforms().getMat4Uniforms()[2].uniformPtr(0);
   Mat4* modelPtr =  model.getPtrUniformPtr("model");
   *modelPtr = modelTranslated;
}

void RenderModuleImpl::setClearColor(Vec4 col)
{
   m_renderer.setClearColor(col);
}

SharedPtr<IModule> RenderModule::createRenderModule(Engine& engine)
{
   // if(engine.initData == 2DModule)
   //  {
   // return createShared<RenderMdodule2D>(engine);
   //  }
   return createShared<RenderModuleImpl>(engine); 
}

}    // namespace Ellipse
