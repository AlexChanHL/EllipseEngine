#pragma once


#include "Renderer/RenderModule.hpp"

namespace Ellipse {
 class RenderComponent : public Component {
    public:
     RenderComponent() {} 
     RenderComponent(RenderModule& renderModule, RenderObjData& data) 
     : m_renderModule{&renderModule},
       m_modelData{createShared<ModelData3D>()} {
      m_data = data;
      m_renderObj = m_renderModule->renderer().createRenderObj(data);
      m_shaderObj = m_renderModule->renderer().createShaderObj("Assets/Shader/Quad.vert.glsl",
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
      auto model = UniformVariable<EllipseMath::Mat4>{"model", m_modelData->model().get()};
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
     RenderObjData& data() { return m_data; }
     SharedPtr<ModelData> model() { return m_modelData; }

    protected:
     SharedPtr<RenderObj> m_renderObj;
     SharedPtr<RenderShaderObj> m_shaderObj;
     RenderModule* m_renderModule;
     RenderObjData m_data;
     SharedPtr<ModelData> m_modelData;
 };
}

