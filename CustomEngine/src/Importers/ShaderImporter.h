#pragma once
#include <string>
#include <memory>
#include <vector>
#include <assimp/scene.h>
#include "Importers/IAssetImporter.h"
#include "Assets/Model.h"
#include "ECS/MeshFilter.h"

class ShaderImporter : public IAssetImporter
{
public:
    ShaderImporter() = default;
    ~ShaderImporter() override = default;

    // IAssetImporter interface
    std::shared_ptr<Asset> Load(const std::string& path) override;
private:

};
