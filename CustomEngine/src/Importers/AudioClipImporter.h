#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Importers/IAssetImporter.h"

class AudioClipImporter : public IAssetImporter
{
public:
    AudioClipImporter() = default;
    ~AudioClipImporter() override = default;

    // IAssetImporter interface
    std::shared_ptr<Asset> Load(const std::string& path) override;
};
