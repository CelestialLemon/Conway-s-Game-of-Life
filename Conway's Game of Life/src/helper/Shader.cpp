#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

ShaderSourceCode ParseShaderSource(const std::string& filepath)
{
std::ifstream stream(filepath);
std::string line;
std::stringstream ss[2];
ShaderType type = ShaderType::NONE;

while (getline(stream, line))
{
    if (line.find("#shader") != std::string::npos)
    {
        if (line.find("vertex") != std::string::npos) type = ShaderType::VERTEX;
        if (line.find("fragment") != std::string::npos) type = ShaderType::FRAGMENT;
    }
    else
    {
        if (type == ShaderType::VERTEX) ss[0] << line << '\n';
        else if (type == ShaderType::FRAGMENT) ss[1] << line << '\n';
    }
}

return { ss[0].str(), ss[1].str() };
}

GLuint CompileShader(GLenum type, const std::string& source)
{
    GLuint shaderID = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    // check compilation result
    int result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        // error during compilation
        // print error to console
        int errorLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength);
        char* errorMessage = (char*)malloc(sizeof(char) * errorLength);
        glGetShaderInfoLog(shaderID, errorLength, nullptr, errorMessage);

        std::string shaderType = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
        std::cout << "Error compiling " << type << "\n";
        std::cout << "Message : " << errorMessage << "\n";
    }

    return shaderID;
}

GLuint CreateShader(const std::string& filepath)
{
    ShaderSourceCode shaderSourcecode = ParseShaderSource(filepath);

    GLuint vs = CompileShader(GL_VERTEX_SHADER, shaderSourcecode.VertexShaderCode);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, shaderSourcecode.FragmentShaderCode);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}