
#include "OpenGLObj.hpp"
#include "Core/Formatter.hpp"
#include "Debug/Log.hpp"

namespace Ellipse
{

OpenGLShaderObj::OpenGLShaderObj()
: m_shaderProgram{0}
{
    m_typeMap = {
           {"vert", GL_VERTEX_SHADER},
           {"Vert", GL_VERTEX_SHADER},
           {"vertex", GL_VERTEX_SHADER},
           {"frag", GL_FRAGMENT_SHADER},
           {"Frag", GL_FRAGMENT_SHADER},
           {"fragment", GL_FRAGMENT_SHADER},
           {"none", 0}
                };
}

OpenGLShaderObj::~OpenGLShaderObj()
{
    deleteAttachedShaders();
}

void OpenGLShaderObj::addShader(const char* name)
{
    compileShader(name);
}

void OpenGLShaderObj::linkShaders()
{
    linkGLShaders();
}

void OpenGLShaderObj::compileShader(const char* fname)
{
     if(m_shaderProgram == 0)
     {
     m_shaderProgram = glCreateProgram();
     }

     FStreamIn ifs{fname};
     if(!ifs)
     {
     ELLIPSE_ENGINE_LOG_WARN("Could not open {}", fname);
     }

     GLenum type = queryType(fname);

     u32_t shader = 0;
     shader = glCreateShader(type);
      
     SStream streamShader;
     streamShader << ifs.rdbuf();

     String strShader{streamShader.str()};
     const char* shaderSrc{strShader.c_str()};

     glShaderSource(shader, 1, &shaderSrc, NULL);
     glCompileShader(shader);


     checkCompileStatus(shader);

     glAttachShader(m_shaderProgram, shader);
}

void OpenGLShaderObj::linkGLShaders()
{
     if(m_shaderProgram == 0)
     {
     ELLIPSE_ENGINE_LOG_WARN("No program handle!\n");
     }

     glLinkProgram(m_shaderProgram);

     checkLinkStatus();

     deleteAttachedShaders();
}

void OpenGLShaderObj::use() const
{
     if(m_shaderProgram == 0)
     {
     ELLIPSE_ENGINE_LOG_WARN("Invalid shader program handle");
     }

     glUseProgram(m_shaderProgram);
}

void OpenGLShaderObj::getShaderSource()
{
    i32_t count = 0;
    glGetProgramiv(m_shaderProgram, GL_ATTACHED_SHADERS, &count);
    auto shaders = createUnique<u32_t[]>(GLuint(count));
    glGetAttachedShaders(m_shaderProgram,
                         sizeof(shaders.get()),
                         NULL,
                         shaders.get()
                        );
    
    for(i32_t i=0;i<count;i++)
    {
    UniquePtr<char[]> source = createUnique<char[]>(static_cast<u64_t>(8192));
    i32_t length = 0;
    glGetShaderSource(shaders[static_cast<u64_t>(i)], 8192, &length, source.get());
    ELLIPSE_ENGINE_LOG_INFO("source {}", source.get());
    }
}

i32_t OpenGLShaderObj::findUniformLocation(const char* name)
{
     return glGetUniformLocation(m_shaderProgram, name);
}

Map<const char*, i32_t> OpenGLShaderObj::findUniformLocationList(UniformList uniformList)
{
    Map<const char*, i32_t> uniformLocations;
    for(UniformVarible<i32_t>& uniform : uniformList.getIntUniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    for(UniformVarible<float>& uniform : uniformList.getFloatUniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    for(UniformVarible<u32_t>& uniform : uniformList.getUnsignedIntUniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    // // [ Setting vectors and matricies one at a time, maybe have
    //      a single list of all ]
    for(UniformVarible<Vec2>& uniform : uniformList.getVec2Uniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    for(UniformVarible<Vec3>& uniform : uniformList.getVec3Uniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    for(UniformVarible<Vec4>& uniform : uniformList.getVec4Uniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    for(UniformVarible<Mat2>& uniform : uniformList.getMat2Uniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    for(UniformVarible<Mat3>& uniform : uniformList.getMat3Uniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    for(UniformVarible<Mat4>& uniform : uniformList.getMat4Uniforms())
    {
    const char* uniformName = uniform.name();
    i32_t loc = findUniformLocation(uniformName);
    uniformLocations[uniformName] = loc;
    }

    return uniformLocations;
}

void OpenGLShaderObj::checkCompileStatus(GLuint shader)
{
     i32_t status = 0;
     UniquePtr<char[]> logLoad = createUnique<char[]>(static_cast<u64_t>(500));
     
     GLint type = 0;
     glGetShaderiv(shader, GL_SHADER_TYPE, &type);
     const char* typeStr = typeToCString(GLenum(type));
   
     glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
     if(!status)
     {
     glGetShaderInfoLog(shader, 500, NULL, logLoad.get());
     ELLIPSE_ENGINE_LOG_WARN("{} error {}", typeStr, logLoad.get());
     }
}

void OpenGLShaderObj::checkLinkStatus()
{
     if(m_shaderProgram == 0)
     {
     ELLIPSE_ENGINE_LOG_WARN("No program handle!\n");
     }

     int status;
     char logLoad[500];
   
     glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);

     if(!status)
     {
     glGetProgramInfoLog(m_shaderProgram, 500, NULL, logLoad);
     ELLIPSE_ENGINE_LOG_WARN("Linking error: {}", logLoad);
     }
}

// [ Not a good name, prints uniform names ]
// void OpenGLShaderObj::printUniformLocations()
// {
//     for(auto& a : m_uniformLoc)
//     {
//     ELLIPSE_ENGINE_LOG_INFO("{}", a.m_name);
//     } 
// }

GLenum OpenGLShaderObj::queryType(const char* fname)
{
    String dest;
    String fileData = fname;

    String shader;
    String glsl;

    Pair<bool, bool> isShaderGlsl{false, false};
    for(u64_t i=0;i<fileData.size();i++)
    {
    if(fileData[i] == '.')
    {
    if(isShaderGlsl.first && isShaderGlsl.second)
    {
    ELLIPSE_ENGINE_LOG_INFO("Not a valid file type");   
    return m_typeMap["none"];
    }
    if(isShaderGlsl.first && (!isShaderGlsl.second))
    {
    isShaderGlsl.second = true;
    }
    if(!isShaderGlsl.first)
    {
    isShaderGlsl.first = true;
    }

    i++;
    if(i == fileData.size())
    {
    break;
    }
    }

    if(isShaderGlsl.first && (!isShaderGlsl.second))
    {
    shader.push_back(fileData[i]);
    }

    if(isShaderGlsl.first && isShaderGlsl.second)
    {
    glsl.push_back(fileData[i]);
    }

    }

    return m_typeMap[shader];
}
const char* OpenGLShaderObj::typeToCString(GLenum type)
{
    switch (type) 
    {
    case GL_VERTEX_SHADER:
    return "vertex shader";
    case GL_FRAGMENT_SHADER:
    return "fragment shader";
    default:
    return "Not a valid type";
    }
    return "Not a valid type";
}

void OpenGLShaderObj::deleteAttachedShaders()
{
    GLint count;
    glGetProgramiv(m_shaderProgram, GL_ATTACHED_SHADERS, &count);
    auto shaders = createUnique<GLuint[]>(GLuint(count));

    glGetAttachedShaders(m_shaderProgram,
                        sizeof(shaders.get()),
                        NULL,
                        shaders.get()
                        );

    for(GLuint i = 0; i < GLuint(count); i++)
    {
    glDeleteShader(shaders[i]);
    }
}

}    // namespace Ellipse
