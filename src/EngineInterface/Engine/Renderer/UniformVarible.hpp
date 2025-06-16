#pragma once

#include "Core/Base.hpp"
#include "Debug/Log.hpp"

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
    ELLIPSE_ENGINE_LOG_INFO("Uniform name: {}", m_name);
    for(unsigned int i = 0; i < m_size;i++)
    {
    std::cout << *(m_uniformValues.get()[i]) << '\n';;
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

    void addUniform(const UniformVarible<bool>& uniform)
    {
    m_boolUniforms.push_back(uniform);
    }

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

    ELLIPSE_ENGINE_LOG_WARN("Couldn't find uniform when setting");
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

    ELLIPSE_ENGINE_LOG_WARN("Couldn't find uniform when setting");
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

    Vector<UniformVarible<bool>> getBoolUniforms()
    {
    return m_boolUniforms;
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
    for(const UniformVarible<Mat4>& uniform : m_mat4Uniforms)
    {
    if(strcmp(uniform.name(), name) == 0)
    {
    return uniform;
    }
    }


    // Returning a null mat4, maybe creating shared a getting
    // underlying ptr will cause bugs
    ELLIPSE_ENGINE_LOG_WARN("Couldn't find uniform, returing invalid mat");
    return UniformVarible<Mat4>{"Null", createShared<Mat4>().get()};
    }
    
    void printMat4UniformList()
    {
    for(const UniformVarible<Mat4>& uniform : m_mat4Uniforms)
    {
    const char* uniformName = uniform.name();

    float x0y0 = uniform.uniformAt(0)[0][0];
    float x1y0 = uniform.uniformAt(0)[1][0];
    float x2y0 = uniform.uniformAt(0)[2][0];
    float x3y0 = uniform.uniformAt(0)[3][0];
    float x0y1 = uniform.uniformAt(0)[0][1];
    float x1y1 = uniform.uniformAt(0)[1][1];
    float x2y1 = uniform.uniformAt(0)[2][1];
    float x3y1 = uniform.uniformAt(0)[3][1];
    float x0y2 = uniform.uniformAt(0)[0][2];
    float x1y2 = uniform.uniformAt(0)[1][2];
    float x2y2 = uniform.uniformAt(0)[2][2];
    float x3y2 = uniform.uniformAt(0)[3][2];
    float x0y3 = uniform.uniformAt(0)[0][3];
    float x1y3 = uniform.uniformAt(0)[1][3];
    float x2y3 = uniform.uniformAt(0)[2][3];
    float x3y3 = uniform.uniformAt(0)[3][3];

    ELLIPSE_ENGINE_LOG_INFO("Uniform name: {}\n Uniform values: [{} {} {} {}]\n                 [{} {} {} {}]\n                 [{} {} {} {}]\n                 [{} {} {} {}]",
                            uniformName, x0y0, x1y0, x2y0, x3y0, x0y1, x1y1, x2y1, x3y1, x0y2, x1y2, x2y2, x3y2, x0y3, x1y3, x2y3, x3y3);
    }

    }

    void printUniformList()
    {
    for(const auto& uniform : m_boolUniforms)
    {
    for(uLong_t i = 0; i < uniform.size(); i++)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform value: {}", uniform.uniformAt(i));
    }
    }

    for(const auto& uniform : m_intUniforms)
    {
    for(uLong_t i = 0; i < uniform.size(); i++)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform value: {}", uniform.uniformAt(i));
    }
    }


    for(const auto& uniform : m_floatUniforms)
    {
    for(uLong_t i = 0; i < uniform.size(); i++)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform value: {}", uniform.uniformAt(i));
    }
    }

    for(const auto& uniform : m_unsignedIntUniforms)
    {
    for(uLong_t i = 0; i < uniform.size(); i++)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform value: {}", uniform.uniformAt(i));
    }
    }

    for(const auto& uniform : m_vec2Uniforms)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform value: {} {}",
                           uniform.uniformAt(0).x,
                           uniform.uniformAt(0).y
                           );
    }

    for(const auto& uniform : m_vec3Uniforms)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform value: {} {} {}",
                           uniform.uniformAt(0).x,
                           uniform.uniformAt(0).y,
                           uniform.uniformAt(0).z
                           );
    }

    for(const auto& uniform : m_vec4Uniforms)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform value: {} {} {} {}",
                           uniform.uniformAt(0).x,
                           uniform.uniformAt(0).y,
                           uniform.uniformAt(0).z,
                           uniform.uniformAt(0).w
                           );
    }

    for(const auto& uniform : m_mat4Uniforms)
    {
    ELLIPSE_ENGINE_LOG_INFO("Uniform name: {}", uniform.name());
    uniform.printUniforms();
    }

    }

    void setUniformLocations(Map<const char*, i32_t> uniformLocations)
    {
    m_uniformLocations = uniformLocations;
    }

    Map<const char*, i32_t> uniformLocations() const
    {
    return m_uniformLocations;
    }


   private:
    Vector<UniformVarible<bool>> m_boolUniforms;

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

    Map<const char*, i32_t> m_uniformLocations;
};

struct UniformLoc
{
   public:
    const char* m_name;
    int m_loc;
};

}    // namespace Ellipse
