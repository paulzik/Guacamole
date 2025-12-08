#include "Shader.h"
#include "Importers/Resources.h"
#include <iostream>
#include <memory>

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

Shader::Shader(std::shared_ptr<Asset> vertAsset,
    std::shared_ptr<Asset> fragAsset)
{
    auto vert = std::dynamic_pointer_cast<ShaderSource>(vertAsset);
    auto frag = std::dynamic_pointer_cast<ShaderSource>(fragAsset);

    if (!vert || !frag) {
        std::cerr << "ERROR: Shader assets are not ShaderSource!" << std::endl;
        return;
    }

    GLuint vs = compileShader(GL_VERTEX_SHADER, vert->sourceCode.c_str());
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, frag->sourceCode.c_str());

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
