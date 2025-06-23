#pragma once

#include "Renderer.hpp"
#include "Core/ModelManagerModule.hpp"
#include "Math/Matrix.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Module.hpp"
#include "Core/Base.hpp"


namespace Ellipse
{

struct RotationAmount
{
    public:
     float m_radians;
     Vec3 m_vec3;
};

class RenderModule : public IModule
{
   public:
    RenderModule()
    {

    }
    virtual ~RenderModule()
    {

    }


    virtual void init() override = 0;
    virtual void onUpdate() override = 0;

    virtual void render(RenderObj* renderObj, RenderShaderObj* shaderObj, const UniformList& uniformList) = 0;
    
    virtual void setViewCamera(Camera camera) = 0;

    virtual void setCameraFront(float amount) = 0;
    virtual void setCameraBackward(float amount) = 0;
    virtual void setCameraRight(float amount) = 0;
    virtual void setCameraLeft(float amount) = 0;

    virtual void setViewport(Viewspace viewspace) = 0;
    virtual void setClearColor(Vec4 col) = 0;

    virtual void setProjPerspective() = 0;
    virtual void setProjOrtho() = 0;

    virtual Mat4& proj() = 0;
    virtual Mat4& view() = 0;

    virtual Camera& camera() = 0;
    Map<String, RenderObjData>& preDefinedObjects()
    {
    return m_objects;
    }

    static SharedPtr<RenderModule> createRenderModule(Engine& engine);

   protected:
    virtual void configureCameras() = 0;

   protected:
    Mat4 m_proj;
    Mat4 m_view;
    Map<String, RenderObjData> m_objects;
};

}    // namespace Ellipse
