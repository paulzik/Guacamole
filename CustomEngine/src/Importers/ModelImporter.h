#pragma once
#include <string>
#include <memory>
#include <vector>
#include <assimp/scene.h>
#include "Importers/IAssetImporter.h"
#include "Assets/Model.h"
#include "Assets/Vertex.h"

class ModelImporter : public IAssetImporter
{
public:
    // IAssetImporter interface
    std::shared_ptr<Asset> Load(const std::string& path) override;

private:
    // Plain geometry, before it becomes a Mesh. A Mesh uploads to the GPU in
    // its constructor, but bone weights are assigned in a later pass - so the
    // vertex data has to be finished first, or the weights would only ever
    // exist CPU-side and skinning would silently do nothing.
    struct MeshData
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    };

    // Helpers for processing Assimp data
    std::vector<MeshData> ProcessScene(const aiScene* scene);
    MeshData ProcessMesh(aiMesh* mesh, const aiScene* scene);

    std::shared_ptr<Skeleton> BuildSkeleton(const aiScene* scene);
    void ExtractBoneWeights(const aiScene* scene, std::vector<MeshData>& meshes,
        std::shared_ptr<Skeleton> skeleton);
    glm::mat4 AssimpToGLM(const aiMatrix4x4& from);

    void LoadSkeleton(const aiScene* scene, Model& model);
    std::vector<std::shared_ptr<Animation>> LoadAnimations(const aiScene* scene, std::shared_ptr<Skeleton> skeleton);
};
