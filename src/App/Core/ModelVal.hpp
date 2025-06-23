#pragma once

#include "Material.hpp"

#include "Ellipse.hpp"


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

    Mat4& model()
    {
    return m_model;
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

