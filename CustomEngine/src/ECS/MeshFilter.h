#pragma once
#include "ECS/Component.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include <vector>
#include <GL/glew.h>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 uv;

    int boneIDs[4] = { 0 };       // max 4 bones per vertex
    float boneWeights[4] = { 0 };
};

struct MeshFilter : public Component {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

    MeshFilter(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    void Start() override;
    COMPONENT_NAME(MeshFilter);
};