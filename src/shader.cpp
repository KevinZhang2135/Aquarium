#include <string.h>
#include "shader.h"

using namespace std;

// reads a file and outputs its contents as a string
string get_file_contents(const char *filename)
{
    ifstream file(filename, ios::binary);
    if (!file)
    {
        throw errno;
    }

    string contents;
    file.seekg(0, ios::end);
    contents.resize(file.tellg());

    file.seekg(0, ios::beg);
    file.read(&contents[0], contents.size());
    file.close();

    return contents;
}

Shader::Shader(const char *vertex_file, const char *fragment_file)
{
    // create vertex shader and reference
    string vertex_code = get_file_contents(vertex_file);
    const char *vertex_source = vertex_code.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);

    glCompileShader(vertex_shader);
    CompileErrors(vertex_shader, "VERTEX");

    // create fragment shader and reference
    string fragment_code = get_file_contents(fragment_file);
    const char *fragment_source = fragment_code.c_str();

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);

    glCompileShader(fragment_shader);
    CompileErrors(vertex_shader, "FRAGMENT");

    // link all shaders into the shader program
    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);

    glLinkProgram(id);
    CompileErrors(vertex_shader, "PROGRAM");

    // delete the now useless vertex and fragment shader objects
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::Activate()
{
    glUseProgram(id);
}

void Shader::Delete()
{
    glDeleteProgram(id);
}

void Shader::CompileErrors(unsigned int shader, const char *type)
{
    GLint has_compiled;
    char infoLog[1024]; // char array to store error message

    if (!std::strcmp(type, "PROGRAM"))
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
        if (has_compiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n"
                      << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_LINK_STATUS, &has_compiled);
        if (has_compiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for: " << type << "\n"
                      << std::endl;
        }
    }
}