#pragma once
#include "IFieldVisitor.h"
#include "Importers/Resources.h"
#include "Assets/Asset.h"
#include <memory>
#include <string>

template<typename T>
void VisitAssetRef(IFieldVisitor& v, const char* name, std::shared_ptr<T>& asset)
{
    static_assert(std::is_base_of_v<Asset, T>, "T must derive from Asset");

    std::string path = asset ? asset->path : std::string();
    v.Visit(name, path);   // reuses the existing string overload - no new virtual

    if (v.IsReading() && !path.empty())
        asset = Resources::Load<T>(path);
}
