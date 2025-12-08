#pragma once
#include <string>
#include <memory>
#include <vector>
#include <assimp/scene.h>
#include "Importers/IAssetImporter.h"

class Texture2DImporter : public IAssetImporter
{
public:
    Texture2DImporter() = default;
    ~Texture2DImporter() override = default;

    // IAssetImporter interface
    std::shared_ptr<Asset> Load(const std::string& path) override;
private:

};
