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
};

class MeshFilter : public Component {
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

public:
    MeshFilter(const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices);
    ~MeshFilter();

    const char* GetComponentName() const override;

    const std::vector<Vertex>& GetVertices() const { return vertices; }
    const std::vector<uint32_t>& GetIndices() const { return indices; }

    GLuint GetVAO() const { return VAO; }
    void InitGPU();

    GLsizei GetIndexCount();

    int GetTrianglesCount();
};