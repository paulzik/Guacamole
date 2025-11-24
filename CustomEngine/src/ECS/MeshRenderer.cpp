#include "MeshRenderer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/mat4x4.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ECS/MeshFilter.h"
#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include "ECS/Scene.h"

MeshRenderer::MeshRenderer()
{
}


MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Start()
{
    std::string vertexShaderSrc = LoadShader("Shaders/BasicVertex.vert");
    std::string fragmentShaderSrc = LoadShader("Shaders/BasicFragment.frag");

    // Compile
    vertexshader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc.c_str());
    fragmentshader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc.c_str());

    CheckShaderErrors(vertexshader);
    CheckShaderErrors(fragmentshader);

    // Link
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexshader);
    glAttachShader(shaderProgram, fragmentshader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, log);
        std::cerr << "Program Link Error:\n" << log << std::endl;
    }
}

void MeshRenderer::Update()
{
    Transform& transform = owner->GetComponent<Transform>();

    glUseProgram(shaderProgram);

    // -----------------------------
    // SET UNIFORMS
    // -----------------------------
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "model"),
        1, GL_FALSE, glm::value_ptr(transform.getModelMatrix())
    );

    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "view"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().getCamera()->getViewMatrix())
    );

    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "projection"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().getCamera()->getProjectionMatrix())
    );

    // -----------------------------
    // LIGHTING
    // -----------------------------
    glm::vec3 lightPos(2, 2, 2);

    glUniform3fv(
        glGetUniformLocation(shaderProgram, "lightPos"),
        1, glm::value_ptr(lightPos)
    );

    glUniform3fv(
        glGetUniformLocation(shaderProgram, "viewPos"),
        1, glm::value_ptr(Scene::Get().getCamera()->getOwner()->GetComponent<Transform>().getPosition())
    );

    // -----------------------------
    // DRAW MESH
    // -----------------------------
    MeshFilter& mesh = owner->GetComponent<MeshFilter>();

    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);
}



GLuint MeshRenderer::compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

std::string MeshRenderer::LoadShader(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void MeshRenderer::CheckShaderErrors(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, NULL, log);
        std::cerr << "Shader Compile Error:\n" << log << std::endl;
    }
}


const char* MeshRenderer::GetComponentName() const  {
	return "MeshRenderer";
}