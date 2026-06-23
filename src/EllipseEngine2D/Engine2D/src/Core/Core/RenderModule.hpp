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
     virtual void setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height) override;
 
     virtual void setViewCamera(Camera camera) override;

     virtual void setCameraFront(float amount) override;
     virtual void setCameraBackward(float amount) override;
     virtual void setCameraRight(float amount) override;
     virtual void setCameraLeft(float amount) override;

     virtual void setClearColor(EllipseMath::Vec4 col) override;

     virtual Renderer& renderer() override {
         return m_renderer;
     }

     virtual EllipseMath::Mat4& proj() override { return m_proj; }
     virtual EllipseMath::Mat4& view() override { return m_view; }

     virtual Ellipse::Camera& camera() override;

     virtual void configureCameras() override;
   
    private:
     Renderer& m_renderer;
     Camera m_camera;
};

}       // namespace Ellipse

