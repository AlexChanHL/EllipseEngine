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

     virtual void render(RenderObj* render,
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

     virtual Renderer& renderer() override
     {
         return m_renderer;
     }

     virtual Mat4& proj() override
     {
         return m_proj;
     }
     virtual Mat4& view() override
     {
         return m_view;
     }

     virtual Ellipse::Camera& camera() override;

     virtual void configureCameras() override;
   
    private:
     Renderer& m_renderer;
     ModelManagerModule& m_modelManager;

     Camera m_camera;
};

}       // namespace Ellipse

