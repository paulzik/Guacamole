#include "Mesh.h"
#include <iostream>
#include <utility>


Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<uint32_t> _indices)
    // Taken by value then moved: the parameters are already copies, so moving
    // avoids a second allocation of the whole vertex buffer.
    : vertices(std::move(_vertices)), indices(std::move(_indices)) {

    if (vertices.empty() || indices.empty()) {
        std::cerr << "Mesh: created with no geometry - it will not draw" << std::endl;
        return;
    }

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

    // 0 here means glGen* did nothing, which in practice means there was no GL
    // context yet - the mesh would silently never render.
    if (VAO == 0)
        std::cerr << "Mesh: failed to create a VAO - was a GL context current?" << std::endl;
}

Mesh::~Mesh()
{
    // glDelete* ignore 0, so no guard is needed for a mesh that never uploaded.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}