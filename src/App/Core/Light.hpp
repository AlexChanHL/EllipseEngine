#pragma once

#include "Ellipse.hpp"


class Material
{
   public:
    Material()
    : m_ambient{createUnique<Vec3>(1.0f)},
      m_diffuse{createUnique<Vec3>(0.8f)},
      m_specular{createUnique<Vec3>(1.0f)},
      m_reflectiveness{createUnique<float>(25.6f)}
    {

    }
    ~Material()
    {

    }

    Material(Material& rhs)
    : m_ambient{std::move(rhs.ambient())},
      m_diffuse{std::move(rhs.diffuse())},
      m_specular{std::move(rhs.specular())},
      m_reflectiveness{std::move(rhs.reflectiveness())}
    {

    }

    Material operator=(Material& rhs)
    {
    // Material material;
    //
    // material.setAmbient(std::move(rhs.ambient()));
    // material.setDiffuse(std::move(rhs.diffuse()));
    // material.setSpecular(std::move(rhs.specular()));
    // material.setReflectiveness(std::move(rhs.reflectiveness()));

    return Material{rhs};
    }

    void setAmbient(UniquePtr<Vec3> ambient)
    {
    m_ambient = std::move(ambient);
    }

    void setDiffuse(UniquePtr<Vec3> diffuse)
    {
    m_diffuse = std::move(diffuse);
    }

    void setSpecular(UniquePtr<Vec3> specular)
    {
    m_specular = std::move(specular);
    }

    void setReflectiveness(UniquePtr<float> reflectiveness)
    {
    m_reflectiveness = std::move(reflectiveness);
    }

    UniquePtr<Vec3>& ambient()
    {
    return m_ambient; 
    }

    UniquePtr<Vec3>& diffuse()
    {
    return m_diffuse; 
    }

    UniquePtr<Vec3>& specular()
    {
    return m_specular; 
    }

    UniquePtr<float>& reflectiveness()
    {
    return m_reflectiveness;
    }

   private:
    UniquePtr<Vec3> m_ambient; 
    UniquePtr<Vec3> m_diffuse; 
    UniquePtr<Vec3> m_specular; 
    UniquePtr<float> m_reflectiveness;
};

inline void translateModel(Mat4& model, Vec3 translateAmount)
{
    model = Ellipse::EllipseMath::translate(model, translateAmount);
}

inline void rotateModel(Mat4& model, float radians, Vec3 rotateAmount)
{
    model = Ellipse::EllipseMath::rotate(model, radians, rotateAmount);
}

inline void scaleModel(Mat4& model, Vec3 scaleAmount)
{
    model = Ellipse::EllipseMath::scale(model, scaleAmount);
}


class ModelVal
{
   public:
    ModelVal()
    : m_model{Mat4{1.0f}},
      m_normalMatrix{createUnique<Mat3>(1.0f)},
      m_translationAmount{Vec3{1.0f}},
      m_rotationAmount{Pair<Vec3, float>{Vec3{1.0f}, 0.0f}},
      m_scaleAmount{Vec3{1.0f}}
    {

    }
    ~ModelVal()
    {

    }

    ModelVal(ModelVal& modelVal)
    : m_model{modelVal.model()},
      m_normalMatrix{std::move(modelVal.normalMatrix())},
      m_translationAmount{modelVal.translationAmount()},
      m_rotationAmount{modelVal.rotationAmount()},
      m_scaleAmount{modelVal.scaleAmount()}
    {

    }

    ModelVal operator=(ModelVal modelVal)
    {
    // ModelVal modelValue;
    //
    // modelValue.setModel(modelVal.model());
    // modelValue.setNormalMatrix(std::move(modelVal.normalMatrix()));
    // modelValue.setTranslateAmount(modelVal.translationAmount());
    // modelValue.setRotateAmount(modelVal.rotationAmount().second, modelVal.rotationAmount().first);
    // modelValue.setScaleAmount(modelVal.scaleAmount());

    // return modelValue;
    return ModelVal{modelVal};
    }

    void setModel(Mat4 model)
    {
    m_model = model;
    }

    void setNormalMatrix(UniquePtr<Mat3> normalMatrix)
    {
    m_normalMatrix = std::move(normalMatrix);
    }

    void setTranslateAmount(Vec3 translateAmount)
    {
    m_translationAmount = translateAmount;
    }

    void setRotateAmount(float radians, Vec3 rotateAmount)
    {
    m_rotationAmount = Pair<Vec3, float>{rotateAmount, radians};
    }

    void setScaleAmount(Vec3 scaleAmount)
    {
    m_scaleAmount = scaleAmount;
    }

    void totalAmounts()
    {
    m_model = Mat4{1.0f};

    translateModel(m_model, m_translationAmount);
    rotateModel(m_model, m_rotationAmount.second, m_rotationAmount.first);
    scaleModel(m_model, m_scaleAmount);

    *m_normalMatrix = Ellipse::EllipseMath::inverse(Ellipse::EllipseMath::transpose(Mat3{m_model}));
    }

    Mat4 model() const
    {
    return m_model;
    }

    UniquePtr<Mat3>& normalMatrix()
    {
    return m_normalMatrix;
    }

    Vec3 translationAmount() const
    {
    return m_translationAmount;
    }

    Pair<Vec3, float> rotationAmount()
    {
    return m_rotationAmount;
    }

    Vec3 scaleAmount()
    {
    return m_scaleAmount;
    }

    Material& material()
    {
    return m_material;
    }

   private:
    Mat4 m_model;

    UniquePtr<Mat3> m_normalMatrix;

    Vec3 m_translationAmount;
    Pair<Vec3, float> m_rotationAmount;
    Vec3 m_scaleAmount;

    Material m_material;
};

class Light
{
   public:
    Light()
    : m_isDirectional{false},
      m_ambient{Vec3{0.1f}},
      m_diffuse{Vec3{0.8f}},
      m_specular{Vec3{1.0f}},
      m_lightColor{Vec3{1.0f}},
      m_lightPosition{Vec3{1.0f}},
      m_lightDirection{Vec3{1.0f}},
      m_isSpotlight{false}
    {

    }
    ~Light()
    {

    }

    void setLightPosition(Vec3 lightPosition)
    {
    m_lightPosition = lightPosition;
    }

    bool& isDirectional()
    {
    return m_isDirectional;
    } 

    Vec3& ambient()
    {
    return m_ambient;
    }
    Vec3& diffuse()
    {
    return m_diffuse;
    }

    Vec3& specular()
    {
    return m_specular;
    }

    Vec3& lightColor()
    {
    return m_lightColor;
    }

    Vec3& lightPosition()
    {
    return m_lightPosition;
    }

    Vec3& lightDirection()
    {
    return m_lightDirection;
    }

    bool& isSpotlight()
    {
    return m_isSpotlight;
    }
    
   private:
    bool m_isDirectional; 

    Vec3 m_ambient;
    Vec3 m_diffuse;
    Vec3 m_specular;

    Vec3 m_lightColor;
    Vec3 m_lightPosition;
    Vec3 m_lightDirection;

    bool m_isSpotlight;
};

inline void addLight(Ellipse::UniformList& uniformList, Light& light)
{
    uniformList.addUniform(Ellipse::UniformVarible<bool>{"lightObject.m_isDirectional", &light.isDirectional()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"lightObject.m_ambient", &light.ambient()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"lightObject.m_diffuse", &light.diffuse()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"lightObject.m_specular", &light.specular()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"lightObject.m_lightColor", &light.lightColor()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"lightObject.m_lightPosition", &light.lightPosition()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"lightObject.m_lightDirection", &light.lightDirection()});
    uniformList.addUniform(Ellipse::UniformVarible<bool>{"lightObject.m_isSpotlight", &light.isSpotlight()});
}

inline void addMaterials(Ellipse::UniformList& uniformList, ModelVal& modelVal)
{
    uniformList.addUniform(Ellipse::UniformVarible<Mat3>{"normalMatrixObject", modelVal.normalMatrix().get()});

    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"materialObject.m_ambient", modelVal.material().ambient().get()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"materialObject.m_diffuse", modelVal.material().diffuse().get()});
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"materialObject.m_specular.m_specular", modelVal.material().specular().get()});
    uniformList.addUniform(Ellipse::UniformVarible<float>{"materialObject.m_specular.m_reflectiveness", modelVal.material().reflectiveness().get()});

}

inline void addCamera(Ellipse::UniformList& uniformList, Ellipse::Camera& camera)
{
    uniformList.addUniform(Ellipse::UniformVarible<Vec3>{"cameraPositionObject", &camera.position()});

}

