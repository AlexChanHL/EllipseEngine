#pragma once

#include "Ellipse.hpp"


// namespace Ellipse3D
// {

namespace Ellipse
{

class RenderModule3D : public RenderModule
{
    public:
     RenderModule3D(Engine& engine); ~RenderModule3D();

     virtual void init() override;
     virtual void onUpdate() override;
     
     void render(RenderObj* renderObj, RenderShaderObj* shaderObj, const UniformList& uniformList) override;

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
     Renderer& m_renderer;

     EllipseMath::RandomRemoveLast m_objectIDGenerator;
    
     // Vector<Camera> m_cameras;
     Camera m_camera;
     Mat4 m_view;
     Mat4 m_proj;
};


}       // namespace Ellipse

// }       // namespace Ellipse3D

