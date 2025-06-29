#pragma once

#include "ModelVal.hpp"

#include "Ellipse.hpp"


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

