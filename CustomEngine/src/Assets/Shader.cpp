#include "Shader.h"
#include "Importers/Resources.h"
#include <iostream>
#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint Shader::compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    CheckShaderErrors(shader);

    return shader;
}

void Shader::CheckShaderErrors(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[2048];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "Shader compile error:\n" << log << std::endl;
    }
}

std::shared_ptr<Shader> Shader::FromFiles(const std::string& vert, const std::string& frag)
{
    auto vs = Resources::Load(vert);
    auto fs = Resources::Load(frag);

    return std::make_shared<Shader>(vs, fs);
}

const std::shared_ptr<ShaderSource> Shader::GetVertexShader()
{
    return vertexShader;
}

const std::shared_ptr<ShaderSource> Shader::GetFragmentShader()
{
    return fragmentShader;
}

void Shader::SetUInt(const std::string& name, unsigned int value) const
{
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' not found!\n";
    }
    glUniform1ui(location, value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' not found!\n";
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetInt(const std::string& name, int value) const
{
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' not found!\n";
    }
    glUniform1i(location, value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' not found!\n";
    }
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetFloat(const std::string& name, float value) const
{
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: uniform '" << name << "' not found!\n";
    }
    glUniform1f(location, value);
}

Shader::Shader(std::shared_ptr<Asset> vertAsset, std::shared_ptr<Asset> fragAsset)
{
    vertexShader = std::dynamic_pointer_cast<ShaderSource>(vertAsset);
    fragmentShader = std::dynamic_pointer_cast<ShaderSource>(fragAsset);

    if (!vertexShader || !fragmentShader) {
        std::cerr << "ERROR: Shader assets are not ShaderSource!" << std::endl;
        return;
    }

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShader->sourceCode.c_str());
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader->sourceCode.c_str());

    // -------- LINK PROGRAM --------
    programID = glCreateProgram();
    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char log[2048];
        glGetProgramInfoLog(programID, sizeof(log), nullptr, log);
        std::cerr << "Shader link error:\n" << log << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    if (programID)
        glDeleteProgram(programID);
}
