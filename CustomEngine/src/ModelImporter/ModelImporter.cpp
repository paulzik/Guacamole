#include "ModelImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stdexcept>
#include <iostream>

std::shared_ptr<Asset> ModelImporter::Load(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_CalcTangentSpace |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices
    );

    if (!scene)
    {
        std::cerr << "Assimp failed: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    if (!scene->HasMeshes())
    {
        std::cerr << "Model has no meshes: " << path << std::endl;
        return nullptr;
    }

    if (!scene || !scene->HasMeshes())
    {
        throw std::runtime_error("Failed to load model: " + path + "\n" + importer.GetErrorString());
    }

    // Process all meshes into MeshFilters
    std::vector<std::shared_ptr<MeshFilter>> meshFilters = ProcessScene(scene);

    return std::make_shared<Model>(meshFilters);
}

bool ModelImporter::CanImport(const std::string& extension) const
{
    std::string ext = extension;
    if (ext[0] == '.') ext.erase(0, 1); // remove leading dot
    for (auto& c : ext) c = tolower(c);

    return ext == "fbx" || ext == "obj" || ext == "gltf" || ext == "glb";
}

std::vector<std::shared_ptr<MeshFilter>> ModelImporter::ProcessScene(const aiScene* scene)
{
    std::vector<std::shared_ptr<MeshFilter>> meshes;

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    return meshes;
}

std::shared_ptr<MeshFilter> ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    // Extract vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        
        // Positions
        vertex.position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        // Normals
        if (mesh->HasNormals())
        {
            vertex.normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            };
        }
        else
        {
            vertex.normal = { 0.0f, 1.0f, 0.0f };
        }

        // Colors (optional)
        if (mesh->HasVertexColors(0))
        {
            vertex.color = {
                mesh->mColors[0][i].r,
                mesh->mColors[0][i].g,
                mesh->mColors[0][i].b
            };
        }
        else
        {
            vertex.color = { 1.0f, 1.0f, 1.0f };
        }

        vertices.push_back(vertex);
    }

    // Extract indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return std::make_shared<MeshFilter>(vertices, indices);
}
