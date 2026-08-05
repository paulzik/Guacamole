#include "Importers/Resources.h"
#include "Importers/AssetImporterRegistry.h"
#include <filesystem>
#include <string>
#include <iostream>

std::filesystem::path Resources::Resolve(const std::string& path)
{
    const std::string scheme = EngineScheme;

    if (path.rfind(scheme, 0) == 0)
        return s_EnginePath / path.substr(scheme.size());

    return s_BasePath / path;
}

std::shared_ptr<Asset> Resources::Load(const std::string& path)
{
    std::filesystem::path fullPath = Resolve(path);

    if (!std::filesystem::exists(fullPath))
    {
        std::cerr << "File not found: " << fullPath.generic_string() << std::endl;
        return nullptr;
    }

    std::string extension = fullPath.extension().string();
    auto importer = AssetImporterRegistry::GetImporter(extension);

    if (!importer)
    {
        std::cout << "No importer found for extension: " << extension << " for path: " << path << std::endl;
        return nullptr;
    }

    std::shared_ptr<Asset> asset = importer->Load(fullPath.string());

    // Record where the asset came from, centrally, so every importer gets this
    // for free. The stored path is the one the caller passed in, so it can be
    // written into a scene file and handed back to Load() unchanged.
    if (asset)
    {
        asset->path = path;
        asset->name = fullPath.filename().string();
    }

    return asset;
}

void Resources::SetBasePath(const std::filesystem::path& path)
{
    s_BasePath = path;
}

const std::filesystem::path& Resources::GetBasePath()
{
    return s_BasePath;
}

void Resources::SetEnginePath(const std::filesystem::path& path)
{
    s_EnginePath = path;
}

const std::filesystem::path& Resources::GetEnginePath()
{
    return s_EnginePath;
}
