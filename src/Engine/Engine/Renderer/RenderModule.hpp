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

// [ RenderModule is a ILayerModule whenever it calls 
//   onUpdate() every layer updates independently ]
class RenderModule : public ILayerModule
{
   public:
    RenderModule()
    {

    }
    virtual ~RenderModule()
    {

    }


    virtual void onUpdateLayer() override = 0;
    virtual void initLayerModule() override = 0;
    
    // virtual Model create2DShape(const char* name, uLong_t size) = 0;
    // [ Create a camera ajusting system and not have
    //   user use these functions ]
    // vi setCaUp(float amount) = 0;

    virtual void setViewCamera(Camera camera) = 0;

    virtual void setCameraUp(float amount) = 0;
    virtual void setCameraDown(float amount) = 0;
    virtual void setCameraRight(float amount) = 0;
    virtual void setCameraLeft(float amount) = 0;
    virtual void updateCamera() = 0;


    virtual void setViewport(Viewspace viewspace) = 0;
    virtual void setClearColor(Vec4 col) = 0;


    static SharedPtr<ILayerModule> createRenderModule(Engine& engine);

   protected:
    virtual void configureCameras() = 0;


   private:

};

}    // namespace Ellipse
