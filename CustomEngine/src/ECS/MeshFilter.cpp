#include "MeshFilter.h"


MeshFilter::MeshFilter(const std::vector<Vertex>& _vertices, const std::vector<uint32_t>& _indices)
	: vertices(_vertices), indices(_indices)
{
}


void MeshFilter::InitGPU() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
        vertices.data(), GL_STATIC_DRAW);

    // Index buffer (EBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
        indices.data(), GL_STATIC_DRAW);

    // position -> location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // color -> location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    // normal -> location 2
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)(sizeof(glm::vec3) * 2));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}



void MeshFilter::Draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

MeshFilter::~MeshFilter() {

}

const char* MeshFilter::GetComponentName() const  {
	return "MeshFilter";
}