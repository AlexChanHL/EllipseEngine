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

