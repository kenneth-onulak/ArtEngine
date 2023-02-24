#include "pch.h"
#include "shader.h"

////////////////////////////////////////////////////////////////////////////////
//// SHADER BASE
////////////////////////////////////////////////////////////////////////////////

std::unordered_map<std::string, GLuint> ShaderBase::sbpi; //!< shader binding point index

ShaderBase::ShaderBase()
{
    m_program = glCreateProgram(); // generate shader
}

ShaderBase::~ShaderBase()
{
    glDeleteProgram(m_program);
}

std::string ShaderBase::read_glsl_file(std::string filename, int32_t &size)
{

    std::ifstream stream(filename);
    if (!stream.is_open())
    {
        std::cout << "Error: File opening \"" << filename << "\" failed." << std::endl;
        return "";
    }

    boost::filesystem::path local_dir = boost::filesystem::path(filename).parent_path();
    std::stringstream buffer;
    std::string line;
    std::string curr_line;

    while (std::getline(stream, curr_line))
    {
        line = curr_line;
        if (line.substr(0, 9) == "#include ")
        {
            int include_size = 0;
            buffer << read_glsl_file((local_dir / line.substr(9)).string(), include_size);
        }
        else
            buffer << line << "\n"; // line contains no newline characters, so add one here
    }
    std::string file_content(buffer.str());

    stream.close();

    size = file_content.length(); // set size
    return file_content;
}

int ShaderBase::add_program(std::string filename, GLenum shader_type)
{
    int32_t size;
    std::string result = read_glsl_file(filename, size);
    char *source = const_cast<char *>(result.c_str());

    int shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &source, &size);
    compile(shader_id, filename);

    return shader_id;
}

void ShaderBase::compile(GLuint shader, std::string filename)
{
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success)
        glAttachShader(m_program, shader);
    else
        error(shader, true, filename);
}

void ShaderBase::link(std::string filename)
{
    glLinkProgram(m_program);
    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
        error(m_program, false, filename);
}

void ShaderBase::use()
{
    m_bound_textures = 0;
    glUseProgram(m_program);
}

void ShaderBase::error(GLuint shader, bool is_compile, std::string filename)
{
    int n;
    if (is_compile)
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &n);
    else
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &n);

    char *info = new char[n]();
    if (is_compile)
        glGetShaderInfoLog(shader, n, &n, info);
    else
        glGetProgramInfoLog(shader, n, &n, info);

    std::cout << "Error: Linker Error (" << filename << "): " << info << std::endl;
    delete[] info;
}

void ShaderBase::ssbo(std::string name)
{
    // nothing to do if named binding point already exists
    if (sbpi.find(name) != sbpi.end())
        return;
    sbpi[name] = sbpi.size();
}

void ShaderBase::ssbo(std::vector<std::string> names)
{
    for (auto const &name : names)
        ssbo(name);
}

void ShaderBase::interface(std::string name)
{
    ssbo(name); // ensure the binding point exists
    glShaderStorageBlockBinding(m_program, glGetProgramResourceIndex(m_program, GL_SHADER_STORAGE_BLOCK, name.c_str()),
                                sbpi[name]);
}

void ShaderBase::interface(std::vector<std::string> names)
{
    for (auto const &name : names)
        interface(name);
}

////////////////////////////////////////////////////////////////////////////////
//// SHADER
////////////////////////////////////////////////////////////////////////////////

Shader::Shader(std::vector<std::string> shaders)
    : ShaderBase()
{
    setup(shaders);   // add individual shaders
    link(shaders[0]); // link the shader program
}

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

Shader::Shader(std::vector<std::string> shaders, std::vector<std::string> in, std::vector<std::string> buffer)
    : Shader(shaders, in)
{
    ssbo(buffer);
}

Shader::~Shader()
{
    glDeleteShader(m_fragment_shader);
    glDeleteShader(m_geometry_shader);
    glDeleteShader(m_vertex_shader);
}

void Shader::setup(std::vector<std::string> shaders)
{
    std::vector<std::string> s = shaders;

    if (s.size() < 2 || s.size() > 3)
    {
        std::cout << "Error: Number of shaders not recognized." << std::endl;
        return;
    }

    int index = 0;
    m_vertex_shader = add_program(s[index++], GL_VERTEX_SHADER);

    if (s.size() == 3) // optional geometry shader
        m_geometry_shader = add_program(s[index++], GL_GEOMETRY_SHADER);

    m_fragment_shader = add_program(s[index], GL_FRAGMENT_SHADER);
}

////////////////////////////////////////////////////////////////////////////////
//// COMPUTE
////////////////////////////////////////////////////////////////////////////////

Compute::Compute(std::string shader)
    : ShaderBase()
    , m_compute_shader(add_program(shader, GL_COMPUTE_SHADER))
{
    link(shader);
}

Compute::Compute(std::string shader, std::vector<std::string> buffer)
    : Compute(shader)
{
    ssbo(buffer);
}

Compute::~Compute()
{
    glDeleteShader(m_compute_shader);
}

void Compute::dispatch(int x, int y, int z, bool block)
{
    glDispatchCompute(x, y, z);
    if (block)
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void Compute::limits()
{
    std::function<int(GLenum)> const get_int = [](GLenum e) {
        int i;
        glGetIntegerv(e, &i);
        return i;
    };

    std::cout << "Max SSBO: " << get_int(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS) << std::endl;
    std::cout << "Max SSBO Block-Size: " << get_int(GL_MAX_SHADER_STORAGE_BLOCK_SIZE) << std::endl;
    std::cout << "Max Compute Shader Storage Blocks: " << get_int(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS) << std::endl;
    std::cout << "Max Shared Storage Size: " << get_int(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE) << std::endl;

    int n;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &n);
    std::cout << "Max Work Groups: " << n << std::endl;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &n);
    std::cout << "Max Local Size: " << n << std::endl;
}