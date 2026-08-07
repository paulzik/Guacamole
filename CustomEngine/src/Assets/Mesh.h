#pragma once
#include <vector>
#include "Asset.h"
#include "Vertex.h"
#include <GL/glew.h>

class Mesh : public Asset
{
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

    // Uploads the geometry to the GPU, so a Mesh is never half-built.
    // Requires a live GL context - meshes are created by importers and the
    // primitive generator, both of which run after glewInit().
    Mesh(std::vector<Vertex> _vertices, std::vector<uint32_t> _indices);

    // Frees the GL objects. Defined in the .cpp so this header stays free of
    // OpenGL for everything that merely references a mesh.
    ~Mesh() override;

    // A Mesh owns GL handles, so copying one would make two objects delete the
    // same VAO/VBO/EBO. Meshes are shared assets held by shared_ptr and never
    // need copying - make the mistake a compile error instead of a double free.
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
};