#pragma once

#include "Renderer.hpp"
#include "Math/Matrix.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Module.hpp"
#include "Core/Base.hpp"
#include "EntitySystem/EntitySystem.hpp"
#include "Camera.hpp"


namespace Ellipse {
 struct RotationAmount {
     public:
      float m_radians;
      EllipseMath::Vec3 m_vec3;
 };
 
 class RenderModule : public IModule {
    public:
     RenderModule() {
     }
     virtual ~RenderModule() {
     }
 
     virtual void init() override = 0;
     virtual void onUpdate() override = 0;
     virtual void render(RenderObj* renderObj, RenderShaderObj* shaderObj, const UniformList& uniformList) = 0;
     virtual void setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height) = 0;
     virtual void setViewCamera(Camera camera) = 0;
     virtual void setCameraFront(float amount) = 0;
     virtual void setCameraBackward(float amount) = 0;
     virtual void setCameraRight(float amount) = 0;
     virtual void setCameraLeft(float amount) = 0;
     virtual void mouseUpdate(Pair<float, float> offsets) {
      camera().registerMouseUpdate(offsets);
      updateView();
     }
 
     virtual void setClearColor(EllipseMath::Vec4 col) = 0;
     void setProjPerspective() {
      i32_t winWidth = renderer().getWindowFrameSize().first;
      i32_t winHeight = renderer().getWindowFrameSize().second;
  
      float aspectRatio = float(winWidth) / float(winHeight);
  
      m_proj = EllipseMath::perspective(EllipseMath::radians(45.0f),
                                        aspectRatio,
                                        0.1f,
                                        100.0f
      );
     }
     void setProjOrtho() {
      m_proj = EllipseMath::ortho(-1.0f,
                                   1.0f,
                                  -1.0f,
                                   1.0f,
                                   0.1f,
                                   100.0f
      );
     }
 
     virtual Renderer& renderer() = 0;
     virtual EllipseMath::Mat4& proj() = 0;
     virtual EllipseMath::Mat4& view() = 0;
     virtual Camera& camera() = 0;
     Map<String, RenderObjData>& preDefinedObjects() {
      return m_objects;
     }
     // virtual Vector<SharedPtr<>> renderables() = 0;
     // virtual Vector<u64_t> renderableToBeRendered() = 0;
 
     static SharedPtr<RenderModule> createRenderModule(Engine& engine);
 
    protected:
     void updateView() {
      m_view = EllipseMath::lookAt(camera().position(),
                                   camera().front() + camera().position(),
                                   camera().upDirection()
      );
     }
     virtual void configureCameras() = 0;
 
    protected:
     EllipseMath::Mat4 m_proj;
     EllipseMath::Mat4 m_view;
     Map<String, RenderObjData> m_objects;
 };
 
}    // namespace Ellipse
