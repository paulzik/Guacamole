#include "Importers/AssetImporterRegistry.h"

std::unordered_map<std::string, IAssetImporter*> AssetImporterRegistry::s_Importers;

void AssetImporterRegistry::RegisterImporter(const std::string& ext, IAssetImporter* importer)
{
    s_Importers[ext] = importer;
}

IAssetImporter* AssetImporterRegistry::GetImporter(const std::string& ext)
{
    if (s_Importers.contains(ext))
        return s_Importers[ext];
    return nullptr;
}
