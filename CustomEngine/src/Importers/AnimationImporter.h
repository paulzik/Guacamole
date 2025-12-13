#pragma once
#include <string>
#include <memory>
#include <vector>
#include <assimp/scene.h>
#include "Importers/IAssetImporter.h"

class Animationmporter : public IAssetImporter
{
public:
    Animationmporter() = default;
    ~Animationmporter() override = default;

    // IAssetImporter interface
    //std::shared_ptr<Asset> Load(const std::string& path) override;

private:
};
