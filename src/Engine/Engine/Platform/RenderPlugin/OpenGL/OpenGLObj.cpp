
#include "OpenGLObj.hpp"
#include "Debug/Log/Log.hpp"

namespace Ellipse
{

void OpenGLRenderObj::initBuffers(Vector<float> verts)
{
    uint32_t vbo;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);  

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 long(verts.size()) * long(sizeof(float)),
                 verts.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          3 * sizeof(float),
                          NULL);

    glBindVertexArray(0);
}

void OpenGLShaderObj::addShader(const char* name)
{
    compileShader(name);
}

void OpenGLShaderObj::linkShaders()
{
    linkGLShaders();
}

OpenGLShaderObj::OpenGLShaderObj()
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

void OpenGLShaderObj::addUniform(UniformVarible<i32_t> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<float> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<u32_t> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<Vec2> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<Vec3> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<Vec4> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<Mat2> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<Mat3> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}
void OpenGLShaderObj::addUniform(UniformVarible<Mat4> uniform)
{
     m_uniforms.addUniform(uniform);
     addUniformToList(uniform.name());
}

void OpenGLShaderObj::setUniformList(UniformList& uniforms)
{
     m_uniforms = uniforms;
}

void OpenGLShaderObj::setUniformPtr(const UniformVarible<i32_t>& uniform) 
{
     m_uniforms.setUniform(uniform);
}
void OpenGLShaderObj::setUniformPtr(const UniformVarible<float>& uniform)
{
     m_uniforms.setUniform(uniform);
}
void OpenGLShaderObj::setUniformPtr(const UniformVarible<u32_t>& uniform)
{
     m_uniforms.setUniform(uniform);
}
void OpenGLShaderObj::setUniformPtr(const UniformVarible<Mat4>& uniform)
{
     m_uniforms.setUniform(uniform);
}

void OpenGLShaderObj::compileShader(const char* fname)
{
     if(m_prog == 0)
     {
     m_prog = glCreateProgram();
     }

     FStreamIn ifs{fname};
     if(!ifs)
     {
     ELLIPSE_ENGINE_LOG_WARN("Could open file!" );
     }

     GLenum type = queryType(fname);

     unsigned int shader;
     shader = glCreateShader(type);
      
     SStream streamShader;
     streamShader << ifs.rdbuf();

     String strShader{streamShader.str()};
     const char* shaderSrc{strShader.c_str()};

     glShaderSource(shader, 1, &shaderSrc, NULL);
     glCompileShader(shader);

     checkCompileStatus(shader);

     glAttachShader(m_prog, shader);
}

void OpenGLShaderObj::linkGLShaders()
{
     if(m_prog == 0)
     {
     ELLIPSE_ENGINE_LOG_WARN("No program handle!\n");
     }

     glLinkProgram(m_prog);

     checkLinkStatus();

     deleteAttachedShaders();
}

void OpenGLShaderObj::use() const
{
     if(m_prog == 0)
     {
     ELLIPSE_ENGINE_LOG_WARN("Invalid shader program handle\n");
     }
     glUseProgram(m_prog);
}

void OpenGLShaderObj::addUniformsToLocList(UniformList uniforms)
{
     for(UniformVarible<i32_t>& uniform : uniforms.getIntUniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<float>& uniform : uniforms.getFloatUniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<u32_t>& uniform : uniforms.getUnsignedIntUniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<Vec2>& uniform : uniforms.getVec2Uniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<Vec3>& uniform : uniforms.getVec3Uniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<Vec4>& uniform : uniforms.getVec4Uniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<Mat2>& uniform : uniforms.getMat2Uniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<Mat3>& uniform : uniforms.getMat3Uniforms())
     {
     addUniformToList(uniform.name());
     }
     for(UniformVarible<Mat4>& uniform : uniforms.getMat4Uniforms())
     {
     addUniformToList(uniform.name());
     }
}

void OpenGLShaderObj::addUniformToList(const char* name)
{
     int loc =  glGetUniformLocation(m_prog, name);
     m_uniformLoc.push_front(UniformLoc{name, loc});
}

void OpenGLShaderObj::checkCompileStatus(GLuint shader)
{
     int status;
     char logLoad[500];
     
     GLint type;
     glGetShaderiv(shader, GL_SHADER_TYPE, &type);
     const char* typeStr = typeToCString(GLenum(type));
   
     // [ Better logging output, currently logs entire array ]
     glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
     if(!status)
     {
     glGetShaderInfoLog(shader, 500, NULL, logLoad);
     ELLIPSE_ENGINE_LOG_WARN("{} error {}", typeStr, logLoad);
     }
}

void OpenGLShaderObj::checkLinkStatus()
{
     if(m_prog == 0)
     {
     ELLIPSE_ENGINE_LOG_WARN("No program handle!\n");
     }

     int status;
     char logLoad[500];
   
     glGetProgramiv(m_prog, GL_LINK_STATUS, &status);

     if(!status)
     {
     glGetProgramInfoLog(m_prog, 500, NULL, logLoad);
     ELLIPSE_ENGINE_LOG_WARN("Linking error: {}", logLoad);
     }
}

// [ Not a good name, prints uniform names ]
void OpenGLShaderObj::printUniformLocations()
{
    for(auto& a : m_uniformLoc)
    {
    ELLIPSE_ENGINE_LOG_INFO("{}", a.m_name);
    } 
}

GLenum OpenGLShaderObj::queryType(const char* fname)
{
    auto newStr = createUnique<char[]>(strlen(fname) + 1);
    strcpy(newStr.get(), fname);

    u64_t extSize = 0;
    u64_t  numExtentions = 0;

    for(auto i = newStr.get(); *i != '\0'; i++)
    {
    if(*i == '.')
    {
    numExtentions++;
    }
    }

    auto extensionAmount = createUnique<unsigned long[]>(numExtentions);
    auto extensionLoc = createUnique<unsigned long[]>(numExtentions);

    unsigned long extAmountIdx = 0;
    const char* ext = newStr.get();

    unsigned long idx = 0; 

    for(auto i = newStr.get(); *i != '\0'; i++)
    {
    if(*i == '.')
    {
    ext += idx + 1;
    for(; *ext != '.'; ext++)
    {
    if(*ext == '\0')
    {
    break;
    }

    extSize++;
    }

    ext = newStr.get();

    extensionLoc[extAmountIdx] = idx;

    extensionAmount[extAmountIdx] = extSize;
    extAmountIdx++;
    extSize = 0;
    }
    idx++;
    }

    auto extension = createUnique<char[]>(extensionAmount[0]);
    auto glsl = createUnique<char[]>(extensionAmount[1]);

    for(unsigned long i = 0; i < extensionAmount[0]; i++)
    {
    extension[i] = newStr[i + extensionLoc[0] + 1];
    }

    for(unsigned long i = 0; i < extensionAmount[1]; i++)
    {
    glsl[i] = newStr[i + extensionLoc[1] + 1];
    }

    for(const auto& [key, val] : m_typeMap)
    {
    if(strcmp(extension.get(), key) == 0)
    {
    return val;
    // return convertGLType()
    }
    }

    return m_typeMap["none"];
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
    glGetProgramiv(m_prog, GL_ATTACHED_SHADERS, &count);
    auto shaders = createUnique<GLuint[]>(GLuint(count));

    glGetAttachedShaders(m_prog,
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
