#include "Importers/Resources.h"
#include "Importers/AssetImporterRegistry.h"
#include <filesystem>
#include <string>
#include <iostream>

std::shared_ptr<Asset> Resources::Load(const std::string& path)
{
    std::filesystem::path fullPath = s_BasePath / path;

    if (!std::filesystem::exists(fullPath))
    {
        std::cerr << "File not found: " << fullPath << std::endl;
        return nullptr;
    }

    std::string extension = fullPath.extension().string();
    auto importer = AssetImporterRegistry::GetImporter(extension);

    if (!importer)
    {
        std::cout << "No importer found for extension: " << extension << std::endl;
        return nullptr;
    }

    return importer->Load(fullPath.string());
}

void Resources::SetBasePath(const std::filesystem::path& path)
{
    s_BasePath = path;
}

const std::filesystem::path& Resources::GetBasePath()
{
    return s_BasePath;
}
