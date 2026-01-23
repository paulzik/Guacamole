#include "MeshFilter.h"
#include <glm/ext/vector_int4.hpp>


MeshFilter::MeshFilter(const std::vector<Vertex>& _vertices, const std::vector<uint32_t>& _indices)
	: vertices(_vertices), indices(_indices)
{
}

void MeshFilter::Start() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
        vertices.data(), GL_STATIC_DRAW);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
        indices.data(), GL_STATIC_DRAW);

    // position -> location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // color -> location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)(offsetof(Vertex, color)));
    glEnableVertexAttribArray(1);

    // normal -> location 2
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(2);

    // uv -> location 3
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)(offsetof(Vertex, uv)));
    glEnableVertexAttribArray(3);

    // bone IDs -> location 4 (integer)
    glVertexAttribIPointer(4, 4, GL_INT, sizeof(Vertex),
        (void*)(offsetof(Vertex, boneIDs)));
    glEnableVertexAttribArray(4);

    // bone weights -> location 5
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)(offsetof(Vertex, boneWeights)));
    glEnableVertexAttribArray(5);

    glBindVertexArray(0);
}


MeshFilter::~MeshFilter() {

}

GLsizei MeshFilter::GetIndexCount() {
    return indices.size();
}

int MeshFilter::GetTrianglesCount()
{
    return GetIndexCount()/3;
}

const char* MeshFilter::GetComponentName() const  {
	return "MeshFilter";
}