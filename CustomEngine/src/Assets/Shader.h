#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>
#include "Asset.h"
#include "ShaderSource.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Shader : public Asset {
public:
    GLuint programID = 0;

    Shader(std::shared_ptr<Asset> vert, std::shared_ptr<Asset> frag);
    ~Shader();

    void Bind() const { glUseProgram(programID); }
    void Unbind() const { glUseProgram(0); }

    static std::shared_ptr<Shader> FromFiles(const std::string& vertPath, const std::string& fragPath);

    const std::shared_ptr<ShaderSource> GetVertexShader();
    const std::shared_ptr<ShaderSource> GetFragmentShader();

    void SetUInt(const std::string& name, unsigned int value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;

private:
    GLuint compileShader(GLenum type, const char* src);
    void CheckShaderErrors(GLuint shader);

    std::shared_ptr<ShaderSource> vertexShader;
    std::shared_ptr<ShaderSource> fragmentShader;

};