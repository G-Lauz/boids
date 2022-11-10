#include "shader.h"

boids::Shader::Shader(const char* vertex_path, const char* fragment_path) 
{
    // Fetch shaders code
    // ------------------------------------------------------------------------
    std::string vertex_code;
    std::string fragment_code;

    std::ifstream vertex_file;
    std::ifstream fragment_file;

    try
    {
        vertex_file.open(vertex_path);
        fragment_file.open(fragment_path);

        std::stringstream vertex_stream;
        std::stringstream fragment_stream;

        vertex_stream << vertex_file.rdbuf();
        fragment_stream << fragment_file.rdbuf();

        vertex_code = vertex_stream.str();
        fragment_code = fragment_stream.str();

        vertex_file.close();
        fragment_file.close();
    } 
    catch (std::ifstream::failure err)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << strerror(errno) << std::endl;
        vertex_file.close();
        fragment_file.close();
        exit(1);
    }

    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();

    // Compile and link shaders
    // ------------------------------------------------------------------------
    int success;
    char info_log[512];

    // Vertex shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) // Check if compile succesfully
    {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << info_log << std::endl;
        exit(1);
    }

    // Fragment shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) // Check if compile succesfully
    {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << info_log << std::endl;
        exit(1);
    }

    // Link shaders
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if(!success) // Check if linking succesfully
    {
        glGetProgramInfoLog(this->id, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << info_log << std::endl;
        exit(1);
    }

    // Cleaning
    glDetachShader(this->id, vertex);
    glDetachShader(this->id, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

boids::Shader::~Shader()
{
    glDeleteProgram(this->id);
}

void boids::Shader::use() 
{
    glUseProgram(this->id);
}

void boids::Shader::set_mat_4(const std::string &name, const GLfloat* mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_TRUE, mat);
}
