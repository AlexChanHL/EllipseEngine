#pragma once

#include "Renderer.hpp"
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

struct Model
{
    public:
     Model(const char* name,
           SharedPtr<RenderObj> rObj,
           SharedPtr<RenderShaderObj> sObj,
           EntityRef entityRef,
           bool hidden,
           bool toBeRemoved)
     : m_name{name},
       m_scalarAmount{1.0f},
       m_rotationAmount{Radians(0.0f), Vec3{0.0f, 0.0f, 1.0f}},
       m_translationAmount{0.0f, 0.0f, 0.0f},
       m_rObj{std::move(rObj)},
       m_sObj{std::move(sObj)},
       m_entityRef{entityRef},
       m_isHidden{hidden},
       m_toBeRemoved{toBeRemoved}
     {
     m_model = Mat4(1.0f);
      
     m_sObj->addUniform(UniformVarible<Mat4>{"model", &m_model});
     }

     const char* name() const
     {
     return m_name.c_str();
     }

     void setScalarAmount(Vec3 scalarAmount)
     {
     m_scalarAmount = scalarAmount;
     }
     void setRotationAmount(float radians, Vec3 rotationAmountVec)
     {
     m_rotationAmount.m_radians = radians;
     m_rotationAmount.m_vec3 = rotationAmountVec;
     }
     void setTranslationAmount(Vec3 translationAmount)
     {
     m_translationAmount = translationAmount;
     }

     Vec3 scalarAmount()
     {
     return m_scalarAmount;
     }
     RotationAmount rotationAmount()
     {
     return m_rotationAmount;
     }
     Vec3 translationAmount()
     {
     return m_translationAmount;
     }

     Mat4* getPtrUniformPtr(const char* name)
     {
     return m_sObj->getUniforms().getMat4UniformFromListByName(name).uniformPtr(0);
     }

     Mat4 modelMat() const
     {
     return m_model;
     }
     Mat4& modelMat() 
     {
     return m_model;
     }
     // Set up a vector copy operater for model class
     // so that when we preform copy operations we remember
     // to redirect the pointer of the uniform varible
     // to the new stack memory of the vector

     //
     Mat4* matPtr()
     {
     return &m_model;
     }

     EntityRef entityRef() const 
     {
     return m_entityRef;
     }

     RenderObj& renderObj() const
     {
     return *m_rObj;
     }
     RenderShaderObj& shaderObj() const
     {
     return *m_sObj;
     }

     void resetModelMat()
     {
     m_model = Mat4{1.0f};
     }

     bool isTobeRemoved()
     {
     return m_toBeRemoved;
     }

     bool isHidden()
     {
     return m_isHidden;
     }

    private:
     String m_name;

     Mat4 m_model;
     Vec3 m_scalarAmount;
     RotationAmount m_rotationAmount;
     Vec3 m_translationAmount;

     // Have a vector of render models
     // with shader object data so that
     // when we push back a model the object
     // retains the pointer

     SharedPtr<RenderObj> m_rObj;
     SharedPtr<RenderShaderObj> m_sObj;

     EntityRef m_entityRef;

     bool m_isHidden;
     bool m_toBeRemoved;
};

void scaleModel(Model& model);
void rotateModel(Model& model);
void translateModel(Model& model);

class RenderModule : public IModule
{
   public:
    RenderModule() = default;
    virtual ~RenderModule() = default;
    
    virtual Model createModel(const char* modelName,
                              String vShader,
                              String fShader,
                              Vector<float> verts,
                              UniformList uniforms,
                              uLong_t size
                                            ) = 0;
    virtual void renderModel(const Model& model) = 0;
    virtual void translateModel(Model& model, Vec3 pos) = 0;

    virtual void setClearColor(Vec4 col) = 0;

    static SharedPtr<IModule> createRenderModule(Engine& engine);

   private:

};

}    // namespace Ellipse
