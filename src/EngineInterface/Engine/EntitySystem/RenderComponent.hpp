#pragma once


#include "Renderer/RenderModule.hpp"

namespace Ellipse {
 class RenderComponent : public Component {
    public:
     RenderComponent() {} 
     RenderComponent(RenderModule& renderModule, RenderObjData& data) 
     : m_renderModule{&renderModule},
       m_model{createShared<EllipseMath::Mat4>(1.0f)} {
      m_renderObj = renderModule.renderer().createRenderObj(data);
      m_shaderObj = renderModule.renderer().createShaderObj("Assets/Shader/Quad.vert.glsl",
                                                            "Assets/Shader/Quad.frag.glsl");
     };
     ~RenderComponent() {
 
     };
  
     virtual void onUpdate() override {
 
     }
 
     static String name() {
      return "Render";
     }

     virtual void onInit() override {
      auto model = UniformVariable<EllipseMath::Mat4>{"model", m_model.get()};
      m_shaderObj->
       addUniform<EllipseMath::Mat4>(model);
      auto proj = UniformVariable<EllipseMath::Mat4>{"proj", &m_renderModule->proj()};
      m_shaderObj->
       addUniform<EllipseMath::Mat4>(proj);
      auto view = UniformVariable<EllipseMath::Mat4>{"view", &m_renderModule->view()};
      m_shaderObj->
       addUniform<EllipseMath::Mat4>(view);

     }

     SharedPtr<RenderObj> renderObj() { return m_renderObj; }
     SharedPtr<RenderShaderObj> shaderObj() { return m_shaderObj; }
     SharedPtr<EllipseMath::Mat4> model() { return m_model; }
 
     void translate(EllipseMath::Vec4 pos) {
      // EllipseMath::Mat4& model = m_shaderObj.findUniform<EllipseMath::Mat4>("Model");
      // EllipseMath::translate(model, pos);
      // m_renderObj;
     }
      
    private:
     SharedPtr<RenderObj> m_renderObj;
     SharedPtr<RenderShaderObj> m_shaderObj;
     RenderModule* m_renderModule;
     SharedPtr<EllipseMath::Mat4> m_model;
 };
}

