
#include "OpenGLObj.hpp"
#include "Debug/Log/Log.hpp"

void OpenGLRenderObj::initRenderObj(Vector<float> verts)
{
       m_nVerts = static_cast<uint32_t>(verts.size()) / 3;
       initBuffers(verts);
}

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
    m_typeMap = 
             {
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

void OpenGLShaderObj::compileShader(const char* fname)
{
      if(m_prog == 0)
       {
     m_prog = glCreateProgram();
       }

     FStreamIn ifs{fname};
      if(!ifs)
       {
     ELPSE_ENGINE_LOG_WARN("Could open file!" );
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
     ELPSE_ENGINE_LOG_WARN("No program handle!\n");
      }

      glLinkProgram(m_prog);

      checkLinkStatus();

      deleteAttachedShaders();
}

void OpenGLShaderObj::use() const
{
    if(m_prog == 0)
      {
    ELPSE_ENGINE_LOG_WARN("Invalid shader program handle\n");
      }
    glUseProgram(m_prog);
}

void OpenGLShaderObj::checkCompileStatus(GLuint shader)
{
     int status;
     char logLoad[500];
     
     GLint type;
     glGetShaderiv(shader, GL_SHADER_TYPE, &type);
     const char* typeStr = typeToCString(GLenum(type));
   
     glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
      if(!status)
       {
     glGetShaderInfoLog(shader, 500, NULL, logLoad);
     ELPSE_ENGINE_LOG_WARN("{} error {}", typeStr, logLoad);
       }
}

void OpenGLShaderObj::checkLinkStatus()
{
      if(m_prog == 0)
       {
      ELPSE_ENGINE_LOG_WARN("No program handle!\n");
       }

     int status;
     char logLoad[500];
   
     glGetProgramiv(m_prog, GL_LINK_STATUS, &status);

     if(!status)
      {
     glGetProgramInfoLog(m_prog, 500, NULL, logLoad);
     ELPSE_ENGINE_LOG_WARN("Linking error: {}", logLoad);
      }
}

void OpenGLShaderObj::addUniform(const char* name)
{
    GLint loc =  glGetUniformLocation(m_prog, name);
    m_uniformLoc.push_front(UniformLoc{name, loc});
}

void OpenGLShaderObj::addUniform(const char* name, int& loc)
{
    loc =  glGetUniformLocation(m_prog, name);
    m_uniformLoc.push_front(UniformLoc{name, loc});
}

void OpenGLShaderObj::setUniform(const char* name, float x)
{
    int loc = findUniformLocation(name);
     glUniform1f(loc, x);
}

void OpenGLShaderObj::setUniform(const char* name, float x, float y)
{
    int loc = findUniformLocation(name);
     glUniform2f(loc, x, y);
}

void OpenGLShaderObj::setUniform(const char* name, float x, float y, float z)
{
    int loc = findUniformLocation(name);
     glUniform3f(loc, x, y, z);
}

void OpenGLShaderObj::setUniform(const char* name, float x, float y, float z, float w)
{
    int loc = findUniformLocation(name);
     glUniform4f(loc, x, y, z, w);
}

void OpenGLShaderObj::setUniform(const char* name, int x)
{
    int loc = findUniformLocation(name);
     glUniform1i(loc, x);
}

void OpenGLShaderObj::setUniform(const char* name, int x, int y)
{
    int loc = findUniformLocation(name);
     glUniform2i(loc, x, y);
}

void OpenGLShaderObj::setUniform(const char* name, int x, int y, int z)
{
    int loc = findUniformLocation(name);
     glUniform3i(loc, x, y, z);
}

void OpenGLShaderObj::setUniform(const char* name, int x, int y, int z, int w)
{
    int loc = findUniformLocation(name);
     glUniform4i(loc, x, y, z, w);
}

void OpenGLShaderObj::setUniform(const char* name, unsigned int x)
{
    int loc = findUniformLocation(name);
     glUniform1ui(loc, x);
}

void OpenGLShaderObj::setUniform(const char* name, unsigned int x, unsigned int y)
{
    int loc = findUniformLocation(name);
     glUniform2ui(loc, x, y);
}

void OpenGLShaderObj::setUniform(const char* name, unsigned int x, unsigned int y, unsigned int z)
{
    int loc = findUniformLocation(name);
     glUniform3ui(loc, x, y, z);
}

void OpenGLShaderObj::setUniform(const char* name, unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
    int loc = findUniformLocation(name);
     glUniform4ui(loc, x, y, z, w);
}

void OpenGLShaderObj::setUniform(const char* name, glm::mat4& mat)
{
    int loc = findUniformLocation(name);
     glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void OpenGLShaderObj::setUniform(const char* name, glm::vec3& vec)
{
    int loc = findUniformLocation(name);
     glUniform3f(loc, vec.x, vec.y, vec.z);
}

void OpenGLShaderObj::printUniformLocations()
{
    for(auto& a : m_uniformLoc)
     {
    ELPSE_ENGINE_LOG_INFO("{}", a.m_name);
     } 
}

int OpenGLShaderObj::findUniformLocation(const char* name)
{
    for(auto& a : m_uniformLoc)
     {
    if(strcmp(name, a.m_name) == 0)
      {
    return a.m_loc;
      }
     } 

    int loc;
    addUniform(name, loc);

    return loc;
}

GLenum OpenGLShaderObj::queryType(const char* fname)
{
   auto newStr = createUnique<char[]>(strlen(fname) + 1);
   strcpy(newStr.get(), fname);

   unsigned long extSize = 0;
   unsigned long numExtentions = 0;

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
