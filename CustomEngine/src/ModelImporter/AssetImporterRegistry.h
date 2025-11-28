#pragma once
#include "ModelImporter/IAssetImporter.h"
#include <string>
#include <unordered_map>

class AssetImporterRegistry
{
public:
    static void RegisterImporter(const std::string& ext, IAssetImporter* importer);
    static IAssetImporter* GetImporter(const std::string& ext);

private:
    static std::unordered_map<std::string, IAssetImporter*> s_Importers;
};
