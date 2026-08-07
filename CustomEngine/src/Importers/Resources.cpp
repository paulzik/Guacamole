#include "Importers/Resources.h"
#include "Importers/AssetImporterRegistry.h"
#include "ECS/PrimitiveFactory.h"
#include "Assets/Model.h"
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

// Built-in meshes have no file: they are generated on first request and then cached
static std::shared_ptr<Asset> CreateBuiltInMesh(const std::string& name)
{
    if (name == "Cube")   return PrimitiveFactory::CreateCubePrimitive();
    if (name == "Sphere") return PrimitiveFactory::CreateSpherePrimitive();

    std::cerr << "Unknown built-in mesh: " << name << std::endl;
    return nullptr;
}

static std::shared_ptr<Asset> LoadSubAsset(const std::string& basePath, int index)
{
    auto model = Resources::Load<Model>(basePath);
    if (!model)
        return nullptr;

    if (index < 0 || static_cast<size_t>(index) >= model->meshes.size())
    {
        std::cerr << "No sub-asset " << index << " on " << basePath << std::endl;
        return nullptr;
    }

    return model->meshes[index];
}

std::shared_ptr<Asset> Resources::Load(const std::string& path)
{
    if (auto cached = s_Cache.find(path); cached != s_Cache.end())
        return cached->second;

    if (auto hash = path.find('#'); hash != std::string::npos)
    {
        int index = -1;
        try
        {
            index = std::stoi(path.substr(hash + 1));
        }
        catch (const std::exception&)
        {
            std::cerr << "Malformed sub-asset path: " << path << std::endl;
            return nullptr;
        }

        std::shared_ptr<Asset> sub = LoadSubAsset(path.substr(0, hash), index);
        if (sub)
            s_Cache[path] = sub;
        return sub;
    }

    const std::string builtInMeshes = std::string(EngineScheme) + "Meshes/";
    if (path.rfind(builtInMeshes, 0) == 0)
    {
        std::shared_ptr<Asset> generated = CreateBuiltInMesh(path.substr(builtInMeshes.size()));
        if (!generated)
            return nullptr;

        generated->path = path;
        generated->name = path.substr(builtInMeshes.size());
        generated->OnPathAssigned();
        s_Cache[path] = generated;
        return generated;
    }

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

    if (asset)
    {
        asset->path = path;
        asset->name = fullPath.filename().string();
        asset->OnPathAssigned();

        s_Cache[path] = asset;
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
