#pragma once
#include "ModelImporter/Asset.h"
#include <string>
#include <memory>

class IAssetImporter
{
public:
    virtual ~IAssetImporter() = default;
    virtual std::shared_ptr<Asset> Load(const std::string& path) = 0;
    virtual bool CanImport(const std::string& extension) const = 0;
};