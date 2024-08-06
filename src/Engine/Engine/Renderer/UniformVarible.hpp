#pragma once

#include "Core/Base.hpp"
#include "Debug/Log/Log.hpp"

namespace Ellipse
{

template<typename T>
class UniformVarible
{
   public:
    template<typename... Args>
    UniformVarible(const char* name, Args... args)
    {
    m_size = sizeof...(args);
    m_name = name;
    m_uniformValues = std::make_shared<T*[]>(m_size);

    T* argList[sizeof...(args)] = {(args)...};
    
    for(unsigned int i = 0; i < m_size ; i++)
    {
    m_uniformValues.get()[i] = argList[i];
    }
    }
   
    template<typename... Args>
    UniformVarible(const char* name, std::vector<T>& userUniform, Args... args)
    {
    m_size = sizeof...(args);
    m_name = name;
    m_uniformValues = std::make_shared<T*[]>(m_size);

    T argList[sizeof...(args)] = {(args)...};

    for(unsigned long i = 0; i < m_size; i++)
    {
    userUniform.push_back(argList[i]);
    }
    
    for(unsigned int i = 0; i < m_size ; i++)
    {
    m_uniformValues.get()[i] = &(userUniform[i]);
    }
    }

    const char* name() const
    {
    return m_name;
    }

    T uniformAt(unsigned long idx) const
    {
    return *(m_uniformValues.get()[idx]);
    }

    T* uniformPtr(uLong_t idx) const
    {
    return m_uniformValues.get()[idx];
    }

    T** getUniformData()
    {
    return m_uniformValues.get();
    }

    uLong_t size() const
    {
    return m_size;
    }


    void createUniformLink(unsigned long idx, T* val)
    {
    m_uniformValues.get()[idx] = val;
    }

    void printUniforms() const
    {
    std::cout << "Uniform name: " << m_name << '\n';
    for(unsigned int i = 0; i < m_size;i++)
    {
    std::cout << *(m_uniformValues.get()[i]) << '\n';
    }
    }

   private:
    const char* m_name;
    SharedPtr<T*[]> m_uniformValues;
    uLong_t m_size;
};

// [ Have pure vitual uniform list class so less expensive ]
class UniformList
{
   public:
    UniformList() = default;
    ~UniformList() = default;

    void addUniform(const UniformVarible<i32_t>& uniform)
    {
    m_intUniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<float>& uniform)
    {
    m_floatUniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<u32_t>& uniform)
    {
    m_unsignedIntUniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<Vec2>& uniform)
    {
    m_vec2Uniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<Vec3>& uniform)
    {
    m_vec3Uniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<Vec4>& uniform)
    {
    m_vec4Uniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<Mat2>& uniform)
    {
    m_mat2Uniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<Mat3>& uniform)
    {
    m_mat3Uniforms.push_back(uniform);
    }
    void addUniform(const UniformVarible<Mat4>& uniform)
    {
    m_mat4Uniforms.push_back(uniform);
    }

    void setUniform(const UniformVarible<i32_t>& uniform)
    {
    for(UniformVarible<int32_t>& a : m_intUniforms)
    {
    if(strcmp(a.name(), uniform.name()) == 0)
    {
    for(unsigned long i = 0; i < uniform.size(); i++)
    {
    int32_t** aPtr = a.getUniformData();
    int32_t* uPtr = uniform.uniformPtr(i);
    aPtr[i] = uPtr;
    }
    return;
    }
    }

    std::cout << "Couldn't find uniform when setting\n";
    }
    void setUniform(const UniformVarible<float>& uniform)
    {
    for(UniformVarible<float>& a : m_floatUniforms)
    {
    if(strcmp(a.name(), uniform.name()) == 0)
    {
    for(unsigned long i = 0; i < uniform.size(); i++)
    {
    float** aPtr = a.getUniformData();
    float* uPtr = uniform.uniformPtr(i);
    aPtr[i] = uPtr;

    }
    return;
    }
    }

    std::cout << "Couldn't find uniform when setting\n";
    }
    void setUniform(const UniformVarible<u32_t>& uniform)
    {
    for(UniformVarible<uint32_t>& a : m_unsignedIntUniforms)
    {
    if(strcmp(a.name(), uniform.name()) == 0)
    {
    for(unsigned long i = 0; i < uniform.size(); i++)
    {
    uint32_t** aPtr = a.getUniformData();
    uint32_t* uPtr = uniform.uniformPtr(i);
    aPtr[i] = uPtr;

    }
    return;
    }
    }
    }
    void setUniform(const UniformVarible<Mat4>& uniform)
    {
    for(UniformVarible<Mat4>& a : m_mat4Uniforms)
    {
    if(strcmp(a.name(), uniform.name()) == 0)
    {
    Mat4** aPtr = a.getUniformData();
    Mat4* uPtr = uniform.uniformPtr(0);
    aPtr[0] = uPtr;
    return;
    }
    }
    }
    
    Vector<UniformVarible<i32_t>> getIntUniforms()
    {
    return m_intUniforms;
    }
    Vector<UniformVarible<float>> getFloatUniforms()
    {
    return m_floatUniforms;
    }
    Vector<UniformVarible<u32_t>> getUnsignedIntUniforms()
    {
    return m_unsignedIntUniforms;
    }
    Vector<UniformVarible<Vec2>> getVec2Uniforms()
    {
    return m_vec2Uniforms;
    }
    Vector<UniformVarible<Vec3>> getVec3Uniforms()
    {
    return m_vec3Uniforms;
    }
    Vector<UniformVarible<Vec4>> getVec4Uniforms()
    {
    return m_vec4Uniforms;
    }
    Vector<UniformVarible<Mat2>> getMat2Uniforms()
    {
    return m_mat2Uniforms;
    }
    Vector<UniformVarible<Mat3>> getMat3Uniforms()
    {
    return m_mat3Uniforms;
    }
    Vector<UniformVarible<Mat4>> getMat4Uniforms()
    {
    return m_mat4Uniforms;
    }

    UniformVarible<Mat4> getMat4UniformFromListByName(const char* name)
    {
    for(const UniformVarible<Mat4>& u : m_mat4Uniforms)
    {
    if(strcmp(u.name(), name) == 0)
    {
    return u;
    }
    }
    // Returning a null mat4, maybe creating shared a getting
    // underlying ptr will cause bugs
    ELPSE_ENGINE_LOG_WARN("Couldn't find uniform, returing invalid mat");
    return UniformVarible<Mat4>{"Null", createShared<Mat4>().get()};
    }

    void printUniformList()
    {
    for(const auto& uniform : m_intUniforms)
    {
    for(uLong_t i = 0; i < uniform.size(); i++)
    {
    ELPSE_ENGINE_LOG_INFO("Uniform value: {}", uniform.uniformAt(i));
    }
    }


    for(const auto& uniform : m_floatUniforms)
    {
    for(uLong_t i = 0; i < uniform.size(); i++)
    {
    ELPSE_ENGINE_LOG_INFO("Uniform value: {}", uniform.uniformAt(i));
    }
    }

    for(const auto& uniform : m_unsignedIntUniforms)
    {
    for(uLong_t i = 0; i < uniform.size(); i++)
    {
    ELPSE_ENGINE_LOG_INFO("Uniform value: {}", uniform.uniformAt(i));
    }
    }

    for(const auto& uniform : m_vec2Uniforms)
    {
    ELPSE_ENGINE_LOG_INFO("Uniform value: {} {}",
                           uniform.uniformAt(0).x,
                           uniform.uniformAt(0).y
                           );
    }

    for(const auto& uniform : m_vec3Uniforms)
    {
    ELPSE_ENGINE_LOG_INFO("Uniform value: {} {} {}",
                           uniform.uniformAt(0).x,
                           uniform.uniformAt(0).y,
                           uniform.uniformAt(0).z
                           );
    }

    for(const auto& uniform : m_vec4Uniforms)
    {
    ELPSE_ENGINE_LOG_INFO("Uniform value: {} {} {} {}",
                           uniform.uniformAt(0).x,
                           uniform.uniformAt(0).y,
                           uniform.uniformAt(0).z,
                           uniform.uniformAt(0).w
                           );
    }

    for(const auto& uniform : m_mat4Uniforms)
    {
    ELPSE_ENGINE_LOG_INFO("Uniform name: {}", uniform.name());
    uniform.printUniforms();
    }

    }

   private:
    Vector<UniformVarible<i32_t>> m_intUniforms;
    Vector<UniformVarible<float>> m_floatUniforms;
    Vector<UniformVarible<u32_t>> m_unsignedIntUniforms;

    // [ Only taking into account float vectors
    //   and matricies, should be aware user
    //   may want to pass in other types ]

    Vector<UniformVarible<Vec2>> m_vec2Uniforms;
    Vector<UniformVarible<Vec3>> m_vec3Uniforms;
    Vector<UniformVarible<Vec4>> m_vec4Uniforms;
    Vector<UniformVarible<Mat2>> m_mat2Uniforms;
    Vector<UniformVarible<Mat3>> m_mat3Uniforms;
    Vector<UniformVarible<Mat4>> m_mat4Uniforms;
};

struct UniformLoc
{
   public:
    const char* m_name;
    int m_loc;
};

}    // namespace Ellipse
