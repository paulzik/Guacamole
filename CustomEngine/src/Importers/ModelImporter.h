#pragma once
#include <string>
#include <memory>
#include <vector>
#include <assimp/scene.h>
#include "Importers/IAssetImporter.h"
#include "Assets/Model.h"
#include "ECS/MeshFilter.h"

class ModelImporter : public IAssetImporter
{
public:
    // IAssetImporter interface
    std::shared_ptr<Asset> Load(const std::string& path) override;

private:
    // Helpers for processing Assimp data
    std::vector<std::shared_ptr<MeshFilter>> ProcessScene(const aiScene* scene);
    std::shared_ptr<MeshFilter> ProcessMesh(aiMesh* mesh, const aiScene* scene);

    std::shared_ptr<Skeleton> BuildSkeleton(const aiScene* scene);
    void ExtractBoneWeights(const aiScene* scene, std::vector<std::shared_ptr<MeshFilter>>& meshes,
        std::shared_ptr<Skeleton> skeleton);
    glm::mat4 AssimpToGLM(const aiMatrix4x4& from);

    void LoadSkeleton(const aiScene* scene, Model& model);
    std::vector<std::shared_ptr<Animation>> LoadAnimations(const aiScene* scene, std::shared_ptr<Skeleton> skeleton);
};
