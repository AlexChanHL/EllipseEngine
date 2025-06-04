#pragma once

#include "Ellipse.hpp"


namespace Ellipse
{

class RenderModule2D : public RenderModule
{
    public:
     RenderModule2D(Engine& engine);
     ~RenderModule2D();

     virtual void init() override;
     virtual void onUpdate() override;

     virtual void renderModel(RenderObj* render,
                              RenderShaderObj* shaderObj,
                              const UniformList& uniformaList
                             );
 
     virtual void setViewCamera(Camera camera) override;

     virtual void setCameraFront(float amount) override;
     virtual void setCameraBackward(float amount) override;
     virtual void setCameraRight(float amount) override;
     virtual void setCameraLeft(float amount) override;

     virtual void setViewport(Viewspace viewspace) override;
     virtual void setClearColor(Vec4 col) override;

     virtual Mat4& proj() override;
     virtual Mat4& view() override;

     virtual Ellipse::Camera& camera() override;

     virtual void configureCameras() override;
   
    private:
     Renderer& m_renderer;
     ModelManagerModule& m_modelManager;

     Camera m_camera;
};

}       // namespace Ellipse

