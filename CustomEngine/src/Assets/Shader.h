#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>
#include "Asset.h"
#include "ShaderSource.h"

class Shader : public Asset {
public:
    GLuint programID = 0;

    Shader(std::shared_ptr<Asset> vert, std::shared_ptr<Asset> frag);
    ~Shader();

    void Bind() const { glUseProgram(programID); }
    void Unbind() const { glUseProgram(0); }

    static std::shared_ptr<Shader> FromFiles(const std::string& vertPath, const std::string& fragPath);

private:
    GLuint compileShader(GLenum type, const char* src);
    void CheckShaderErrors(GLuint shader);
};