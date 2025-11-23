#pragma once
#include "ECS/Component.h"
#include <string>
#include <GL/glew.h>

class MeshRenderer : public Component {
public:
    GLuint shaderProgram;
    GLuint vertexshader;
    GLuint fragmentshader;

    MeshRenderer();
    ~MeshRenderer();

    void Start() override;
    void Update() override;

    const char* GetComponentName() const override;

private:
    std::string LoadShader(const std::string& filepath);
    GLuint compileShader(GLenum type, const char* src);
    void CheckShaderErrors(GLuint shader);
};
