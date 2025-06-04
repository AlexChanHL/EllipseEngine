#pragma once

#include "Ellipse.hpp"


// namespace Ellipse3D
// {

namespace Ellipse
{

class RenderModule3D : public RenderModule
{
    public:
     RenderModule3D(Engine& engine);
     ~RenderModule3D();

     virtual void init() override;
     virtual void onUpdate() override;
     
     virtual void setViewCamera(Ellipse::Camera camera) override;

     virtual void setCameraFront(float amount) override;
     virtual void setCameraBackward(float amount) override;
     virtual void setCameraRight(float amount) override;
     virtual void setCameraLeft(float amount) override;

     virtual void setViewport(Ellipse::Viewspace viewspace) override;
     virtual void setClearColor(Vec4 col) override;

     virtual Mat4& proj() override
     {
     return m_proj;
     }
     virtual Mat4& view() override
     {
     return m_view;
     }

     virtual Camera& camera() override
     {
     return m_camera;
     }

     virtual void configureCameras() override
     {

     }

    private:
     void renderModels();
     void renderModel(RenderObj* renderObj, RenderShaderObj* shaderObj, const UniformList& uniformList);

    private:
     ModelManagerModule& m_modelManager;
     Renderer& m_renderer;

     // [ Model manager will be NoModule if ModelManager is initalized after RenderModule's onInit() ]
     EllipseMath::RandomRemoveLast m_objectIDGenerator;
    
     // Vector<Camera> m_cameras;
     Camera m_camera;
     Mat4 m_view;
     Mat4 m_proj;
};


}       // namespace Ellipse

// }       // namespace Ellipse3D

