
#include "Core/Base.hpp"
#include "Renderer.hpp"
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

   // Math::printMat(model.modelMat());
   // exit(1);
}

class RenderModuleImpl final : public RenderModule
{
    public:
     RenderModuleImpl(Engine& engine);
     virtual Model createModel(const char* modelName,
                              String vShader,
                              String fShader,
                              Vector<float> verts,
                              UniformList uniforms,
                              uLong_t size
                                            ) override;
     virtual void renderModel(const Model& model) override;
     virtual void setClearColor(Vec4 col) override;
     virtual void translateModel(Model& model, Vec3 pos) override;

     String name() override;
     void setName(const char* name) override;

    private:
     Mat4 m_view;
     Mat4 m_proj;
     Renderer& m_renderer;
};

RenderModuleImpl::RenderModuleImpl(Engine& engine)
: m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))}
{
   setName("RenderModule");

   m_view = Mat4(1.0f);
   m_proj = Mat4(1.0f);
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
                                    Vector<float> verts,
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

void RenderModuleImpl::renderModel(const Model& model) 
{
   m_renderer.render(model.renderObj(), model.shaderObj());
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

   // Model.setTranslationAmount;
}

void RenderModuleImpl::setClearColor(Vec4 col)
{
   m_renderer.setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});
}

SharedPtr<IModule> RenderModule::createRenderModule(Engine& engine)
{
   return createShared<RenderModuleImpl>(engine); 
}

}    // namespace Ellipse
