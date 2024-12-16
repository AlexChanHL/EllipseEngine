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

// struct Model
// {
//     public:
//      Model(const char* name,
//            SharedPtr<RenderObj> rObj,
//            SharedPtr<RenderShaderObj> sObj,
//            EntityRef entityRef,
//            bool hidden,
//            bool toBeRemoved)
//      : m_name{name},
//        m_scalarAmount{1.0f},
//        m_rotationAmount{Radians(0.0f), Vec3{0.0f, 0.0f, 1.0f}},
//        m_translationAmount{0.0f, 0.0f, 0.0f},
//        m_rObj{std::move(rObj)},
//        m_sObj{std::move(sObj)},
//        m_entityRef{entityRef},
//        m_isHidden{hidden},
//        m_toBeRemoved{toBeRemoved}
//      {
//      m_model = Mat4(1.0f);
//       
//      m_sObj->addUniform(UniformVarible<Mat4>{"model", &m_model});
//      }
//
//      Model(const char* name,
//            Mat4 model,
//            Vec3 scalarAmount,
//            RotationAmount rotationAmount,
//            Vec3 translationAmount,
//            SharedPtr<RenderObj> rObj,
//            SharedPtr<RenderShaderObj> sObj,
//            EntityRef entityRef,
//            bool hidden,
//            bool toBeRemoved)
//      : m_name{name},
//        m_model{model},
//        m_scalarAmount{scalarAmount},
//        m_rotationAmount{rotationAmount},
//        m_translationAmount{translationAmount},
//        m_rObj{std::move(rObj)},
//        m_sObj{std::move(sObj)},
//        m_entityRef{entityRef},
//        m_isHidden{hidden},
//        m_toBeRemoved{toBeRemoved}
//      {
//
//      }
//
//      Model(const Model& rhs)
//      : m_name{rhs.name()},
//        m_scalarAmount{rhs.scalarAmount()},
//        m_rotationAmount{rhs.rotationAmount()},
//        m_translationAmount{rhs.translationAmount()},
//        m_rObj{rhs.renderObjSharedPtr()},
//        m_sObj{rhs.shaderObjSharedPtr()},
//        m_entityRef{rhs.entityRef()},
//        m_isHidden{rhs.isHidden()},
//        m_toBeRemoved{rhs.isTobeRemoved()}
//      // [ Uniform varible class shouldn't allow creation of uniforms
//      //   with same name ]
//      {
//      // std::cout << "Copy\n";
//      m_model = rhs.modelMat();
//      m_sObj->setUniformPtr(UniformVarible<Mat4>{"model", &m_model});
//      }
//
//      Model operator=(const Model& rhs)
//      {
//      m_model = rhs.modelMat();
//      m_sObj->setUniformPtr(UniformVarible<Mat4>{"model", &m_model});
//      return *this;
//      }
//
//      const char* name() const
//      {
//      return m_name.c_str();
//      }
//
//      void setScalarAmount(Vec3 scalarAmount)
//      {
//      m_scalarAmount = scalarAmount;
//      }
//      void setRotationAmount(float radians, Vec3 rotationAmountVec)
//      {
//      m_rotationAmount.m_radians = radians;
//      m_rotationAmount.m_vec3 = rotationAmountVec;
//      }
//      void setTranslationAmount(Vec3 translationAmount)
//      {
//      m_translationAmount = translationAmount;
//      }
//
//      Vec3 scalarAmount() const
//      {
//      return m_scalarAmount;
//      }
//      RotationAmount rotationAmount() const
//      {
//      return m_rotationAmount;
//      }
//      Vec3 translationAmount() const
//      {
//      return m_translationAmount;
//      }
//
//      Mat4* getPtrUniformPtr(const char* name)
//      {
//      // m_sObj->getUniforms().printUniformList();
//      return m_sObj->getUniforms().getMat4UniformFromListByName(name).uniformPtr(0);
//      }
//
//      Mat4 modelMat() const
//      {
//      return m_model;
//      }
//      Mat4& modelMat() 
//      {
//      return m_model;
//      }
//      // Set up a vector copy operater for model class
//      // so that when we preform copy operations we remember
//      // to redirect the pointer of the uniform varible
//      // to the new stack memory of the vector
//
//      Mat4* matPtr()
//      {
//      return &m_model;
//      }
//
//      EntityRef entityRef() const 
//      {
//      return m_entityRef;
//      }
//
//      RenderObj& renderObj() const
//      {
//      return *m_rObj;
//      }
//      RenderShaderObj& shaderObj() const
//      {
//      return *m_sObj;
//      }
//
//      SharedPtr<RenderObj> renderObjSharedPtr() const
//      {
//      return m_rObj;
//      }
//
//      SharedPtr<RenderShaderObj> shaderObjSharedPtr() const
//      {
//      return m_sObj;
//      }
//
//      void resetModelMat()
//      {
//      m_model = Mat4{1.0f};
//      }
//
//      EntityRef entityRef()
//      {
//      return m_entityRef;
//      }
//
//      bool isTobeRemoved() const
//      {
//      return m_toBeRemoved;
//      }
//
//      bool isHidden() const
//      {
//      return m_isHidden;
//      }
//
//     private:
//      String m_name;
//
//      Mat4 m_model;
//      Vec3 m_scalarAmount;
//      RotationAmount m_rotationAmount;
//      Vec3 m_translationAmount;
//
//      SharedPtr<RenderObj> m_rObj;
//      SharedPtr<RenderShaderObj> m_sObj;
//
//      EntityRef m_entityRef;
//
//      bool m_isHidden;
//      bool m_toBeRemoved;
// };
//
// void scaleModel(Model& model);
// void rotateModel(Model& model);
// void translateModel(Model& model);

class Camera
{
   public:
     // [ Shouldn't automatically set camera positions ]
     Camera()
     {
     m_camPos = Vec3{0.0f, 0.0f, 3.0f};
     m_camFront = Vec3{0.0f, 0.0f, -3.0f};
     m_camUp = Vec3{0.0f, 1.0f, 0.0f};
     }

   public:
     Vec3 m_camPos;
     Vec3 m_camFront;
     Vec3 m_camUp;
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

    struct RenderModel
    {
       public:
        RenderModel(int32_t ID,
                    SharedPtr<RenderShaderObj> shaderObj,
                    SharedPtr<RenderObj> renderObj,
                    Mat4* model)
        : m_ID{ID},
          m_shaderObj{shaderObj},
          m_renderObj{renderObj},
          m_model{model}
        {

        }
        ~RenderModel()
        {

        }

       public:
        int32_t m_ID;
        SharedPtr<RenderShaderObj> m_shaderObj;
        SharedPtr<RenderObj> m_renderObj;
        Mat4* m_model;
    };

    struct RenderLayer
    {
       public:
        Vector<ModelWorld> m_modelWorlds;
    };

    virtual void onUpdateLayer() override = 0;
    virtual void initLayerModule() override = 0;
    
    virtual RenderModel createRenderModel(ModelID modelID,
                                          String vShader,
                                          String fShader,
                                          VerticiesData verts,
                                          UniformList uniforms,
                                          Mat4* model) = 0;

    // virtual Model create2DShape(const char* name, uLong_t size) = 0;
    virtual void renderModel(const RenderModel& model) = 0;
    // [ Create a camera ajusting system and not have
    //   user use these functions ]
    virtual void setCameraUp(float amount) = 0;
    virtual void setCameraDown(float amount) = 0;
    virtual void setCameraRight(float amount) = 0;
    virtual void setCameraLeft(float amount) = 0;
    virtual void updateCamera() = 0;

    virtual void setViewport(Viewspace viewspace) = 0;
    virtual void setClearColor(Vec4 col) = 0;

    // getFramesize()

    static SharedPtr<ILayerModule> createRenderModule(Engine& engine);

   private:

};

}    // namespace Ellipse
