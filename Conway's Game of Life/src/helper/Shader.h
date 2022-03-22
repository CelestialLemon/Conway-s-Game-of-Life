#pragma once
#include <GL/glew.h>
#include <string>

struct ShaderSourceCode
{
    std::string VertexShaderCode;
    std::string FragmentShaderCode;
};

enum class ShaderType
{
    VERTEX = 0,
    FRAGMENT = 1,
    NONE = -1
};

ShaderSourceCode ParseShaderSource(const std::string& filepath);
GLuint CompileShader(GLenum type, const std::string& source);
GLuint CreateShader(const std::string& filepath);

