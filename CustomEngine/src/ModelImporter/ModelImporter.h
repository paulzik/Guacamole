#pragma once
#include <string>
#include <memory>
#include <vector>
#include <assimp/scene.h>
#include "IAssetImporter.h"
#include "Model.h"
#include "ECS/MeshFilter.h"

class ModelImporter : public IAssetImporter
{
public:
    ModelImporter() = default;
    ~ModelImporter() override = default;

    // IAssetImporter interface
    std::shared_ptr<Asset> Load(const std::string& path) override;

private:
    // Helpers for processing Assimp data
    std::vector<std::shared_ptr<MeshFilter>> ProcessScene(const aiScene* scene);
    std::shared_ptr<MeshFilter> ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
