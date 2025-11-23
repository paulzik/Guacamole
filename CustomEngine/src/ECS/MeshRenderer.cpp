#include "MeshRenderer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/mat4x4.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ECS/MeshFilter.h"
#include "ECS/Entity.h"

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
    glUseProgram(shaderProgram);

    // -----------------------------
    // MODEL MATRIX
    // -----------------------------
    float scale = 1.0f;
    float posx = 0, posy = 0, posz = 0;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(posx, posy, posz));
    model = glm::rotate(model, 0.0f, glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(scale));

    // -----------------------------
    // VIEW MATRIX
    // -----------------------------
    glm::vec3 cameraPos(0, 0, 3);
    glm::mat4 view = glm::lookAt(
        cameraPos,              // camera position
        glm::vec3(0, 0, 0),     // look at
        glm::vec3(0, 1, 0)      // up
    );

    // -----------------------------
    // PROJECTION MATRIX
    // -----------------------------
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        1280.f / 720.f,          // aspect ratio
        0.1f, 100.f
    );

    // -----------------------------
    // SET UNIFORMS
    // -----------------------------
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "model"),
        1, GL_FALSE, glm::value_ptr(model)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "view"),
        1, GL_FALSE, glm::value_ptr(view)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "projection"),
        1, GL_FALSE, glm::value_ptr(projection)
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
        1, glm::value_ptr(cameraPos)
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