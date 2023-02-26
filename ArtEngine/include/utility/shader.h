#ifndef ARTENGINE_SHADER_H
#define ARTENGINE_SHADER_H

////////////////////////////////////////////////////////////////////////////////
//// SHADER BASE
////////////////////////////////////////////////////////////////////////////////

class ShaderBase
{
  public:
    ShaderBase();
    ~ShaderBase();

    static std::string read_glsl_file(std::string filename, int32_t &size);
    int add_program(std::string filename, GLenum shader_type);
    void compile(GLuint shader, std::string filename);
    void link(std::string filename);
    void use();
    static void error(GLuint shader, bool is_compile, std::string filename);

    static void ssbo(std::string name);
    static void ssbo(std::vector<std::string> names);
    void interface(std::string name);
    void interface(std::vector<std::string> names);

    template <typename T>
    static void bind(std::string name, Buffer *buffer);

    template <typename T>
    void uniform(std::string name, const T u);
    template <typename T, size_t N>
    void uniform(std::string name, const T (&u)[N]);
    template <typename T>
    void texture(std::string name, const T &t);

    static std::unordered_map<std::string, GLuint> sbpi; //!< shader binding point index

  protected:
    GLuint m_program;     //!< shader program id
    int m_bound_textures; //!< texture indexing

}; // class ShaderBase

template <typename T>
void ShaderBase::bind(std::string name, Buffer *buffer)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer->index);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, sbpi[name], buffer->index);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template <typename T>
void ShaderBase::uniform(std::string name, const T u)
{
    std::cout << "Error: Data type not recognized for uniform " << name << "." << std::endl;
}

template <typename T, size_t N>
void ShaderBase::uniform(std::string name, const T (&u)[N])
{
    std::cout << "Error: Data type not recognized for uniform " << name << "." << std::endl;
}

template <>
inline void ShaderBase::uniform(std::string name, const bool u)
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), u);
}

template <>
inline void ShaderBase::uniform(std::string name, const int u)
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), u);
}

template <>
inline void ShaderBase::uniform(std::string name, const float u)
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), u);
}

template <>
inline void ShaderBase::uniform(std::string name, const double u) // GLSL Intrinsically Single Precision
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), (float)u);
}

template <>
inline void ShaderBase::uniform(std::string name, const glm::vec2 u)
{
    glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &u[0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const glm::ivec2 u)
{
    glUniform2iv(glGetUniformLocation(m_program, name.c_str()), 1, &u[0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const glm::vec3 u)
{
    glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &u[0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const float (&u)[3])
{
    glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &u[0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const float (&u)[4])
{
    glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &u[0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const glm::vec4 u)
{
    glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &u[0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const glm::mat3 u)
{
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &u[0][0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const glm::mat4 u)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &u[0][0]);
}

template <>
inline void ShaderBase::uniform(std::string name, const std::vector<glm::mat4> u)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), u.size(), GL_FALSE, &u[0][0][0]);
}

template <typename T>
void ShaderBase::texture(std::string name, const T &texture)
{
    glActiveTexture(GL_TEXTURE0 + m_bound_textures);
    glBindTexture(texture.m_type, texture.m_texture);
    uniform(name, m_bound_textures++);
}

////////////////////////////////////////////////////////////////////////////////
//// SHADER
////////////////////////////////////////////////////////////////////////////////

class Shader : public ShaderBase
{
  public:
    template <typename... Args>
    Shader(std::vector<std::string> shaders, std::vector<std::string> in);
    Shader(std::vector<std::string> shaders);
    Shader(std::vector<std::string> shaders, std::vector<std::string> in);
    Shader(std::vector<std::string> shaders, std::vector<std::string> in, std::vector<std::string> buffer);
    ~Shader();

    void setup(std::vector<std::string> shaders);

  private:
    GLuint m_vertex_shader;
    GLuint m_geometry_shader;
    GLuint m_fragment_shader;

}; // class Shader

template <typename... Args>
Shader::Shader(std::vector<std::string> shaders, std::vector<std::string> in)
    : ShaderBase()
{
    // add individual shaders
    setup(shaders);
    for (int i = 0; i < in.size(); ++i)
        glBindAttribLocation(m_program, i, in[i].c_str());
    // link the shader program
    link(shaders[0]);
}

////////////////////////////////////////////////////////////////////////////////
//// COMPUTE
////////////////////////////////////////////////////////////////////////////////

class Compute : public ShaderBase
{
  public:
    Compute(std::string shader);
    Compute(std::string shader, std::vector<std::string> buffer);
    ~Compute();

    void dispatch(int x = 1, int y = 1, int z = 1, bool block = true);
    static void limits();

  private:
    GLuint m_compute_shader;

}; // class Compute

#endif // ARTENGINE_SHADER_H
